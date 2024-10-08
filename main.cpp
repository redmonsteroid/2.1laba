#include <iostream>
#include <sstream>
#include <vector>
#include "mainHeader.hpp"

using namespace std;

void processQuery(const string& query, Array& array) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    while (getline(ss, token, ' ')) {// Разбиваем строку запроса на отдельные токены, используя пробел как разделитель
        tokens.push_back(token);
    }

    
    if (tokens[0] == "MPUSH") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = tokens[2];    // Значение, которое нужно добавить
            array.add(index, value);     // Вызов метода add для добавления элемента
        } else {
            cout << "Error: MPUSH command requires 2 arguments." << endl;
        }
    }
  
    else if (tokens[0] == "MDEL") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            array.remove(index);         // Вызов метода remove для удаления элемента
        } else {
            cout << "Error: MDEL command requires 1 argument." << endl;
        }
    }
 
    else if (tokens[0] == "MGET") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = array.get(index); // Вызов метода get для получения элемента
            cout << "Element at index " << index << ": " << value << endl; // Вывод значения
        } else {
            cout << "Error: MGET command requires 1 argument." << endl;
        }
    }
    
    else if (tokens[0] == "MREPLACE") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]); // Преобразование индекса в целое число
            string value = tokens[2];    // Новое значение для замены
            array.replace(index, value); // Вызов метода replace для замены элемента
        } else {
            cout << "Error: MREPLACE command requires 2 arguments." << endl;
        }
    }
    
    else if (tokens[0] == "PRINT") {
        array.print(); 
    }
    
    else {
        cout << "Unknown command: " << tokens[0] << endl;
    }
}

int main(int argc, char* argv[]) {
    string query;
    string filename;
    int capacity = 10; // Задаем изначальную емкость массива
    Array array(capacity); // Создаем объект Array с заданной емкостью


    for (int i = 1; i < argc; i++) {  // Обработка аргументов командной строки
        string arg = argv[i];
    
        if (arg == "--file" && i + 1 < argc) {// Проверка на наличие --file для загрузки данных из файла
            filename = argv[++i];
        }
        if (arg == "--query" && i + 1 < argc) {// Проверка на наличие флага --query для выполнения запроса
            query = argv[++i];
        }
    }

    // Если был указан файл, загружаем данные массива из файла
    if (!filename.empty()) {
        array.loadFromFile(filename);
    }

    // Если был указан запрос, обрабатываем его
    if (!query.empty()) {
        processQuery(query, array); // Вызов функции для обработки запроса
    } else {
        cout << "Error: query not specified." << endl;
        return 1;
    }

    // Если был указан файл, сохраняем данные массива обратно в файл
    if (!filename.empty()) {
        array.saveToFile(filename);
    }

    return 0;
}
