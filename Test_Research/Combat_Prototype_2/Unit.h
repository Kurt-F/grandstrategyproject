#ifndef UNIT
#define UNIT
#define EQ_RIFLE 0;
#define EQ_BODY_ARMOR 1;
#define EQ_BULLETS 2;

class Unit
{
private:
	int num_attr;
	float* attributes;

public:
	Unit(float* a, int s);
	~Unit();
	float* GetAttributes();
	void SetAttributes(float *a);
	int GetSize();
};
#endif
