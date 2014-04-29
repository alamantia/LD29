#pragma once
class AVector
{
public:
	float x;
	float y;
	AVector(void);
	~AVector(void);
    
	float add(AVector *b);
	float sub(AVector *b);
	float mul(AVector *b);
	float dot(AVector *b);
	float cross(AVector *b);

};

