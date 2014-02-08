#include <iostream>
#include <cstdlib>
#include "DisjSets.h"
#include <time.h>
#include <vector>
void getInput(int &, int &);
void print(std::vector<char> board, int h, int w);
void clearScreen();

/*
Written by Aaron Andrews July 2012
*/


/*
A 3x3 grid

*******
*0*0*0* 
*******
*0*0*0*
*******
*0*0*0*
*******

0's represent a cell that has a top, bottom, left, and right wall that can be knocked down provided the
conditions are met.

A cell may not have a wall if
	- The wall is a boarder wall.
	- The wall has been knocked down.

Note that a cell shares a wall with the ajacent cells

Cell structure

 * 
*0*
 *


Math
	-total stars in a row = w + (w + 1) = 2w + 1
	-total stars in a column = h + (h + 1) = 2h + 1


*/

int main()
{
	int w;
	int h;
	srand (time(NULL));
	getInput(w, h);	

	DisjSets set(w * h);

	int cellNum = (2 * w + 1) * (2 * h + 1);
	
	std::vector<char> cells(cellNum, ' ');
	
	//Set up the board
	for(int i = 0; i < (2 * h + 1); i++)
	{
		for(int j = 0; j < (2 * w + 1); j++)
		{
			if(i % 2 != 0)
			{
				if(j % (2 * w) == 0 || j % 2 == 0)
					cells[i * (2 * w + 1) + j] = '@';
				else
					cells[i * (2 * w + 1) + j] = '0';
			}
			else
				cells[i * (2 * w + 1) + j] = '@';
		}
	}

	float r;
	float r2;

	int getCell;

	while(!set.check())
	{
		for(int i = 0; i < w * h; i++)
		{
			r = static_cast<float>(rand()) / RAND_MAX;
			r *= (w * h);
	
			r2 = static_cast<float>(rand()) / RAND_MAX;
			r2 *= 4;	
			switch((int)r2)
			{

			case 0:
				if(i % w != 0)
					getCell = i - 1;//West wall
				else 
					continue;
				break;
			case 1:
				getCell = i - w;//North wall
				if(getCell < 0)
					continue;
				break;
			case 2:
				if((i + 1) % w == 0)
					continue;
				getCell = i + 1;//East wall
				break;
			case 3:
				getCell = i + w;//South wall
				if(getCell > w * h - 1)
					continue;
				break;
			}
			
			if(set.find(i) != set.find(getCell))
			{	
				if(set.find(getCell) == getCell && getCell != 0)
				{
					set.unionSets( i, getCell );
				}
				else if(set.find(i) == i && i != 0)
				{
					set.unionSets( getCell, i );				
				}
				else
					set.unionSets(i, getCell);
			}
		}
	}
	
	std::vector<int> maze = set.getSet();
	int cell = 0;
	int count = 0;

	for(int i = 0; i < maze.size(); i++)
	{  
		for(int j = 0; j < cellNum; j++)
		{
			
			if(cells[j] == '0')
				count++;
			if(count == i + 1)
				break;
			cell++;
		}

		if(maze[i] != -1)
		{
			
			if(i + 1 == maze[i])
			{
				cells[cell + 1] = ' ';
			}
			else if(i - 1 == maze[i])
			{
				cells[cell - 1] = ' ';
			}
		  else if(i < maze[i] )
			{
				cells[cell + (2 * w + 1)] = ' ';
			}
			else if(i > maze[i] )
			{
				cells[cell - (2 * w + 1)] = ' ';
			}
		}
		count = 0;
		cell = 0;
	}
	
	for(int j = 0; j < cellNum; j++)
	{
		if(cells[j] == '0')
			cells[j] = ' ';
	}
	//clearScreen();
	print(cells, h, w);

	return EXIT_SUCCESS;
}

void getInput(int &w, int &h)
{
	std::cout << "Please enter a width from 1-39" << std::endl;
	std::cin >> w;

	std::cout << "Please enter a height from 1-120" << std::endl;
	std::cin >> h;

}

void print(std::vector<char> board, int h, int w)
{
	std::cout << std::endl;
	for(int i = 0; i < (2 * h + 1); i++)
	{
		for(int j = 0; j < (2 * w + 1); j++)
		{
			std::cout << board[i * (2 * w + 1) + j];
		}
		std::cout << "\n";
	}
}

void clearScreen()
{
	std::cout << std::string( 1000, '\n' );
}
