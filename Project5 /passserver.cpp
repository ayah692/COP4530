#include "passserver.h"
#include <iostream>
using namespace std;
using namespace cop4530;

// Constructor
PassServer::PassServer(size_t size) 
        : table(size) {}

// Destructor
PassServer::~PassServer() {
    table.clear();
}

// Load username and password pairs from a file
bool PassServer::load(const char *filename) {
    return table.load(filename);
}

// Add a new user (encrypt password before insertion)
bool PassServer::addUser(std::pair<std::string, std::string> &kv) {
    kv.second = encrypt(kv.second);
    if (table.contains(kv.first)) {
        return false; // User already exists
    }
    return table.insert(kv); // Insert the new username and password
}

// Move version of addUser
bool PassServer::addUser(std::pair<std::string, std::string> &&kv) {
    kv.second = encrypt(kv.second);
    if (table.contains(kv.first)) {
        return false; // User already exists
    }
    return table.insert(std::move(kv)); // Insert the new username and password
}

// Remove an existing user
bool PassServer::removeUser(const std::string &k) {
    return table.remove(k);
}

// Change an existing user's password
bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword) {
    // Encrypt the current password to match it against the stored password
    std::string encrypted_current_password = encrypt(p.second);
    std::pair<std::string, std::string> encrypted_pair = {p.first, encrypted_current_password};

    // Check if the current username and encrypted password match an entry in the table
    if (!table.match(encrypted_pair)) {
         // Debug statement
        return false;
    }

    // Check if the new password is the same as the old password
    if (p.second == newpassword) {
        //cout << "*****Error: New password cannot be the same as the old password." << endl; // Debug statement
        return false;
    }

    // Encrypt the new password
    std::string encrypted_newpassword = encrypt(newpassword);
  // Update the password in the hash table
    table.remove(p.first);
    std::pair<std::string, std::string> new_entry = {p.first, encrypted_newpassword};
    return table.insert(new_entry);
}

// Find if a user exists
bool PassServer::find(const std::string &user) const {
    return table.contains(user);
}

// Display the structure and content of the hash table
void PassServer::dump() const {
    table.dump();
}

// Return the number of users in the hash table
size_t PassServer::size() const {
    return table.size();
}

// Save the username and encrypted password pairs to a file
bool PassServer::write_to_file(const char *filename) const {
    return table.write_to_file(filename);
}

// Encrypt the given password using MD5-based crypt() with a fixed salt
std::string PassServer::encrypt(const std::string & str) {
    const char *salt = "$1$########";
    char *encrypted = crypt(str.c_str(), salt);
    std::string encrypted_str(encrypted);
    size_t pos = encrypted_str.find('$', encrypted_str.find('$', encrypted_str.find('$') + 1) + 1);
    return encrypted_str.substr(pos + 1);
}
 // namespace cop4530
