#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


bool searchXMAS(const vector< vector<char> >& charArray, int row, int col, int rowDir, int colDir) {
    string target = "XMAS";
    int nRows = charArray.size();
    int nCols = charArray[0].size();

    for (int i = 0; i < target.length(); i++) {
        int newRow = row + i * rowDir;  
        int newCol = col + i * colDir; 


        if (newRow < 0 || newRow >= nRows || newCol < 0 || newCol >= nCols) {
            return false;
        }


        if (charArray[newRow][newCol] != target[i]) {
            return false;
        }
    }
    return true; 
}


bool searchX_MAS(const vector< vector<char> >& charArray, int row, int col){
    int nRows = charArray.size();
    int nCols = charArray[0].size();

    if (row == 0 || col == 0 || row == nRows - 1 || col == nCols - 1) {
        return false;
    }

    if(charArray[row - 1][col - 1] == 'M' && charArray[row + 1][col + 1] == 'S'){

        if(charArray[row + 1][col - 1] == 'M' && charArray[row - 1][col + 1] == 'S'){
            return true;
        }
        else if(charArray[row + 1][col - 1] == 'S' && charArray[row - 1][col + 1] == 'M'){
            return true;
        }
    }
    else if(charArray[row - 1][col - 1] == 'S' && charArray[row + 1][col + 1] == 'M'){

        if(charArray[row + 1][col - 1] == 'M' && charArray[row - 1][col + 1] == 'S'){
            return true;
        }
        else if(charArray[row + 1][col - 1] == 'S' && charArray[row - 1][col + 1] == 'M'){
            return true;
        }
    }
    
    return false;


}



int main() {
    ifstream inputFile("day4.txt");
    if (!inputFile) {
        cerr << "Error: Could not open file day4.txt" << endl;
        return 1; 
    }


    vector< vector<char> > charArray;
    string line;

    while (getline(inputFile, line)) {
        vector<char> row;
        for (char ch : line) {

            row.push_back(ch);

        }
        if (!row.empty()) {
            charArray.push_back(row);
        }
    }
    inputFile.close();

    int count = 0;  
    int nRows = charArray.size();
    int nCols = charArray.empty() ? 0 : charArray[0].size();


    vector< pair<int, int> > directions = {
        {-1, 0}, 
        {1, 0},   
        {0, -1},  
        {0, 1},   
        {-1, -1},
        {-1, 1},  
        {1, -1},  
        {1, 1}    
    };


    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            if (charArray[row][col] == 'X') { 
                for (const auto& dir : directions) {
                    if (searchXMAS(charArray, row, col, dir.first, dir.second)) {
                        count++;
                    }
                }
            }
        }
    }

    cout << "XMAS Found " << count << endl;





    //Part Two

    int X_MasCount = 0;

    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            if (charArray[row][col] == 'A') { 

                if (searchX_MAS(charArray, row, col)) {
                    X_MasCount++;
                }
            }
        }
    }


    cout << "X-MAS Found " << X_MasCount << endl;

    return 0;
}



//Part 1 Answer: 2358

//Part 2 Answer: 1737


