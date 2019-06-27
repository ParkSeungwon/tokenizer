#include<sstream>
#include<iostream>
using namespace std;

int main() {
	stringstream ss; 
	string s = "3213,3213";
	ss << s;
	getline(ss, s, ',');
	cout << s;
	getline(ss, s, ',');
	cout << s;

}
