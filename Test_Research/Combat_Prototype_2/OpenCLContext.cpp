#include "OpenClContext.h"
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

	std::string OpenCLContext::GetPlatformName(cl_platform_id id)
	{
		size_t size = 0;
		clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, nullptr, &size);
		std::string result;
		result.resize(size);
		clGetPlatformInfo(id, CL_PLATFORM_NAME, size,
			const_cast<char*> (result.data()), nullptr);
		return result;
	}
	 cl_context OpenCLContext::CreateCLContext() {
		cl_uint platformIdCount = 0;
		// Get platform information
		clGetPlatformIDs(0, nullptr, &platformIdCount);

		if (platformIdCount == 0) {
			std::cerr << "No OpenCL platform found" << std::endl;
			exit(1);
		}
		std::vector<cl_platform_id> platformIds(platformIdCount);
		clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);

		cl_uint deviceIdCount = 0;
		clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr,
			&deviceIdCount);

		if (deviceIdCount == 0) {
			std::cerr << "No OpenCL devices found" << std::endl;
			exit(1);
		}

		std::vector<cl_device_id> deviceIds(deviceIdCount);
		clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount,
			deviceIds.data(), nullptr);

		const cl_context_properties contextProperties[] =
		{
			CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties> (platformIds[0]),
			0, 0
		};

		cl_int error = CL_SUCCESS;
		cl_context context = clCreateContext(contextProperties, deviceIdCount,
			deviceIds.data(), nullptr, nullptr, &error);

		std::cout << "Context created" << std::endl;
		return context;
	}