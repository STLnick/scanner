//
// Created by Nick Ray on 2/21/21.
//

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "ScannerStruct.hpp"

Scanner* initScanner(std::ifstream &src);
void advanceScanner(Scanner *scanner);

#endif //SCANNER_HPP
