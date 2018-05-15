#include <iostream>
#include <string>

using namespace std;

struct Object
{
    const string _name;
    int _i;

    Object(const string& name, int i) : _name(name), _i(i) {
        cout << __LINE__ << "\t ordinary constructor: " << _name << " " << _i << endl;
    }

    ~Object() {
        // cout << "destructor: \t" << _a << " | " << _b << endl;
    }

    Object(const Object& obj) : _name(obj._name + "-copy"), _i(obj._i) {
        cout << __LINE__ << "\t copy constructor: \t" << _name << " " << _i << endl;
    }

    Object& operator= (const Object& obj) {
        cout << __LINE__ << "\t copy assignment: \t" << _name << " <= " << obj._name << endl;
        this->_i = obj._i;
        return *this;
    }

#if __cplusplus >= 201103L
    Object(Object&& obj) : _name(obj._name + "-move"), _i(obj._i) {
        cout << __LINE__ << "\t move constructor \t" << _name << " " << _i << endl;
        obj._i = 0;
    }

    Object& operator=(Object&& obj) {
        cout << __LINE__ << "\t move assignment: \t" << _name << " <= " << obj._name <<  endl;
        if (this != &obj) {
            this->_i = obj._i;
            obj._i = 0;
        }
        return *this;
    }
#endif
};

Object m0() {
    return Object("M0", 10);
}

Object& m1() {
    static Object object("M1", 11);
    return object;
}


#if __cplusplus >= 201103L
Object&& m2() {
    static Object object("M2", 12);
    return std::move(object);
}
#else
Object m2() {
    return Object("M2", 12);
}
#endif

static void func(const Object& object) {
    cout << __LINE__ << "\t func" << endl;
}

static void func(Object& object) {
    cout << __LINE__ << "\t func" << endl;
}

#if __cplusplus >= 201103L
static void func(Object&& object) {
    cout << __LINE__ << "\t func" << endl;
}
static void func(const Object&& object) {
    cout << __LINE__ << "\t func" << endl;
}
#endif

int main()
{
    cout << "__cplusplus: " << __cplusplus << endl;

    {
        Object x("x", 3);
        Object y(x);
        Object z = y;
        z = x;
    }

    cout << string().assign(20, '*') << endl;
    {
        Object x("X", 4);
        Object y(x);

        Object z(Object("_", 5));      // this line actually calls ONLY the ordinary constructor

        Object u(std::move(x));     // Though std::move is introduced in C++11, this line could be compiled by
                                    // Apple LLVM version 9.1.0 (clang-902.0.39.1) with -std=c++09 on MacOS.

        Object v = std::move(y);

        u = std::move(z);
    }

    cout << string().assign(30, '=') << endl;
    {
        Object a0(m0());
        Object a1(m1());
        Object a2(m2());
        Object a3(m2());
    }

    cout << string().assign(30, 'X') << endl;
    {
        Object object("Object", __LINE__);
        func(object);
        func(const_cast<Object const &>(object));
        func(Object("Object", __LINE__));

#if __cplusplus >= 201103L
        void (*func_weird)(const Object&&) = func;
        func_weird(Object("Object", __LINE__));
#endif
    }

    return 0;
}

/*
# https://docs.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp

# What is the significance of "const rvalue"?

# http://yacoder.guru/blog/2015/03/14/cpp-curiosities-std-move-that-doesnt-move/
# http://yacoder.guru/blog/2015/05/06/cpp-curiosities-one-does-not-simply-move-a-const-object/
*/
