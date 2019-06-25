#include<vector>
#include<string>
#include<utility>

class Tokenizer 
{//inside quote separator is invalid, quote has priority. "[ ]" -> " "
public:
	Tokenizer();
	std::vector<std::string> tokenize(std::string s);
	void quote(std::string open, string close);
	void separate(std::string sep);
	void escape(char esc);
	
protected:
	std::vector<std::string> separate_;
	std::vector<size_t> sep_pos_, escape_pos_;
	std::vector<std::pair<std::string>> quote_;
	std::vector<std::pair<size_t, size_t>> quote_pos_;
	char escape_ = '\\';

private:
	std::vector<std::pair<size_t, size_t>> quo_find(std::string s, size_t begin,
			size_t end, std::string open, std::string close) const;
	std::vector<std::pair<size_t, size_t>> quo_find(std::string s,
			std::string open, std::string close) const;
};
