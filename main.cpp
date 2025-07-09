
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "include/picosha2.h"


using namespace std;


class User {
public:
    int usernameLength;
    static const int hashLength = 64; 
    static const int saltLength = 8;  

    string username;
    string salt;
    string hashedPassword;

    
    User(const string& uname, const string& password) {
        username = uname;
        usernameLength = uname.length();
        salt = generateSalt(saltLength);
        hashedPassword = picosha2::hash256_hex_string(salt + password);
    }

    
    string toLine() const {
        return username + salt + hashedPassword;
    }

private:
   
    string generateSalt(int length) {
        string salt;
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        srand(time(0));
        for (int i = 0; i < length; ++i) {
            salt += charset[rand() % (sizeof(charset) - 1)];
        }
        return salt;
    }
};

void saveUserToFile(const User& user) {
    ofstream file("users.txt", ios::app);
    file << user.toLine() << endl;
    file.close();
}


bool userExists(const string& username) {
    ifstream file("users.txt");
    string line;
    int usernameLength = username.length();

    while (getline(file, line)) {
        string storedUsername = line.substr(0, usernameLength);
        if (storedUsername == username) {
            return true;
        }
    }

    return false;
}


bool login(const string& username, const string& password) {
    ifstream file("users.txt");
    string line;
    int usernameLength = username.length();

    while (getline(file, line)) {
        

        string storedUsername = line.substr(0, usernameLength);
        string storedSalt = line.substr(usernameLength, User::saltLength);
        string storedHash = line.substr(usernameLength + User::saltLength, User::hashLength);

        if (storedUsername == username) {
            string hashedInput = picosha2::hash256_hex_string(storedSalt + password);
            return hashedInput == storedHash;
        }
    }

    return false;
}

int main() {
    cout << "Welcome! 1. Sign Up  2. Login  Choice: ";
    int choice;
    cin >> choice;

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (choice == 1) {
        if (userExists(username)) {
            cout << "Username already exists.\n";
        } else {
            User newUser(username, password);
            saveUserToFile(newUser);
            cout << "Signup successful!\n";
        }
    } else if (choice == 2) {
        if (login(username, password)) {
            cout << "Login successful!\n";
        } else {
            cout << "Login failed.\n";
        }
    }

    return 0;
}

