// July 2, 2018
// http://codeforces.com/contest/999/problem/D

#include <bits/stdc++.h>

using namespace std;


const int MAX = (int) 2e5;

int N, M;
int a[MAX];
int cnt[MAX];
int nextm[MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    fill(cnt, cnt + MAX, 0);
    for (int i = 0; i < MAX; i++) {
        nextm[i] = i;
    }

    cin >> N >> M;

    int ans = 0;
    int avg = N / M;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        int m = a[i] % M;
        int ch = 0;
        while (cnt[nextm[m]] + 1 > avg) {
            ch++;
            nextm[m] = (nextm[m] + 1) % M;
        }
        cnt[nextm[m]]++;
        a[i] += ch;
        ans += ch;
    }

    cout << ans << '\n';
    for (int i = 0; i < N; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';


    return 0;
}
