#include <iostream>
#include <string>
#include <typeinfo>

#define _log_ std::cout << "\t" << __LINE__ << " - " << __PRETTY_FUNCTION__ << " [" << this << "]\n";

template<typename T>
inline void use(T const &) {}

struct A
{
public:
    A () : _v(0) {
        _log_
    }

    A (A const & a) : _v(0) { _log_ }
    A& operator= (A const &) { _log_; return *this; }

    A (A &&) : _v(0) { _log_ }
    A& operator= (A &&) { _log_; return *this; }

    A& inc() { ++_v; return *this; }
    int v() const { return _v; }

private:
    int _v;
};

struct B
{
public:
    B () : _v(0) { _log_ }

    B (B const &) : _v(0) { _log_ }
    B& operator= (B const &) { _log_; return *this; }

    B (B &&) : _v(0) { _log_ }
    B& operator= (B &&) { _log_; return *this; }

    B (B const &&) = delete;
    B& operator= (B const &&) = delete;

    B& inc() { ++_v; return *this; }
    int v() const { return _v; }

private:
    int _v;
};

template <typename T>
struct W
{
    using type = T;
    using ref = T&;

    type _x;

    W() { _log_ }
    W& operator=(const W&) = delete;

    ref access() { return _x; }
};

template<typename T> struct TypeName {};
#define TYPE_NAME(x) template<> struct TypeName<x> { constexpr static auto value = #x; };

TYPE_NAME(void);
TYPE_NAME(int);
TYPE_NAME(int &);
TYPE_NAME(int const &);
TYPE_NAME(int &&);
TYPE_NAME(int const &&);

TYPE_NAME(W<A>);
TYPE_NAME(A &);
TYPE_NAME(A &&);

TYPE_NAME(W<A const>);
TYPE_NAME(A const &);
TYPE_NAME(A const &&);

#define _(t) std::cout << TypeName<t>::value << std::endl;

int main()
{
    _(int);
    _(int &);
    _(const int&);
    _(int const &);
    _(int &&);
    _(const int &&);
    _(int const &&);
    // _(int &&&); // error: type name declared as a reference to a reference

    // ******************************** //
    std::cout << std::string().assign(32, '*')<< std::endl;

    auto wa = W<A>(); use(wa);
    wa.access().v();
    wa.access().inc().v();

    auto wca = W<A const>(); use(wca);
    wca.access().v();
    // wca.access().inc().v(); // compilation error

    _(decltype(wa));
    _(decltype(wa.access()));
    _(decltype(std::move(wa.access())));

    _(decltype(wca));
    _(decltype(wca.access()));
    _(decltype(std::move(wca.access())));


    auto yaa = A(std::move(wa.access()));   // will invoke the move constructor
    A(std::move(wca.access()));             // will invoke the copy constructor
    yaa = std::move(wa.access());           // will invoke the move assignment function
    yaa = std::move(wca.access());          // will invoke the copy assignment function

    // ******************************** //
    std::cout << std::string().assign(32, '*')<< std::endl;

    auto wb = W<B>(); use(wb);
    auto wcb = W<B const>(); use(wcb);

    auto yab = B(std::move(wb.access()));   // move constructor
    // B(std::move(wcb.access()));          // error // candidate has been explicitly deleted // clang-902; macOS
    yab = std::move(wb.access());           // move assignment
    // yab = std::move(wcb.access());       // error // candidate has been explicitly deleted // clang-902; macOS

    return 42;
}
