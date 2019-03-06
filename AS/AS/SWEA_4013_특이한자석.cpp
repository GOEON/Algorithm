// 190306
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH&categoryId=AWIeV9sKkcoDFAVH&categoryType=CODE

#include <cstdio>
using namespace std;

int a[4][8];
int revolution[4];
int T;
int k;


void revolve(int num, int d)
{
	revolution[num] = d;
	// 왼쪽 톱니 회전검사 
	for (int i = num; i > 0; i--) {
		if (a[i][6] != a[i - 1][2]) {
			revolution[i - 1] = -revolution[i];
		}
		else { 
			for (int ii = i - 1; ii >= 0; ii--) {
				revolution[ii] = 0;
			}
			break;
		}
	}
	// 오른쪽 톱니 회전검사 
	for (int i = num; i < 3; i++) {
		if (a[i][2] != a[i + 1][6]) {
			revolution[i + 1] = -revolution[i];
		}
		else {
			for (int ii = i + 1; ii < 4; ii++) {
				revolution[ii] = 0;
			}
			break;
		}
	}
	// 회전 
	for (int i = 0; i < 4; i++) {
		if (revolution[i] == 1) { // 시계
			int temp = a[i][7];
			for (int j = 7; j > 0; j--) {
				a[i][j] = a[i][j - 1];
			}
			a[i][0] = temp;
		}
		else if (revolution[i] == -1) { // 반시계
			int temp = a[i][0];
			for (int j = 0; j < 7; j++) {
				a[i][j] = a[i][j + 1];
			}
			a[i][7] = temp;
		}
	}
}

int main()
{
	int ans = 0;
	int num, d; 
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &k);
		ans = 0;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				scanf("%d", &a[i][j]);
			}
		}

		for (int i = 0; i < k; i++) {
			scanf("%d %d", &num, &d);
			revolve(num - 1, d);
		}

		ans = a[0][0] + a[1][0] * 2 + a[2][0] * 4 + a[3][0] * 8;
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}