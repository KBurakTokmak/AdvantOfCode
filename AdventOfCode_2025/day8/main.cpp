#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y, z;
};

struct Edge {
    int a, b;
    double distance;
    
    bool operator<(const Edge& other) const {
        return distance < other.distance;
    }
};

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> size;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false; 
        }
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
        return true;
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};

double calculateDistance(const Point& a, const Point& b) {
    long long dx = (long long)a.x - b.x;
    long long dy = (long long)a.y - b.y;
    long long dz = (long long)a.z - b.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    
    // Read all junction boxes
    std::vector<Point> points;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string valueStr;
        Point p;
        
        std::getline(ss, valueStr, ',');
        p.x = std::stoi(valueStr);
        std::getline(ss, valueStr, ',');
        p.y = std::stoi(valueStr);
        std::getline(ss, valueStr, ',');
        p.z = std::stoi(valueStr);
        
        points.push_back(p);
    }
    inputFile.close();
    
    int n = points.size();
    std::cout << "Number of junction boxes: " << n << std::endl;

    std::vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e;
            e.a = i;
            e.b = j;
            e.distance = calculateDistance(points[i], points[j]);
            edges.push_back(e);
        }
    }
    
    std::sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    int connections = 0;
    int connectionsNeeded = 1000;
    
    for (const Edge& e : edges) {
        if (connections >= connectionsNeeded) {
            break;
        }
        
        connections++;
        bool connected = uf.unite(e.a, e.b);
        std::cout << "Connection " << connections << ": Point " << e.a 
                  << " (" << points[e.a].x << "," << points[e.a].y << "," << points[e.a].z << ")"
                  << " to Point " << e.b
                  << " (" << points[e.b].x << "," << points[e.b].y << "," << points[e.b].z << ")"
                  << " - Distance: " << e.distance;
        if (!connected) {
            std::cout << " (already connected)";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nTotal connections made: " << connections << std::endl;
    
    std::vector<int> circuitSizes;
    for (int i = 0; i < n; i++) {
        if (uf.find(i) == i) { // tree root
            circuitSizes.push_back(uf.getSize(i));
        }
    }
    
    std::sort(circuitSizes.begin(), circuitSizes.end(), std::greater<int>());
    
    std::cout << "\nNumber of circuits: " << circuitSizes.size() << std::endl;
    std::cout << "Circuit sizes (largest to smallest): ";
    for (int size : circuitSizes) {
        std::cout << size << " ";
    }
    std::cout << std::endl;
    
    if (circuitSizes.size() >= 3) {
        long long result = (long long)circuitSizes[0] * circuitSizes[1] * circuitSizes[2];
        std::cout << "\nProduct of three largest circuits: " 
                  << circuitSizes[0] << " * " << circuitSizes[1] << " * " << circuitSizes[2]
                  << " = " << result << std::endl;
    }
    
    return 0;
}