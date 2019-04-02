// 190402
// https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq&categoryId=AV5PpFQaAQMDFAUq&categoryType=CODE&&&

#include <iostream>
#include <vector>
using namespace std;

int T, ans;
int num;

bool check[13];
int month[13];
int price[5];
int temp2;
int cnt;

vector<int> v;

void dfs(int h, int p)
{
	if (h == num) { // ����
		if (ans > temp2) ans = temp2;
		return;
	}

	int m = v[h];
	
	int temp1 = temp2;
	
	for (int i = 1; i < 4; i++) {
		// ��ݰ��
		if (p == 1) { // m�� 1��ġ ����� 
			check[m] = true;
			temp2 += month[m] * price[1];
			dfs(h + 1, i);
		}
		else if (p == 2) { // m�� ��ġ �����
			check[m] = true;
			temp2 += price[2];
			dfs(h + 1, i);
		}
		else if (p == 3) { // m�޺��� 3��ġ �����
			for (int k = m; k < m + 3; k++) {
				if (k > 12) break;
				check[k] = true;
			}
			temp2 += price[3];
			int idx = h;
			for (int k = 0; k < 3; k++) {
				if (idx == num) break;
				if (check[v[idx]] == false) break;
				idx += 1;
			}
			
			dfs(idx, i);
		}

		// ����
		if (p == 1) { // m�޺��� 3��ġ �������� 
			check[m] = false;
		}
		else if (p == 2) {
			check[m] = false;
		}
		else if (p == 3) { // m�޺��� 3��ġ �����
			for (int k = m; k < m + 3; k++) {
				if (k > 12) break;
				check[k] = false;
			}
		}
		temp2 = temp1;
	}
}

void howmuch()
{
	int idx = 0;
	for (int i = 1; i < 4; i++)
		dfs(idx, i); // v[idx]���� i �����̽���
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 1; i <= 4; i++) cin >> price[i];
		for (int i = 1; i <= 12; i++) {
			cin >> month[i];
			check[i] = false;
			if (month[i] > 0) {
				v.push_back(i);
			}
		}

		cnt = 0; // Ŀ���ϴ� ���� ��
		temp2 = 0;
		num = v.size();
		ans = price[4]; // 1��ġ �ݾ��� �ʱ�ȭ

		howmuch();
		vector<int>().swap(v);
		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}