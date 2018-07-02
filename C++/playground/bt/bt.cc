
#define UNW_LOCAL_ONLY

#include <libunwind.h>

#include <iostream>
#include <stdio.h>

using namespace std;

auto& _i = cout;
auto& _x = cerr;

void bt()
{
 	unw_cursor_t cursor;
 	unw_context_t context;

	// Initialize cursor to current frame for local unwinding.
	unw_getcontext(&context);
	unw_init_local(&cursor, &context);

	// Unwind frames one by one, going up the frame stack.
	while (unw_step(&cursor) > 0) {
		unw_word_t offset, pc;
		unw_get_reg(&cursor, UNW_REG_IP, &pc);
		if (pc == 0) {
			break;
		}
		printf("0x%lx:", pc);

		char sym[256];
		if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
			printf(" (%s+0x%lx)\n", sym, offset);
		} else {
			printf(" -- error: unable to obtain symbol name for this frame\n");
		}
	}
}

void func_a()
{
	int a = __LINE__;
	bt();
	_x << a << endl;
}

void func_b()
{
	int b = __LINE__;
	func_a();
	_x << b << endl;
}

void func_c()
{
	int c = __LINE__;
	func_b();
	_x << c << endl;
}

void func_d()
{
	int d = __LINE__;
	func_c();
	_x << d << endl;
}

void func_z()
{
	int z = __LINE__;
	func_d();
	_x << z << endl;
}

int run()
{
	// TODO

	func_z();

	return 0;
}

int main()
{
	int rc = run();
	return rc;
}

