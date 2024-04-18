#pragma once
#include "HashTable.h"

class DoubleHashTable : public HashTable {
public:

	DoubleHashTable();
	~DoubleHashTable();

	void insert(int value) override;
	void remove(int value) override;
	int find(int value) override;
	int get(int key) override;
private:
	const int arrSize = 1000000;
	int hash(int value);
	int secondHash(int value);
	int* values;
};