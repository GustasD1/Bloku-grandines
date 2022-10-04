#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;


#define ROTRIGHT(word,bits) (((word) >> (bits)) | ((word) << (32-(bits))))
#define SSIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SSIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define BSIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define BSIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))

void binary(string zodis, vector<unsigned long> & reiksmes);
void didinimas(vector<unsigned long> & reiksmes);
void rusiavimas(vector<unsigned long> & reiksmes);
void hashavimas(vector<unsigned long>& reiksmes);
string show_as_hex(unsigned long input);

int main() {
	vector <unsigned long> reiksmes;
	string zodis;
	cout << "iveskite zodi" << endl;
	cin >> zodis;
	binary(zodis, reiksmes);
	didinimas(reiksmes);
	rusiavimas(reiksmes);
	hashavimas(reiksmes);


}
void binary(string zodis, vector<unsigned long> & reiksmes) {

	for (int i = 0; i < zodis.size(); i++){
		bitset<8> a(zodis.c_str()[i]);
		reiksmes.push_back(a.to_ulong());
		
}

}
void didinimas(vector<unsigned long> & reiksmes) {
	
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
void rusiavimas(vector<unsigned long> & reiksmes) {

	vector<unsigned long>temp(16);
	for (int i = 0; i < 64; i=i + 4) {
		bitset<32> laik(0);

		laik = (unsigned long)reiksmes[i] << 24;
		laik |= (unsigned long) reiksmes[i + 1] << 16;
		laik |= (unsigned long) reiksmes[i+2] << 8;
		laik |= (unsigned long) reiksmes[i + 3];
		temp[i / 4] = laik.to_ulong();
	}
	
reiksmes = temp;
}
void hashavimas(vector<unsigned long>& reiksmes) {
	unsigned long E[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
		0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
		0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
		0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
		0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
		0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};
 
	unsigned long static H0 = 0x6a09e667;
	unsigned long static H1 = 0xbb67ae85;
	unsigned long static H2 = 0x3c6ef372;
	unsigned long static H3 = 0xa54ff53a;
	unsigned long static H4 = 0x510e527f;
	unsigned long static H5 = 0x9b05688c;
	unsigned long static H6 = 0x1f83d9ab;
	unsigned long static H7 = 0x5be0cd19;

	unsigned long S[64];

	for (int i = 0; i <= 15; i++) {
		S[i] = reiksmes[i] & 0xFFFFFFFF;
	}
	for (int i = 16; i <= 63; i++) {
		S[i] = SSIG1(S[i - 2]) + S[i - 7] + SSIG0(S[i - 15]) + S[i - 16];
		S[i] = S[i] & 0xFFFFFFFF;
	}

	unsigned long laik1;
	unsigned long laik2;
		unsigned long a=H0;
		unsigned long b=H1;
		unsigned long c=H2;
		unsigned long d=H3;
		unsigned long e = H4;
			unsigned long f = H5;
			unsigned long g = H6;
			unsigned long h = H7;


			for (int i = 0; i < 64; i++) {
				laik1 = h + EP1(e) + CH(e, f, g) + E[i] + S[i];
}
			laik2 = EP0(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = (d+laik1) & 0xFFFFFFFF;
			d = c;
			c = b;
			b = a;
			a = (laik1+laik2) & 0xFFFFFFFF;
			H0=(H0+a) & 0xFFFFFFFF;
			H1 = (H1 + b) & 0xFFFFFFFF;
			H2 = (H2 + c) & 0xFFFFFFFF;
			H3 = (H3 + d) & 0xFFFFFFFF;
			H4 = (H4 + e) & 0xFFFFFFFF;
			H5 = (H5 + f) & 0xFFFFFFFF;
			H6 = (H6 + g) & 0xFFFFFFFF;
			H7 = (H7 + h) & 0xFFFFFFFF;

		cout<< show_as_hex(H0) + show_as_hex(H1) + show_as_hex(H2) +
				show_as_hex(H3) + show_as_hex(H4) + show_as_hex(H5) +
				show_as_hex(H6) + show_as_hex(H7)<<endl;

}
string show_as_hex(unsigned long input)
{
	bitset<32> bs(input);
	unsigned n = bs.to_ulong();

	stringstream sstream;
	sstream << std::hex << std::setw(8) << std::setfill('0') << n;
	string temp;
	sstream >> temp;

	return temp;
}
