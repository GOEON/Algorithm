// 190313
// https://www.acmicpc.net/problem/16986

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

bool possible;
int n, k;
int a[10][10];
int kh[21];
int mh[21];
int w[3];

vector<bool> v(10); // 지우가 낸 인싸가위바위보 체크(1~9)

void dfs(int p1, int p2, int r_kh, int r_mh) // player1, player2, round 경희, round 민호
{
	if (possible) return;
	// 종료
	if (w[0] == k) { // 지우가 k번 승리하면 가능 
		possible = true;
		return;
	}
	if (w[1] == k || w[2] == k) {
		return;
	}

	// 게임
	if (p1 == 0 && p2 == 1) { // 지우 vs 경희
		for (int i = 1; i <= n; i++) { // i는 지우가 내는 것 
			if (v[i] == false) {
				if (a[i][kh[r_kh]] == 2) { // 이김 
					w[0] += 1; v[i] = true;
					dfs(0, 2, r_kh, r_mh + 1);
					w[0] -= 1; v[i] = false;
				}
				else if (a[i][kh[r_kh]] == 0 || a[i][kh[r_kh]] == 1) { // 짐
					w[1] += 1; v[i] = true;
					dfs(1, 2, r_kh + 1, r_mh + 1);
					w[1] -= 1; v[i] = false;
				}
			}
		}
	}
	else if (p1 == 0 && p2 == 2) { // 지우 vs 민호
		for (int i = 1; i <= n; i++) { // i는 지우가 내는 것 
			if (v[i] == false) {
				if (a[i][mh[r_mh]] == 2) { // 이김 
					w[0] += 1; v[i] = true;
					dfs(0, 1, r_kh + 1, r_mh);
					w[0] -= 1; v[i] = false;
				}
				else if (a[i][mh[r_mh]] == 0 || a[i][mh[r_mh]] == 1) { // 짐 
					w[2] += 1; v[i] = true;
					dfs(1, 2, r_kh + 1, r_mh + 1);
					w[2] -= 1; v[i] = false;
				}
			}
		}
	}
	else if (p1 == 1 && p2 == 2) { // 경희 vs 민호
		if (a[kh[r_kh]][mh[r_mh]] == 2) { // 이김 
			w[1] += 1;
			dfs(0, 1, r_kh + 1, r_mh);
			w[1] -= 1;
		}
		else if (a[kh[r_kh]][mh[r_mh]] == 0 || a[kh[r_kh]][mh[r_mh]] == 1) { // 짐 
			w[2] += 1;
			dfs(0, 2, r_kh, r_mh + 1);
			w[2] -= 1;
		}
	}
}

int main()
{
	possible = false;
	for (int i = 0; i < 3; i++) w[i] = 0;
	scanf("%d %d", &n, &k);
	
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) 
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= 20; i++) 
		scanf("%d", &kh[i]); // 경희

	for (int i = 1; i <= 20; i++) 
		scanf("%d", &mh[i]); // 민호

	dfs(0, 1, 1, 0); // 지우 vs 경희, 라운드 경희, 라운드 민호
	if (possible) printf("1\n");
	else printf("0\n");

	return 0;
}