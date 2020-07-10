#ifndef TOKEN_H
#define TOKEN_H

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum Token_type {ID, INT, OP, EQ, OpenBrace, CloseBrace, INVALID, SPACE};

class Token {
public:
    // Constructors
    Token();
    Token(string s);
    
    // Methods
    void set(string s);
    int value() const;
    void display() const;
    Token_type get_type() const;
    string get_token() const;
    int get_priority() const;
    void set_value(int val);
    
    
private:
    
    // Data members
    Token_type type;
    string token;
    int priority;
    int tokval;
    
};
#endif
