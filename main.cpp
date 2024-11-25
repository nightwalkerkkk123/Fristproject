#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;

bool topologicalSort(int n, vector<vector<double>>& adjMatrix) {
    vector<double> dist(n, 0);
    vector<bool> visited(n, false);

    // Bellman-Ford算法
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] > 0) {
                    dist[v] = max(dist[v], dist[u] + log(adjMatrix[u][v]));
                }
            }
        }
    }

    // 检测负环
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] > 0 && dist[v] < dist[u] + log(adjMatrix[u][v])) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<double>> adjMatrix(n, vector<double>(n, 0));
        unordered_map<string, int> point;
        vector<double> weight(m);

        for (int i = 0; i < n; ++i) {
            string temp;
            cin >> temp;
            point[temp] = i;
        }

        for (int i = 0; i < m; ++i) {
            string name1, name2;
            cin >> name1 >> weight[i] >> name2;
            adjMatrix[point[name1]][point[name2]] = weight[i];
        }

        if (topologicalSort(n, adjMatrix)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
