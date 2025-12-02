#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }
int cursor = 50;
int password = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        while (ss >> token) {
            char dir = token[0];
            int dist = std::stoi(token.substr(1));

            if (dir=='R'){
                cursor += dist;
                while(cursor>99){
                    cursor -= 100;
                    password++;
                }
            }
            else if(dir=='L'){
                if (cursor == 0) password--;
                cursor -= dist;
                while(cursor < 0){
                    cursor += 100;
                    password++;
                }
                if (cursor == 0) {
                    password++;
                }
            }
        }
    }

    file.close();
    std::cout << "Password is: " << password << std::endl;
    return 0;
}
