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
