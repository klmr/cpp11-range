#include "range.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename R>
void print_range(R const& range) {
    using T = typename std::iterator_traits<decltype(range.begin())>::value_type;
    std::copy(range.begin(), range.end(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << "\n";
}

int main() {
    using std::cout;
    using util::lang::range;
    using util::lang::indices;

    cout << "Basic usage: iterating over a range of numbers.\n";
    for (auto i : range(1, 5)) {
        cout << i << " ";
    }
    cout << "\n";

    cout << "Ranges can be “infinite”.\n";
    for (auto u : range(0u)) {
        if (u == 3u) {
            cout << "\n";
            break;
        }
        cout << u << " ";
    }

    cout << "Ranges can be non-numeric, as long as the type is incrementable and equality comparable.\n";
    print_range(range('a', 'd'));

    cout << "Ranges can be non-contiguous.\n";
    print_range(range(20u, 29u).step(2u));

    cout << "… and we can even step backwards.\n";
    for (auto i : range(100).step(-3)) {
        if (i < 90) {
            cout << "\n";
            break;
        }
        cout << i << " ";
    }
    cout << "\n";

    cout << "Container indices are a special case of ranges.\n";
    std::vector<int> x{1, 2, 3};
    print_range(indices(x));

    print_range(indices({"foo", "bar"}));

    cout << "Strings are containers, too.\n";
    print_range(indices("foobar").step(2));
    cout << "\n";

    // TODO: Test cases; do something smarter with them.
    print_range(range(6, 10));
    print_range(range(1, 8).step(2));
    print_range(range(8, 1).step(-2));
    print_range(range(8.0, 1.0).step(-2.0));
    cout << "\n";
}
