#include <algorithm>
#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <set>
#include <sstream>
#include <regex>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	int u = 1;
	while (t--) {
		int n, k, maxm = 0;
		cin >> n >> k;
		cout << "Case " << u++ << ":" << endl;
		unordered_map<string, int> m;
		queue<string> q;
		set<string> v[n + 1];
		string s, l;
		string p = "";
		int i = 0;
		while (i < n) {
//			cin >> s;
// XXX: https://stackoverflow.com/questions/5882872/reading-a-full-line-of-input
			getline(cin, s);
// XXX: https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
			s = std::regex_replace(s, std::regex("\\s+"), "");
			if (s.empty()) {
				continue;
			}
//			cout << "puta madre '" << s << "' " << endl;
			if (q.size() >= k) {
				p = q.front();
				q.pop();
				v[m[p]].erase(p);
				m[p]--;

//				cout << "conteo de '" << p << "' dism a " << m[p] << endl;
				v[m[p]].insert(p);

			}
			q.push(s);
			v[m[s]].erase(s);
			m[s]++;
//			cout << "conteo de '" << s << "' aum a " << m[s] << endl;
			v[m[s]].insert(s);
			if (!v[maxm].size()) {
				maxm = 0;
			}
			if (m[s] > maxm) {
				l = s;
				maxm = m[s];
			}
//			cout << "ass '" << p << "' " << endl;
			if (!p.empty()) {
				if (m[p] > maxm) {
					maxm = m[p];
					l = p;
				}
			}

			set<string>::iterator it = v[maxm].begin();
			cout << *it << " " << maxm << endl;
			i++;
		}
	}
	return 0;
}
