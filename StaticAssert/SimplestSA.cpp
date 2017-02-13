/* Compiled with
	g++ SimplestSA.cpp -pedantic -Wno-unused-variable -Werror -o SimplestSA.out
*/

//If A is false, char[0] is called, which is illegal
//If A is true, char[1] is called, then goes out of scope
#define STATIC_CHECK(A)  {		\
	char test[ (A) ? 1 : 0 ];	\
}

//Main function
int main() {

	//Test if 1 + 1 = 20
	STATIC_CHECK(1 + 1 == 20);

	//Success
	return 0;
}
