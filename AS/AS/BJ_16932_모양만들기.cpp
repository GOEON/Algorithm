// 190328
// https://www.acmicpc.net/problem/16932

#include <iostream>
#include <set>
#include <queue>
using namespace std;

int n, m, ans;
int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int grp_num, grp_size;
bool visit[1000][1000]; // 방문 체크
int grp[1000][1000]; // 그룹 번호
int a[1000][1000];
int grp_tbl[1000001]; // 그룹의 (idx) 크기 저장 

queue<pair<int, int>> q0;
queue<pair<int, int>> q1;
 
void dfs(int r, int c)
{
	for (int k = 0; k < 4; k++) {
		int nr = r + dr[k];
		int nc = c + dc[k];

		if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
		if (a[nr][nc] == 1 && grp[nr][nc] == 0 && visit[nr][nc] == false) {
			grp_size += 1;
			grp[nr][nc] = grp_num;
			visit[nr][nc] = true;
			dfs(nr, nc);
			visit[nr][nc] = false;
		}
	}
}

void numofone()
{
	grp_num = 1;
	while (!q1.empty()) {
		auto au = q1.front();
		q1.pop();

		grp_size = 1;
		if (grp[au.first][au.second] == 0 && visit[au.first][au.second] == false) {
			grp[au.first][au.second] = grp_num;
			visit[au.first][au.second] = true;
			dfs(au.first, au.second);
			visit[au.first][au.second] = false;
			grp_tbl[grp_num] = grp_size;
			grp_num += 1;
		}
		
	}
}

void zeroToOne()
{
	ans = 0;
	int sub_ans;
	while (!q0.empty()) {
		auto au = q0.front();
		q0.pop();
		sub_ans = 1;
		set<int> S; // 그룹 번호가 사용되었는지 검사
		for (int k = 0; k < 4; k++) {
			int nr = au.first + dr[k];
			int nc = au.second + dc[k];

			if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
			if (a[nr][nc] == 0) continue;

			if (S.find(grp[nr][nc]) == S.end()) {
				S.insert(grp[nr][nc]);
				sub_ans += grp_tbl[grp[nr][nc]];
			}
		}
		if (ans < sub_ans) ans = sub_ans;
		S.clear();
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 0) q0.push({ i, j });
			else q1.push({ i,j });
		}
	}

	numofone(); // 1로 그룹 나눠서 크기 구하기 
	zeroToOne(); // 0의 상하좌우로 그룹 크기 더 해서 답 구하기

	cout << ans << endl;
	return 0;
}