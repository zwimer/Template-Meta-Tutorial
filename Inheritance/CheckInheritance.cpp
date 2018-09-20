/* Compiled with
	g++ CheckInheritance.cpp -pedantic -Werror -std=c++11 -o CheckInheritance.out
*/

#include <stdlib.h>
#include <iostream>


/****************************************************************/
/*																*/
/*						Template Meta							*/
/*																*/
/****************************************************************/


// A macro wrapper
#define is_subclass(x, y) ( (bool) CheckInheritance<x,y>::result )

/* The CheckInheritance class works as follows: First off, let's begin
 * with static Testing MakeTesting(). The reason for this is simple.
 * We wish to call sizeof on a Testing. To do this, we could call
 * sizeof(Testing()). But we do not know if Testing has a default
 * constructor, so this could fail. However, since sizeof does not
 * evaluate (most) anything, we can call sizeof(MakeTesting()). sizeof
 * will notice that MakeTesting will return a Testing, and thus will
 * return the size of a Testing. Now, if Testing is a sub-class of
 * Super, then the function static IsConvertible Test( const Super& )
 * can be used as it takes in a super. The return value of this function
 * is an IsConvertible. In the enum below, we compare the sizeof an
 * IsConvertible to the size of the result of our Test function. Thus,
 * if Testing is a subclass of Super, they shall match and result will
 * equal one. If however Testing is not a subclass of Super, the first
 * Test function will fail. Do to SFINAE, this is not an error, and so
 * our second, ellipsis, Test function will be used. This returns a
 * NotConvertible. You will note below that we defined IsConvertible
 * and NotConvertible specifically to be two different sizes. Thus,
 * the sizes of will not match in the comparison in the enum, and
 * result will be false.
*/


// A class used to check to see if Testing is a subclass of Super
// This class makes the assumption that a class is its own subclass.
template <class Testing, class Super> class CheckInheritance {

	// Two different sized classes
	typedef char IsConvertible;
	class NotConvertible { char IsConvertible[64]; };

	// Two different test functions
	static IsConvertible Test( const Super & );
	static NotConvertible Test( ... );

	// Returns a Testing
	static Testing MakeTesting();
public:

	// Check to see if a Testing is a subclass of Super
	enum { result = ( sizeof( Test( MakeTesting() ) ) == sizeof(IsConvertible) ) };
};


/****************************************************************/
/*																*/
/*						  Test classes							*/
/*																*/
/****************************************************************/


// An extendable class
class Mammal {};

// A subclass of Mammal
class Human: public Mammal {};

// Not a subclass of Mammal
class Guitar {};


/****************************************************************/
/*																*/
/*						  Main function							*/
/*																*/
/****************************************************************/


// Main function
int main() {

	// Print booleans as strings
	std::cout << std::boolalpha;

	// Check to see if a human is a mammal
	std::cout << "It is " << is_subclass(Human, Mammal)
			<< " that a human is a mammal" << std::endl;

	// Check to see if a guitar is a mammal
	std::cout << "It is " << is_subclass(Guitar, Mammal)
			<< " that a guitar is a mammal" << std::endl;

	// Success
	return EXIT_SUCCESS;
}
