#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <unordered_map> 

using namespace std;

int main() {
    vector<int> list1, list2;
    string line;


    ifstream inputFile("day1.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file 'day1.txt'." << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        istringstream iss(line);
        int num1, num2;
        if (iss >> num1 >> num2) {
            list1.push_back(num1);
            list2.push_back(num2);
        } else {
            cerr << "Invalid line: " << line << endl;
        }
    }

    inputFile.close();





    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());



    int sum_of_differences = 0;
    for (size_t i = 0; i < list1.size(); ++i) {
        sum_of_differences += abs(list1[i] - list2[i]);
    }




    unordered_map<int, int> list2_occurrences;
    for (int num : list2) {
        list2_occurrences[num]++;
    }



    int similarity_score = 0;
    for (int num : list1) {
        if (list2_occurrences.find(num) != list2_occurrences.end()) {
            similarity_score += num * list2_occurrences[num];
        }
    }



    cout << "Sum of differences: " << sum_of_differences << endl;
    cout << "Similarity score: " << similarity_score << endl;

    return 0;
}

//Part 1 Answer: 2756096

//Part 2 Answer: 23117829

