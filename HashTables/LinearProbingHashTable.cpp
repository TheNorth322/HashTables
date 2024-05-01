#include "LinearProbingHashTable.h"
#include <iostream>
#include <string>

LinearProbingHashTable::LinearProbingHashTable(int arrSize) {
	this->arrSize = arrSize;
	values = new int[arrSize];
	this->probeCount = 0;

	for (int i = 0; i < arrSize; i++) {
		values[i] = -1;
	}

	this->size = 0;
}

LinearProbingHashTable::~LinearProbingHashTable() {
	delete[] values;
}

// �������� � ��������� ������� �������� � �������. ���� ��������, �� ���������� �������� ������������
void LinearProbingHashTable::insert(int value) {
	if (size == arrSize) {
		throw std::runtime_error("table is full");
	}

	int index = hash(value);
	
	// ��������
	if (values[index] != -1)
		probe(index, value);
	else {
		values[index] = value;
		size++;
	}
}

int LinearProbingHashTable::getSize() {
	return this->size;
}

int LinearProbingHashTable::get(int key) {
	return values[key];
}

std::string LinearProbingHashTable::toString() {
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

void LinearProbingHashTable::remove(int value) {
	int index = find(value);
	
	// �� ����� �������
	if (index == -1)
		throw new std::invalid_argument("Invalid value to remove");

	// ������� �������
	values[index] = -1;
	size--;

	int currentIndex = index;

	// ���� �� ����� �������
	do {
		currentIndex++;
		
		// ���������
		if (currentIndex == arrSize) {
			currentIndex = 0;
		}

		// ����� ������ �������, �������
		if (values[currentIndex] == -1)
			return;
		
		// ������ �� ������, ��������� ����� �� �� ����� �����
		int trueIndex = hash(values[currentIndex]);
		if (trueIndex != currentIndex) {
			int temp = values[currentIndex];
			
			// �������, 
			remove(values[currentIndex]);
			// ���������� �� ����� ����������
			insert(temp);
		}
	} while (currentIndex != index);

}

int LinearProbingHashTable::find(int value) {
	int index = hash(value);

	if (values[index] != value) {
		this->probeCount++;
		index++;
	}
	do {
		this->probeCount++;
		// ��������� (�� ����� � ������)
		if (index == arrSize)
			index %= arrSize;

		// ����� ������ �����
		if (values[index] == -1) {
			return -1;
		}

		// ����� ��������
		if (values[index] == value)
			return index;
		
		index++;
	} while (index != index);
}

int LinearProbingHashTable::hash(int value) {
	return value % arrSize;
}

int LinearProbingHashTable::getProbeCount() {
	return this->probeCount;
}
// �������� ������������
void LinearProbingHashTable::probe(int index, int value) {
	do {
		index++;
		
		// ����� �� �����, ��������� � ������
		if (index >= arrSize)
			index = 0;

		// ��������� � ������ �����
		if (values[index] == -1) {
			values[index] = value;
			break;
		}
		
	} while (index != index);
	size++;
}

void LinearProbingHashTable::clear() {
	for (int i = 0; i < arrSize; i++) {
		values[i] = -1;
	}
	size = 0;
	probeCount = 0;
}