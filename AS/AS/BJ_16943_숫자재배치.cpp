// 190317
// https://www.acmicpc.net/problem/16943

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	int a, b, ans;
	bool ok = false;
	scanf("%d %d", &a, &b);
	vector<int> v;
	int temp = a;
	while (temp > 0) {
		v.push_back(temp % 10);
		temp /= 10;
	}

	sort(v.begin(), v.end());
	int size = v.size() - 1;
	do {
		temp = 0;
		if (v[0] == 0) continue;
		for (int i = size; i >= 0; i--) 
			temp += v[i] * pow(10, size - i);
		if (temp <= b) ans = temp, ok = true;
		else break;
	} while (next_permutation(v.begin(), v.end()));

	if (ok) printf("%d\n", ans);
	else printf("-1\n");


	return 0;
}