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
#include "cxxopts.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
	HCTree* tree = new HCTree();
	vector<unsigned int> freqs(256);
	unsigned int freqNum;
	string letters;

	ifstream in;
	ofstream out;

	in.open(inFileName, ios::binary);
	out.open(outFileName, ios::trunc);
	if(!out.good()){
		out.close();
		fstream out(outFileName, ios::out);
		out.open(outFileName, ios::trunc);
	}
	for(unsigned int i = 0; i < 256; i++){
		in >> freqNum;
		freqs[i] = freqNum;
	}
	tree->build(freqs);
	in.get();
	while(in.peek()!= ifstream::traits_type::eof()){
		unsigned char decod= tree->decode(in);
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
	cxxopts::Options options("./uncompress", "Uncompress files using Huffman Encoding");
	options.positional_help("./path_to_input_file ./path_to_output_file");
	bool isAsciiOutput = false;
	string inFileName, outFileName;
	options.allow_unrecognised_options().add_options()(
			"ascii", "Write output in ascii mode instead of bit stream",
			cxxopts::value<bool>(isAsciiOutput))(
			"input", "", cxxopts::value<string>(inFileName))(
			"output", "", cxxopts::value<string>(outFileName))(
			"h,help", "Print help and exit");
	options.parse_positional({"input", "output"});
	auto userOptions = options.parse(argc, argv);

	if(userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
			outFileName.empty()){
		        cout << options.help({"help"}) << std::endl;
			exit(0);
	}

	if(isAsciiOutput){
		pseudoDecompression(argv[2], argv[3]);
	}
	return 0; 
}
