#include "LinearProbingHashTable.h"
#include <iostream>

LinearProbingHashTable::LinearProbingHashTable() {
	values = new int[arrSize];
}

LinearProbingHashTable::~LinearProbingHashTable() {
	delete[] values;
}

// �������� � ��������� ������� �������� � �������. ���� ��������, �� ���������� �������� ������������
void LinearProbingHashTable::insert(int value) {
	int index = hash(value);

	if (values[index] == 0)
		values[index] = value;
	else 
		solveCollision(index , value);
	
}

int LinearProbingHashTable::get(int key) {
	return values[key];
}

void LinearProbingHashTable::remove(int value) {
	int index = find(value);
	
	// �� ����� �������
	if (index == -1)
		throw new std::invalid_argument("Invalid value to remove");

	// ������� �������
	values[index] = 0;
	
	int currentIndex = index;

	// ���� �� ����� �������
	while (currentIndex != arrSize - 1) {
		// ����� ������ �������, �������
		if (values[currentIndex] == 0)
			return;
		
		// ������ �� ������, ��������� ����� �� �� ����� �����
		int trueIndex = hash(values[currentIndex]);
		if (trueIndex != currentIndex) {
			int temp = values[currentIndex];

			remove(values[currentIndex]);
			values[index] = temp;
		}
	}

}

int LinearProbingHashTable::find(int value) {
	int index = hash(value);

	do {
		// ����� ������ �����
		if (values[index] == 0) {
			return -1;
		}

		// ����� ��������
		if (values[index] == value)
			return index;

		// ����� �� �����, ��������� � ������
		if (index == arrSize - 1)
			index = 0;

		index++;
	} while (index != index);
}

int LinearProbingHashTable::hash(int value) {
	return value % arrSize;
}

// �������� ������������
void LinearProbingHashTable::solveCollision(int index, int value) {
	do {
		index++;
		
		// ��������� � ������ �����
		if (values[index] == 0)
			values[index] = value;
		
		// ����� �� �����, ��������� � ������
		if (index == arrSize - 1)
			index = 0;

	} while (index != index);
}