#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

struct MachineData {
    std::string pattern;
    std::vector<std::vector<int>> buttons;
    std::vector<int> jolts;
};

std::string trim(const std::string &s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}


std::vector<int> parseIntList(const std::string &s) {
    std::vector<int> result;
    std::stringstream ss;
    for (char c : s) {
        if (c == ',') ss << ' ';
        else ss << c;
    }
    int x;
    while (ss >> x) {
        result.push_back(x);
    }
    return result;
}

int main() {
    std::ifstream in("sample.txt");
    if (!in) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    std::vector<MachineData> machines;
    std::string line;

    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        MachineData data;

        // --- Pattern inside [] ---
        std::size_t lb = line.find('[');
        std::size_t rb = line.find(']', lb + 1);
        if (lb == std::string::npos || rb == std::string::npos) {
            std::cerr << "Invalid line (missing []): " << line << "\n";
            continue;
        }
        data.pattern = line.substr(lb + 1, rb - lb - 1);

        // --- Jolts inside {} ---
        std::size_t lc = line.find('{', rb + 1);
        std::size_t rc = line.find('}', lc + 1);
        if (lc == std::string::npos || rc == std::string::npos) {
            std::cerr << "Invalid line (missing {}): " << line << "\n";
            continue;
        }
        std::string joltsContent = trim(line.substr(lc + 1, rc - lc - 1));
        data.jolts = parseIntList(joltsContent);

        std::string mid = line.substr(rb + 1, lc - rb - 1);
        std::size_t pos = 0;
        while (true) {
            std::size_t lp = mid.find('(', pos);
            if (lp == std::string::npos) break;
            std::size_t rp = mid.find(')', lp + 1);
            if (rp == std::string::npos) break;

            std::string groupContent = trim(mid.substr(lp + 1, rp - lp - 1));
            data.buttons.push_back(parseIntList(groupContent));

            pos = rp + 1;
        }

        machines.push_back(std::move(data));
    }
    for(auto &machine : machines) {
        
    }


    return 0;
}
