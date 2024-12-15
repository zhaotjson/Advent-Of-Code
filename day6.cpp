#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


//Constants for directions
const int up = 0;
const int rightD = 1;
const int down = 2;
const int leftD = 3;



vector<vector<char>> read2DArrayFromFile(const string& filename) {
    ifstream inputFile(filename);
    vector<vector<char>> charArray;

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return charArray;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<char> row;
        for (char c : line) {
                row.push_back(c);

        }
        if (!row.empty()) {
            charArray.push_back(row);
        }
    }

    inputFile.close();
    return charArray;
}

void print2DArray(const vector<vector<char>>& charArray) {
    for (const auto& row : charArray) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}



pair<int, int> locateChar(const vector<vector<char>>& charArray) {
    for (int row = 0; row < charArray.size(); ++row) {
        for (int col = 0; col < charArray[row].size(); ++col) {
            if (charArray[row][col] == '^') {
                return make_pair(row, col);
            }
        }
    }

    return make_pair(-1, -1);
}




void parseAndReplace(vector<vector<char>>& charArray, pair<int, int> startCoord, int direction) {
    int row = startCoord.first;
    int col = startCoord.second;

    while(true) {
        switch (direction) {
            case up: // Up
                if (row - 1 >= 0 && charArray[row - 1][col] == '#') {
                    direction = (direction + 1) % 4;
                    continue;
                }
                break;
            case rightD: // Right
                if (col + 1 < charArray[row].size() && charArray[row][col + 1] == '#') {
                    direction = (direction + 1) % 4;
                    continue;
                }
                break;
            case down: // Down
                if (row + 1 < charArray.size() && charArray[row + 1][col] == '#') {
                    direction = (direction + 1) % 4;
                    continue;
                }
                break;
            case leftD: // Left
                if (col - 1 >= 0 && charArray[row][col - 1] == '#') {
                    direction = (direction + 1) % 4;
                    continue;
                }
                break;
            default:
                cerr << "Invalid direction" << endl;
                return;
        }

        charArray[row][col] = 'X';

        switch (direction) {
            case up: // Up
                row--;
                break;
            case rightD: // Right
                col++;
                break;
            case down: // Down
                row++;
                break;
            case leftD: // Left
                col--;
                break;
            default:
                cerr << "Invalid direction" << endl;
                return;
        }

        if (row < 0 || row >= charArray.size() || col < 0 || col >= charArray[row].size()) {
            cerr << "Out of bounds" << endl;
            return;
        }
    }
}

int numX(const vector<vector<char>>& charArray) {
    int count = 0;
    for (const auto& row : charArray) {
        for (char c : row) {
            if (c == 'X') {
                count++;
            }
        }
    }
    return count;
}




int main() {

    int currDirec = 0;



    string filename = "day6.txt";


    vector<vector<char>> charArray = read2DArrayFromFile(filename);


    if (charArray.empty()) {
        cerr << "Error: No data found in file or file format is incorrect." << endl;
        return 1;
    }




    pair<int, int> currCoord = locateChar(charArray);


    parseAndReplace(charArray, currCoord, currDirec);

    print2DArray(charArray);


    cout << numX(charArray) << endl;


    return 0;
}



// Part 1 Answer: 5564

// Part 2 Answer: