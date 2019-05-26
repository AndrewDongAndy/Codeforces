#include <bits/stdc++.h>

using namespace std;


#define DEBUGV(v) cout << #v << ": "; \
for (auto it = v.begin(); it != v.end(); it++) \
cout << *it << ' '; cout << '\n';

const int MAX = (int) 1e5;

int A, B, C;

int sieve[MAX + 1];
vector<int> primes;

vector<int> divisors;
vector< pair<int, int> > pfac;


void gen_primes(int max_prime) {
    fill(sieve, sieve + MAX + 1, 0);
	for (int i = 2; i * i <= max_prime; i++) {
		if (sieve[i]) continue;
		for (int j = i * i; j <= max_prime; j += i) {
			sieve[j] = i;
		}
	}
	for (int i = 2; i <= max_prime; i++) {
		if (sieve[i] == 0) {
			primes.push_back(i);
		}
	}
}


map<int, int> prime_factorization(int n) {
    map<int, int> res;
    for (int p : primes) {
        while (n % p == 0) {
            n /= p;
            res[p]++;
        }
    }
    return res;
}

void gen_divs(int cur, int p_ind) {
    if (p_ind == (int) pfac.size()) {
        divisors.push_back(cur);
        return;
    }
    int p, e;
    tie(p, e) = pfac[p_ind];
    gen_divs(cur, p_ind + 1);
    int curpow = 1;
    for (int i = 1; i <= e; i++) {
        curpow *= p;
        gen_divs(cur * curpow, p_ind + 1);
    }
}

vector<int> get_divs(int n) {
    // stores in divisors vector
    pfac.clear();
    divisors.clear();

    auto tmp = prime_factorization(n);
    for (auto p : tmp) {
        pfac.push_back(p);
    }

    gen_divs(1, 0);
    sort(divisors.begin(), divisors.end());

    return divisors;
}


void run() {
    cin >> A >> B >> C;
    vector<int> da = get_divs(A), db = get_divs(B), dc = get_divs(C);
    // DEBUGV(da); DEBUGV(db); DEBUGV(dc);

    int ans = (int) da.size() * (int) db.size() * (int) dc.size();

    int x;

    x = 0;
    for (int a : da) {
        if (binary_search(db.begin(), db.end(), a)) {
            x++;
        }
    }
    ans -= x * (x - 1) * (int) dc.size();

    x = 0;
    for (int b : db) {
        if (binary_search(dc.begin(), dc.end(), b)) {
            x++;
        }
    }
    ans -= x * (x - 1) * (int) da.size();

    x = 0;
    for (int c : dc) {
        if (binary_search(da.begin(), da.end(), c)) {
            x++;
        }
    }
    ans -= x * (x - 1) * (int) db.size();

    x = 0;
    for (int a : da) {
        bool indb = binary_search(db.begin(), db.end(), a);
        bool indc = binary_search(dc.begin(), dc.end(), a);
        if (indb && indc) {
            x++;
        }
    }
    ans += x * (x - 1) * (x - 2);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // _DEBUG)


    gen_primes(MAX);

    int TC;
    cin >> TC;
    while (TC--) {
        run();
    }

    return 0;
}
