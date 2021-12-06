#ifndef __PARSER_H__
#define __PARSER_H__

#include "Lexer.h"

class ASTNode {

public:
    enum class KIND{NUMBERNODE, BINOPNODE} Kind;
    virtual void SetType() = 0;
};

class NumberNode : public ASTNode {
private:
    void SetType(){Kind = ASTNode::KIND::NUMBERNODE;}
public:
    Token NumberToken;
    NumberNode(Token &tok)
            : NumberToken(tok) {SetType();}

};

class BinOPNode : public ASTNode {
private:
    void SetType(){Kind = ASTNode::KIND::BINOPNODE;}
public:
    Token::KIND Operator;
    ASTNode *LeftNode;
    ASTNode *RightNode;

    BinOPNode()
            : LeftNode(nullptr), RightNode(nullptr) {SetType();}

    BinOPNode(Token::KIND op, ASTNode *left_node, ASTNode *right_node)
            : Operator(op), LeftNode(left_node), RightNode(right_node) {SetType();}

    ~BinOPNode() {
        if (LeftNode != nullptr)
            delete (LeftNode);
        if (RightNode != nullptr)
            delete (RightNode);
    }
};
std::ostream &operator<<(std::ostream &os, ASTNode::KIND &kind);


class Parser {
private:
    // Tokens List & Parameters
    std::vector<Token> TokenList;
    size_t TokenIndex = -1;
    size_t TokenListSize = 0;
    Token CurrentToken;
    // File Name
    std::string FileName;

    // Error Handler
    enum class ERROR {
        INVALID_NUMBER_TOKEN
    };
    std::array<std::string, 10> ErrorMessage =
            {
                    "Expected a number.",

            };

    void Error(ERROR Code);

    void NextToken();

public:
    Parser();

    Parser(std::string file_name);

    void Init(std::string file_name);

    void Read();

    // expr : term ((PLUS|MINUS) term)*
    ASTNode* Expression();

    // term : factor ((MULT|DIVIDE) factor)*
    ASTNode* Term();

    // factor : INT|FLOAT
    ASTNode* Factor();


};


#endif
