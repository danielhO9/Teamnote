/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 */
#pragma once

// 0-index
struct UF {
	vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UF() = default;
	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
    int time() { return st.size(); }
    void rollback(int t) {
        while (st.size() > t) {
            auto [v, p, r] = st.back(); st.pop_back();
            par[v] = p;
            rk[v] = r;
        }
    }
	int find(int x) {
		if (par[x] == x) return x;
		return find(par[x]);
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
        st.push_back({x, par[x], rk[x]});
        st.push_back({y, par[y], rk[y]});
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
} uf;