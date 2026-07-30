/**
 * Description: Trie (prefix tree) for efficient string storage and retrieval.
 *  Supports insertion, search, and deletion of strings.
 * Time: $O(L)$ per operation, where $L$ is the length of the string.
 */
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; };

struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;

	TrieNode(): terminal(false) { memset(children, 0, sizeof(children)); }
	~TrieNode() { for (int i = 0; i < ALPHABETS; ++i) if (children[i]) delete children[i]; }
	void insert(const string& s, int idx = 0) {
		if (idx == s.size()) terminal = true;
		else {
			int next = toNumber(s[idx]);
			if (children[next] == nullptr) children[next] = new TrieNode();
			children[next]->insert(s, idx + 1);
		}
	}
	bool find(const string& s, int idx = 0) {
		if (idx == s.size()) return this->terminal;
		int next = toNumber(s[idx]);
		if (children[next] == nullptr) return false;
		return children[next]->find(s, idx + 1);
	}
	bool erase(const string& s, int idx = 0) {
		if (idx == s.size()) {
			terminal = false;
			for (int i = 0; i < ALPHABETS; ++i) if (children[i]) return false;
			return true;
		}
		int next = toNumber(s[idx]);
		if (children[next] == nullptr) return false;
		if (children[next]->erase(s, idx + 1)) {
			delete children[next];
			children[next] = nullptr;
		}
		if (terminal) return false;
		for (int i = 0; i < ALPHABETS; ++i) if (children[i]) return false;
		return true;
	}
};