#include<fstream>
#include<regex>
#include<boost/tokenizer.hpp>
#include"database/mysqldata.h"
using namespace std;
using namespace boost;

int main()
{
	SqlQuery sq[5];
	for(auto &a : sq) a.connect("localhost", "zeta", "cockcodk0", "site");
	sq[0].select("bangalore_zomato", "limit 1");
	sq[1].select("review", "limit 1");
	sq[2].select("cuisine", "limit 1");
	sq[3].select("dish_liked", "limit 1");
	sq[4].select("menu", "limit 1");
//url, address, name, online_order, book_table, rate,  vote, tel, location, rest_type,
//dish_liked, cuisine,cost,review, menu, type, city;
	string cols[17];
	string type, city;
	float rate; int vote, cost; char c, br=',';

	ifstream f{"zomato.csv"};
	string line;
	getline(f, line);//first line skip
	for(int index=1; getline(f, line); index++) {
		stringstream ss; string s;
		if(*line.rbegin() >= '0' && *line.rbegin() <= '9') {//telephone new line bug
			ss << line << ',';
			getline(f, line);
		}
		ss << line;
		tokenizer<escaped_list_separator<char>> tok{ss.str()};
		for(auto it = tok.begin(); it != tok.end(); ++it) {
			cout << "\nnew token : " << *it << endl;
		}
//		size_t k = line.find("\"[(");
//		size_t l = line.find(")]\"");
//		string review;
//		if(k != string::npos) {
//			review = line.substr(k + 1, l - k + 1);
//			line.replace(k + 1, l - k + 1, "review");
//		}
//		k = line.find("\"[");
//		l = line.find("]\"");
//		string menu;
//		if(k != string::npos) {
//			menu = line.substr(k + 2, l - k - 2);
//			line.replace(k, l - k + 2, "menu");
//		}
//		ss << line;
//
//		for(int i=0; ss >> noskipws >> c;) {
//			if(c == br) {
//				cols[i++] = s;
//				s = "";
//				if(c == '"') ss >> c;//,
//				ss >> c;//first character of the field
//				if(c == ',') {//no data
//					cols[i++] = s;
//					ss >> c;
//				}
//				if(c == '"') br = '"';//next column
//				else br = ',', s += c;
//			} else s += c;
//		}
//		cols[16] = s;
//
//		for(int i=0; i<17; i++) cout << i << " : " << cols[i] << endl;
//		ss.clear(); ss << cols[7];
//		string phone1, phone2;
//		getline(ss, phone1, ',');
//		getline(ss, phone2, ',');
//
//		ss.clear(); ss << cols[5];//3.4/5.0
//		float rate;
//		ss >> rate >> s;
//
//		if(size_t it = cols[6].find(','); it != string::npos) cols[6].erase(it, 1);
//		if(size_t it = cols[12].find(','); it != string::npos) cols[12].erase(it, 1);
//		sq[0].insert(index, cols[0], cols[1], cols[2], cols[3] == "Yes" ? 1 : 0,
//				cols[4] == "Yes" ? 1 : 0, rate, stoi(cols[6]), phone1, phone2,
//				cols[8], cols[9], stoi(cols[12]) / 2, cols[15], cols[16]);
//		ss.clear(); ss << cols[10];
//		while(getline(ss, s, ',')) sq[3].insert(index, s);
//		ss.clear(); ss << cols[11];
//		while(getline(ss, s, ',')) sq[2].insert(index, s);
//		smatch m; regex e{R"(Rated (\d\.\d).+?\\n  )"};//? no greedy
//		while(regex_search(review, m, e)) {
//			ss.clear(); ss << m[1]; ss >> rate;
//			review = m.suffix();//suffix function invalidate m[1]
//			regex_search(review, m, regex{R"("?['"]\)[,\]])"});//? 0 or 1
//			sq[1].insert(index, rate, m.prefix().str());//prefix is between two regex
//			review = m.suffix();
//		}
//		if(menu != "") {
//			ss.clear(); ss << menu;
//			while(getline(ss, s, ',')) sq[4].insert(index, s);
//		}
	}
}

