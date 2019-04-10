// 190410
// https://www.acmicpc.net/problem/15684

#include <iostream>
#include <cstring>
using namespace std;

int n, m, h;
int ans;
int a[31][11];
bool ok;

bool test()
{
	int r, c;
	for (int j = 1; j <= n; j++) {
		r = 1; c = j;
		while (r <= h) {
			if (a[r][c] == 1) { c += 1; }
			else if (a[r][c] == 2) { c -= 1; }
			r += 1;
		}
		if (c != j) 
			return false;
	}
	return true;
}

void dfs(int remain, int si, int sj) 
{
	if (remain == 0) {
		if (test()) ok = true;
		return;
	}
	for (int i = si; i <= h; i++) {
		for (int j = (i == si ? sj : 1); j < n; j++) {
			if (a[i][j] == 0 && a[i][j + 1] == 0) {
				a[i][j] = 1; a[i][j + 1] = 2;
				dfs(remain - 1, i, j);
				if (ok) return;
				a[i][j] = 0; a[i][j + 1] = 0;
			}
		}
	}
}

bool ladderGame()
{
	ok = false;
	for (int i = 0; i < 4; i++) {
		ans = i;
		dfs(i, 1, 1);
		if (ok) return true;
	}
	return false;
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ans = 0;
	memset(a, 0, sizeof(a));
	int r1, c1;
	cin >> n >> m >> h;

	for (int i = 1; i <= m; i++) {
		cin >> r1 >> c1;
		a[r1][c1] = 1; a[r1][c1 + 1] = 2;
	}

	if (ladderGame()) cout << ans << '\n';
	else cout << -1 << '\n';

	return 0;
}