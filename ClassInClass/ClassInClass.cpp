/* Compiled with:
	g++ ClassInClass.cpp -o ClassInClass.out
*/

#include <iostream>
#include <string>

//A class with a function that can print out 
//messages given to it by it's internal classes
class Printer {
private:

	//A class that has a function
	//that returns "Hello World!"
	class GetHi {
		public: std::string getHi() { return std::string("Hello World!"); }
	};

public:

	//Print "Hello World!"
	void pntMsg() {

		//Make a GetHi
		GetHi tmp;
	
		//Print "Hello World!"
		std::cout << tmp.getHi() << std::endl;
	}
};

//Main function
int main() {

	//Make a printer
	Printer p;

	//Print Hello World!
	p.pntMsg();

	//Success
	return 0;
}
