#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 

using namespace std;


bool isValidNumber(const string& str) {
    if (str.empty()) return false;


    if (str.length() > 3) return false;

    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

int main() {
    string input;
    int totalSum = 0;
    bool mul = true;


    ifstream inputFile("day3.txt");

    if (!inputFile) {
        cerr << "Error: Could not open the file day3.txt!" << endl;
        return 1;
    }


    while (getline(inputFile, input)) {
        size_t length = input.length();
        size_t i = 0; 

        while (i < length) {

            if (i + 4 < length && input.substr(i, 4) == "do()") {
                mul = true;
                i += 4;
            } 

            else if (i + 7 < length && input.substr(i, 7) == "don't()") {
                mul = false;

                i += 7; 
            }

            else if (i + 3 < length && input[i] == 'm' && input[i+1] == 'u' && input[i+2] == 'l' && input[i+3] == '(') {

                i += 4; 


                size_t start = i;
                while (i < length && isdigit(input[i])) {
                    i++;
                }
                string num1_str = input.substr(start, i - start);


                if (!isValidNumber(num1_str)) {
                    i++;
                    continue;
                }


                if (i < length && input[i] == ',') {
                    i++; 


                    start = i;
                    while (i < length && isdigit(input[i])) {
                        i++;
                    }
                    string num2_str = input.substr(start, i - start);


                    if (!isValidNumber(num2_str)) {
                        continue;
                    }


                    if (i < length && input[i] == ')') {
                        i++;


                        if (mul) {

                            int num1 = stoi(num1_str);
                            int num2 = stoi(num2_str);
                            totalSum += num1 * num2;
                        }
                    } else {
                        continue; 
                    }
                } else {
                    continue;
                }
            } else {
                i++; 
            }
        }
    }


    inputFile.close();


    cout << "Total sum of products: " << totalSum << endl;

    return 0;
}




//Part 1 Answer: 185797128
//Part 2 Answer:  89798695

