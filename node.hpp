#pragma once
#include <iostream>
#include <string>

struct Node {
    std::string data;
    Node* next;
    Node* prev;

    Node(const std::string& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
        : data(value), next(nextNode), prev(prevNode) {
    }
};