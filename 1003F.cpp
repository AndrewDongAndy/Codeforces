#include <bits/stdc++.h>

using namespace std;


const int MAXN = 300;

int n;
vector<string> w;

vector<int> z;
int cnt[MAXN];

void gen_z() {
    z.resize(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - x], y - i + 1));
        while (i + z[i] < n && w[z[i]] == w[i + z[i]]) {
            x = i;
            y = i + z[i];
            z[i]++;
        }
    }
}

int main() {
    cin >> n;
    w.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    gen_z();
    fill(cnt, cnt + N, 0);
    for (int i = 1; i < n; i++) {
        cnt[i]++;
    }

    for (int i = N - 1; i >= 0; i--) {
        if (i >= 2) {
            
        }
    }


    return 0;
}
