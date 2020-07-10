#include <stack>
#include "Expression.h"


using namespace std;

    // Constructors
    Expression::Expression(){
        
        original = '\0';
        valid = true; 
        type = assignment;
    
    }
    
    Expression::Expression(const string& s) {
        
        set(s);

    }
    
    // Methods
    void Expression::set(const string& s){
        //sets original to the whole string
        original = s;
        //counts the number of items in the tokenized vector
        unsigned int count = 0;
        //iterates through the string
        unsigned int j = 0;
        //place holder for each token
        string funky = "fin";
        type = illegal;
        valid = true;
        //finds the first OP brace or EQ and sets opr to its place in the string
        size_t opr = s.find_first_of(")+*-%/(= ");
        
            //search stop the loop when the null terminator is found
            while(s[j] != '\0') { 
                
                //error check: finds all delimiters before ID or INTs
                //can handle a string of only delimiters
                if(j == opr) {

                    tokenized.push_back(string(1, s[opr]));
                    count++;
                    opr = s.find_first_of(")+*-%/(= ", opr+1);
                    j++;
                    continue;
                    
                //error check: if no delimiters are found set the whole string
                // to the 1 token in the vector tokenized.
                } else if(opr == string::npos && count == 0) {
                    
                    tokenized.push_back(s);
                    count++;                    
                    break;
                
                // if we havent reached last delimiter sets up funky to push on to the stack
                // push funky and the delimiter following it on to the stack
                // sear for the next delimiter
                } else if (opr != string::npos) {   
                
                    funky.resize(opr - j);
                
                    for(int i = 0; j < opr; i++) {
                    
                        funky[i] = s[j];
                        j++;
                    }
                
                    tokenized.push_back(funky);
                    count++;
                    tokenized.push_back(string(1, s[opr]));
                    count++;
                    opr = s.find_first_of(")+*-%/(= ", opr+1);
                    j++;
                
                //found no more delimiters but have previously added tokens to the tokenized vector.
                //code to find the last token
                } else if(opr == string::npos && count > 0) {
                    
                    int m = 0;
                    int finder = j;
                    
                    while(s[finder] != '\0') {
                        
                        m++;
                        finder++;
                    }
                    
                    funky.resize(m);
                    
                    for(int i = 0; s[j] != '\0'; i++) {
                        
                        funky[i] = s[j];
                        j++;
                        
                    }
                    
                    //if there is something in funky put it in the vector else break
                    if(funky[0] != '\0') {
                        tokenized.push_back(funky);
                        count++;
                    }
                    break;
                    
                }
             
            }
        int m = 0;
        while(m < tokenized.size()) {
        if(tokenized[m].get_type() == 7) {
            tokenized.erase(tokenized.begin()+m);
        }
        m++;
        }
        //cout << "can u get here plz" << endl;
        set_valid();
        set_type();
        set_postfix();
        set_prefix();
        set_parenthesized();
        set_value();
    }
    void Expression::set_valid(){
        int i = 0;
        int open = 0;
        int closed = 0;
        while(i < tokenized.size()) {
            //only 2 things wont work
            if(tokenized.size() < 3) {
                valid = false;
                type = illegal;
            } else
            //if invalid token then invalid expression
            if(tokenized[i].get_type() == INVALID /*|| tokenized[i].get_type() == ID*/) {
                valid = false;
                type = illegal;
                //you cant have 2 of the same kind following each other
                //except braces
            } else if((tokenized[i].get_type() != OpenBrace &&
                       tokenized[i].get_type() != CloseBrace) &&
                      (i+1 != tokenized.size()) &&
                      (tokenized[i].get_type() == tokenized[i+1].get_type())) {
                valid = false;
                type = illegal; 
        //must have the same number of open and closed braces        
            } else if(tokenized[i].get_type() == OpenBrace) {
                open++;
                if(tokenized[i+1].get_type() == OP) {
                    valid = false;
                    type = illegal;
                }
                    
            } else if(tokenized[i].get_type() == CloseBrace) {
                closed++;
                if(tokenized[i-1].get_type() == OP) {
                    valid = false;
                    type = illegal;
                }
            }
            i++;
        }
        if(open != closed) {
            valid = false;
            type = illegal;
        }
        
    }
    void Expression::set_type(){
        //cout << "\nuhhhh hello" << endl;
        if(tokenized[0].get_type() == ID && tokenized[1].get_type() == EQ && tokenized[2].get_type() == INT) {
            valid = true;
            type = assignment;
            tokenized[0].set_value(tokenized[2].value());
            //cout << tokenized[0].value() << endl;
        } else   
        if(valid == true && type != assignment) {
            type = arithmetic;
        }
    }
    
    void Expression::set_postfix() {
        

        //if(type == illegal) {cout << "ILLEGAL\n";}
        //else if(type == assignment) { cout << "NOPE\n";} else
        if(type == arithmetic) {
            int i = 0;
            vector<Token> infix = tokenized;
            vector<Token> QueueFIFO;
            stack<Token> StackLIFO;
            while(i < infix.size()) {
                //if the token is an open brace push it on to the stack
            if(infix[i].get_type() == OpenBrace) {
                StackLIFO.push(infix[i].get_token());
           //if the token is an int push it on the queue
            } else if(infix[i].get_type() == INT) {
                QueueFIFO.push_back(infix[i].get_token());
            }else if(infix[i].get_type() == ID) {    
                QueueFIFO.push_back(infix[i].get_token());
            //if the token is an operator check PMDAS    
            } else if(infix[i].get_type() == OP) {
                if(!StackLIFO.empty() && infix[i].get_priority() <= StackLIFO.top().get_priority()) {
                //AS get pushed if previous push was not a MD operator
                    QueueFIFO.push_back(StackLIFO.top().get_token());
                    StackLIFO.pop();
                    StackLIFO.push(infix[i].get_token());
                } else {
                    StackLIFO.push(infix[i].get_token());
                }
            } else if(infix[i].get_type() == CloseBrace) {
                int q = 0;
                while(!StackLIFO.empty()) {
                    switch (StackLIFO.top().get_type()) {
                        case OP:
                            QueueFIFO.push_back(StackLIFO.top().get_token());
                            StackLIFO.pop();
                            break;
                        case OpenBrace:
                            StackLIFO.pop();
                            break;
                        default:
                            break;
                    }
                  q++;
                }             
            }
        i++;     
        }    
        int m = 0;
        while(!StackLIFO.empty()) {
            QueueFIFO.push_back(StackLIFO.top().get_token());
            StackLIFO.pop();            
            m++;    
        }    
        postfix = QueueFIFO;    
        }
    }       
    
    void Expression::set_prefix() {
        //cout << "uhh hello" << endl;
        //if(type == illegal) {cout << "ILLEGAL\n";}
        //else if(type == assignment) { cout << "NOPE\n";} else
        if(type == arithmetic) {
            
            int i = 0;
            vector<Token> infix = tokenized;
            vector<Token> QueueFIFO;
            stack<Token> StackLIFO;
            i = (infix.size() - 1);
            //cout << "wez here" << endl;
            while(i >= 0) {
                //if the token is an open brace push it on to the stack
            if(infix[i].get_type() == CloseBrace) {
                StackLIFO.push(infix[i].get_token());
           //if the token is an int or ID push it on the queue
            } else if(infix[i].get_type() == INT) {
                //cout << "yo dawg" << endl;
                QueueFIFO.insert(QueueFIFO.begin(), infix[i].get_token());
            }else if(infix[i].get_type() == ID) {    
                QueueFIFO.insert(QueueFIFO.begin(), infix[i].get_token());
            //if the token is an operator check PMDAS   
            } else if(infix[i].get_type() == OP) {
                if(!StackLIFO.empty() && infix[i].get_priority() <= StackLIFO.top().get_priority()) {
                //AS get pushed if previous push was not a MD operator
                    QueueFIFO.insert(QueueFIFO.begin(), StackLIFO.top().get_token());
                    StackLIFO.pop();
                    StackLIFO.push(infix[i].get_token());
                } else {
                    StackLIFO.push(infix[i].get_token());
                }
            } else if(infix[i].get_type() == OpenBrace) {
                int q = 0;
                while(!StackLIFO.empty()) {
                    switch (StackLIFO.top().get_type()) {
                        case OP:
                            QueueFIFO.insert(QueueFIFO.begin(), StackLIFO.top().get_token());
                            StackLIFO.pop();
                            break;
                        case CloseBrace:
                            StackLIFO.pop();
                            break;
                        default:
                            break;
                    }
            
                  q++;
                }
            }
                i--;    
            }
            int m = 0;
            while(!StackLIFO.empty()) {
                QueueFIFO.insert(QueueFIFO.begin(), StackLIFO.top().get_token());
                StackLIFO.pop();
                  
            m++;    
            }
            prefix = QueueFIFO;
//        } else {
//            cout << " " << endl;
       }
    }
    
    int value_finder_(int first, int second, string opr) {
        //cout << "yo yo yo" << endl;
        char gotten = opr[0];
        int val = 0;
        switch(gotten) {
            case '+':
                val = first + second;
                //cout << val << endl;
                break;
            case '-':
                val = first - second;
                //cout << val << endl;
                break;
            case '*':
                val = first * second;
                //cout << val << endl;
                break;
            case '/':
                val = first / second;
                //cout << val << endl;
                break;
            case '%':
                val = first % second;
            default:
                break;
        }
        return val;
    }
    
    void Expression::set_value() {
        
       int i = 0;
       int num1;
       int num2;
       string op;
       int builder;
       stack<int> StackNum;
       while(i < postfix.size()) {
           if(postfix[i].get_type() == INT) {
               StackNum.push(postfix[i].value());
           } else if(postfix[i].get_type() == ID) {
               StackNum.push(postfix[i].value());
               
           } else if(postfix[i].get_type() == OP) {
               op = postfix[i].get_token();
               num2 = StackNum.top();
               StackNum.pop();
               num1 = StackNum.top();
               StackNum.pop();
               builder = value_finder_(num1, num2, op);
               StackNum.push(builder);
           }
           
           i++;
       }
       //cout << builder << endl;
       
       value = builder;
    }
    
    void Expression::set_parenthesized() {
       int i = 0;
       string num1;
       string num2;
       string op;
       string builder;
       stack<string> StackNum;
       while(i < postfix.size()) {
           if(postfix[i].get_type() == INT) {
               StackNum.push(postfix[i].get_token());
           }else if(postfix[i].get_type() == ID) {
               StackNum.push(postfix[i].get_token());
               
           } else if(postfix[i].get_type() == OP) {
               op = postfix[i].get_token();
               num2 = StackNum.top();
               StackNum.pop();
               num1 = StackNum.top();
               StackNum.pop();
               builder = "(" + num1 + op + num2 + ")";
               StackNum.push(builder);
           }
           
           i++;
       }
       //cout << builder << endl;
       
       parenthesized = builder;
    }    
    
    void Expression::display_postfix() const {
        if(type != 1) {
            cout << "No postfix";
        } else {
        cout << "postfix: ";
        for(int i = 0; i < postfix.size(); i++) {
            cout << postfix[i].get_token();
        }
        }
    }
    void Expression::display_prefix() const {
        if(type != 1) {
            cout << "No prefix";
        } else {
        cout << "prefix: ";
        for(int i = 0; i < prefix.size(); i++) {
            cout << prefix[i].get_token();
        }
        }
    }
    void Expression::display_parenthesized() const {
        if(type != 1) {
            cout << "No parenthesis";
        } else {
        cout << "parenthesized: " << parenthesized;
        }
        
    }
    void Expression::display_tokenized() const {
        if(type == assignment) { 
                cout << tokenized[0].get_token();
            cout << " = " << tokenized[0].value();
        } else if(type == 1){
            for(int i = 0; i < tokenized.size(); i++){ 
                cout << tokenized[i].get_token();
            }
            cout << " = " << value;
        } else if(type == illegal) {
            cout << "Illegal Expression" << endl << "Output: ";
            for(int i = 0; i < tokenized.size(); i++){ 
                cout << tokenized[i].get_token();
            }
        }
    }
    
    void Expression::display() const {
        
        cout << "original = " << original << endl;
        display_tokenized();    
        display_postfix();  
        display_prefix();
        display_parenthesized();
        cout << "\nvalid = ";
        if(valid) {
            cout << "TRUE" << endl;
        } else {
            cout << "FALSE" << endl;
        }
        cout << "type = ";
        switch(type) {
            case 0:
                cout << "Assignment" << endl;
                break;
            case 1:
                cout << "Athrimetic" << endl;
                break;
            case 2:
                cout << "illegal" << endl; 
                break;
            default:
                break;    
        }
        
    }
    
    string Expression:: get_original() const {
        
       return original;
        
    }
    
    vector<Token> Expression:: get_tokenized() const {
        
        return tokenized;
        
    }
    
    Exp_type Expression::get_type() const {
        
        return type;
    }
    
    int Expression::get_value() const {
        
        return value;
    }
