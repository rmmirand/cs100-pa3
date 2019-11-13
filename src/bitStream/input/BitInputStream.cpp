/**
 * TODO: Implementation of fill and readBit functions from BitInputStream class.
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 *
 * fill and readBit function examples from STEPIK Data Structures Section 7.4
 */
#include "BitInputStream.hpp"
#define BYTE 8
/* TODO */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 8;
}

/* TODO */
unsigned int BitInputStream::readBit() {
    if (nbits == 0) {
        fill();
    }
    unsigned char temp = buf;
    temp = (temp >> (nbits - 1)) & 1;
    nbits--;
    return temp;
}
