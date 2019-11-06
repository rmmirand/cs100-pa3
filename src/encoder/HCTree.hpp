/**
 * TODO: file header
 *
 * Author:
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
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

  public:
    /* TODO: add function header and implement */
    /* Initializes tree with a null root */
    HCTree() {
    	root = nullptr;
    }

    /* TODO: add function header */
    /* deletes all nodes in tree */
    ~HCTree();

    /* TODO: add function header */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    byte decode(istream& in) const;

    /* helper method for destructor */
    void deleteAll(HCNode* node) const;
 
};

#endif  // HCTREE_HPP
