#ifndef _FROTATOR_H_
#define _FROTATOR_H_

struct FRotator
{
	float Pitch, Yaw, Roll;

	FRotator() {}

	FRotator(float Pitch, float Yaw, float Roll)
	{
		this->Pitch = Pitch;
		this->Yaw = Yaw;
		this->Roll = Roll;
	}


	// casting
	operator FLOAT* ();
	operator CONST FLOAT* () const;

	FRotator operator - () { return FRotator(-Pitch, -Yaw, -Roll); }

	FRotator operator + (FRotator r) { return FRotator(Pitch + r.Pitch, Yaw + r.Yaw, Roll + r.Roll); }
	FRotator operator - (FRotator r) { return FRotator(Pitch - r.Pitch, Yaw - r.Yaw, Roll - r.Roll); }
	FRotator operator * (FRotator r) { return FRotator(Pitch * r.Pitch, Yaw * r.Yaw, Roll * r.Roll); }
	FRotator operator / (FRotator r) { return FRotator(Pitch / r.Pitch, Yaw / r.Yaw, Roll / r.Roll); }

	FRotator operator = (FRotator r)
	{
		this->Pitch = r.Pitch;
		this->Yaw = r.Yaw;
		this->Roll = r.Roll;

		return *this;
	}

	FRotator operator += (FRotator r)
	{
		this->Pitch += r.Pitch;
		this->Yaw += r.Yaw;
		this->Roll += r.Roll;

		return *this;
	}

	FRotator operator -= (FRotator r)
	{
		this->Pitch -= r.Pitch;
		this->Yaw -= r.Yaw;
		this->Roll -= r.Roll;

		return *this;
	}

	FRotator operator /= (FRotator r)
	{
		this->Pitch /= r.Pitch;
		this->Yaw /= r.Yaw;
		this->Roll /= r.Roll;

		return *this;
	}

	FRotator operator *= (FRotator r)
	{
		this->Pitch *= r.Pitch;
		this->Yaw *= r.Yaw;
		this->Roll *= r.Roll;

		return *this;
	}

	FRotator operator + (FLOAT f) { return FRotator(Pitch + f, Yaw + f, Roll + f); }
	FRotator operator - (FLOAT f) { return FRotator(Pitch - f, Yaw - f, Roll - f); }
	FRotator operator * (FLOAT f) { return FRotator(Pitch * f, Yaw * f, Roll * f); }
	FRotator operator / (FLOAT f) { return FRotator(Pitch / f, Yaw / f, Roll / f); }

	FRotator operator = (FLOAT f)
	{
		this->Pitch = f;
		this->Yaw = f;
		this->Roll = f;

		return *this;
	}

	FRotator operator += (FLOAT f)
	{
		this->Pitch += f;
		this->Yaw += f;
		this->Roll += f;

		return *this;
	}

	FRotator operator -= (FLOAT f)
	{
		this->Pitch -= f;
		this->Yaw -= f;
		this->Roll -= f;

		return *this;
	}

	FRotator operator /= (FLOAT f)
	{
		this->Pitch /= f;
		this->Yaw /= f;
		this->Roll /= f;

		return *this;
	}

	FRotator operator *= (FLOAT f)
	{
		this->Pitch *= f;
		this->Yaw *= f;
		this->Roll *= f;

		return *this;
	}

	BOOL operator == (FRotator r) { return ((Pitch == r.Pitch) && (Yaw == r.Yaw) && (Roll == r.Roll)); }
	BOOL operator != (FRotator r) { return ((Pitch != r.Pitch) || (Yaw != r.Yaw) || (Roll != r.Roll)); }

	FLOAT operator [] (INT i)
	{
		if (i == 0)
			return Pitch;
		else if (i == 1)
			return Yaw;
		else
			return Roll;
	}
};

#endif