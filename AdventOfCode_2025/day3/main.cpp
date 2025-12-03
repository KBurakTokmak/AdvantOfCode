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
        int max_ls = 0;
        int max_rs = 0;
        int max_loc = 0;
        for (int i=0; i<s.length()-1;i++){
            int current = s[i]-'0';
            if(current > max_ls){
                max_ls = current;
                max_loc=i;
            }
        }
        for (int i=s.length(); i>max_loc; i--){
            int current = s[i]-'0';
            if(current > max_rs){
                max_rs= current;
            }
        }
        int line_max = (max_ls * 10) +(max_rs);
        std::cout << "Adding to sum : " << line_max << std::endl;
        sum+= line_max;
    }

    std::cout << "Sum is: " << sum << std::endl;

    return 0;
}
