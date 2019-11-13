/**
 * TODO: Contains the declaration of the constructor, flush and writeBit
 * functions and the members inside the BitOutputStream class. Author: Rosa
 * Miranda rmmirand@ucsd.edu
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* TODO: add function header and implement */
    /* Initializes the object and its members to the correct values*/
    explicit BitOutputStream(ostream& os) : out(os) {
        nbits = 0;
        buf = 0;
    };

    /* TODO: add function header */
    /* sends the byte to outstream and clears buffer*/
    void flush();

    /* TODO: add function header */
    /* Writes a bit to the buffer */
    void writeBit(int i);

    // returns number of bits
    int getBits() { return nbits; }
};

#endif
