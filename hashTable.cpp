#include "node.hpp"
#include "mainHeader.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

HashTable::HashTable(int size) {
    capacity = size;
    table = new HashNode*[capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clearTable(table, capacity);
}

// Хеш-функция для вычисления индекса на основе ключа
int HashTable::hashFunction(const string& key) const {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % capacity;
    }
    return hash;
}

// Функция для добавления или обновления элемента
void HashTable::insert(const string& key, const string& value) {
    int index = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* current = table[index];

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {  // Ключ не найден, создаем новый элемент
        HashNode* newNode = new HashNode(key, value);
        if (prev == nullptr) {  // Вставляем в начало цепочки
            table[index] = newNode;
        } else {                // Добавляем в конец цепочки
            prev->next = newNode;
        }
        cout << "Inserted: [" << key << "] -> " << value << endl;
    } else {  // Ключ уже существует, обновляем значение
        current->value = value;
        cout << "Updated: [" << key << "] -> " << value << endl;
    }
}

// Функция для получения значения по ключу
string HashTable::get(const string& key) {
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            cout << "Found: [" << key << "] -> " << current->value << endl;
            return current->value;
        }
        current = current->next;
    }
    cout << "Key [" << key << "] not found!" << endl;
    return "";
}

// Функция для удаления элемента по ключу
void HashTable::remove(const string& key) {
    int index = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* current = table[index];

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Key [" << key << "] not found!" << endl;
        return;
    }

    if (prev == nullptr) {  // Удаление первого элемента в цепочке
        table[index] = current->next;
    } else {                // Удаление элемента в середине или конце цепочки
        prev->next = current->next;
    }

    delete current;  // Освобождение памяти
    cout << "Deleted: [" << key << "]" << endl;
}

// Функция для сохранения хеш-таблицы в файл
void HashTable::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < capacity; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                outFile << current->key << " " << current->value << endl;
                current = current->next;
            }
        }
        outFile.close();
    } else {
        cerr << "Unable to open file for writing!" << endl;
    }
}

// Функция для загрузки хеш-таблицы из файла
void HashTable::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string key, value;
        clearTable(table, capacity);  // Очищаем текущую хеш-таблицу перед загрузкой
        while (inFile >> key >> value) {
            insert(key, value);
        }
        inFile.close();
    } else {
        cerr << "Unable to open file for reading!" << endl;
    }
}

// Функция для вывода всех элементов хеш-таблицы
void HashTable::print() const {
    for (int i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            cout << "[" << current->key << "] -> " << current->value << endl;
            current = current->next;
        }
    }
}

// Функция для очистки хеш-таблицы
void HashTable::clearTable(HashNode** table, int size) {
    for (int i = 0; i < size; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    delete[] table;
}
