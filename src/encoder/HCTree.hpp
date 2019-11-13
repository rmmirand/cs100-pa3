/**
 * TODO: Defines the HCTree class, which takes a frequency vector to build a
 * tree based on the vector, encode and decode a given file.
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** TODO: class header */
/** Defines the members and functions within the HCTree class */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

  public:
    /* TODO: add function header and implement */
    /* Initializes tree with a null root */
    HCTree() { root = nullptr; }

    /* TODO: add function header */
    /* deletes all nodes in tree */
    ~HCTree();

    /* TODO: add function header */
    /* Builds a tree and assigns bit sequences to characters*/
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    /* compresses a given file using bitwise i/o*/
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    /* compresses a given file using pseudocompression*/
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    /* decodes a compressed file using bitwise i/o*/
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    /* decodes a compressed file using pseudodecompression*/
    byte decode(istream& in) const;

    /* helper method for destructor */
    void deleteAll(HCNode* node) const;
};

#endif  // HCTREE_HPP
