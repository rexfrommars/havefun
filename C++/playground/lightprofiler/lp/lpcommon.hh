#ifndef _LP_COMMON_
#define _LP_COMMON_

#include <cstdint>

namespace light_profiler
{

constexpr auto LP_SOCK_PREFIX = "/tmp/lightprofiler.";

struct ProfSample
{
	uint32_t _magic;

	uint32_t thread_id;
	uint32_t sample_id;

	uint32_t list_size;

	uintptr_t addr_list[32];
};

} // namespace light_profiler

#endif // _LP_COMMON_
