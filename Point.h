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

public:
	Point(const Point& p);
	~Point() = default;

	static Point rect(float x, float y, float z);
	static Point polar(float radius, float angle, float z);

	void set(const float x, const float y, const float z);

	float magnitude() const;
	float magnitude(const Point& p);

	Point& anchor(const float& mod);
	Point anchor(const Point& p, const float& mod);

	Point& floor();
	Point& round();

	const void print(bool newline = false) const;

	/* Internal Value Getters of different types (x,y,z:floats) (xi,yi,zi:ints) */
	const float& x() const;
	const float& y() const;
	const float& z() const;

	const int& xi() const;
	const int& yi() const;
	const int& zi() const;

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
	Point& operator-= (const float& f);
	Point operator- (const float& f);

	Point& operator*= (const float& f);
	Point operator* (const float& f);

};

/* Methods */
inline Point::Point(float x, float y, float z) : X_(x), Y_(y), Z_(z) {}
inline Point::Point(const Point& p) : X_(p.X_), Y_(p.Y_), Z_(p.Z_) {}

inline Point Point::rect(float x, float y, float z) { return Point(x, y, z); }
inline Point Point::polar(float radius, float angle, float vert) { return Point(radius * std::cos(angle), vert, radius * std::sin(angle)); }

inline void Point::set(const float x, const float y, const float z) { X_ = x; Y_ = y; Z_ = z; }

inline float Point::magnitude() const { return std::sqrt(std::pow(this->X_, 2) + std::pow(this->Y_, 2) + std::pow(this->Z_, 2)); }
inline float Point::magnitude(const Point& p) { return Point(*this + p).magnitude(); }

inline Point& Point::anchor(const float& mod) {
	this->X_ -= std::fmod(this->X_, mod);
	this->Y_ -= std::fmod(this->Y_, mod);
	this->Z_ -= std::fmod(this->Z_, mod);
	return *this;
}
inline Point Point::anchor(const Point& p, const float& mod) {
	return Point::rect(p.X_ - std::fmod(p.X_, mod), p.Y_ - std::fmod(p.Y_, mod), p.Z_ - std::fmod(p.Z_, mod));
}

inline Point& Point::floor() {
	this->X_ = std::floor(this->X_);
	this->Y_ = std::floor(this->Y_);
	this->Z_ = std::floor(this->Z_);
	return *this;
}
inline Point& Point::round() {
	this->X_ = std::round(this->X_);
	this->Y_ = std::round(this->Y_);
	this->Z_ = std::round(this->Z_);
	return *this;
}

/* Print (x,y,z) with no leading/trailing spaces or newlines */
inline const void Point::print(bool newline) const { std::cout << "(" << X_ << "," << Y_ << "," << Z_ << ")"; if(newline) { std::cout << std::endl; } }

/* Getters and Setters */
inline const float& Point::x() const { return this->X_; }
inline const float& Point::y() const { return this->Y_; }
inline const float& Point::z()  const { return this->Z_; }

inline const int& Point::xi() const { return static_cast<int>(this->X_); }
inline const int& Point::yi() const { return static_cast<int>(this->Y_); }
inline const int& Point::zi() const { return static_cast<int>(this->Z_); }


/* Logic Overloads */
inline bool Point::operator==(const Point& p) const { return (this->X_ == p.X_) && (this->Y_ == p.Y_) && (this->Z_ == p.Z_); }
inline bool Point::operator!= (const Point& p) const { return !operator==(p); }
inline bool Point::operator<(const Point& p) const { return (this->Y_ < p.Y_) || (this->Y_ == p.Y_ && this->Z_ < p.Z_) || (this->Y_ == p.Y_ && this->Z_ == p.Z_ && this->X_ < p.X_); }
inline bool Point::operator> (const Point& p) const { return p < *this; }
inline bool Point::operator<= (const Point& p) const { return !operator>(p); }
inline bool Point::operator>= (const Point& p) const { return !operator<(p); }


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
inline Point& Point::operator-=(const float& f) {
	this->X_ -= f;
	this->Y_ -= f;
	this->Z_ -= f;
	return *this;
}
inline Point Point::operator-(const float& f) { return Point::rect(this->X_ - f, this->Y_ - f, this->Z_ - f); }

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