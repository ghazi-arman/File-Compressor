/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#define MSB_MASK 0x80
#define EOF_REACHED -1

#include <iostream>
#include <bitset>

using namespace std;

class BitInputStream {
	
private:
	istream& in;
	char buffer;
	int nbits;
	
public:

	BitInputStream(istream& is) : in(is) {
		buffer = 0;
		nbits = 8;
	}
	
	/** Fill the buffer from the input */
	void fill();

	/** Read the next bit from the big buffer. Fill the buffer
     * from the input stream.
     * Return bit as the LSB of an int.
     * Return -1 at EOF.
     */
	int readBit();
	
	/** Read a byte from the ostream.
     * Return -1 at EOF.
     *
     */ 
	int readByte();
	
	/** Read a non-negative int from the ostream.
     * Return -1 at EOF
     *
     */ 
	int readInt();
};

#endif //BITINPUTSTREAM_HPP
