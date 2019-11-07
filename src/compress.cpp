/**
 * TODO: file header
 *
 * Author:
 * empty file check from cplusplus infile documentation
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
	HCTree* tree = new HCTree();
	char wurd;

	ifstream in;
	ofstream out;

	in.open(inFileName, ios::binary);
	out.open(outFileName, ios::trunc);

	if(in.peek() == ifstream::traits_type::eof()){
		return;	
	}

	vector<unsigned int> frequencies(256);
	char a;
	in.get(a);
	while(!in.eof()){
		frequencies[a]++;
		in.get(a);
	}
	
	tree->build(frequencies);
	in.close();
	in.open(inFileName);
	for(unsigned int i = 0; i < 256; i++){
		out << frequencies[i] << endl;
	}
	while(in.peek() != ifstream::traits_type::eof()){
		in.get(wurd);
		tree->encode(wurd, out);
	}
	delete tree;
	in.close();
	out.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 	
	pseudoCompression(argv[1], argv[2]);

	return 0; }
