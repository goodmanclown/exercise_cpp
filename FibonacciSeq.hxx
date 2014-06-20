/**
 * function to calculate nth FibonacciSeq
 * F(n) = F(n-1) + F(n-2)
 * F(0) = 0, F(1) = 1
 */ 

#include <stdint.h>
#include <iostream>

using std::cout;
using std::endl;

class FibonacciSeq {

public:

	/**
	 * @param nth - nth FibonacciSeq to be calculated
    *
	 * @return value of nth FibonacciSeq
	 */
	static uint32_t calculate(uint32_t nth)
	{
		if (0 == nth) return 0;

		if (1 == nth) return 1;

		uint32_t fn_2 = 0;
		uint32_t fn_1 = 1;
		uint32_t fn = 0;
		for (uint32_t index=2; index <= nth; index++) {
			fn = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = fn;
		}

		return fn;
	}
};


