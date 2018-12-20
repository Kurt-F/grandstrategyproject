// Inits the army
__kernel void INIT(__global float *army, int unit_size)
{
	const int i = get_global_id(0);
	int norm_i = i * unit_size;
	for (int j = 0; j < unit_size; j++)
	{
		army[norm_i + j] = j;
	}
}