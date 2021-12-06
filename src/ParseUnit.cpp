#include "../include/Interface.h"

TOKEN Interface::GetNextToken()
{
    
}

bool Interface::ParseUnit(std::string Key)
{
    if (!IsKeyword((Key)))
        return false;
    if (Key == "POINT")
        ParsePoint();
    return true;
}
