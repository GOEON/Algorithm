// 190404
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu&categoryId=AV5VwAr6APYDFAWu&categoryType=CODE

#include <iostream>
#include <cstring>
using namespace std;

bool ll;
bool rr;

int T, ans;
int n, r, c;
int sr, sc;
int a[20][20];
bool visit[20][20];
bool disert[101];

int dr[] = { -1, 1, 1, -1 };
int dc[] = { -1, -1, 1, 1 };

void dfs(int r_cnt, int d_cnt, int d)
{
	if (r_cnt > 3) return;
	if (r == sr && c == sc && r_cnt == 3) { // 종료
		if (ans < d_cnt) ans = d_cnt;
		return;
	}

	if (r < 0 || c < 0 || r >= n || c >= n) { // 범위 벗어날 경우
		return;
	}
	else if (visit[r][c] || disert[a[r][c]]) { // 방문한 적 있거나 먹었던 디저트
		return;
	}

	for (int i = 0; i < 2; i++) { // 방향 유지, 왼쪽
		if (i == 1) {
			d -= 1; if (d == -1) d = 3;
			r_cnt += 1;
		}

		visit[r][c] = true; disert[a[r][c]] = true;
		r += dr[d]; c += dc[d]; // 이동
		dfs(r_cnt, d_cnt + 1, d);
		r -= dr[d]; c -= dc[d]; // 원위치
		visit[r][c] = false; disert[a[r][c]] = false;
	}
}

void letsgo()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 네 꼭지점은 시작점에서 제외 
			if (i == 0 && j == 0) continue;
			else if (i == 0 && j == n - 1) continue;
			else if (i == n - 1 && j == 0) continue;
			else if (i == n - 1 && j == n - 1) continue;

			for (int d = 0; d < 4; d++) { // 시작 방향 
				sr = r = i, sc = c = j;
				visit[i][j] = true; disert[a[i][j]] = true;
				r += dr[d]; c += dc[d]; // 이동
				dfs(0, 1, d);
				visit[i][j] = false; disert[a[i][j]] = false;
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> n;
		ans = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
			}
		}

		letsgo();

		if (ans) cout << "#" << tc << " " << ans << '\n';
		else cout << "#" << tc << " -1" << '\n';
	}
	return 0;
}