#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::vector<std::pair<long long, long long>> ranges;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            if (token.empty()) continue; // skip empty entries

            size_t dashPos = token.find('-');
            if (dashPos == std::string::npos) continue; // invalid entry

            long long first = std::stoll(token.substr(0, dashPos));
            long long second = std::stoll(token.substr(dashPos + 1));

            ranges.emplace_back(first, second);
        }
    }
    long long sum=0;
    for (auto &p : ranges) {
        std::cout << p.first << " - " << p.second << "\n";
        for (long long i=p.first; i<(p.second + 1); i++){
            std::string str = std::to_string(i);
            long long lenght = str.length();
            // std:: cout << "len is: " << lenght << std::endl;
            long long part_cursor = lenght/2;
            while(part_cursor>0){
                if(lenght % part_cursor != 0){
                    // std::cout << "part cursor: " << part_cursor << " is not a divider for "<< length << std::endl;
                    part_cursor--;
                    continue;
                }
                // std::cout << "Checking for part cursor: " << part_cursor << std::endl;
                bool is_repeated = true;
                std::string part = str.substr(0, part_cursor);
                for (long long j=part_cursor; j<lenght; j+=part_cursor){
                    std::string next_part = str.substr(j, part_cursor);
                    if(part != next_part){
                        is_repeated = false;
                        break;
                    }
                }

                if(is_repeated){
                    std::cout << "Adding " << str << " to sum" << std::endl;
                    sum += std::stoll(str);
                    break;
                }
                part_cursor--;
                
            }
               
        }
    }
    std::cout << "Sum is: "<< sum << std::endl;

    return 0;
}
