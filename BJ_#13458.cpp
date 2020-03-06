#include <memory.h>
#include<iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int B, C;
int N;
int room[1000001];
long long rst = 0;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> room[i];
	cin >> B >> C;

	for (int i = 0; i < N; i++) {
		room[i] -= B;						//�� �濡�� �Ѱ����� ����-
		rst++;
		if (room[i] < 0)
			room[i] = 0;					
	}

	for (int i = 0; i < N; i++) {	
		int ans = room[i] / C;				//�� �� �����ο�/�ΰ����� ����
		rst += ans;
		room[i] = room[i] % C;				//���� �ο���
		if (room[i] > 0) {
			room[i] = 0;
			rst++;							//���� �ΰ����� �Ѹ� ��ġ
		}
	}
	cout << rst << endl;

	return 0;
}