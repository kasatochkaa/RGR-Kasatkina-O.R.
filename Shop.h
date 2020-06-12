#ifndef _SHOP_H_
#define _SHOP_H_

#include "Node.h"

class Shop : public Node {
public:

	Shop(int i, int j) {
		this->i = i;
		this->j = j;
	}
};

#endif // _SHOP_H_
