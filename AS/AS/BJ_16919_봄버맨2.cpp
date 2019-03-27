// 190327
// 봄버맨이랑 N의 범위가 다른데.. 처음부터 N의 사이즈에 상관없이 풀어서 해결
// https://www.acmicpc.net/problem/16919

#include <iostream>
#include <queue>
using namespace std;

char arr[201][201];
char arr2[201][201];
char arr3[201][201];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int r, c, n;
int t;

queue<pair<int, int>> q;

void func()
{
	for (int i = q.size(); i--;) { // arr2
		auto au = q.front();
		q.pop();

		if (arr2[au.first][au.second] != '.') arr2[au.first][au.second] = '.';
		for (int k = 0; k < 4; k++) {
			int nr = au.first + dr[k];
			int nc = au.second + dc[k];

			if (nr < 1 || nc < 1 || nr > r || nc > c) continue;
			if (arr2[nr][nc] != '.') arr2[nr][nc] = '.';
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (arr2[i][j] != '.') {
				arr2[i][j] = 'O';
				q.push({ i, j });
			}
		}
	}

	for (int i = q.size(); i--;) { // arr3
		auto au = q.front();
		q.pop();

		if (arr3[au.first][au.second] != '.') arr3[au.first][au.second] = '.';
		for (int k = 0; k < 4; k++) {
			int nr = au.first + dr[k];
			int nc = au.second + dc[k];

			if (nr < 1 || nc < 1 || nr > r || nc > c) continue;
			if (arr3[nr][nc] != '.') arr3[nr][nc] = '.';
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (arr3[i][j] != '.') {
				arr3[i][j] = 'O';
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	//freopen("sample_input.txt", "r", stdin);
	cin >> r >> c >> n;
	for (int i = 1; i <= r; i++) {
		cin >> arr[i] + 1;
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (arr[i][j] == 'O') q.push({ i,j });
		}
	}

	func();

	if (n % 2 == 0) {
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				cout << 'O';
			}
			cout << endl;
		}
	}
	else if (n == 1) {
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				cout << arr[i][j];
			}
			cout << endl;
		}
	}
	else if (n % 4 == 3) {
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				cout << arr2[i][j];
			}
			cout << endl;
		}
	}
	else if (n % 4 == 1) {
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				cout << arr3[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}