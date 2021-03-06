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

struct BIT {
    vector<long long> values;

    BIT(int size) {
        values = vector<long long>(size + 1);
    }

    long long get(long long index) {
        long long sum = 0;
        // cerr << "Doing get(" << index << ")\n";
        for (long long i = index; i > 0; i -= i & -i) {
            sum += values[i];
        }
        // cerr << "get(" << index << ") = " << sum << '\n';
        return sum;
    }

    void set(long long index, long long value) {
        long long add = value - query(index, index);
        for (long long i = index; i < values.size(); i += i & -i) {
            values[i] += add;
        }
    }

    long long query(long long L, long long R) {
        return get(R) - get(L - 1);
    }
};

constexpr long long flatify(long long index, long long value) {
    return (index % 2 == 1 ? 1 : -1) * value;
}

constexpr long long rampify(long long index, long long value) {
    return (index % 2 == 1 ? 1 : -1) * index * value;
}

void solution() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, Q;
        cin >> N >> Q;
        BIT bit_flat(N);
        BIT bit_ramp(N);
        for (long long idx = 1; idx <= N; ++idx) {
            long long val;
            cin >> val;
            bit_flat.set(idx, flatify(idx, val));
            bit_ramp.set(idx, rampify(idx, val));
            cerrd << "Flat[" << idx << "] (" << flatify(idx, val) << ") = " << bit_flat.values << '\n';
            cerrd << "Ramp[" << idx << "] (" << rampify(idx, val) << ") = " << bit_ramp.values << '\n';
        }
        long long sum = 0;
        for (int i = 0; i < Q; ++i) {
            char type;
            cin >> type;
            if (type == 'U') {
                long long idx, val;
                cin >> idx >> val;
                bit_flat.set(idx, flatify(idx, val));
                bit_ramp.set(idx, rampify(idx, val));
            } else {
                int L, R;
                cin >> L >> R;
                long long query = (L % 2 == 1 ? 1 : -1) * bit_ramp.query(L, R);
                query += (L % 2 == 0 ? 1 : -1) * (L - 1) * bit_flat.query(L, R);
                cerrd << "Q[" << i << "] = " << query << '\n';
                sum += query;
            }
        }
        cout << "Case #" << t << ": " << sum << '\n';
    }
}
