#ifndef VECT2_HPP
#define VECT2_HPP

class vect2
{
	private:
		int x;
		int y;

	public:
		/* Orthodox Canonical Form */
		vect2();  // {0, 0}
		vect2(int x, int y);  // {x, y}
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

		// + - *
		vect2 operator+(const vect2 other) const;
		vect2 operator-(const vect2 other) const;
		vect2 operator*(const int scalar) const;  // v * 2
		// += -= *=
		vect2& operator+=(const vect2 other);
		vect2& operator-=(const vect2 other);
		vect2& operator*=(const int scalar);
		// ++ --
		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);
		// unary -
		vect2 operator-() const;
		// == !=
		bool operator==(const vect2& other) const;
		bool operator!=(const vect2& other) const;

		// []
		int& operator[](int index);
		const int& operator[](int index) const;
};

// <<
std::ostream& operator<<(std::ostream& out, const vect2& v);

// 2 * v
vect2 operator*(const int scalar, const vect2& v);


#endif