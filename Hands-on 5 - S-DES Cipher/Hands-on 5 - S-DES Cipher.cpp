#include <iostream>
using namespace std;

const int S1Box[16] = {101, 010, 001, 110, 011, 100, 111, 000, 001, 100, 110, 010, 000, 111, 101, 011};
const int S2Box[16] = {100, 000, 110, 101, 111, 001, 011, 010, 101, 011, 000, 111, 110, 010, 001, 100};
void DESEncrypt(int *text, int *key);

int main() {
	int text[12];
	int key[9];
	long textIn, keyIn;
	cout << "Please enter the text in binary you wish to encrypt/decrypt: ";
	cin >> textIn;
	for (int i = 11; i >= 0; i--) {
		text[i] = textIn % 10;
		textIn /= 10;
	}
	cout << "Please enter the given key value: ";
	cin.ignore();
	cin >> keyIn;
	for (int i = 8; i >= 0; i--) {
		key[i] = keyIn % 10;
		keyIn /= 10;
	}

	DESEncrypt(text, key);
}

void DESEncrypt(int *text, int *key) {
	//Initialize Ki-1 Values, Li-1 and Ri-1 Values, and Li; Values;
	int KeyOne[8] = { key[0], key[1], key[2], key[3], key[4], key[5], key[6], key[7] };
	int LZero[6] = {text[0], text[1], text[2], text[3], text[4], text[5] };
	int RZero[6] = { text[6], text[7], text[8], text[9], text[10], text[11] };
	int LOne[6] = { RZero[0], RZero[1], RZero[2], RZero[3], RZero[4], RZero[5] };

	//Expansion Of Ri-1;
	int RZeroExpanded[8] = { RZero[0], RZero[1], RZero[3], RZero[2], RZero[3], RZero[2], RZero[4], RZero[5] };

	//Expansion of Ri-1 XOR Ki-1;
	int ExpandedModKey[8];
	for (int i = 0; i < 7; i++) {
		if (RZeroExpanded[i] == KeyOne[i]) {
			ExpandedModKey[i] = 0;
		}
		else
			ExpandedModKey[i] = 1;
	}

	//Find index for S1 Box;
	int S1[4] = { ExpandedModKey[0], ExpandedModKey[1], ExpandedModKey[2], ExpandedModKey[3] };
	int SOne = 0;
	if (S1[0] == 1)
		SOne += 8;
	if (S1[1] == 1)
		SOne += 4;
	if (S1[2] == 1)
		SOne += 2;
	if (S1[3] == 1)
		SOne += 1;

	//Find index for S2 Box;
	int S2[4] = { ExpandedModKey[4], ExpandedModKey[5], ExpandedModKey[6], ExpandedModKey[7] };
	int STwo = 0;
	if (S2[0] == 1)
		STwo += 8;
	if (S2[1] == 1)
		STwo += 4;
	if (S2[2] == 1)
		STwo += 2;
	if (S2[3] == 1)
		STwo += 1;

	//Grab values from S1 and S2 Box;
	SOne = S1Box[SOne];
	STwo = S2Box[STwo];

	int fRiMinus1ModKi[6];

	//Initialize right side of f(Ri-1, Ki);
	for (int i = 5; i >= 3; i--) {
		fRiMinus1ModKi[i] = STwo % 10;
		STwo /= 10;
	}

	//Initialize left side of (fRi-1, Ki);
	for (int i = 2; i >= 0; i--) {
		fRiMinus1ModKi[i] = SOne % 10;
		SOne /= 10;
	}

	int ROne[8];
	for (int i = 0; i < 7; i++) {
		if (LZero[i] == fRiMinus1ModKi[i]) {
			ROne[i] = 0;
		}
		else
			ROne[i] = 1;
	}

	int toReturn[12] = { LOne[0], LOne[1], LOne[2], LOne[3], LOne[4], LOne[5], ROne[6], ROne[7], ROne[8], ROne[9], ROne[10], ROne[11] };

	cout << "CypherText is: ";
	for (int i = 0; i < 11; i++) {
		cout << toReturn[i];
	}
}