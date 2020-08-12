#include "Domicilio.h"
#include <string>
#include <stdexcept>
using namespace std;

// Constructor
Domicilio::Domicilio():
    numero( 0 ), numeroInterior( 0 )
{
    // Nada por hacer aquí
}

// Constructor con parámetros
Domicilio::Domicilio( std::string calle, int numero, int numeroInterior, std::string colonia, int codigoPostal, std::string municipio, std::string estado, std::string pais )
{
    establecerCalle( calle );
    establecerNumero( numero );
    establecerNumeroInterior( numeroInterior );
    establecerColonia( colonia );
    establecerCodigoPostal( codigoPostal );
    establecerMunicipio( municipio );
    establecerEstado( estado );
    establecerPais( pais );
}

// Establece el nombre de la calle
void Domicilio::establecerCalle( string calle )
{
    if( calle.empty() ){
        throw invalid_argument( "Es necesario indicar la calle de la empresa." );
    }
    
    if( calle.size() > 100 ){
        throw invalid_argument( "El nombre de la calle excede la longitud máxima (100 caracteres)." );
    }
    this -> calle = calle;
}

// Obtine el nombre de la calle
string Domicilio::obtenerCalle() const
{
    return calle;
}

// Establece el número
void Domicilio::establecerNumero( int numero )
{
    if( numero < 0 ){
        throw invalid_argument( "Introduzca un numero válido." );
    }
    
    this -> numero = numero;
}

// Obtiene el número
int Domicilio::obtenerNumero() const
{
    return numero;
}

// Establece el número interior
void Domicilio::establecerNumeroInterior( int numeroInterior )
{
    if( numeroInterior < -1 ){
        throw invalid_argument( "Introduzca un numero interior válido." );
    }
    this -> numeroInterior = numeroInterior;
}

// Obtiene el número interior
int Domicilio::obtenerNumeroInterior() const
{
    return numeroInterior;
}

// Establece la colonia en la que se encuentre la entidad
void Domicilio::establecerColonia( string colonia )
{
    if( colonia.empty() ){
        throw invalid_argument( "Es necesario indicar la colania en la que se\nencuentra la empresa." );
    }
    
    if( colonia.size() > 100 ){
        throw invalid_argument( "El nombre de la colonia la longitud máxima (100 caracteres)." );
    }
    
    this -> colonia = colonia;
}

// Obtiene la colonia
string Domicilio::obtenerColonia() const
{
    return colonia;
}

//Establece el código postal
void Domicilio::establecerCodigoPostal( int codigoPostal )
{
    if( codigoPostal < 0 ){
        throw invalid_argument( "Introduzca un código postal válido." );
    }
    
    this -> codigoPostal = codigoPostal;
}

// Obtiene el código postal
int Domicilio::obtenerCodigoPostal() const
{
    return codigoPostal;
}

// Establece el municipio
void Domicilio::establecerMunicipio( string municipio )
{
    if( calle.empty() ){
        throw invalid_argument( "Es necesario indicar el municipio en\nel que se encuentra la empresa." );
    }
    
    if( calle.size() > 100 ){
        throw invalid_argument( "El nombre del municipio excede la longitud máxima (100 caracteres)." );
    }
    
    this -> municipio = municipio;
}

// Obtiene el municipio
string Domicilio::obtenerMunicipio() const
{
    return municipio;
}

// Establece el estado
void Domicilio::establecerEstado( string estado )
{
    if( calle.empty() ){
        throw invalid_argument( "Es necesario indicar el estado en\nel que se encuentra la empresa." );
    }
    
    if( calle.size() > 100 ){
        throw invalid_argument( "El nombre del estado excede la longitud máxima (100 caracteres)." );
    }
    
    this -> estado = estado;
}

// Obtener estado
string Domicilio::obtenerEstado() const
{
    return estado;
}

// Establece el país
void Domicilio::establecerPais( string pais )
{
    if( calle.empty() ){
        throw invalid_argument( "Es necesario indicar el país de la empresa." );
    }
    
    if( calle.size() > 100 ){
        throw invalid_argument( "El nombre del país excede la longitud máxima (100 caracteres)." );
    }
    
    this -> pais = pais;
}

// Obtiene el país
string Domicilio::obtenerPais() const
{
    return pais;
}

// Obtiene el domicilio en formato string
string Domicilio::obtenerDomicilio() const
{
    // String a devolver
    string domicilio;

    // Concatena la calle,
    domicilio = calle + " " + to_string( obtenerNumero() );

    // el número interior (si es distinto de cero)
    if( numeroInterior != 0 ){
        domicilio = domicilio + " " + to_string( obtenerNumeroInterior() );
    }

    // la colonia,
    domicilio = domicilio + ',' + ' ' + obtenerColonia();
    
    // el código postal,
    domicilio = domicilio + " " + to_string( obtenerCodigoPostal() );

    // el municipio,
    domicilio = domicilio + ", " + obtenerMunicipio();
    
    // el estado,
    domicilio = domicilio + " " + obtenerEstado();

    // y el país
    domicilio = domicilio + ", " + obtenerPais();

    return domicilio;
}

