/* Compiled with
	g++ Select.cpp -O3 -o Select.out
*/

#include <iostream>

//Converts an int to a type
template<int N> struct Int2Type { enum { value = N }; };


//If B is true (general case), then result = T
template<bool B, class T, class U> struct Select {
	typedef T result;
};

//If B is false, then result = U
//Since this is specialized, it takes priority over the general case
template<class T, class U> struct Select<false, T, U> {
	typedef U result;
};


//Main function
int main() {

	//Determine what to print
	const bool flag = true;

	//Set Num to Int2Type<100> if flag = true, Int2Type<0> if false
	typedef Select< flag, Int2Type<100>, Int2Type<0> >::result Num;

	//Print the result
	std::cout << "Flag = " << std::boolalpha << flag
				<< ", thus Num::value = " << Num::value << std::endl;

	//Success
	return 0;
}
