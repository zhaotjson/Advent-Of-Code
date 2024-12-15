#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

pair<vector<long long>, vector<vector<long long>>> processInput(const string& filename) {
    vector<long long> testValues;
    vector<vector<long long>> values;
    
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;
     

        long long testValue = stoll(line.substr(0, colonPos));
        testValues.push_back(testValue);
        
        vector<long long> lineValues;
        stringstream ss(line.substr(colonPos + 1));
        long long value;
        while (ss >> value) {
            lineValues.push_back(value);
        }
        values.push_back(lineValues);
    }
    
    return {testValues, values};
}

bool findCombinationHelper(long long target, const vector<long long>& nums, size_t index, long long runningTotal) {
    if (index >= nums.size()) {
        return runningTotal == target;
    }
    

    if (findCombinationHelper(target, nums, index + 1, runningTotal + nums[index])) {
        return true;
    }
    

    if (findCombinationHelper(target, nums, index + 1, runningTotal * nums[index])) {
        return true;
    }
    

    string concatStr = to_string(runningTotal) + to_string(nums[index]);
    long long concatNum;
    try {
        concatNum = stoll(concatStr);
        if (findCombinationHelper(target, nums, index + 1, concatNum)) {
            return true;
        }
    } catch (const out_of_range&) {
        
    }
    
    return false;
}

bool findCombination(long long target, const vector<long long>& nums) {
    if (nums.empty()) return false;
    return findCombinationHelper(target, nums, 1, nums[0]);
}


int main() {
    auto [testValues, values] = processInput("day7.txt");
    
    long long sum = 0;
    
    for (size_t i = 0; i < testValues.size(); i++) {
        bool possible = findCombination(testValues[i], values[i]);
        // cout << testValues[i] << ": " << (possible ? "Possible" : "Impossible") << endl;
        
        if (possible) {
            sum += testValues[i];
        }
    }
    
    cout << "\nSum of possible test values: " << sum << endl;
    
    return 0;
}





// Part 1 Answer: 975671981569

// Part 2 Answer: 223472064194845