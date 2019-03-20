// 190320
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo&categoryId=AWXRUN9KfZ8DFAUo&categoryType=CODE

#include <cstdio>
#include <map>
#include <queue>
#include <cstdlib>
#include <cmath>
using namespace std;

queue<char> q;
int T, n, k, unit;
long long ans;

void revolve()
{
	char temp = q.front();
	q.pop();
	q.push(temp);
}

void kthnumber()
{
	priority_queue<long long, vector<long long>, less<long long>> pq;
	map<long long, int> m;

	for (int i = 0; i < n; i++) { // 회전수 
		// 숫자 계산
		int e = unit - 1;
		long long temp = 0;
		for (int j = q.size(); j--;) {
			char tmp = q.front();
			int num = q.front(); // A = 65
			q.pop();
			if (num >= 65) num -= 55;
			else num -= '0';
			temp = temp + num * (int)pow(16, e--); 
			if (e < 0) {
				e = unit - 1;
				if (m.count(temp) == 0) {
					m.insert({ temp, 2 });
					pq.push(temp);
				}
				temp = 0;
			}
			q.push(tmp);
		}
		// 회전
		revolve();
	}

	for (int i = 1; i < k; i++) {
		pq.pop();
	}
	ans = pq.top();
}

int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		queue<char>().swap(q);
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			char ch;
			scanf(" %c", &ch);
			q.push(ch);
		}
		unit = n / 4;
		kthnumber();

		printf("#%d %lld\n", tc, ans);
	}
	return 0;
}