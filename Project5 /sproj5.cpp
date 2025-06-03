#include "passserver.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;
using namespace cop4530;

void Menu();
void hideInput(string &input);

int main() {
    size_t capacity;
    cout << "Enter preferred hash table capacity (integer): ";
    cin >> capacity;
    cout << capacity << endl;

    PassServer server(capacity);
    char choice;
    string username, password, newpassword;
    string filename;

    do {
        Menu();
        cin >> choice;
	cout << "choice: " << choice << endl;
        choice = tolower(choice);

        switch (choice) {
            case 'l':
                cout << "Enter password file name to load from: ";
                cin >> filename;
                if (server.load(filename.c_str())) {
                    cout << "Loaded successfully." << endl;
                } else {
                    cout << "*****Error: Could not load file." << endl;
                }
                break;
            case 'a':
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                hideInput(password);
                if (server.addUser({username, password})) {
                    cout << "User " << username << " added." << endl;
                } else {
                    cout << "*****Error: User already exists. Could not add user." << endl;
                }
                break;
            case 'r':
                cout << "Enter username: ";
                cin >> username;
                if (server.removeUser(username)) {
                    cout << "User " << username << " deleted." << endl;
                } else {
                    cout << "*****Error: User not found. Could not delete user." << endl;
                }
                break;
            case 'c':
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                hideInput(password);
                cout << "Enter new password: ";
                hideInput(newpassword);
                if (server.changePassword({username, password}, newpassword)) {
                    cout << "Password changed for user " << username << endl;
                } else {
                    cout << "*****Error: Could not change user password" << endl;
                }
                break;
            case 'f':
                cout << "Enter username: ";
                cin >> username;
                if (server.find(username)) {
                    cout << "\nUser '" << username << "' found." << endl;
                } else {
                    cout << "\nUser '" << username << "' not found." << endl;
                }
                break;
            case 'd':
                server.dump();
                break;
            case 's':
                cout << "Size of hashtable: " << server.size() << endl;
                break;
            case 'w':
                cout << "Enter password file name to write to: ";
                cin >> filename;
                if (server.write_to_file(filename.c_str())) {
                    cout << "Data written to file successfully." << endl;
                } else {
                    cout << "*****Error: Could not write to file." << endl;
                }
                break;
            case 'x':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "*****Error: Invalid entry.  Try again." << endl;
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

void hideInput(string &input) {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~ECHO;          // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply settings

    cin >> input;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    cout << endl;
}
