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
#include <iostream>
#include <string>


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

	std::string GetDeviceName(cl_device_id id)
	{
		size_t size = 0;
		clGetDeviceInfo(id, CL_DEVICE_NAME, 0, nullptr, &size);

		std::string result;
		result.resize(size);
		clGetDeviceInfo(id, CL_DEVICE_NAME, size,
			const_cast<char*> (result.data()), nullptr);

		return result;
	}


	 OpenCLContext::OpenCLContext() {
		cl_uint platformIdCount = 0;
		// Get platform information
		clGetPlatformIDs(0, nullptr, &platformIdCount);

		if (platformIdCount == 0) {
			std::cerr << "No OpenCL platform found" << std::endl;
			exit(1);
		}

		else {
			std::cout << "Found " << platformIdCount << " platform(s)" << std::endl;
		}

		std::vector<cl_platform_id> platformIds(platformIdCount);
		clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);

		OpenCLContext::deviceIdCount = 0;
		clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr,
			&deviceIdCount);

		if (deviceIdCount == 0) {
			std::cerr << "No OpenCL devices found" << std::endl;
			exit(1);
		}
		else {
			std::cout << "Found " << deviceIdCount << " device(s)" << std::endl;
		}

		std::vector<cl_device_id> deviceIds(deviceIdCount);
		clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount,
			deviceIds.data(), nullptr);
		OpenCLContext::deviceIds = deviceIds;
		const cl_context_properties contextProperties[] =
		{
			CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties> (platformIds[0]),
			0, 0
		};

		cl_int error = CL_SUCCESS;
		OpenCLContext::context = clCreateContext(contextProperties, deviceIdCount,
			deviceIds.data(), nullptr, nullptr, &error);
		for (cl_uint i = 0; i < deviceIdCount; ++i) {
			std::cout << GetDeviceName(deviceIds[i]) << std::endl;
		}
	}

	 cl_uint OpenCLContext::getDeviceIdCount()
	 {
		 return deviceIdCount;
	 }
	
	 std::vector<cl_device_id> OpenCLContext::getDeviceIds()
	 {
		 return deviceIds;
	 }

	 cl_context OpenCLContext::GetClContext()
	 {
		 return context;
	 }