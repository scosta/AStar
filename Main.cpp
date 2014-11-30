/*-----------------------------------------------------------------------------------
File:			Main.cpp
Author:			Steve Costa
Description:	This is the entry point for the application where the A* class
will be tested.
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
Header files
-----------------------------------------------------------------------------------*/
#include "AStar.h"
#include "stdafx.h"
#include <iostream>
#include <tchar.h>

/*-----------------------------------------------------------------------------------
Constants
-----------------------------------------------------------------------------------*/

#define NUM_ROWS1	7
#define NUM_COLS1	7

/*-----------------------------------------------------------------------------------
Program entry point
-----------------------------------------------------------------------------------*/

int _tmain(int argc, _TCHAR* argv[])
{
	int wait;						// Prompt for user input before ending
	TPathNode* path = NULL;			// Path returned by A*
	int path_length;				// Number of nodes in path
	CAStar star_search;				// A* object
	int s_row, s_col,				// Start and destination
		d_row, d_col;
	bool check;

	// Define the terrain that will be searched
	TTerrainNode terrain[NUM_ROWS1 * NUM_COLS1];

	// Terrain costs
	int t_cost[NUM_ROWS1 * NUM_COLS1] = {
		-1, -1, 0, 0, 0, -1, 0,
		-1, -1, -1, 0, 0, -1, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, -1, 0,
		-1, -1, 0, 0, 0, -1, -1,
		-1, -1, 0, 0, 0, -1, -1 };

	// Define the start and destination
	s_row = 0; s_col = 2; d_row = 4; d_col = 6;

	// Initialize the terrain array with cost values
	for (int i = 0; i < NUM_ROWS1 * NUM_COLS1; i++)
		terrain[i].terrain_cost = t_cost[i];

	// Print the terrain
	cout << endl << "GIVEN THESE CONSTRAINTS: " << endl << endl;
	for (int i = 0; i < NUM_ROWS1; i++)
	{
		for (int j = 0; j < NUM_COLS1; j++)
		{
			if (i == s_row && j == s_col) cout << "[S]\t";
			else if (i == d_row && j == d_col) cout << "[E]\t";
			else cout << t_cost[i * NUM_COLS1 + j] << "\t";
		}
		cout << endl;
	}

	cout << endl;

	// Set the standard cost for traversing one tile
	star_search.Init(10);

	// Have the A* find the shortest path
	if (star_search.FindPath(terrain, NUM_ROWS1, NUM_COLS1, s_row, s_col,
		d_row, d_col, path, path_length) < 0) {
		cout << "No Solution!" << endl;
	}
	else {
		// Print the path result
		cout << "THE SHORTEST PATH FOUND BY A* WAS:" << endl << endl;
		for (int i = 0; i < NUM_ROWS1; i++)
		{
			for (int j = 0; j < NUM_COLS1; j++)
			{
				check = false;

				for (int k = 0; k < path_length; k++)
				{
					if (path[k].row == i && path[k].col == j)
						check = true;
				}

				if (check) cout << "* ";
				else cout << "0 ";
			}
			cout << endl;
		}
	}

	// Clean up memory
	star_search.Shutdown();
	cout << "\nPress any key and enter to end";
	cin >> wait;

	return 0;
}