#include <iostream>

#include <atomic>
#include <exception>
#include <utility>
#include <sstream>

class ExceptionBase : public std::exception
{
public:
	using id_t = int;

	ExceptionBase() : std::exception(), _id(++_id_gen)
	{}

	id_t id() const { return _id; }

	virtual const char* what() const noexcept override { return "ExceptionBase"; }

private:
	static std::atomic<id_t> _id_gen;
	const id_t _id;
};

template <typename E>
class ExceptionWrapper : public ExceptionBase
{
public:
	using InnerE = E;

	template <typename... Args>
	ExceptionWrapper(Args... args) : ExceptionBase(), _e(std::forward<Args>(args)...)
	{}

	operator InnerE () { return _e; }

public:
	InnerE _e;
};

std::atomic<ExceptionBase::id_t> ExceptionBase::_id_gen {};

template <typename E>
class ExceptionDiamond : public ExceptionBase, public E
{
public:
	template <typename... Args>
	ExceptionDiamond(Args... args) : ExceptionBase(), E(std::forward<Args>(args)...)
	{}

	virtual const char* what() const noexcept override {
		std::ostringstream oss;
		oss << "ExceptionDiamond | " << E::what();
		_what = oss.str();
		return _what.c_str();
	}

private:
	mutable std::string _what;
};

void run(void (*func)())
{
	try {
		func();
	}
	catch (std::invalid_argument& ia) {
		std::cout<< ia.what() << std::endl;
	}
	catch (ExceptionBase& e) {
		std::cout << e.what() << "(" << e.id() << ")" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int run()
{
	run([]() -> void { throw ExceptionBase(); });
	
	run([](){ throw std::exception(); });
	run([](){ throw std::invalid_argument("ia"); });

	run([](){ throw ExceptionWrapper<std::invalid_argument>("w-ia"); });
	run([](){ throw ExceptionDiamond<std::invalid_argument>("d-ia"); });

	run([](){ throw ExceptionWrapper<bool>(false); });
	// run([](){ throw ExceptionDiamond<bool>(false); });

	return 0;
}

int main()
{
	return run();
}
