#include <bits/stdc++.h>

using namespace std;

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

// Output Stream Overloads
template<
    // Multiple template arguments may be needed for containers like std::map.
    template<class...> class Range, class... Ts,
    // This overload must be disabled for std::string to avoid ambiguity.
    typename = std::enable_if_t<!std::is_same_v<Range<Ts...>, std::string>>
>
std::ostream& operator<<(std::ostream& out, const Range<Ts...>& range) {
    out << '{';
    for (auto it = range.begin(); it != range.end(); ++it) {
        out << *it << (std::next(it) != range.end() ? ", " : "");
    }
    return out << '}';
}

template <class F, class S>
ostream& operator<<(ostream& out, const pair<F, S>& pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
}

// Hash Template Specializations
template<class T, class U>
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
}

// -----------------------------------------------------------------------------

void cut(map<int, int>& tiles, int width, int height) {
    if (tiles.empty()) {
        return;
    }
    if (width < height) {
        swap(width, height);
    }
    if (height == 0) {
        return;
    }
    auto it = tiles.upper_bound(height);
    if (it == tiles.begin()) {
        return;
    }
    int tile = (--it)->first;
    if (--tiles[tile] == 0) {
        tiles.erase(tile);
    }
    cut(tiles, tile, height - tile);
    cut(tiles, width - tile, tile);
    cut(tiles, width - tile, height - tile);
}

void solution() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M;
        cin >> N >> M;
        map<int, int> tiles;
        for (int i = 0; i < N; ++i) {
            int tile;
            cin >> tile;
            ++tiles[1 << tile];
        }
        int bought = 0;
        while (!tiles.empty()) {
            cut(tiles, M, M);
            ++bought;
        }
        cout << "Case #" << t << ": " << bought << '\n';
    }
}
