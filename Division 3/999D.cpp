// July 2, 2018
// http://codeforces.com/contest/999/problem/D

#include <bits/stdc++.h>

using namespace std;


const int MAX = (int) 2e5;

int N, M;
long long a[MAX];
int cnt[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);


    cin >> N >> M;

    set<int> s;
    for (int i = 0; i < N; i++) {
        cnt[i] = 0;
        s.insert(i);
    }

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];

        int nextm = -1;
        if (a[i] % M > *s.rbegin()) {
            nextm = *s.begin();
        } else {
            nextm = *s.lower_bound(a[i] % M);
        }
        assert(nextm != -1);

        int ch = nextm - a[i] % M;
        if (ch < 0) ch += M;

        a[i] += ch;
        ans += ch;
        cnt[a[i] % M]++;
        if (cnt[a[i] % M] == N / M) s.erase(a[i] % M);
    }

    for (int i = 0; i < M; i++) {
        assert(cnt[i] == N / M);
    }

    cout << ans << '\n';
    for (int i = 0; i < N; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';


    return 0;
}
