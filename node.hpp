#pragma once
#include <string>

using namespace std;

struct Node {
    std::string data;
    Node* next;

    Node(const std::string& value, Node* nextNode = nullptr)
        : data(value), next(nextNode) {
    }
};

struct DoublyNode {
    std::string data;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(const std::string& value, DoublyNode* nextNode = nullptr, DoublyNode* prevNode = nullptr)
        : data(value), next(nextNode), prev(prevNode) {
    }
};

struct HashNode {
    string key;
    string value;
    HashNode* next;

    // Конструктор узла с инициализацией ключа и значения
    HashNode(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};
