// 190219
// https://www.acmicpc.net/problem/10974

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int nxt_perm(vector<int> &v) // next permutation
{
	// a[i-1] < a[i]�� �����ϴ� ���� ū i ã�� 
	int i = n - 1;
	while (i > 0 && v[i - 1] >= v[i]) i -= 1;
	if (i <= 0) return 0;

	// j>=i �鼭 a[j] > a[i-1]�� �����ϴ� ���� ū j ã��
	int j = n - 1;
	while (v[j] <= v[i - 1]) j -= 1;

	// a[j] <-> a[i-1]
	swap(v[i - 1], v[j]);

	// i ���� ������ ���� ������ 
	j = n - 1;
	while (j >= i) {
		swap(v[i], v[j]);
		i += 1;
		j -= 1;
	}

	return 1;
}
int main()
{
	vector<int> v;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		v.push_back(i + 1);
	}
	do {
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
	} while (nxt_perm(v));

	return 0;
}