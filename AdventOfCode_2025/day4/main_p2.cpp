#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<char>> readGridFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<char>> grid;
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return grid;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    file.close();
    return grid;
}
int paper_remover(std::vector<std::vector<char>>& table) {
    int removed_count = 0;
    int row_count = table.size();
    int col_count = table[0].size();
    for (int r = 0; r < row_count; ++r) {
        for (int c = 0; c < col_count; ++c) {
            if (table[r][c] != '@') continue;
            int neigbour_count = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if(i == 0 && j == 0) continue;
                    if(r + i < 0 || r + i >= row_count || c + j < 0 || c + j >= col_count) continue; // boundry or seg fault
                    if (table[r + i][c + j] == '@') ++neigbour_count;
                }
            }
            if (neigbour_count < 4){
                table[r][c] = '.';
                removed_count++;
            }
        }
    }
    return removed_count;
}
int main() {
    std::string filename = "input.txt";
    std::vector<std::vector<char>> table = readGridFromFile(filename);
    long long remove_count = 0;
    bool is_removing = true;
    while (is_removing) {
        int current_removed = paper_remover(table);
        if (current_removed > 0) {
            remove_count += current_removed;
        } else {
            is_removing = false;
        }
    }
    std::cout << "Total paper removed: " << remove_count << std::endl;



    return 0;
}