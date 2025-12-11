#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;


void dfs(int src, int dest, vector<vector<int>> &graph, vector<int> &path,
         vector<vector<int>> &allPaths) {
    path.push_back(src);

    if (src == dest) {
        allPaths.push_back(path);
    } else {
        for (int adj_node : graph[src]) {
            dfs(adj_node, dest, graph, path, allPaths);
        }
    }

    path.pop_back();
}

vector<vector<int>> findPaths(int v, vector<vector<int>> &edges, int src, int dest) {
    vector<vector<int>> graph(v);

    // Build the graph from edges
    for (const auto &edge : edges) {
        graph[edge[0]].push_back(edge[1]);
    }

    vector<vector<int>> allPaths;
    vector<int> path;

    dfs(src, dest, graph, path, allPaths);

    return allPaths;
}

int main() {
    ifstream fin("input.txt");

    vector<pair<string, vector<string>>> stringGraph;
    string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string vertex;
        iss >> vertex;          // e.g. "aaa:" or "you:"

        if (vertex.empty()) continue;
        if (vertex.back() == ':') {
            vertex.pop_back();  // remove ':'
        }

        vector<string> neighbors;
        string nb;
        while (iss >> nb) {
            neighbors.push_back(nb);
        }

        stringGraph.push_back({vertex, neighbors});
    }

    fin.close();

    sort(stringGraph.begin(), stringGraph.end(),
         [](const auto &a, const auto &b) {
             return a.first < b.first;
         });


    unordered_map<string, int> nameToId;
    for (int i = 0; i < (int)stringGraph.size(); ++i) {
        nameToId[stringGraph[i].first] = i;
    }

    const string OUT_NAME = "out";

    int outIndex = (int)stringGraph.size(); 
    int V = (int)stringGraph.size() + 1; 
    vector<vector<int>> edges;

    for (int i = 0; i < (int)stringGraph.size(); ++i) {
        for (const string &nb : stringGraph[i].second) {
            int u = i;
            int v;

            if (nb == OUT_NAME) {
                v = outIndex;
            } else {
                auto it = nameToId.find(nb);
                if (it == nameToId.end()) {
                    cerr << "Unknown vertex referenced: " << nb << endl;
                    continue;
                }
                v = it->second;
            }

            edges.push_back({u, v});
        }
    }

    int youIndex = nameToId["you"];


    vector<vector<int>> paths = findPaths(V, edges, youIndex, outIndex);

    vector<string> idToName(V);
    for (int i = 0; i < (int)stringGraph.size(); ++i) {
        idToName[i] = stringGraph[i].first;
    }
    idToName[outIndex] = OUT_NAME;

    cout << "All paths from \"you\" to \"out\":\n";
    for (const auto &path : paths) {
        for (int vtx : path) {
            cout << vtx << "(" << idToName[vtx] << ") ";
        }
        cout << '\n';
    }

    cout << "Total paths: " << paths.size() << endl;

    return 0;
}
