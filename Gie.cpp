#include <iostream>

using namespace std;

int ceny[500007];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> ceny[i];
    }

    long long zysk = 0;
    bool mam = false;

    for (int i = 0; i < n; i++) {
        if (!mam && ceny[i + 1] > ceny[i]) {
            zysk -= ceny[i];
            mam = true;
        }
        else if (mam && ceny[i + 1] < ceny[i]) {
            zysk += ceny[i];
            mam = false;
        }
    }

    cout << zysk << '\n';
}