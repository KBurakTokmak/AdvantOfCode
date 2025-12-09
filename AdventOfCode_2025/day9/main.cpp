#include <fstream>
#include <iostream>
#include <utility>
#include <vector>


int main()
{
    std::vector<std::pair<int, int>> coordinates;
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    int firstVal, secondVal;
    char delimiter;
    while (inputFile >> firstVal >> delimiter >> secondVal)
    {
        if (delimiter == ',')
        {
            coordinates.push_back({firstVal, secondVal});
        }
    }
    inputFile.close();

    long long maxArea = 0;
    for (size_t i = 0; i < coordinates.size(); i++)
    {
        for (size_t j = i + 1; j < coordinates.size(); j++)
        {
            long long width = abs(coordinates[j].first - coordinates[i].first) + 1;
            long long height = abs(coordinates[j].second - coordinates[i].second) + 1;
            long long area = width * height;
            if (area > maxArea)
            {
                maxArea = area;
            }
        }
    }
    std::cout << "Area: " << maxArea << std::endl;

    return 0;
}