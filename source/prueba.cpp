#include <iostream>
#include <string>
using namespace std;


int main()
{
	double numero = 29862.239749;
	string strNumero = to_string( numero );
	size_t posicionPunto = strNumero.find( ',', 0 );

	if( posicionPunto == string::npos ){
		
		cout <<  << endl;
	}

	return 0;
}