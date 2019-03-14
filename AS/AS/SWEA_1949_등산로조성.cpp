// 190314
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&categoryId=AV5PoOKKAPIDFAUq&categoryType=CODE

#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int n, k;
int T, ans;
bool Kused;
bool check[8][8];
int a[8][8];
int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};
vector<pair<int, int>> v; // 가장 높은 봉우리

void dfs(int r, int c, int h)
{
	for (int ii = 0; ii < 4; ii++) {
		int nr = r + di[ii];
		int nc = c + dj[ii];

		if (0 <= nr && nr < n && 0 <= nc && nc < n) {
			if (check[nr][nc] == false) {
				if (a[r][c] > a[nr][nc]) {
					check[nr][nc] = true;
					dfs(nr, nc, h + 1);
					check[nr][nc] = false;
				}
				else if (Kused == false && a[nr][nc] - k < a[r][c]) {
					Kused = true;
					int copy = a[nr][nc];
					a[nr][nc] = a[r][c] - 1;
					if (a[nr][nc] >= 0) {
						check[nr][nc] = true;
						dfs(nr, nc, h + 1);
						check[nr][nc] = false;
					}
					a[nr][nc] = copy;
					Kused = false;
				}
			}
		}
	}
	
	if (ans < h) ans = h;
	return;
}
void findLongestWay()
{
	int vSize = v.size();
	for (int i = 0; i < vSize; i++) {
		check[v[i].first][v[i].second] = true;
		dfs(v[i].first, v[i].second, 1);
		check[v[i].first][v[i].second] = false;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int maxH = 0;
		ans = 1;
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
				if (maxH < a[i][j]) maxH = a[i][j];
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] == maxH) {
					v.push_back(make_pair(i, j));
				}
			}
		}

		findLongestWay();
		vector<pair<int, int>>().swap(v);
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}