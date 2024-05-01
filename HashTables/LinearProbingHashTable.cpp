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

// Хэшируем и проверяем наличие элемента в массиве. Если коллизия, то используем линейное зондирование
void LinearProbingHashTable::insert(int value) {
	if (size == arrSize) {
		throw std::runtime_error("table is full");
	}

	int index = hash(value);
	
	// Коллизия
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
	
	// Не нашли элемент
	if (index == -1)
		throw new std::invalid_argument("Invalid value to remove");

	// Удалили элемент
	values[index] = -1;
	size--;

	int currentIndex = index;

	// Идем до конца массива
	do {
		currentIndex++;
		
		// Замыкание
		if (currentIndex == arrSize) {
			currentIndex = 0;
		}

		// Нашли пустой элемент, выходим
		if (values[currentIndex] == -1)
			return;
		
		// Ячейка не пустая, проверяем стоит ли на своем месте
		int trueIndex = hash(values[currentIndex]);
		if (trueIndex != currentIndex) {
			int temp = values[currentIndex];
			
			// Удаляем, 
			remove(values[currentIndex]);
			// Перемещаем на место удаленного
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
		// Замыкание (из конца в начало)
		if (index == arrSize)
			index %= arrSize;

		// Нашли пустое место
		if (values[index] == -1) {
			return -1;
		}

		// Нашли значение
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
// Линейное зондирование
void LinearProbingHashTable::probe(int index, int value) {
	do {
		index++;
		
		// Дошли до конца, переходим в начало
		if (index >= arrSize)
			index = 0;

		// Вставляем в пустое место
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