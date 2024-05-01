#pragma once
#include "HashTable.h"

class DoubleHashTable : public HashTable {
public:

	DoubleHashTable(int arrSize);
	~DoubleHashTable();

	void insert(int value) override;
	void remove(int value) override;
	int find(int value) override;
	int get(int key) override;
	int getSize() override;
	int getProbeCount() override;
	void clear() override;

	std::string toString() override;
private:
	int arrSize;
	int size;
	int probeCount;

	int hash(int value);
	int secondHash(int value);
	int* values;
};