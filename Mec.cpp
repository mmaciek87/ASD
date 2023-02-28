#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long history[400001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;

    cin >> n >> m;

    int x = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n/2; j++) {
            cin >> x;
        }
        for (int j = 0; j < n/2; j++) {
            cin >> x;
            history[x] |= 1ll << i;
        }
    }

    sort(history + 1, history + n);

    bool result = true;

    for (int i = 1; i < n; i++) {
        if (history[i] == history[i+1]) {
            result = false;
        }
    }

    cout << (result ? "TAK": "NIE");
}