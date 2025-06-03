#include <iostream>
#include <string>
#include <utility>
#include "passserver.h"

using namespace std;
using namespace cop4530;
void Menu();

int main() {
    size_t capacity;
    cout << "Enter preferred hash table capacity (integer): ";
    cin >> capacity;
	cout << capacity << endl;
    

    PassServer server(capacity);

    char choice;
    string filename, 
            username, 
            password, 
            newpassword;

    do {
        Menu();
        cin >> choice;
        cout << "choice: " << choice << endl;
        choice = tolower(choice); // Normalize input to lowercase

        switch (choice) {
            case 'l': {
                cout << "Enter password file name to load from: ";
                cin >> filename;
                if (server.load(filename.c_str())) {
                    cout << "File loaded successfully.\n";
                } else {
                    cout << "Failed to load file.\n";
                }
                break;
            }

            case 'a': {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (server.addUser({username, password})) {
                    cout << "\nUser " << username << " added.\n";
                } else  {
                    cout << "\n*****Error: User already exists. Could not add user.\n";
                }
                break;
            }

            case 'r': {
                cout << "Enter username: ";
                cin >> username;
                if (server.removeUser(username)) {
                    cout << "User " << username << " deleted.\n";
                } else {
                    cout << "\n*****Error: User not found. Could not delete user.\n";
                }
                break;
            }

            case 'c': {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter  password: ";
                cin >> password;
                cout << "\nEnter new password: ";
                cin >> newpassword;
                if (server.changePassword({username, password}, newpassword)) {
                    cout << "\nPassword changed for user " << username << ".\n";
                } else {
                    cout << "*****Error: Could not change user password.\n";
                }
                break;
            }

            case 'f': 
{
                cout << "Enter username: ";
                cin >> username;
                if (server.find(username)) {
                    cout << "\nUser '" << username << "' found.\n";
                } else {
                    cout << "\nUser '" << username << "' not found.\n";
                }
                break;
            }

            case 'd': {
                server.dump();
                break;
            }

            case 's': {
                cout << "Size of hashtable: " << server.size() << "\n";
                break;
            }

            case 'w': {
                cout << "Enter password file name to write to: ";
                cin >> filename;
                if (server.write_to_file(filename.c_str())) {
                    cout << "Data written successfully.\n";
                } else {
                    cout << "Failed to write to file.\n";
                }
                break;
            }

            case 'x': {
                cout << "Exiting program.\n";
                break;
            }

            default: {
                cout << "*****Error: Invalid entry.  Try again.\n";
            }
        }
    } while (choice != 'x');

    return 0;
}

void Menu() {
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}
