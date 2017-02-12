#include <iostream>


/****************************************************************/
/*																*/
/*							General								*/
/*																*/
/****************************************************************/


//Empty type
class NullType {};

//A container that converts an int to a distinct type, with a value
template<int N> struct intc { 
	enum { value = N };
	
	//For printing
	static void print() { std::cout << value; }
};

//Checks to see if two types are the same
template <class A, class B> struct SameType {
	static const bool result = false;
};
template <class A> struct SameType<A, A> {
	static const bool result = true;
};

//A TMP version of an if statement
//Result = A if C, otherwise result = B
template<bool C, class A, class B> struct Select {
	typedef A result;	
};
template<class A, class B> struct Select<false, A, B> {
	typedef B result;
};

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

//Add list B to list A
template <class A, class B> struct AddList {
	typedef List<typename A::Head, typename AddList<typename A::Tail, B>::result > result;
};
template <class A> struct AddList<A, NullType> {
	typedef A result;
};
template <class B> struct AddList<NullType, B> {
	typedef B result;
};

//Determiens if item A exists in list L
template <class A, class L> struct ItemExists {
	static const bool result = SameType<A, typename L::Head>::result || ItemExists<A, typename L::Tail>::result;
};
template<class A> struct ItemExists<A, NullType> {
	static const bool result = false;
};

//Remove duplicates
template <class L> class RemoveDuplicates {
	typedef typename RemoveDuplicates<typename L::Tail>::result NewT;
public:
	typedef typename Select<ItemExists< typename L::Head, typename L::Tail>::result, 
						NewT, List<typename L::Head, NewT>
						>::result result;
};
template <> class RemoveDuplicates<NullType> {
public: typedef NullType result;
};



/****************************************************************/
/*																*/
/*							Power Set							*/
/*																*/
/****************************************************************/


#define PowerSet(A) make_power_set<A>::result

//A struct representing an empty set
struct EmptySet {
	static void print() { std::cout << "{}"; }
};

//Prepend P to sublists of L
template<class P, class L> struct PrependToSublists {
	typedef List<List<P, typename L::Head>, typename PrependToSublists<P, typename L::Tail>::result > result;
};
template<class P> struct PrependToSublists<P, NullType> {
	typedef NullType result;
};

//Make the power set of T
template<class T> class make_power_set {
	typedef typename make_power_set<typename T::Tail>::result SubPower;
public:
	typedef typename RemoveDuplicates<
			typename AddList<
				typename PrependToSublists<typename T::Head, SubPower>::result,
				SubPower
			>::result
		>::result result;
};
template <> class make_power_set<NullType> {
	public:	typedef List<List<EmptySet, NullType>, NullType> result;
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
	get(V, 0)::print(); std::cout << (V::size > 1 ? ", ":" ");
	printVectorHelper<typename V::Tail>();
}

//Called when there is nothing left to print
template<> void printVectorHelper<NullType>() {}


/****************************************************************/
/*																*/
/*						For PowerSet printing					*/
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

	//Make list A
	typedef makeList(
		intc<1>, intc<2>, intc<3>, intc<4>,
		intc<5>, intc<6>, intc<7>, intc<8>,
		intc<9>, intc<10>, intc<11>, intc<12>
) A;
//		intc<13>, intc<14>, intc<15>, intc<16>,

	//Make the power set of A
	typedef PowerSet(A) B;

	//Print the power set
	pntM(B);

	//Success
	return 0;
}
