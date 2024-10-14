#include <iostream>
#include <sstream>
#include <vector>
#include "mainHeader.hpp"
#include <fstream>

using namespace std;

void processQuery(const string& query, Array& array, Stack& stack, Queue& queue, SinglyLinkedList& singlyList, DoublyLinkedList& doublyList) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    // массив (array)
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
    } else if (tokens[0] == "MREPLACE") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            string value = tokens[2];
            array.replace(index, value);
        } else {
            cout << "Error: MREPLACE command requires 2 arguments." << endl;
        }
    }

    // стек (stack)
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

    // очередь (queue)
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

    // односвязный список (singlyList)
    else if (tokens[0] == "LSADDHEAD") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            singlyList.addToHead(value);
        } else {
            cout << "Error: LSADDHEAD requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LSADDTAIL") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            singlyList.addToTail(value);
        } else {
            cout << "Error: LSADDTAIL requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LSDELHEAD") {
        singlyList.removeHead();
    } else if (tokens[0] == "LSDELTAIL") {
        singlyList.removeTail();
    }

    // двусвязный список (doublyList)
    else if (tokens[0] == "LDADDHEAD") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            doublyList.addToHead(value);
        } else {
            cout << "Error: LDADDHEAD requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LDADDTAIL") {
        if (tokens.size() == 2) {
            string value = tokens[1];
            doublyList.addToTail(value);
        } else {
            cout << "Error: LDADDTAIL requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LDDELHEAD") {
        doublyList.removeFromHead();
    } else if (tokens[0] == "LDDELTAIL") {
        doublyList.removeFromTail();
    }

    // общая операция PRINT
    else if (tokens[0] == "PRINT") {
        array.print();
        stack.print();
        queue.print();
        singlyList.print();
        doublyList.print();
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
        else if (command == "PRINT") {
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
        }else {
            cout << "Error: unrecognized command type." << endl;
            return 1;
        }
    }

    // Выполнение запроса
    if (!query.empty()) {
        processQuery(query, array, stack, queue, singlyList, doublyList);
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
        }else if (command == "PRINT") {
           return 1; 
        }else {
            cout << "Error: unrecognized command type." << endl;
            return 1;
        }
    }

    return 0;
}
