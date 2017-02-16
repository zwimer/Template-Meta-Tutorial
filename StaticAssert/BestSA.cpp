/* Compile with
	clang++ BestSA.cpp -o BestSA.out -std=c++14

	Why Clang?
	- Clang gives nicer error messages than g++ for this
*/

//'Catch all' constructor, can take in ANY type
template <bool> struct CompileTimeChecker {
	CompileTimeChecker(...);
};

//Specialize definition for when bool = false
//There is no (non-implicit) constructor here! Calling it illegal
template <> struct CompileTimeChecker<false> {};

// Macro Wrapper
#define STATIC_CHECK(A, msg) {	 								\
	class ERROR_##msg{};										\
	(void) sizeof( CompileTimeChecker<A>{ ERROR_##msg() } );	\
}

/* How it works:
 *	
 * STATIC_CHECK wrapes everything in a new scope { }
 * It then declares a class called ERROR_ prepended by msg
 * If A is true, sizeof returns the size of CompileTimeChecker<true>,
 *   as the catch all constructor accepts the ERROR_##msg class.
 * If A is false, sizeof attempts to find the return type of
 * the CompileTimeChecker<false> that accepts ERROR_##msg as an
 * argument. Since this constructor however is not defined,
 * The compiler will throw an error about how it cannot find
 * a matching constructor. With any luck, it will complain about
 * CompileTimeChecker not having a matching constructor for ERROR_##msg 
 */

//Main function
int main() {

	//Test if 1 + 1 = 20
	STATIC_CHECK(1 + 1 == 20, Math_Works);

	//Success
	return 0;
}
