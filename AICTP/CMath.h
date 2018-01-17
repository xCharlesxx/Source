#pragma once
#include "CoreMinimal.h"

//inline void Copy(FVector* dest, const FVector* a) {
//	dest[0] = a->X;
//	dest[1] = a->Y;
//	dest[2] = a->Z;
//};
inline float Dist(const FVector* v1, const FVector* v2) {
	const float dx = v2->X - v1->X;
	const float dy = v2->Y - v1->Y;
	const float dz = v2->Z - v1->Z;
	return sqrtf(dx*dx + dy * dy + dz * dz);
};
inline unsigned int NextPow2(unsigned int v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
inline void Add(FVector* dest, const FVector* v1, const FVector* v2)
{
	dest->X = v1->X + v2->X;
	dest->Y = v1->Y + v2->Y;
	dest->Z = v1->Z + v2->Z;
}

/// Performs a vector subtraction. (@p v1 - @p v2)
///  @param[out]	dest	The result vector. [(x, y, z)]
///  @param[in]		v1		The base vector. [(x, y, z)]
///  @param[in]		v2		The vector to subtract from @p v1. [(x, y, z)]
inline void Sub(FVector* dest, const FVector* v1, const FVector* v2)
{
	dest->X = v1->X - v2->X;
	dest->Y = v1->Y - v2->Y;
	dest->Z = v1->Z - v2->Z;
}