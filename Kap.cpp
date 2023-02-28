#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

const int N = 200007;

vector<pair<int, int> > g[N];
vector<tuple<int, int, int> > pairs;
vector<int> dist(N, INT32_MAX);

int cmpX(tuple<int, int, int> first, tuple<int, int,int> second){
    return get<1>(first) < get<1>(second);
}

int cmpY(tuple<int, int, int> first, tuple<int, int,int> second){
    return get<2>(first) < get<2>(second);
}

void addToGraph(int n) {
    int distx = 0, disty = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            distx = abs(get<1>(pairs[i]) - get<1>(pairs[i - 1]));
            disty = abs(get<2>(pairs[i]) - get<2>(pairs[i - 1]));
            g[get<0>(pairs[i])].push_back({get<0>(pairs[i - 1]), min(distx, disty)});
        }

        if (i < n - 1) {
            distx = abs(get<1>(pairs[i]) - get<1>(pairs[i + 1]));
            disty = abs(get<2>(pairs[i]) - get<2>(pairs[i + 1]));
            g[get<0>(pairs[i])].push_back({get<0>(pairs[i + 1]), min(distx, disty)});
        }
    }
}

void Dijkstra(int x){
    priority_queue<pair<int, int>> q;
    q.push({0, x});
    dist[x] = 0;

    while(!q.empty()) {
        int u = q.top().second; q.pop();

        for(pair<int, int> e : g[u]) {
            int v = e.first, w = e.second;

            if(dist[u] + w < dist[v]) {
                q.push({-(dist[u] + w), v});
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, x, y;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        pairs.push_back({i, x, y});
    }

    sort(pairs.begin(), pairs.end(), cmpX);
    addToGraph(n);

    sort(pairs.begin(), pairs.end(), cmpY);
    addToGraph(n);
    
    Dijkstra(1);

    cout << dist[n] << '\n';
}