#include <ctype.h>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <string>
#include "ScannerStruct.hpp"
#include "Table.hpp"
#include "token.hpp"
#include "TokenRecord.hpp"

Scanner *initScanner(std::string &src) {
    Scanner *scanner = (Scanner *) malloc(sizeof(Scanner));

    scanner->src = &src;
    scanner->i = 0;
    scanner->c = scanner->src->at(scanner->i); // Explicitly set the first character

    return scanner;
}

void advanceScanner(Scanner *scanner) {
    scanner->i += 1;
    if (scanner->i != scanner->src->length())
        scanner->c = scanner->src->at(scanner->i);
}

int isKeyword(std::string str) {
    for (int i = 0; i < 14; i++) {
        if (str == keywords[i]) {
            return 1;
        }
    }
    return 0;
}

TokenRecord *getKeywordToken(std::string str) {
    if (str == "begin")  return initToken(str, BEGIN_tk);
    if (str == "end")    return initToken(str, END_tk);
    if (str == "loop")   return initToken(str, LOOP_tk);
    if (str == "whole")  return initToken(str, WHOLE_tk);
    if (str == "void")   return initToken(str, VOID_tk);
    if (str == "exit")   return initToken(str, EXIT_tk);
    if (str == "getter") return initToken(str, GETTER_tk);
    if (str == "outter") return initToken(str, OUTTER_tk);
    if (str == "main")   return initToken(str, MAIN_tk);
    if (str == "if")     return initToken(str, IF_tk);
    if (str == "then")   return initToken(str, THEN_tk);
    if (str == "assign") return initToken(str, ASSIGN_tk);
    if (str == "data")   return initToken(str, DATA_tk);
    if (str == "proc")   return initToken(str, PROC_tk);
}

TokenRecord *getNextToken(Scanner *scanner) {
    State nextState;
    State state = INITIAL;
    State tempState;
    std::string str;
    int isInComment = 0;
    int transition;

    while (state != FINAL) {
        transition = getTransitionFromChar(scanner->c, state);
        nextState = Table[state][transition];

        // Handle errors
        if (nextState == ERROR) {
            std::cout << "SCANNER ERROR: Unexpected character `" << scanner->c << "` (" << (int) scanner->c << ")"
                      << std::endl;
            exit(1);
        }

        if (nextState == FINAL) {
            // determine token type
            switch (state) {
                case ASSIGNOP:
                    return initToken(str, ASSIGNOP_tk);
                case GTEQ:
                    return initToken(str, GTEQ_tk);
                case EQ:
                    return initToken(str, EQ_tk);
                case COLONEQ:
                    return initToken(str, COLONEQ_tk);
                case LTEQ:
                    return initToken(str, LTEQ_tk);
                case ID:
                    if (isKeyword(str)) {
                        return getKeywordToken(str);
                    }
                    return initToken(str, ID_tk);
                case NUM:
                    return initToken(str, NUM_tk);
                case EOF_:
                    return initToken(str, EOF_tk);
                case SEMI:
                    return initToken(str, SEMI_tk);
                case PLUS:
                    return initToken(str, PLUS_tk);
                case MINUS:
                    return initToken(str, MINUS_tk);
                case MULT:
                    return initToken(str, MULT_tk);
                case DIVIDE:
                    return initToken(str, DIVIDE_tk);
                case MOD:
                    return initToken(str, MOD_tk);
                case DOT:
                    return initToken(str, DOT_tk);
                case COMMA:
                    return initToken(str, COMMA_tk);
                case COLON:
                    return initToken(str, COLON_tk);
                case LPAREN:
                    return initToken(str, LPAREN_tk);
                case RPAREN:
                    return initToken(str, RPAREN_tk);
                case LBRACE:
                    return initToken(str, LBRACE_tk);
                case RBRACE:
                    return initToken(str, RBRACE_tk);
                case LBRACKET:
                    return initToken(str, LBRACKET_tk);
                case RBRACKET:
                    return initToken(str, RBRACKET_tk);
            }
        } else if (nextState == CMT_ST_A) {
            tempState = state; // save the current state when comment started
            state = nextState;
            advanceScanner(scanner);
        } else if (nextState == CMT_ST_B || nextState == CMT_END_A || nextState == CMT_END_B) {
            state = nextState == CMT_END_B ? tempState : nextState;
            advanceScanner(scanner);
        } else {
            state = nextState;
            if (!isspace(scanner->c)) {
                str += scanner->c;
            }
            advanceScanner(scanner);
        }
    }
}
