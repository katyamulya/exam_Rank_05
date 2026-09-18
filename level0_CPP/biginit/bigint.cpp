#include "bigint.hpp"

//Default Constructor
bigint::bigint() : value("0") {}   //init value by 0

//Constructor with a numeric parameter
bigint::bigint(unsigned int  number)
{
	//converting number to string
	std::ostringstream buffer;
	buffer << number;
	value = buffer.str();
}

//Constructor with a string parameter
bigint::bigint(const std::string &str)
{
	//if (value.empty())
		//throw std::invalid_argument("invalid input");  //??? or just save "0"  ???
	if (str.empty()) 
	{
        value = "0";
    }
	else
	{
		this->value = str;
		check_digits();
		//throw std::invalid_argument("invalid input");  //??? or just save "0"  ??? if not digits
		remove_zeros();
	}
}

//Copy Constructor
bigint::bigint(const bigint& other) : value(other.value) {}

//Copy Assignment Operator
bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;

}

//Destructor
bigint::~bigint() {}

//Help tools:
void bigint::check_digits()
{
	size_t i = 0;
    while (i < value.size())
    {
        // If any character is not a digit (including negative signs), reset to 0
        if (!std::isdigit(static_cast<unsigned char>(value[i])))
        {
            value = "0";
            return;
        }
        i++;
    }
}

void bigint::remove_zeros()
{
    // Find the first non-zero digit after the sign
    size_t pos = value.find_first_not_of('0');

   	if (pos == std::string::npos) 
	{
        // The string consists entirely of zeros (e.g., "0000")
        value = "0";
    } 
    else 
    {
        // Strip out all leading zeros
        value = value.substr(pos);
    }
}

const std::string& bigint::getValue() const
{
	return value;
}

// Addition
bigint bigint::operator+(const bigint& other) const
{
	// Access internal strings using the reference getter
	const std::string& num1 = this->getValue();
	const std::string& num2 = other.getValue();
	std::string reversed_result = "";

	// Start tracking indices from the rightmost digits <-
	int i = static_cast<int>(num1.size()) - 1;
	int j = static_cast<int>(num2.size()) - 1;
	int carry = 0;

	// Pre-calculate max possible size to prevent reallocations
	size_t max_size = (num1.size() > num2.size() ? num1.size() : num2.size()) + 1;
	reversed_result.reserve(max_size);

	// Loop until all digits are processed and no carry remains
	while (i >= 0 || j >= 0 || carry > 0)
	{
		int sum = carry;
		if (i >= 0)
		{
			sum += num1[i] - '0';  // Convert character digit to integer
			i--;
		}
		if (j >= 0)
		{
			sum += num2[j] - '0';
			j--;
		}
		carry = sum / 10;  // Calculate the next carry (0 or 1)
		int digit = sum % 10;  // Extract the digit to save

		// Append digit character to our working string
		reversed_result += static_cast<char>(digit + '0');
	}
	// Because we appended right-to-left, the string is reversed.
	std::string result(reversed_result.rbegin(), reversed_result.rend());

	return bigint(result);
}

bigint bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return *this;
}

// Increments
bigint& bigint::operator++()  // ++b
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int) // b++
{
	// 1. Create a copy of the current state before making modifications
	bigint tmp(*this);
	// 2. Reuse your existing compound addition operator to increment by 1
    *this = *this + bigint(1); 
	// 3. Return the unmodified copy (returns the old value)
    return tmp; 
}

// Helper Function to convert bigint to size_t
/* If the shift value is too large or invalid, it clamps it to prevent memory crashes:
	bigint huge_shift("999999999999999999");
	bigint c = a << huge_shift;
*/
unsigned int bigint::bigint_to_uint(const bigint& b) const
{
	std::string str = b.getValue();
	if (str.size() > 7)
		return 9999999;  //takes 10 Mb of memory - safe size for any computer to allocate instantly (7x9)
	
	unsigned int result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

// Primitive Shift
bigint bigint::operator<<(unsigned int shift_amount) const  // b << 3 means multiplying by 1000
{
	if (this->value == "0" || shift_amount == 0)
		return *this;
	
	std::string new_value = this->value;

	// Reserve memory and append zeros
	new_value.reserve(new_value.size() + shift_amount);
	new_value.append(shift_amount, '0');

	return bigint(new_value);
}

bigint bigint::operator>>(unsigned int shift_amount) const  // b >> 3 means division by 1000
{
	if (shift_amount == 0)
		return *this;
	if (shift_amount >= this->value.size())
		return bigint("0");
	return bigint(this->value.substr(0, this->value.size() - shift_amount));
}

bigint bigint::operator<<=(unsigned int shift_amount)
{
	*this = *this << shift_amount;
	return *this;
}

bigint bigint::operator>>=(unsigned int shift_amount)
{
	*this = *this >> shift_amount;
	return *this;
}

// Bigint-Object Shift Overloads (Reusing primitive code)
bigint bigint::operator<<(const bigint& other) const
{
	return *this << bigint_to_uint(other);
}

bigint bigint::operator>>(const bigint& other) const
{
	return *this >> bigint_to_uint(other);
}

bigint bigint::operator<<=(const bigint& other)
{
	return *this <<= bigint_to_uint(other);
}

bigint bigint::operator>>=(const bigint& other)
{
	return *this >>= bigint_to_uint(other);
}

// Comparisons
bool bigint::operator==(const bigint& other) const
{
	return (this->getValue() == other.getValue());
}

bool bigint::operator!=(const bigint& other) const
{
	return !(*this == other);
}

bool bigint::operator<(const bigint& other) const
{
	if (this->getValue().size() != other.getValue().size())
		return (this->getValue().size() < other.getValue().size());
	return (this->getValue() < other.getValue());  // if sizes equal
}

bool bigint::operator>(const bigint& other) const
{
	return !(*this < other);
}

bool bigint::operator<=(const bigint& other) const
{
	return (*this < other || *this == other);
}
bool bigint::operator>=(const bigint& other) const
{
	return (*this > other || *this == other);
}

// Overload << operator
std::ostream& operator<<(std::ostream& os, const bigint& b)
{
	os << b.getValue();
	return os;
}