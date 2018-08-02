#include "lib.hh"

#include <stdexcept>

namespace
{
	void _weird()
	{
		throw std::logic_error("_werid");
	}

	struct A
	{
		int16_t i16;
		int32_t i32;
	};

	struct B
	{
		int16_t i16;
		int32_t i32;

		B() = default;

		~B()
		{
			_weird();
		}
	};

	[[maybe_unused]] A _a;
}

Weird::~Weird()
{
	_weird();
}


int lib_open()
{
	return 0;
}

int lib_close()
{
	return 0;
}

int lib_weird()
{
	_weird();
	return 0;
}

int lib_func()
{
	[[maybe_unused]]
	A a;

	[[maybe_unused]]
	B b;

	return 0;
}
