/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
	HCTree* tree = new HCTree();
	vector<unsigned int> freqs(256);
	unsigned int freqNum;

	ifstream in;
	ofstream out;

	in.open(inFileName);
	out.open(outFileName, ios::trunc);
	
	for(unsigned int i = 0; i < 256; i++){
		in >> freqNum;
		freqs[i] = freqNum;
	}
	tree->build(freqs);
	while(!(in.peek() == EOF)){
		char decod= tree->decode(in);
		out << decod;
	}
	delete tree;
	in.close();
	out.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) { 

	pseudoDecompression(argv[1], argv[2]);
	return 0; 
}
