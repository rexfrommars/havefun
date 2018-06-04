#ifndef _FLAG_STAFF_
#define _FLAG_STAFF_

#include <memory>

#include "epollee.h"

namespace flagstaff
{

class Epollee;
class Engine
{
public:
	Engine() = default;
	virtual ~Engine() = default;

	Engine(const Engine&) = delete;
	Engine& operator= (const Engine&) = delete;

	Engine(Engine&&) = delete;
	Engine& operator= (Engine&&) = delete;

	virtual int add_target(Epollee*) = 0;
	virtual int del_target(Epollee*) = 0;

	virtual int run() = 0;
	virtual int stop() = 0;
};

Engine* GetEngineInstance();

}

#endif // _FLAG_STAFF_
