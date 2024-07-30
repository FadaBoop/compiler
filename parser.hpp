#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "tokens.hpp"

using namespace std;

vector<pair<string,int>> nums;

void parser(vector<token> tokenized)
{
    int i,j=0;
    for (i = 0; i<tokenized.size();i++)
    {
        if (tokenized[i].type == tokenType::line)
        {
            // cout << tokenized[j].value << " ";
            if (tokenized[j].type == tokenType::variable && tokenized[j+1].value == "=" && tokenized[j+2].type == tokenType::content)
            {
                nums.emplace_back(tokenized[j].value,stoi(tokenized[j+2].value));
            }
            else if (tokenized[j].type == tokenType::print && tokenized[j+1].type == tokenType::variable)
            {
                cout << "Here";
                auto idkbro = find_if(nums.begin(), nums.end(), [&tokenized, j](const pair<string, int>& p) {return p.first == tokenized[j + 1].value;});
                if(idkbro != nums.end())
                    cout << idkbro->second << endl;
            }
            j=i+1;
        }
    }
}

#endif 
