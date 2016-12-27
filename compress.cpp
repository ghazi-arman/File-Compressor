/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include "HCNode.hpp"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 3) {
		cerr << argv[0] << " called with incorrect arguments." << "\n";
		cerr << "Usage: " << argv[0] << " infile outfile" << "\n";
		return 0;
	}
	
	if(string(argv[1]) == string(argv[2])) {
		cerr << "infile and outfile must be different files" << "\n";
		cerr << argv[0] << " called with incorrect arguments. " << "\n";
		cerr << "Usage: " << argv[0] << + " infile outfile" << "\n";
		return 0;
	}

	ifstream inFile;
	inFile.open(argv[1], ios::in); 
	if(!inFile) {
		cerr << "Error opening \"0\"." << "\n";
		return 0;
	}

	ofstream outFile;
	outFile.open(argv[2], ios::out);
	if(!outFile) {
		cerr << "Error opening \"0\"." << "\n";
		return 0;
	}

	cerr << "Reading from this \"" << argv[1] << "\"... done." << "\n";
	HCTree hcTree;
	vector<int> freqs(256, 0);
	int count = 0;
	//Fill the vector with the frequencies of the symbols in the file
	while(((int)inFile.peek() != EOF)) {
		unsigned char symbol = inFile.get();
		if(freqs[symbol] == 0) {
			count++;
		}
		freqs[symbol]++;
	}
	cout << "Found " << count << " unique symbols in input file of size ";
	//Find size of the read file
	inFile.seekg(0, ios_base::end);
	int end = inFile.tellg();
	inFile.seekg(0, ios_base::beg);
	int beg = inFile.tellg();
	int inSize = end - beg;
	
	cout << inSize << " bytes." << "\n";
	cout << "Building Huffman code tree... ";
	hcTree.build(freqs);
	cout << "done." << "\n";
	
	inFile.seekg(0,inFile.beg);
	cerr << "Writing to file \"" << argv[2] << "\"... ";
	BitOutputStream bStrm (outFile);
	//Write the size of the original file into the ostream
	bStrm.writeInt(inSize);
	//Write the number of unique symbols in the original file
	bStrm.writeInt(count);
	//Create header by writing the character along with its frequency
	for(unsigned int i = 0; i < freqs.size(); i++) {
		if(freqs[i] != 0) {
			bStrm.writeByte(i);
			bStrm.writeInt(freqs[i]);
		}
	}
	//Encode the tree based on the header 
	while(((int)inFile.peek() != EOF)) {
		unsigned char c = inFile.get();
		hcTree.encode(c, bStrm);
	}
	
	bStrm.flush();
	outFile.flush();
	cout << "done." << "\n";

	//Calculating the size of the compressed file
	outFile.seekp(0, ios_base::end);
	int end2 = outFile.tellp();
	outFile.seekp(0, ios_base::beg);
	int beg2 = outFile.tellp();
	int outSize = end2 - beg2;
	cout << "Output file has size " << outSize << " bytes." << "\n";
	
	double ratio = (double)outSize/inSize;
	cout << "Compression ratio: " << ratio << "\n";
	
	inFile.close();
	outFile.close();
	
	return 0;
}
