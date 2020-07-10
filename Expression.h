#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Token.h"

using namespace std;

enum Exp_type {assignment, arithmetic, illegal};

class Expression {
public:
    // Constructors
    Expression();
    Expression(const string& s);
    
    // Methods
    void set(const string& s);
    void set_valid();
    void set_type();
    void set_postfix();
    void set_prefix();
    void set_parenthesized();
    void set_value();
    void display_tokenized() const;
    void display_postfix() const;
    void display_prefix() const;
    void display_parenthesized() const;
    void display() const;
    string get_original() const;
    vector<Token> get_tokenized() const;
    vector<Token> get_postfix() const;
    vector<Token> get_prefix() const;
    vector<Token> get_parenthesized() const;
    int get_value() const;
    bool get_valid() const;
    Exp_type get_type() const;
    
private:
    
    // Data members
    string original;
    vector<Token> tokenized;
    vector<Token> postfix;
    vector<Token> prefix;
    string parenthesized;
    int value;
    bool valid;
    Exp_type type;
    
};
#endif