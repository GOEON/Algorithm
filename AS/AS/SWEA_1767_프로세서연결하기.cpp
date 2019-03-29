// 190329
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf&

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int T, n, coreNum;
int ans_core, ans_line; // 연결된 코어 수, 연결된 코어들의 전선수
bool v[13][13];
int a[13][13];

pair<int, int> core[13];

int check(int r, int c, int k)
{
	int lineNum = 0;
	if (k == 0) { // 상
		for (int i = 1; i < r; i++) {
			if (v[i][c] == false) {
				v[i][c] = true;
				lineNum += 1;
			}
			else { // 실패
				for (int j = 1; j < i; j++) v[j][c] = false;
				return 0;
			}
		}
		return lineNum;
	}
	else if (k == 1) { // 하
		for (int i = r + 1; i <= n; i++) {
			if (v[i][c] == false) {
				v[i][c] = true;
				lineNum += 1;
			}
			else { // 실패
				for (int j = r + 1; j < i; j++) v[j][c] = false;
				return 0;
			}
		}
		return lineNum;
	}
	else if (k == 2) { // 좌
		for (int i = 1; i < c; i++) {
			if (v[r][i] == false) {
				v[r][i] = true;
				lineNum += 1;
			}
			else { // 실패
				for (int j = 1; j < i; j++) v[r][j] = false;
				return 0;
			}
		}
		return lineNum;
	}
	else if (k == 3) { // 우
		for (int i = c + 1; i <= n; i++) {
			if (v[r][i] == false) {
				v[r][i] = true;
				lineNum += 1;
			}
			else { // 실패
				for (int j = c + 1; j < i; j++) v[r][j] = false;
				return 0;
			}
		}
		return lineNum;
	}
}

void restore(int r, int c, int k)
{
	if (k == 0) for (int i = 1; i < r; i++) v[i][c] = false;
	else if (k == 1) for (int i = r + 1; i <= n; i++) v[i][c] = false;
	else if (k == 2) for (int i = 1; i < c; i++) v[r][i] = false;
	else if (k == 3) for (int i = c + 1; i <= n; i++) v[r][i] = false;
}
void dfs(int idx, int cn, int ln) // core num, line num
{
	if (idx > coreNum) { // 종료
		if (ans_core < cn) {
			ans_core = cn, ans_line = ln;
		}
		else if (ans_core == cn) {
			if (ans_line > ln) ans_line = ln;
		}
		return;
	}

	int r = core[idx].first;
	int c = core[idx].second;
	int cnt = 0;
	for (int k = 0; k < 4; k++) {
		int line;
		line = check(r, c, k);
		if (line > 0) { // 성공
			dfs(idx + 1, cn + 1, ln + line);
			restore(r, c, k);
		}
		else cnt += 1;
	}
	if (cnt == 4) dfs(idx + 1, cn, ln);
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans_core = 0, ans_line = 225;
		coreNum = 0;
		memset(a, 0, sizeof(a));
		memset(v, false, sizeof(v));
		cin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> a[i][j];
				
				if (a[i][j] == 1) {
					if (i == 1 || i == n || j == 1 || j == n) {
						v[i][j] = true;
						continue;
					}
					v[i][j] = true;
					coreNum += 1;
					core[coreNum] = {i, j};
				}
			}
		}

		dfs(1, 0, 0); // 1번 코어부터 시작

		cout << "#" << tc << " " << ans_line << endl;
	}

	return 0;
}