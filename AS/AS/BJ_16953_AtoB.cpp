// 190317
// https://www.acmicpc.net/problem/16953

#include <iostream>
#include <queue>
# define MAX 1000000000
using namespace std;

bool ok;
long long a, b, ans;

void atob()
{
	ok = false, ans = 0;
	queue<int> q;
	q.push(a);

	long long temp = 0;
	while (!q.empty()) {
		for (long long i = q.size(); i--;) {
			temp = q.front();
			q.pop();

			if (temp == b) {
				ok = true;
				return;
			}

			// 곱하기 2
			if (temp * 2 <= b && temp * 2 <= MAX)
				q.push(temp * 2);
			
			// 1 붙이기 
			long long temp2 = temp * 10 + 1;
			if (temp2 <= b && temp2 <= MAX)
				q.push(temp2);
		}
		ans += 1;
	}
}

int main()
{
	cin >> a >> b;
	atob();
	if (ok) cout << ans + 1 << endl;
	else cout << -1 << endl;
	return 0;
}