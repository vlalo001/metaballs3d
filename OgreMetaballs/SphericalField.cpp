#include "SphericalField.h"

#include "FieldHelper.h"

//-----------------------------------
// SphericalField
//-----------------------------------

SphericalField::SphericalField(const Vector3& center, float radius)
: m_center(center), m_radiusSquared(radius * radius), m_radius(radius)
{
}

SphericalField::~SphericalField()
{
}

ScalarFieldValue SphericalField::Sample(const Vector3& position) const 
{
//#define HELPER
#ifndef HELPER
	ScalarFieldValue result;

	//Compute the relative position from the center
	Vector3 relativePos = m_center - position;

	float length = relativePos.length();
	float lengthSquared = relativePos.squaredLength();

	//The scalar value is proportional to 1/r^2
	result.Scalar = m_radiusSquared / lengthSquared;

	//The gradient is is proportional to 1/r^3 and radial to the sphere
	result.Gradient = 2 * (result.Scalar) / lengthSquared * relativePos;

	//The color is uniform
	result.Color = m_color;

#else
	ScalarFieldValue result; 
	FieldHelper::CentralExpField(m_radius, m_center, position,result);
	result.Color = m_color;

#endif;
	return result;
}