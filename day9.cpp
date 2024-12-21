#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct FileBlock {
    int id;
    int length;
    int spaceAfter;
};

string processDiskMap(const string& input) {
    vector<FileBlock> files;
    string result;
    int currentId = 0;
    
    // Process pairs of numbers (file length and space after)
    for (size_t i = 0; i < input.length(); i++) {
        int fileLength = input[i] - '0';
        int spaceLength = 0;
        
        if (i + 1 < input.length()) {
            spaceLength = input[i + 1] - '0';
            i++; // Skip space length in next iteration
        }
        
        files.push_back({currentId, fileLength, spaceLength});
        currentId++;
    }
    
    // Create disk map representation
    for (const auto& file : files) {
        // Add file blocks
        for (int i = 0; i < file.length; i++) {
            result += to_string(file.id);
        }
        // Add free space
        for (int i = 0; i < file.spaceAfter; i++) {
            result += '.';
        }
    }
    
    return result;
}




vector<string> simulateFileMovement(const string& initialMap) {
    vector<string> steps;
    string currentMap = initialMap;
    steps.push_back(currentMap);
    
    bool moved;
    bool terminalPositionFound = false;
    
    do {
        moved = false;
        // Find rightmost file block
        for (int i = currentMap.length() - 1; i >= 0 && !terminalPositionFound; i--) {
            if (isdigit(currentMap[i])) {
                // Find leftmost free space
                for (int j = 0; j < i; j++) {
                    if (currentMap[j] == '.') {
                        cout << "i: " << i << " j: " << j << endl;
                        bool hasDigitBefore = false;
                        for (int k = 0; k < j; k++) {
                            if (isdigit(currentMap[k])) {
                                hasDigitBefore = true;
                                break;
                            }
                        }
                        
                        // If no digits before this position, we've found a terminal state
                        if (!hasDigitBefore) {
                            terminalPositionFound = true;
                            moved = false;
                            break;
                        }
                        
                        // Valid move found
                        currentMap[j] = currentMap[i];
                        currentMap[i] = '.';
                        moved = true;
                        cout << "Moved" << endl;
                        steps.push_back(currentMap);
                        break;
                    }
                }
                if (terminalPositionFound) break;
            }
        }

        cout << moved << endl;
    } while (moved && !terminalPositionFound);
    
    return steps;
}

long long calculateChecksum(const string& finalMap) {
    long long checksum = 0;
    
    for (size_t i = 0; i < finalMap.length(); i++) {
        if (isdigit(finalMap[i])) {
            checksum += i * (finalMap[i] - '0');
        }
    }
    
    return checksum;
}



string readInputFromFile(const string& filename) {
    ifstream file(filename);
    string input;
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }
    
    getline(file, input);
    file.close();
    
    return input;
}



int main() {
    string filename = "day9.txt";
    cout << "Reading input file..." << endl;
    string input = readInputFromFile(filename);
    
    if (input.empty()) {
        cerr << "No data found in file" << endl;
        return 1;
    }
    cout << "Input read: " << input << endl;
    
    cout << "Processing disk map..." << endl;
    string initialMap = processDiskMap(input);
    cout << "Initial map: " << initialMap << endl;
    
    cout << "Simulating file movement..." << endl;
    vector<string> steps = simulateFileMovement(initialMap);
    cout << "Final map: " << steps.back() << endl;
    
    cout << "Calculating checksum..." << endl;
    long long checksum = calculateChecksum(steps.back());
    cout << "Final checksum: " << checksum << endl;
    
    return 0;
}
