#include "DoubleHashTable.h"
#include <iostream>

DoubleHashTable::DoubleHashTable() {
	values = new int[arrSize];
}

DoubleHashTable::~DoubleHashTable() {
	delete[] values;
}

// Хэшируем и проверяем наличие элемента в массиве. Если коллизия, то используем двойное хэшировние
void DoubleHashTable::insert(int value) {
	int firstHash = hash(value);
	int secondHash = hash(value);

	for (int i = 0; i < arrSize - 1; i++) {
		if (values[firstHash] == 0) {
			values[firstHash] = value;
			break;
		}
		firstHash = (firstHash + secondHash) % arrSize;
	}
}

void DoubleHashTable::remove(int value) {
	int firstHash = hash(value);
	int secondHash = this->secondHash(value);

	for (int i = 0; i < arrSize - 1; i++) {
		if (values[firstHash] != 0) {
			if (values[firstHash] == value) {
				values[firstHash] = 0;
			}
		}
		// Next try
		firstHash = (firstHash + secondHash) % arrSize;
	}
}

int DoubleHashTable::find(int value) {
	int firstHash = hash(value);
	int secondHash = this->secondHash(value);

	for (int i = 0; i < arrSize - 1; i++) {
		if (values[firstHash] != 0) {
			if (values[firstHash] == value) {
				return firstHash;
			}
		}
		// Next try
		firstHash = (firstHash + secondHash) % arrSize;
	}
}


int DoubleHashTable::hash(int value) {
	return value % arrSize;
}

int DoubleHashTable::secondHash(int value) {
	return 1 + value % arrSize - 2;
}

int DoubleHashTable::get(int key) {
	return values[key];
}
