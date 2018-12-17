__kernel void FIGHT(__global unsigned char* attk_hp, __global unsigned char* def_hp, __global unsigned char* attk_pow, __global unsigned char* def_pow)
{
	const int i = get_global_id(0);
	if (attk_pow[i] > 0 && def_pow[i] > 0)
	{
		if (def_hp[i] < attk_pow[i])
		{
			def_hp[i] = 0;
		}
		else
		{
			def_hp[i] = def_hp[i] - attk_pow[i];
		}

	}
}

__kernel void DEFEND(__global unsigned char* attk_hp, __global unsigned char* def_hp, __global unsigned char* attk_pow, __global unsigned char* def_pow)
{
	const int i = get_global_id(0);
	if (attk_pow[i] > 0 && def_pow[i] > 0)
	{
		if (attk_hp[i] < def_pow[i])
		{
			attk_hp[i] = 0;
		}
		else
		{
			attk_hp[i] = attk_hp[i] - def_pow[i];
		}

	}
}

