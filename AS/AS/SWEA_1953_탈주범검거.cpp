// 190403
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpLlKAQ4DFAUq&categoryId=AV5PpLlKAQ4DFAUq&categoryType=CODE

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int ans, T;
int n, m, r, c, l;

bool v[50][50];
int a[50][50];

int timer;

queue<pair<int, int>> q;

int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };

int tunnel[8][4] = {
	{0,0,0,0},
	{1,2,3,4},
	{1,2,0,0},
	{3,4,0,0},
	{1,4,0,0},
	{2,4,0,0},
	{3,2,0,0},
	{1,3,0,0}
};

void move(int cr, int cc)
{
	for (int i = 0; i < 4; i++) {
		if (tunnel[a[cr][cc]][i] == 0) break;
		int nr = cr + dr[tunnel[a[cr][cc]][i]];
		int nc = cc + dc[tunnel[a[cr][cc]][i]];

		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (v[nr][nc]) continue;

		int from = tunnel[a[cr][cc]][i];
		int to = a[nr][nc];

		if (from == 1) {
			if (to == 0 || to == 3 || to == 4 || to == 7) continue;
		}
		else if (from == 2) {
			if (to == 0 || to == 3 || to == 5 || to == 6) continue;
		}
		else if (from == 3) {
			if (to == 0 || to == 2 || to == 6 || to == 7) continue;
		}
		else if (from == 4) {
			if (to == 0 || to == 2 || to == 4 || to == 5) continue;
		}

		v[nr][nc] = true;
		ans += 1;
		q.push({nr, nc});
	}
}

void bfs()
{
	// 맨홀
	timer = 1;
	q.push({ r,c });
	v[r][c] = true;
	ans += 1;
	timer += 1;

	// 지하터널
	while (timer <= l) {
		int size = q.size();
		while (size--) {
			int cr = q.front().first;
			int cc = q.front().second;
			q.pop();

			move(cr, cc);
		}
		timer += 1;
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		memset(v, false, sizeof(v));
		queue < pair<int, int>>().swap(q);
		cin >> n >> m >> r >> c >> l;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> a[i][j];

		bfs();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}