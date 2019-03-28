// 190328
// https://www.acmicpc.net/problem/16935

#include <iostream>
#include <algorithm>
using namespace std;

int n, m, r, mode;
int a[101][101];
int b[101][101];

void updown()
{
	int tmp[101];
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) tmp[n - i + 1] = a[i][j];
		for (int i = 1; i <= n; i++) a[i][j] = tmp[i];
	}
}


void leftright()
{
	int tmp[101];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) tmp[m - j + 1] = a[i][j];
		for (int j = 1; j <= m; j++) a[i][j] = tmp[j];
	}
}

void cw()
{
	int tmp[101];
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) tmp[j] = a[n - j + 1][i];
		for (int j = 1; j <= n; j++) b[i][j] = tmp[j];
	}
	swap(n, m);
	swap(a, b);
}

void ccw()
{
	int tmp[101];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) tmp[j] = a[i][m - j + 1];
		for (int j = 1; j <= m; j++) b[j][i] = tmp[j];
	}
	swap(n, m);
	swap(a, b);
}

void scw()
{
	int tmp[51][51];

	int di[] = { 0, 0, n / 2, n / 2 };
	int dj[] = { 0, m / 2, m / 2, 0 };

	for (int k = 0; k < 4; k++) {
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				tmp[i][j] = a[i + di[k]][j + dj[k]];
			}
		}
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				b[i + di[(k + 1) % 4]][j + dj[(k + 1) % 4]] = tmp[i][j];
			}
		}
	}
	swap(a, b);
}

void sccw()
{
	int tmp[51][51];

	int di[] = { 0, n / 2, n / 2, 0 };
	int dj[] = { 0, 0, m / 2, m / 2 };

	for (int k = 0; k < 4; k++) {
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				tmp[i][j] = a[i + di[k]][j + dj[k]];
			}
		}
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				b[i + di[(k + 1) % 4]][j + dj[(k + 1) % 4]] = tmp[i][j];
			}
		}
	}

	swap(a, b);
}

void revolution(int mode)
{
	if (mode == 1) updown();
	else if (mode == 2) leftright();
	else if (mode == 3) cw(); // clock-wise
	else if (mode == 4) ccw(); // counter-clock-wise
	else if (mode == 5) scw(); // sub clock-wise
	else if (mode == 6) sccw();// sub counter-clock-wise
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];

	for (int i = 0; i < r; i++) {
		cin >> mode;
		revolution(mode);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}