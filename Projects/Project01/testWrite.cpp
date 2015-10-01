#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]) {
	std::ofstream out("testWrite.txt");
	out << "Probando :D";
	out.close();
	return 0; 
}