/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"
#define VECTOR_SIZE 256

#include <iostream>
#include <algorithm>
#include <vector>
/* TODO */
/*Destructor*/
HCTree::~HCTree() {
	deleteAll(root);
}
/*destructor method helper*/
void HCTree::deleteAll(HCNode* node)const{
	if(!node){
		return;
	}
	deleteAll(node->c0);
	deleteAll(node->c1);
	delete node;
}
/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest; 
	for(int i = 0; i < VECTOR_SIZE; i++){
		if(freqs[i] != 0){
			HCNode* newNode = new HCNode(freqs[i], i);
			leaves.push_back(newNode);
			forest.push(newNode);
		}
	}
	while(forest.size() > 1){
		HCNode* c0 = forest.top();
		forest.pop();
		HCNode* c1 = forest.top();
		forest.pop();
		int newCount = c0->count + c1->count;
		HCNode* newParent = new HCNode(newCount, c1->symbol);
		newParent->c0 = c0;
		newParent->c1 = c1;
		c0->p = newParent;
		c1->p = newParent;
		forest.push(newParent);
		if(forest.size() == 1){
			root = newParent;
		}
	}
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {

}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
	HCNode* curr;
	char character = (char) symbol;
	for(unsigned int i = 0; i < leaves.size(); i++){
		if(character == leaves[i]->symbol){
			curr = leaves[i];
		}
	}
	HCNode* parent;
	while(curr->p){
		parent = curr->p;
		if(curr == parent->c0){
			out << '0';
		}else{
			out << '1';
		}
		curr = parent;
	}
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { 
	return ' ';
}

/* TODO */
byte HCTree::decode(istream& in) const { 
	HCNode* letter = root;
	char ch;
	while(!(letter->c0 || letter->c1)){
		in >> ch;
		if( ch == '0'){
			letter = letter->c0;
		}else{
			letter = letter->c1;
		}
	}
	return letter->symbol; 
}
