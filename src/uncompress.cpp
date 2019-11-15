/**
 * TODO: The Uncompression file that takes in a compressed file and uncompresses
 * it to the output file. Uses --ascii flag to determine whether to use
 * pseudoDecompression or trueDecompression.
 *
 * Author: Rosa Miranda
 * rmmirand@ucsd.edu
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

#define ASCII 256
#define ARGONE 1
#define ARGTWO 2

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    HCTree* tree = new HCTree();
    vector<unsigned int> freqs(ASCII);
    unsigned int freqNum;
    string letters;

    ifstream in;
    ofstream out;

    in.open(inFileName, ios::binary);
    out.open(outFileName, ios::trunc);
    if (!out.good()) {
        out.close();
        fstream out(outFileName, ios::out);
        out.open(outFileName, ios::trunc);
    }
    for (unsigned int i = 0; i < ASCII; i++) {
        in >> freqNum;
        freqs[i] = freqNum;
    }
    tree->build(freqs);
    in.get();
    while (in.peek() != ifstream::traits_type::eof()) {
        unsigned char decod = tree->decode(in);
        out << decod;
    }
    delete tree;
    in.close();
    out.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {
    HCTree* tree = new HCTree();
    vector<unsigned int> freqs(ASCII);
    string letters;

    ifstream in;
    ofstream out;

    in.open(inFileName, ios::binary);
    out.open(outFileName, ios::trunc);
    if (!out.good()) {
        out.close();
        fstream out(outFileName, ios::out);
        out.open(outFileName, ios::trunc);
    }
    unsigned int a;
    unsigned int num;
    unsigned int chars;
    unsigned int count = 0;
    unsigned int totcnt = 0;
    bool go = true;

    chars = ((unsigned int)in.get() - '0');
    while (in.peek() != '\n') {
        chars *= 10;
        chars = chars + ((unsigned int)in.get() - '0');
    }
    in.get();
    unsigned int i = 1;
    while (go) {
        a = in.get();
      //  num = ((unsigned int)in.get() - '0');
       // while (in.peek() != '\n') {
        //    num = num * 10;
         //   num = num + ((unsigned int)in.get() - '0');
       // }
       // in.get();
        freqs[(unsigned char)a] = i;
	i++;
        if ((in.peek() == '\n') && (freqs['\n'] > 0)) {
            a = in.get();
	    go = false;
        }
    }

    in.get();
    BitInputStream input(in);
    tree->build(freqs);
    while (count < chars) {
        unsigned char decod = tree->decode(input);
        out << decod;
        count++;
    }
    delete tree;
    in.close();
    out.close();
}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./uncompress",
                             "Uncompress files using Huffman Encoding");
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
/*
    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({"help"}) << std::endl;
        exit(0);
    }*/

    if (isAsciiOutput) {
        pseudoDecompression(argv[ARGONE + 1], argv[ARGTWO + 1]);
    } else {
        trueDecompression(argv[ARGONE], argv[ARGTWO]);
    }
    return 0;
}
