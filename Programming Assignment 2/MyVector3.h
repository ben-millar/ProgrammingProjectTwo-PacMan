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

#ifndef MYVECTOR3 
#define MYVECTOR3

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector3
{
public:
	double x;
	double y;
	double z;

	MyVector3();
	~MyVector3();


	std::string toString(); // Converts our 3D vectors to strings 


	// Casting an SFML vector to MyVector3 vector
	MyVector3(double t_x, double t_y, double t_z);
	MyVector3(sf::Vector3f t_sfVector);
	MyVector3(sf::Vector3i t_sfVector);
	MyVector3(sf::Vector2i t_sfVector);
	MyVector3(sf::Vector2u t_sfVector);
	MyVector3(sf::Vector2f t_sfVector); 
	
	
	// Operator overloads
	MyVector3 operator +(const MyVector3 t_right) const; // overload + operator for the addition of 3D vectors
	MyVector3 operator -(const MyVector3 t_right) const; // overload - operator for the subtraction of 3D vectors
	MyVector3 operator *(const double t_scalar) const; // overload * operator to multiply 3D vectors by a single scalar
	MyVector3 operator /(const double t_divisor) const; // overload * operator to divide 3D vectors by a single divisor

	// We are changing the value on the left, so it is not a constant
	void operator +=(const MyVector3 t_right); // overload += operator for in-place addition of 3D vectors
	void operator -=(const MyVector3 t_right); // overload -= operator for in-place subtraction of 3D vectors

	// Check for equality/inequality overloads
	bool operator == (const MyVector3 t_right) const; // overload == operator to check equality of 3D vectors
	bool operator != (const MyVector3 t_right) const; // overload != operator to check inequality of 3D vectors

	// negative of a vector 
	MyVector3 operator -();  // this changes the vector to its inverse

	//new methods for bouncing off sides of table in billiards
	void reverseX(); // this negates the x element of the vector
	void reverseY();  // this negates the y element of the vector

	double length()const;
	double lengthSquared()const;
	double dot(const MyVector3 t_other) const;
	MyVector3 crossProduct(const MyVector3 t_other)const;
	double angleBetween(const MyVector3 t_other)const;  // answer in degrees NOT WORKING AS EXPECTED
	MyVector3 unit() const;  // vector doesn't change
	void normalise(); // vector changes and will have length 1 
	MyVector3 projection(const MyVector3 t_onto)const; // NOT WORKING AS EXPECTED
	// projection onto the other vector so answer will parallel to other vector.
	MyVector3 rejection(const MyVector3 t_onto)const;

	// These are for casting from MyVector3 types to SFML vector types? I don't fully understand this.
	operator sf::Vector2f() { return sf::Vector2f{static_cast<float>(x),static_cast<float>(y) }; }; // {2.4,-2.6,3.0} ->  {2.4~,-2.6~}
	operator sf::Vector2i() { return sf::Vector2i{static_cast<int>(x),static_cast<int>(y)}; };// {2.4,-2.6,3.0} ->  {2,-3}
	operator sf::Vector2u();// {2.4,-2.6,3.0} ->  {2,3}  needs more space than an inline
	operator sf::Vector3i() { return sf::Vector3i{static_cast<int>(x),static_cast<int>(y), static_cast<int>(z) }; };// {2.4,-2.6,3.0} ->  {2,-3,3}
	operator sf::Vector3f() { return sf::Vector3f{static_cast<float>(x),static_cast<float>(y), static_cast<float>(z) }; };// {2.4,-2.6,3.0} ->  {2.4~,-2.6~, 3.0}

};



#endif // !MYVECTOR3