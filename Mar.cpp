#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> G[500007];
bool visited[500007];
int skad[500007];
int length = 0;
int endV = 0;
vector<int> res;

void dfs(int n) {
    res.push_back(n);
    visited[n] = true;
    for (int i = 0; i < G[n].size(); i++) {
        if (!visited[G[n][i]]) {
            skad[G[n][i]] = n;
            dfs(G[n][i]);
            length++;
            res.push_back(n);
        }
    }
    length++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    endV = n;

    int a, b;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1);


    int current = n;
    vector<int> last;

    while (current != 1) {
        last.push_back(current);
        current = skad[current];
        length++;
    }

    reverse(last.begin(), last.end());

    cout << length << "\n";

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }

    for (int i = 0; i < last.size(); i++) {
        cout << last[i] << " ";
    }
}

/*
6 8
1 2 
2 3
3 4
4 5
5 6
6 1
1 3
3 5
*/