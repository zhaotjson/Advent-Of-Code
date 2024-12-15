#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>

using namespace std;





void parseInput(const string& inputFile, vector<pair<int, int>>& rules, vector<vector<int>>& updates) {
    ifstream input(inputFile);
    string line;
    bool parsingRules = true;

    while (getline(input, line)) {
        if (line.empty()) {
            parsingRules = false; 
            continue;
        }

        if (parsingRules) {

            size_t sep = line.find('|');
            int x = stoi(line.substr(0, sep));
            int y = stoi(line.substr(sep + 1));
            rules.emplace_back(x, y);
        } else {

            vector<int> update;
            stringstream ss(line);
            string page;
            while (getline(ss, page, ',')) {
                update.push_back(stoi(page));
            }
            updates.push_back(update);
        }
    }
}

bool isUpdateCorrect(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> pagePositions;


    for (int i = 0; i < update.size(); ++i) {
        pagePositions[update[i]] = i;
    }


    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;

        if (pagePositions.find(x) == pagePositions.end() || pagePositions.find(y) == pagePositions.end()) {
            continue;
        }


        if (pagePositions[x] > pagePositions[y]) {
            return false;
        }
    }

    return true;
}


vector<int> reorderUpdate(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, unordered_set<int>> graph;
    unordered_map<int, int> inDegree;           
    unordered_set<int> updatePages(update.begin(), update.end());


    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;


        if (updatePages.count(x) && updatePages.count(y)) {
            graph[x].insert(y);
            inDegree[y]++;
            inDegree[x];
        }
    }


    queue<int> q;
    for (const auto& [page, degree] : inDegree) {
        if (degree == 0) {
            q.push(page);
        }
    }

    vector<int> sortedOrder;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        sortedOrder.push_back(curr);

        for (int neighbor : graph[curr]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sortedOrder;
}


int findMiddlePage(const vector<int>& update) {
    int n = update.size();
    return update[n / 2];
}

int main() {
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;


    parseInput("day5.txt", rules, updates);

    int sumCorrect = 0;
    int sumReordered = 0;

    for (const auto& update : updates) {
        if (isUpdateCorrect(update, rules)) {

            sumCorrect += findMiddlePage(update);
        } else {

            vector<int> reorderedUpdate = reorderUpdate(update, rules);
            sumReordered += findMiddlePage(reorderedUpdate);
        }
    }

    cout << "Sum 1" << sumCorrect << endl;
    cout << "Sum 2" << sumReordered << endl;

    return 0;
}



// Part 1 Answer: 5166

// Part 2 Answer: 4579