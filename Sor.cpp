#include <iostream>

using namespace std;

int t[1007];
int l[1007][1007];
int r[1007][1007];

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    for(int i = 0; i < n; i++) {
        l[i][i] = 1;
        r[i][i] = 1;

        if(i != n - 1) {
            if(t[i] < t[i+1]) {
                l[i][i+1] = 1;
                r[i][i+1] = 1;
            } else {
                l[i][i+1] = 0;
                r[i][i+1] = 0;
            }
        }
    }

    int ls = 0, rs = 0;

    for (int i = 3; i <= n; i++) {
        for (int j = 0; j < n - i + 1; j ++) {
            if (t[j] < t[j + 1]) ls = l[j + 1][j + i - 1];
            if (t[j] < t[j + i - 1]) rs = r[j + 1][j + i - 1];
            l[j][j + i - 1] = (ls + rs) % (int) 1e9;
            ls = 0; rs = 0;

            if (t[j + i - 1] > t[j]) ls = l[j][j + i - 2];
            if (t[j + i - 1] > t[j + i - 2]) rs = r[j][j + i - 2];
            r[j][j + i - 1] = (ls + rs) % (int) 1e9;
            ls = 0; rs = 0;
        }
    }

    if (n == 1) cout << 1;
    else cout << (l[0][n - 1] + r[0][n - 1]) % (int) 1e9;
}