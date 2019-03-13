// 190313
// https://www.acmicpc.net/problem/16234

#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
using namespace std;

bool visit[50][50];
int a[50][50];
int n, L, R;
int ans;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

typedef struct country {
	int r;
	int c;
}Country;

void people_move()
{
	bool isMove = true;
	while (isMove) {
		isMove = false;
		memset(visit, false, sizeof(visit));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visit[i][j] == false) {
					queue<Country> q_check; // �˻�� 
					queue<Country> q_union; // ���տ�
					Country c;
					c.r = i;
					c.c = j;
					q_check.push(c);
					q_union.push(c);
					visit[i][j] = true;

					int u_people = a[i][j];  // ���ձ� �α��� 
					int c_country = 1; // ���ձ� ��

					while (!q_check.empty()) { // �˻�
						int cr = q_check.front().r ;
						int cc = q_check.front().c;
						q_check.pop();

						for (int k = 0; k < 4; k++) {
							int nr = cr + dr[k];
							int nc = cc + dc[k];
							if (0 <= nr && nr < n && 0 <= nc && nc < n) {
								if (visit[nr][nc] == false) {
									if (L <= abs(a[cr][cc] - a[nr][nc]) && abs(a[cr][cc] - a[nr][nc]) <= R) {
										visit[nr][nc] = true;
										Country c2;
										c2.r = nr;
										c2.c = nc;
										u_people += a[nr][nc];
										c_country += 1;
										q_check.push(c2);
										q_union.push(c2);
										isMove = true;
									}
								}
							}
						}
					}
					// ���� ������ �α� ������Ʈ 
					int nu_people = u_people / c_country;
					while (!q_union.empty()) {
						int ur = q_union.front().r;
						int uc = q_union.front().c;
						q_union.pop();
						a[ur][uc] = nu_people;
					}
				}
			}
		}
		if (isMove) ans += 1;
	}
}

int main()
{
	ans = 0;
	scanf("%d %d %d", &n, &L, &R);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	// �� ������ �α����� �־����� ��, 
    // �α� �̵��� �� �� �߻��ϴ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�
	people_move();

	printf("%d\n", ans);

	return 0;
}