#include <iostream>
#include <vector>

#include "range.hpp"

using std::cout;
using util::lang::range;
using util::lang::indices;

int main() {
    for (auto i : range(1, 5))
        cout << i << "\n";

    for (auto u : range(0u))
        if (u == 3u) break;
        else         cout << u << "\n";

    for (auto c : range('a', 'd'))
        cout << c << "\n";

    for (auto u : range(20u, 29u).step(2u))
        cout << u << "\n";

    for (auto i : range(100).step(-3))
        if (i < 90) break;
        else        cout << i << "\n";

    std::vector<int> x{1, 2, 3};
    for (auto i : indices(x))
        cout << i << '\n';

    for (auto i : indices({"foo", "bar"}))
        cout << i << '\n';

    for (auto i : indices("foobar").step(2))
        cout << i << '\n';
}
