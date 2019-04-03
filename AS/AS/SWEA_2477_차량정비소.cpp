// 190403
// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int ans, T;
int n, m, k, a, b;

int ai[10]; // �ð�
int bj[10]; // �ð�

struct Node {
	int num; // ����ȣ
	int tk; // ����� �����ð� 
	int na; // ������ ��ȣ
	int t_aend; // ���� ������ �ð� 
	int t_bend; // ���� ������ �ð�
};

Node aa[10]; // ������
Node bb[10]; // �����

queue<Node> qa; // ���� ��⿭
queue<Node> qb; // ���� ��⿭

int timer;
int people;

void a_process() // ����
{
	// ���� ���� �� ������ qb�� �̵� 
	for (int i = 1; i <= n; i++) {
		if (aa[i].num != 0 && aa[i].t_aend == timer) {
			qb.push(aa[i]);
			aa[i].num = 0; // ��� ������ �ǹ�
		}
	}

	// �����뿡 �� ��ġ
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

void b_process() // ����
{
	// ���� ���� �� ������ people ���� �� ans ������Ʈ 
	for (int i = 1; i <= m; i++) {
		if (bb[i].num != 0 && bb[i].t_bend == timer) {
			people += 1;
			if (bb[i].na == a && i == b) {
				ans += bb[i].num;
			}
			bb[i].num = 0; // ��� ������ �ǹ�
		}
	}

	// ����뿡 ����ġ 
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
	people = 0; // ��� ���� ��� �� 
	while (people < k) {
		a_process(); // ���� ó��
		b_process(); // ����ó��
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

		for (int i = 1; i <= n; i++) cin >> ai[i]; // i�� ������ ó�� �ð�
		for (int i = 1; i <= m; i++) cin >> bj[i]; // i�� ����� ó�� �ð�
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