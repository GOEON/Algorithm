// 190228
// https://www.acmicpc.net/problem/1963

#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int t;
int prime[10000]; // 1면 소수 

int main()
{
	for (int i = 2; i < 10000; i++) {
		if (prime[i] == 0) prime[i] = 1;
		for (int j = 2; i*j < 10000; j++) {
			prime[i*j] = 2;
		}
	}

	scanf("%d", &t);
	while (t--) {
		queue<int> q;
		int before;
		int after;
		int dist[10000];
		bool isFirst[10000]; // false 면 큐에 들어왔었음 
		int num4[4] = { 0 };

		memset(dist, 0, sizeof(dist));
		memset(isFirst, true, sizeof(isFirst));

		scanf("%d %d", &before, &after);
		dist[before] = 0;
		isFirst[before] = false;

		q.push(before);

		while (!q.empty()) {
			int temp = q.front();
			int curPW = temp;
			q.pop();
			for (int i = 3; i >= 0; i--) {
				num4[i] = temp % 10;
				temp /= 10;
			}

			// 천
			for (int i = 1; i <= 9; i++) {
				num4[0] = i;
				int newPW = num4[0] * 1000 + num4[1] * 100 + num4[2] * 10 + num4[3];
				if (isFirst[newPW] && prime[newPW] == 1) {
					isFirst[newPW] = false;
					dist[newPW] = dist[curPW] + 1;
					q.push(newPW);
				}
			}
			num4[0] = curPW / 1000;
			// 백
			for (int i = 0; i <= 9; i++) {
				num4[1] = i;
				int newPW = num4[0] * 1000 + num4[1] * 100 + num4[2] * 10 + num4[3];
				if (isFirst[newPW] && prime[newPW] == 1) {
					isFirst[newPW] = false;
					dist[newPW] = dist[curPW] + 1;
					q.push(newPW);
				}
			}
			num4[1] = (curPW / 100) % 10;
			
			// 십
			for (int i = 0; i <= 9; i++) {
				num4[2] = i;
				int newPW = num4[0] * 1000 + num4[1] * 100 + num4[2] * 10 + num4[3];
				if (isFirst[newPW] && prime[newPW] == 1) {
					isFirst[newPW] = false;
					dist[newPW] = dist[curPW] + 1;
					q.push(newPW);
				}
			}
			num4[2] = (curPW / 10) % 10;

			// 일
			for (int i = 0; i <= 9; i++) {
				num4[3] = i;
				int newPW = num4[0] * 1000 + num4[1] * 100 + num4[2] * 10 + num4[3];
				if (isFirst[newPW] && prime[newPW] == 1) {
					isFirst[newPW] = false;
					dist[newPW] = dist[curPW] + 1;
					q.push(newPW);
				}
			}
		}
		printf("%d\n", dist[after]);
	}
	return 0;
}