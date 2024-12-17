#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <fstream>
#include <string>
#include <numeric>
using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};


vector<vector<char>> readMapFromFile(const string& filename);
vector<vector<char>> createAntinodeMap(const vector<vector<char>>& originalMap);
void printMap(const vector<vector<char>>& map);
bool isValidAntinode(int x, int y, const vector<vector<char>>& map);


vector<vector<char>> readMapFromFile(const string& filename) {
    vector<vector<char>> map;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }
    return map;
}

vector<vector<char>> createAntinodeMap(const vector<vector<char>>& originalMap) {
    if (originalMap.empty()) return vector<vector<char>>();
    return vector<vector<char>>(originalMap.size(), vector<char>(originalMap[0].size(), '.'));
}

void printMap(const vector<vector<char>>& map) {
    for (const auto& row : map) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

bool isValidAntinode(int x, int y, const vector<vector<char>>& map) {
    return x >= 0 && x < map[0].size() && y >= 0 && y < map.size();
}

void findAntinodes(const vector<vector<char>>& map, vector<vector<char>>& antinodeMap) {

    std::map<char, std::vector<Point>> frequencies;
    

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            char c = map[y][x];
            if (isalnum(c)) {
                frequencies[c].push_back(Point(x, y));
            }
        }
    }
    

    for (const auto& freq_pair : frequencies) {
        const vector<Point>& positions = freq_pair.second;
        

        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i + 1; j < positions.size(); j++) {
                Point a1 = positions[i];
                Point a2 = positions[j];
                

                int dx = a2.x - a1.x;
                int dy = a2.y - a1.y;
                

                int gcd = std::gcd(abs(dx), abs(dy));
                if (gcd > 0) {
                    dx /= gcd;
                    dy /= gcd;
                }
                

                int x = a1.x;
                int y = a1.y;

                
                while (isValidAntinode(x, y, map)) {

                    

                    antinodeMap[y][x] = '#';

                    
                    x += dx;
                    y += dy;

                }
                
                x = a1.x - dx;
                y = a1.y - dy;
                
                while (isValidAntinode(x, y, map)) {

                    

                    antinodeMap[y][x] = '#';
                    
                    
                    x -= dx;
                    y -= dy;


                }
            }
        }
    }
}




int countAntinodes(const vector<vector<char>>& antinodeMap) {
    int count = 0;
    for (const auto& row : antinodeMap) {
        for (char c : row) {
            if (c == '#') count++;
        }
    }
    return count;
}

int main() {
    vector<vector<char>> map = readMapFromFile("day8.txt");
    
    if (map.empty()) {
        cerr << "No data found in file" << endl;
        return 1;
    }
    
    vector<vector<char>> antinodeMap = createAntinodeMap(map);
    findAntinodes(map, antinodeMap);
    
    cout << "Original map:" << endl;
    printMap(map);
    cout << "\nAntinode map:" << endl;
    printMap(antinodeMap);
    cout << "\nTotal antinodes: " << countAntinodes(antinodeMap) << endl;
    
    return 0;
}



// Part 1 Answer: 299

// Part 2 Answer: 1032

