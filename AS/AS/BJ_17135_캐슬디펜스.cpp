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
	// �� �Ʒ� �� 
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
		score += 1; // ����
		temp -= 1; // ����忡�� ��
		b[n][sj] = -1; // ���������� ǥ��
		return;
	}

	int r;
	int c;

	// d >= 2
	for (int k = 2; k <= d; k++) {
		r = n;
		c = sj - k + 1; // ������

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
			if (b[r][c] == -1) return; // �����Ÿ� �� �ε� �̹� ���� ���ݼ��� ������ 
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
	cnt = 1; // ���� row
	score = 0; // ���� ���� ��
	temp = total; // temp �� map�� ���� �ִ� ���� ��
	while (1) { // map �� ������ ���� ������ ��� 
		sniper(s1); // �������� 1�� ����
		sniper(s2); // �������� 2�� ����
		sniper(s3); // �������� 3�� ����
		drop(); // ���� �����ϸ鼭 ó��
		cnt += 1; // ��ĭ ���� ǥ��
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
				memcpy(b, a, sizeof(a)); // map ����
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