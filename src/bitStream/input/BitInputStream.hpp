/**
 * TODO: Contains all the neccesary functions that make up the BitInputStream
 * class, including a constructor, a fill function and a bit reader function.
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /* TODO: add function header and implement */
    /* Initializes BitInputStream and its members to the appropriate values */
    explicit BitInputStream(istream& is) : in(is) {
        buf = 0;
        nbits = 0;
    };

    /* TODO: add function header */
    /* Fills the buffer with one byte from the stream */
    void fill();

    /* TODO: add function header */
    /* Reads next bit in the stream or fills buffer if empty*/
    unsigned int readBit();
};

#endif
