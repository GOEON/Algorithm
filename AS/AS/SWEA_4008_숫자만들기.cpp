// 190306
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH&categoryId=AWIeRZV6kBUDFAVH&categoryType=CODE

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int T;
int op[4];
int num[12];
int n, maxAns, minAns;

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int ans = 0;
	
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		vector<int> v;
		scanf("%d", &n);
		for (int i = 0; i < 4; i++) {
			scanf("%d", &op[i]);
			for (int j = 0; j < op[i]; j++) {
				v.push_back(i);
			}
		}
		
		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);
		}
		int count = 0;
		do {
			int temp = num[0];
			for (int i = 0; i < n - 1; i++) {
				if (v[i] == 0) { // 더하기
					temp += num[i + 1];
				}
				else if (v[i] == 1) { // 빼기
					temp -= num[i + 1];
				}
				else if (v[i] == 2) { // 곱하기
					temp *= num[i + 1];
				}
				else { // 나누기
					temp /= num[i + 1];
				}
			}
			if (count == 0) {
				maxAns = temp;
				minAns = temp;
			}
			if (maxAns < temp) maxAns = temp;
			if (minAns > temp) minAns = temp;
			count++;
		} while (next_permutation(v.begin(), v.end()));

		ans = maxAns - minAns;
		printf("#%d %d\n", tc, ans);
		vector<int>().swap(v);
	}

	return 0;
}