// 190219
// https://www.acmicpc.net/problem/10972

#include <cstdio>
#include <vector>
using namespace std;

int n;

int nxt_perm(vector<int> &v) // next permutation
{
	// a[i-1] < a[i]를 만족하는 가장 큰 i 찾기 
	int ii = -1;
	for (int i = 1; i < n; i++) {
		if (v[i - 1] < v[i]) {
			ii = i;
		}
	}
	if (ii == -1) return 0;

	// j>=i 면서 a[j]>a[i-1]을 만족하는 가장 큰 j 찾기
	int jj = -1;
	for (int j = ii; j < n; j++) {
		if (v[j] > v[ii - 1]) {
			jj = j;
		}
	}

	// a[j] <-> a[i-1]
	int temp = v[jj];
	v[jj] = v[ii - 1];
	v[ii - 1] = temp;

	// i 부터 끝까지 순열 뒤집기 
	int i = 0;
	while (ii + i <= (n - 1 - i)) {
		int temp = v[ii + i];
		v[ii + i] = v[n - 1 - i];
		v[n - 1 - i] = temp;
		i++;
	}

	return 1;
}
int main()
{
	vector<int> v;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		v.push_back(num);
	}
	if (nxt_perm(v)) { // 다음 순열 출력 
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
	}
	else { // 마지막일 때 -1 출력 
		printf("-1\n");
	}

	return 0;
}