/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "BitOutputStream.hpp"
#include <iostream>

void BitOutputStream::writeBit(int i) {
	if(nbits == (int)sizeof(char)*8)
		flush();
	
	buffer = buffer| ((i&1)<< nbits);
	
	nbits++;
}

void BitOutputStream::writeByte(int b) {
	char c = b;
	out.write((char*)&c, sizeof(c));
}

void BitOutputStream::writeInt(int i) {
	out.write((char*)&i, sizeof(i));
}

void BitOutputStream::flush() {
	out.put(buffer);
	out.flush();
	
	buffer = nbits = 0;
}
