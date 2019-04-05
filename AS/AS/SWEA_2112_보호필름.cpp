#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int T, ans;
int d, w, k;

int a[13][20];
int liquid;

bool test()
{
	for (int j = 0; j < w; j++) {
		int cnt = 1;
		int temp = a[0][j];
		for (int i = 1; i < d; i++) {
			if (a[i][j] == temp) {
				cnt += 1;
				if (cnt == k) break;
			}
			else {
				cnt = 1;
				temp = a[i][j];
			}
		}
		if (cnt < k) return false;
	}
	return true;
}

void launch(int row, int c)
{
	for (int i = 0; i < w; i++) a[row][i] = c;
}


void film()
{
	liquid = 0; // 약품 투입 횟수
	int b[13][20];
	int row=0;
	
	while (1) {
		vector<int> v(d);
		for (int i = 0; i < liquid; i++) { // liquid 수 만큼 1 채우기
			v[i] = 1;
		}

		int cnt = 0;
		do {
			for (int x = 0; x < 2; x++) { // 약품 투입 
				memcpy(b, a, sizeof(a));
				for (int i = 0; i < v.size(); i++) { // 약품 투입 위치 
					if (v[i] == 1) {
						launch(i, x);
						cnt += 1;
						if (cnt == liquid) break; // 약품 투입 끝
					}
				}
				if (test()) return;
				swap(b, a);
			}
		} while (prev_permutation(v.begin(), v.end()));

		if(liquid == 0) // 약품 투입 안 했을 때 검사 
			if (test()) return;
		liquid += 1;// 약품 투입 횟수 늘리기
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> d >> w >> k;
		liquid = 0;
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				cin >> a[i][j];
			}
		}

		film();
		cout << "#" << tc << " " << liquid << '\n';
	}
	return 0;
}