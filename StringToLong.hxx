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

class StringToLong {

public:

	/**
	 * @param str - a pointer to a character string representing an integral number
	 * 
	 * @return value of type long parsed from the input  
	 */
	static long stringToLong(const char* str);

	
	/**
	 * a recursive api to convert the string to a long 
    *
	 * @param str - an array of character string representing an integral number
	 * @param index - index to character in the array to be converted
	 * @param len - length of input str to be examined
	 * @param place - value of power of 10 based on the position of digits
	 *
	 * @return value of type unsigned long parsed from the input
    */
#if __LP64__
	static uint64_t convertRecursive(const char str[], uint32_t index, uint32_t len, uint64_t& place);
#else
	static uint32_t convertRecursive(const char str[], uint32_t index, uint32_t len, uint32_t& place);
#endif
		
};


