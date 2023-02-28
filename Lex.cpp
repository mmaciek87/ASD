#include <iostream>

using namespace std;
using ll = long long;

const ll p = 30;
const ll q = 13819240;

ll s[300007];
ll h[300007];
ll pr[300007];

ll getHash(ll i, ll j) {
    return ((h[i] - (h[j + 1] * pr[j - i + 1]) % q) + q) % q;
}

pair<ll, ll> check(ll a, ll b, ll l) {
    if (l == 0) {
        return {a, b};
    }

    if (getHash(a, a + l / 2) == getHash(b, b + l / 2)) 
        return check(a + l / 2 + 1, b + l / 2 + 1, l / 2);

    else return check(a, b, l / 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    char x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        s[i] = x - 'a' + 1;
    }

    h[n] = s[n];

    for (int i = n - 1; i > 0; i--) {
        h[i] = (s[i] + h[i + 1] * p) % q;
    }

    pr[0] = 1;

    for (int i = 1; i < n - 1; i++) {
        pr[i] = (pr[i - 1] * p) % q;
    }

    ll a, b, c, d;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        ll l1 = b - a, l2 = d - c;
        ll shorter = min(l1, l2);
        auto p = check(a, c, shorter);

        if (getHash(a, a + shorter) == getHash(c, c + shorter)) {
            if (l1 == l2) cout << "=\n";
            else if (l1 < l2) cout << "<\n";
            else cout << ">\n";
        } else {
            if (s[p.first] < s[p.second]) cout << "<\n";
            else cout << ">\n";
        }
    }
}

/*
1 a
2 b
3 a
4 a
5 b
6 a
7 b
8 a
9 a
10 b
11 a
12 a
13 b
*/