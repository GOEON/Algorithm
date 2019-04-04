#include <iostream>
#include <cstring>
using namespace std;

int ans, T;
int r, c, n;
int a[100][100];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int block[6][4] = { // 도형 번호, 들어오는 방향 output : 나가는 방향 
	{0,0,0,0}, // dummy
	{1,3,0,2},
	{3,0,1,2},
	{2,0,3,1},
	{1,2,3,0},
	{1,0,3,2}
};

struct WH {
	int r1; int c1;
	int r2; int c2;
};

WH wh[11];

int go(int d)
{
	int sr = r;
	int sc = c;

	int score = 0;

	while (1) {
		r += dr[d]; c += dc[d];

		if (r < 0 || c < 0 || r >= n || c >= n) { // 벽
			score += 1;
			d = block[5][d];
		}
		else if (a[r][c] == -1) { // 블랙홀
			break;
		}
		else if (r == sr && c == sc) { // 시작점
			break;
		}
		else if (1 <= a[r][c] && a[r][c] <= 5) { // 도형
			score += 1;
			d = block[a[r][c]][d];
		}
		else if (6 <= a[r][c] && a[r][c] <= 10) { // 웜홀
			int tr = r; int tc = c;
			if (wh[a[tr][tc]].r1 == r && wh[a[tr][tc]].c1 == c) {
				r = wh[a[tr][tc]].r2;
				c = wh[a[tr][tc]].c2;
			}
			else {
				r = wh[a[tr][tc]].r1;
				c = wh[a[tr][tc]].c1;
			}
		}
	}
	return score;
}

void play()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != 0) continue; // 시작점 x
			for (int d = 0; d < 4; d++) {
				r = i; c = j;
				int temp = go(d);
				if (ans < temp) ans = temp;
			}
		}
	}
}


int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(wh, 0, sizeof(wh));
		ans = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				if (6 <= a[i][j] && a[i][j] <= 10) {
					if (wh[a[i][j]].r1 == 0 && wh[a[i][j]].c1 == 0) {
						wh[a[i][j]].r1 = i; wh[a[i][j]].c1 = j;
					}
					else {
						wh[a[i][j]].r2 = i; wh[a[i][j]].c2 = j;
					}
				}
			}
		}

		play();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}