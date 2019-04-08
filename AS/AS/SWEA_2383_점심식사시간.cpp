#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int T, ans, n;
int a[10][10];
int people, timer;
int A, B, idx1, idx2;
pair<int, int> p[10]; // 사람들 좌표
pair<int, int> s[2]; // stair 좌표
int s1[10]; // stair 1에 가는 시간 
int s2[10]; // stair 2에 가는 시간 

int gIdx1, gIdx2;
int g[10];
int g1[10]; // group 1 
int g2[10]; // group 2


void simulation()
{ 
	int totalA = A;
	int totalB = B;
	int ta = a[s[0].first][s[0].second];
	int tb = a[s[1].first][s[1].second];
	int waitA = 0; // 계단 1 입구에 모인 사람 수 
	int waitB = 0; // 계단 2 입구에 모인 사람 수 
	int sIdx1 = 0; // 검사 시작 인덱스 
	int sIdx2 = 0;
	queue<int> q1; // 계단 1을 내려가는 사람 (끝나는 시간 저장)
	queue<int> q2; // 계단 2를 내려 가는 사람 (끝나는 시간 저장)
	// 시뮬레이션 돌려서 시간 계산
	timer = 0;
	while (1) {
		if (totalA) {
			// 계단 다 내려오기 검사 
			while (!q1.empty()) {
				int temp = q1.front();
				if (temp <= timer) {
					q1.pop();
					totalA -= 1;
				}
				else {
					break;
				}
			}

			// 계단입구에서 계단으로 진입 
			if (waitA > 0 && q1.size() < 3) {
				int num = 3 - q1.size();
				if (waitA <= num) {
					num = waitA;
					waitA = 0;
				}
				else {
					waitA -= num;
				}

				for (int i = 0; i < num; i++) {
					q1.push(timer + ta);
				}
			}

			for (int i = sIdx1; i < A; i++) { // 계단 입구 들어가기 
				if (timer < g1[i]) {
					break;
				}
				else {
					if (waitA == 3) break;
					else {
						sIdx1 += 1;
						waitA += 1;
					}
				}
			}
		}
		if (totalB) {
			// 계단 다 내려오기 검사 
			while (!q2.empty()) {
				int temp = q2.front();
				if (temp <= timer) {
					q2.pop();
					totalB -= 1;
				}
				else {
					break;
				}
			}

			// 계단입구에서 계단으로 진입 
			if (waitB > 0 && q2.size() < 3) {
				int num = 3 - q2.size();
				if (waitB <= num) {
					num = waitB;
					waitB = 0;
				}
				else {
					waitB -= num;
				}
				for (int i = 0; i < num; i++) {
					q2.push(timer + tb);
				}
			}

			for (int i = sIdx2; i < B; i++) { // 계단 입구 들어가기 
				if (timer < g2[i]) {
					break;
				}
				else {
					if (waitB == 3) break;
					else {
						sIdx2 += 1;
						waitB += 1;
					}
				}
			}
		}

		if (totalA == 0 && totalB == 0) break; // 계단을 다 내려오면 끝
		timer += 1;
	}
	if (ans > timer) 
		ans = timer;
}

void divideGroup()
{
	for (int i = 0; i < B; i++) g[i] = 1; // B의 숫자만큼 1넣기 
	for (int i = B; i < people; i++) g[i] = 0;

	do {
		gIdx1 = 0; gIdx2 = 0;
		for (int i = 0; i < people; i++) {
			if (g[i] == 1) { // s2
				g2[gIdx2++] = s2[i];
			}
			else if (g[i] == 0) { // s1
				g1[gIdx1++] = s1[i];
			}
		}
		sort(g1, g1 + gIdx1);
		sort(g2, g2 + gIdx2);
		simulation();
	} while (prev_permutation(g, g + people));
}

void calTime()
{
	for (int i = 0; i < idx1; i++) {
		s1[i] = abs(p[i].first - s[0].first) + abs(p[i].second - s[0].second);
		s2[i] = abs(p[i].first - s[1].first) + abs(p[i].second - s[1].second);
	}
}

void play()
{
	calTime(); // 계단까지 걸리는 시간 구하기
	A = 0;
	B = people;
	for (int ai = 0; ai <= people; ai++) {
		A = ai; // 계단 1에 배정된 수 
		B = people - ai; // 계단 2에 배정된 수 
		divideGroup();
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> n;
		ans = 2147483647;
		people = 0;
		idx1 = 0; // 사람들 수 
		idx2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				if (a[i][j] == 1) {
					people += 1;
					p[idx1++] = { i, j };
				}
				else if (a[i][j] > 1) {
					s[idx2++] = { i, j };
				}
			}
		}

		play();

		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}