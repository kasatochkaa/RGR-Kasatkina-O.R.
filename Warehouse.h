#ifndef _WAREHOUSE_H_
#define _WAREHOUSE_H_


#include "Node.h"

class Warehouse : public Node{
public:

	Warehouse() {

	}

	Warehouse(int i, int j) {
		this->i = i;
		this->j = j;
	}

};

#endif //_WAREHOUSE_H_
