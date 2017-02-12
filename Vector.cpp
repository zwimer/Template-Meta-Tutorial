#include <iostream>


/****************************************************************/
/*																*/
/*							General								*/
/*																*/
/****************************************************************/


//Empty type
class NullType {};


/****************************************************************/
/*																*/
/*							intList								*/
/*																*/
/****************************************************************/


//Macro wrapper around intList, V is the name of the variable defines
#define makeIntList(V, ...) typedef intList<__VA_ARGS__> V

//Macro wrapper around intListGet
#define get(T, N) intListGet<T,N>::result


//A vector of numbers
template <int T, int... U> struct intList {
	typedef intList<U...> Tail;
	enum { Head = T, size = Tail::size + 1 };
};
template <int T> struct intList<T> {
	typedef NullType Tail;
	enum { Head = T, size = 1 };
};


//Get the n'th item of the list
template <class T, int N> struct intListGet {
	enum { result = intListGet<typename T::Tail, N-1>::result };
};
template <class T> struct intListGet<T, 0> {
	enum { result = T::Head };
};


/****************************************************************/
/*																*/
/*							Dot Product							*/
/*																*/
/****************************************************************/


//Dot product wrapper
#define dotProd(A, B) intDotProd<A, B>::result


//Dot product
template <class T1, class T2> struct intDotProd {

	//Check for errors
	static_assert(T1::size > 0, "Error, invalid type passed in");
	static_assert(T1::size == T2::size, "Error, cannot take dot product "
											"of different sized vectors");

	//Multiply the heads then recurse with the tails.
	enum { result =  T1::Head * T2::Head + intDotProd<typename T1::Tail, typename T2::Tail>::result }; 
};

//Called when the end of the lists have been hit
template <> struct intDotProd<NullType, NullType> { enum { result = 0 }; };


/****************************************************************/
/*																*/
/*							For printing						*/
/*																*/
/****************************************************************/


//Print wrapper
#define pnt(V) {							\
	std::cout << #V << " = [ ";				\
	if (V::size) printVectorHelper<V>();	\
	std::cout << "]" << std::endl;			\
}


//Print a vector
template<class V> void printVectorHelper() {
	std::cout << get(V, 0) << (V::size > 1 ? ", ":" ");
	printVectorHelper<typename V::Tail>();
}

//Called when there is nothing left to print
template<> void printVectorHelper<NullType>() {}


/****************************************************************/
/*																*/
/*								Main 							*/
/*																*/
/****************************************************************/


//Main function
int main() {

	//Initial vectors
	makeIntList(A, 1, 2, 3, 4, 5, 6);
	makeIntList(B, 6, 5, 4, 3, 2, 1);

	//Print the maticies
	pnt(A); pnt(B);

	//Dot product
	std::cout << "\nA • B = " << dotProd(A, B) << std::endl;

	//Success
	return 0;
}
