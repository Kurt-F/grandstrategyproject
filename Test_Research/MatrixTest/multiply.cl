__kernel void MULT(__global int* buf_matrix_a, __global int* buf_matrix_b, __global int* buf_matrix_c, int COLUMNSA,  int ROWSA, int COLUMNSB)
{
	const int id = get_global_id(0);
	int rows_b = COLUMNSA;
	buf_matrix_c[id] = 0;
	int row_from_a = id / COLUMNSB;
	int column_from_b = id % COLUMNSB;
	for (int i = 0; i < COLUMNSA; i++)
	{
		buf_matrix_c[id] += buf_matrix_a[row_from_a * COLUMNSA + i] * buf_matrix_b[i * COLUMNSB + column_from_b];
	}
}