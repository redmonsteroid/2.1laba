#include <iostream>
#include <sstream>
#include <vector>
#include "mainHeader.hpp"
#include <fstream>

using namespace std;

void processQuery(const string& query, Array& array, Stack& stack, Queue& queue, SinglyLinkedList& singlyList, DoublyLinkedList& doublyList, HashTable& hashTable) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    // Массив (array)
    if (tokens[0] == "MPUSH") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            string value = tokens[2];
            array.add(index, value);
        } else {
            cout << "Error: MPUSH command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "MDEL") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]);
            array.remove(index);
        } else {
            cout << "Error: MDEL command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "MGET") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]);
            string value = array.get(index);
            cout << "Element at index " << index << ": " << value << endl;
        } else {
            cout << "Error: MGET command requires 1 argument." << endl;
        }
    }

    // Стек (stack)
    else if (tokens[0] == "SPUSH") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            stack.push(value);
        } else {
            cout << "Error: SPUSH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "SPOP") {
        stack.pop();
    }

    // Очередь (queue)
    else if (tokens[0] == "QPUSH") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            queue.push(value);
        } else {
            cout << "Error: QPUSH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "QPOP") {
        queue.pop();
    }

    // Односвязный список (singlyList)
    else if (tokens[0] == "LSADDHEAD") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            singlyList.addToHead(value);
        } else {
            cout << "Error: LSADDHEAD requires 1 argument." << endl;
        }
    }

    // Двусвязный список (doublyList)
    else if (tokens[0] == "LDADDHEAD") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            doublyList.addToHead(value);
        } else {
            cout << "Error: LDADDHEAD requires 1 argument." << endl;
        }
    }

    // Хэш-таблица (hashTable)
    else if (tokens[0] == "HSET") {
        if (tokens.size() == 3) {
            string key = tokens[1];
            string value = tokens[2];
            hashTable.insert(key, value);
        } else {
            cout << "Error: HSET command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "HGET") {
        if (tokens.size() == 2) {
            string key = tokens[1];
            string value = hashTable.get(key);
            cout << "Value for key [" << key << "]: " << value << endl;
        } else {
            cout << "Error: HGET command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "HDEL") {
        if (tokens.size() == 2) {
            string key = tokens[1];
            hashTable.remove(key);
        } else {
            cout << "Error: HDEL command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "HPRINT") {
        hashTable.print();
    }

    // Общая операция PRINT
    else if (tokens[0] == "PRINT") {
        array.print();
        stack.print();
        queue.print();
        singlyList.print();
        doublyList.print();
        hashTable.print();
    } else {
        cout << "Unknown command: " << tokens[0] << endl;
    }
}

int main(int argc, char* argv[]) {
    string query;
    string filename;
    int capacity = 10; 
    Array array(capacity); 
    Stack stack;           
    Queue queue;           
    SinglyLinkedList singlyList;
    DoublyLinkedList doublyList;
    HashTable hashTable(capacity);  // Хэш-таблица

    // Чтение аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    // Логика загрузки данных для конкретной структуры данных
    if (!filename.empty() && !query.empty()) {
        stringstream ss(query);
        string command;
        ss >> command;

        // Проверка команд для массива
        if (command[0] == 'M') {
            array.loadFromFile(filename);
        }
        // Проверка команд для стека
        else if (command[0] == 'S') {
            stack.loadFromFile(filename);
        }
        // Проверка команд для очереди
        else if (command[0] == 'Q') {
            queue.loadFromFile(filename);
        }
        // Проверка команд для односвязного списка
        else if (command[0] == 'L' && command[1] == 'S') {
            singlyList.loadFromFile(filename);
        }
        // Проверка команд для двусвязного списка
        else if (command[0] == 'L' && command[1] == 'D') {
            doublyList.loadFromFile(filename);
        }
        // Проверка команд для хэш-таблицы
        else if (command[0] == 'H') {
            hashTable.loadFromFile(filename);
        } else if (command == "PRINT") {
            if (!filename.empty()) {
                ifstream file(filename);
                if (file.is_open()) {
                    string line;
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                    file.close();
                } else {
                    cout << "Error: could not open file " << filename << endl;
                }
            } else {
                cout << "Error: no file specified for PRINT." << endl;
            }
        } else {
            cout << "Error: unrecognized command type." << endl;
            return 1;
        }
    }

    // Выполнение запроса
    if (!query.empty()) {
        processQuery(query, array, stack, queue, singlyList, doublyList, hashTable);
    } else {
        cout << "Error: query not specified." << endl;
        return 1;
    }

    // Логика сохранения данных для конкретной структуры данных
    if (!filename.empty() && !query.empty()) {
        stringstream ss(query);
        string command;
        ss >> command;

        // Сохранение данных только для нужной структуры
        if (command[0] == 'M') {
            array.saveToFile(filename);
        }
        else if (command[0] == 'S') {
            stack.saveToFile(filename);
        }
        else if (command[0] == 'Q') {
            queue.saveToFile(filename);
        }
        else if (command[0] == 'L' && command[1] == 'S') {
            singlyList.saveToFile(filename);
        }
        else if (command[0] == 'L' && command[1] == 'D') {
            doublyList.saveToFile(filename);
        }
        else if (command[0] == 'H') {
            hashTable.saveToFile(filename);
        } else if (command == "PRINT") {
           return 1; 
        } else {
            cout << "Error: unrecognized command type." << endl;
            return 1;
        }
    }

    return 0;
}
