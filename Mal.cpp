#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;

void propagate(int i, int l) {
    if (tree[i] == 0) {
        tree[i * 2] = 0;
        tree[i * 2 + 1] = 0;
    } 
    else if (tree[i] == l) {
        tree[i * 2] = l / 2;
        tree[i * 2 + 1] = l / 2;
    }
}

int query(int i, int cl, int cr, int l, int r) {
    if (cl >= l && cr <= r) {
        return tree[i];
    }

    propagate(i, cr - cl + 1);

    int res = 0;
    int mid = (cl + cr) / 2;

    if (l <= mid) {
        res += query(i * 2, cl, mid, l, r);
    } 
    if (r > mid) {
        res += query(i * 2 + 1, mid + 1, cr, l, r);
    }

    return res;
}

void insert(int i, int cl, int cr, int l, int r, int k) {
    if (cl >= l && cr <= r) {
        tree[i] = k * (cr - cl + 1);
        return; 
    }

    propagate(i, cr - cl + 1);

    int mid = (cl + cr) / 2;
    
    if (l <= mid) {
        insert(i * 2, cl, mid, l, r, k);
    }
    if (r > mid) {
        insert(i * 2 + 1, mid + 1, cr, l, r, k);
    }

    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;

    int base = 1;

    while (base < n) {
        base *= 2;
    }

    tree.resize(base * 2);

    char a;
    int l, r;
	
	for (int i = 0; i < m; i++) {
        cin >> l >> r >> a;

        if (a == 'C') {
            insert(1, 0, base - 1, l, r, 0);
        } else {
            insert(1, 0, base - 1, l, r, 1);
        }

        cout << query(1, 0, base - 1, 1, n) << '\n';
    }
}

/*
12
4
1 5 C
2 10 B
4 6 B
4 7 C
*/