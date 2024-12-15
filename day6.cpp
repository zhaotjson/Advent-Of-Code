#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;


//Constants for directions
const int up = 0;
const int rightD = 1;
const int down = 2;
const int leftD = 3;



void resetArray(vector<vector<char>>& charArray) {
    for (int r = 0; r < charArray.size(); r++) {
        for (int c = 0; c < charArray[0].size(); c++) {
            if (charArray[r][c] == '^' || charArray[r][c] == '>' || 
                charArray[r][c] == 'v' || charArray[r][c] == '<' || charArray[r][c] == 'X') {
                charArray[r][c] = '.';
            }
        }
    }
}


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







//Part 2

char getDirectionChar(int direction) {
    switch(direction) {
        case up: return '^';
        case rightD: return '>';
        case down: return 'v';
        case leftD: return '<';
        default: return '.';
    }
}
bool parseWithDirectionalMarks(vector<vector<char>>& charArray, pair<int, int> startCoord) {
    int row = startCoord.first;
    int col = startCoord.second;
    int direction = up;
    int turnsInPlace = 0;
    int steps = 0;
    const int MAX_STEPS = 10000000;

    while (steps < MAX_STEPS) {
        steps++;
        

        charArray[row][col] = getDirectionChar(direction);


        int nextRow = row;
        int nextCol = col;
        switch (direction) {
            case up: nextRow--; break;
            case rightD: nextCol++; break;
            case down: nextRow++; break;
            case leftD: nextCol--; break;
        }


        if (nextRow < 0 || nextRow >= charArray.size() || 
            nextCol < 0 || nextCol >= charArray[0].size()) {
            return false;
        }


        if (charArray[nextRow][nextCol] == getDirectionChar(direction)) {
            return true;
        }


        if (charArray[nextRow][nextCol] == '#') {
            direction = (direction + 1) % 4;
            turnsInPlace++;
            if (turnsInPlace >= 4) {
                return false;
            }
            continue;
        }

        turnsInPlace = 0;
        row = nextRow;
        col = nextCol;
    }
    
    cout << "Max steps reached at position (" << row << "," << col << ")" << endl;
    return true; 
}

int findValidObstacles(vector<vector<char>>& charArray, pair<int, int> startCoord) {
    int count = 0;
    for (int r = 0; r < charArray.size(); r++) {
        for (int c = 0; c < charArray[0].size(); c++) {
            if (charArray[r][c] == '.' && (r != startCoord.first || c != startCoord.second)) {
                resetArray(charArray);
                vector<vector<char>> testArray = charArray;
                testArray[r][c] = '#';
                if (parseWithDirectionalMarks(testArray, startCoord)) {
                    count++;
                }
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

    //print2DArray(charArray);


    cout << numX(charArray) << endl;

    resetArray(charArray);

    cout << findValidObstacles(charArray, currCoord) << endl;


    return 0;
}



// Part 1 Answer: 5564

// Part 2 Answer: 1976
