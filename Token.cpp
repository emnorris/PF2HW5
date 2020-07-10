
#include "Token.h"

using namespace std;

    // Constructors
    Token::Token() {
    
        token = '\0';
        type = INVALID;
        priority = -1;
    
    }
    
    Token::Token(string s) {
    
        set(s);
        
    }
    
    void Token::set_value(int val) {
        //cout << "uhh hello?" << endl;
        if(type == ID)
        tokval = val;
        else
            tokval = -3;
        
        //cout << tokval << endl;
        
    }
    
    // Methods
    void Token::set(string s) {
    
        token = s;
        bool validate = true;
        tokval = -2;
        
    if(isdigit(token[0])) {
        
        for(int j = 0; token[j] != '\0'; j++) {
            
            if(isdigit(token[j]) == false) {
                type = INVALID;
                priority = -1;
                validate = false;
                return;
            }
    
        }
        
        if(validate == true) {
            type = INT;
            priority = -1;
        }
            
    }   else if(isalpha(token[0])) {
        
        for(int i = 0; token[i] != '\0'; i++) {
            
            if(isalpha(token[i]) == false && isdigit(token[i]) == false) {
                
                type = INVALID;
                priority = -1;
                validate = false;
                break;
            }
    
        }
        
        if(validate == true) {
            type = ID;
            priority = -1;
        }
        
    } else {
        
        switch(token[0]) {
            case    ' ':
                type = SPACE;
                priority = -1;
                break;
            case   '=':
                    type = EQ;
                    priority = -1;
                    break;
            case   '(':
                    type = OpenBrace;
                    priority = -1;
                    break;
            case   ')':
                    type = CloseBrace;
                    priority = -1;
                    break;
            case   '+':
                    type = OP;
                    priority = 1;
                    break;
            case   '-':
                    type = OP;
                    priority = 1;
                    break;
            case   '*':
                    type = OP;
                    priority = 2;
                    break;
            case   '%':
                    type = OP;
                    priority = 2;
                    break;        
            case   '/':
                    type = OP;
                    priority = 2;
                    break;         
            default:
                    type = INVALID;
                    priority = -1;
                    break;
           
        }

      }
    
    }
    
    int Token::value() const {
        
        int i;
        if(type == INT) {            
            sscanf(token.c_str(), "%d", &i);
            
            return i;
            
            
        } else if (type == ID) {
            
            i = tokval;
            return i;
            
        } else {
            
            return -1;
            
        }
    
    }
    
    void Token::display() const {
    
        cout << "token = " << token << endl;
                
        cout << "type = ";
                
        switch (type) {
            case(SPACE) :
                cout << "SPACE" << endl;
                break;
            case(ID) :
                cout << "ID" << endl;
                break;
            case(INT) :
                cout << "INT" << endl;
                break;
            case(OP) :
                cout << "OP" << endl;
                break;
            case(EQ) :
                cout << "EQ" << endl;
                break;
            case(OpenBrace) :
                cout << "OpenBrace" << endl;
                break;
            case(CloseBrace) :
                cout << "CloseBrace" << endl;
                break;
            case(INVALID) :
                cout << "INVALID" << endl;
                break;
    
        }        
                
                
        cout << "priority = " << priority << endl;
    
    }
    
    Token_type Token::get_type() const {
    
        return type;
    
    }
    
    string Token::get_token() const {
    
        return token;
    
    }
    
    int Token::get_priority() const {
    
        return priority;
    
    } 
        
        
                                
