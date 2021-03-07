#include <ctype.h>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <string>
#include "ScannerStruct.hpp"
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

TokenRecord *advanceScannerWith(Scanner *scanner, TokenRecord *token) {
    advanceScanner(scanner);
    return token;
}

TokenRecord *advanceScannerWithCurrent(Scanner *scanner, tokenID type) {
    std::string str(1, scanner->c);
    TokenRecord *token = initToken(str, type);
    advanceScanner(scanner);
    return token;
}

char lookahead(Scanner *scanner, int offset = 1) {
    int index = scanner->i + offset < scanner->src->length()
                ? scanner->i + offset
                : scanner->src->length();
    return index < scanner->src->length()
           ? scanner->src->at(index)
           : scanner->src->at(scanner->src->length() - 1);
}

void skipWhitespace(Scanner *scanner) {
    while (scanner->c == 13 || scanner->c == 10 || scanner->c == ' ' || scanner->c == '\t')
        advanceScanner(scanner);
}

void skipComments(Scanner *scanner) {
    if (scanner->c == '$' && lookahead(scanner) == '$') {
        // Advance past the initial '$$' to properly identify the second set of '$$'
        advanceScanner(scanner);
        advanceScanner(scanner);

        while (1) {
            if (scanner->c == '$' && lookahead(scanner) == '$') {
                advanceScanner(scanner);
                advanceScanner(scanner);
                break;
            }
            advanceScanner(scanner);
        }
        skipWhitespace(scanner);
    }
}

TokenRecord *scannerParseIdOrKeyword(Scanner *scanner) {
    std::string value;

    while (isalpha(scanner->c)) {
        value += scanner->c;
        advanceScanner(scanner);
    }

    // Determine if value is a keyword
    if (value == "begin")  return initToken(value, BEGIN_tk);
    if (value == "end")    return initToken(value, END_tk);
    if (value == "loop")   return initToken(value, LOOP_tk);
    if (value == "whole")  return initToken(value, WHOLE_tk);
    if (value == "void")   return initToken(value, VOID_tk);
    if (value == "exit")   return initToken(value, EXIT_tk);
    if (value == "getter") return initToken(value, GETTER_tk);
    if (value == "outter") return initToken(value, OUTTER_tk);
    if (value == "main")   return initToken(value, MAIN_tk);
    if (value == "if")     return initToken(value, IF_tk);
    if (value == "then")   return initToken(value, THEN_tk);
    if (value == "assign") return initToken(value, ASSIGN_tk);
    if (value == "data")   return initToken(value, DATA_tk);
    if (value == "proc")   return initToken(value, PROC_tk);

    // Return as an identifier token if not found as a keyword
    return initToken(value, ID_tk);
}

TokenRecord *scannerParseNumber(Scanner *scanner) {
    std::string value;

    while (isdigit(scanner->c)) {
        value += scanner->c;
        advanceScanner(scanner);
    }

    return initToken(value, NUM_tk);
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
                    if (isKeyword(str)) {
                        return getKeywordToken(str);
                    }
    while (scanner->c != '\0') {
        skipWhitespace(scanner);
        skipComments(scanner);

        // If we get an alpha character then parse as an Identifier/Keyword
        if (isalpha(scanner->c))
            return scannerParseIdOrKeyword(scanner);

        // If we get a digit then parse as a Number
        if (isdigit(scanner->c))
            return scannerParseNumber(scanner);

        // Else determine parse path with remaining tokens
        // NOTE: Any double character operator has nested advances to advance scanner past the two chars after lookahead
        switch (scanner->c) {
            case '=': {
                switch (lookahead(scanner)) {
                    case '=':
                        return advanceScannerWith(scanner, advanceScannerWith(scanner, initToken("==", EQ_tk)));
                    case '>':
                        return advanceScannerWith(scanner, advanceScannerWith(scanner, initToken("=>", GTEQ_tk)));
                    case '<':
                        return advanceScannerWith(scanner, advanceScannerWith(scanner, initToken("=<", LTEQ_tk)));
                }
                return advanceScannerWithCurrent(scanner, ASSIGNOP_tk);
            }
                break;
            case ';':
                return advanceScannerWithCurrent(scanner, SEMI_tk);
            case '+':
                return advanceScannerWithCurrent(scanner, PLUS_tk);
            case '-':
                return advanceScannerWithCurrent(scanner, MINUS_tk);
            case '*':
                return advanceScannerWithCurrent(scanner, MULT_tk);
            case '/':
                return advanceScannerWithCurrent(scanner, DIVIDE_tk);
            case '%':
                return advanceScannerWithCurrent(scanner, MOD_tk);
            case '.':
                return advanceScannerWithCurrent(scanner, DOT_tk);
            case ',':
                return advanceScannerWithCurrent(scanner, COMMA_tk);
            case ':':
                if (lookahead(scanner) == '=') {
                    return advanceScannerWith(scanner, advanceScannerWith(scanner, initToken(":=", COLONEQ_tk)));
                }
                return advanceScannerWithCurrent(scanner, COLON_tk);
            case '(':
                return advanceScannerWithCurrent(scanner, LPAREN_tk);
            case ')':
                return advanceScannerWithCurrent(scanner, RPAREN_tk);
            case '{':
                return advanceScannerWithCurrent(scanner, LBRACE_tk);
            case '}':
                return advanceScannerWithCurrent(scanner, RBRACE_tk);
            case '[':
                return advanceScannerWithCurrent(scanner, LBRACKET_tk);
            case ']':
                return advanceScannerWithCurrent(scanner, RBRACKET_tk);
            case '\0':
                break; // Synonymous for the EOF Token
            default:
                std::cout << "SCANNER ERROR: Unexpected character `" << scanner->c << "` (" << (int) scanner->c << ")"
                          << std::endl;
                exit(1);
        }
    }

    return initToken("EOF", EOF_tk);
}
