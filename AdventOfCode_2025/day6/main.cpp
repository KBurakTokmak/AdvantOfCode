#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> numberMatrix;
    std::vector<char> operatorRow;
    std::string line;

    while (std::getline(inputFile, line)) {
        // Skip empty lines to ensure robustness
        if (line.empty()) continue;
        
        // Find first non-whitespace character to determine line type
        size_t firstCharIdx = line.find_first_not_of(" \t\r\n");
        if (firstCharIdx == std::string::npos) continue; // Line is all whitespace

        char firstChar = line[firstCharIdx];
        std::stringstream ss(line);

        // Check if the line starts with a digit or a minus sign (for negative numbers)
        if (std::isdigit(firstChar) || firstChar == '-') {
            std::vector<int> row;
            int num;
            // Extraction operator >> automatically handles whitespace delimiters
            while (ss >> num) {
                row.push_back(num);
            }
            numberMatrix.push_back(row);
        } 
        else {
            // Treat as the operator line
            char op;
            while (ss >> op) {
                operatorRow.push_back(op);
            }
        }
    }

    inputFile.close();
    long long result = 0;
    std::cout << "Row count: "<< numberMatrix.size()<<std::endl;
    std::cout << "Column count: "<< numberMatrix[0].size()<<std::endl;
    for (size_t j = 0; j < numberMatrix[0].size(); ++j) {
        long long row_result = 0;
        if (operatorRow[j] == '*'){
            row_result = 1;
        }
        for (size_t i = 0; i < numberMatrix.size(); ++i) {
            if (operatorRow[j] == '+'){
                std::cout << "Adding " << numberMatrix[i][j] << " to row result." << std::endl;
                row_result += numberMatrix[i][j];
            }
            else if (operatorRow[j] == '*'){
                std::cout << "Multiplying " << numberMatrix[i][j] << " to row result." << std::endl;
                row_result *= numberMatrix[i][j];
            }
        }
        std::cout << "Row " << j << " result: " << row_result << std::endl;
        result += row_result;
    }
    
    std::cout << "Final Result: " << result << std::endl;

    return 0;
}