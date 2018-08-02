#include <iostream>

using namespace std;

class A
{
public:
	virtual ~A() = default;

	virtual void fa()
	{
		cout << "A::fa()" << endl;
	}
};

class B
{
public:
	virtual ~B() = default;

	virtual void fb()
	{
		cout << "B::fb()" << endl;
	}
};

class C : public A, public B
{
public:
	void funcx() {}
};


int run()
{
	auto p = new C;

	p->fa();
	p->fb();

	((A*)p)->fa();
	((B*)p)->fb();

	((A*)(void*)p)->fa();
	((B*)(void*)p)->fb(); // "fa" not "fb"

	(dynamic_cast<A*>(p))->fa();
	(dynamic_cast<B*>(p))->fb();

	// (dynamic_cast<A*>((void*)p))->fa(); // void is not a class
	// (dynamic_cast<B*>((void*)p))->fb(); // void is not a class

	return 0;
}


int main()
{
	run();
	return 0;
}
