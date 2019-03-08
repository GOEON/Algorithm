// 190308
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE

#include <cstdio>
#include <cstdlib>
using namespace std;

int n, x;
int a[20][20];

bool isOKWidth(int i)
{
	int same_cnt = 1; // ���� ������ 
	bool check = false; // ���� �� �˻� �ؾ� �ϴ���, true�� �ؾ��� 
	for (int j = 1; j < n; j++) {
		if (abs(a[i][j] - a[i][j - 1]) >= 2) {
			return false;
		}
		else if (a[i][j] - a[i][j - 1] == 1) { // ���� üũ ��
			if (check || same_cnt < x) {
				return false;
			}
			same_cnt = 1;
		}
		else if(a[i][j] - a[i][j - 1] == -1) { // ���� üũ ��
			if (check) return false;
			check = true;
			same_cnt = 1;
		}
		else { // 
			same_cnt += 1;
			if (check) {
				if (same_cnt >= x) {
					check = false;
					same_cnt = 0;
				}
			}
		}
	}
	if (check) return false; // check�� true�� for���� ������ �� �� 
	return true;
}

bool isOKHeight(int j)
{
	int same_cnt = 1; // ���� ������ 
	bool check = false; // ���� �� �˻� �ؾ� �ϴ���, true�� �ؾ��� 
	for (int i = 1; i < n; i++) {
		if (abs(a[i][j] - a[i - 1][j]) >= 2) {
			return false;
		}
		else if (a[i][j] - a[i - 1][j] == 1) { // ���� üũ ��
			if (check || same_cnt < x) {
				return false;
			}
			same_cnt = 1;
		}
		else if (a[i][j] - a[i - 1][j] == -1) { // ���� üũ ��
			if (check) return false;
			check = true;
			same_cnt = 1;
		}
		else { // 
			same_cnt += 1;
			if (check) {
				if (same_cnt >= x) {
					check = false;
					same_cnt = 0;
				}
			}
		}
	}
	if (check) return false; // check�� true�� for���� ������ �� �� 
	return true;
}

int main()
{
	int T;
	int ans = 0;
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		scanf("%d %d", &n, &x);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
			}
		}

		for (int i = 0; i < n; i++) {
			if (isOKWidth(i)) { // ����
				ans += 1;
			}
			if (isOKHeight(i)) { // ����
				ans += 1;
			}
		}

		printf("#%d %d\n", tc, ans);
	}

	return 0;
}