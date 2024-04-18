#pragma once
#include "HashTable.h"

class LinearProbingHashTable : public HashTable {
public:
	
	LinearProbingHashTable();
	~LinearProbingHashTable();

	void insert(int value) override;
	void remove(int value) override;
	int find(int value) override;
	int get(int key) override;
private:
	const int arrSize = 1000000;
	int hash(int value);
	void solveCollision(int index, int value);
	int* values;
};