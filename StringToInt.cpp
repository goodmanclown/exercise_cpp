#include "StringToInt.hxx" 

#include <string.h>
#include <limits.h>

// on a 32 bit system, INT_MAX is 2147483647, and INT_MIN is -2147483648
// if the result accumulated is > 147483647 (if positive) or > 147483648 (if negative) and the last character is > 1, there's an overflow
// if the result accumlated is 147483647 (if positive) or 147483648 (if negative) and the last character is > 2, there's an overflow

#define OVERFLOW_CHECK (INT_MAX / 10)

#define OVERFLOW_CHECK_POS (INT_MAX % 10)
#define OVERFLOW_CHECK_NEG -(INT_MIN % 10)

#define REV_OVERFLOW_CHECK_POS 147483647
#define REV_OVERFLOW_CHECK_NEG 147483648

bool StringToInt::stringToInt(const char str[], uint32_t base, int& result)
{
	// is input string empty?
	uint32_t len = strlen(str);
	if (len == 0) return false;

	uint32_t index = 0;

	// check the sign of the number
	// assume it's a positive number
	bool neg = false; 
	char sign = str[index];
	if (sign == '-') {
		// preceded with a '-' sign, remember as a negative number
		neg = true;

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return false;
	}
	else if (sign == '+') {
		// preceded with a '+' sign

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return false;
	}

	result = 0;

	uint32_t max_value = (neg == true) ? -(INT_MIN) : (INT_MAX);
	uint32_t overflow_check = max_value / base;
	uint32_t overflow_check_digit = max_value % base;

	// use a bool to keep track if any conversion is done
	bool converted = false;
	for (uint32_t i = index; i < len; i++) {

		int numeral = -1;

		if (str[i] >= '0' && str[i] <= '9') {
			numeral = str[i] - '0';
		} 
		else if ((str[i] >= 'A' && str[i] <= 'F') && 16 == base) {
			numeral = str[i] - 'A' + 10;
		}
		else if ((str[i] >= 'a' && str[i] <= 'f') && 16 == base) {
			numeral = str[i] - 'a' + 10;
		}

		if ((numeral >= 0) && (numeral <=9)) {
			if (result > overflow_check) {
				// we got an overflow, just return
				return false;	
			}
			else if (result == overflow_check) {
				if (numeral > overflow_check_digit) {
					// we got an overflow, just return
					return false;	
				}
			}
				
			// accumulate values converted
			result = result*base + numeral;

			// mark we have converted a number
			converted = true;
		}
		else {
			// this character is not valid, return the result got so far
			break;
		}
	}

	// has any character been converted
	if (true == converted) {
		// check the sign of it
		if (neg == true) {
			result = -result;
		}
	}

	return converted;
}
	

bool StringToInt::stringToIntReverse(const char str[], int& result)
{
	// is input string empty?
	uint32_t len = strlen(str);
	if (len == 0) return false;

	uint32_t index = 0;

	// check the sign of the number
	// assume it's a positive number
	bool neg = false; 
	char sign = str[index];
	if (sign == '-') {
		// preceded with a '-' sign, remember as a negative number
		neg = true;

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return false;
	}
	else if (sign == '+') {
		// preceded with a '+' sign

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return false;
	}

// on a 32 bit system, INT_MAX is 2147483647, and INT_MIN is -2147483648
	if (len - index > 10) return false;

	uint32_t position=1;
	result = 0;

	// use a boolean to remember if the conversion is ok
	bool converted = false;
	for (uint32_t i = len - 1; i >= index; i--) {

		int numeral = str[i] - '0';

		if ((numeral >= 0) && (numeral <=9)) {
			if (((neg == false && result == REV_OVERFLOW_CHECK_POS) || (neg == true && result == REV_OVERFLOW_CHECK_NEG)) && numeral > 2) {
				// we got an overflow, just return
				return false;	
			}
			else if (((neg == false && result > REV_OVERFLOW_CHECK_POS) || (neg == true && result > REV_OVERFLOW_CHECK_NEG)) && numeral > 1) {
				// we got an overflow, just return
				return false;
			}
				
			// accumulate values converted
			result = result + numeral * position;
			position *= 10;
			
			// remember conversion is ok until told otherwise
			converted = true;
		}
		else {
			// this character is not valid, ignore the result got so far
			// restart the conversion

			// remember conversion is ng until told otherwise
			converted = false;

			position = 1;
			result = 0;
		}
	}

	if (converted == true) {
		// the string is a valid integral number
		// check the sign of it
		if (neg == true) {
			result = -result;
		}
	}

	return converted;
}
	

