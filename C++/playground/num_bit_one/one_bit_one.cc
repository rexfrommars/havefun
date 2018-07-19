#include <iostream>

using namespace std;

template <uint64_t>
struct has_one_bit_one {
    constexpr static auto value = false;
};

#define _obo(i) \
template <> \
struct has_one_bit_one<((static_cast<uint64_t>(1))<<i)> { \
    constexpr static auto value = true; \
};
_obo(0);
_obo(1);
_obo(2);
_obo(3);
_obo(4);
_obo(5);
_obo(6);
_obo(7);
// ...
_obo(63);
#undef _obo

int main()
{
    cout << "one-bit-one!!" << endl;

    cout << std::boolalpha;
    cout << has_one_bit_one<0>::value << endl;
    cout << has_one_bit_one<1>::value << endl;
    cout << has_one_bit_one<2>::value << endl;

    return 0;
}

