// 190308
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH&categoryId=AWIeW7FakkUDFAVH&categoryType=CODE

#include <cstdio>
#include <cstdlib>
using namespace std;

int n, x;
int a[20][20];

bool isOKWidth(int i)
{
	int same_cnt = 1; // 같은 지형수 
	bool check = false; // 경사로 ↘ 검사 해야 하는지, true면 해야함 
	for (int j = 1; j < n; j++) {
		if (abs(a[i][j] - a[i][j - 1]) >= 2) {
			return false;
		}
		else if (a[i][j] - a[i][j - 1] == 1) { // 경사로 체크 ↗
			if (check || same_cnt < x) {
				return false;
			}
			same_cnt = 1;
		}
		else if(a[i][j] - a[i][j - 1] == -1) { // 경사로 체크 ↘
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
	if (check) return false; // check가 true로 for문이 끝나면 안 됨 
	return true;
}

bool isOKHeight(int j)
{
	int same_cnt = 1; // 같은 지형수 
	bool check = false; // 경사로 ↘ 검사 해야 하는지, true면 해야함 
	for (int i = 1; i < n; i++) {
		if (abs(a[i][j] - a[i - 1][j]) >= 2) {
			return false;
		}
		else if (a[i][j] - a[i - 1][j] == 1) { // 경사로 체크 ↗
			if (check || same_cnt < x) {
				return false;
			}
			same_cnt = 1;
		}
		else if (a[i][j] - a[i - 1][j] == -1) { // 경사로 체크 ↘
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
	if (check) return false; // check가 true로 for문이 끝나면 안 됨 
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
			if (isOKWidth(i)) { // 가로
				ans += 1;
			}
			if (isOKHeight(i)) { // 세로
				ans += 1;
			}
		}

		printf("#%d %d\n", tc, ans);
	}

	return 0;
}