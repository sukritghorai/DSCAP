#include "../include/Interface.h"

Interface::Interface()
{
}

Interface::Interface(std::string FileName)
{
    Init(FileName);
}

void Interface::Init(std::string FileName)
{
    LineNumber = 0;
    KeyWordList = {
        "POINT",
        "LINE"
        };
    OpenFile(FileName);
    ProcessFile();
    CloseFile();
}

void Interface::OpenFile(std::string FileName)
{
    if (FileStream.is_open())
        FileStream.close();
    else
        FileStream.open(FileName);
    if (!FileStream.is_open())
        Error(ERROR::FILE_NOT_FOUND);
}

void Interface::CloseFile()
{
    if (FileStream.is_open())
        FileStream.close();
}

void Interface::Error(ERROR Code)
{
    std::array<std::string, 3> ErrorMessage =
    {
        "File could not be opened.",
        "Invalid Keyword.",
        "Point - Number of parameters must be 2."
    };
    std::cerr << "Error: " << ErrorMessage[static_cast<int>(Code)]
              << ", line " << LineNumber << std::endl;
    std::exit(-1);
}

bool Interface::IsKeyword(std::string& Key)
{
    std::transform(Key.begin(), Key.end(), Key.begin(),
                   [](char c)
                   { return std::toupper(c); });
    auto result = std::find_if(KeyWordList.begin(), KeyWordList.end(),
                               [Key](std::string str)
                               { return str.compare(Key); });
    if (result != std::end(KeyWordList))
        return true;
    return false;
}

void Interface::ProcessFile()
{
    std::string Line, Key;
    while (!FileStream.eof())
    {
        std::getline(FileStream, Line);
        // Check empty line
        if (Line.empty())
        {
            LineNumber++;
            continue;
        }
        else
        {
            InputStringStream.clear();
            InputStringStream.str(Line);
            InputStringStream >> Key;
            std::transform(Key.begin(), Key.end(), Key.begin(),
                           [](char c)
                           { return std::toupper(c); });
            // Check Comment Line
            if (Key[0] == '#')
            {
                LineNumber++;
                continue;
            }
            // Check Valid Keyword
            else if (ParseUnit(Key))
                continue;
            else
                Error(ERROR::INVALID_KEYWORD);
        }
    }
}

void Interface::ParsePoint()
{
    std::string Line, Key;
    std::getline(FileStream, Line);
    InputStringStream >> Key;
    if (!Key.empty())
        Error(ERROR::OPTIONS_NOT_REQD);
    while (!FileStream.eof())
    {
        
    }
    



std::vector<std::string> Parameters;

    InputStringStream.str(Line);
    InputStringStream >> Key;
    std::array<std::string, 2> Unit = {"TRVS"};

   
    // check options
    if (result != std::end(Unit))
    {
        int index = std::distance(Unit.begin(), result);
        switch (index)
        {
            case 1:
            break;
            default:
            Error(())
            break;


        }

    LineNumber++;
    do
    {
        std::getline(FileStream, Line);
        InputStringStream.clear();
        InputStringStream.str(Line);
        Parameters.clear();
        // Collect all parameters of the line
        while (std::getline(InputStringStream, Key, ' '))
            Parameters.push_back(Key);
        // Check empty line
        if (Parameters.size() == 0)
        {
            LineNumber++;
            continue;
        }
        // Check comments
        else if (Parameters[0][0] == '#')
        {   
            LineNumber++;
            continue;
        }
        else if (Parameters.size() != 3)
            Error(ERROR::INVALID_POINT_ARGS, LineNumber);
        else
        {
            LineNumber++;
            std::cout << "Point: " << std::stoi(Parameters[0]);
            std::cout << " (" << std::stod(Parameters[1]) << ", ";
            std::cout << std::stod(Parameters[2]) << ")" << std::endl;
        }

    } while (!FileStream.eof());
}

