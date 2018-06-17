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
		unordered_map<string, std::set<Caca*, compara_caca>::iterator> m;
		queue<string> q;
		set<Caca *, compara_caca> v;
		string s, l;
		string p;
		int i = 0;
		std::pair<std::set<Caca *, compara_caca>::iterator, bool> culo;
		std::set<Caca*, compara_caca>::iterator ass;
		Caca *borrado = NULL;

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
				borrado = *ass;
////				cout << "conteo o de '" << p << "' s " << *borrado << endl;
				v.erase(ass);

				borrado->conteo--;

//				cout << "conteo de '" << p << "' dism a " << *borrado << endl;
				culo = v.insert(borrado);
				m[p] = culo.first;

			}
			q.push(s);
// XXX: https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
//			cout << "antes de bus en m " << endl;
			unordered_map<string, std::set<Caca*, compara_caca>::iterator>::iterator it1 =
					m.find(s);
//			cout << "despues de bus en m " << endl;
			if (it1 == m.end()) {
				borrado = new Caca(s);
//				cout << "creado " << borrado << " mapeado a " << s << endl;
			} else {
				ass = it1->second;
//				ass = m[s];
				borrado = *ass;
//				cout << "antes de borrar" << endl;
				v.erase(ass);
//				cout << "despes de borrar" << endl;
			}

			borrado->conteo++;

			culo = v.insert(borrado);
			//		cout << "conteo de '" << s << "' aum a " << *borrado << endl;
			ass = culo.first;
			m[s] = ass;

			set<Caca*, compara_caca>::iterator it = v.begin();
			cout << (*it)->cadena << " " << (*it)->conteo << endl;
			i++;
		}
	}
	return 0;
}
