// 190403
// https://www.acmicpc.net/problem/14500

#include <iostream>
using namespace std;

int n, m;
int a[500][500];

int dr[] = { -1, 1, 0, 0, -1, -1};
int dc[] = { 0, 0, -1, 1, -1, 1 };

int shape[19][3] = {
	{3, 3, 3}, {1, 1, 1}, {3, 1, 2}, {1, 1, 3}, {0, 3, 3}, 
	{1, 1, 2}, {1, 3, 3}, {1, 3, 1}, {3, 0, 3}, {1, 1, 4}, 
	{3, 3, 4}, {1, 1, 5}, {3, 1, 5}, {3, 1, 1}, {1, 2, 2}, 
	{2, 1, 1}, {3, 3, 1}, {1, 2, 1}, {3, 1, 3}
};

int ans;

int check(int i, int j)
{
	int maxT = 0;
	int temp;
	for (int k = 0; k < 19; k++) {
		temp = a[i][j];
		int cr = i; int cc = j;
		for (int h = 0; h < 3; h++) {
			cr += dr[shape[k][h]]; cc += dc[shape[k][h]];
			if (cr < 0 || cc < 0 || cr >= n || cc >= m) {
				temp = 0;
				break;
			}
			temp += a[cr][cc];
		}
		if (maxT < temp) maxT = temp;
	}
	return maxT;
}

void play()
{
	int temp;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			temp = check(i, j);
			if (ans < temp) ans = temp;
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	play();

	cout << ans << '\n';

	return 0;
}