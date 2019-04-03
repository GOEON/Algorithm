// 190403
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int ans, T;
int n, m, k, a, b;

int ai[10]; // 시간
int bj[10]; // 시간

struct Node {
	int num; // 고객번호
	int tk; // 정비소 도착시간 
	int na; // 접수대 번호
	int t_aend; // 접수 끝나는 시간 
	int t_bend; // 정비 끝나는 시간
};

Node aa[10]; // 접수대
Node bb[10]; // 정비대

queue<Node> qa; // 접수 대기열
queue<Node> qb; // 정비 대기열

int timer;
int people;

void a_process() // 접수
{
	// 접수 끝난 고객 꺼내서 qb로 이동 
	for (int i = 1; i <= n; i++) {
		if (aa[i].num != 0 && aa[i].t_aend == timer) {
			qb.push(aa[i]);
			aa[i].num = 0; // 비어 있음을 의미
		}
	}

	// 접수대에 고객 배치
	for (int i = 1; i <= n; i++) {
		if (aa[i].num == 0) {
			if (!qa.empty() && qa.front().tk <= timer) {
				aa[i] = qa.front();
				qa.pop();
				aa[i].na = i;
				aa[i].t_aend = timer + ai[i];
			}
		}
	}
}

void b_process() // 정비
{
	// 정비 끝난 고객 꺼내서 people 증가 및 ans 업데이트 
	for (int i = 1; i <= m; i++) {
		if (bb[i].num != 0 && bb[i].t_bend == timer) {
			people += 1;
			if (bb[i].na == a && i == b) {
				ans += bb[i].num;
			}
			bb[i].num = 0; // 비어 있음을 의미
		}
	}

	// 정비대에 고객배치 
	for (int i = 1; i <= m; i++) {
		if (bb[i].num == 0) {
			if (!qb.empty()) {
				bb[i] = qb.front();
				qb.pop();
				bb[i].t_bend = timer + bj[i];
			}
		}
	}
}

void play()
{
	timer = 0;
	people = 0; // 모두 끝난 사람 수 
	while (people < k) {
		a_process(); // 정비 처리
		b_process(); // 접수처리
		timer += 1;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = 0;
		memset(aa, 0, sizeof(aa));
		memset(bb, 0, sizeof(bb));

		queue<Node>().swap(qa);
		queue<Node>().swap(qb);

		cin >> n >> m >> k >> a >> b;

		for (int i = 1; i <= n; i++) cin >> ai[i]; // i번 접수대 처리 시간
		for (int i = 1; i <= m; i++) cin >> bj[i]; // i번 정비대 처리 시간
		for (int i = 1; i <= k; i++) { // tk
			Node node;
			node.num = i;
			cin >> node.tk;
			qa.push(node);
		}

		play();

		if(ans) cout << "#" << tc << " " << ans << '\n';
		else cout << "#" << tc << " " << -1 << '\n';
	}
	return 0;
}