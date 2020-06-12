#ifndef _NODE_H_
#define _NODE_H_

using namespace std;

class Node {
public:
	int i, j;

	string toString() {
		return "(x = " + to_string(i) + "; y = " + to_string(j) + ")";
	}
};

#endif //_NODE_H_
