// 190402
// https://www.acmicpc.net/problem/13460

#include <iostream>
#include <set>
#include <queue>
using namespace std;

bool ok;
int n, m, ans;
char a[10][10];

pair<int, int> red;
pair<int, int> blue;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

set<pair<pair<int, int>, pair<int, int>>> S; // Red, Blue
queue<pair<int, int>> q; // red, blue 순 

int first_second(int k)
{
	if (k == 0) return red.first <= blue.first ? 1 : 0;
	else if (k == 1) return red.first >= blue.first ? 1 : 0;
	else if (k == 2) return red.second <= blue.second ? 1 : 0;
	else if (k == 3) return red.second >= blue.second ? 1 : 0;
}

bool red_move(int k) // 1 리턴시 구멍에 빠짐
{
	int nr = red.first;
	int nc = red.second;

	while (1) {
		nr += dr[k], nc += dc[k];
		if (nr == 0 || nc == 0 || nr == n - 1 || nc == m - 1 || a[nr][nc] == '#' || a[nr][nc] == 'B') {
			red = { nr - dr[k], nc - dc[k]};
			a[red.first][red.second] = 'R';
			return 0;
		}
		if (a[nr][nc] == 'O') return 1;
	}
}

bool blue_move(int k)
{
	int nr = blue.first;
	int nc = blue.second;

	while (1) {
		nr += dr[k], nc += dc[k];
		if (nr == 0 || nc == 0 || nr == n - 1 || nc == m - 1 || a[nr][nc] == '#' || a[nr][nc] == 'R') {
			blue = { nr - dr[k], nc - dc[k] };
			a[blue.first][blue.second] = 'B';
			return 0;
		}
		if (a[nr][nc] == 'O') return 1;
	}
}

void play()
{
	ok = false;
	ans = 0;
	int cnt = 1;
	
	while (!q.empty()) {
		int size = q.size() / 2;
		for (int i = 0; i < size; i++) {
			red = q.front();
			q.pop();
			blue = q.front();
			q.pop();
			pair<int, int> fr = red;
			pair<int, int> fb = blue;
			for (int k = 0; k < 4; k++) {
				red = fr;
				blue = fb;
				bool rr;
				bool rb;
				int ret = first_second(k); // red 먼저면 1, blue 먼저면 0
				
				if (ret == 1) { // red 먼저
					rr = red_move(k);
					rb = blue_move(k);
					if (rr == true) {
						if (rb == false) {
							ok = true;
							ans = cnt;
							return;
						}
						else {
							a[red.first][red.second] = '.';
							a[blue.first][blue.second] = '.';
							continue;
						}
					}
					if (rb == true) {
						a[red.first][red.second] = '.';
						a[blue.first][blue.second] = '.';
						continue;
					}

					if (S.find({ red, blue }) != S.end()) {
						a[red.first][red.second] = '.';
						a[blue.first][blue.second] = '.';
						continue;
					}

					S.insert({ red, blue });
					q.push(red);
					q.push(blue);
					a[red.first][red.second] = '.';
					a[blue.first][blue.second] = '.';
				}
				else { // blue 먼저 
					rb = blue_move(k);
					rr = red_move(k);
					if (rr == true) {
						if (rb == false) {
							ok = true;
							ans = cnt;
							return;
						}
						else {
							a[red.first][red.second] = '.';
							a[blue.first][blue.second] = '.';
							continue;
						}
					}
					if (rb == true) {
						a[red.first][red.second] = '.';
						a[blue.first][blue.second] = '.';
						continue;
					}

					if (S.find({ red, blue }) != S.end()) {
						a[red.first][red.second] = '.';
						a[blue.first][blue.second] = '.';
						continue;
					}

					S.insert({ red, blue });
					q.push(red);
					q.push(blue);
					a[red.first][red.second] = '.';
					a[blue.first][blue.second] = '.';
				}
			}
		}
		cnt += 1;
		if (cnt == 11) return;
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
			if (a[i][j] == 'R') red.first = i, red.second = j, a[i][j] = '.';
			else if(a[i][j] == 'B') blue.first = i, blue.second = j, a[i][j] = '.';
		}
	}
	S.insert({ red, blue });
	q.push(red);
	q.push(blue);

	play();

	if (ok) cout << ans << '\n';
	else cout << -1 << '\n';

	return 0;
}