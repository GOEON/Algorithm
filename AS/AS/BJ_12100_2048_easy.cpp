// 190401
// https://www.acmicpc.net/problem/12100

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, ans;

int a[20][20];
int b[20][20];

int cnt;

void up()
{
	queue<int> q;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			if (a[i][j] != 0) {
				q.push(a[i][j]);
				a[i][j] = 0;
			}
		}

		int idx = 0;
		while (!q.empty()) {
			int temp = q.front();
			q.pop();

			if (a[idx][j] == 0) a[idx][j] = temp;
			else if (a[idx][j] == temp) a[idx][j] *= 2, idx += 1, cnt += 1;
			else if (a[idx][j] != temp) idx += 1, a[idx][j] = temp;
		}
	}
}

void down()
{
	queue<int> q;
	for (int j = 0; j < n; j++) {
		for (int i = n - 1; i >= 0; i--) {
			if (a[i][j] != 0) {
				q.push(a[i][j]);
				a[i][j] = 0;
			}
		}

		int idx = n - 1;
		while (!q.empty()) {
			int temp = q.front();
			q.pop();

			if (a[idx][j] == 0) a[idx][j] = temp;
			else if (a[idx][j] == temp) a[idx][j] *= 2, idx -= 1, cnt += 1;
			else if (a[idx][j] != temp) idx -= 1, a[idx][j] = temp;
		}
	}
}

void left()
{
	queue<int> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != 0) {
				q.push(a[i][j]);
				a[i][j] = 0;
			}
		}

		int idx = 0;
		while (!q.empty()) {
			int temp = q.front();
			q.pop();

			if (a[i][idx] == 0) a[i][idx] = temp;
			else if (a[i][idx] == temp) a[i][idx] *= 2, idx += 1, cnt += 1;
			else if (a[i][idx] != temp) idx += 1, a[i][idx] = temp;
		}
	}
}

void right()
{
	queue<int> q;
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			if (a[i][j] != 0) {
				q.push(a[i][j]);
				a[i][j] = 0;
			}
		}

		int idx = n - 1;
		while (!q.empty()) {
			int temp = q.front();
			q.pop();

			if (a[i][idx] == 0) a[i][idx] = temp;
			else if (a[i][idx] == temp) a[i][idx] *= 2, idx -= 1, cnt += 1;
			else if (a[i][idx] != temp) idx -= 1, a[i][idx] = temp;
		}
	}
}

void copy_to(int (*to)[20])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			to[i][j] = a[i][j];
		}
	}
}

void copy_from(int (*from)[20])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = from[i][j];
		}
	}
}

void dfs(int h)
{
	if (h == 5) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ans < a[i][j]) ans = a[i][j];
			}
		}
		return;
	}

	int b[20][20];
	copy_to(b);

	for (int k = 0; k < 4; k++) {
		cnt = 0;
		if (k == 0) up();
		else if (k == 1) down();
		else if (k == 2) left();
		else if (k == 3) right();
		dfs(h + 1);
		copy_from(b);
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ans = 0;

	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];

	dfs(0);

	cout << ans << endl;

	return 0;
}