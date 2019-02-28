// 190228
// https://www.acmicpc.net/problem/10971

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int w[10][10];

int main()
{
	int ans = 10000000;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &w[i][j]);
		}
	}

	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = i;
	}


	do {
		int temp = 0;
		bool escape = false;
		for (int i = 0; i < n - 1; i++) {
			if (w[v[i]][v[i + 1]]) {
				temp += w[v[i]][v[i + 1]];
			}
			else {
				escape = true;
				break;
			}
		}
		if (escape) continue;
		if (w[v[n - 1]][v[0]]) {
			temp += w[v[n - 1]][v[0]];
		}
		else {
			continue;
		}

		if (ans > temp) ans = temp;
	} while (next_permutation(v.begin(), v.end()));

	printf("%d\n", ans);
	return 0;
}