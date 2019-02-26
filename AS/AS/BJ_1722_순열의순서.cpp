// 190226
// https://www.acmicpc.net/problem/1722

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, sn;
long long k, f[21];
bool s[21];
int v[20];

void findV(long long num)
{
	long long sum = 0;
	// 자리수 별로 숫자 체크하기 
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[j] == false) {
				int p = j;
				// 첫째자리 검사 
				long long temp = f[n - i - 1];
				if (sum + temp < num) {
					sum += temp;
				}
				else {
					s[j] = true;
					v[i] = p;
					break;
				}
			}
		}
	}
}

long long findK()
{
	long long ret = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[j] == true)continue;
			if (v[i] == j) {
				s[j] = true;
				break;
			}
			else {
				ret += f[n - 1 - i];
			}
		}
	}

	ret += 1;
	return ret;
}

int main()
{
	scanf("%d", &n);
	scanf("%d", &sn);
	
	// factorial 저장
	f[0] = 1; f[1] = 1;
	for (int i = 2; i <= 20; i++) {
		f[i] = f[i - 1] * i;
	}

	if (sn == 1) { // k 입력 
		scanf("%lld", &k);
		findV(k);
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < n; i++) {
			scanf("%d", &k);
			v[i] = k;
		}
		k = findK();
		printf("%lld\n", k);
	}
	

	return 0;
}