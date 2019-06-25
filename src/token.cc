#include<algorithm>
#include"token.h"
using namespace std;

Tokenizer::Tokenizer()
{}

void Tokenizer::quote(string open, string close)
{
	quote_.push_back({open, close});
}

void Tokenizer::escape(char c)
{
	escape_ = c;
}

void Tokenizer::separate(string s)
{
	separate_.push_back(s);
}

vector<pair<size_t, size_t>>
Tokenizer::quo_find(string s, string o, string c) const
{
	vector<pair<size_t, size_t>> r;
	for(size_t begin=0, end=0; begin != string::npos && end != string::npos;) {
		do begin = s.find(o, end);
		while(find(escape_pos_.begin(), escape_pos_.end(), begin - 1)
				!= escape_pos_.end());
		do end = s.find(c, begin);
		while(find(escape_pos_.begin(), escape_pos_.end(), end - 1)
				!= escape_pos_.end());
		r.push_back({begin, end});
	}
}
vector<pair<size_t, size_t>>
Tokenizer::quo_find(string s, size_t beg, size_t end, string o, string c) const
{//find quotes between beg and end of string s
	s = s.substr(beg, end - beg + 1);
	auto r = s.quo_find(s, o, c);
	for(auto &[a, b] : r) a += beg, b += beg;
	return r;
}
vector<string> Tokenizer::tokenize(string s)
{
	for(size_t it = s.find(escape_); it != string::npos;) {
		escape_pos_.push_back(it);
		it = s.find(escape_, it + 2);// case esc+esc
	}
	for(const string &[o, c] : quote_) {
		sort(quote_pos_.begin(), quote_pos_.end());
		size_t start = 0;
		for(const size_t &[a, b] : quote_pos_]) {
			auto quotes = quo_find(s, start, a - 1, o, c);
			start = b + c.size();
			quote_pos_.insert(quote_pos_.end(), quotes.begin(), quotes.end());
		}
	}
	sort(quote_pos_.begin(), quote_pos_.end());

	

}
