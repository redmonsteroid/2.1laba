#include <iostream>
#include <sstream>
#include <vector>
#include "mainHeader.hpp"

using namespace std;

void processQuery(const string& query, Array& array) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    // Split query into parts
    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    if (tokens[0] == "MPUSH") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            string value = tokens[2];
            array.add(index, value); // Add element to array at index
        } else {
            cout << "Error: MPUSH command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "MDEL") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]);
            array.remove(index); // Remove element by index
        } else {
            cout << "Error: MDEL command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "MGET") {
        if (tokens.size() == 2) {
            int index = stoi(tokens[1]);
            string value = array.get(index); // Get element by index
            cout << "Element at index " << index << ": " << value << endl;
        } else {
            cout << "Error: MGET command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "MREPLACE") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            string value = tokens[2];
            array.replace(index, value); // Replace element by index
        } else {
            cout << "Error: MREPLACE command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "PRINT") {
        array.print(); // Display array
    } else {
        cout << "Unknown command: " << tokens[0] << endl;
    }
}

int main(int argc, char* argv[]) {
    string query;
    string filename;
    int capacity = 10; // Default array size

    // Default array with a size of 10
    Array array(capacity);

    // Reading command line arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];  // Get file name
        }
        if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];  // Get query
        }
    }

    // Load data from file, if specified
    if (!filename.empty()) {
        array.loadFromFile(filename);
    }

    if (!query.empty()) {
        processQuery(query, array); // Process the query
    } else {
        cout << "Error: query not specified." << endl;
        return 1;
    }

    // Save data to file after processing the query, if file is specified
    if (!filename.empty()) {
        array.saveToFile(filename);
    }

    return 0;
}
