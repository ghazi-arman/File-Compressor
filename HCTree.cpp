/**
 * C++ File Compressor 
 * Authors: Alan Chen
 *	    Arman Ghazi
 */

#include "HCTree.hpp"
#include <queue>
#include <vector>

using namespace std;

//Destructure that deletes the whole Huffman tree
HCTree::~HCTree() {
	delete root;
}

void HCTree::build(const vector<int>& freqs) {
	//Create priority queue of all the letters present in the file
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> q;
	
	for(unsigned int i = 0;i < freqs.size(); i++) {
		HCNode* lNode; 
		if(freqs[i] > 0) {
			lNode = new HCNode(freqs[i],(byte)i);
			q.push(lNode);
			leaves[i] = lNode;
		}
	}
	//Build Huffman Tree bottom-up starting with the two lowest frequency nodes
	while(q.size() > 0) {
		HCNode* c0;
		HCNode* c1;
		if(q.size() == 1) {
			root = q.top();
			q.pop();
		}
		else {
			c0 = q.top();
			q.pop();
			c1 = q.top();
			q.pop();
			int count = c0->count + c1->count;
			HCNode* p;
			p = new HCNode(count, (byte) 0, c0, c1);
			c0->p = p;
			c1->p = p;
			q.push(p);
		}
	}	
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
	HCNode* n = leaves[symbol];
	string s = "";
	if(n->count == 0) {
		return;
	}
	while(n->p != 0) {
		if(n->p->c0 == n) {
			s = "0" + s;
		}
		else {
			s = "1" + s;
		}
		n = n->p;
	}
	for(size_t i = 0; i < s.size(); i++) {
		int b = s[i] - '0';
		out.writeBit(b);
	}
}

void HCTree::encode(byte symbol, ofstream& out) const {
	HCNode* n = leaves[symbol];
	string s = "";
	if(n->count == 0) {
		return;
	}
	while(n->p != 0) {
		if(n->p->c0 == n) {
			s = "0" + s;
		} 
		else {
			s = "1" + s;
		}
		n = n->p;
	}
	out << s;
}

int HCTree::decode(BitInputStream& in) const {
	HCNode* n = root;
	int c = 0;
	if(n == 0) {
		return -1;
	}
	
	while((n->c0 != 0) && (n->c1 != 0)) {
		c = in.readBit();
		if(c == 0) {
			n = n->c0;
		}
		else {
			n = n->c1;
		}
	}
	if(n == root) {
		c = in.readBit();
	}
	
	return (int)n->symbol;
}

int HCTree::decode(ifstream& in) const {
	HCNode* n = root;
	unsigned char c;
	while((n->c0 != 0) && (n->c1 != 0)) {
		in >> c;
		if(c == '0') {
			n = n->c0;
		} 
		else {
			n = n->c1;
		}
	}
	if(n == root) {
		in.get();
	}
	return (int)n->symbol;
}

