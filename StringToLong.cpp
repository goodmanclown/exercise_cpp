#include "StringToLong.hxx"

#include <string.h>

/**
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
 *  
 * @param str - a pointer to a character string representing an integral number
 *   
 * @return value of type long parsed from the input  
 */ 
long StringToLong::stringToLong(const char* str)
{
	// is input pointer null?
	if (str == NULL) return 0;

	// is input string empty?
	uint32_t len = strlen(str);
	if (len == 0) return 0;

	// stripped away preceding whitespace
	uint32_t index=0;
	while (str[index] == ' ' && index < len) index++;

	// is left with an empty string?
	if (index >= len) return 0;

	// check the sign of the number
	// assume it's a positive number
	bool negativeNum = false; 
	char sign = str[index];
	if (sign == '-') {
		// preceded with a '-' sign, remember as a negative number
		negativeNum = true;

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return 0;
	}
	else if (sign == '+') {
		// preceded with a '+' sign

		// skip this character
		index++;

		// is left with an empty string?
		if (index >= len) return 0;
	}

	// reduce the length of the string by the number of characters examined so far
	len -= index;

#ifdef __LP64__
	// on a 64-bit system, LONG_MAX is 9223372036854775807L
	// limit to the remaining 19 characters
	if (len > 19) len = 19;

	uint64_t place=0;
	uint64_t result = convertRecursive(str, index, len, place);
#else
	// on a 32-bit system, LONG_MAX is 2147483647L
	// limit to the remaining 10 characters
	if (len > 10) len = 10;

	uint32_t place=0;
	uint32_t result = convertRecursive(str, index, len, place);
#endif

	if (place >= 1) {
		// the string is a valid integral number
		// check the sign of it
		if (negativeNum == true) return -result;
		else return result;
	}
	else {
		// the string is not a valid integral number
		return 0;
	}
}
	


/** 
 * a recursive api to convert the string to a long
 *
 * @param str - an array of character string representing an integral number
 * @param index - index to character in the array to be converted
 * @param len - length of input str to be examined
 * @param place - value of power of 10 based on the position of digits.  if place is 0, ignore output 
 *   
 * @return value of type long parsed from the input
 */ 
#ifdef __LP64__
uint64_t StringToLong::convertRecursive(const char str[], uint32_t index, uint32_t len, uint64_t& place)
#else
uint32_t StringToLong::convertRecursive(const char str[], uint32_t index, uint32_t len, uint32_t& place)
#endif
{
	if (len == 0) {
		// an error, just return
		place = 0;
      return 0;
	}
   else if (len == 1) { 
      // we are at the last digit
		char numeral = str[index] - '0';
      if (numeral >= 0 && numeral <= 9) {
			// set the place to 1, i.e., 10 to the power 0
      	place = 1;  
         return numeral;
      }
      else {
			// the character at the position is not a numeral, ignore it
			place = 0;
         return 0;
		}
   }
   else {  
      // convert the 1st char in the string  
		char numeral = str[index] - '0';
      if (numeral >= 0 && numeral <= 9) {
			// call the api again to convert the rest of the string
#ifdef __LP64__
			uint64_t sum = convertRecursive(str, index+1, len-1, place);
#else
			uint32_t sum = convertRecursive(str, index+1, len-1, place);
#endif
			if (place >= 1) {
				place = place*10;	// raise another power of 10
				return sum + numeral*place;
			}
			else {
				// ignore the rest of the string
				// make this character the last digit of the integral number
				// set the place to 1, i.e., 10 to the power 0
				place = 1;
				return numeral;
			}
      }
      else {    
			// the character at the position is not a numeral, ignore it and the rest of the string
			place = 0;
         return 0;
		}
   }
}
