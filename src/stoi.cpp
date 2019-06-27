#include<exception>
#include<iostream>
#include<string>
using namespace std;

int s2i(string s) {
	int r = 3;
	try {
		r = stoi(s);
	} catch(...) {} 
	//	r = 3;
	return r;
}
int main()
{
	int i;
	try {
		i = stoi("new");
	} catch(const exception &e) {
		cerr << "error : " << e.what() << endl;
		i = 22;
	} catch(...) {
		cerr << "some error" << endl;
	}
	cout << i;

	cout << s2i("new");
}

