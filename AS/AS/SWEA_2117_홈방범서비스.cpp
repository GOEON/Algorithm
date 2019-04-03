// 190403
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&categoryId=AV5V61LqAf8DFAWu&categoryType=CODE&&&

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int ans, T;
int n, m;
int a[20][20];
int cost[22];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void check(int i, int j)
{
	bool v[20][20]; // 검사했는지 체크 
	memset(v, false, sizeof(v));
	queue<pair<int, int>> q;
	q.push({i, j});

	int k = 2;
	int prev = 0;
	int crnt = 0;

	if (a[i][j] == 1) crnt = 1;
	v[i][j] = true;

	if (ans < crnt) ans = crnt;

	while (k <= n + 1) {
		int temp = 0;
		for (int s = q.size(); s--;) {
			pair<int, int> cp = q.front(); // current position
			q.pop();

			for (int h = 0; h < 4; h++) {
				int nr = cp.first + dr[h];
				int nc = cp.second + dc[h];

				if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
				if (v[nr][nc]) continue;
				
				v[nr][nc] = true;
				if (a[nr][nc] == 1) temp += 1;
				q.push({ nr, nc });
			}
		}
		crnt += temp;
		if (crnt * m >= cost[k]) {
			if (ans < crnt) ans = crnt;
		}
		k += 1;
	}
}

void calCost()
{
	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			check(i, j);
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int i = 1; i <= 21; i++) {
		cost[i] = i * i + (i - 1) * (i - 1);
	}
	for (int tc = 1; tc <= T; tc++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> a[i][j];

		calCost();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}