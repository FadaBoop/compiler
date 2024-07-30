#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <iostream>

using namespace std;

enum class tokenType {
    print, text, line, content, variable, sign
};

class token
{
    public:
        tokenType type;
        string value;
        int position,lposition;

        void initialize(tokenType tipo,string valor,int pos)
        {
            type=tipo;
            value=valor;
            position=pos;
        }
};

#endif
