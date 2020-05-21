#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> dwarf;
int total = 0;

int main() {
	for (int i = 0; i < 9; i++) {
		int tmp;
		cin >> tmp;
		dwarf.push_back(tmp);
		total += tmp;					//9명 난쟁이 키의 합
	}
	sort(dwarf.begin(), dwarf.end());
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (total - dwarf[i] - dwarf[j] == 100) {		//두가지를 뺐을 때 100이라면
				for (int k = 0; k < 9; k++) {
					if (k == i || k == j) continue;			//그 두가지를 제외한 나머지 출력
					cout << dwarf[k] << endl;
				}
				return 0;
			}
		}
	}
}