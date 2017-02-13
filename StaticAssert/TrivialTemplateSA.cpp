/* Compiled with:
	g++ TrivialTemplateSA.cpp -o TrivialTemplateSA.out
*/

//Declare the struct
template <bool> struct CompileTimeError;

//Define the struct for true
template <> struct CompileTimeError<true> {};

// Wrapper
#define STATIC_CHECK(A)	 CompileTimeError<A>()


//Main function
int main() {

	//Check to see if 1 + 1 == 20
	CompileTimeError< 1 + 1 == 20 >();

	//Success
	return 0;
}

