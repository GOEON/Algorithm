// 190402
// https://www.acmicpc.net/problem/14499

#include <iostream>
#include <queue>
using namespace std;

int n, m, x, y, k;

int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };
int a[20][20];
int dice[6];

queue<int> q; // 움직이는 방향 

bool move(int d)
{
	int nx = x + dx[d];
	int ny = y + dy[d];

	if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
		return false;
	}
	x = nx; y = ny;

	// 주사위 굴리기 (윗면 d[2], 바닥 d[5])
	if (d == 1) { // 우
		int t = dice[2]; dice[2] = dice[1]; 
		dice[1] = dice[5]; dice[5] = dice[3];
		dice[3] = t;
	}
	else if (d == 2) { // 좌
		int t = dice[2]; dice[2] = dice[3];
		dice[3] = dice[5]; dice[5] = dice[1];
		dice[1] = t;
	}
	else if (d == 3) { // 상
		int t = dice[2]; dice[2] = dice[4];
		dice[4] = dice[5]; dice[5] = dice[0];
		dice[0] = t;
	}
	else if (d == 4) { // 하
		int t = dice[2]; dice[2] = dice[0];
		dice[0] = dice[5]; dice[5] = dice[4];
		dice[4] = t;
	}

	if (a[x][y] == 0) a[x][y] = dice[5];
	else dice[5] = a[x][y], a[x][y] = 0;

	return true;
}

void play()
{
	while (!q.empty()) {
		int d = q.front();
		q.pop();

		bool ok = move(d);
		if (ok) cout << dice[2] << '\n';
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> n >> m >> x >> y >> k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	for (int i = 0; i < k; i++) {
		int temp;
		cin >> temp;
		q.push(temp);
	}
	
	play();

	return 0;
}