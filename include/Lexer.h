#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

class Token {
public:
    std::array<std::string, 20> KindT =
            {
                    "NONE",
                    "END",
                    "INT",
                    "FLOAT",
                    "ID",
                    "DOT",
                    "SEMI",
                    "ASSIGN",
                    "PLUS",
                    "MINUS",
                    "MULT",
                    "DIV",
                    "COMMA",
                    "LSQBCKT",
                    "RSQBCKT",
                    "KEYWORD"};

    enum class KIND {
        NONE,
        END,
        INT,
        FLOAT,
        ID,
        DOT,
        SEMI,
        ASSIGN,
        PLUS,
        MINUS,
        MULT,
        DIV,
        COMMA,
        LSQBCKT,
        RSQBCKT,
        KEYWORD
    }Kind;

    std::string Value;
    size_t LineNumber;


public:
    Token();

    explicit Token(KIND kind, size_t line_number, std::string value = "");
};

std::ostream &operator<<(std::ostream &os, Token &tok);

std::ostream &operator<<(std::ostream &os, Token::KIND &kind);

class Lexer {
private:
    // Keywords
    std::array<std::string, 10> KeyWords =
            {
                    "POINT",
                    "LINE"
            };

    std::ifstream FileStream;
    std::string FileName;
    size_t LineNumber;

    // Get Line Number
    size_t GetLineNumber() const;

    // Get Next Token
    Token GetNextToken();

    // Create Number Token
    Token CreateNumberToken();

    // Create Identifier
    Token CreateIDToken();

    // Error Handler
    enum class ERROR {
        FILE_NOT_FOUND,
        STREAM_BUSY
    };
    std::array<std::string, 10> ErrorMessage =
            {
                    FileName + "File could not be opened.",
                    "Lexer is already open."};

    void Error(ERROR Code);



    // Get File Name
    std::string GetFileName() const;

public:
    Lexer();

    explicit Lexer(std::string file_name);

    ~Lexer();

    // Open Token Stream
    void Open(std::string file_name);

    // Close Token Stream
    void Close();

    // Read Tokens
    std::vector<Token> Read();

};

inline size_t Lexer::GetLineNumber() const{
    return LineNumber;
}

#endif
