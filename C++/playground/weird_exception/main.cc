#include <iostream>
#include <exception>

#include "lib.hh"

using namespace std;

int run()
{
	try {
		//lib_weird();
		lib_func();
		return 0;
	}
	catch (std::exception &e)
	{

		cout << __LINE__ << " got " << e.what() << endl;
		return -1;
	}
}

void terminate_handle()
{
	{
		Weird w;
		(void)w;
	}

	lib_weird();
	cout << __func__ << " | " << __LINE__ << endl;
}

int main()
{
	set_terminate(terminate_handle);

	int rc{};

	lib_open();

	rc = run();

	lib_close();

	return rc;
}
