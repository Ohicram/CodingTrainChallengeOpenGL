#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Cell.h"

#define GRID_SIZE  24

using namespace std;

static bool inline check_sub(const int i, const int j) {
	return (i >= 0 && i < GRID_SIZE) && (j >= 0 && j < GRID_SIZE);
}

static bool ind2sub(const int idx, int & i, int & j) {
	i = idx % GRID_SIZE;
	j = idx / GRID_SIZE;
	return check_sub(i, j);
}

static bool sub2ind(int &idx, const int i, const int j) {
	idx = j * GRID_SIZE + i;
	return check_sub(i, j);
}

static int findNeighbour(vector<Cell> & grid, int index) {
	int i, j;
	if (!ind2sub(index, i, j)) {
		cerr << "[findNeighbour(const vector<Cell> grid, int index)] >> Cell index: " << index << " out of range" << endl;
		return index;
	}
	vector<int> neighbours;
	for (int is = -1; is < 2; is += 2) {
		int t_idx;
		if (sub2ind(t_idx, i + is, j) && !grid[t_idx].IsVisited()) {
				neighbours.push_back(t_idx);
		}
	}
	for (int js = -1; js < 2; js += 2) {
		int t_idx;
		if (sub2ind(t_idx, i, j+js) && !grid[t_idx].IsVisited()) {
			neighbours.push_back(t_idx);
		}
	}
	//cout << "Neighbours size: " << neighbours.size() << endl;
	if (neighbours.size() > 0)
		return neighbours[rand() % neighbours.size()];
	return index;
}

static void removeWall(int a, int b, vector<Cell> & grid) {
	int ia, ib, ja, jb;
	ind2sub(a, ja, ia);
	ind2sub(b, jb, ib);
	if ((ia - ib) == -1) {
		grid[a].RemoveRight();
		grid[b].RemoveLeft();
	}
	if ((ia - ib) == 1) {
		grid[a].RemoveLeft();
		grid[b].RemoveRight();
	}
	if ((ja - jb) == -1) {
		grid[a].RemoveTop();
		grid[b].RemoveBottom();
	}
	if ((ja - jb) == 1) {
		grid[a].RemoveBottom();
		grid[b].RemoveTop();
	}
}