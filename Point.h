#pragma once
#include <cmath>

/*
3 Dimensional Point system using rectangular, polar, and spherical coordinate systems

# Future Implementation #
If only two values are given, assume vertical axis to be zero
*/
class Point {

	float X_, Y_, Z_; // Y is vertical in OpenGL

	Point(float x, float y, float z);
	Point(const Point& p);

public:
	~Point() = default;

	static Point rect(float x, float y, float z);
	static Point polar(float radius, float angle, float z);

	float magnitude() const;
	float magnitude(const Point& p);

	/* Logic Overloads*/
	bool operator== (const Point& p) const;
	bool operator!= (const Point& p) const;
	bool operator< (const Point& p) const;
	bool operator> (const Point& p) const;
	bool operator<= (const Point& p) const;
	bool operator>= (const Point& p) const;

	/* Arithmetic Overloads */
	Point& operator+= (const Point& p);
	Point operator+ (const Point& p);
	Point& operator-= (const Point& p);
	Point operator- (const Point& p);
	Point& operator*= (const float& f);
	Point operator* (const float& f);

};

/* Methods */
inline Point::Point(float x, float y, float z) : X_(x), Y_(y), Z_(z) {}
inline Point::Point(const Point& p) : X_(p.X_), Y_(p.Y_), Z_(p.Z_) {}

inline Point Point::rect(float x, float y, float z) { return Point(x, y, z); }
inline Point Point::polar(float radius, float angle, float vert) { return Point(radius * std::cos(angle), vert, radius * std::sin(angle)); }
inline float Point::magnitude() const { return std::sqrt(std::pow(this->X_, 2) + std::pow(this->Y_, 2) + std::pow(this->Z_, 2)); }
inline float Point::magnitude(const Point& p) { return Point(*this + p).magnitude(); }

/* Logic Overloads */
inline bool Point::operator==(const Point& p) const { return (this->X_ == p.X_) && (this->Y_ == p.Y_) && (this->Z_ == p.Z_); }
inline bool Point::operator!= (const Point& p) const { return !operator==(p); }
inline bool Point::operator<(const Point& p) const {
	float r = std::sqrt(std::pow(this->X_, 2) + std::pow(this->Y_, 2) + std::pow(this->Z_, 2));
	float r2 = std::sqrt(std::pow(p.X_, 2) + std::pow(p.Y_, 2) + std::pow(p.Z_, 2));
	return r < r2;
}
inline bool Point::operator> (const Point& p) const {
	float r = std::sqrt(std::pow(this->X_, 2) + std::pow(this->Y_, 2) + std::pow(this->Z_, 2));
	float r2 = std::sqrt(std::pow(p.X_, 2) + std::pow(p.Y_, 2) + std::pow(p.Z_, 2));
	return r > r2;
}
inline bool Point::operator<= (const Point& p) const { return !operator>(p); }
inline bool Point::operator>= (const Point& p) const { return !operator< (p); }


/* Arithmetic Overloads */
inline Point& Point::operator+= (const Point& p) {
	this->X_ += p.X_;
	this->Y_ += p.Y_;
	this->Z_ += p.Z_;
	return *this;
}
inline Point Point::operator+(const Point& p) { return Point::rect(this->X_ + p.X_, this->Y_ + p.Y_, this->Z_ + p.Z_); }
inline Point& Point::operator-=(const Point& p) {
	this->X_ -= p.X_;
	this->Y_ -= p.Y_;
	this->Z_ -= p.Z_;
	return *this;
}
inline Point Point::operator-(const Point& p) { return Point::rect(this->X_ - p.X_, this->Y_ - p.Y_, this->Z_ - p.Z_); }
inline Point& Point::operator*=(const float& f) {
	this->X_ *= f;
	this->Y_ *= f;
	this->Z_ *= f;
	return *this;
}
inline Point Point::operator*(const float& f) { return Point::rect(this->X_ * f, this->Y_ * f, this->Z_ * f); }








/* Useful Information

Spherical -> Rect
x = r cos 0
y = y
z = r sin 0

Rect -> Spherical
r^2 = x^2 + z^2
tan0 = z/x
y = y

*/