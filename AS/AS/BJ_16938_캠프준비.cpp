// 190328
// https://www.acmicpc.net/problem/16938

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n, l, r, x;
int a[15];
int ans;

void howmanyproblems()
{
	ans = 0;
	for (int i = 2; i <= n; i++) {
		vector<int> v(n);
		// i는 문제 수 
		for (int k = 0; k < n - i; k++) v[k] = 0;
		for (int k = n - i; k < n; k++) v[k] = 1;

		// 
		do {
			long long maxP = 0, minP = 1e9;
			long long sumP = 0;

			for (int j = 0; j < n; j++) {
				if (v[j] == 1) {
					sumP += a[j];
					if (maxP < a[j]) maxP = a[j];
					if (minP > a[j]) minP = a[j];
				}
			}

			if (sumP < l || sumP > r) continue;
			if (abs(maxP - minP) < x) continue;
			ans += 1;
		} while (next_permutation(v.begin(), v.end()));
		vector<int>().swap(v);
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l >> r >> x;
	for (int i = 0; i < n; i++) cin >> a[i];

	howmanyproblems();
	cout << ans << endl;
	return 0;
}