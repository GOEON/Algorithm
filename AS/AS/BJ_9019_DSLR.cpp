// 190311
// https://www.acmicpc.net/problem/9019

#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

void minCmd(int s, int d)
{
	bool check[10000];
	memset(check, false, sizeof(check));
	char DSLR[10000];
	int prev[10000];
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		// D
		int D = (2 * temp) % 10000;
		if (!check[D]) {
			DSLR[D] = 'D';
			prev[D] = temp;
			check[D] = true;
			q.push(D);
		}
		// S
		int S;
		if (temp == 0) S = 9999;
		else S = temp - 1;
		if (!check[S]) {
			DSLR[S] = 'S';
			prev[S] = temp;
			check[S] = true;
			q.push(S);
		}

		int num4[4];
		for (int i = 0; i < 4; i++) {
			num4[i] = (temp / (int)pow(10, 3 - i)) % 10;
		}
		// L
		int L = num4[1] * 1000 + num4[2] * 100 + num4[3] * 10 + num4[0];
		if (!check[L]) {
			DSLR[L] = 'L';
			prev[L] = temp;
			check[L] = true;
			q.push(L);
		}
		// R
		int R = num4[3] * 1000 + num4[0] * 100 + num4[1] * 10 + num4[2];
		if (!check[R]) {
			DSLR[R] = 'R';
			prev[R] = temp;
			check[R] = true;
			q.push(R);
		}
		if (check[d]) break;
	}
	vector<char> v;
	int n1 = d;
	while (n1 != s) {
		v.push_back(DSLR[n1]);
		n1 = prev[n1];
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		cout << v[i];
	}
	cout << endl;
}

int main()
{
	int T;
	int a, b;
	cin >> T;
	while (T--) {
		cin >> a >> b;
		minCmd(a, b);
	}
	return 0;
}