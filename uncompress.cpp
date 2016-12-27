/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include "HCNode.hpp"

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

	ifstream inFile(argv[1], ios::binary); 
	if(!inFile) {
		cerr << "Error opening \"0\"." << "\n";
		return 0;
	}

	ofstream outFile(argv[2]);
	if(!outFile) {
		cerr << "Error opening \"0\"." << "\n";
		return 0;
	}

	//Calculate the size of the compressed file 
	inFile.seekg(0, ios_base::end);
	int end = inFile.tellg();
	inFile.seekg(0, ios_base::beg);
	int beg = inFile.tellg();
	int inSize = end - beg;

	HCTree hcTree;
	int count;
	int numChar = 0;;
	int size;
	int outSize;

	//Read in header to create frequency vector.
	vector<int> freqs(256, 0);
	BitInputStream bStrm(inFile);
	cerr << "Reading header from file \"" << argv[1] << "\"... done.\n";
#define ISEOF(to, from) \
	if((to = from) == -1) { \
		cerr << "Problem: EOF while reading header." << endl;\
		return 0;\
	}
		
	ISEOF(size, bStrm.readInt());
	ISEOF(count, bStrm.readInt());
	for(int i = 0; i < count; i++) {
		int symbol;
		ISEOF(symbol, bStrm.readByte());
		ISEOF(freqs[(size_t)symbol], bStrm.readInt());
	}
#undef ISEOF
	
	cout << "Uncompressed file will have " << count;
	cout << " unique symbols and size " << size << " bytes.\n";
	cout << "Building Huffman code tree... done.\n";
	hcTree.build(freqs);
	cerr << "Writing to file \"" << argv[2] << "\"... done.\n";
	
	//Decode the tree based on the header
	int counter = 0;
	while( ((int)inFile.peek()) != EOF || counter < size) {
		int c = hcTree.decode(bStrm);
		if(c < 0) {
			break;
		}
		outFile << (byte) c;
		counter++;
	} 
	
	//Calculate the size of the uncompressed file
	outFile.seekp(0, ios_base::end);
	int end2 = outFile.tellp();
	outFile.seekp(0, ios_base::beg);
	int beg2 = outFile.tellp();
	outSize = end2 - beg2;
	
	double ratio = (double)outSize/inSize;
	cout << "Uncompression ratio: " << ratio << "\n";
	
	inFile.close();
	outFile.close();
	
	return 0;
}
