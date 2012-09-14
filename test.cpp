#include <iostream>

#include "range.hpp"

using std::cout;
using util::lang::range;

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
}
