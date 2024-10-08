#include "node.hpp"
#include "mainHeader.hpp"
#include <fstream>
#include <string>

using namespace std;

void Array::add(int index, string value) {
    if (index < 0 || index > size || size>=maxCapacity) {
        cout << "Index invalid" << endl;
        return;
    }
    Node *newNode = new Node(value); // create new node with value
    if (index == 0) { //new node is head, rebond head
     newNode->next = head;
     head = newNode;
    } else {
         Node *temp = head;
         for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
         }
         newNode->next = temp->next;
         temp->next = newNode;
    }
     size++;
}

void Array::addToTheEnd(int index) {
    add (size, index); //size == index of the end
}
void Array::remove(int index) {
    if (index < 0 || index >= size) {
         cout << "Index invalid" << endl; //index out of range
         return;
    }

    Node *deleteNode = nullptr;
    if (index == 0) { //delete head
        deleteNode=head;
        head = head->next;
    } else{
         Node *temp = head;
         for (int i = 0; i < index - 1; i++) {
             temp = temp->next; 
         }
        deleteNode = temp->next; //pointer to the node to be deleted
        temp->next = deleteNode->next;
    }
    size--;
    delete deleteNode;
}
void Array::replace(int index, string value) {
     if (index < 0 || index >= size) {
        cout << "Index invalid" << endl;
        return;
     }
     Node *temp = head; //pointer to the node to be replaced
     for (int i = 0; i < index; i++) {
         temp = temp->next;

     }
     temp->data = value; //replace the data
}
void Array::print() {
    Node *temp=head;
    while (temp){
        cout << temp->data << " ";
        temp=temp->next;
    }
    cout << endl;
}
void Array::length(){
    return size;
}
void Array::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Cannot open file for writing: " << filename << endl;
        return;
    }

    Node* temp = head;
    while (temp) {
        outFile << temp->data << endl;
        temp = temp->next;
    }
    
    outFile.close();
}

// Чтение массива из файла
void Array::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Cannot open file for reading: " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        addToTheEnd(line);  // Чтение строки из файла и добавление в массив
    }

    inFile.close();
}