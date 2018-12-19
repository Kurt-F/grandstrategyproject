#include <list>
#include "Army.cpp"
#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#include <iostream>
#include <vector>
#include <stdio.h>

class OpenCLContext {
private:
	std::string GetPlatformName(cl_platform_id id)
	{
		size_t size = 0;
		clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, nullptr, &size);

		std::string result;
		result.resize(size);
		clGetPlatformInfo(id, CL_PLATFORM_NAME, size,
			const_cast<char*> (result.data()), nullptr);

		return result;
	}
public:
	cl_context CreateCLContext() {
		cl_uint platformIdCount = 0;
		clGetPlatformIDs(0, nullptr, &platformIdCount);

		if (platformIdCount == 0) {
			std::cerr << "No OpenCL platform found" << std::endl;
			exit(1);
		}
		std::vector<cl_platform_id> platformIds(platformIdCount);
		clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);


	}
};