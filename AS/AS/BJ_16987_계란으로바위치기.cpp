// 190317
// https://www.acmicpc.net/problem/16987

#include <cstdio>
using namespace std;

int n, ans, temp;
int s[300], w[300];

void dfs(int idx) // �տ� �� ��� index 
{
	if (idx == n) {
		if (ans < temp) ans = temp;
		return; // ���� ������ ����� ����� ���
	}
	if (s[idx] <= 0) {
		dfs(idx + 1);
		return; // �տ� �� ����� ���� 
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) { // ġ�� �� ���
		if (i == idx) continue;
		if (s[i] <= 0) {
			cnt += 1;
			continue; // ġ�� �� ����� ���� ���� 
		}

		int ms = s[idx]; // ��� �ִ� 
		int ts = s[i]; // ����

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