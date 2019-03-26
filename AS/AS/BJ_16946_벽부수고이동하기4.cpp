// 190325
// https://www.acmicpc.net/problem/16946

#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

bool ok;
int n, m;
int a[1001][1001]; // 원본
int g[1001][1001];  // group
int ans[1001][1001];
int grp[500001];

queue<pair<int, int>> q;
queue<pair<int, int>> q2;

int gIdx;
int gNum;

void dfs(pair<int, int> p)
{
	for (int k = 0; k < 4; k++) {
		int ny = p.first + dy[k];
		int nx = p.second + dx[k];

		if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
		if (g[ny][nx] > 0 || a[ny][nx] == 1) continue; // 이미 그룹이 정해짐
		gNum++;
		g[ny][nx] = gIdx;
		dfs({ ny, nx });
	}
}

void groupmatch()
{
	grp[0] = 0; // dummy
	gIdx = 1;
	while (!q.empty()) {
		auto au = q.front();
		q.pop();
		
		if (g[au.first][au.second] > 0) continue;
		gNum = 1;
		g[au.first][au.second] = gIdx;
		dfs(au);
		grp[gIdx++] = gNum;
	}
}

void mapchange()
{
	int sum;
	set<int> S;
	while (!q2.empty()) {
		sum = 1;
		auto au = q2.front();
		q2.pop();

		for (int i = 0; i < 4; i++) {
			int ny = au.first + dy[i];
			int nx = au.second + dx[i];

			if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
			if (a[ny][nx] == 1) continue;

			if (S.find(g[ny][nx]) == S.end()) {
				S.insert(g[ny][nx]);
				sum += grp[g[ny][nx]];
			}
		}
		ans[au.first][au.second] = sum;
		S.clear();
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	ok = false;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1d", &a[i][j]);
			if (a[i][j] == 0) q.push({i, j});
			else q2.push({ i, j });
		}
	}

	groupmatch();
	mapchange();
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ans[i][j] == 0) printf("0");
			else printf("%d", ans[i][j] % 10);
		}
		printf("\n");
	}

	return 0;
}