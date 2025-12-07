#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    std::vector<std::string> lines;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    // insert beam
    for(int i=0; i<lines[0].size(); ++i) {
        if(lines[0][i] == 'S') {
            lines[1][i] = '|';
            break;
        }
    }

    long long split_count = 0;
    for (int i=1; i < lines.size()-1; ++i) {
        for (int j=0; j < lines[i].size();j++){
            if(lines[i][j] == '|'){
                if(lines[i+1][j] == '.'){
                    lines[i+1][j] = '|';
                } else if(lines[i+1][j] == '^'){
                    lines[i+1][j-1] = '|';
                    lines[i+1][j+1] = '|';
                    split_count++;
                }
            }
        }
    }
    std::cout << "Number of splits: " << split_count << std::endl;

    return 0;
}