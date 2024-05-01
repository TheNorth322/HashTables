#pragma once
#include <string>
class HashTable {
public:
	virtual void insert(int value) = 0;
	virtual void remove(int value) = 0;
	virtual int find(int value) = 0;
	virtual int get(int key) = 0;
	virtual int getSize() = 0;
	virtual int getProbeCount() = 0;
	virtual void clear() = 0;
	virtual std::string toString() = 0;
};
