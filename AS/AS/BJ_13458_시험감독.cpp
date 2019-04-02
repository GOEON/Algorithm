// 190402
// https://www.acmicpc.net/problem/13458

#include <iostream>
#include <queue>
using namespace std;

int n;

int b, c;
long long ans;

queue<int> q;

void howmanypeople()
{
	ans = 0;
	int idx = 0;
	while (!q.empty()) {
		int temp = q.front();
		q.pop();

		temp -= b;
		ans += 1;
		if (temp <= 0) continue;

		int quot = temp / c;
		if (temp % c > 0) quot += 1;
		ans += quot;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		q.push(temp);
	}
	cin >> b >> c;

	howmanypeople();

	cout << ans << '\n';

	return 0;
}