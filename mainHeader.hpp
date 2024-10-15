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

struct SinglyLinkedList {
    Node *head;
    int size;

    SinglyLinkedList() : head(nullptr), size(0) {}

    void addToHead(string value);
    void addToTail(string value);
    void removeHead();
    void removeTail();
    void removeByValue(string value);
    Node* search(string value);
    void print();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

struct DoublyLinkedList {
    DoublyNode* head = nullptr;
    DoublyNode* tail = nullptr;
    int size;

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void addToHead(string value);
    void addToTail(string value);
    void removeFromHead();
    void removeFromTail();
    void removeByValue(string value);
    DoublyNode* search(string value);
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

struct HashNode {
    std::string key;
    std::string value;
    HashNode* next;

    HashNode(const std::string& k, const std::string& v, HashNode* nextNode = nullptr)
        : key(k), value(v), next(nextNode) {}
};

// Класс HashTable для реализации хеш-таблицы
class HashTable {
public:
    HashTable(int size = 10);
    ~HashTable();

    void hset(const std::string& key, const std::string& value);
    void hget(const std::string& key) const;
    void hdel(const std::string& key);
    void clear();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void hprint() const;

private:
    int hashFunction(const std::string& key) const;
    HashNode** table;
    int capacity;
};
