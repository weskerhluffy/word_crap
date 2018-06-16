#include <algorithm> 
#include <iostream> 
#include <string> 
#include <cstdio> 
#include <map> 
#include <queue> 
using namespace std;

int max_size;
string words[100000];
int ifrontword, ilastword;

bool mycmp(pair<const string, size_t>& lhs, pair<const string, size_t>& rhs) {
	if (lhs.second == rhs.second)
		return rhs.first < lhs.first;
	else
		return lhs.second < rhs.second;
}
map<string, size_t>::iterator it;

#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <queue>

class Counter {
public:
	Counter(std::size_t size) :
			max_size(size) {
	}

	void AddWord(const std::string& word) {
		if (words.size() == max_size) {
			auto it = counts.find(words.front());
			--it->second;
			if (it->second == 0) {
				counts.erase(it);
			}
			words.pop();
		}
		words.push(word);
		++counts[word];
	}

	const std::pair<const std::string, std::size_t>& getMax() const {
		return *std::max_element(counts.begin(), counts.end(), [](const std::pair<const std::string, std::size_t>& lhs, const std::pair<const std::string, std::size_t>& rhs)
				{
					return std::tie(lhs.second, rhs.first) < std::tie(rhs.second, lhs.first);
				});
	}

private:
	std::size_t max_size;
	std::queue<std::string> words;
	std::map<std::string, std::size_t> counts;
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, k;
	int tc, cs = 0;
	string word;
	scanf("%d", &tc);
	while (tc--) {
		cout << "Case " << ++cs << ":" << endl;

		scanf("%d%d", &n, &k);

		max_size = k;
		Counter counter(max_size);

		ilastword = ifrontword = 0;
		while (n--) {
			cin >> word;
			counter.AddWord(word);
			const auto& p = counter.getMax();
			cout << p.first << " " << p.second << endl;
		}
	}
	return 0;
}
