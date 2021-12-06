#include <utility>

#include "../include/Lexer.h"

Token::Token()
        : Kind(KIND::NONE), LineNumber(1) {
}

Token::Token(KIND kind, size_t line_number, std::string value)
        : Kind(kind), Value(std::move(value)), LineNumber(line_number) {
}

std::ostream &operator<<(std::ostream &os, Token &Tok) {
    os << Tok.KindT[static_cast<int>(Tok.Kind)];
    if (Tok.Kind == Token::KIND::ID || Tok.Kind == Token::KIND::INT || Tok.Kind == Token::KIND::FLOAT || Tok.Kind == Token::KIND::KEYWORD)
        os << ": " << Tok.Value;
    return os;
}

std::ostream &operator<<(std::ostream &os, Token::KIND &Kind) {
    Token t;
    os << t.KindT[static_cast<int>(Kind)];
    return os;
}

Lexer::Lexer() {
    LineNumber = 1;
}

Lexer::Lexer(std::string file_name) {
    LineNumber = 1;
    Open(std::move(file_name));
}

void Lexer::Error(ERROR Code) {
    std::cerr << "File \"" << FileName << "\", line "
              << LineNumber << std::endl;
    std::cerr << "Error: " << ErrorMessage[static_cast<int>(Code)]
              << std::endl;
    std::exit(EXIT_FAILURE);
}

void Lexer::Open(std::string file_name) {
    if (FileStream.is_open())
        Error(ERROR::STREAM_BUSY);
    FileName = std::move(file_name);
    FileStream.open(FileName);
    if (!FileStream.is_open())
        Error(ERROR::FILE_NOT_FOUND);
}

void Lexer::Close() {
    if (FileStream.is_open())
        FileStream.close();
}

Lexer::~Lexer() {
    Close();
}

Token Lexer::GetNextToken() {
    if (!FileStream.is_open())
        return Token(Token::KIND::END, LineNumber);
    char c;
    while ((c = (char)FileStream.get()) != EOF) {
        switch (c) {
            // Comments
            case '#':
                while (c != EOF && c != '\n') {
                    c = (char)FileStream.get();
                }
                LineNumber++;
                break;
                // Whitespaces & New lines
            case '\n':
                LineNumber++;
                break;
            case ' ':
            case '\t':
                break;
                //Numbers
            case 48 ... 57:
            case '.':
                return CreateNumberToken();
                // Operators
            case '[':
                return Token(Token::KIND::LSQBCKT, LineNumber);
            case ']':
                return Token(Token::KIND::RSQBCKT, LineNumber);
            case ',':
                return  Token(Token::KIND::COMMA, LineNumber);
            case ';':
                return Token(Token::KIND::SEMI, LineNumber);
            case '+':
                return  Token(Token::KIND::PLUS, LineNumber);
            case '-':
                return  Token(Token::KIND::MINUS, LineNumber);
            case '*':
                return  Token(Token::KIND::MULT, LineNumber);
            case '/':
                return  Token(Token::KIND::DIV, LineNumber);
            case '=':
                return  Token(Token::KIND::ASSIGN, LineNumber);
                // Identifier
            case 95:
            case 65 ... 90:
            case 97 ... 122:
                return  CreateIDToken();
            default:
                return  {};
        }
    }
    // End of File
    return  Token(Token::KIND::END, LineNumber);
}

Token Lexer::CreateIDToken() {
    char c;
    std::string TokenString;
    FileStream.unget();
    while (!FileStream.eof()) {
        c = (char)FileStream.get();
        if (std::isalnum(c) || c == '_')
            TokenString += c;
        else {
            FileStream.unget();
            if (std::find(KeyWords.begin(), KeyWords.end(), TokenString) != KeyWords.end())
                return Token(Token::KIND::KEYWORD, LineNumber, TokenString);
            else
                return Token(Token::KIND::ID, LineNumber, TokenString);
        }
    }
    return Token(Token::KIND::END, LineNumber);
}

Token Lexer::CreateNumberToken() {
    char c;
    std::string TokenString;
    FileStream.unget();
    size_t nE = 0, nDot = 0;
    while (!FileStream.eof()) {
        c = (char)FileStream.get();
        if (std::isdigit(c))
            TokenString += c;
        else if (c == '.') {
            nDot++;
            if (nDot > 1) {
                FileStream.unget();
                break;
            }
            TokenString += c;
        } else if (c == 'e') {
            nE++;
            if (nE > 1) {
                FileStream.unget();
                break;
            }
        } else {
            FileStream.unget();
            if (nDot == 1 && TokenString.length() == 1)
                return Token(Token::KIND::DOT, LineNumber);
            else if (nE == 1 || nDot == 1)
                return Token(Token::KIND::FLOAT, LineNumber, TokenString);
            else
                return Token(Token::KIND::INT, LineNumber, TokenString);
        }
    }
    if (nDot > 1 && TokenString.length() > 1)
        return Token(Token::KIND::FLOAT, LineNumber, TokenString);
    else if (nDot > 1) {
        return Token(Token::KIND::DOT, LineNumber);
    } else
        return Token(Token::KIND::NONE, LineNumber);
}

std::vector<Token> Lexer::Read() {
    std::vector<Token> TokenList;
    Token t;
    while ((t = GetNextToken()).Kind != Token::KIND::END) {
        TokenList.push_back(t);
    }
    return TokenList;
}

std::string Lexer::GetFileName() const{
    return FileName;
}
