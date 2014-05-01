#include <stdint.h>

/**
 * class to convert string to long
 *
 * Parses the C-string str interpreting its content as an integral number, which is returned as a value of type long int.
 *
 * The function first discards as many whitespace characters (as in isspace) as necessary until the first non-whitespace character is found. Then, starting
 * from this character, takes an optional initial plus or minus sign followed by as many base-10 digits as possible, and interprets them as a numerical 
 * value.
 *
 * The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this 
 * function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or 
 * it contains only whitespace characters, no conversion is performed and zero is returned.
 */ 

class StringToInt {

public:

	/**
	 * @param str - a pointer to a character string representing an integral number
	 * 
	 * @return value of type long parsed from the input  
	 */
	static bool stringToInt(const char str[], uint32_t base, int& result);


	/**
	 * @param str - a pointer to a character string representing an integral number
	 * 
	 * @return value of type long parsed from the input  
	 */
	static bool stringToIntReverse(const char str[], int& result);

};


