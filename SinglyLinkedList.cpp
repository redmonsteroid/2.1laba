#include "node.hpp"
#include "mainHeader.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void SinglyLinkedList::addToHead(string value){
    Node* newNode = new Node(value);
    newNode->next = head; // н узел указывает на голову
    head = newNode;
    size++;
}

void SinglyLinkedList::addToTail(string value){
    Node *newNode = new Node(value);
    if (head == nullptr){ // список пуст -> новый узел голова
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr){ // до конца 
            curent = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void SinglyLinkedlist::removeFromHead(){
    if (head == nullptr){
        cout << " list is empty" << endl;
        return;
    } else {
        Node *temp = head;
        head = head -> next;
        delete temp;
        size--;
    }
}

void SinglyLinkedlist::removeFromTail(){
    if (head == nullptr){
        cout << " list is empty" << endl;
        return;
    }

    if (head -> next == nullptr){ // один элемент в листе
        delete head;
        head == nullptr;
    } else {
        Node* current = head;
        while (current->next->next != nullptr){ // до предпоследнего
            curent = current->next;
        }
        delete current->next;
        current->next = nullptr;   
    }
    size--;
}

void SinglyLinkedList::removeByValue(string value) {
    if (head == nullptr) {
        cout << " List is empty." << endl;
        return;
    }

    if (head->data == value) {  // Если элемент в голове
        removeFromHead();
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {  // Поиск узла перед нужным
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;  // Временный указатель на узел, который нужно удалить
        current->next = current->next->next;  // Переподключаем указатели
        delete temp;  
        size--; 
    } else {
        cout << " Value not found." << endl;
    }
}


Node* SinglyLinkedList::searchByValue(string value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;  // Возвращаем узел, если значение совпало
        }
        current = current->next;
    }
    cout << " Value not found." << endl;
    return nullptr;  // Если элемент не найден, возвращаем nullptr
}


void SinglyLinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}



void SinglyLinkedList::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Node* current = head;
        while (current != nullptr) {
            file << current->data << endl;
            current = current->next;
        }
        file.close();
    } else {
        cout << " Unable to open file " << filename << endl;
    }
}


void SinglyLinkedList::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string value;
        while (getline(file, value)) {
            addToTail(value); // Добавляем каждый элемент в хвост
        }
        file.close();
    } else {
        cout << " Unable to open file " << filename << endl;
    }
}
