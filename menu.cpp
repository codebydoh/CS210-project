#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Function prototype (declaration)
vector<string> split_string(string str, string delimiter);

// Class for word frequency counting and data saving
class WordFrequencyCounter {
public:
    // Constructor to initialize the object
    WordFrequencyCounter(const string& inputFile) : inputFile_(inputFile) {}

    // Function to calculate word frequencies
    void calculateFrequencies() {
        ifstream input_file(inputFile_);
        if (!input_file) {
            cerr << "Error: Could not open input file" << endl;
            exit(1);
        }

        string line;
        while (getline(input_file, line)) {
            // Split the line into words.
            vector<string> words = split_string(line, " ");

            // Increment the frequency of each word.
            for (string word : words) {
                word_frequencies_[word]++;
            }
        }
        input_file.close();
    }

    // Function to save word frequencies to a data file
    void saveToDataFile(const string& outputFile) {
        ofstream dataFile(outputFile);
        if (!dataFile) {
            cerr << "Error: Could not create data file" << endl;
            exit(1);
        }

        for (const auto& pair : word_frequencies_) {
            dataFile << pair.first << " " << pair.second << endl;
        }
        dataFile.close();
    }

private:
    string inputFile_;
    map<string, int> word_frequencies_;
};

int main() {
    // Create an instance of WordFrequencyCounter
    WordFrequencyCounter frequencyCounter("CS210_Project_Three_Input_File.txt");

    // Calculate word frequencies
    frequencyCounter.calculateFrequencies();

    // Save word frequencies to a data file
    frequencyCounter.saveToDataFile("frequency.dat");

    // Initialize the choice variable.
    int choice;

    while (true) {
        // Print the menu options.
        cout << "\nSelect an option:" << endl;
        cout << "1. Find the frequency of a word." << endl;
        cout << "2. Print the frequency list." << endl;
        cout << "3. Print the frequency histogram." << endl;
        cout << "4. Exit" << endl;

        // Get the user's choice.
        cin >> choice;

        // Process the user's choice.
        switch (choice) {
            case 1: {
                // Prompt the user for the word.
                string word;
                cout << "Enter the word: ";
                cin >> word;

                // Print the frequency of the word.
                cout << "The frequency of " << word << " is " << frequencyCounter[word] << endl;
                break;
            }
            case 2: {
                // Print the frequency list.
                for (auto iter : frequencyCounter) {
                    cout << iter.first << " - " << iter.second << endl;
                }
                break;
            }
            case 3: {
                // Print the frequency histogram.
                for (auto iter : frequencyCounter) {
                    cout << iter.first << ": ";
                    for (int i = 0; i < iter.second; i++) {
                        cout << "*";
                    }
                    cout << endl;
                }
                break;
            }
            case 4: {
                cout << "Exiting program..." << endl;
                return 0; // Exit the program
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}

// Split a string into words.
vector<string> split_string(string str, string delimiter) {
    vector<string> words;

    // Split the string on the delimiter.
    size_t pos = 0;
    while (pos != string::npos) {
        size_t next_pos = str.find(delimiter, pos);

        // If the delimiter was not found, add the rest of the string as a word.
        if (next_pos == string::npos) {
            words.push_back(str.substr(pos));
            break;
        } else {
            words.push_back(str.substr(pos, next_pos - pos));
            pos = next_pos + delimiter.length();
        }
    }

    return words;
}
