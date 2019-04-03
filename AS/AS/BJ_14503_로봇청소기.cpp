// 190404
// https://www.acmicpc.net/problem/14503

#include <iostream>
using namespace std;

int dr[] = { -1,0,1,0 };
int dc[] = { 0,1,0,-1 };

int n, m;
int ans;
int r, c, d;

int a[50][50];

void cleaning()
{
	bool ok;
	while (1) {

		// û��
		if (a[r][c] == 0) {
			a[r][c] = 2; // ���� ���� û��
			ans += 1;
		}
		int cd = d;
		ok = true;

		for (int k = 0; k < 4; k++) {
			cd -= 1;
			if (cd == -1) cd = 3;
			int nr = r + dr[cd];
			int nc = c + dc[cd];

			if (a[nr][nc] == 1 || a[nr][nc] == 2) continue; // ���̳� û���ߴٸ� 

			d = cd;
			r = nr; c = nc;
			ok = false;
			break;
		}

		if (ok) { // �� ���� û���� �� ���� ���
			int rd = (d + 2) % 4; // ���� ����
			int nr = r + dr[rd];
			int nc = c + dc[rd];
			if (a[nr][nc] == 1) break; // �ڷ� �̵��� �� ������ ����
			r = nr; c = nc; // �ڷ� �̵�
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ans = 0;
	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	cleaning();

	cout << ans << '\n';
	return 0;
}