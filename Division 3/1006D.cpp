// July 16, 2018
// http://codeforces.com/contest/1006/problem/D

/*
Bashy casework.

Is there a better way? Let me check some other quality submissions.
*/


#include <bits/stdc++.h>

using namespace std;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG)


	int n;
	string a, b;
	cin >> n;
	cin >> a >> b;

	int ans = 0;
	for (int i = 0; i < n / 2; i++) {
		char a1 = a[i], a2 = a[n - 1 - i];
		char b1 = b[i], b2 = b[n - 1 - i];

		if (b1 == b2) {
			ans += (a1 == a2 ? 0 : 1);
		} else {
			map<char, int> m;
			m[a1]++; m[a2]++; m[b1]++; m[b2]++;
			if (m.size() == 4) {
				ans += 2;
			} else if (m.size() == 3) {
				if (a1 == a2) {
					ans += 2;
				} else {
					ans += 1;
				}
			} else {
				if (m[a1] == 3) {
					ans += 1;
				}
			}
		}
	}


	if (n % 2 == 1) {
		ans += (a[n / 2] == b[n / 2] ? 0 : 1);
	}

	cout << ans << '\n';

	return 0;
}
