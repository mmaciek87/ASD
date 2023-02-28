#include <iostream>
#include <vector>

using namespace std;

#define N 500007

vector<int> G[N];
vector<int> visited(N);
vector<int> jumpPtrs[2][N];

int dia0, dia1;
int log;
int dist[2][N];
int currMaxL, currDia;
int debug = false;

void findDiameter(int x, int l) {
    visited[x] = true;

    if (l > currMaxL) {
        currDia = x;
        currMaxL = l;
    }

    for (int i = 0; i < G[x].size(); i++) {
        if(!visited[G[x][i]])
            findDiameter(G[x][i], l + 1);
    }
}

void DFS (int x, int dia, int l) {
    visited[x] = true;
    dist[dia][x] = l;

    for (int i = 0; i < G[x].size(); i++) {
        if(!visited[G[x][i]]) {
            jumpPtrs[dia][G[x][i]][0] = x;  
            DFS(G[x][i], dia, l + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ai, bi;
    for (int i = 1; i <= n; i++) {
        cin >> ai >> bi;

        if (ai != -1) {
            G[ai].push_back(i);
            G[i].push_back(ai);
        }

        if (bi != -1) {
            G[bi].push_back(i);
            G[i].push_back(bi);
        }
    }

    currDia = 1;
    findDiameter(1, 0);
    dia0 = currDia;
    
    currMaxL = 0;
    visited.clear();
    visited.resize(N);
    findDiameter(dia0, 0);
    dia1 = currDia;

    // cout << "KOŃCE ŚREDNICY: " << dia0 << " " << dia1 << '\n';

    for (int k = n; k > 0; k /= 2) log++;

    for (int i = 1; i <= n; i++) {
        jumpPtrs[0][i].resize(log);
        jumpPtrs[1][i].resize(log);
    }

    visited.clear();
    visited.resize(N);
    jumpPtrs[0][dia0][0] = dia0;
    DFS(dia0, 0, 0);

    visited.clear();
    visited.resize(N);
    jumpPtrs[1][dia1][0] = dia1;
    DFS(dia1, 1, 0);

    for (int i = 1; i < log; i++) {
        for (int x = 1; x <= n; x++) {
            jumpPtrs[0][x][i] = jumpPtrs[0][jumpPtrs[0][x][i - 1]][i - 1];
            jumpPtrs[1][x][i] = jumpPtrs[1][jumpPtrs[1][x][i - 1]][i - 1];
        }
    }

    // for (int i = 1; i < n; i++) {
    //     cout << "odległość " << i << " od " << dia0 << " to: " << dist[0][i] << '\n';
    //     cout << "odległość " << i << " od " << dia1 << " to: " << dist[1][i] << '\n';
    // }

    int m, a, d, dia;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> a >> d;
        
        if (dist[0][a] > dist[1][a]) dia = 0;
        else dia = 1;

        if (dist[dia][a] < d) {
            cout << "-1\n";
            continue;
        }

        int cnt = 0;
        while (d > 0) {
            if (d % 2 == 1) {
                a = jumpPtrs[dia][a][cnt];
            }

            d /= 2;
            cnt++;
        }

        cout << a << '\n';
    }
}
