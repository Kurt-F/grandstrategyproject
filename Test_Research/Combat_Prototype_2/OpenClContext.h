#ifndef  Context
# define Context


#include <list>
#include "Army.h"
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
	std::string GetPlatformName(cl_platform_id id);
public:
	static cl_context CreateCLContext();
};
#endif // ! OpenCLContext