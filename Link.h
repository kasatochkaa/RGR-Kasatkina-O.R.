#ifndef _LINK_H_
#define _LINK_H_

#include "Node.h"

class Link {
public:
	Node begin, end;

	Link() {

	}

	Link(Node begin, Node end) {
		this->begin = begin;
		this->end = end;
	}

	void setBegin(Node begin) {
		this->begin = begin;
	}

	void setEnd(Node end) {
		this->end = end;
	}
};

#endif // _LINK_H_
