#pragma once

struct Node {
	int key;
	int value;
	Node* next;
	Node(int key, int value) : key(key), value(value), next(nullptr) {}
};
