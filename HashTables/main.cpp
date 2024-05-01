#include <iostream>
#include "DoubleHashTable.h"
#include "LinearProbingHashTable.h"
#include <vector>
#include <unordered_set>
#include <chrono>

void testInsertAndSearch() {
	DoubleHashTable table(10);
	table.insert(5);
	table.insert(15);
	table.insert(25);

	if (table.get(table.find(5)) == 5)
		std::cout << "Test Insert and Search 1 passed\n";
	else
		std::cout << "Test Insert and Search 1 failed\n";

	if (table.get(table.find(15)) == 15)
		std::cout << "Test Insert and Search 2 passed\n";
	else
		std::cout << "Test Insert and Search 2 failed\n";

	if (table.get(table.find(25)) == 25)
		std::cout << "Test Insert and Search 3 passed\n";
	else
		std::cout << "Test Insert and Search 3 failed\n";
}

void testRemove() {
	DoubleHashTable table(10);
	table.insert(5);
	table.insert(15);
	table.insert(25);

	table.remove(15);

	if (table.find(15) == -1)
		std::cout << "Test Remove passed\n";
	else
		std::cout << "Test Remove failed\n";
}

void testCollision() {
	DoubleHashTable table(5);
	table.insert(5);
	table.insert(15);
	table.insert(25);
	table.insert(35); // Должен вызвать коллизию с 5

	if (table.get(table.find(5)) == 5)
		std::cout << "Test Collision 1 passed\n";
	else
		std::cout << "Test Collision 1 failed\n";

	if (table.get(table.find(15)) == 15)
		std::cout << "Test Collision 2 passed\n";
	else
		std::cout << "Test Collision 2 failed\n";

	if (table.get(table.find(25)) == 25)
		std::cout << "Test Collision 3 passed\n";
	else
		std::cout << "Test Collision 3 failed\n";

	if (table.get(table.find(35)) == 35)
		std::cout << "Test Collision 4 passed\n";
	else
		std::cout << "Test Collision 4 failed\n";
}

void testTableSize() {
	DoubleHashTable table(3);
	table.insert(5);
	table.insert(15);
	table.insert(25);

	bool exceptionThrown = false;
	try {
		table.insert(35);
	}
	catch (std::runtime_error& e) {
		exceptionThrown = true;
	}

	if (exceptionThrown)
		std::cout << "Test Table Size passed\n";
	else
		std::cout << "Test Table Size failed\n";
}

// Функция для генерации равномерно распределенных чисел на интервале [0, 1000000)
int generateUniformRandomNumber() {
	int randomBits = rand() << 15 | rand();
	return randomBits % 1000000;
}

std::vector<int> getDataSet(int size) {
	std::vector<int> numbers;
	std::unordered_set<int> seen;

	while (numbers.size() < size) {
		int num = generateUniformRandomNumber(); // генерируем число

		if (seen.find(num) == seen.end()) { // если число еще не было добавлено
			seen.insert(num);
			numbers.push_back(num); // добавляем в массив
		}
	}
	
	return numbers;
}
void fillTable(HashTable& table, const std::vector<int>& dataSet, int percentage) {
	int elementsToInsert = dataSet.size() * percentage / 100;
	table.clear();
	for (int i = 0; i < elementsToInsert; i++) {
		table.insert(dataSet[i]);
	}
}
// Функция для проведения серии успешных поисков
void successfulSearchExperiment(HashTable& table, const std::vector<int>& dataSet) {
	std::cout << "Successful search experiment:" << std::endl;
	double totalProbeCount = 0;

	for (int i = 1; i <= 9; ++i) {
		int successfulSearchCount = 0;
		fillTable(table, dataSet, i * 10);

		auto start = std::chrono::steady_clock::now();
		for (int j = 0; j < table.getSize(); ++j) {
			table.find(dataSet[j]);
			successfulSearchCount++;
		}

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;
		
		totalProbeCount = table.getProbeCount();
		double averageProbeCount =  (double) totalProbeCount / (double)successfulSearchCount;
		
		std::cout << "Search for " << i * 10 << "%" << " table. Time elapsed: " 
			<< elapsedSeconds.count() << " seconds." 
			<< " Average probe count for successful search: " << averageProbeCount << "expected: " << (double) (0.5f * (1.0f + 1.0f / (1.0f - ((double) table.getSize() / 100000.0f)))) << std::endl;
	}

}

void unsuccessfulSearchExperiment(HashTable& table, const std::vector<int>& dataSet) {
	std::cout << "Successful search experiment:" << std::endl;
	double totalProbeCount = 0;

	for (int i = 1; i <= 9; ++i) {
		int successfulSearchCount = 0;
		fillTable(table, dataSet, i * 10);

		auto start = std::chrono::steady_clock::now();
		for (int j = 0; j < table.getSize(); ++j) {
			table.find(1000001);
			successfulSearchCount++;
		}

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;
		
		totalProbeCount = table.getProbeCount();
		double averageProbeCount =  (double) totalProbeCount / (double)successfulSearchCount;
		
		std::cout << "Search for " << i * 10 << "%" << " table. Time elapsed: " 
			<< elapsedSeconds.count() << " seconds." 
			<< " Average probe count for successful search: " << averageProbeCount << "expected: " << (double) (0.5f * (1.0f + 1.0f / (1.0f - ((double) table.getSize() / 100000.0f)))) << std::endl;
	}

}

int main() {
	srand(time(NULL));

	int size = 100000;

	LinearProbingHashTable linearProbingHashTable = LinearProbingHashTable(size);
	DoubleHashTable doubleHashTable = DoubleHashTable(size);
	std::vector<int> dataSet = getDataSet(size);

	successfulSearchExperiment(doubleHashTable, dataSet);

	return 0;
}
