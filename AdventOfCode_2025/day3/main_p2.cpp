#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    std::vector<std::string> lines;
    std::string line;

    if (!file) {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    long long sum = 0;
    for (auto s : lines) {
        std::vector<int> max_numerals;
        int last_loc=0;
        for (int i=0;i<12;i++){
            std::string temp_string = s.substr(last_loc);
            int current_max = 0;
            int max_pos = last_loc;
            for (int j=0; j<temp_string.length()-11+i;j++){
                int current_value = temp_string[j]- '0';
                if(current_value>current_max){
                    current_max = current_value;
                    max_pos = last_loc + j;
                }
            }
            last_loc = max_pos+1;
            max_numerals.push_back(current_max);
        }
        long long line_max =0;
        for (int d : max_numerals){
            line_max = line_max*10 +d;
        }
        std::cout << "Adding to sum : " << line_max << std::endl;
        sum+= line_max;
    }

    std::cout << "Sum is: " << sum << std::endl;

    return 0;
}
