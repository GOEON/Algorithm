// 190307
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo&categoryId=AWXRDL1aeugDFAUo&categoryType=CODE

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

int map[11][11];
int m; // 움직인 시간 
int a; // BC 의 개수 
int ma[100];
int mb[100];

int timer;

typedef struct _BC {
	int x;
	int y;
	int c; // coverage 
	int p; // performance 
}BC;

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int T;
	int ans;
	int x1, y1, x2, y2; // p1, p2 각 좌표 
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &m, &a);
		vector<BC> bc(a);
		for (int i = 0; i < m; i++) {
			scanf("%d", &ma[i]);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &mb[i]);
		}
		for (int i = 0; i < a; i++) {
			scanf("%d %d %d %d", &bc[i].x, &bc[i].y, &bc[i].c, &bc[i].p);
		}

		// map 탐색, bc 정하기, 겹치는 부분은 비트마스크로 저장 
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				map[i][j] = 0;
				for (int k = 0; k < a; k++) {
					int d = abs(j - bc[k].x) + abs(i - bc[k].y);
					if (d <= bc[k].c) {
						map[i][j] |= (1 << k);
					}
				}
			}
		}
		// timer를 돌려가면서 계산, 겹칠 경우, vector에 넣고 permutation 
		ans = 0;
		timer = -1;
		x1 = 1, y1 = 1, x2 = 10, y2 = 10;
		while (timer < m) {

			// 이동
			if (timer >= 0) {
				if (ma[timer] == 1) y1 -= 1; // 상
				else if (ma[timer] == 2) x1 += 1; // 우
				else if (ma[timer] == 3) y1 += 1; // 하
				else if (ma[timer] == 4) x1 -= 1; // 좌		

				if (mb[timer] == 1) y2 -= 1; // 상
				else if (mb[timer] == 2) x2 += 1; // 우
				else if (mb[timer] == 3) y2 += 1; // 하
				else if (mb[timer] == 4) x2 -= 1; // 좌		
			}

			// p 계산
			vector<int> v1;
			vector<int> v2; 
			bool same_seat = false;
			for (int i = 0; i < a; i++) {
				if (map[y1][x1] & (1 << i)) {
					v1.push_back(i);
				}
				if (map[y2][x2] & (1 << i)) {
					v2.push_back(i);
				}
				if (map[y1][x1] & (1 << i) && map[y2][x2] & (1 << i)) {
					same_seat = true;
				}
			}
			int temp1 = 0;
			int temp2 = 0;
			if (same_seat) {
				for (int i = 0; i < v1.size(); i++) {
					for (int j = 0; j < v2.size(); j++) {
						temp2 = 0;
						if (v1[i] == v2[j]) {
							temp2 = bc[v1[i]].p;
						}
						else {
							temp2 = bc[v1[i]].p + bc[v2[j]].p;
						}
						if (temp1 < temp2) temp1 = temp2;
					}
				}
				ans += temp1;
			}
			else {
				temp1 = 0;
				temp2 = 0;
				for (int i = 0; i < v1.size(); i++) {
					temp2 = bc[v1[i]].p;
					if (temp1 < temp2) temp1 = temp2;
				}
				ans += temp1;
				temp1 = 0;
				temp2 = 0;
				for (int i = 0; i < v2.size(); i++) {
					temp2 = bc[v2[i]].p;
					if (temp1 < temp2) temp1 = temp2;
				}
				ans += temp1;
			}
			vector<int>().swap(v1);
			vector<int>().swap(v2);
			timer += 1;
		}

		printf("#%d %d\n", tc, ans);
		vector<BC>().swap(bc);
	}

	return 0;
}