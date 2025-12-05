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

std::vector<std::pair<long long, long long>> mergeRanges(std::vector<std::pair<long long, long long>>& ranges) {
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long long, long long>> merged;
    
    merged.push_back(ranges[0]);

    for (size_t i = 1; i < ranges.size(); ++i) {
        std::pair<long long, long long>& lastMerged = merged.back();
        const std::pair<long long, long long>& current = ranges[i];
        if (current.first <= lastMerged.second) {
            lastMerged.second = std::max(lastMerged.second, current.second);
        } 
        else {
            merged.push_back(current);
        }
    }

    return merged;
}

int main() {
    std::ifstream in("input.txt");
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
    std::vector<std::pair<long long,long long>> fresh_ranges = mergeRanges(ranges);
    long long fresh_count = 0;
    for (const auto &x: fresh_ranges){
        fresh_count += x.second - x.first +1;
    }

    std::cout<<"Fresh count: "<<fresh_count<<std::endl;

    return 0;
}
