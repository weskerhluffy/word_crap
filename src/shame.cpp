#include <algorithm> 
#include <iostream> 
#include <string> 
#include <cstdio> 
#include <map> 
#include <queue> 
using namespace std; 

int max_size; 
string words[100000]; 
map<string, size_t> counts; 
int ifrontword,ilastword; 

bool mycmp(pair<const string, size_t>& lhs, pair<const string, size_t>& rhs){ 
    if (lhs.second==rhs.second) return rhs.first<lhs.first; 
    else return lhs.second<rhs.second; 
} 
map<string, size_t>::iterator it; 

void AddWord(string& word){  
    if (ilastword-ifrontword == max_size) { 
    counts[words[ifrontword]]--; 
    if (counts[words[ifrontword]]==0) 
     counts.erase(words[ifrontword]); 
    ifrontword++; 
    } 
    words[ilastword++]=word; 
    counts[word]++; 
} 

pair<const string, size_t>& getMax() { 
    return *max_element(counts.begin(), counts.end(), mycmp); 
} 

int main(){ 
    ios_base::sync_with_stdio(false); 
    int n,k; 
    int tc,cs=0; 
    string word; 
    scanf("%d",&tc); 
    while(tc--){ 
    cout<<"Case "<<++cs<<":"<<endl; 
    scanf("%d%d",&n,&k); 
    max_size=k; 
    counts.clear(); 
    ilastword=ifrontword=0; 
    while(n--){ 
     cin>> word; 
     AddWord(word); 
     pair<const string, size_t> &p = getMax(); 
     cout << p.first << " " << p.second << endl; 
    } 
    } 
    return 0; 
} 
