/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Utility_Math.h
* Description : Extra utility functions and structures for mathematics
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

//Inclusion Guards
#pragma once
#ifndef __UTILITY_MATH_H__
#define __UTILITY_MATH_H__

// Defines
#define _USE_MATH_DEFINES

// Library Includes
#include <math.h>

/***********************
Constants
********************/
const float PI = 3.14159265358979323f;

/***********************
* v2float: Struct to hold 2 float values
* @author: Callan Moore
********************/
struct v2float
{
	float x;
	float y;

	/***********************
	* v2float: Constructor for the v2float struct
	* @author: Callan Moore
	* @parameter: x: X coordinate
	* @parameter: y: Y coordinate
	********************/
	v2float(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
	}

	/***********************
	* operator=: Assignment Operator for the v2float struct
	* @author: Callan Moore
	* @parameter: _v2: v2float to be copied
	* @return: v2float: the result of the assignment
	********************/
	v2float& operator=(const v2float _v2)
	{
		x = _v2.x;
		y = _v2.y;
		return *this;
	}

	/***********************
	* operator==: Is equal to Operator for the v2float struct
	* @author: Callan Moore
	* @parameter: _v2: v2float to be checked against
	* @return: bool: True if the v2floats are equal
	********************/
	bool operator==(const v2float _v2)
	{
		if (x == _v2.x
			&&	y == _v2.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/***********************
	* operator+: Addition Operator for the v2float struct plus a v2float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the addition
	* @return: v2float: The result of the addition
	********************/
	v2float operator+ (const v2float _v2) const
	{
		return v2float{ _v2.x + x, _v2.y + y };
	}

	/***********************
	* operator+: Addition Operator for the v2float struct plus a float
	* @author: Callan Moore
	* @parameter: _f: Right hand side of the addition
	* @return: v2float: The result of the addition
	********************/
	v2float operator+ (const float _f) const
	{
		return v2float{ _f + x, _f + y };
	}

	/***********************
	* operator+=: Addition Assignment Operator for the v2float struct
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the addition
	* @return: v2float: The result of the addition assignment
	********************/
	v2float operator+= (const v2float _v2)
	{
		return v2float{ x += _v2.x, y += _v2.y };
	}

	/***********************
	* operator-: Subtraction Operator for the v2float struct minus a v2float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the subtraction
	* @return: v2float: The result of the subtraction
	********************/
	v2float operator- (const v2float _v2) const
	{
		return v2float{ x - _v2.x, y - _v2.y };
	}

	/***********************
	* operator-: Subtraction Operator for the v2float struct minus a float
	* @author: Callan Moore
	* @parameter: _f: Right hand side of the subtraction
	* @return: v2float: The result of the subtraction
	********************/
	v2float operator- (const float _f) const
	{
		return v2float{ x - _f, y - _f };
	}

	/***********************
	* operator-=: Subtraction Assignment Operator for the v2float struct minus a v2float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the subtraction
	* @return: v2float: The result of the subtraction
	********************/
	v2float operator-= (const v2float _v2)
	{
		return v2float{ x -= _v2.x, y -= _v2.y };
	}

	/***********************
	* operator*: Multiplication Operator for a v2float times a v3float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the multiplication
	* @return: v2float: The result of the multiplication
	********************/
	v2float operator* (const v2float _v2) const
	{
		return v2float{ _v2.x * x, _v2.y * y };
	}

	/***********************
	* operator*: Multiplication Operator for a v2float times a float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the multiplication
	* @return: v2float: The result of the multiplication
	********************/
	v2float operator* (const float _f) const
	{
		return v2float{ _f * x, _f * y };
	}

	/***********************
	* operator/: Division Operator for a v2float times a float
	* @author: Callan Moore
	* @parameter: _v2: Right hand side of the Division
	* @return: v2float: The result of the Division
	********************/
	v2float operator/ (const float _f) const
	{
		return v2float{ x / _f, y / _f };
	}

	/***********************
	* Magnitude: Calculate the magnitude of this v2float
	* @author: Callan Moore
	* @return: float: The magnitude of the v2float
	********************/
	float Magnitude()
	{
		return (sqrt(pow(x, 2) + pow(y, 2)));
	}

	/***********************
	* NormaliseV2Float: Normalise a vector of 2 floats
	* @author: Callan Moore
	* @parameter: _v2: vector to normalize
	* @return: v2float: the normalized vector
	********************/
	v2float Normalise()
	{
		float fMagnitude = this->Magnitude();

		if (fMagnitude != 0)
		{
			this->x = (this->x / fMagnitude);
			this->y = (this->y / fMagnitude);
		}
		return (*this);
	}
};

/***********************
* v3float: Struct to hold 3 float values
* @author: Callan Moore
********************/
struct v3float
{
	float x;
	float y;
	float z;

	/***********************
	* v3float: Constructor for the v3float struct
	* @author: Callan Moore
	* @parameter: x: X coordinate
	* @parameter: y: Y coordinate
	* @parameter: z: Z coordinate
	********************/
	v3float(float _x = 0, float _y = 0, float _z = 0)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	/***********************
	* operator=: Assignment Operator for the v3float struct
	* @author: Callan Moore
	* @parameter: _v3: v3float to be copied
	* @return: v3float: the result of the assignment
	********************/
	v3float& operator=(const v3float _v3)
	{
		x = _v3.x;
		y = _v3.y;
		z = _v3.z;
		return *this;
	}

	/***********************
	* operator==: Is equal to Operator for the v3float struct
	* @author: Callan Moore
	* @parameter: _v3: v3float to be checked against
	* @return: bool: True if the v3floats are equal
	********************/
	bool operator==(const v3float _v3)
	{
		if (x == _v3.x
			&&	y == _v3.y
			&&	z == _v3.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/***********************
	* operator+: Addition Operator for the v3float struct plus a v3float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the addition
	* @return: v3float: The result of the addition
	********************/
	v3float operator+ (const v3float _v3) const
	{
		return v3float{ _v3.x + x, _v3.y + y, _v3.z + z };
	}

	/***********************
	* operator+: Addition Operator for the v3float struct plus a float
	* @author: Callan Moore
	* @parameter: _f: Right hand side of the addition
	* @return: v3float: The result of the addition
	********************/
	v3float operator+ (const float _f) const
	{
		return v3float{ _f + x, _f + y, _f + z };
	}

	/***********************
	* operator+=: Addition Assignment Operator for the v3float struct
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the addition
	* @return: v3float: The result of the addition assignment
	********************/
	v3float operator+= (const v3float _v3)
	{
		return v3float{ x += _v3.x, y += _v3.y, z += _v3.z };
	}

	/***********************
	* operator-: Subtraction Operator for the v3float struct minus a v3float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the subtraction
	* @return: v3float: The result of the subtraction
	********************/
	v3float operator- (const v3float _v3) const
	{
		return v3float{ x - _v3.x, y - _v3.y, z - _v3.z };
	}

	/***********************
	* operator-: Subtraction Operator for the v3float struct minus a float
	* @author: Callan Moore
	* @parameter: _f: Right hand side of the subtraction
	* @return: v3float: The result of the subtraction
	********************/
	v3float operator- (const float _f) const
	{
		return v3float{ x - _f, y - _f, z - _f };
	}

	/***********************
	* operator-=: Subtraction Assignment Operator for the v3float struct minus a v3float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the subtraction
	* @return: v3float: The result of the subtraction
	********************/
	v3float operator-= (const v3float _v3)
	{
		return v3float{ x -= _v3.x, y -= _v3.y, z -= _v3.z };
	}

	/***********************
	* operator*: Multiplication Operator for a v3float times a v3float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the multiplication
	* @return: v3float: The result of the multiplication
	********************/
	v3float operator* (const v3float _v3) const
	{
		return v3float{ _v3.x * x, _v3.y * y, _v3.z * z };
	}

	/***********************
	* operator*=: Multiplication Assignment Operator for a v3float times a v3float
	* @author: Jc Fowles
	* @parameter: _v3: Right hand side of the multiplication
	* @return: v3float: The result of the multiplication
	********************/
	v3float operator*= (const v3float _v3) 
	{
		return v3float{ x *= _v3.x, y *= _v3.y, z *= _v3.z };
	}

	/***********************
	* operator*: Multiplication Operator for a v3float times a float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the multiplication
	* @return: v3float: The result of the multiplication
	********************/
	v3float operator* (const float _f) const
	{
		return v3float{ _f * x, _f * y, _f * z };
	}

	/***********************
	* operator/: Division Operator for a v3float times a float
	* @author: Callan Moore
	* @parameter: _v3: Right hand side of the Division
	* @return: v3float: The result of the Division
	********************/
	v3float operator/ (const float _f) const
	{
		return v3float{ x / _f, y / _f, z / _f };
	}

	/***********************
	* Magnitude: Calculate the magnitude of this v3float
	* @author: Callan Moore
	* @return: float: The magnitude of the v3float
	********************/
	float Magnitude()
	{
		return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
	}

	/***********************
	* NormaliseV3Float: Normalise a vector of 3 floats
	* @author: Callan Moore
	* @parameter: _v3: vector to normalise
	* @return: v3float: the normalised vector
	********************/
	v3float Normalise()
	{
		float fMagnitude = this->Magnitude();

		if (fMagnitude != 0)
		{
			this->x = (this->x / fMagnitude);
			this->y = (this->y / fMagnitude);
			this->z = (this->z / fMagnitude);
		}
		return (*this);
	}

	/***********************
	* Limit: Limit the magnitude of the vector if it is greater than the input float
	* @author: Callan Moore
	* @parameter: _f: vector to normalise
	* @return: v3float: the normalised vector
	********************/
	v3float Limit(const float _f)
	{
		float fMagnitude = this->Magnitude();

		if (fMagnitude > _f)
		{
			(*this) = (this->Normalise()) * _f;
		}
		return (*this);
	}
};

/***********************
* OnLineSegment: Checks if a point is on the given line segment
* @author: Callan Moore
* @parameter: _linePtA: First point of the line
* @parameter: _linePtB: Second point of the line
* @parameter: _point: Point to check if it lies on the line segment
* @return: bool: True if the point is on the line, false otherwise
********************/
inline bool OnLineSegment(v2float _linePtA, v2float _linePtB, v2float _point)
{
	if (_linePtB.x <= max(_linePtA.x, _point.x) && _linePtB.x >= min(_linePtA.x, _point.x) &&
		_linePtB.y <= max(_linePtA.y, _point.y) && _linePtB.y >= min(_linePtA.y, _point.y))
	{
		return true;
	}

	return false;
}

/***********************
* Orientation: Determines the orientation of a line and a point
* @author: Callan Moore
* @parameter: _linePtA: First point on the line
* @parameter: _linePtB: second point on the line
* @parameter: _point: Point of the second line to cross reference
* @return: int: Value to represent the orientation of the 3 points
********************/
inline int Orientation(v2float _linePtA, v2float _linePtB, v2float _point)
{
	// 0 -> All points are co linear
	// 1 -> Clockwise orientation
	// 2 -> Counterclockwise orientation

	float val = (_linePtB.y - _linePtA.y) * (_point.x - _linePtB.x) - (_linePtB.x - _linePtA.x) * (_point.y - _linePtB.y);

	if (val == 0)
	{
		return 0;  // co linear
	}

	return (val > 0) ? 1 : 2;
}

/***********************
* CheckLinesIntersect: Checks whether two line segments intersect
* @author: Callan Moore
* @parameter: _line1PtA: First point on line 1
* @parameter: _line1PtB: Second point on line 1
* @parameter: _line2PtA: First point on line 2
* @parameter: _line2PtB: Second point on line 2
* @return: bool: True if the line segments intersect
********************/
inline bool CheckLinesIntersect(v2float _line1PtA, v2float _line1PtB, v2float _line2PtA, v2float _line2PtB)
{
	// Find the four orientations needed for general and special cases
	int orientation1 = Orientation(_line1PtA, _line1PtB, _line2PtA);
	int orientation2 = Orientation(_line1PtA, _line1PtB, _line2PtB);
	int orientation3 = Orientation(_line2PtA, _line2PtB, _line1PtA);
	int orientation4 = Orientation(_line2PtA, _line2PtB, _line1PtB);

	// General case
	if (orientation1 != orientation2 && orientation3 != orientation4)
	{
		return true;
	}

	// Special Cases
	// _line1PtA, _line1PtB and _line2PtA are co linear and _line2PtA lies on segment Line1
	if (orientation1 == 0 && OnLineSegment(_line1PtA, _line2PtA, _line1PtB))
	{
		return true;
	}

	// _line1PtA, _line1PtB and _line2PtA are co linear and _line2PtB lies on segment Line1
	if (orientation2 == 0 && OnLineSegment(_line1PtA, _line2PtB, _line1PtB))
	{
		return true;
	}

	// _line2PtA, _line2PtB and _line1PtA are co linear and _line1PtA lies on segment Line2
	if (orientation3 == 0 && OnLineSegment(_line2PtA, _line1PtA, _line2PtB))
	{
		return true;
	}

	// _line2PtA, _line2PtB and _line1PtB are co linear and _line1PtB lies on segment Line2
	if (orientation4 == 0 && OnLineSegment(_line2PtA, _line1PtB, _line2PtB))
	{
		return true;
	}

	return false; // No situation does the line segments intersect
}

/***********************
* DegreesToRadians: Converts degrees to radians
* @author: Callan Moore
* @parameter: _degrees: Angle in Degrees to convert
* @return: float: Angle in Radians
********************/
inline float DegreesToRadians(float _degrees)
{
	return ((_degrees * (float)M_PI) / 180.0f);
}

/***********************
* RadiansToDegrees: Converts radians to degrees
* @author: Callan Moore
* @parameter: _radians: Angle in radians to convert
* @return: float: Angle in degrees
********************/
inline float RadiansToDegrees(float _radians)
{
	return (180.0f * _radians / float(M_PI));
}

#endif	// __UTILITY_MATH_H__