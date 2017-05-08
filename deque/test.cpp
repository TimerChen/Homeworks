#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include "deque.hpp"
int n,m;
sjtu::deque<int> dui;
const int N = 20;
void error(){throw(0);}
void print( sjtu::deque<int> *d = &dui )
{
	int i,j;
	for(i=0;i<d->size();++i)
		printf("%d ",(*d)[i]);
		printf("\n");
}
void print( std::deque<int> *d )
{
	int i,j;
	for(i=0;i<d->size();++i)
		printf("%d ",(*d)[i]);
		printf("\n");
}
bool isEqual(std::deque<int> &a, sjtu::deque<int> &b) {
	static std::vector<int> resultA, resultB;
	resultA.clear();
	resultB.clear();
	for (auto x : a) resultA.push_back(x);
	for (auto x : b) resultB.push_back(x);
	if (resultA.size() != resultB.size()) return false;
	for (int i = 0; i < (int)resultA.size(); i++) {
		if (resultA[i] != resultB[i]) return false;
	}
	return true;
}
//errorBracketChecker
std::pair<bool, double> test() {
	std::deque<int> a;
	sjtu::deque<int> b;
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	std::deque<int>::iterator itA;
	sjtu::deque<int>::iterator itB;
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			printf("Part 1: %d\n", i);
			return std::make_pair(false, 0);
		}
		if (itA == a.end()) {
			itA--;
			itB--;
		}
		itA = a.erase(itA);
		itB = b.erase(itB);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			printf("Part 2: %d\n", i);
			return std::make_pair(false, 0);
		}
	}
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, 0);
	}
}

int main()
{
	int i,j;
	i = test().first;
	printf("%d\n",i);
	return 0;
	n = 6000;
	//freopen("out.txt","w",stdout);
	sjtu::deque<int> dui2(dui);
	//dui.clear();
	//dui2 = dui;
	dui = dui2;
	for(i=1;i<=n;++i)
	{
		dui.push_back(i);
		//printf("%d\n",dui[i-1]);
	}
	print();
	return 0;
}
