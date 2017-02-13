/* Compile with
	g++ BestSA.cpp -o BestSA.out
*/

//'Catch all' constructor, can take in ANY type
template <bool> struct CompileTimeChecker {
	CompileTimeChecker(...);
};

//Specialize definition for when bool = false
//There is no constructor here! Calling it illegal
template <> struct CompileTimeChecker<false> {};

// Macro Wrapper
#define STATIC_CHECK(A, msg) {	 					\
	class ERROR_##msg;								\
	(void) sizeof(CompileTimeChecker<(A) != 0>((ERROR_##msg())));	\
}


//Main function
int main() {

	//Test if 1 + 1 = 20
	STATIC_CHECK(1 + 1 == 20, Math_Works);

	//Success
	return 0;
}
