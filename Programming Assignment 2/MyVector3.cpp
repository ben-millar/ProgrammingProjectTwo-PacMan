/// <summary>
/// Author: Ben Millar C00236772
/// Date: 15/12/2018
/// Estimated time to complete: 12 hours
/// Session 1 Start: 11:50 End: 12:31 15/12/2018
/// Session 2 Start: 12:15 End: 13:40 17/12/2018
/// Session 3 Start: 22:28 End: 22:57 17/12/2018
/// Session 4 Start: 14:05 End: 14:30 18/12/2018
/// Session 5 Start: 18:33 End: 19:05 18/12/2018
/// Session 6 Start: 17:55 End: 19:21 01/01/2019 
/// Session 7 Start: 18:00 End: 18:10 02/01/2019 
/// Session 8 Start: 15:25 End: 16:20 04/01/2019 
/// Session 9 Start: 17:50 End: 18:05 04/01/2019
/// Session 10 Start: 16:15 End: 16:52 04/01/2019 TOTAL: 6 hours 30 minutes
/// Known bugs: Not sure if I need to check if angle is positive or negative for angle between
/// </summary>

#include "MyVector3.h"
#include <string.h>
#define PI 3.14159265358979323846

/// <summary>
/// Default constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

/// <summary>
/// Converts a MyVector3 vector to a string
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and separated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;	
}

/// <summary>
/// create a vector 3 from three values
/// </summary>
MyVector3::MyVector3(double t_x, double t_y, double t_z)
{
	x = t_x;
	y = t_y;
	z = t_z;
}

/// <summary>
/// create a vector 3 from an sf::vector3f
/// </summary>
/// <param name="t_sfVector">input vector</param>
MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

/// <summary>
/// create a vector 3 from an sf::vector3i
/// </summary>
MyVector3::MyVector3(sf::Vector3i t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

/// <summary>
/// create a vector 3 from an sf::vector2i (z = 0.0)
/// </summary>
MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = 0.0;
}

/// <summary>
/// create a vector 3 from an sf::vector2u (z = 0.0)
/// </summary>
MyVector3::MyVector3(sf::Vector2u t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = 0.0;
}

/// <summary>
/// create a vector 3 from an sf::vector2f (z = 0.0)
/// </summary>
MyVector3::MyVector3(sf::Vector2f t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = 0.0;
}

/// <summary>
/// addition operator overload to add two 3D vectors.
/// </summary>
MyVector3 MyVector3::operator+(const MyVector3 t_right) const
{
	MyVector3 newVector;

	// add each element of the vector in turn
	newVector.x = x + t_right.x;
	newVector.y = y + t_right.y;
	newVector.z = z + t_right.z;

	return newVector;
}

/// <summary>
/// subtraction operator overload to subract two 3D vectors.
/// </summary>
MyVector3 MyVector3::operator-(const MyVector3 t_right) const
{
	MyVector3 newVector;

	// subtract each element of the RH operand from the LH operand in turn
	newVector.x = x - t_right.x;
	newVector.y = y - t_right.y;
	newVector.z = z - t_right.z;

	return newVector;
}

/// <summary>
/// multiplication operator overload to multiply a 3D vector by a scalar
/// </summary>
MyVector3 MyVector3::operator*(const double t_scalar) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	// multiply each element in turn by the scalar passed in
	newVector.x *= t_scalar;
	newVector.y *= t_scalar;
	newVector.z *= t_scalar;

	return newVector;
}

/// <summary>
/// division operator overload to divide a 3D vector by a scalar.
/// </summary>
MyVector3 MyVector3::operator/(const double t_divisor) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	if (t_divisor != 0)
	{
		// divide each element in turn by the divisor passed in
		newVector.x /= t_divisor;
		newVector.y /= t_divisor;
		newVector.z /= t_divisor;
	}
	else
	{
		newVector = { 0,0,0 }; // return null if divisor is zero
	}

	return newVector;
}

/// <summary>
/// overload for += in-place incrementation operator
/// </summary>
void MyVector3::operator+=(const MyVector3 t_right)
{
	x += t_right.x;
	y += t_right.y;
	z += t_right.z;
}

/// <summary>
/// overload for -= in-place decrementation operator
/// </summary>
void MyVector3::operator-=(const MyVector3 t_right)
{
	// subtract each element of the RH operand from the LH operand in turn
	x -= t_right.x;
	y -= t_right.y;
	z -= t_right.z;
}

/// <summary>
/// overload for ==, checks equality of 3D vectors
/// </summary>
bool MyVector3::operator==(const MyVector3 t_right) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	bool equal = false; // default to false

	// checks if ALL elements of each vector are equal 
	if (newVector.x == t_right.x && newVector.y == t_right.y && newVector.z == t_right.z)
	{
		equal = true;
	}

	return equal;
}

/// <summary>
/// overload for !=, checks inequality of 3D vectors
/// </summary>
bool MyVector3::operator!=(const MyVector3 t_right) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	bool notEqual = false; // default to false (I.e., vectors are equal)
	
	// compare each element in turn; if any do not match, then vectors are not equal.
	// the flow of control is such that if any of the elements are not equal, it won't evaluate the rest
	if (newVector.x != t_right.x)
	{
		notEqual = true;
	}
	else if (newVector.y != t_right.y)
	{
		notEqual = true;
	}
	else if (newVector.z != t_right.z)
	{
		notEqual = true;
	}

	return notEqual;
}

/// <summary>
/// gets the negation of a vector by inverting all of its components
/// </summary>
MyVector3 MyVector3::operator-()
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	newVector.x *= -1;
	newVector.y *= -1;
	newVector.z *= -1;

	return newVector;
}

/// <summary>
/// reflects a vector along the YZ-plane by inverting X-value
/// </summary>
void MyVector3::reverseX()
{
	x *= -1; // invert x-value of the original vector 
}

/// <summary>
/// reflects a vector along the XZ-plane by inverting Y-value
/// </summary>
void MyVector3::reverseY()
{
	y *= -1; // invert y-value of the original vector
}

/// <summary>
/// gets the length of a 3D vector
/// </summary>
double MyVector3::length() const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	double length = sqrt(newVector.lengthSquared()); // get the square root of the vector length squared

	return length;
}

/// <summary>
/// gets the length squared of a 3D vector (less computationally intensive than length)
/// </summary>
double MyVector3::lengthSquared() const
{
	double lengthSquared = (x*x) + (y*y) + (z*z);

	return lengthSquared;
}

/// <summary>
/// Calculates the dot product of two 3D vectors
/// </summary>
/// <returns>Dot product as a double</returns>
double MyVector3::dot(const MyVector3 t_other) const
{
	// a.b = (a.x * b.x) + (a.y * b.y) + (a.z * b.z)
	double dotProduct = (x * t_other.x) + (y* t_other.y) + (z*t_other.z);
	return dotProduct;
}

/// <summary>
/// Calculates the cross product of two 3D vectors
/// </summary>
/// <returns>Cross product as a MyVector3 vector</returns>
MyVector3 MyVector3::crossProduct(const MyVector3 t_other) const
{
	// A matrix... My kingdom for a matrix...
	// a cross b = (a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x)
	MyVector3 crossProduct = { (y*t_other.z) - (z*t_other.y), (z*t_other.x) - (x*t_other.z), (x*t_other.y) - (y*t_other.x) };

	return crossProduct;
}

/// <summary>
/// Calculates the angle between two 3D vectors
/// </summary>
/// <returns>Angle between vectors in degrees</returns>
double MyVector3::angleBetween(const MyVector3 t_other) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	double angleBetween;
	double angleBetweenDegrees;

	double dotProduct = newVector.dot(t_other); // u . v
	double lengthProduct = newVector.length() * t_other.length(); // ||u||*||v||

	if (lengthProduct != 0) // avoid division by zero
	{
		angleBetween = acos(dotProduct / lengthProduct); // angle = cos ((u.v) / ||u|| * ||v||), .'. acos = answer.
		angleBetweenDegrees = angleBetween * (180 / PI); // convert result to degrees
	}
	else
	{
		angleBetweenDegrees = 0.0; // return null if vector length product is zero
	}

	return angleBetweenDegrees;
}

/// <summary>
/// Creates a unit vector of a given vector (doesn't change original values)
/// </summary>
/// <returns>Unit vector as a MyVector3 vector</returns>
MyVector3 MyVector3::unit() const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	newVector = newVector/newVector.length(); // divide vector by its own magnitude
	return newVector;
}

/// <summary>
/// Transforms a given vector into its unit vector (changes original values)
/// </summary>
/// <returns>Original vector is changed to unit vector</returns>
void MyVector3::normalise()
{
	MyVector3 newVector{ x,y,z }; // only used for calculating magnitude
	double magnitude = newVector.length(); // get magnitude of left operand values

	if (magnitude != 0)
	{
		// change the original values
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
	else // return null if vector length is zero
	{
		x = 0;
		y = 0;
		z = 0;
	}
}

/// <summary>
/// Calculates the projection of a vector 'u', along another vector 'v'
/// </summary>
/// <returns>a MyVector3 vector 'u1' representing u projected along v</returns>
MyVector3 MyVector3::projection(const MyVector3 t_onto) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	MyVector3 projection{ 0.0,0.0,0.0 };

	double dotProduct = newVector.dot(t_onto); // dot product of u and v
	double magnitude = t_onto.length(); // magnitude of v
	MyVector3 unitVector = t_onto.unit(); // unit vector of v

	if (magnitude != 0)
	{	
		projection = unitVector * (dotProduct / magnitude);
	}

	// will return null if magnitude is zero
	return projection;
}

/// <summary>
/// Calculates the rejection of a vector 'u', along another vector 'v'
/// </summary>
/// <returns>a MyVector3 vector 'u1' representing u projected orthagonally to v</returns>
MyVector3 MyVector3::rejection(const MyVector3 t_onto) const
{
	MyVector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	MyVector3 rejection = newVector - newVector.projection(t_onto); // w = u - u1

	return rejection;
}

/// <summary>
/// MyVector3 to sf::Vector2u cast
/// </summary> 
/// <returns>sf::vector2u</returns>
MyVector3::operator sf::Vector2u()
{
	MyVector3 inputVector = { x,y,z }; // input vector
	sf::Vector2u sfv2u{}; // return vector

	// if either element is negative, make positive to avoid underflow error upon cast
	if (inputVector.x < 0) inputVector.x *= -1;
	if (inputVector.y < 0) inputVector.y *= -1;

	// cast and assign
	sfv2u.x = static_cast<unsigned>(inputVector.x);
	sfv2u.y = static_cast<unsigned>(inputVector.y);

	return sfv2u;
}
