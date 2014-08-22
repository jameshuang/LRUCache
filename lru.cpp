/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#include <map>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class LruCache{
public:
    LruCache(int capacity) : _cap(capacity) {}
    
    void peek(string key) {
        auto it = _map.find(key);
        if (it == _map.end()) {
            cout << "NULL" << endl;
        }
		else {
			cout << it->second->second << endl;
		}
    }
    
    void get(string key) {
        auto it = _map.find(key);
        if (it == _map.end()) {
            cout << "NULL" << endl;
            return;
        }
        auto p = *(it->second);
        _list.erase(it->second);
        _list.push_front(p);
        _map[key] = _list.begin();
        cout << p.second << endl;
        return;
    }

    void set(string key, int value) {
        auto it = _map.find(key);
        if (it != _map.end()) {
            _list.erase(it->second);
        }
        _list.push_front(make_pair(key, value));
        _map[key] = _list.begin();
        bound(_cap);
        return;
    }

    void bound(int cap) {
        if (cap < 1) return;
        _cap = cap;
        while (_list.size() > _cap) {
            auto p = _list.back();
            _list.pop_back();
            _map.erase(p.first);
        }
    }

    void dump() {
        priority_queue<string, vector<string>, greater<string>>heap;
        
        for (auto &p : _list) heap.push(p.first);
        while (!heap.empty()) {
            string k = heap.top();
            heap.pop();
            cout << k;
            cout << " ";
            cout << (*_map[k]).second;
            cout << endl;
        }
    }

private:
    map<string, list<pair<string, int>>::iterator> _map;
    list<pair<string, int>> _list;
    int _cap;
};
    
int main(int argc, char *argv[]) {
	LruCache lru(100);
	int lines;
	if (!(cin >> lines && lines >= 0)) {
		return -1;
	}
	
	bool bounded = false;
	string cmd;
	while (lines > 0) {
		if (!(cin >> cmd)) break;
		else if (cmd == "BOUND") {
			int b;
			if (cin >> b && b > 0) lru.bound(b);
			else break;
			bounded = true;
		}
		else if (!bounded) break;
		else if (cmd == "SET") {
			string k;
			int    v;
			if (cin >> k && cin >> v) lru.set(k, v);
			else break;
		}
		else if (cmd == "GET") {
			string k;
			if (cin >> k) lru.get(k);
			else break;
		}
		else if (cmd == "PEEK") {
			string k;
			if (cin >> k) lru.peek(k);
			else break;
		}
		else if (cmd == "DUMP") lru.dump();
		else break;
		--lines;
	}
	if (lines > 0) return -1;
	return 0;
}

