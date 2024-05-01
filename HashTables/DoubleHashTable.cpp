#include "DoubleHashTable.h"
#include <iostream>

DoubleHashTable::DoubleHashTable(int arrSize) {
	values = new int[arrSize];
	
	this->arrSize = arrSize;

	for (int i = 0; i < this->arrSize; i++) {
		values[i] = -1;
	}

	this->size = 0;
}

DoubleHashTable::~DoubleHashTable() {
	delete[] values;
}

// Хэшируем и проверяем наличие элемента в массиве. Если коллизия, то используем двойное хэшировние
void DoubleHashTable::insert(int value) {
	if (size == arrSize)
		throw std::runtime_error("table is full");

	int index = hash(value);
	int step = secondHash(value);
	
	if (values[index] != -1) {
		probeCount++;
		while (values[index] != -1) {
			index = (index + step) % arrSize;
		}
	}
	values[index] = value;
	size++;
}

int DoubleHashTable::getProbeCount() {
	return this->probeCount;
}

void DoubleHashTable::remove(int value) {
	int index = find(value);

	if (index == -1) {
		throw std::invalid_argument("Invalid value to remove");
	}

	values[index] = -1;
	size--;
}

int DoubleHashTable::find(int value) {
	int index = hash(value);
	int step = secondHash(value);
	
	this->probeCount++;

	// Ищем элемент с использование двойного хэширования
	while (values[index] != value && values[index] != -1) {
		index = (index + step) % arrSize;
		this->probeCount++;
	}
	
	// Не нашли элемент
	if (values[index] == -1)
		return -1;

	return index;
}


int DoubleHashTable::hash(int value) {
	return value % arrSize;
}

int DoubleHashTable::secondHash(int value) {
	return 7 - (value % 7);
}

int DoubleHashTable::get(int key) {
	return values[key];
}

int DoubleHashTable::getSize() {
	return this->size;
}

std::string DoubleHashTable::toString() {
	std::string string = "";

	for (int i = 0; i < arrSize; i++) {
		if (values[i] != -1) {
			string += std::to_string(values[i]) + " ";
		}
		else {
			string += "- ";
		}
	}

	return string;
}

void DoubleHashTable::clear() {
	for (int i = 0; i < arrSize; i++) {
		values[i] = -1;
	}
	size = 0;
	probeCount = 0;
}