#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int maxSteps = 500001;
const long long mod = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l, x;
    cin >> n >> k >> l;

    vector<int> rangi;

    for (int i = 0; i < n; i++) {
        cin >> x;
        rangi.push_back(x);
    }

    sort(rangi.begin(), rangi.end());

    vector<int> dpMin(n);

    int okk = 0, ok = 0, ol = 0, mini = 1, currMin = 0, minSteps = n;
    dpMin[0] = 1;

    for(int i = 1; i < n; i++) {
        while (rangi[i] - rangi[ol] >= l) {
            ol++;
        }
        while (rangi[i] - rangi[ok] > k) {
            ok++;
        }
        if(ok > 0) {
            while(rangi[ok - 1] - rangi[okk] > k) {
                okk++;
                if(dpMin[okk] == maxSteps) {
                    currMin = okk;
                    while(dpMin[currMin] == maxSteps) {
                        currMin++;
                    }
                    mini = dpMin[currMin];
                } else {
                    mini = dpMin[okk];
                }
            }
        }

        if (ok == 0) dpMin[i] = 1;
        else if (ol <= okk) dpMin[i] = maxSteps;
        else dpMin[i] = mini + 1;

        if (rangi[n - 1] - rangi[i] <= k) minSteps = min(minSteps, dpMin[i]);
    } 

    okk = 0, ok = 0, ol = 0;
    long long suma = 0, ways = 0;
    int currentSteps = 1;
    vector<long long> dpSum(n);
    dpSum[0] = 1;
    if (rangi[n-1] - rangi[0] <= k) ways = 1;

    for(int i = 1; i < n; i++) {
        currentSteps = dpMin[i];

        while ((rangi[i] - rangi[ol] >= l && currentSteps > dpMin[ol]) || dpMin[ol] == maxSteps) {
            suma = (suma + mod + dpSum[ol]) % mod;
            ol++;
        }
        while (rangi[i] - rangi[ok] > k) {
            ok++;
        }
        if(ok > 0) {
            while ((okk < ol && (rangi[ok - 1] - rangi[okk] > k || dpMin[ol] - 1 > dpMin[okk])) || dpMin[okk] == maxSteps) {
                suma = (suma + mod - dpSum[okk]) % mod;
                okk++;
            }
        }

        if (ok == 0) dpSum[i] = 1;
        else dpSum[i] = suma;

        if (rangi[n - 1] - rangi[i] <= k && dpMin[i] == minSteps) ways = (ways + dpSum[i]) % mod;
    }

    cout << minSteps << " " << ways << '\n';
}
