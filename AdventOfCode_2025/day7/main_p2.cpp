#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::map<std::pair<int, int>, long long> dp;
long long count_timelines(const std::vector<std::string>& matrix, int row, int col) {
    if (row >= matrix.size() - 1 || col < 0 || col >= matrix[0].size()) {
        return 1; 
    }
    

    auto key = std::make_pair(row, col);
    if (dp.find(key) != dp.end()) {
        return dp[key];
    }
    

    int next_row = row + 1;
    char next_cell = matrix[next_row][col];
    
    long long count = 0;
    
    if (next_cell == '.') {
        count = count_timelines(matrix, next_row, col);
    } else if (next_cell == '^') {
        long long left_count = count_timelines(matrix, next_row, col - 1);
        long long right_count = count_timelines(matrix, next_row, col + 1);
        count = left_count + right_count;
    }
    
    dp[key] = count;
    return count;
}
int main() {
    std::ifstream file("input.txt");
    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    
    for(int i = 0; i < lines[0].size(); ++i) {
        if(lines[0][i] == 'S') {
            long long result = count_timelines(lines, 0, i);
            std::cout << "Timeline Count: " << result << std::endl;
            break;
        }
    }
    
    return 0;
}