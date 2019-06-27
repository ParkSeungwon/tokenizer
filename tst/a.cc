#include<catch.hpp>
#include<sstream>
#include<iostream>
#include"src/token.h"
using namespace std;

TEST_CASE("stringstream") {
	stringstream ss; 
	string s = "hello";
	ss << s;
	for(char c; ss >> c; ) cout << c;
	s = "Park";
	ss << s;
	for(char c; ss >> c; ) cout << c;
}

TEST_CASE("quo_find") {
}
