#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isSafe(const vector<int>& line) {
    if (line.size() == 1) {
        return true;
    }

    if (line.size() < 1) {
        return false;
    }

    int firstVal = line[0];
    int secondVal = line[1];


    if (firstVal > secondVal) {
        for (int i = 0; i < line.size() - 1; i++) {
            int nextVal = line[i + 1];
            int thisVal = line[i];
            if (thisVal - nextVal < 1 || thisVal - nextVal > 3) {
                return false;
            }
        }
        return true;
    } else if (secondVal > firstVal) {
        for (int i = 0; i < line.size() - 1; i++) {
            int nextVal = line[i + 1];
            int thisVal = line[i];
            if (nextVal - thisVal < 1 || nextVal - thisVal > 3) {
                return false;
            }
        }
        return true;
    }
    return false;
}




bool qualifies(const vector<int>& line) {
    if (isSafe(line)) {
        return true;
    }

    for (size_t i = 0; i < line.size(); i++) {
        vector<int> modifiedLine = line;
        modifiedLine.erase(modifiedLine.begin() + i);
        if (isSafe(modifiedLine)) {
            return true; 
        }
    }

    return false;
}



int main() {
    string line;
    int safeCounter = 0;


    ifstream inputFile("day2.txt"); 
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file 'day2.txt'." << endl;
        return 1;
    }


    while (getline(inputFile, line)) {

        istringstream iss(line);
        vector<int> numbers;
        int num;


        while (iss >> num) {
            numbers.push_back(num);
        }


        if (qualifies(numbers)) {
            safeCounter++;
        }
    }

    inputFile.close();



    cout << "Number of safe reports: " << safeCounter << endl;

    return 0;
}



//Part 1 Answer: 510
//Part 2 Answer: 553