#include "DisjSets.h"
#include <iostream>

DisjSets::DisjSets(int numEle) : set(numEle)
{

	for(unsigned int i = 0; i < set.size(); i++)
		set[i] = -1;

}

int DisjSets::find(int x)
{
	if(set[x] < 0)
		return x;
	else
		return find(set[x]);
	
}

void DisjSets::unionSets(int root1, int root2)
{
	set[root2] = root1;
}

void DisjSets::print()
{
	for(unsigned int i = 0; i < set.size(); i++)
		std::cout << i << "  " << set[i] << std::endl;
}


bool DisjSets::check()
{
	for(int i = 0; i < (set.size() - 1); i++)
	{
		if(find(i) != find(i + 1))
		{
			return false;
		}
	}
		return true;
} 

std::vector<int> DisjSets::getSet()
{
	return set;
}