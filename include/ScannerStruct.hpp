//
// Created by Nick Ray on 2/21/21.
//

#ifndef SCANNER_STRUCT_HPP
#define SCANNER_STRUCT_HPP

#include <fstream>

typedef struct {
    std::ifstream *src; // String created from source code
    char c;             // Current character
    unsigned int i;     // Current index
} Scanner;

#endif //SCANNER_STRUCT_HPP
