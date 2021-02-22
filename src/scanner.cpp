#include <stdlib.h>
#include "ScannerStruct.hpp"

Scanner *initScanner(std::ifstream &src) {
    Scanner *scanner = (Scanner*) malloc (sizeof(Scanner));

    scanner->src = &src;
    scanner->i = 0;
    scanner->src->get(scanner->c); // Explicitly set the first character

    return scanner;
}

void advanceScanner(Scanner *scanner) {
    scanner->i += 1;
    scanner->src->get(scanner->c);
}