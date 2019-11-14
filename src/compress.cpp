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
#define ARGONE 1
#define ARGTWO 2
#define ARGTHREE 3
#define ASCII 256
/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    HCTree* tree = new HCTree();
    char wurd;

    ifstream in;
    ofstream out;

    in.open(inFileName, ios::binary);
    out.open(outFileName, ios::trunc);

    if (in.peek() == ifstream::traits_type::eof()) {
        return;
    }
    if (!out.good()) {
        fstream file(outFileName, ios::out);
        out.close();
        out.open(outFileName, ios::trunc);
    }

    vector<unsigned int> frequencies(ASCII);
    while (in.peek() != ifstream::traits_type::eof()) {
        unsigned char a = in.get();
        frequencies[(unsigned char)a]++;
    }
    tree->build(frequencies);
    in.close();
    in.open(inFileName);
    for (unsigned int i = 0; i < frequencies.size(); i++) {
        out << frequencies[i] << endl;
    }
    while (in.peek() != ifstream::traits_type::eof()) {
        in.get(wurd);
        tree->encode((unsigned char)wurd, out);
    }

    delete tree;
    in.close();
    out.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {
    HCTree* tree = new HCTree();
    char wurd;

    ifstream in;
    ofstream out;

    in.open(inFileName, ios::binary);
    out.open(outFileName, ios::trunc);

    if (in.peek() == ifstream::traits_type::eof()) {
        return;
    }
    if (!out.good()) {
        fstream file(outFileName, ios::out);
        out.close();
        out.open(outFileName, ios::trunc);
    }

    BitOutputStream stream(out);
    vector<unsigned int> frequencies(ASCII);

    while (in.peek() != ifstream::traits_type::eof()) {
        unsigned char a = in.get();
        frequencies[(unsigned char)a]++;
    }
    tree->build(frequencies);
    out << (unsigned char)tree->getRoot()->count;
    for (unsigned int i = 0; i < frequencies.size(); i++) {
        if (frequencies[i] > 0) {
            out << (unsigned char)i << frequencies[i] << " ";
        }
    }
    out << "\n"
        << "00" << endl;
    in.close();
    in.open(inFileName, ios::binary);
    while (in.peek() != ifstream::traits_type::eof()) {
        in.get(wurd);
        tree->encode((unsigned char)wurd, stream);
    }
    cout << "length: " << outFileName.length();
    delete tree;
    in.close();
    out.close();
}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compress files using Huffman Encoding");
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

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({"help"}) << std::endl;
        exit(0);
    }

    if (isAsciiOutput) {
        pseudoCompression(argv[ARGONE + 1], argv[ARGTWO + 1]);
    } else {
        trueCompression(argv[ARGONE], argv[ARGTWO]);
    }

    return 0;
}
