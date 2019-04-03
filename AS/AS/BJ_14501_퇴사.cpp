// 190403
// https://www.acmicpc.net/problem/14501

#include <iostream>
using namespace std;

int n, ans;
int r_day; // retire day
int t[16];
int p[16];

int d[16]; // i날 끝나고 벌 수 있는 돈을 d[i]에

void play()
{
	for (int i = 1; i <= n; i++) {
		if (d[i] < d[i - 1]) d[i] = d[i - 1];
		if (i + t[i] > n + 1) continue;
		if (d[i + t[i] - 1] < d[i - 1] + p[i]) {
			d[i + t[i] - 1] = d[i - 1] + p[i];
		}
	}
	ans = d[n];
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ans = 0;
	cin >> n;
	r_day = n + 1;
	for (int i = 1; i <= n; i++)
		cin >> t[i] >> p[i];

	play();

	cout << ans << '\n';
	return 0;
}