#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string> // for std::string
//#include <ostream> // for std::ostream 
//#include <cstddef>  // for size_t
#include <sstream>  //for std::ostringstream
//#include <stdexcept>  // for std::invalid_argument
#include <iostream>   // for std::ostream
#include <cctype>   // for std::isdigit
#include <climits>

/* 3 tools (digits, zeros, convert) + 5 orthodox + getter + help_func + 18 operators + overload << = 28 */
class bigint
{
	private:

		std::string value;

		// Helper Functions
		void check_digits();  // used in constructor
		void remove_zeros();  // used in constructor
	
	public:

		bigint();  // Default Constructor
		bigint(unsigned int  number);  // Constructor with a numeric parameter
		bigint(const std::string &str);  // Constructor with a string parameter
		bigint(const bigint& other);  // Copy Constructor
		bigint& operator=(const bigint& other);  // Copy Assignment Operator
		~bigint();  // Destructor

		// Getter
		const std::string& getValue() const;

		static unsigned int bigint_to_uint(const bigint& b);  // used for shift operators

		// Addition
		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);

		// Increments
		bigint& operator++();  // Pre-increment (++b)
		bigint operator++(int); // Post-increment (b++)

		// Shifts with primitive numbers
		bigint operator<<(unsigned int shift_amount) const;  // b << 3 means multiplying by 1000
		bigint operator>>(unsigned int shift_amount) const;  // b >> 3 means division by 1000
		bigint& operator<<=(unsigned int shift_amount);
		bigint& operator>>=(unsigned int shift_amount);

		// Shifts with bigint objects
		bigint operator<<(const bigint& other) const;
		bigint operator>>(const bigint& other) const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		// Comparisons
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator>=(const bigint& other) const;
};

// Overload the << operator for printing
std::ostream& operator<<(std::ostream& os, const bigint& b);
//std::string reverse_str(const std::string& str);

#endif