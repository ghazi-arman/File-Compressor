/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <bitset>

using namespace std;

class BitOutputStream {
	
private:

	ostream& out;
	char buffer;
	int nbits;

public:
	BitOutputStream(ostream& os) : out(os), buffer(0), nbits(0) {  }
	
	/** Write the least significant bit of the argument to the bit buffer,
	* and increment the bit buffer index. But flush the buffer first, if
	* it is full.
	*/
	void writeBit(int i);
	
	/** Write the least signficant byte of the argument to the ostream.
 	*
 	*/ 
	void writeByte(int b);
	
	/** Write an integer to the ostream.
 	*
 	*/ 
	void writeInt(int i);
	
	/** Flushes any bits in the buffer to the ostream, and then
 	* clear the bit buffer.
 	*/ 
	void flush();  
};

#endif //BITOUTPUTSTREAM_HPP
