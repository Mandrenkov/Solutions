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

#define print(label, var) cerrd << label << ": " << #var << " = " << var << '\n';

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

void solution() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, K, P;
        cin >> N >> K >> P;
        vector2D<int> A(N, vector<int>(K));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < K; ++j) {
                cin >> A[i][j];
            }
        }
        vector2D<int> S(N, vector<int>(K));
        for (int i = 0; i < N; ++i) {
            S[i][0] = A[i][0];
            for (int j = 1; j < K; ++j) {
                S[i][j] = S[i][j - 1] + A[i][j];
            }
        }
        vector2D<int> dp(N * K + 1, vector<int>(P + 1));
        for (int i = 0; i <= N * K; ++i) {
            dp[i][0] = 0;
        }
        for (int j = 1; j <= P; ++j) {
            dp[1][j] = A[0][0];
        }
        for (int i = 1; i <= N * K; ++i) {
            int stack = (i - 1) / K;
            int plate = (i - 1) % K;
            for (int j = 1; j <= P; ++j) {
                if (plate + 1 <= j) {
                    dp[i][j] = max(dp[i - plate - 1][j - plate - 1] + S[stack][plate], dp[i - 1][j]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        cout << "Case #" << t << ": " << dp.back().back() << '\n';
    }
}