// 190328
// https://www.acmicpc.net/problem/16927

#include <iostream>
using namespace std;

int n, m, r;
int rsize;
bool c[301][301];
int a[301][301];
int order[1200];
pair<pair<int, int>, int> coord[1200];

int di[] = { 1,0,-1,0 }; // ����, �� �� �� ��
int dj[] = { 0,1,0,-1 };

void getOrder(pair<int, int> s)
{
	int i = s.first;
	int j = s.second;

	int stti = i;
	int dsti = n - i + 1;
	int sttj = j;
	int dstj = m - j + 1;
	int d = 0;

	rsize = 0;

	while (1) {
		order[rsize] = a[i][j];
		if (i == stti && j == sttj) coord[rsize] = { { i, j }, 0 };
		else if (i == dsti && j == sttj) coord[rsize] = { { i, j }, 1 };
		else if (i == dsti && j == dstj) coord[rsize] = { { i, j }, 2 };
		else if (i == stti && j == dstj) coord[rsize] = { { i, j }, 3 };
		else coord[rsize] = { { i, j }, d };
		
		i += di[d];
		j += dj[d];
		if (i > dsti) i = dsti, d = 1, j = sttj + 1; 
		else if (j > dstj) j = dstj, d = 2, i = dsti - 1; 
		else if (i < stti) i = stti, d = 3, j = dstj - 1;
		else if (j < sttj) j = sttj, d = 0, i = stti + 1;
		rsize += 1;
		if (i == stti && j == sttj) break;
	}
}

void revolution(pair<int, int> s)
{
	int size = r % rsize;
	int d, i, j;
	int stti, dsti, sttj, dstj;
	
	i = coord[size].first.first;
	j = coord[size].first.second;
	d = coord[size].second;

	stti = s.first;
	dsti = n - s.first + 1;
	sttj = s.second;
	dstj = m - s.second + 1;

	int idx = 0;

	while (idx < rsize) { // ����

		int temp = order[idx];

		a[i][j] = temp;
		c[i][j] = true;

		i += di[d];
		j += dj[d];
		if (i > dsti) i = dsti, d = 1, j = sttj + 1;
		else if (j > dstj) j = dstj, d = 2, i = dsti - 1;
		else if (i < stti) i = stti, d = 3, j = dstj - 1;
		else if (j < sttj) j = sttj, d = 0, i = stti + 1;
		idx += 1;
	}
}

void counter_clock_wise()
{
	pair<int, int> s;
	int i = 1;
	while (1) {
		s = { i,i }; // ������
		if (c[i][i]) break;
		getOrder(s); // �ű� ��ǥ�� ť�� ����
		revolution(s);
		i += 1;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}

	counter_clock_wise();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}