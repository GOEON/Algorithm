// 190219
// https://www.acmicpc.net/problem/10973

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int prev_perm(vector<int> &v) // previous permutation
{
	// a[i-1] > a[i]�� �����ϴ� ���� ū i ã�� 
	int i = n - 1;
	while (i > 0 && v[i - 1] <= v[i]) i -= 1;
	if (i <= 0) return 0;

	// j>=i �鼭 a[j] < a[i-1]�� �����ϴ� ���� ū j ã��
	int j = n - 1;
	while (v[j] >= v[i - 1]) j -= 1;

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
		int num;
		scanf("%d", &num);
		v.push_back(num);
	}
	if (prev_perm(v)) { // ���� ���� ��� 
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
	}
	else { // �������� �� -1 ��� 
		printf("-1\n");
	}

	return 0;
}