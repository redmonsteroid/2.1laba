#include <iostream>
#include <sstream>
#include <vector>
#include "mainHeader.hpp"

using namespace std;

void processQuery(const string& query, Array& array, Stack& stack, Queue& queue) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    while (getline(ss, token, ' ')) { // Разбиваем строку запроса на отдельные токены
        tokens.push_back(token);
    }

    // массив (array)
    if (tokens[0] == "MPUSH") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = tokens[2];    // Значение, которое нужно добавить
            array.add(index, value);     // Добавляем элемент в массив
        } else {
            cout << "Error: MPUSH command requires 2 arguments." << endl;
        }
    }
    
    else if (tokens[0] == "MDEL") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            array.remove(index);         // Удаляем элемент из массива
        } else {
            cout << "Error: MDEL command requires 1 argument." << endl;
        }
    }
    
    else if (tokens[0] == "MGET") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = array.get(index); // Получаем элемент из массива
            cout << "Element at index " << index << ": " << value << endl;
        } else {
            cout << "Error: MGET command requires 1 argument." << endl;
        }
    }
    
    else if (tokens[0] == "MREPLACE") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = tokens[2];    // Новое значение для замены
            array.replace(index, value); // Замена элемента в массиве
        } else {
            cout << "Error: MREPLACE command requires 2 arguments." << endl;
        }
    }

    // стек (stack)
    else if (tokens[0] == "SPUSH") {
        if (tokens.size() == 2) {
            string value = tokens[1];    // Значение, которое нужно добавить в стек
            stack.push(value);           // Добавляем элемент в стек
        } else {
            cout << "Error: SPUSH command requires 1 argument." << endl;
        }
    }
    
    else if (tokens[0] == "SPOP") {
        stack.pop(); // Удаляем элемент из стека
    }

    // очередь (queue)
    else if (tokens[0] == "QPUSH") {
        if (tokens.size() == 2) {
            string value = tokens[1];    // Значение, которое нужно добавить в очередь
            queue.push(value);           // Добавляем элемент в очередь
        } else {
            cout << "Error: QPUSH command requires 1 argument." << endl;
        }
    }
    
    else if (tokens[0] == "QPOP") {
        queue.pop(); // Удаляем элемент из очереди
    }

    // общая операция вывода для всех структур данных
    else if (tokens[0] == "PRINT") {
        array.print();  // Вывод массива
        stack.print();  // Вывод стека
        queue.print();  // Вывод очереди
    }
    
    else {
        cout << "Unknown command: " << tokens[0] << endl;
    }
}


int main(int argc, char* argv[]) {
    string query;
    string filename;
    int capacity = 10; // Емкость массива
    Array array(capacity); // Создаем массив с заданной емкостью
    Stack stack;           // Создаем стек
    Queue queue;           // Создаем очередь

    // Обрабатываем аргументы командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "--file" && i + 1 < argc) { // Проверка на флаг --file
            filename = argv[++i];
        }
        if (arg == "--query" && i + 1 < argc) { // Проверка на флаг --query
            query = argv[++i];
        }
    }

    // Если был указан файл, загружаем данные массива из файла
    if (!filename.empty()) {
        array.loadFromFile(filename);
    }

    // Если был указан запрос, обрабатываем его
    if (!query.empty()) {
        processQuery(query, array, stack, queue); // Передаем массив, стек и очередь в функцию
    } else {
        cout << "Error: query not specified." << endl;
        return 1;
    }

    // Если был указан файл, сохраняем данные массива обратно в файл
    if (!filename.empty()) {
        array.saveToFile(filename);
        stack.saveToFile(filename);
    }

    return 0;
}
