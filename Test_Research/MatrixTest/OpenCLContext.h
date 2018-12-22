#ifndef  Context
# define Context


#include <list>
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
	cl_uint deviceIdCount;
	std::vector<cl_device_id> deviceIds;
	cl_context context;
public:
	OpenCLContext();
	cl_context GetClContext();
	cl_uint getDeviceIdCount();
	std::vector<cl_device_id> getDeviceIds();
};
#endif // ! OpenCLContext