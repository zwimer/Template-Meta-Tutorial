/* Compiled with:
	g++ IsPointer.cpp -o IsPointer.out
*/

#include <iostream>

//Macro wrapper
#define isPtr(T) ((bool) IsPointer<T>::result)

//General template
template <class T> struct IsPointer{
	enum { result = false };
};
 
//Specified template. You will notice that this 
//still  takes in an argument T, but that the 
//specification is simply that T is a pointer!
template <class T> struct IsPointer<T*> {
	enum { result = true };
};



//Main function
int main() {

	//Setup
	std::cout << std::boolalpha;

	//Verify that int * is a pointer and that int is not
	std::cout << "It is " << isPtr(int) << " that int is a pointer.\n";
	std::cout << "It is " << isPtr(int *) << " that int * is a pointer.\n";

	//Success
	return 0;
}
