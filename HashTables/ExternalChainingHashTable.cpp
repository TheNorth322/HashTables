#include "ExternalChainingHashTable.h"
#include <iostream>

ExternalChainingHashTable::ExternalChainingHashTable(int tableSize) {
    lists.resize(tableSize, nullptr);
    size = 0;
}

ExternalChainingHashTable::~ExternalChainingHashTable() {
    for (int i = 0; i < lists.size(); ++i) {
        Node* current = lists[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

void ExternalChainingHashTable::insert(int key, int value) {
    int index = hash(key);
    Node* newNode = new Node(key, value);
    newNode->next = lists[index];
    lists[index] = newNode;
    size++;
}

int ExternalChainingHashTable::get(int key) {
    int index = hash(key);
    Node* current = lists[index];
    while (current != nullptr) {
        if (current->key == key)
            return current->value;
        current = current->next;
    }
    throw std::invalid_argument("Key not found");
}

void ExternalChainingHashTable::remove(int key) {
    int index = hash(key);
    Node* prev = nullptr;
    Node* current = lists[index];

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr)
            lists[index] = current->next;
        else
            prev->next = current->next;
        delete current;
        size--;
    }
    else {
        throw std::invalid_argument("Key not found");
    }
}

std::string ExternalChainingHashTable::toString() {
    std::string result = "";
    for (int i = 0; i < lists.size(); ++i) {
        result += "[" + std::to_string(i) + "]: ";
        Node* current = lists[i];
        while (current != nullptr) {
            result += "(" + std::to_string(current->key) + "," + std::to_string(current->value) + ") ";
            current = current->next;
        }
        result += "\n";
    }
    return result;
}

int ExternalChainingHashTable::hash(int key) {
    return key % lists.size();
}

int ExternalChainingHashTable::getProbeCount() {
    return this->probeCount;
}

