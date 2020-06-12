#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Route.h"
#include "Shop.h"
#include "Warehouse.h"
#include <locale.h>

using namespace std;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");

	system("color 70");
	ifstream map;
	char ch = 0;
	int n=0, m=0;

	cout << "Карта: " << endl << endl;

	map.open("Map.txt");
	cout << " ";
	while (ch != -1) {
		ch = (char) map.get();
		if (ch != 'я') {
			cout << ch;
		}
		if (ch == '0') {
			m++;
		} else if(ch == '1'){
			m++;
		} else if (ch == '2') {
			m++;
		} else if (ch == '3') {
			m++;
		}
		if (ch == '\n') {
			n++;
		}
		cout << " ";
	}
	map.close();

	m = m / n;

	int** chart = new int* [n];
	for (int i = 0; i < n; i++) {
		chart[i] = new int[m];
	}

	ifstream in;
	in.open("Map.txt");
	for (int i = 0; i < n;i++) {
		for (int j = 0; j < m; j++) {
			in >> chart[i][j];
		}
	}
	in.close();

	int stc = 0, shc = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (chart[i][j] == 3) {
				stc++;
			}
			if (chart[i][j] == 2) {
				shc++;
			}
			if(chart[i][j] == 3 && chart[i+1][j] == 1 && chart[i-1][j] == 1 && chart[i][j+1] == 1 && chart[i][j-1] == 1){
				cout << "Склад недоступен!" << endl;
				return 0;
			} else if (chart[i][j] == 2 && chart[i + 1][j] == 1 && chart[i - 1][j] == 1 && chart[i][j + 1] == 1 && chart[i][j - 1] == 1) {
				cout << "Один из магазинов недоступен!" << endl;
				return 0;
			}
		}
	}


	if (stc > 1) {
		cout << "Больше двух складов нельзя" << endl;
		return 0;
	} else if (stc == 0) {
		cout << "Нет ни одного склада" << endl;
		return 0;
	}

	if (shc == 0) {
		cout << "Нет ни одного магазина" << endl;
		return 0;
	}

	Route Route;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (chart[i][j] == 2) {
				Shop shop(i, j);
				Route.setShop(shop);
			} else if (chart[i][j] == 3) {
				Warehouse store(i, j);
				Route.setStore(store);
			}
		}
	}

	cout << endl << "Склад: " << endl;
	Route.printStore();
	cout << endl << "Магазины: " << endl;
	Route.printwh();

	vector<Node> tN;
	tN.push_back(Route.store);
	for (Shop i : Route.wh) {
		tN.push_back(i);
	}

	int iter = tN.size();
	Node b, e;
	for (int i = 0; i < iter;i++) {
		Link Link;
		if (i==0) {
			b = tN[0];
			Link.setBegin(b);
			float min = Route.shortestLink(b, tN[1]);
			for (int j = 1; j < tN.size(); j++) {
				if (Route.shortestLink(b, tN[j]) < min) {
					min = Route.shortestLink(b, tN[j]);
				}
			}
			for (int j = 1; j < tN.size(); j++) {
				if (Route.shortestLink(b, tN[j]) == min) {
					Link.setEnd(tN[j]);
					b = tN[j];
					tN.erase(tN.begin() + j);
					break;
				}
			}
		} else if(i == iter-1){
			Link.setBegin(b);
			e = tN.back();
			Link.setEnd(e);
		} else {
			Link.setBegin(b);
			float min = Route.shortestLink(b, tN[iter-i-1]);
			for (int j = 1; j < iter - i; j++) {
				if (Route.shortestLink(b, tN[j]) < min) {
					min = Route.shortestLink(b, tN[j]);
				}
			}
			for (int j = 1; j < iter - i; j++) {
				if (Route.shortestLink(b, tN[j]) == min) {
					Link.setEnd(tN[j]);
					b = tN[j];
					tN.erase(tN.begin() + j);
					break;
				}
			}
		}
		Route.setLink(Link);
	}
	cout << endl << "Маршрут по точкам: " << endl;
	Route.printLinks();
	cout << endl;
	int counter = 0;
	for (Link l : Route.Links) {
		int ci = l.begin.i, cj = l.begin.j;

		while ((ci != l.end.i) || (cj != l.end.j)){

			if (ci < l.end.i) {
				if (counter > m * n) {
					break;
				}
				if (chart[ci + 1][cj] != 1) {
					ci++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci][cj + 1] != 1) {
					cj++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					if (chart[ci + 1][cj] != 1) {
						ci++;
						chart[ci][cj] = 4;
						counter++;
						if ((ci == l.end.i) && (cj == l.end.j)) {
							chart[ci][cj] = 5;
							break;
						}
						continue;
					}
					continue;
				} else if (chart[ci - 1][cj] != 1) {
					ci--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci][cj-1] != 1) {
					cj--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				}
			}
			if (cj < l.end.j) {
				if (counter > m * n) {
					break;
				}
				if (chart[ci][cj + 1] != 1) {
					cj++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci - 1][cj] != 1) {
					ci--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					if (chart[ci][cj + 1] != 1) {
						cj++;
						chart[ci][cj] = 4;
						counter++;
						if ((ci == l.end.i) && (cj == l.end.j)) {
							chart[ci][cj] = 5;
							break;
						}
						continue;
					}
					continue;
				} else if (chart[ci + 1][cj] != 1) {
					ci++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci][cj - 1] != 1) {
					cj--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				}
			}

			if (ci > l.end.i) {
				if (counter > m * n) {
					break;
				}
				if (chart[ci - 1][cj] != 1) {
					ci--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci][cj - 1] != 1) {
					cj--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					if (chart[ci - 1][cj] != 1) {
						ci--;
						chart[ci][cj] = 4;
						counter++;
						if ((ci == l.end.i) && (cj == l.end.j)) {
							chart[ci][cj] = 5;
							break;
						}
						continue;
					}
					continue;
				} else if (chart[ci][cj + 1] != 1) {
					cj++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci + 1][cj] != 1) {
					ci++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				}
			}
			if (cj > l.end.j) {
				if (counter > m * n) {
					break;
				}
				if (chart[ci][cj - 1] != 1) {
					cj--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				} else if (chart[ci + 1][cj] != 1) {
					ci++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					if (chart[ci][cj - 1] != 1) {
						cj--;
						chart[ci][cj] = 4;
						counter++;
						if ((ci == l.end.i) && (cj == l.end.j)) {
							chart[ci][cj] = 5;
							break;
						}
						continue;
					}
					continue;
				} else if (chart[ci - 1][cj] != 1) {
					ci--;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				}else if (chart[ci][cj + 1] != 1) {
					cj++;
					chart[ci][cj] = 4;
					counter++;
					if ((ci == l.end.i) && (cj == l.end.j)) {
						chart[ci][cj] = 5;
						break;
					}
					continue;
				}
			}
		}
	}
	cout << endl << "Путь занял " << counter << " шагов." << endl << "Маршрут: " << endl << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (chart[i][j] == 0) {
				cout << '_';
			} else if (chart[i][j] == 1) {
				cout << '^';
			} else if (chart[i][j] == 4) {
				cout << '.';
			} else if (chart[i][j] == 5) {
				cout << '*';
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << endl << "_ - Дороги;\n. - Маршрут;\n^ - Строения;\n* - Точки;\n\n";

	for (int i = 0; i < n; i++) {
		delete[] chart[i];
	}
}
