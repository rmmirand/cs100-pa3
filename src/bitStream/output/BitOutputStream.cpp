/**
 * TODO: The implementations of the flush and writeBit functions of the
 * BitOutputStream class.
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 *
 * flush function taken from STEPIK Data Structures Section 7.4
 * writeBit function taken from Discussion 7 lecture slides.
 */
#include "BitOutputStream.hpp"
#define BYTE 8
/* TODO */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = 0;
    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(int i) {
    if (nbits == 8) {
        flush();
    }
    int here = BYTE - nbits - 1;
    buf = buf | (i << here);
    nbits++;
}
