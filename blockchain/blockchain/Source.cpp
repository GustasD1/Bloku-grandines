#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;
void binary(string zodis, vector<unsigned long> reiksmes);
void didinimas(vector<unsigned long> reiksmes);

int main() {
	vector <unsigned long> reiksmes;
	string zodis;
	cout << "iveskite zodi" << endl;
	cin >> zodis;
	binary(zodis, reiksmes);
	didinimas(reiksmes);

}
void binary(string zodis, vector<unsigned long> reiksmes) {

	for (int i = 0; i < zodis.size(); i++){
		bitset<8> a(zodis.c_str()[i]);
		reiksmes.push_back(a.to_ulong());
		
}

}
void didinimas(vector<unsigned long> reiksmes) {
	
	int sk = reiksmes.size() * 8;
	int k = 447 - sk;
	unsigned long s1 = 0x80;
	reiksmes.push_back(s1);
	k = k - 7;
	for (int i = 0; i < k / 8; i++) {
		reiksmes.push_back(0x00000000);
	}
	bitset<64> block(1);
	string block_string = block.to_string();

	bitset<8> temp(block_string.substr(0, 8));
	reiksmes.push_back(temp.to_ulong());
	for (int i = 8; i < 63; i = i + 8) {
		bitset<8> temp2(block_string.substr(i, 8));
		reiksmes.push_back(temp2.to_ulong());

	}




}