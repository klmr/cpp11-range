#ifndef UTIL_LANG_RANGE_HPP
#define UTIL_LANG_RANGE_HPP

#include <iterator>

namespace util { namespace lang {

namespace detail {

template <typename T>
struct range_iter_base : std::iterator<std::input_iterator_tag, T> {
    range_iter_base(T current) : current(current) { }

    T operator *() const { return current; }

    T const* operator ->() const { return &current; }

    range_iter_base& operator ++() {
        ++current;
        return *this;
    }

    range_iter_base operator ++(int) {
        auto copy = *this;
        ++*this;
        return copy;
    }

    bool operator ==(range_iter_base const& other) const {
        return current == other.current;
    }

    bool operator !=(range_iter_base const& other) const {
        return not (*this == other);
    }

protected:
    T current;
};

} // namespace detail

template <typename T>
struct range_proxy {
    struct iter : detail::range_iter_base<T> {
        iter(T current) : detail::range_iter_base<T>(current) { }
    };

    struct step_range_proxy {
        struct iter : detail::range_iter_base<T> {
            iter(T current, T step)
                : detail::range_iter_base<T>(current), step(step) { }

            using detail::range_iter_base<T>::current;

            iter& operator ++() {
                current += step;
                return *this;
            }

            iter operator ++(int) {
                auto copy = *this;
                ++*this;
                return copy;
            }

            // Loses commutativity. Iterator-based ranges are simply broken. :-(
            bool operator ==(iter const& other) const {
                return step > 0 ? current >= other.current
                                : current < other.current;
            }

            bool operator !=(iter const& other) const {
                return not (*this == other);
            }

        private:
            T step;
        };

        step_range_proxy(T begin, T end, T step)
            : begin_(begin, step), end_(end, step) { }

        iter begin() const { return begin_; }

        iter end() const { return end_; }

    private:
        iter begin_;
        iter end_;
    };

    range_proxy(T begin, T end) : begin_(begin), end_(end) { }

    step_range_proxy step(T step) {
        return step_range_proxy(*begin_, *end_, step);
    }

    iter begin() const { return begin_; }

    iter end() const { return end_; }

private:
    iter begin_;
    iter end_;
};

template <typename T>
struct infinite_range_proxy {
    struct iter : detail::range_iter_base<T> {
        iter(T current = T()) : detail::range_iter_base<T>(current) { }

        bool operator ==(iter const&) const { return false; }

        bool operator !=(iter const&) const { return true; }
    };

    struct step_range_proxy {
        struct iter : detail::range_iter_base<T> {
            iter(T current = T(), T step = T())
                : detail::range_iter_base<T>(current), step(step) { }

            using detail::range_iter_base<T>::current;

            iter& operator ++() {
                current += step;
                return *this;
            }

            iter operator ++(int) {
                auto copy = *this;
                ++*this;
                return copy;
            }

            bool operator ==(iter const&) const { return false; }

            bool operator !=(iter const&) const { return true; }

        private:
            T step;
        };

        step_range_proxy(T begin, T step) : begin_(begin, step) { }

        iter begin() const { return begin_; }

        iter end() const { return  iter(); }

    private:
        iter begin_;
    };

    infinite_range_proxy(T begin) : begin_(begin) { }

    step_range_proxy step(T step) {
        return step_range_proxy(*begin_, step);
    }

    iter begin() const { return begin_; }

    iter end() const { return iter(); }

private:
    iter begin_;
};

template <typename T>
range_proxy<T> range(T begin, T end) {
    return range_proxy<T>(begin, end);
}

template <typename T>
infinite_range_proxy<T> range(T begin) {
    return infinite_range_proxy<T>(begin);
}

} } // namespace util::lang

#endif // ndef UTIL_LANG_RANGE_HPP
