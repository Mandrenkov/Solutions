#include <bits/stdc++.h>

using namespace std;

// Common Utilities
//______________________________________________________________________________

// Macros
#ifdef D3BUG
    #define cerrd if (D3BUG) cerr
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
// _____________________________________________________________________________

string toposort(const unordered_set<int>& L, const vector<vector<bool>>& G) {
    vector<int> V(26, false);
    string order;

    const std::function<void(int)> dfs = [&](int node) {
        if (!V[node]) {
            cerrd << "Visiting " << (char) (node + 'A') << '\n';
            for (int next : L) {
                if (G[node][next]) {
                    dfs(next);
                }
            }
            V[node] = true;
            order += node + 'A';
        }
    };
    for (int letter : L) {
        dfs(letter);
    }
    return order;
}

void solution() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int R, C;
        cin >> R >> C;
        vector<string> grid(R);
        unordered_set<int> L;
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
            for (char c : grid[i]) {
                L.emplace(c - 'A');
            }
        }
        vector<vector<bool>> G(26, vector<bool>(26, 0));
        for (int r = 0; r < R - 1; ++r) {
            for (int c = 0; c < C; ++c) {
                char top = grid[r][c] - 'A';
                char bot = grid[r + 1][c] - 'A';
                if (top != bot) {
                    G[top][bot] = true;
                }
            }
        }

        bool stable = true;
        vector<vector<bool>> D = G;
        for (int k = 0; k < 26 && stable; ++k) {
            for (int i = 0; i < 26 && stable; ++i) {
                for (int j = 0; j < 26 && stable; ++j) {
                    if (G[i][k] && G[k][j]) {
                        G[i][j] = true;
                        stable = i != j;
                    }
                }
            }
        }

        string ans = !stable ? "-1" : toposort(L, G);
        cout << "Case #" << t << ": " << ans << '\n';
    }
}
