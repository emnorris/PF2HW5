
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "Expression.h"

#define MAX_BUFF_SIZE 64

using namespace std;

void search_for_id_value(vector<Token> & IDvalues, Expression* input) {    
    if(input->get_type() == assignment) {
            IDvalues.push_back(input->get_tokenized()[0]);
            return;
        } else if(input->get_type() == arithmetic) {
            for(int j = 0; j < input->get_tokenized().size(); j++) {
                if(input->get_tokenized()[j].get_type() == ID) {
                    for(int i = 0; i < IDvalues.size(); i++) {
                        if(IDvalues[i].get_token() == input->get_tokenized()[j].get_token()) {
                            input->get_tokenized()[j].set_value(IDvalues[i].value());
                            //cout << IDvalues[i].value() << endl;
                            //cout << input->get_tokenized()[j].value() << endl;
                        }
                    }
                }
            }
        }
    
}

int main(int argc, char** argv) {
        string buffer;
        char* temp;
        bool ACTION = 0;
        vector<Token> IDvalues;
        vector<Expression> expressions;
        int iterate = 0;
    while(1) {
        cout << "input: ";
        getline(cin, buffer);
        strcpy(temp, buffer.c_str());
        char* token;
        token = strtok(temp, ";");
        //cout << "yup" << endl;
        while(token != NULL) {
            Expression* input = new Expression();
            input->set(token);
            search_for_id_value(IDvalues, input);
            expressions.push_back(*input);
            //cout << token << endl;
            token = strtok(NULL, ";");
            delete input;
        }
        
        ACTION = 1;
        char actionBuff[MAX_BUFF_SIZE];
        char ActSwitch;    
    while(ACTION) {
        //input.display();
        cout << "action: ";
        cin >> actionBuff;
        if(actionBuff[1] != '\0') {
            cout << "error: Input is 1 character" << endl;
            continue;
        } else {
            ActSwitch = actionBuff[0];
        }
        
        while(ACTION && iterate < (expressions.size())) {
            switch (ActSwitch) {
                case '=':
                    expressions[iterate].display_tokenized();
                    cout << endl;
                    ACTION = 1;
                    break;
                case '>':
                    expressions[iterate].display_prefix();
                    cout << endl;
                    ACTION = 1;
                    break;
                case '<':
                    expressions[iterate].display_postfix();
                    cout << endl;
                    ACTION = 1;
                    break;
                case 'f':
                    expressions[iterate].display_parenthesized();
                    cout << endl;
                    ACTION = 1;
                    break;
                case 'q':                   
                    return 0;
                    break;
                case 'c':
                    ACTION = 0;
                    cin.ignore();
                    continue;
                    break;
                case 's':
                    ACTION = 0;
                    cin.ignore();
                    IDvalues.clear();
                    expressions.clear();
                    continue;
                    break;
                default:
                    cout << "no dice" << endl;
                    break;
            }
        iterate++;    
        }
        iterate = 0;
        
    }
    }
    return 0;
}


