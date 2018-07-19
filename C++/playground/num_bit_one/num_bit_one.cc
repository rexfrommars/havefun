#include <iostream>

using namespace std;

template <auto> struct _n1e {};
#define _N1E(i,n) template<> \
	struct _n1e<i> { constexpr static auto value = n; }
_N1E(0x00, 0);
_N1E(0x01, 1);
_N1E(0x02, 1);
_N1E(0x04, 1);
_N1E(0x08, 1);
_N1E(0x10, 1);
_N1E(0x20, 1);
_N1E(0x40, 1);
_N1E(0x80, 1);
#undef _N1E

template <uint8_t u8>
struct _n1u8
{
    constexpr static auto value =
	    _n1e<(u8 & 0x01)>::value +
	    _n1e<(u8 & 0x02)>::value +
	    _n1e<(u8 & 0x04)>::value +
	    _n1e<(u8 & 0x08)>::value +
	    _n1e<(u8 & 0x10)>::value +
	    _n1e<(u8 & 0x20)>::value +
	    _n1e<(u8 & 0x40)>::value +
	    _n1e<(u8 & 0x80)>::value;
};

template <uint16_t u16>
struct _n1u16
{
    constexpr static auto value =
	    _n1u8<((u16 & 0x00FF) >> 0)>::value +
	    _n1u8<((u16 & 0xFF00) >> 8)>::value;
};

template <uint32_t u32>
struct _n1u32
{
    constexpr static auto value =
	    _n1u16<((u32 & 0x0000FFFF) >>  0)>::value +
	    _n1u16<((u32 & 0xFFFF0000) >> 16)>::value;
};

template <uint64_t u64>
struct _n1u64
{
    constexpr static auto value =
	    _n1u32<((u64 & 0x00000000FFFFFFFF) >>  0)>::value +
	    _n1u32<((u64 & 0xFFFFFFFF00000000) >> 32)>::value;
};

template <uint64_t u64>
using _n1 = _n1u64<u64>;

int main()
{
    cout << "!!num-bit-one!!" << endl;

    cout << _n1e<0>::value << endl;
    cout << _n1e<1>::value << endl;
    cout << _n1e<2>::value << endl;

#define _x8(i) \
    cout << "_n1u8<" #i ">::value is " << _n1u8<i>::value << endl;

    _x8(0);
    _x8(1);
    _x8(2);
    _x8(3);
    _x8(4);
    _x8(5);
    _x8(6);
    _x8(7);
    _x8(8);
    _x8(0x0f);
    _x8(0xff);
    //_x8(0x100);
#undef _x8

#define _x16(i) \
    cout << "_n1u16<" #i ">::value is " << _n1u16<i>::value << endl;
    _x16(0);
    _x16(0xff);
    _x16(0x100);
    _x16(0xffff);
    //_x16(0x10000);
#undef _x16

    cout << "_n1u32<0x10000>::value is " << _n1u32<0x10000>::value << endl;

    return 0;
}

