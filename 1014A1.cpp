// July 24, 2018
// http://codeforces.com/contest/1014/problem/A1

/*
This is a "Marathon" contest, so here's my partial progress
(likely the only I will make this contest).

Note that 1014A2 is the same problem, just with different
test data, as can be seen in the following announcement
that was sent out by the organizers:

"The two problem statements are the same. Submit for problem
A1 to test on examples, and for problem A2 to test on
preliminary tests."
*/


#include <bits/stdc++.h>

using namespace std;


const int MAXN = 100000;
const int MAXC = 10;
const int MAXU = 10;

int N, S, C, H, U;
int stripe[MAXN];
queue<int> colours;

// chamPos[i] is the square of chameleon number i
// NOT taken mod N
long long chamPos[MAXU];

int hand[MAXC];

// nextSquare[i][j] is the number of the square STRICTLY AFTER i having colour j
// taken mod N
int nextSquare[MAXN][MAXC];


int dist(int a, int b) {
	return (b - a + N) % N;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG)


	cin >> N >> S >> C >> H >> U;
	for (int i = 0; i < N; i++) {
		char c;
		cin >> c;
		stripe[i] = c - 'A';
	}
	for (int i = 0; i < H + S; i++) {
		char c;
		cin >> c;
		colours.push(c - 'A');
	}
	fill(hand, hand + MAXC, 0);
	for (int i = 0; i < H; i++) {
		int c = colours.front(); colours.pop();
		hand[c]++;
	}

	for (int i = 0; i < U; i++) {
		chamPos[i] = i;
	}

	vector<int> last(C, 0);
	for (int i = 0; i < N; i++) {
		int c = stripe[i];
		last[c] = i;
	}

	/*
	cout << "last on strip with colours: ";
	for (int i = 0; i < C; i++) {
		cout << last[i] << ' ';
	}
	cout << '\n';
	*/

	for (int i = 0; i < N; i++) {
		int c = stripe[i];
		if (last[c] == i) {
			for (int j = 0; j < N; j++) {
				nextSquare[j][c] = i;
			}
		}
		else {
			for (int j = last[c]; j != i; j = (j + 1) % N) {
				nextSquare[j][c] = i;
			}
		}

		last[c] = i;
	}

	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < C; j++) {
			cout << nextSquare[i][j] << ' ';
		}
		cout << '\n';
	}
	*/

	for (int i = 0; i < S; i++) {

	}


	return 0;
}
