/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "BitInputStream.hpp"

void BitInputStream::fill() {
	buffer = in.get();
	nbits = 0;
}

int BitInputStream::readBit() {
	if(nbits == 8) {
		fill();
	}
	
	int bit = buffer & (1 << nbits);
	nbits++;
	//Return 1 if bit is 1 or return 0 if it is 0
	return (bit > 0 ? 1 : 0);
}

int BitInputStream::readByte() {
	if(in.eof()) {
		return EOF_REACHED;
	}
	
	unsigned char c = 0;
	in.read((char*)& c, sizeof(c));
	
	return (int) c;
}

int BitInputStream::readInt() {
	if(in.eof()) {
		return EOF_REACHED;
	}
	
	int intVal = 0;
	in.read((char*)& intVal, sizeof(intVal));
	
	return (int)intVal;
}
