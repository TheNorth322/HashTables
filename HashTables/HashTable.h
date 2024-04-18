#pragma once

class HashTable {
public:
	HashTable();
	virtual void insert(int value) = 0;
	virtual void remove(int value) = 0;
	virtual int find(int value) = 0;
	virtual int get(int key) = 0;
};
