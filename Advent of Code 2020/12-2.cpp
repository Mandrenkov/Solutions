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

template<
    // Output stream overload for STL containers with one explicit type parameter.
    template<class> class Range, class T,
    typename = enable_if_t<is_same_v<Range<T>, deque<T>> ||
                           is_same_v<Range<T>, forward_list<T>> ||
                           is_same_v<Range<T>, list<T>> ||
                           is_same_v<Range<T>, multiset<T>> ||
                           is_same_v<Range<T>, set<T>> ||
                           is_same_v<Range<T>, unordered_multiset<T>> ||
                           is_same_v<Range<T>, unordered_set<T>> ||
                           is_same_v<Range<T>, vector<T>>>
>
ostream& operator<<(ostream& out, const Range<T>& range) {
    constexpr auto brackets = is_same_v<Range<T>, vector<T>> ? "[]" : "{}";
    out << brackets[0];
    for (auto it = range.begin(); it != range.end(); ++it) {
        out << *it << (next(it) != range.end() ? ", " : "");
    }
    return out << brackets[1];
}

template<
    // Output stream overload for STL containers with two explicit type parameters.
    template<class, class> class Range, class K, class V,
    typename = enable_if_t<is_same_v<Range<K, V>, map<K, V>> ||
                           is_same_v<Range<K, V>, multimap<K, V>> ||
                           is_same_v<Range<K, V>, unordered_map<K, V>> ||
                           is_same_v<Range<K, V>, unordered_multimap<K, V>>>
>
ostream& operator<<(ostream& out, const Range<K, V>& range) {
    out << '{';
    for (auto it = range.begin(); it != range.end(); ++it) {
        out << it->first << ": " << it->second << (next(it) != range.end() ? ", " : "");
    }
    return out << '}';
}

template <class F, class S>
ostream& operator<<(ostream& out, const pair<F, S>& duo) {
  return out << '(' << duo.first << ", " << duo.second << ')';
}

// Hash Template Specializations
template<class T, class U>
struct hash<std::pair<T, U>> {
    size_t operator()(const std::pair<T, U>& pair) const noexcept {
        return std::hash<T>{}(pair.first) ^ (std::hash<U>{}(pair.second) << 1);
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

struct Location {
    int x;
    int y;
};

struct Waypoint {
    Location offset;

    void translate(int direction, int distance) {
        switch (direction) {
            case 0: offset.y += distance; break; // North (N)
            case 1: offset.x += distance; break; // East  (E)
            case 2: offset.y -= distance; break; // South (S)
            case 3: offset.x -= distance; break; // West  (W)
        }
    }

    void rotate(int degrees) {
        int turns = degrees / 90;
        for (int i = 0; i < turns; ++i) {
            // [0 -1] * [x] = [-y]
            // [1  0]   [y]   [x]
            tie(offset.x, offset.y) = pair<int, int>{-offset.y, offset.x};
        }
    }
};

void solution() {
    int N;
    cin >> N;
    Waypoint waypoint{10, 1};
    Location ship = {0, 0};
    for (int i = 0; i < N; ++i) {
        string instruction;
        cin >> instruction;
        char action = instruction[0];
        if (action == 'L' || action == 'R') {
            int degrees = stoi(instruction.substr(1));
            if (action == 'R') {
                degrees = 360 - degrees;
            }
            waypoint.rotate(degrees);
        } else if (action == 'F') {
            int moves = stoi(instruction.substr(1));
            ship.x += moves * waypoint.offset.x;
            ship.y += moves * waypoint.offset.y;
        } else {
            int distance = stoi(instruction.substr(1));
            switch (action) {
                case 'N': waypoint.translate(0, distance); break;
                case 'E': waypoint.translate(1, distance); break;
                case 'S': waypoint.translate(2, distance); break;
                case 'W': waypoint.translate(3, distance); break;
            }
        }
    }
    cout << abs(ship.x) + abs(ship.y) << '\n';
}
