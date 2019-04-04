// 190404
// https://www.acmicpc.net/problem/14888

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ans_max;
int ans_min;
int n;
int a[11];
int op[4];

void cal()
{
	int idx = 0;
	vector<int> v(n - 1);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < op[i]; j++) {
			v[idx++] = i;
		}
	}
	

	bool ok = true;
	do {
		int temp = a[0];

		for (int i = 1; i < n; i++) {
			if (v[i - 1] == 0) temp += a[i];
			else if (v[i - 1] == 1) temp -= a[i];
			else if (v[i - 1] == 2) temp *= a[i];
			else if (v[i - 1] == 3) {
				if (temp < 0) {
					temp = -temp;
					temp /= a[i];
					temp = -temp;
				}
				else {
					temp /= a[i];
				}
			}
		}

		if (ok) { // ÃÊ±â
			ok = false;
			ans_max = temp;
			ans_min = temp;
		}

		if (ans_max < temp) ans_max = temp;
		if (temp < ans_min) ans_min = temp;
	} while (next_permutation(v.begin(), v.end()));
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < 4; i++) cin >> op[i];

	cal();

	cout << ans_max << '\n';
	cout << ans_min << '\n';
	return 0;
}