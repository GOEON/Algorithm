// 190404
// https://www.acmicpc.net/problem/5373

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n;

char color[] = { 'w', 'o', 'g', 'b', 'r', 'y' };
char cube[6][4][4];
char revolve[1000][2];

int shape[6][4] = {
	{1,3,4,2},
	{0,2,5,3},
	{0,4,5,1},
	{0,1,5,4},
	{0,3,5,2},
	{1,2,4,3}
};

pair<int, int> solution[6][4][3] = { // shape, order, coordinate
	{{{3,1},{3,2},{3,3}}, {{1,1},{2,1},{3,1}}, {{1,3},{1,2},{1,1}}, {{3,3},{2,3},{1,3}}},
	{{{1,1},{1,2},{1,3}}, {{1,1},{1,2},{1,3}}, {{1,1},{1,2},{1,3}}, {{1,1},{1,2},{1,3}}},
	{{{1,1},{2,1},{3,1}}, {{1,1},{2,1},{3,1}}, {{3,3},{2,3},{1,3}}, {{1,1},{2,1},{3,1}}},
	{{{1,3},{2,3},{3,3}}, {{1,3},{2,3},{3,3}}, {{3,1},{2,1},{1,1}}, {{1,3},{2,3},{3,3}}},
	{{{3,1},{3,2},{3,3}}, {{3,1},{3,2},{3,3}}, {{3,1},{3,2},{3,3}}, {{3,1},{3,2},{3,3}}},
	{{{1,1},{1,2},{1,3}}, {{3,1},{2,1},{1,1}}, {{3,3},{3,2},{3,1}}, {{1,3},{2,3},{3,3}}}
};

void print()
{
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cout << cube[0][i][j];
		}
		cout << '\n';
	}
}

void init()
{
	for (int k = 0; k < 6; k++) {
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				cube[k][i][j] = color[k];
			}
		}
	}
}

void func(int num, int dir) // 면, 방향
{
	if (dir == 0) { // 반시계
		char c1 = cube[shape[num][0]][solution[num][0][0].first][solution[num][0][0].second];
		char c2 = cube[shape[num][0]][solution[num][0][1].first][solution[num][0][1].second];
		char c3 = cube[shape[num][0]][solution[num][0][2].first][solution[num][0][2].second];

		for (int i = 1; i <= 3; i++) {
			for (int j = 0; j < 3; j++) {
				cube[shape[num][i-1]][solution[num][i-1][j].first][solution[num][i-1][j].second] = cube[shape[num][i]][solution[num][i][j].first][solution[num][i][j].second];
			}			
		}
		cube[shape[num][3]][solution[num][3][0].first][solution[num][3][0].second] = c1;
		cube[shape[num][3]][solution[num][3][1].first][solution[num][3][1].second] = c2;
		cube[shape[num][3]][solution[num][3][2].first][solution[num][3][2].second] = c3;

	}
	else { // 시계
		char c1 = cube[shape[num][3]][solution[num][3][0].first][solution[num][3][0].second];
		char c2 = cube[shape[num][3]][solution[num][3][1].first][solution[num][3][1].second];
		char c3 = cube[shape[num][3]][solution[num][3][2].first][solution[num][3][2].second];

		for (int i = 3; i >= 1; i--) {
			for (int j = 0; j < 3; j++) {
				cube[shape[num][i]][solution[num][i][j].first][solution[num][i][j].second] = cube[shape[num][i-1]][solution[num][i-1][j].first][solution[num][i-1][j].second];
			}
		}

		cube[shape[num][0]][solution[num][0][0].first][solution[num][0][0].second] = c1;
		cube[shape[num][0]][solution[num][0][1].first][solution[num][0][1].second] = c2;
		cube[shape[num][0]][solution[num][0][2].first][solution[num][0][2].second] = c3;
	}
}

void cw(int num)
{
	// 해당면 시계방향 회전
	char temp[4][4];
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			temp[j][4 - i] = cube[num][i][j];
		}
	}
	swap(cube[num], temp);

	// 다른 면들 이동
	func(num, 1); 
}

void ccw(int num)
{
	// 해당면 반시계방향 회전
	char temp[4][4];
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			temp[4 - j][i] = cube[num][i][j];
		}
	}
	swap(cube[num], temp);
	
	// 다른 면들 이동
	func(num, 0);
}

void play(char plate, char dir) // 면, 방향
{
	if (plate == 'U') { // 0
		if (dir == '-') ccw(0);
		else if(dir == '+') cw(0);
	}else if (plate == 'B') { // 1
		if (dir == '-') ccw(1);
		else if (dir == '+') cw(1);
	}
	else if (plate == 'L') {// 2
		if (dir == '-') ccw(2);
		else if (dir == '+') cw(2);
	}
	else if (plate == 'R') {// 3
		if (dir == '-') ccw(3);
		else if (dir == '+') cw(3);
	}
	else if (plate == 'F') {// 4
		if (dir == '-') ccw(4);
		else if (dir == '+') cw(4);
	}
	else if (plate == 'D') {// 5
		if (dir == '-') ccw(5);
		else if (dir == '+') cw(5);
	}
}

void go()
{
	for (int i = 0; i < n; i++) {
		play(revolve[i][0], revolve[i][1]);
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> n;
		init();
		for (int i = 0; i < n; i++) {
			cin >> revolve[i];
		}
		
		go();

		print();
	}
	return 0;
}