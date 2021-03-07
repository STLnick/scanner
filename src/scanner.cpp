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

TokenRecord *getKeywordToken(std::string str, int lineCnt) {
    if (str == "begin")  return initToken(str, BEGIN_tk, lineCnt);
    if (str == "end")    return initToken(str, END_tk, lineCnt);
    if (str == "loop")   return initToken(str, LOOP_tk, lineCnt);
    if (str == "whole")  return initToken(str, WHOLE_tk, lineCnt);
    if (str == "void")   return initToken(str, VOID_tk, lineCnt);
    if (str == "exit")   return initToken(str, EXIT_tk, lineCnt);
    if (str == "getter") return initToken(str, GETTER_tk, lineCnt);
    if (str == "outter") return initToken(str, OUTTER_tk, lineCnt);
    if (str == "main")   return initToken(str, MAIN_tk, lineCnt);
    if (str == "if")     return initToken(str, IF_tk, lineCnt);
    if (str == "then")   return initToken(str, THEN_tk, lineCnt);
    if (str == "assign") return initToken(str, ASSIGN_tk, lineCnt);
    if (str == "data")   return initToken(str, DATA_tk, lineCnt);
    if (str == "proc")   return initToken(str, PROC_tk, lineCnt);
}

TokenRecord *getTypedToken(State state, std::string str, int lineCnt) {
    switch (state) {
        case ASSIGNOP:
            return initToken(str, ASSIGNOP_tk, lineCnt);
        case GTEQ:
            return initToken(str, GTEQ_tk, lineCnt);
        case EQ:
            return initToken(str, EQ_tk, lineCnt);
        case COLONEQ:
            return initToken(str, COLONEQ_tk, lineCnt);
        case LTEQ:
            return initToken(str, LTEQ_tk, lineCnt);
        case ID:
            if (isKeyword(str)) {
                return getKeywordToken(str, lineCnt);
            }
            return initToken(str, ID_tk, lineCnt);
        case NUM:
            return initToken(str, NUM_tk, lineCnt);
        case EOF_:
            return initToken(str, EOF_tk, lineCnt);
        case SEMI:
            return initToken(str, SEMI_tk, lineCnt);
        case PLUS:
            return initToken(str, PLUS_tk, lineCnt);
        case MINUS:
            return initToken(str, MINUS_tk, lineCnt);
        case MULT:
            return initToken(str, MULT_tk, lineCnt);
        case DIVIDE:
            return initToken(str, DIVIDE_tk, lineCnt);
        case MOD:
            return initToken(str, MOD_tk, lineCnt);
        case DOT:
            return initToken(str, DOT_tk, lineCnt);
        case COMMA:
            return initToken(str, COMMA_tk, lineCnt);
        case COLON:
            return initToken(str, COLON_tk, lineCnt);
        case LPAREN:
            return initToken(str, LPAREN_tk, lineCnt);
        case RPAREN:
            return initToken(str, RPAREN_tk, lineCnt);
        case LBRACE:
            return initToken(str, LBRACE_tk, lineCnt);
        case RBRACE:
            return initToken(str, RBRACE_tk, lineCnt);
        case LBRACKET:
            return initToken(str, LBRACKET_tk, lineCnt);
        case RBRACKET:
            return initToken(str, RBRACKET_tk, lineCnt);
    }
}

TokenRecord *getNextToken(Scanner *scanner, int &lineCnt) {
    State nextState;
    State state = INITIAL;
    State tempState;
    std::string str;
    int transition;

    while (state != FINAL) {
        transition = getTransitionFromChar(scanner->c);
        nextState = Table[state][transition];
        if(scanner->c == '\n' && state == INITIAL) {
            lineCnt++;
        }

        // Handle errors
        if (nextState == ERROR) {
            std::cout << "SCANNER ERROR: Unexpected character `" << scanner->c << "` (" << (int) scanner->c << ")" << std::endl;
            exit(1);
        }

        if (nextState == FINAL) {
            return getTypedToken(state, str, lineCnt);
        } else if (nextState == EOF_) {
            return initToken("\0", EOF_tk, lineCnt);
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
