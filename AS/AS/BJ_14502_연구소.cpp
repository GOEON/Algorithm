// 190404
// https://www.acmicpc.net/problem/14502

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int a[9][9];
int b[9][9];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int total;
int ans;

vector < pair<int, int>> v;
queue<pair<int, int>> q;


int spread()
{
	queue<pair<int, int>> q2 = q;
	int ret = 0;
	while (!q2.empty()) {
		int cr = q2.front().first;
		int cc = q2.front().second;
		q2.pop();

		for (int k = 0; k < 4; k++) {
			int nr = cr + dr[k];
			int nc = cc + dc[k];

			if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
			if (b[nr][nc] == 1 || b[nr][nc] == 2) continue;

			b[nr][nc] = 2; ret += 1;
			q2.push({ nr,nc });
		}
	}
	return ret;
}

void virus()
{
	vector <int> v2(v.size());
	v2[v2.size() - 1] = 1; v2[v2.size() - 2] = 1; v2[v2.size() - 3] = 1;
	total -= 3;

	ans = 0;
	do {
		memcpy(b, a, sizeof(a));
		for (int i = 0; i < v2.size(); i++) {// 벽 세개 정하기
			if (v2[i] == 1) {
				b[v[i].first][v[i].second] = 1;
			}
		}

		int temp = spread(); // 바이러스 퍼뜨리기
		if (ans < total - temp) ans = total - temp;
	} while (next_permutation(v2.begin(), v2.end()));
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 0) {
				v.push_back({ i,j });
				total += 1;
			}
			else if (a[i][j] == 2) {
				q.push({ i,j });
			}
		}
	}
	
	virus();
	cout << ans << '\n';

	return 0;
}