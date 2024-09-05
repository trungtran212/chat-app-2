#include "user.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream file("users.txt");
    string username, password;
    
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
    return users;
}

bool signUp(const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();
    return true;
}

bool signIn() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers();
    return users.find(username) != users.end() && users[username] == password;
}
