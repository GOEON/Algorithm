// 190226
// https://www.acmicpc.net/problem/1476

#include <cstdio>
using namespace std;

int e, s, m;

int main()
{
	int ans = 1;
	int n1 = 1, n2 = 1, n3 = 1;
	scanf("%d %d %d", &e, &s, &m);

	while (1) {
		if (n1 == e && n2 == s && n3 == m) break;
		n1++; n2++; n3++;
		ans += 1;
		if (n1 == 16) n1 = 1;
		if (n2 == 29) n2 = 1;
		if (n3 == 20) n3 = 1;
	}

	printf("%d\n", ans);
	return 0;
}