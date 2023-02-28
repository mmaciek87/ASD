#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    string s;

    cin >> n >> k;
    cin >> s;

    vector<pair<int, double> > vec;
    int l, p;
    double mid;

    for (int i = 0; i < k; i++) {
        cin >> l >> p;
        l--;
        p--;
        vec.push_back(make_pair(l, l + p));
    }

    sort(vec.begin(), vec.end());

    int j = 0;
    bool swap = false;
    double currmid = 0;
    int currL = 0;
    char tmp;

    for(int i = 0; i < n; i++) {
        if (i > currmid - currL) swap = false;

        l = vec[j].first;
        mid = vec[j].second;

        if (i == l && j < vec.size()) {
            swap = !swap;
            if (mid != currmid) {
                currmid = mid;
                currL = l;
            }
            j++;
        }

        if (swap && (i < currmid / 2)) {
            tmp = s[i];
            s[i] = s[currmid - i];
            s[currmid - i] = tmp;
        }
    }

    cout << s;
}
