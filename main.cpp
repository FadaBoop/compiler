#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "tokens.hpp"
#include "parser.hpp"

using namespace std;

map<string, tokenType> tokenMap{{"\\bprint",tokenType::print},
                                {"\n",tokenType::line},
                                {"\\b([a-zA-Z_][a-zA-Z0-9_]*)\\s*=",tokenType::variable},
                                {"=\\s*\\w+",tokenType::content},
                                {"[=\\*/\\-\\+]",tokenType::sign},
                                {"\\(\".*?\"\\)",tokenType::text} };
vector<token> tokens;

string text;

void read(){
    ifstream inputFile ("hyperion.hyp");
    if (inputFile.is_open())
    {
        stringstream buffer;
        buffer << inputFile.rdbuf();
        text = buffer.str();
        inputFile.close();
    }
}

vector<token> sort(vector<token> vec)
{
    int x;
    for(x = 0; x < vec.size(); x++)
        if(vec[x].type == tokenType::content)
            vec[x].position = vec[x].position + 2;
    x = 0;
    while(x < vec.size())
    {
        if(vec[x].position > vec[x+1].position)
        {
            vec.push_back(vec[x]);
            vec.erase(vec.begin() + x);
            x = 0;
        }
        else
            x++;
    }
    return vec;
}

int main()
{
    read();
    token currentMatch;
    size_t pos;
    for(const auto& [delimiters, tokenTypes] : tokenMap)
    {
        regex currentRegex (delimiters);
        sregex_iterator begin(text.begin(),text.end(), currentRegex);
        sregex_iterator end;

        for (regex_iterator i = begin; i!=end; i++)
        {
            smatch match = *i;
            string matched_str = match.str();
            matched_str.erase(remove(matched_str.begin(), matched_str.end(), '('), matched_str.end());
            matched_str.erase(remove(matched_str.begin(), matched_str.end(), ')'), matched_str.end());
            matched_str.erase(remove(matched_str.begin(), matched_str.end(), ' '), matched_str.end());
            if (matched_str != "=")
                matched_str.erase(remove(matched_str.begin(), matched_str.end(), '='), matched_str.end());
            currentMatch.initialize (tokenTypes,matched_str,match.position());
            tokens.push_back(currentMatch);
        }

    }
    tokens = sort(tokens);
    for(int x = 0;x < tokens.size();x++)
    {
        if (tokens[x].type != tokenType::line)
            cout << "Value: " << tokens[x].value << " | Pos: " << tokens[x].position << " | ";
        else
            cout << "Value: New Line | Pos: " << tokens[x].position << " | ";
        if (tokens[x].type == tokenType::sign)
            cout << "Type: Sign" << endl;
        else if (tokens[x].type == tokenType::line)
            cout << "Type: New Line" << endl;
        else if (tokens[x].type == tokenType::text)
            cout << "Type: Text" << endl;
        else if (tokens[x].type == tokenType::print)
            cout << "Type: Print" << endl;
        else if (tokens[x].type == tokenType::variable)
            cout << "Type: Variable" << endl;
        else if (tokens[x].type == tokenType::content)
            cout << "Type: Content" << endl;
    }
    parser(tokens);
}
