// 190407
// https://www.acmicpc.net/problem/17135

#include <iostream>
#include <cstring>
using namespace std;

int total, ans;
int n, m, d, cnt;
int a[16][16];
int b[16][16];
int temp, score;

void drop()
{
	// 맨 아래 줄 
	for (int j = 1; j <= m; j++) {
		if (b[n][j] == 1) temp -= 1;
		b[n][j] = 0;
	}

	for (int j = 1; j <= m; j++) {
		for (int i = n; i > cnt; i--) {
			if (b[i - 1][j] == -1) {
				b[i - 1][j] = 0;
			}
			else {
				b[i][j] = b[i - 1][j];
				b[i - 1][j] = 0;
			}
		}
	}
}

void sniper(int sj)
{
	// d == 1
	if (b[n][sj] == -1) return;
	if (b[n][sj] == 1) {
		score += 1; // 맞춤
		temp -= 1; // 경기장에서 뺌
		b[n][sj] = -1; // 죽은놈으로 표시
		return;
	}

	int r;
	int c;

	// d >= 2
	for (int k = 2; k <= d; k++) {
		r = n;
		c = sj - k + 1; // 시작점

		for (int h = 0; h < 2 * k - 1; h++) {
			if (r < 1 || c < 1 || r > n || c > m) {
				c += 1;
				if (h + 1 < k) {
					r -= 1;
				}
				else {
					r += 1;
				}
				continue;
			}
			if (b[r][c] == -1) return; // 사정거리 안 인데 이미 이전 저격수가 저격함 
			if (b[r][c] == 1) {
				score += 1;
				temp -= 1;
				b[r][c] = -1;
				return;
			}
			c += 1;
			if (h + 1 < k) {
				r -= 1;
			}
			else {
				r += 1;
			}
		}
	}
}

void play(int s1, int s2, int s3)
{
	cnt = 1; // 시작 row
	score = 0; // 죽인 병사 수
	temp = total; // temp 는 map에 남아 있는 병사 수
	while (1) { // map 에 적병이 남아 있으면 계속 
		sniper(s1); // 스나이퍼 1이 저격
		sniper(s2); // 스나이퍼 2가 저격
		sniper(s3); // 스나이퍼 3이 저격
		drop(); // 적병 전진하면서 처리
		cnt += 1; // 한칸 내림 표시
		if (temp <= 0) {
			if (ans < score) ans = score;
			break;
		}
	}
}

void simulation()
{
	ans = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = i + 1; j <= m; j++) {
			for (int k = j + 1; k <= m; k++) {
				memcpy(b, a, sizeof(a)); // map 복사
				play(i, j, k);
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> n >> m >> d;
	total = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 1) total += 1;
		}
	}

	simulation();
	cout << ans << '\n';
	return 0;
}