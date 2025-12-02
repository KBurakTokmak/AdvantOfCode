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
        std::cout<< "Diff is: "<< p.second - p.first<<std::endl;
        for (long long i=p.first; i<(p.second + 1); i++){
            std::string str = std::to_string(i);
            long long lenght = str.length();
            // std:: cout << "len is: " << lenght << std::endl;
            if (str.length() % 2 == 0){
                std::string part1 = str.substr(0,lenght/2);
                std::string part2 = str.substr((lenght/2),lenght-1);
                // std::cout << "part1 :" << part1 << " part2: " << part2 << std::endl;
                if (part1==part2){
                    sum+= std::stoll(str);
                    std::cout << "Adding " << str << " to sum" << std::endl;
                }
            }
        }
    }
    std::cout << "Sum is: "<< sum << std::endl;

    return 0;
}
