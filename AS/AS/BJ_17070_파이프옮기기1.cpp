// 190317
// https://www.acmicpc.net/problem/17070

#include <cstdio>
using namespace std;

int a[16][16];
int n, ans;

void dfs(int r, int c, int s)
{
	if (r == n - 1 && c == n - 1) {
		ans += 1;
		return;
	}

	if (s == 0) {
		// 0 -> 0
		if (c + 1 < n && a[r][c + 1] == 0) 
			dfs(r, c + 1, 0);
		// 0 -> 2
		if (c + 1 < n && r + 1 < n && a[r][c + 1] == 0 && a[r + 1][c] == 0 && a[r + 1][c + 1] == 0)
			dfs(r + 1, c + 1, 2);
	}
	else if (s == 1) {
		// 1 -> 1
		if (r + 1 < n && a[r + 1][c] == 0)
			dfs(r + 1, c, 1);
		// 1 -> 2
		if (c + 1 < n && r + 1 < n && a[r][c + 1] == 0 && a[r + 1][c] == 0 && a[r + 1][c + 1] == 0)
			dfs(r + 1, c + 1, 2);
	}
	else if (s == 2) {
		// 2 -> 0
		if (c + 1 < n && a[r][c + 1] == 0)
			dfs(r, c + 1, 0);
		// 2 -> 1
		if (r + 1 < n && a[r + 1][c] == 0)
			dfs(r + 1, c, 1);
		// 2 -> 2
		if (c + 1 < n && r + 1 < n && a[r][c + 1] == 0 && a[r + 1][c] == 0 && a[r + 1][c + 1] == 0)
			dfs(r + 1, c + 1, 2);
	}
}

int main()
{
	ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	dfs(0, 1, 0); // (r,c)

	printf("%d\n", ans);
	return 0;
}