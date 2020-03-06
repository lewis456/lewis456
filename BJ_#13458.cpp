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
		room[i] -= B;						//각 방에서 총감독관 감시-
		rst++;
		if (room[i] < 0)
			room[i] = 0;					
	}

	for (int i = 0; i < N; i++) {	
		int ans = room[i] / C;				//각 방 남은인원/부감독관 감시
		rst += ans;
		room[i] = room[i] % C;				//남은 인원들
		if (room[i] > 0) {
			room[i] = 0;
			rst++;							//각각 부감독관 한명씩 배치
		}
	}
	cout << rst << endl;

	return 0;
}