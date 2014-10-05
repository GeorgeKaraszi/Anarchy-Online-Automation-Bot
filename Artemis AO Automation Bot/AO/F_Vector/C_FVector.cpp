#include "C_FVector.h"

C_FVector::C_FVector()
{}

FLOAT C_FVector::VectorDotProduct(FVector* pV1, FVector* pV2)
{
	return ((pV1->X * pV2->X) + (pV1->Y * pV2->Y) + (pV1->Z * pV2->Z));
}

FLOAT C_FVector::VectorLength(FVector* pV)
{
	return pV->Length();
}

FVector* C_FVector::VectorNormalize(FVector* pOut, FVector* pV)
{
	FLOAT Len = pV->Length();

	*pOut /= Len;

	return pOut;
}

FVector* C_FVector::VectorScale(FVector* pOut, FVector* pV, FLOAT Scale)
{
	pOut->X = pV->X * Scale;
	pOut->Y = pV->Y * Scale;
	pOut->Z = pV->Z * Scale;

	return pOut;
}

FVector* C_FVector::VectorSubtract(FVector* pOut, FVector* pV1, FVector* pV2)
{
	*pOut = *pV1 - *pV2;

	return pOut;
}

FVector* C_FVector::VectorMaximize(FVector* pOut, FVector* pV1, FVector* pV2)
{
	pOut->X = pV1->X > pV2->X ? pV1->X : pV2->X;
	pOut->Y = pV1->Y > pV2->Y ? pV1->Y : pV2->Y;
	pOut->Z = pV1->Z > pV2->Z ? pV1->Z : pV2->Z;

	return pOut;
}

FVector* C_FVector::VectorMinimize(FVector* pOut, FVector* pV1, FVector* pV2)
{
	pOut->X = pV1->X < pV2->X ? pV1->X : pV2->X;
	pOut->Y = pV1->Y < pV2->Y ? pV1->Y : pV2->Y;
	pOut->Z = pV1->Z < pV2->Z ? pV1->Z : pV2->Z;

	return pOut;
}

FVector* C_FVector::VectorAdd(FVector* pOut, FVector* pV1, FVector* pV2)
{
	*pOut = *pV1 + *pV2;

	return pOut;
}