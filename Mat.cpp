#include <iostream>

using namespace std;

int main() {

    string pattern;
    cin >> pattern;

    char prevc = pattern[0];
    int prevj = 0, l = pattern.size() + 1;

    bool bpc = false;

    if (pattern[0] != '*') bpc = true;

    for(int j = 1; j < (int) pattern.size(); j++) {
        if (pattern[j] != '*') {
            if (bpc && pattern[j] != prevc) {
                l = min(l, j + 1 - prevj);
            }
            prevc = pattern[j];
            prevj = j;
            bpc = true;
        }
    }

    if (l == (int) pattern.size() + 1) {
        cout << 1;
    }
    else {
        cout << pattern.size() - l + 2;
    }
}