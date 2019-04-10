#include <iostream>
#include <cstring>
using namespace std;

int ans, cnt;
int grpIdx;
int grp[12][6];
int member[81]; // 0Àº dummy 

bool ok;

char map[12][6];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void dfs(int si, int sj) 
{
	int cr = si;
	int cc = sj;
	char color = map[cr][cc];

	if (member[grp[cr][cc]] >= 4) ok = true;

	for (int k = 0; k < 4; k++) {
		int nr = cr + dr[k];
		int nc = cc + dc[k];

		if (nr < 0 || nc < 0 || nr >= 12 || nc >= 6) continue;
		if (grp[nr][nc] > 0) continue;
		if (map[nr][nc] == '.') continue;
		if (map[nr][nc] != color) continue;
		grp[nr][nc] = grpIdx;
		member[grpIdx] += 1;
		dfs(nr, nc);
	}
}

void drop()
{
	char tmp[12];
	int idx;
	for (int j = 0; j < 6; j++) {
		idx = 0;
		for (int i = 11; i >= 0; i--) {
			if (map[i][j] != '.') {
				tmp[idx++] = map[i][j];
				map[i][j] = '.';
			}
		}

		for (int i = 0; i < idx; i++) {
			map[11 - i][j] = tmp[i];
		}
	}
}

void bomb()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (grp[i][j] == 0) continue;
			if (member[grp[i][j]] >= 4) {
				map[i][j] = '.';
			}
		}
	}
}

void play()
{
	while (1) {
		grpIdx = 1;
		ok = false;
		memset(grp, 0, sizeof(grp));
		memset(member, 0, sizeof(member));
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] == '.' || grp[i][j] > 0) continue;
				member[grpIdx] += 1;
				grp[i][j] = grpIdx;
				dfs(i, j);
				grpIdx++;
			}
		}
		if (grpIdx) {
			bomb();
			drop();
			ans += 1;
		}
		else {
			break;
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	ans = 0;

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 6; j++)
			cin >> map[i][j];

	play();
	cout << ans << '\n';

	return 0;
}