#ifndef _CFVECTOR_H_
#define _CFVECTOR_H_
#include <windows.h>
#include <math.h>

struct FVector
{
	FLOAT X, Y, Z;

	FVector() {}

	FVector(FLOAT X, FLOAT Y, FLOAT Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	operator FLOAT* ();
	operator CONST FLOAT* () const;

	FVector operator - () { return FVector(-X, -Y, -Z); }

	FVector operator + (FVector v) { return FVector(X + v.X, Y + v.Y, Z + v.Z); }
	FVector operator - (FVector v) { return FVector(X - v.X, Y - v.Y, Z - v.Z); }
	FVector operator * (FVector v) { return FVector(X * v.X, Y * v.Y, Z * v.Z); }
	FVector operator / (FVector v) { return FVector(X / v.X, Y / v.Y, Z / v.Z); }

	FVector operator = (FVector v)
	{
		this->X = v.X;
		this->Y = v.Y;
		this->Z = v.Z;

		return *this;
	}

	FVector operator += (FVector v)
	{
		this->X += v.X;
		this->Y += v.Y;
		this->Z += v.Z;

		return *this;
	}

	FVector operator -= (FVector v)
	{
		this->X -= v.X;
		this->Y -= v.Y;
		this->Z -= v.Z;

		return *this;
	}

	FVector operator /= (FVector v)
	{
		this->X /= v.X;
		this->Y /= v.Y;
		this->Z /= v.Z;

		return *this;
	}

	FVector operator *= (FVector v)
	{
		this->X *= v.X;
		this->Y *= v.Y;
		this->Z *= v.Z;

		return *this;
	}

	FVector operator + (FLOAT f) { return FVector(X + f, Y + f, Z + f); }
	FVector operator - (FLOAT f) { return FVector(X - f, Y - f, Z - f); }
	FVector operator * (FLOAT f) { return FVector(X * f, Y * f, Z * f); }
	FVector operator / (FLOAT f) { return FVector(X / f, Y / f, Z / f); }

	FVector operator = (FLOAT f)
	{
		this->X = f;
		this->Y = f;
		this->Z = f;

		return *this;
	}

	FVector operator += (FLOAT f)
	{
		this->X += f;
		this->Y += f;
		this->Z += f;

		return *this;
	}

	FVector operator -= (FLOAT f)
	{
		this->X -= f;
		this->Y -= f;
		this->Z -= f;

		return *this;
	}

	FVector operator /= (FLOAT f)
	{
		this->X /= f;
		this->Y /= f;
		this->Z /= f;

		return *this;
	}

	FVector operator *= (FLOAT f)
	{
		this->X *= f;
		this->Y *= f;
		this->Z *= f;

		return *this;
	}

	BOOL operator == (FVector v) { return ((X == v.X) && (Y == v.Y) && (Z == v.Z)); }
	BOOL operator != (FVector v) { return ((X != v.X) || (Y != v.Y) || (Z != v.Z)); }

	FLOAT operator [] (INT i)
	{
		if (i == 0)
			return X;
		else if (i == 1)
			return Y;
		else
			return Z;
	}

	FLOAT Length() { return sqrtf(X * X + Y * Y + Z * Z); }

};

class C_FVector
{
public:
	C_FVector();
	static FLOAT VectorDotProduct(FVector* pV1, FVector* pV2);
	static FLOAT VectorLength(FVector* pV);
	static FVector* VectorNormalize(FVector* pOut, FVector* pV);
	static FVector* VectorScale(FVector* pOut, FVector* pV, FLOAT Scale);
	static FVector* VectorSubtract(FVector* pOut, FVector* pV1, FVector* pV2);
	static FVector* VectorMaximize(FVector* pOut, FVector* pV1, FVector* pV2);
	static FVector* VectorMinimize(FVector* pOut, FVector* pV1, FVector* pV2);
	static FVector* VectorAdd(FVector* pOut, FVector* pV1, FVector* pV2);


};

#endif