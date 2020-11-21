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

    auto s1 = range(1, 8).step(2).size();
    cout << "Expected result for 'range(1, 8).step(2).size()' is 4: " << std::boolalpha << (s1 == 4) << '\n';
    if (s1 != 4) {
        cout << " - found " << s1 << " instead!\n";
    }

    auto s2 = range(8.0, 1.0).step(-2.0).size();
    cout << "Expected result for 'range(8.0, 1.0).step(-2.0).size()' is 4: " << std::boolalpha << (s2 == 4) << '\n';
    if (s2 != 4) {
        cout << " - found " << s2 << " instead!\n";
    }

    auto s3 = range(8, 1).step(-2).size();
    cout << "Expected result for 'range(8, 1).step(-2).size()' is 4: " << std::boolalpha << (s3 == 4) << '\n';
    if (s3 != 4) {
        cout << " - found " << s3 << " instead!\n";
    }

    auto s4 = range(0.1, 0.11).step(2).size();
    cout << "Expected result for 'range(0.1, 0.11).step(2).size()' is 1: " << std::boolalpha << (s4 == 1) << '\n';
    if (s4 != 1) {
        cout << " - found " << s4 << " instead!\n";
    }

    auto s5 = range(-7, 1).step(7).size();
    cout << "Expected result for 'range(-7, 1).step(7).size()' is 1: " << std::boolalpha << (s5 == 2) << '\n';
    if (s5 != 2) {
        cout << " - found " << s5 << " instead!\n";
    }
}
