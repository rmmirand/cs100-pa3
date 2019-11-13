/**
 * TODO: file header
 *
 * Author: Rosa Miranda
 * empty file check from cplusplus infile documentation
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

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
	if(!out.good()){
		fstream file(outFileName, ios::out);
		out.close();
		out.open(outFileName, ios::trunc);
	}

	vector<unsigned int> frequencies(256);
	while(in.peek() != ifstream::traits_type::eof()){
		unsigned char a = in.get();
		frequencies[(unsigned char)a]++;
	}
	tree->build(frequencies);
	in.close();
	in.open(inFileName);
	for(unsigned int i = 0; i < frequencies.size(); i++){
		out << frequencies[i] << endl;
	}
	while(in.peek() != ifstream::traits_type::eof()){
		in.get(wurd);
		tree->encode((unsigned char)wurd, out);
	}
	delete tree;
	in.close();
	out.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 
	cxxopts::Options options("./compress", "Compress files using Huffman Encoding");
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
		pseudoCompression(argv[2], argv[3]);
	}else{

	}

	return 0; }
