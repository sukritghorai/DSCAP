#include "../include/Parser.h"

#include <utility>



std::ostream &operator<<(std::ostream &os, ASTNode* node)
{
    if (node->Kind == ASTNode::KIND::NUMBERNODE)
    {
        NumberNode* n = dynamic_cast<NumberNode*>(node);
        os << " [Number Node: " << n->NumberToken.Value << "] ";
    }
    else if (node->Kind == ASTNode::KIND::BINOPNODE)
    {
        BinOPNode* n = dynamic_cast<BinOPNode*>(node);
        os << n->LeftNode;
        os << "[OPERATOR: " << n->Operator << "]";
        os <<  n->RightNode << std::endl;
    }
    else
        os << "Error: 123";
    return os;
}

std::ostream &operator<<(std::ostream &os, ASTNode::KIND &kind)
{
    if (kind == ASTNode::KIND::NUMBERNODE)
        os << "NUMBER NODE";
    else if (kind == ASTNode::KIND::BINOPNODE)
        os << "BINOP NODE";
    else
        os << "NONE";
    return os;
}
Parser::Parser() = default;

Parser::Parser(std::string file_name)
{
     FileName = file_name;
    Init(std::move(file_name));
}

void Parser::Init(std::string file_name)
{
    Lexer Stream;
    Stream.Open(std::move(file_name));
    TokenList = Stream.Read();
    TokenListSize = TokenList.size();
    Stream.Close();
}

void Parser::Error(ERROR Code)
{
    std::cerr << "File \"" << FileName << "\", line "
              << "[LINE NUMBER]" << std::endl;
    std::cerr << "Error: " << ErrorMessage[static_cast<int>(Code)]
              << std::endl;
    std::exit(EXIT_FAILURE);
}

void Parser::Read() {
//    for (Token t : TokenList)
//        std::cout << t << std::endl;
    NextToken();
    ASTNode* Root = Expression();
    std::cout << Root;
}

void Parser::NextToken()
{
    TokenIndex++;
    if (TokenIndex < TokenListSize)
        CurrentToken = TokenList[TokenIndex];
}

ASTNode* Parser::Factor()
{
    Token t;
    if (CurrentToken.Kind == Token::KIND::INT || CurrentToken.Kind == Token::KIND::FLOAT)
    {
        t = CurrentToken;
        NextToken();
        return new NumberNode(t);
    }
    else
        Error(ERROR::INVALID_NUMBER_TOKEN);
}

ASTNode* Parser::Term()
{
    Token::KIND OP;
    ASTNode *Left = Factor();
    ASTNode *Right = nullptr;
    while (CurrentToken.Kind == Token::KIND::MULT || CurrentToken.Kind == Token::KIND::DIV)
    {
        OP = CurrentToken.Kind;
        NextToken();
        Right = Term();
        Left = new BinOPNode(OP, Left, Right);
        NextToken();
    }
    return Left;
}

ASTNode* Parser::Expression()
{
    Token::KIND OP;
    ASTNode *Left = Term();
    ASTNode *Right = nullptr;
    while (CurrentToken.Kind == Token::KIND::PLUS || CurrentToken.Kind == Token::KIND::MINUS)
    {
        OP = CurrentToken.Kind;
        NextToken();
        Right = Expression();
        Left = new BinOPNode(OP, Left, Right);
        NextToken();
    }
    return Left;
}
