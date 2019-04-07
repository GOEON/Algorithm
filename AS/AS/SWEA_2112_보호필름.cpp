#include <iostream>
#include <cstring>
using namespace std;

int T, ans;
int d, w, k;

bool a[13][20];

bool test()
{
	for (int j = 0; j < w; j++) {
		int cnt = 1;
		int temp = a[0][j];
		for (int i = 1; i < d; i++) {
			if (a[i][j] == temp) {
				cnt += 1;
				if (cnt == k) break;
			}
			else {
				cnt = 1;
				temp = a[i][j];
			}
		}
		if (cnt < k) return false;
	}
	return true;
}

bool dfs(int inject, int depth)
{
	if (depth == d) return test();
	for (int x = 0; x < 3; x++) {
		if (x == 2) {
			if(dfs(inject, depth + 1)) return true;
		}
		else if (inject > 0) {
			bool tmp[20];
			memcpy(tmp, a[depth], sizeof(a[depth]));
			memset(a[depth], x, sizeof(a[depth]));
			if (dfs(inject - 1, depth + 1)) return true;
			memcpy(a[depth], tmp, sizeof(a[depth]));
		}
	}
	return false;
}

int film()
{
	if (k == 1) return 0;
	if (test()) return 0;

	for (int i = 1; i < k; i++) {
		if (dfs(i, 0)) return i;
	}
	return k;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> d >> w >> k;

		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				cin >> a[i][j];
			}
		}

		cout << "#" << tc << " " << film() << '\n';
	}
	return 0;
}