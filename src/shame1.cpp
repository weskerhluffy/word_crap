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

class Caca {
public:
	string cadena;
	int conteo;

	Caca() {
		cadena = "";
		conteo = 0;
	}
	Caca(string c) {
		cadena = c;
		conteo = 0;
	}

};

// XXX: https://stackoverflow.com/questions/1549930/c-equivalent-of-java-tostring
// XXX: http://www.cplusplus.com/forum/general/34661/
ostream& operator<<(ostream& outs, const Caca & obj) {
	return outs << "'" << obj.cadena << "':" << obj.conteo << "(" << &obj << ")";
}

/*
 bool compara_caca(const caca &a, const caca &b) {
 bool r = false;
 if (a.conteo == b.conteo) {
 r = a < b;
 } else {
 r = a.conteo > b.conteo;
 }
 //	return s1.str() < s2.str();
 return r;
 }
 */
// XXX: http://neutrofoton.github.io/blog/2016/12/30/c-plus-plus-set-with-custom-comparator/

struct compara_caca {
	bool operator()(const Caca *a, const Caca *b) {
		bool r = false;
		if (a->conteo == b->conteo) {
			r = a->cadena.compare(b->cadena) < 0;
		} else {
			r = a->conteo > b->conteo;
		}
//	return s1.str() < s2.str();
//		cout << "a " << *a << " comp " << *b << " r " << r << endl;
		return r;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	int u = 1;
	while (t--) {
		int n, k = 0;
		cin >> n >> k;
		cout << "Case " << u++ << ":" << endl;
		unordered_map<string, Caca *> m;
		queue<string> q;
		set<Caca *, compara_caca> v;
		string s, l;
		string p;
		int i = 0;
		Caca *ass = NULL;
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
				ass = m[p];
//				cout << "conteo o de '" << p << "' s " << *ass << endl;
				v.erase(ass);

				ass->conteo--;

//				cout << "conteo de '" << p << "' dism a " << *ass << endl;
				v.insert(ass);

			}
			q.push(s);
// XXX: https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
			unordered_map<string, Caca*>::iterator it1 = m.find(s);
			if (it1 == m.end()) {
				ass = new Caca(s);
//				cout << "creado " << *ass << " mapeado a " << s << endl;
				m[s] = ass;
			} else {
				ass = it1->second;
				v.erase(ass);
			}
			ass->conteo++;
//			cout << "conteo de '" << s << "' aum a " << *ass << endl;
			v.insert(ass);
			set<Caca*, compara_caca>::iterator it = v.begin();
			cout << (*it)->cadena << " " << (*it)->conteo << endl;
			i++;
		}
	}
	return 0;
}
