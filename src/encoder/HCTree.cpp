/**
 * TODO: Implementations of the HCTree functions: destructor, build, encode,
 * encode with bitwise i/o, decode, decode with bitwise i/o
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 */
#include "HCTree.hpp"
#define VECTOR_SIZE 256

#include <algorithm>
#include <iostream>
#include <vector>
/* TODO */
/*Destructor*/
HCTree::~HCTree() { deleteAll(root); }
/*destructor method helper*/
void HCTree::deleteAll(HCNode* node) const {
    if (!node) {
        return;
    }
    deleteAll(node->c0);
    deleteAll(node->c1);
    delete node;
}
/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;
    for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
        if (freqs[i] > 0) {
            HCNode* newNode = new HCNode(freqs[i], (unsigned char)i);
            leaves.push_back(newNode);
            forest.push(newNode);
        } else {
            leaves.push_back(nullptr);
        }
    }
    if (forest.size() == 1) {
        root = forest.top();
    }
    while (forest.size() > 1) {
        HCNode* c0 = forest.top();
        forest.pop();
        HCNode* c1 = forest.top();
        forest.pop();
        unsigned int newCount = (c0->count + c1->count);
        HCNode* newParent = new HCNode(newCount, c1->symbol);
        c0->p = newParent;
        c1->p = newParent;
        newParent->c0 = c0;
        newParent->c1 = c1;
        forest.push(newParent);
        if (forest.size() < 2) {
            root = newParent;
        }
    }
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* curr = leaves[symbol];
    HCNode* parent;
    string word = "";

    if (!curr->p) {
        out.writeBit(0);
    }
    while (curr->p) {
        parent = curr->p;
        if (curr == parent->c0) {
            word = "0" + word;
        } else {
            word = "1" + word;
            ;
        }
        curr = curr->p;
    }
    for (unsigned int i = 0; i < word.size(); i++) {
        if (word[i] == '0') {
            out.writeBit(0);
        } else {
            out.writeBit(1);
        }
    }
}
/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* curr;
    string word = "";
    curr = leaves[symbol];
    HCNode* parent;
    if (!curr->p) {
        out << "0";
    }
    while (curr->p) {
        parent = curr->p;
        if (curr == parent->c0) {
            word = "0" + word;
        } else {
            word = "1" + word;
        }
        curr = parent;
    }
    out << word;
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const {
    HCNode* letter = root;
    if (!(letter->c0 && letter->c1)) {
        in.fill();
    }
    while (letter->c0 && letter->c1) {
        if (in.readBit() == 0) {
            letter = letter->c0;
        } else {
            letter = letter->c1;
        }
    }
    return letter->symbol;
}

/* TODO */
byte HCTree::decode(istream& in) const {
    HCNode* letter = root;
    char ch;
    if (!(letter->c0 && letter->c1)) {
        ch = in.get();
    }
    while (letter->c0 && letter->c1) {
        ch = in.get();
        if (ch == '0') {
            letter = letter->c0;
        } else {
            letter = letter->c1;
        }
    }
    return letter->symbol;
}
