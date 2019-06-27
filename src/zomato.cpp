#include<sstream>
#include<fstream>
#include<regex>
#include<cassert>
#include"token.h"
#include"database/mysqldata.h"
using namespace std;

int s2i(string s) {
	int r = 0;
	try {
		r = stoi(s);
	} catch(...) { }
	return r;
}

string unquote(string s) {
	if(s[0] == '"' || s[0] == '\'') { 
		s.pop_back();
		s = s.erase(0, 1);
	}
	return s;
}
int main()
{
	SqlQuery sq[5];
	for(auto &a : sq) a.connect("localhost", "zeta", "cockcodk0", "site");
	sq[0].select("bangalore_zomato", "limit 1");
	sq[1].select("review", "limit 1");
	sq[2].select("cuisine", "limit 1");
	sq[3].select("dish_liked", "limit 1");
	sq[4].select("menu", "limit 1");
	string review, menu, type, city;
	float rate; int vote, cost; char c, br=',';

	ifstream f{"zomato.csv"};
	ofstream of{"error.txt"};
	string line;
	getline(f, line);//first line skip

	Tokenizer tk, tk2;
	tk.separate(",");
	tk2.separate(",");
	tk.quote("\"", "\"");
	tk2.quote("[", "]");
	tk2.quote("\"", "\"");

	for(int index=1; getline(f, line); index++) {
		string s;
		if(*line.rbegin() >= '0' && *line.rbegin() <= '9') {//telephone new line bug
			s = line + ',';
			getline(f, line);
		}
		s += line;
		size_t it = s.find(",\"[(");
		auto cols = tk.tokenize(s.substr(0, it));

//url, address, name, online_order, book_table, rate,  vote, tel, location, rest_type,
//dish_liked, cuisine,cost,review, menu, type, city;
		s = s.substr(it + 3);
		it = s.find(")]\",");
		review = s.substr(0, it + 1);
		s = s.substr(it + 4);//below review
		it = s.rfind(',');
		city = s.substr(it + 1);
		s = s.substr(0, it);
		it = s.rfind(',');
		type = s.substr(it + 1);
		menu = s.substr(0, it);
		for(string s : cols) cout << s << endl;
		stringstream ss;
		string phone1, phone2;
		ss << cols[5] << endl << unquote(cols[7]);
		ss >> rate;
		getline(ss, s);
		getline(ss, phone1, ',');
		getline(ss, phone2, ',');

		if(size_t it = cols[6].find(','); it != string::npos) cols[6].erase(it, 1);
		if(size_t it = cols[12].find(','); it != string::npos) cols[12].erase(it, 1);
		cout << "rate : " << rate << endl << "phone1 : " << phone1 << endl << "phone2 : " << phone2 << endl << "review : " << review << endl << "menu : " << menu << endl << "type : " << type << endl << "city : " << city << endl << endl;

		sq[0].insert(index, cols[0], unquote(cols[1]), cols[2], cols[3]=="Yes" ? 1 : 0,
				cols[4] == "Yes" ? 1 : 0, rate, s2i(cols[6]), phone1, phone2,
				cols[8], cols[9], stoi(cols[12]) / 2, type, city);
		ss.clear(); ss << unquote(cols[10]);//dish_liked
		while(getline(ss, s, ',')) sq[3].insert(index, s);
		ss.clear(); ss << unquote(cols[11]);//cuisine
		while(getline(ss, s, ',')) sq[2].insert(index, s);
		smatch m; regex e{R"(Rated (\d\.\d).+?\\n  )"};//? no greedy
		while(regex_search(review, m, e)) {
			ss.clear(); ss << m[1]; ss >> rate;
			review = m.suffix();//suffix function invalidate m[1]
			regex_search(review, m, regex{R"("?['"]\)[,\]])"});//? 0 or 1
			sq[1].insert(index, rate, m.prefix().str());//prefix is between two regex
			review = m.suffix();
		}
		if(menu != "[]") {
			menu = menu.substr(2, menu.size() - 4);
			ss.clear(); ss << menu;
			while(getline(ss, s, ',')) sq[4].insert(index, unquote(s));
		}
	}
}

