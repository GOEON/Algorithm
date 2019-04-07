// 190407
// https://www.acmicpc.net/problem/17136

#include <iostream>
using namespace std;

int used[6] = { 0,5,5,5,5,5 };
int a[11][11];
int ans, total;
int temp;
bool ok;

struct Node {
	int r;
	int c;
};

Node findCoord(int si, int sj)
{
	for (int i = si; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			if (a[i][j] == 7) return {i, j};
		}
	}
}

bool test(int si, int sj, int num)
{
	for (int i = si; i < si + num; i++) {
		if (i > 10) return false;
		for (int j = sj; j < sj + num; j++) {
			if (j > 10) return false;
			if (a[i][j] != 7) return false;
		}
	}
	return true;
}

void insertShape(int si, int sj, int shape, int num)
{
	for (int i = si; i < si + shape; i++) {
		for (int j = sj; j < sj + shape; j++) {
			a[i][j] = num;
		}
	}
}

void dfs(int si, int sj)
{
	// Á¾·á
	if (total == 0) {
	//	ok = false;
		if (ans > temp) ans = temp;
	}
	// 
	for (int i = 1; i <= 5; i++) {
		if (used[i] > 0 && test(si, sj, i)) {
			used[i] -= 1; insertShape(si, sj, i, i);
			total -= (i*i); temp += 1;
			Node node = findCoord(si, sj);
			dfs(node.r, node.c);
			used[i] += 1; insertShape(si, sj, i, 7);
			total += (i*i); temp -= 1;
		}
	}

//	if (ok) ans = -1;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	total = 0;
	temp = 0;
	ans = 25;
	ok = true;
	Node node;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cin >> a[i][j];
			if (a[i][j] == 1) {
				a[i][j] = 7;
				total += 1;
			}
		}
	}

	node = findCoord(0, 0);

	dfs(node.r, node.c);
	if (ans == 25) ans = -1;
	cout << ans << '\n';
	return 0;
}