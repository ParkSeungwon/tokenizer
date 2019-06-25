#include<sstream>
#include<iostream>
using namespace std;

int main() {
	stringstream ss; 
	string s = "hello";
	ss << s;
	char c;
	for(int i=0; i<5; i++) { 
		ss >> c; cout << c;
	}
	s = "Park";
	cin >> c;
//	ss.clear();
	ss << s;
	for(char c; ss >> c; ) cout << c;
}
