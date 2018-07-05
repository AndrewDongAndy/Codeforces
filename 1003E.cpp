#include <bits/stdc++.h>

using namespace std;


int N, D, K;
int nextn = 1;
vector< pair<int, int> > edges;


void add_edges(int x, int deg, int depth) {
    if (depth == 0 || deg <= 0) return;
    for (int i = 0; i < deg; i++) {
        if (nextn > N - 1) return;
        edges.push_back({x, nextn});
        add_edges(nextn++, K - 1, depth - 1);
    }
}


void print_edges(int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        cout << edges[i].first << ' ' << edges[i].second << '\n';
    }
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> D >> K;


    if (N == 1) {
        cout << (D == 0 ? "YES" : "NO") << '\n';
        return 0;
    }
    if (D > N - 1) {
        cout << "NO\n";
        return 0;
    }

    if (K == 1) {
        if (N == 2) {
            cout << "YES" << '\n';
            cout << "1 2" << '\n';
        } else {
            cout << "NO" << '\n';
        }
        return 0;
    }


    for (int i = 1; i <= D; i++) {
        edges.push_back({i, i + 1});
    }
    nextn = D + 2;

    for (int i = 2; i <= D; i++) {
        int depth = min(i - 1, D - (i - 1));
        add_edges(i, K - 2, depth);
    }


    if ((int) edges.size() >= N - 1) {
        cout << "YES\n";
        print_edges(N - 1);
    } else {
        cout << "NO\n";
    }

    return 0;
}
