// 190226
// https://www.acmicpc.net/problem/1107

#include <cstdio>
using namespace std;

int n,m;
bool r[10]; // 리모컨 버튼 true면 고장

int check(int ch)
{
	if (ch == 0) {
		if (r[0]) return 0;
		else return 1;
	}

	int len = 0;
	while (ch) {
		if (r[ch % 10]) return 0;
		ch /= 10;
		len += 1;
	}
	return len;
}

int main()
{
	int ans = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int b;
		scanf("%d", &b);
		r[b] = true; // 고장 
	}
	
	ans = n - 100;
	if (ans < 0) ans = -ans;

	for (int i = 0; i <= 1000000; i++) {
		int len = check(i); // 0~9 버튼으로 접근 가능 한 지 
		if (len > 0) {
			int p = i - n;
			if (p < 0) p = -p; 
			if (ans > len + p) ans = len + p;
		}
	}

	printf("%d\n", ans);
	return 0;
}