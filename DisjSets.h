#ifndef DISJ_SETS_86
#define DISJ_SETS_86
#include <vector>

class DisjSets
{

public:
	explicit DisjSets(int numEle);
	int find(int x);
	void unionSets( int root1, int root2);
	void print();
	bool check();
	std::vector<int> getSet();
private:
	std::vector<int> set;
};

#endif