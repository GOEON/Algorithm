// 190313
// https://www.acmicpc.net/problem/16985

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

bool visit[5][5][5];
int cube1[5][5][5]; // 원본
int cube2[5][5][5]; // 층 바꿔서 저장
int cube3[5][5][5]; // 회전해서 저장
int ans;

// 여섯 방향 
int di[] = {0, 0, 0, 0, 1, -1};
int dj[] = {1, -1, 0, 0, 0, 0};
int dk[] = {0, 0, 1, -1, 0, 0};

typedef struct _point {
	int i;
	int j;
	int k;
	int d; // distance
}Point;

queue<Point> q;

void copy_cube(vector<int> &v1)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cube2[i][j][k] = cube1[v1[i]][j][k];
			}
		}
	}
}

void revolve_cube(vector<int> &v2)
{
	for (int i = 0; i < 5; i++) {
		// 0은 그대로 이므로
		// i는 층도 나타냄
		if (v2[i] == 0) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					cube3[i][j][k] = cube2[i][j][k];
				}
			}
		}
		else if (v2[i] == 1) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					cube3[i][j][k] = cube2[i][4 - k][j];
				}
			}
		}
		else if (v2[i] == 2) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					cube3[i][j][k] = cube2[i][4 - j][4 - k];
				}
			}
		}
		else if (v2[i] == 3) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					cube3[i][j][k] = cube2[i][k][4 - j];
				}
			}
		}
	}

}

bool play()
{
	bool possible = false;
	vector<int> v1(5); // 층 구성 
	vector<int> v2(5); // 모양 구성 (회전)
	for (int ii = 0; ii < 5; ii++) {
		v1[ii] = ii;
	}

	do {
		copy_cube(v1); // 층 배치
		for (int n1 = 0; n1 < 4; n1++) {
			v2[0] = n1;
			for (int n2 = 0; n2 < 4; n2++) {
				v2[1] = n2;
				for (int n3 = 0; n3 < 4; n3++) {
					v2[2] = n3;
					for (int n4 = 0; n4< 4; n4++) {
						v2[3] = n4;
						for (int n5 = 0; n5 < 4; n5++) {
							v2[4] = n5;
							revolve_cube(v2); // v2에 따라 큐브 회전 
							memset(visit, false, sizeof(visit));
							// 정육면체 하나 만들어지고 가장 짧은 길 찾는 과정 
							Point stt[4] = { {0,0,0}, {0,0,4}, {0,4,0}, {0,4,4} };
							Point dst[4] = { {4,4,4}, {4,4,0}, {4,0,4}, {4,0,0} };

							for (int ch = 0; ch < 4; ch++) {
								if (cube3[stt[ch].i][stt[ch].j][stt[ch].k] == 0 || cube3[dst[ch].i][dst[ch].j][dst[ch].k] == 0) continue;

								Point p;
								p.i = stt[ch].i, p.j = stt[ch].j, p.k = stt[ch].k;
								p.d = 0;
								q.push(p);
								visit[p.i][p.j][p.k] = true;

								while (!q.empty()) {
									int ci = q.front().i;
									int cj = q.front().j;
									int ck = q.front().k;
									int cd = q.front().d;
									q.pop();

									for (int k = 0; k < 6; k++) {
										int ni = ci + di[k];
										int nj = cj + dj[k];
										int nk = ck + dk[k];

										if (0 <= ni && ni < 5 && 0 <= nj && nj < 5 && 0 <= nk && nk < 5) {
											if (visit[ni][nj][nk] == false && cube3[ni][nj][nk] == 1) {
												Point np;
												np.i = ni, np.j = nj, np.k = nk;
												np.d = cd + 1;
												q.push(np);
												visit[ni][nj][nk] = true;
												if (ni == dst[ch].i && nj == dst[ch].j && nk == dst[ch].k) {
													if (ans > np.d) ans = np.d;
													queue<Point>().swap(q);
													possible = true;
													break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	} while (next_permutation(v1.begin(), v1.end()));

	return possible;
}

int main()
{
	ans = 125;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				scanf("%d", &cube1[i][j][k]);

	if(play()) printf("%d\n", ans);
	else printf("-1\n");
	return 0;
}