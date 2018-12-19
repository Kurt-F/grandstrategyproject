#define EQ_RIFLE 0;
#define EQ_BODY_ARMOR 1;
#define EQ_BULLETS 2;


class Unit {
private:
	int num_attr;
	float* attributes;
public:
	Unit(float* a, int s) {
		this->attributes = a;
		this->num_attr = s;
	}
	~Unit() {
		delete(attributes);
	}
	float* GetAttributes() {
		return attributes;
	}
	void SetAttributes(float* a) {
		this->attributes = a;
	}
};