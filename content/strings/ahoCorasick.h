/**
 * Description: Aho-Corasick algorithm for finding multiple patterns in a text.
 *  Builds a trie from a set of patterns and adds failure links to efficiently transition between states.
 * Time: $O(L + N)$, where $L$ is the sum of pattern lengths and $N$ is the text length.
 */
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; };

struct TrieNode {
	TrieNode* children[ALPHABETS];
	TrieNode* failure;
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
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (int i = 0; i < ALPHABETS; ++i) if (trie->children[i]) {
		trie->children[i]->failure = trie;
		Q.push(trie->children[i]);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (int i = 0; i < ALPHABETS; ++i) if (here->children[i]) {
			TrieNode* there = here->children[i];
			TrieNode* p = here->failure;
			while (p != trie && p->children[i] == nullptr) p = p->failure;
			if (p->children[i]) p = p->children[i];
			there->failure = p;
			if (p->terminal) there->terminal = true;
			Q.push(there);
		}
	}
}

// check s's substring
bool query(string& s, TrieNode* trie) {
	TrieNode* p = trie;
	for (auto& i: s) {
		int next = toNumber(i);
		while (p != trie && p->children[next] == nullptr) p = p->failure;
		if (p->children[next]) p = p->children[next];
		if (p->terminal) return true;
	}
	return false;
}