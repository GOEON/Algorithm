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

queue<pair<pair<int, int>, int>> q; // ��ǥ, impact

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
	return -1; // ���� ���� �� 
}

void bomb(pair<int, int> brick)
{
	while (!q.empty()) {
		auto au = q.front();
		q.pop();

		int impact = au.second;

		// ��
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

		// ��
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

		// ��
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

		// ��
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
		for (int i = h - 1; i >= 0; i--) { // tmp ����
			if (a[i][j] != 0) tmp[idx++] = a[i][j], a[i][j] = 0;
		}

		for (int i = 0; i < idx; i++) { // ���� ����߸���
			a[h - i - 1][j] = tmp[i];
		}
	}
}

void dfs(int d)
{
	if (d == n) { // ����
		if (ans < temp2) ans = temp2;
		return;
	}

	int b[15][12];
	int cnt = 0;
	copy(b, a);
	int temp1 = temp2;
	for (int j = 0; j < w; j++) {
	
		int brick = findBrick(j); // ���� ���� �ִ� brick ��ġ
		if (brick == -1) {
			cnt += 1;
			continue; // ���� ���� �� 
		}

		// �ڽ�
		int impact = a[brick][j];
		a[brick][j] = 0;
		temp2 += 1;
		if (impact == 1) dfs(d + 1);

		q.push({ { brick, j }, impact });
		bomb({ brick, j }); // ��, ��, ��, �� �Ͷ߸�

		dropBricks();

		dfs(d + 1);
		temp2 = temp1;
		copy(a, b);
	}
	// ���� �ϱ� �߰����ٰ� 
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