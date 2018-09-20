#include <iostream>


/****************************************************************/
/*																*/
/*							General								*/
/*																*/
/****************************************************************/


//Empty type
class NullType {};

//A container that converts an int to a distinct type, with a value
template<int N> struct intc { enum { value = N }; };


/****************************************************************/
/*																*/
/*							List								*/
/*																*/
/****************************************************************/


//Macro wrapper around List, V is the name of the variable defines
#define makeList(...) make_list<__VA_ARGS__>::result

//Macro wrapper around ListGet
#define get(T, N) ListGet<T,N>::result


//A list of types
template <class T, class U> struct List {
	typedef U Tail;
	typedef T Head;
	enum { size = Tail::size + 1 };
};
template <class T> struct List<T, NullType> {
	typedef NullType Tail;
	typedef T Head;
	enum { size = 1 };
};

//Make a list of types
template <class T, class... U> struct make_list {
	typedef List<T, typename make_list<U...>::result > result;
};
template <class T> struct make_list<T> {
	typedef List<T, NullType> result;
};

//Get the n'th item of the list
template <class T, int N> struct ListGet {
	typedef typename ListGet<typename T::Tail, N-1>::result result;
};
template <class T> struct ListGet<T, 0> {
	typedef typename T::Head result;
};


/****************************************************************/
/*																*/
/*						For Error Checking						*/
/*																*/
/****************************************************************/


#define CHECK_LEGAL(A, B) \
	static_assert(A::size > 0, "Error, invalid type passed in"); \
	static_assert(A::size == B::size, "Error, cannot take dot product " \
											"of different sized vectors");


/****************************************************************/
/*																*/
/*							Dot Product							*/
/*																*/
/****************************************************************/


//Dot product wrapper
#define dotProd(A, B) dotProd<A, B>::result


//Dot product
template <class A, class B> struct dotProd {

	//Check for errors
	CHECK_LEGAL(A, B);

	//Multiply the heads then recurse with the tails.
	enum { result =  A::Head::value * B::Head::value + dotProd<typename A::Tail, typename B::Tail>::result };
};

//Called when the end of the lists have been hit
template <> struct dotProd<NullType, NullType> { enum { result = 0 }; };


/****************************************************************/
/*																*/
/*						Vector Operations						*/
/*																*/
/****************************************************************/


//Wrapper around Add_vectors
#define AddVectors(A, B) Add_vectors<A,B>::result

//Add vectors together
template <class A, class B> struct Add_vectors {

	//Check for errors
	CHECK_LEGAL(A, B);

	//Add the vectors together
	typedef List< intc<A::Head::value + B::Head::value>,
		typename Add_vectors<typename A::Tail, typename B::Tail>::result > result;
};
template <> struct Add_vectors<NullType, NullType> {
	typedef NullType result;
};


/****************************************************************/
/*																*/
/*						Matrix Operations						*/
/*																*/
/****************************************************************/


//Wrap add matrices
#define AddMatrices(A, B) Add_matrices<A,B>::result

//Add two matrices
template <class A, class B> struct Add_matrices {

	//Check for errors
	CHECK_LEGAL(A, B);

	//Add the vectors
	typedef List< typename AddVectors(typename A::Head, typename B::Head),
		typename Add_matrices<typename A::Tail, typename B::Tail>::result > result;
};
template <> struct Add_matrices<NullType, NullType> {
	typedef NullType result;
};


/****************************************************************/
/*																*/
/*						For vector printing						*/
/*																*/
/****************************************************************/


//Print wrapper
#define pntV(V) {							\
	std::cout << #V << " = [ ";				\
	if (V::size) printVectorHelper<V>();	\
	std::cout << "]" << std::endl;			\
}


//Print a vector
template<class V> void printVectorHelper() {
	std::cout << get(V, 0)::value << (V::size > 1 ? ", ":" ");
	printVectorHelper<typename V::Tail>();
}

//Called when there is nothing left to print
template<> void printVectorHelper<NullType>() {}


/****************************************************************/
/*																*/
/*						For matrix printing						*/
/*																*/
/****************************************************************/


//Print wrapper
#define pntM(V) {							\
	std::cout << #V << ":\n";				\
	if (V::size) printMatrixHelper<V>();	\
	std::cout  << std::endl;				\
}

//Print a vector
template<class V> void printMatrixHelper() {
	std::cout << "  [ ";
	if (V::size) printVectorHelper<typename V::Head>();
	std::cout << "]" << std::endl;
	printMatrixHelper<typename V::Tail>();
}

//Called when there is nothing left to print
template<> void printMatrixHelper<NullType>() {}


/****************************************************************/
/*																*/
/*								Main 							*/
/*																*/
/****************************************************************/


//Main function
int main() {

	// One could even make this better by using a templated function to return a variable
	// In C++11 using hte using A = B syntax would also work!

	//Make matrix A
	typedef makeList(intc<1>, intc<2>, intc<3>) A1;
	typedef makeList(intc<4>, intc<5>, intc<6>) A2;
	typedef makeList(intc<7>, intc<8>, intc<9>) A3;
	typedef makeList(A1, A2, A3) A;

	//Make matrix B
	typedef makeList(intc<1>, intc<2>, intc<3>) B1;
	typedef makeList(intc<4>, intc<5>, intc<6>) B2;
	typedef makeList(intc<7>, intc<8>, intc<9>) B3;
	typedef makeList(B1, B2, B3) B;

	//Print A and B
	pntM(A); pntM(B);

	//Add the two matrices
	typedef AddMatrices(A, B) C;

	//Print C
	std::cout << "A + B:\n";
	pntM(C);

	//Success
	return 0;
}
