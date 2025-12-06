#include <cctype>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream inputFile("input.txt");

  std::vector<std::string> lines;

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }

  std::string currentLine;

  while (std::getline(inputFile, currentLine)) {
    lines.push_back(currentLine);
  }

  inputFile.close();
  long long result = 0;
  for (size_t lineIndex = 0; lineIndex < lines[4].size();) {
    char ch = lines[4][lineIndex];
    if (ch == '+' || ch == '*') {
      long long column_result = (ch == '*') ? 1 : 0;
      bool numeric_exists = true;
      std::vector<long long> column_values;
      while (numeric_exists) {
        // checking if numeric exists in this column
        // First, check bounds for all lines
        bool out_of_bounds = false;
        for (int i = 0; i < 4; ++i) {
          if (lineIndex >= lines[i].size()) {
            out_of_bounds = true;
            break;
          }
        }
        if (out_of_bounds) {
          numeric_exists = false;
          break;
        }

        // Check if any digit exists in this column
        bool has_digit = false;
        for (int i = 0; i < 4; ++i) {
          if (std::isdigit(lines[i][lineIndex])) {
            has_digit = true;
            break;
          }
        }
        if (!has_digit) {
          numeric_exists = false;
          break;
        }

        long long current_value = 0;
        for (int i = 0; i < 4; ++i) {
          int current_num = 0;
          char c = lines[i][lineIndex];
          if (std::isdigit(c)) {
            current_num = c - '0';
          }
          // else current_num stays 0 (for spaces or other chars)
          current_value += current_num * std::pow(10, 3 - i);
        }
        std::cout << "Adding current value: " << current_value
                  << " to the column values" << std::endl;
        column_values.push_back(current_value);
        lineIndex += 1;
      }
      // compute column result
      for (const auto &val : column_values) {
        if (ch == '+') {
          column_result += val;
        } else if (ch == '*') {
          column_result *= val;
        }
      }
      std::cout << "Adding column result: " << column_result
                << " to total result" << std::endl;
      result += column_result;
      continue; // Don't double-increment lineIndex
    }
    lineIndex += 1;
  }
  std::cout << "Final Result: " << result << std::endl;

  return 0;
}
