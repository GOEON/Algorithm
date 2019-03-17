// 190317
// https://www.acmicpc.net/problem/16987

#include <cstdio>
using namespace std;

int n, ans, temp;
int s[300], w[300];

void dfs(int idx) // 손에 든 계란 index 
{
	if (idx == n) {
		if (ans < temp) ans = temp;
		return; // 가장 오른쪽 계란을 들었을 경우
	}
	if (s[idx] <= 0) {
		dfs(idx + 1);
		return; // 손에 든 계란이 깨짐 
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) { // 치게 될 계란
		if (i == idx) continue;
		if (s[i] <= 0) {
			cnt += 1;
			continue; // 치게 될 계란이 깨져 있음 
		}

		int ms = s[idx]; // 들고 있는 
		int ts = s[i]; // 상대방

		// m -> t
		s[idx] -= w[i], s[i] -= w[idx];
		if (s[idx] <= 0) temp += 1;
		if (s[i] <= 0) temp += 1;
		dfs(idx + 1);
		if (s[idx] <= 0) temp -= 1;
		if (s[i] <= 0) temp -= 1;
		s[idx] = ms, s[i] = ts;
	}
	if (cnt == n - 1) dfs(idx + 1);
}

int main()
{
	ans = 0, temp = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &s[i], &w[i]);
	}
	dfs(0);
	printf("%d\n", ans);

	return 0;
}