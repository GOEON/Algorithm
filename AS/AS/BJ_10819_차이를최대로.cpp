// 190226
// https://www.acmicpc.net/problem/10819

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int main()
{
	int ans = 0;
	scanf("%d", &n);
	vector<int> v(n);

	for (int i = 0; i < n; i++) {
		int b;
		scanf("%d", &b);
		v[i] = b;
	}

	sort(v.begin(), v.end());
	do {
		int sum = 0;
		for (int i = 1; i < n; i++) {
			int temp = v[i - 1] - v[i];
			if (temp < 0) temp = -temp;
			sum += temp;
		}
		if (ans < sum) ans = sum;
	} while (next_permutation(v.begin(), v.end()));

	printf("%d\n", ans);

	return 0;
}