#include <iostream>
#include <vector>

using namespace std;

struct Tree {
private: 
    int base;
    vector<int> data;

public:
    Tree() {
		base = 0;
		data.clear();
	}

    Tree(int n) {
        base = 1;

        while (base < n) {
            base *= 2;
        }

        data.clear();   
        data.resize(base);
    }

    void insert(int i, int x) {
        i += base;

        data[i] += x;

        for(i >>= 1; i > 0; i >>= 1) {
            data[i] += x;
        }
    }

    void wypisz(int i) {
        cout << "drzewo: " << i << '\n';
        for(int i = 0; i < 30; i++) {
            cout << data[i] <<  " ";
        }
        cout << '\n';
    }

    int query(int l, int r) {
        int wynik = 0;

        for(l += base, r += base + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                wynik += data[l];
                l++;
            }
            if (r & 1) {
                r--;
                wynik += data[r];
            }
        }

        return wynik; 
    }
};

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	cin >> n >> k;
	
	vector<Tree> dp(k, Tree(n));
	
    for(int i = 0; i < n; i++) {
        dp[0].insert(i, 1);
    }

    for(int i = 0; i < k; i++) {
        dp[i].wypisz(i);
    }
}