#ifndef _ROUTE_H_
#define _ROUTE_H_

#include <vector>
#include "Node.h"
#include "Shop.h"
#include "Warehouse.h"
#include "Link.h"
#include <cmath>
using namespace std;

class Route {
public:
	vector<Shop> wh;
	vector<Link> Links;
	Warehouse store;

	void setStore(Warehouse newWarehouse) {
		store = newWarehouse;
	}

	void setShop(Shop newShop) {
		wh.push_back(newShop);
	}

	void setLink(Link newLink) {
		Links.push_back(newLink);
	}

	void printwh() {
		for (Shop i : wh) {
			cout << i.toString() << endl;
		}
	}

	void printStore() {
		cout << store.toString() << endl;
	}

	void printLinks() {
		for (Link i : Links) {
			cout << i.begin.toString() << " -> " << i.end.toString() << endl;
		}
	}

	float shortestLink(Node begin, Node end) {
		return sqrt(pow((begin.i-end.i),2)+ pow((begin.j - end.j),2));
	}
};

#endif //_ROUTE_H_
