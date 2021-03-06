#include <bits/stdc++.h>

using namespace std;

// Common Utilities
//______________________________________________________________________________

// Macros
#ifdef DEBUG
    #define cerrd if (DEBUG) cerr
#else
    #define cerrd if (false) cerr
#endif

// Types
template <typename T> using vector1D = vector<T>;
template <typename T> using vector2D = vector<vector1D<T>>;
template <typename T> using vector3D = vector<vector2D<T>>;
template <typename T> using uset = unordered_set<T>;
template <typename K, typename V> using umap = unordered_map<K, V>;

// Output stream overloads.
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i == 0) {
            out << '[';
        }
        out << v[i];
        if (i < v.size() - 1) {
            out << ", ";
        } else {
            out << ']';
        }
    }
    return out;
}

template <typename T>
ostream& operator<<(ostream& out, const deque<T>& d) {
    if (d.size() == 0) {
        return out << "[]";
    }

    out << '[' << d[0];
    for (int i = 1; i < d.size(); ++i) {
        out << ' ' << d[i];
    }
    return out << ']';
}

template <typename T>
ostream& operator<<(ostream& out, const set<T>& s) {
    if (s.size() == 0) {
        return out << "{}";
    }

    out << '{' << *s.begin();
    for (auto it = ++s.begin(); it != s.end(); ++it) {
        out << ' ' << *it;
    }
    return out << '}';
}

template <typename T>
ostream& operator<<(ostream& out, const multiset<T>& s) {
    return out << vector<T>(s.begin(), s.end());
}

template <typename T>
ostream& operator<<(ostream& out, const unordered_set<T>& s) {
    if (s.size() == 0) {
        return out << "{}";
    }

    vector<T> v(s.begin(), s.end());
    sort(v.begin(), v.end());

    out << '{' << v[0];
    for (int i = 1; i < v.size(); ++i) {
        out << ' ' << v[i];
    }
    return out << '}';
}

template <typename K, typename V>
ostream& operator<<(ostream& out, const map<K, V>& m) {
    if (m.size() == 0) {
        return out << "{}";
    }

    out << "{\n";
    for (const auto& p : m) {
        const K& key = p.first;
        out << "    " << key << ": " << m.at(key) << '\n';
    }
    return out << '}';
}

template <typename K, typename V>
ostream& operator<<(ostream& out, const unordered_map<K, V>& m) {
    if (m.size() == 0) {
        return out << "{}";
    }

    vector<K> keys;
    for (const auto& p : m) {
        keys.push_back(p.first);
    }
    sort(keys.begin(), keys.end());

    out << "{\n";
    for (const auto& key : keys) {
        out << "    " << key << ": " << m.at(key) << '\n';
    }
    return out << '}';
}

template <typename F, typename S>
ostream& operator<<(ostream& out, const pair<F, S>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<typename T, typename U>
struct hash<pair<T, U>> {
    size_t operator()(const pair<T, U>& p) const noexcept {
        return hash<T>{}(p.first) ^ (hash<U>{}(p.second) << 1);
    }
};

void solution();

// Initalize the execution environment and call the solution function.
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solution();
    return 0;
}

// Solution
// ______________________________________________________________________________

constexpr long long MOD = 1E9;

pair<long long, long long> move(const vector<int>& brackets, string& S, int beg, int end) {
    long long dx = 0;
    long long dy = 0;
    for (int i = beg; i < end; ++i) {
        char c = S[i];
        if ('2' <= c && c <= '9') {
            auto [idx, idy] = move(brackets, S, i + 2, brackets[i + 2]);
            dx += (c - '0') * idx;
            dy += (c - '0') * idy;
            i = brackets[i + 2];
        } else if (c == 'N') {
            --dy;
        } else if (c == 'S') {
            ++dy;
        } else if (c == 'E') {
            ++dx;
        } else if (c == 'W') {
            --dx;
        }
        dx = (MOD + dx % MOD) % MOD;
        dy = (MOD + dy % MOD) % MOD;
    }
    return {dx, dy};
}

void solution() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        string S;
        cin >> S;
        vector<int> brackets(S.size());
        vector<int> stack = {-1};
        for (int i = S.size() - 1; i >= 0; --i) {
            brackets[i] = stack.back();
            if (S[i] == '(') {
                stack.pop_back();
            } else if (S[i] == ')') {
                stack.push_back(i);
            }
        }
        const auto [dx, dy] = move(brackets, S, 0, S.size());
        cout << "Case #" << t << ": " << (dx + 1) << ' ' << (dy + 1) << '\n';
    }
}
