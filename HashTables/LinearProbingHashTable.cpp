#include "LinearProbingHashTable.h"
#include <iostream>

LinearProbingHashTable::LinearProbingHashTable() {
	values = new int[arrSize];
}

LinearProbingHashTable::~LinearProbingHashTable() {
	delete[] values;
}

// Хэшируем и проверяем наличие элемента в массиве. Если коллизия, то используем линейное зондирование
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
	
	// Не нашли элемент
	if (index == -1)
		throw new std::invalid_argument("Invalid value to remove");

	// Удалили элемент
	values[index] = 0;
	
	int currentIndex = index;

	// Идем до конца массива
	while (currentIndex != arrSize - 1) {
		// Нашли пустой элемент, выходим
		if (values[currentIndex] == 0)
			return;
		
		// Ячейка не пустая, проверяем стоит ли на своем месте
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
		// Нашли пустое место
		if (values[index] == 0) {
			return -1;
		}

		// Нашли значение
		if (values[index] == value)
			return index;

		// Дошли до конца, переходим в начало
		if (index == arrSize - 1)
			index = 0;

		index++;
	} while (index != index);
}

int LinearProbingHashTable::hash(int value) {
	return value % arrSize;
}

// Линейное зондирование
void LinearProbingHashTable::solveCollision(int index, int value) {
	do {
		index++;
		
		// Вставляем в пустое место
		if (values[index] == 0)
			values[index] = value;
		
		// Дошли до конца, переходим в начало
		if (index == arrSize - 1)
			index = 0;

	} while (index != index);
}