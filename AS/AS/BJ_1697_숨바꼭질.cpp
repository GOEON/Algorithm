// 190228
// https://www.acmicpc.net/problem/1697

#include <cstdio>
#include <queue>
#define MAX 200000
using namespace std;

int n, k;

bool check[MAX + 1];
int dist[MAX + 1];


int main()
{
	scanf("%d %d", &n, &k);

	check[n] = true;
	dist[n] = 0;

	queue<int> q;
	q.push(n);

	int count = 0;
	while (!q.empty()) {
		int temp = q.front();
		q.pop();

		if (temp - 1 >= 0) {
			if (!check[temp - 1]) {
				check[temp - 1] = 1;
				dist[temp - 1] = dist[temp] + 1;
				q.push(temp - 1);
			}
		}
		if (temp + 1 <= MAX) {
			if (!check[temp + 1]) {
				check[temp + 1] = 1;
				dist[temp + 1] = dist[temp] + 1;
				q.push(temp + 1);
			}
		}
		if (temp * 2 <= MAX) {
			if (!check[temp * 2]) {
				check[temp * 2] = 1;
				dist[temp * 2] = dist[temp] + 1;
				q.push(temp * 2);
			}
		}
	}

	printf("%d\n", dist[k]);
	return 0;
}