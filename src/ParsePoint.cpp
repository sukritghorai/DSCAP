#include "../include/Parser.h"

void Parser::ParsePoint()
{
    size_t ID = GetID(Stream.GetCurrentToken().Value, 5);
    EatToken(Token::KIND::ASSIGN);
    switch (Stream.GetCurrentToken().Kind)
    {
    case Token::KIND::ID:
        
        break;
    
    default:
        break;
    } 
}
