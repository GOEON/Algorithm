// 190306
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH&categoryId=AWIeUtVakTMDFAVH&categoryType=CODE

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int a[16][16];

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int T;
	int n;
	int ans;
	int sum0 = 0;
	int sum1 = 0;
	int count = 0;

	scanf("%d", &T);
	
	for (int t = 1; t <= T; t++) {
		ans = 0;
		count = 0;
		scanf("%d", &n);
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
			}
		}

		for (int i = 0; i < n / 2; i++) {
			v[n / 2 + i] = 1;
		}
		
		do {
			sum0 = 0;
			sum1 = 0;
			vector<int> v1;
			vector<int> v2;
			for (int i = 0; i < n; i++) {
				if (v[i] == 0) {
					v1.push_back(i);
				}
				else {
					v2.push_back(i);
				}
			}

			for (int i = 0; i < n / 2; i++) {
				for (int j = i + 1; j < n / 2; j++) {
					sum0 += a[v1[i]][v1[j]] + a[v1[j]][v1[i]];
					sum1 += a[v2[i]][v2[j]] + a[v2[j]][v2[i]];
				}
			}

			int temp;
			if (count == 0) {
				ans = sum0 - sum1;
				if (ans < 0) ans = -ans;
			}
			else {
				temp = sum0 - sum1;
				if (temp < 0) temp = -temp;
				if (ans > temp) ans = temp;
			}
			//vector<int>().swap(v1);
			//vector<int>().swap(v2);
			v1.clear();
			v2.clear();
			
			count++;
		} while (next_permutation(v.begin(), v.end()));


		vector<int>().swap(v);
		printf("#%d %d\n", t, ans);
	}


	return 0;
}