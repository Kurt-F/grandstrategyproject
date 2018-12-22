#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "OpenCLContext.h"
#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

int* multiplyMatrices(int* matrx_a, int* matrix_b, int columns_a, int rows_a, int columns_b, int rows_b);
int*multiplyMatricesOpenCL(int* matrx_a, int* matrix_b, int columns_a, int rows_a, int columns_b, int rows_b);
void printMatrix(int *matrix, int columns, int rows, std::string file_name = "");

void CheckError(cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << error << std::endl;
		std::exit(1);
	}
}


std::string LoadKernel(const char* name)
{
	std::ifstream in(name);
	std::string result(
		(std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	return result;
}

cl_program CreateProgram(const std::string& source,
	cl_context context)
{
	size_t lengths[1] = { source.size() };
	const char* sources[1] = { source.data() };

	cl_int error = 0;
	cl_program program = clCreateProgramWithSource(context, 1, sources, lengths, &error);

	return program;
}


int main()
{
	int num_columns_a;
	int num_rows_a; 
	int num_columns_b; 
	int num_rows_b; 
	int* matrix_a; 
	int* matrix_b;
	int*matrix_output;
	int openCL_or_CPP;
	std::cout << "How many columns in the first matrix?\n";
	std::cin >> num_columns_a; 
	num_rows_b = num_columns_a; 
	std::cout << "Since there must be as many rows in the second matrix as there are columns in the first, there are " << num_rows_b << " rows in the second matrix\n";
	std::cout << "How many rows in the first matrix?\n";
	std::cin >> num_rows_a; 
	std::cout << "How many columns in the second matrix?\n";
	std::cin >> num_columns_b;
	int min = std::min(std::min(num_rows_a,num_columns_a), std::min(num_rows_b, num_columns_b));
	if (min <= 0)
	{
		std::cout << "Invalid input; all values must be above 0\n";
		return -1;
	}
	matrix_a = new int[num_rows_a * num_columns_a];
	for (int i = 0; i < num_rows_a; i++)
	{
		for (int j = 0; j < num_columns_a; j++)
		{
			matrix_a[(i * num_columns_a) + j] = i + j * i + j;
		//matrix_a[(i * num_columns_a) + j] = 1;
		}
	}
	matrix_b = new int[num_rows_b * num_columns_b];
	for (int i = 0; i < num_rows_b; i++)
	{
		for (int j = 0; j < num_columns_b; j++)
		{
			matrix_b[(i * num_columns_b) + j] = j * 3 + 1 + i;
			//matrix_b[(i * num_columns_a) + j] = 1;
		}
	}
	std::cout << "Do you want to multiply these matrices using OpenCl or regular C++?(0 or 1)\n";
	std::cin >> openCL_or_CPP;
	printMatrix(matrix_a, num_columns_a, num_rows_a);
	printMatrix(matrix_b, num_columns_b, num_rows_b);
	if (openCL_or_CPP == 0)
	{
		matrix_output = multiplyMatricesOpenCL(matrix_a, matrix_b, num_columns_a, num_rows_a, num_columns_b, num_rows_b);
		printMatrix(matrix_output, num_columns_b, num_rows_a, "OPENCL.txt");
	}

	else
	{
    matrix_output = multiplyMatrices(matrix_a, matrix_b, num_columns_a, num_rows_a, num_columns_b, num_rows_b);
	printMatrix(matrix_output, num_columns_b, num_rows_a, "NOTOPENCL.txt");
	}
	return 0; 
}


int*multiplyMatricesOpenCL(int* matrix_a, int* matrix_b, int columns_a, int rows_a, int columns_b, int rows_b)
{
	size_t global_work_size[3];
	global_work_size[0] = rows_a * columns_b;
	global_work_size[1] = 0;
	global_work_size[2] = 0;
	int *matrix_out = new int[rows_a * columns_b];
	OpenCLContext context = OpenCLContext();
	cl_int error = 0;
	cl_program program = CreateProgram(LoadKernel("multiply.cl"), context.GetClContext());
	int b = clBuildProgram(program, context.getDeviceIdCount(), context.getDeviceIds().data(), nullptr, nullptr, nullptr);
	cl_kernel kernel = clCreateKernel(program, "MULT", &error);
	cl_mem buf_matrix_a = clCreateBuffer(context.GetClContext(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * columns_a * rows_a, matrix_a, &error);
	cl_mem buf_matrix_b = clCreateBuffer(context.GetClContext(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * columns_b * rows_b, matrix_b, &error);
	cl_mem out_buffer = clCreateBuffer(context.GetClContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(int) * rows_a * columns_b, matrix_out, &error);
	const int ROWS_INPUT = rows_a;
	const int COLUMNS_INPUT = columns_b;
	CheckError(clSetKernelArg(kernel, 0, sizeof(cl_mem), &buf_matrix_a));
	CheckError(clSetKernelArg(kernel, 1, sizeof(cl_mem), &buf_matrix_b));
	CheckError(clSetKernelArg(kernel, 2, sizeof(cl_mem), &out_buffer));
	CheckError(clSetKernelArg(kernel, 3, sizeof(int), &columns_a));
	CheckError(clSetKernelArg(kernel, 4, sizeof(int), &rows_a));
	CheckError(clSetKernelArg(kernel, 5, sizeof(int), &columns_b));
	cl_command_queue queue = clCreateCommandQueue(context.GetClContext(), context.getDeviceIds().data()[0], 0, &error);
	int a = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, global_work_size, nullptr, 0, nullptr, nullptr);
	int c = clEnqueueReadBuffer(queue, out_buffer, true, 0, global_work_size[0] * sizeof(int), matrix_out, 0, nullptr, nullptr);
	return matrix_out;
}

int* multiplyMatrices(int* matrix_a, int* matrix_b, int columns_a,int rows_a, int columns_b, int rows_b)
{
	int* matrix_output;
	int columns_output, rows_output;
	int temp;
	rows_output = rows_a;
	columns_output = columns_b;
	matrix_output = new int[rows_output * columns_output];
	for (int i = 0; i < rows_output; i++)
	{
		for (int j = 0; j < columns_output; j++)
		{
			temp = 0;
			for (int k = 0; k < columns_a; k++)
			{
				int matrix_a_result = matrix_a[(columns_a * i) + k];
				int matrix_b_result =  matrix_b[(k * columns_b) + j];
				temp += matrix_a_result * matrix_b_result;
			}
			matrix_output[(i * columns_output) + j] = temp;
		}
	}
	return matrix_output;
}

void printMatrix(int *matrix, int columns, int rows, std::string file_name)
{
	if (file_name.size() != 0)
	{
		std::ofstream myfile; 
		myfile.open(file_name);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				myfile << matrix[(i * columns) + j] << " ";
			}
			myfile << "\n";
		}
		myfile.close();
	}
	if (columns > 10 || rows > 10)
	{
		return;
	}
	std::cout << "Printing a matrix\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << matrix[(i * columns) + j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Done printing a matrix\n";
}