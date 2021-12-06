#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <array>
#include <string>
#include <vector>

enum class TOKEN
{
    END,
    ID, NUMBER,
    POINT, TRVS, LINE
};


class Interface
{
private:
    // Error Handler
    enum class ERROR
    {
        FILE_NOT_FOUND,
        INVALID_KEYWORD,
        INVALID_POINT_ARGS,
        OPTIONS_NOT_REQD
    };
    void Error(ERROR Code);
    
    // Variables
    size_t LineNumber;
    std::ifstream FileStream;
    std::istringstream InputStringStream;

    // Built-in Functions
    std::array<std::string, 2> KeyWordList;

    // Parse Unit
    bool ParseUnit(std::string Key);

    // Parse Functions
    void ParsePoint();

    // Get Next Token
    TOKEN GetNextToken();

    
    // Utility Functions
    bool IsKeyword(std::string& Key);
    void OpenFile(std::string FileName);
    void ProcessFile();
    void CloseFile();

    public:
        Interface();
        Interface(std::string FileName);
        void Init(std::string FileName);
    };
