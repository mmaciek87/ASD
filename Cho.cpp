#include <iostream>
#include <vector>

using namespace std;

struct Tree {
private: 
    int base;
    vector<int> mini;
    vector<int> minCount;
    vector<int> maxi;
    vector<int> maxCount;

public:
    Tree(int n) {
        base = 1;

        while (base < n) {
            base *= 2;
        }

        mini.clear();   
        mini.resize(2 * base);

        maxi.clear();   
        maxi.resize(2 * base);

        minCount.clear();   
        minCount.resize(2 * base);

        maxCount.clear();   
        maxCount.resize(2 * base);
    }

    void insert(int i, int x) {
        i += base;

        maxi[i] = x;
        mini[i] = x;
        maxCount[i] = 1;
        minCount[i] = 1;

        for(i >>= 1; i > 0; i >>= 1) {
            if (maxi[i * 2] == maxi[i * 2 + 1]) {
                maxi[i] = maxi[i * 2];
                maxCount[i] = maxCount[i * 2] + maxCount[i * 2 + 1];
            }
            else if (maxi[i * 2] > maxi[i * 2 + 1]) {
                maxi[i] = maxi[i * 2];
                maxCount[i] = maxCount[i * 2];
            } 
            else {
                maxi[i] = maxi[i * 2 + 1];
                maxCount[i] = maxCount[i * 2 + 1];
            }

            if (mini[i * 2] == mini[i * 2 + 1]) {
                mini[i] = mini[i * 2];
                minCount[i] = minCount[i * 2] + minCount[i * 2 + 1];
            }
            else if (mini[i * 2] > mini[i * 2 + 1]) {
                mini[i] = mini[i * 2 + 1];
                minCount[i] = minCount[i * 2 + 1];
            } 
            else {
                mini[i] = mini[i * 2];
                minCount[i] = minCount[i * 2 ];
            }
        }
    }

    void query(int left, int right) {
        int minN = INT32_MAX, maxN = 0;
        int minC = 0, maxC = 0;

        for(int l = left + base, r = right + base + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (mini[l] < minN) {
                    minN = mini[l];
                    minC = minCount[l];
                } else if (mini[l] == minN) {
                    minC += minCount[l];
                }

                if (maxi[l] > maxN) {
                    maxN = maxi[l];
                    maxC = maxCount[l];
                } else if (maxi[l] == maxN) {
                    maxC += maxCount[l];
                }

                l++;
            }
            if (r & 1) {
                r--;
                if (mini[r] < minN) {
                    minN = mini[r];
                    minC = minCount[r];
                } else if (mini[r] == minN) {
                    minC += minCount[r];
                }

                if (maxi[r] > maxN) {
                    maxN = maxi[r];
                    maxC = maxCount[r];
                } else if (maxi[r] == maxN) {
                    maxC += maxCount[r];
                }
            }
        }


        // cout << "minN: " << minN << " maxN: " << maxN << "\n";
        // cout << "minCount: " << minC << " maxCount: " << maxC << "\n";
        if (minN == maxN) cout << "TAK\n";
        else if (minC + maxC == right - left + 1 && (minC == 1 || maxC == 1)) cout << "TAK\n";
        else cout << "NIE\n";
    }
};

vector<int> tree[200007];
int preOrder[200007];
int postOredr[200007];
int timer = 0;

void dfs(int v) {

    timer++;
    preOrder[v] = timer;

    for (int i = 0; i < tree[v].size(); i++) {
        dfs(tree[v][i]);
    }

    postOredr[v] = timer;
}



int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int x;
    for (int i = 2; i <= n; i++) {
        cin >> x;
        tree[x].push_back(i);
    }

    dfs(1);

    Tree segTree(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> x;
        segTree.insert(preOrder[i], x);
    }

    char a;
    int y;
    for (int i = 0; i < q; i++) {
        cin >> a;
        
        if (a == '?') {
            cin >> x;
            segTree.query(preOrder[x], postOredr[x]);
        } 
        else if (a == 'z') {
            cin >> x >> y;
            segTree.insert(preOrder[x], y);
        }
    }
}

/*
5 5
1 2 1 3
3 1 2 5 4
? 2
z 5 1
? 2
z 2 2
? 2
*/