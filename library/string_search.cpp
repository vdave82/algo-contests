// String Search algorithms
//
// 1) Knuth-Morris-Pratt search (https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
//    Searches word of size |W| in string of size |S| on O(|W| + |S|) time.

#include <string>
#include <vector>

// Knuth-Morris-Pratt
// Works with both T == std::string and T == std::vector<U>.

// Builds the prefix lookup table for the word being searched.
template<typename TWord> std::vector<int> kmp_build_table(const TWord& S) {
	std::vector<int> T(S.size() + 1);

	T[0] = -1;
	int pos = 1, cnd = 0;
	while (pos < S.size()) {
		if (S[pos] == S[cnd]) {
			T[pos] = T[cnd];
		}
		else {
			T[pos] = cnd;
			while (cnd >= 0 && S[pos] != S[cnd]) {
				cnd = T[cnd];
			}
		}
		pos++;
		cnd++;
	}
	T[pos] = cnd;

	return T;
}

// Returns the list of starting positions where W is found in S.
template<class TWord> std::vector<int> kmp_search(const TWord& W, const TWord& S) {
	std::vector<int> T = kmp_build_table(W);
	std::vector<int> result;

	int posW = 0;
	int posS = 0;
	while (posS < S.size()) {
		if (W[posW] == S[posS]) {
			posW++;
			posS++;
			if (posW == W.size()) {
				result.push_back(posS - posW);
				posW = T[posW];
			}
		}
		else {
			posW = T[posW];
			if (posW < 0) {
				posS++;
				posW++;
			}
		}
	}

	return result;
}
