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
		total += tmp;					//9�� ������ Ű�� ��
	}
	sort(dwarf.begin(), dwarf.end());
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (total - dwarf[i] - dwarf[j] == 100) {		//�ΰ����� ���� �� 100�̶��
				for (int k = 0; k < 9; k++) {
					if (k == i || k == j) continue;			//�� �ΰ����� ������ ������ ���
					cout << dwarf[k] << endl;
				}
				return 0;
			}
		}
	}
}