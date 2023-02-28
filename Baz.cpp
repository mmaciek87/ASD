#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int aSize = 1e6 + 2;
long long a[aSize];
long long s[aSize];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n = 0;
    cin >> n;

    queue<long long> np;
    queue<long long> p;

    long long bp = 0, bnp = 0, np2p = 0, p2np = 0;

    for(int i = 0; i < n; i++) {
        cin >> a[n - i - 1];
    }

    s[0] = a[0];

    for(int i = 0; i < n; i++) {
        if(a[i] % 2 == 0) p.push(a[i]);
        else np.push(a[i]);
        if (i > 0) s[i] = s[i - 1] + a[i];
    }
    
    for(int i = 0; i < n; i++) {

        if(a[i] % 2 == 0) {
            p.pop();
            bp = a[i];
        }
        else {
            np.pop();
            bnp = a[i];
        } 

        if(s[i] % 2 == 0) {
            if(bp != 0 && !np.empty()) {
                p2np = s[i] - bp + np.front();
            }
            if(bnp != 0 && !p.empty()) {
                np2p = s[i] - bnp + p.front();
            }

            s[i] = max(p2np, np2p);
        } 

        if(s[i] %  2 == 0) s[i] = -1;

        p2np = 0, np2p = 0;
    }

    int m = 0, x = 0;
    cin >> m;

    for(int i = 0; i < m; i++) {
        cin >> x;
        cout << s[x - 1] << "\n";
    }
}