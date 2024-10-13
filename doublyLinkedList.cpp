#include "node.hpp"
#include "mainHeader.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void DoublyLinkedList::addToHead(string value) {
    DoublyNode* newNode = new DoublyNode(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head-> prev = newNode;
        head = newNode;
    }
    size++;
}

void DoublyLinkedList::addToTail(string value) {
    DoublyNode* newNode = new DoublyNode(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void DoublyLinkedList::removeFromHead() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    DoublyNode* temp = head;
    if (head == tail) {  // Если в списке один элемент
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size--;
}

void DoublyLinkedList::removeFromTail() {
    if (tail == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    DoublyNode* temp = tail;
    if (head == tail) {  // Если в списке один элемент
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size--;
}

void DoublyLinkedList::removeByValue(string value) {
    DoublyNode* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            if (current == head) {
                removeFromHead();
            } else if (current == tail) {
                removeFromTail();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                size--;
            }
            return;
        }
        current = current->next;
    }
    cout << "Value not found." << endl;
}

DoublyNode* DoublyLinkedList::searchByValue(string value) {
    DoublyNode* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    cout << "Value not found." << endl;
    return;
}

void DoublyLinkedList::print() {
    DoublyNode* current = head;
    while (current != nullptr) {
        cout << current->data << "<-> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

void DoublyLinkedList::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        DoublyNode* current = head;
        while (current != nullptr) {
            file << current->data << " ";
            current = current->next;
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

// Загрузка списка из файла
void DoublyLinkedList::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string value;
        while (file >> value) {
            addToTail(value);
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}