// October 28, 2018
//

/*

*/


#include <bits/stdc++.h>

using namespace std;


const int MAXN = 300000;
const int MAXA = 300000;

int n;
vector<int> a;
vector<int> primes;
vector<int> sieve;
unordered_map<int, int> dp[MAXN + 1];

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void gen_primes(int cap) {
	sieve.resize(cap + 1);
	for (int i = 2; i * i <= cap; i++) {
		if (sieve[i]) continue;
		for (int j = i * i; j <= cap; j += i) {
			sieve[j] = i;
		}
	}
	for (int i = 2; i <= cap; i++) {
		if (sieve[i] == 0) primes.push_back(i);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG


	gen_primes(MAXA);

	cin >> n;
	a.resize(n);
	int num_primes = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == 1) {
			cout << "1\n";
			return 0;
		}
		if (binary_search(primes.begin(), primes.end(), a[i])) num_primes++;
	}
	if (num_primes >= 2) {
		cout << "2\n";
		return 0;
	}
	int g = a[0];
	for (int i = 1; i < n; i++) {
		g = gcd(g, a[i]);
	}
	if (g != 1) {
		cout << "-1\n";
		return 0;
	}



	return 0;
}
