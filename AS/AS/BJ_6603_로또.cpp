// 190228
// https://www.acmicpc.net/problem/6603

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int k = 1;
	
	while (1) {
		scanf("%d", &k);
		if (k == 0) break;

		int x;
		vector<int> s;
		vector<int> v;
		for (int i = 0; i < k; i++) {
			scanf("%d", &x);
			s.push_back(x);
			v.push_back(0);
		}

		for (int i = 0; i < 6; i++)
			v[i] = 1;

		do {
			for (int i = 0; i < k; i++) {
				if (v[i] == 1) printf("%d ", s[i]);
			}
			printf("\n");
		} while (prev_permutation(v.begin(), v.end()));
		printf("\n");
	}
	return 0;
}