#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility> 
#include <cctype>    
#include <algorithm> 

bool is_blank(const std::string &s) {
    return std::all_of(s.begin(), s.end(),
                       [](unsigned char c){ return std::isspace(c); });
}

int main() {
    std::ifstream in("sample.txt");
    if (!in) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::vector<std::pair<long long,long long>> ranges;
    std::vector<long long> numbers;

    std::string line;
    bool readingRanges = true;

    while (std::getline(in, line)) {
        if (is_blank(line)) {
            // first blank line ends the "range" section
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            // line format: "a-b"
            std::size_t dashPos = line.find('-');
            if (dashPos == std::string::npos) {
                continue;
            }

            long long first  = std::stoll(line.substr(0, dashPos));
            long long second = std::stoll(line.substr(dashPos + 1));

            ranges.emplace_back(first, second);
        } else {
            long long value = std::stoll(line);
            numbers.push_back(value);
        }
    }



    long long fresh_count = 0;
    for (auto &x : numbers) {
        std::cout<<"Checking number: "<<x<<std::endl;
        bool found = false;
        for (const auto &p : ranges) {
            if (found) continue;
            if(p.second >= x && p.first <= x ) {
                fresh_count++;
                found = true;
            }
            
        }
    }

    std::cout<<"Fresh count: "<<fresh_count<<std::endl;

    return 0;
}
