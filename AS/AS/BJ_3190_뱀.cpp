// 190402
// https://www.acmicpc.net/problem/3190

#include <iostream>
#include <queue>
using namespace std;

int n, k, l;
int a[102][102];
int dr[] = { 0, 0, 1, 0, -1 };
int dc[] = { 0, 1, 0, -1, 0 };

int ar, ac;
int x, d;
char c;

bool ok;
queue<pair<int, int>> q;

pair<int, int> head;
pair<int, int> tail;

int timer;

void move()
{
	head.first += dr[d];
	head.second += dc[d];
}

void check()
{
	if (a[head.first][head.second] == -1 || (1 <= a[head.first][head.second] && a[head.first][head.second] <= 4)) { // Á¾·á (º® or ¸ö)
		ok = false;
		return;
	}
	
	if (a[head.first][head.second] == 0) { // ºóÄ­
		a[head.first][head.second] = d;
		int td = a[tail.first][tail.second];
		a[tail.first][tail.second] = 0;
		tail.first += dr[td];
		tail.second += dc[td];
	}
	else if (a[head.first][head.second] == 9) { // »ç°ú
		a[head.first][head.second] = d;
	}

	if (!q.empty()) {
		pair<int, int> temp = q.front();
		if (temp.first == timer) {
			if (temp.second == 1) {
				d -= 1;
				if (d == 0) d = 4;
				a[head.first][head.second] = d;
			}
			else {
				d += 1;
				if (d == 5) d = 1;
				a[head.first][head.second] = d;
			}
			q.pop();
		}
	}
}

void play()
{
	timer = 0;
	ok = true;
	d = 1;
	while (ok) {
		timer += 1;
		move();
		check();
	}
}

int main()
{
//	freopen("sample_input.txt", "r", stdin);
	head.first = 1; head.second = 1; 
	tail.first = 1; tail.second = 1;
	a[1][1] = 1;

	cin >> n;
	for (int i = 0; i < n + 2; i++) a[i][0] = -1, a[i][n + 1] = -1;
	for (int i = 0; i < n + 2; i++) a[0][i] = -1, a[n + 1][i] = -1;

	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> ar >> ac;
		a[ar][ac] = 9; // apple
	}

	cin >> l;

	for (int i = 0; i < l; i++) {
		cin >> x >> c;
		if (c == 'L') q.push({x, 1}); // ¿ÞÂÊÀ¸·Î 90µµ
		else q.push({ x, 2 }); // ¿À¸¥ÂÊÀ¸·Î 90µµ
	}

	play();

	cout << timer << endl;
	return 0;
}