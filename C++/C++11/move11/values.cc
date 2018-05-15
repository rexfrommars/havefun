#include <iostream>
#include <string>

#define _log_ std::cout << "\t" << __LINE__ << " - " << __func__ << std::endl;

struct Object {};

void f(Object &) { _log_ }
void f(Object const &) { _log_ }

void g(Object &) { _log_ }
void g(Object const &) { _log_ }
void g(Object &&) { _log_ }

void h(Object&) { _log_ }
void h(Object const &) { _log_ }
void h(Object &&) { _log_ }
void h(Object const &&) { _log_ }

void w(Object) { _log_ }    // 0th
void w(Object &) { _log_ }
void w(Object const &) { _log_ }
void w(Object &&) { _log_ }
void w(Object const &&) { _log_ }

int main()
{
    _log_

    std::cout << std::string().assign(30, '-') << std::endl;
    {
        Object a;
        Object const b;

        f(Object());        // 2nd (T&&) -> (T const &)
        f(a);               // 1st (T&)
        f(b);               // 2nd (T const &)
        f(std::move(a));    // 2nd (T&&) -> (T const &)
        f(std::move(b));    // 2nd (T const &&) -> (T const &)
    }

    std::cout << std::string().assign(30, '=') << std::endl;
    {
        Object a;
        Object const b;

        g(Object());        // 3rd  (T&&)
        g(a);               // 1st  (T&)
        g(b);               // 2nd  (T const &)
        g(std::move(a));    // 3rd  (T&&)
        g(std::move(b));    // 2nd  (T const &&) -> (T const &)
    }

    std::cout << std::string().assign(30, '*') << std::endl;
    {
        Object a;
        Object const b;

        h(Object());        // 3rd  (T&&)
        h(a);               // 1st  (T&)
        h(b);               // 2nd  (T const &)
        h(std::move(a));    // 3rd  (T&&)
        h(std::move(b));    // 4th  (T const &&)
    }

    std::cout << std::string().assign(30, 'x') << std::endl;
    {
        Object a; (void)a;
        Object const b;

        w(Object());
    }

    return 0;
}

/*
 * TODO
 * https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
 * https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/reference_collapsing.htm
 */