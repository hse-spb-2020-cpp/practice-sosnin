#include <iostream>
#include <stdexcept>
#include <utility>

namespace hse::cpp {

template <typename T, typename Alloc = std::allocator<T>>
class vector {
    T *data = nullptr;
    size_t cp = 0;
    size_t sz = 0;

public:
    static T *Allocate(size_t n) {
        return static_cast<T *>(Alloc().allocate(n));
    }

    static void Deallocate(T *buf, size_t n) {
        Alloc().deallocate(buf, n);
    }

    static void Construct(void *buf) {
        new (buf) T();
    }

    static void Construct(void *buf, const T &elem) {
        new (buf) T(elem);
    }

    static void Destroy(T *buf) {
        buf->~T();
    }

public:
    explicit vector(size_t n) {
        size_t i = 0;
        try {
            data = Allocate(n);
            for (; i != n; ++i) {
                Construct(data + i);
            }
            sz = cp = n;
        } catch (...) {
            for (size_t j = 0; j != i; ++j) {
                Destroy(data + j);
            }
            Deallocate(data, n);
            throw;
        }
    }

    vector(const vector &other) {
        size_t i = 0;
        try {
            data = Allocate(other.sz);
            for (; i != other.sz; ++i) {
                Construct(data + i, other[i]);
            }
            sz = cp = other.sz;
        } catch (...) {
            for (size_t j = 0; j != i; ++j) {
                Destroy(data + j);
            }
            Deallocate(data, other.sz);
            throw;
        }
    }

    ~vector() noexcept {
        for (size_t i = 0; i != sz; ++i) {
            Destroy(data + i);
        }
        Deallocate(data, cp);
    }

    // Будьте осторожны с оператором копирующего присваивания.
    // В нём можно добиться строгой гарантии исключений, но какой ценой? В этом
    // задании мы готовы заплатить, в отличие от стандартной библиотеки.
    void resize(size_t n) {
        if (n <= sz) {
            for (size_t i = n; i != sz; ++i) {
                Destroy(data + i);
            }
            sz = n;
        } else if (n <= cp) {
            try {
                for (size_t i = sz; i != n; ++i) {
                    Construct(data + i);
                }
                sz = n;
            } catch (...) {
                for (size_t i = sz; i != n; ++i) {
                    Destroy(data + i);
                }
                throw;
            }
        } else {  // n > cp
            T *buf = Allocate(n);
            size_t i = 0;
            try {
                for (; i != n; ++i) {
                    Construct(buf + i, data[i]);
                }
            } catch (...) {
                for (size_t j = 0; j != i; ++j) {
                    Destroy(buf + j);
                }
                throw;
            }
            std::swap(data, buf);
            Deallocate(buf, sz);
            sz = cp = n;
        }
    }

    T &operator[](std::size_t index) &noexcept {
        return data[index];
    }

    const T &operator[](std::size_t index) const &noexcept {
        return data[index];
    }
};

struct Counted {
    inline static size_t constructed = 0;
    inline static size_t destroyed = 0;

    Counted() {
        if (constructed > 8)
            throw std::runtime_error("Too many default constructed objects");

        ++constructed;
    }

    Counted(const Counted &) {
        // if (constructed > 4)
        //     throw std::runtime_error("Too many copy constructed objects");

        ++constructed;
    }

    ~Counted() {
        ++destroyed;
    }
};

}  // namespace hse::cpp
int main() {
    using namespace hse::cpp;

    try {
        vector<Counted> v1(2);
        v1.resize(10);
        v1.resize(3);

        // Копирующе присваивание
        // vector<Counted> v1(2);
        // vector<Counted> v2(10);
        // v1 = v2;  // Здесь произойдет изменение v1 в случае успеха
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Unhandled exception" << std::endl;
    }

    std::cout << "Constructed: " << Counted::constructed << std::endl;
    std::cout << "Destroyed: " << Counted::destroyed << std::endl;
}
