#ifndef _LIB_HH_
#define _LIB_HH_

#ifdef __cplusplus
extern "C" {
#endif

struct Weird
{
	Weird() = default;

	~Weird();
};

int lib_open();
int lib_close();

int lib_weird();
int lib_func();

#ifdef __cplusplus
}
#endif

#endif // _LIB_HH_
