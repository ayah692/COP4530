#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

// Function Prototypes
void characters(map<char, pair<int, int>>& characterMap);
void words(map<string, pair<int, int>>& wordMap);
void numbers(map<string, pair<int, int>>& numberMap);

int main() {
    // Declare variables
    string word;
    string number;
    char character;

    // Maps to hold the characters, words, and numbers
    map<string, pair<int, int>> wordMap;     // words
    map<string, pair<int, int>> numberMap;   // numbers
    map<char, pair<int, int>> characterMap;  // characters

    while (cin.get(character)) { // Get characters until EOF
        if (isalpha(character)) { // If character is a letter
            word += tolower(character); // Add to word (convert to lowercase)
            // Process any previously encountered number
            if (!number.empty()) {
                ++numberMap[number].first; // Increment number count
                if (numberMap[number].first == 1) { // Update priority if new number
                    numberMap[number].second = numberMap.size();
                }
                number.clear(); // Reset number string
            }
        } else if (isdigit(character)) { // If character is a number
            number += character; // Add to number
            // Process any previously encountered word
            if (!word.empty()) {
                ++wordMap[word].first; // Increment word count
                if (wordMap[word].first == 1) { // Update priority if new word
                    wordMap[word].second = wordMap.size();
                }
                word.clear(); // Reset word string
            }
        } else { // If character is not alphanumeric
            // Process remaining word and number
            if (!word.empty()) {
                ++wordMap[word].first;
                if (wordMap[word].first == 1) {
                    wordMap[word].second = wordMap.size();
                }
                word.clear();
            }
            if (!number.empty()) {
                ++numberMap[number].first;
                if (numberMap[number].first == 1) {
                    numberMap[number].second = numberMap.size();
                }
                number.clear();
            }
        }
        ++characterMap[character].first; // Increment character count
        characterMap[character].second = (int)character; // Store ASCII value
    }

    // Final check for any remaining word or number
    if (!word.empty()) {
        ++wordMap[word].first;
        if (wordMap[word].first == 1) {
            wordMap[word].second = wordMap.size();
        }
    }
    if (!number.empty()) {
        ++numberMap[number].first;
        if (numberMap[number].first == 1) {
            numberMap[number].second = numberMap.size();
        }
    }

    // Call functions to display results
    words(wordMap);
    numbers(numberMap);
    characters(characterMap);

    return 0;
}

// Function to display top words
void words(map<string, pair<int, int>>& wordMap) {
    int numberOfWords = min((int)wordMap.size(), 10); // Get number of words to display
    cout << "\nThere are " << wordMap.size() << " Unique Words, The Top " << numberOfWords << " Words:\n";
    cout << "\nIndex       Item   Number    Priority\n";

    for (int i = 0; i < numberOfWords; i++) {
        auto best = wordMap.begin(); // Initialize best iterator
        for (auto it = wordMap.begin(); it != wordMap.end(); it++) {
            if (best->second.first < it->second.first || 
               (best->second.first == it->second.first && it->second.second < best->second.second)) {
                best = it; // Update best if current is better
            }
        }
        cout << "[  " << i << "] " << setw(12) << best->first << setw(5) << best->second.first << setw(12) << best->second.second << endl;
        wordMap.erase(best); // Erase max value
    }
}

// Function to display top numbers
void numbers(map<string, pair<int, int>>& numberMap) {
    int numberOfNumbers = min((int)numberMap.size(), 10); // Get number of numbers to display
    cout << "\nThere are " << numberMap.size() << " Unique Numbers, The Top " << numberOfNumbers << " Numbers:\n";
    cout << "\nIndex       Item   Number    Priority\n";

    for (int i = 0; i < numberOfNumbers; i++) {
        auto best = numberMap.begin();
        for (auto it = numberMap.begin(); it != numberMap.end(); it++) {
            if (best->second.first < it->second.first || 
               (best->second.first == it->second.first && it->second.second < best->second.second)) {
                best = it; // Update best if current is better
            }
        }
        cout << "[  " << i << "] " << setw(12) << best->first << setw(5) << best->second.first << setw(12) << best->second.second << endl;
        numberMap.erase(best); // Erase max value
    }
}

// Function to display top characters
void characters(map<char, pair<int, int>>& characterMap) {
    int numberOfCharacters = min((int)characterMap.size(), 10); // Get number of characters to display
    cout << "\nThere are " << characterMap.size() << " Unique Characters, The Top " << numberOfCharacters << " Characters:\n";
    cout << "\nIndex       Item   Number    Priority\n";

    for (int i = 0; i < numberOfCharacters; i++) {
        auto best = characterMap.begin();
        for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
            if (best->second.first < it->second.first || 
               (best->second.first == it->second.first && it->second.second < best->second.second)) {
                best = it; // Update best if current is better
            }
        }
        string displayChar = (best->first == '\n') ? "Newline" : 
                             (best->first == '\t') ? "Tab" : 
                             (best->first == ' ') ? "Space" : string(1, best->first);
        cout << "[  " << i << "] " << setw(12) << displayChar << setw(5) << best->second.first << setw(12) << best->second.second << endl;
        characterMap.erase(best); // Erase max value
    }
}
