// 190402
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&categoryId=AWXRQm6qfL0DFAUo&categoryType=CODE&&&

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int T, ans;
int n, w, h;
int temp2, total;

int a[15][12];

queue<pair<pair<int, int>, int>> q; // 좌표, impact

void copy(int (*from)[12], int(*to)[12])
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			from[i][j] = to[i][j];
}

int findBrick(int j)
{
	for (int i = 0; i < h; i++)
		if (a[i][j] != 0)
			return i;
	return -1; // 벽돌 없을 시 
}

void bomb(pair<int, int> brick)
{
	while (!q.empty()) {
		auto au = q.front();
		q.pop();

		int impact = au.second;

		// 상
		for (int i = au.first.first - 1; i >= au.first.first - impact + 1; i--) {
			if (i < 0) break;
			if (a[i][au.first.second] == 0) continue;
			if (a[i][au.first.second] == 1) {
				temp2 += 1;
				a[i][au.first.second] = 0;
			}
			else {
				int ipt = a[i][au.first.second];
				a[i][au.first.second] = 0;
				temp2 += 1;
				q.push({ {i, au.first.second}, ipt });
			}
		}

		// 하
		for (int i = au.first.first + 1; i < au.first.first + impact; i++) {
			if (i >= h) break;
			if (a[i][au.first.second] == 0) continue;
			if (a[i][au.first.second] == 1) {
				temp2 += 1;
				a[i][au.first.second] = 0;
			}
			else {
				int ipt = a[i][au.first.second];
				a[i][au.first.second] = 0;
				temp2 += 1;
				q.push({ {i, au.first.second}, ipt });
			}
		}

		// 좌
		for (int j = au.first.second - 1; j >= au.first.second - impact + 1; j--) {
			if (j < 0) break;
			if (a[au.first.first][j] == 0) continue;
			if (a[au.first.first][j] == 1) {
				temp2 += 1;
				a[au.first.first][j] = 0;
			}
			else {
				int ipt = a[au.first.first][j];
				a[au.first.first][j] = 0;
				temp2 += 1;
				q.push({ {au.first.first, j}, ipt });
			}
		}

		// 우
		for (int j = au.first.second + 1; j < au.first.second + impact; j++) {
			if (j >= w) break;
			if (a[au.first.first][j] == 0) continue;
			if (a[au.first.first][j] == 1) {
				temp2 += 1;
				a[au.first.first][j] = 0;
			}
			else {
				int ipt = a[au.first.first][j];
				a[au.first.first][j] = 0;
				temp2 += 1;
				q.push({ {au.first.first, j}, ipt });
			}
		}
	}
}

void dropBricks()
{
	int tmp[15];
	int idx;
	for (int j = 0; j < w; j++) {
		idx = 0;
		for (int i = h - 1; i >= 0; i--) { // tmp 저장
			if (a[i][j] != 0) tmp[idx++] = a[i][j], a[i][j] = 0;
		}

		for (int i = 0; i < idx; i++) { // 벽돌 떨어뜨리기
			a[h - i - 1][j] = tmp[i];
		}
	}
}

void dfs(int d)
{
	if (d == n) { // 종료
		if (ans < temp2) ans = temp2;
		return;
	}

	int b[15][12];
	int cnt = 0;
	copy(b, a);
	int temp1 = temp2;
	for (int j = 0; j < w; j++) {
	
		int brick = findBrick(j); // 가장 위에 있는 brick 위치
		if (brick == -1) {
			cnt += 1;
			continue; // 벽돌 없을 시 
		}

		// 자신
		int impact = a[brick][j];
		a[brick][j] = 0;
		temp2 += 1;
		if (impact == 1) dfs(d + 1);

		q.push({ { brick, j }, impact });
		bomb({ brick, j }); // 상, 하, 좌, 우 터뜨림

		dropBricks();

		dfs(d + 1);
		temp2 = temp1;
		copy(a, b);
	}
	// 종료 하기 추가해줄것 
	if (cnt == w) {
		dfs(d + 1);
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		temp2 = 0;
		total = 0;
		memset(a, 0, sizeof(a));
		cin >> n >> w >> h;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> a[i][j];
				if (a[i][j] != 0) total += 1;
			}
		}
		dfs(0);
		cout << "#" << tc << " " << total - ans << '\n';
	}

	return 0;
}