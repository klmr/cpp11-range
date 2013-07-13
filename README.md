## Re-imagining the `for` loop

C++11 now knows two distinct types of `for` loops: the classic loop over an “index” and the range-based `for` loop which vastly simplifies the iteration over a range specified by a pair of iterators.

By contrast, Python knows only one loop type – roughly equivalent to the range-based for loop. In fact, loops over indices are exceedingly rare, but made possible by the use of the `range` method:

```python
for i in range(10):
    print i
```

Which does what it promises – although Python version < 3.0 does the “wrong” thing and actually instantiates the whole collection in memory at once; a remedy is `xrange` which yields values lazily as they are consumed by the loop.

C++11 effortlessly allows the same but there is no standard library function to provide this. [Boost.Range][] provides *part* of the functionality via `irange` which only works on integers, and not for unlimited ranges (this will make sense in a second).

The header `range.hpp` provides a very basic implementation for this. It allows running the following code:

```c++
for (auto i : range(1, 5))
    cout << i << "\n";

for (auto u : range(0u))
    if (u == 3u) break;
    else         cout << u << "\n";

for (auto c : range('a', 'd'))
    cout << c << "\n";

for (auto i : range(100).step(-3))
    if (i < 90) break;
    else        cout << i << "\n";
```

`range` with a single argument deviates from the Python semantic and creates an endless loop, unless it’s interrupted manually. This is an interesting use-case that cannot be modelled in Python using `range`.

## Iterating over container indices

In Python, the one-argument version of `range` is often used to iterate over the indices of a container via `range(len(container))`. Because that overload creates an infinite range in our C++ library, we cannot use this idiom.

But we can do better anyway. For those few cases where we actually want to iterate over a container’s indices, we just use the `indices` function:

```c++
std::vector<int> x{1, 2, 3};
for (auto i : indices(x))
    cout << i << '\n';
```

This works as expected for *any* type which has a member function `size() const` that returns some integral type. It also works with `initializer_list`s and C-style fixed-size arrays.

Adding `.step(…)` to the end of either `range` or `indices` specifies a step size instead of the default, 1.

The construct works for arbitrary types which fulfil the interface requirements (incrementing, copying, equality comparison, default construction in the case of infinite ranges).

## Performance (the cost of beauty)

When compiling with optimisations enabled (and why wouldn’t you?), using the `range` function yield very similar output compared with a manual `for` loop. In fact, on g++ 4.8 with `-O2` or higher, *the following two loops yield identical assembly*.

```c++
for (int i = 0; i < n; ++i)
    cout << i;

for (int i : range(0, n))
    cout << i;
```

Even though the `range` function creates a proxy container and an iterator wrapper, those are completely elided from the resulting code.

**☞ Beauty is free.**

[Boost.Range]: http://www.boost.org/doc/libs/1_54_0/libs/range/doc/html/index.html
