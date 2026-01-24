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

    std::pair<Point, Point> latest_points;

    for (const Edge& e : edges) {
        bool is_one_circuit = false;
        for (int i = 0; i < n; i++) {
            if (uf.find(i) == i) { // tree root
                if (uf.getSize(i) == 1000){
                    long long last_junctions_x_multiplied = (long long)latest_points.first.x * latest_points.second.x;
                    std::cout << "Last junctions x multiplied: " << last_junctions_x_multiplied << std::endl;
                    is_one_circuit = true;
                    break;
                }
            }
        }
        if (is_one_circuit) {
            break;
        }
        bool connected = uf.unite(e.a, e.b);
        std::cout << "Connection at " << ": Point " << e.a 
                  << " (" << points[e.a].x << "," << points[e.a].y << "," << points[e.a].z << ")"
                  << " to Point " << e.b
                  << " (" << points[e.b].x << "," << points[e.b].y << "," << points[e.b].z << ")"
                  << " - Distance: " << e.distance;
        if (!connected) {
            std::cout << " (already connected)";
        }
        else {
            std::cout << "new connection made with points " << e.a << " and " << e.b << std::endl;
            latest_points = std::make_pair(points[e.a], points[e.b]);
        }
        std::cout << std::endl;
    }
    
    return 0;
}