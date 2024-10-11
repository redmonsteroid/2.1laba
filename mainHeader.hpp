#pragma once
#include <iostream>
#include "node.hpp"
using namespace std;

struct Array {
    Node *head;
    int size;
    int maxCapacity;  // макс размер 

    // Конструкторы
    Array() : head(nullptr), size(0), maxCapacity(0) {}
    Array(int max) : head(nullptr), size(0), maxCapacity(max) {}

    void add(int index, string value);
    void addToTheEnd(string value);
    string get(int index);
    void remove(int index);
    void replace(int index, std::string value);
    int length();
    void print();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

struct Stack {
    Node *top;
    int size;

    Stack() : top(nullptr), size(0) {}

    void push( string value );
    void pop();
    void print();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

struct Queue {
    Node *front;
    Node *end;
    int size;

    Queue() : front(nullptr), end(nullptr), size(0) {}

    void push( string value );
    void pop();
    void print();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
