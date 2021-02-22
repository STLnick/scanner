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

char lookahead(Scanner *scanner, int offset = 1) {
    int index = scanner->i + offset < scanner->src->length()
                ? scanner->i + offset
                : scanner->src->length();
    return index < scanner->src->length()
           ? scanner->src->at(index)
           : scanner->src->at(scanner->src->length() - 1);
}

TokenRecord* scannerParseNumber(Scanner *scanner) {
    std::string value;

    while (isdigit(scanner->c)) {
        value += scanner->c;
        advanceScanner(scanner);
    }

    return initToken(value, NUM_tk);
}

TokenRecord* getNextToken(Scanner *scanner) {
    while (scanner->c != '\0') {
        // TODO: If we get an alpha character then parse as an Identifier
        //if (isalpha(scanner->c))
        //    return scannerParseId(scanner);

        // TODO: If we get a digit then parse as a number
        if (isdigit(scanner->c))
            return scannerParseNumber(scanner);

        // Else determine parse path with remaining tokens
        switch (scanner->c) {
            case '\0':
                break; // Synonymous for the EOF Token
            default:
                std::cout << "[Scanner]: Unexpected character `" << scanner->c << "` (" << (int) scanner->c << ")"
                          << std::endl;
                exit(1);
        }
    }

    return initToken("EOF", EOF_tk);
}
