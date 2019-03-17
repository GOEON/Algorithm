// 190317
// https://www.acmicpc.net/problem/16954

#include <cstdio>
#include <queue>
using namespace std;

bool ok = false;
int a[8][8];
int wall[8][8][8];
int dr[] = { 0, -1, 0, -1, 0, -1, 1, 1, 1};
int dc[] = {-1, -1, 0, 0, 1, 1, 1, 0, -1};
queue<pair<int, int>> q; // 벽위치

void dfs(int r, int c, int h)
{
	if (h == 8 || (r == 0 && c == 7)) {
		ok = true;
		return;
	}
	
	if (wall[h][r][c] == 1 && wall[h][r][c] == 1) return;

	for (int k = 0; k < 9; k++) {
		int nr = r + dr[k];
		int nc = c + dc[k];

		if (0 <= nr && nr < 8 && 0 <= nc && nc < 8) {
			if (wall[h][nr][nc] == 0) 
				dfs(nr, nc, h + 1);
		}
	}

}

int main()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			char c;
			scanf(" %c", &c);
			if (c == '.') {
				a[i][j] = 0;
			}
			else {
				a[i][j] = 1;
				q.push({i, j}); // 벽
			}
		}
	}

	for(int h=0; h < 8; h++){
		for (int i = q.size(); i--;) {
			auto w = q.front();
			q.pop();

			wall[h][w.first][w.second] = 1;
			if (w.first + 1 < 8) q.push({ w.first + 1,w.second });
		}
	}

	dfs(7, 0, 0); // 내위치, 벽이 떨어진 횟수 

	if(ok) printf("1\n");
	else printf("0\n");
	return 0;
}