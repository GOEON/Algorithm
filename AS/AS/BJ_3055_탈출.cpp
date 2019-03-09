// 190308
// https://www.acmicpc.net/problem/3055

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int r, c;
int a[50][50];
int water[50][50];// 물 
int ksdc[50][50]; // 고슴도치

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};


queue<pair<int, int>> sq; // 고슴도치 큐 
queue<pair<int, int>> wq; // 물큐 

int go()
{
	int sq_size = sq.size();
	int wq_size = wq.size();
	while (sq_size) {
		while (wq_size--) {
			int cy = wq.front().first;
			int cx = wq.front().second;
			wq.pop();

			for (int k = 0; k < 4; k++) {
				int nx = cx + dx[k];
				int ny = cy + dy[k];

				if (0 <= nx && nx < c && 0 <= ny && ny < r) {
					if (a[ny][nx] == 4) continue; // 돌
					if (a[ny][nx] == 2) continue; // 비버
					if (water[ny][nx] > 0) continue; // 이미 방문한 물
					water[ny][nx] = water[cy][cx] + 1;
					wq.push(make_pair(ny, nx));
				}
			}
		}

		while (sq_size--) {
			int cy = sq.front().first;
			int cx = sq.front().second;
			sq.pop();

			for (int k = 0; k < 4; k++) {
				int nx = cx + dx[k];
				int ny = cy + dy[k];

				if (0 <= nx && nx < c && 0 <= ny && ny < r) {
					if (a[ny][nx] == 4) continue; // 돌
					if (water[ny][nx] > 0) continue; // 이미 물이 참 
					if (ksdc[ny][nx] > 0) continue; // 이미 고슴도치 방문
					ksdc[ny][nx] = ksdc[cy][cx] + 1;
					sq.push(make_pair(ny, nx));
					if (a[ny][nx] == 2) return ksdc[ny][nx] - 1;
				}
			}
		}
		if (sq_size < 0) {
			sq_size = sq.size();
			wq_size = wq.size();
		}
	}
	return false;
}

int main()
{
	int ans;
	ans = 0;
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char ch;
			cin >> ch;
			if (ch == '.') { // 빈칸
				a[i][j] = 0;       
			}
			else if (ch == 'S') { // 고슴도치
				a[i][j] = 1; 
				ksdc[i][j] = 1;
				sq.push(make_pair(i, j));
			}
			else if (ch == 'D') { // 비버굴
				a[i][j] = 2; 
			}
			else if (ch == '*') { // 물
				a[i][j] = 3; 
				water[i][j] = 1;
				wq.push(make_pair(i, j));
			}
			else if (ch == 'X') { // 돌
				a[i][j] = 4;
			}
		}
	}
	if(ans = go()){
		printf("%d\n", ans);
	}
	else {
		printf("KAKTUS\n");
	}
	
	return 0;
}