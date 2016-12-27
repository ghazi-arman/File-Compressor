/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "HCNode.hpp"

HCNode::~HCNode() {
	delete c0;
	delete c1;
}

bool HCNode::operator<(const HCNode& other) {
	if(this->count != other.count) {
		return count > other.count;
	}
	return this->symbol < other.symbol;
}

bool comp(HCNode* one, HCNode* other) {
	return *one < *other;
}
