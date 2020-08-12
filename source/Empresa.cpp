#include "Empresa.h"
#include <string>
#include <stdexcept>
using namespace std;

// Constructor
Empresa::Empresa():
    codigoEmpresa( 0 )
{
    // Nada que hacer aquí
}

// Establece el código empresa
void Empresa::establecerCodigoEmpresa( int codigoEmpresa )
{
    if( codigoEmpresa < 0 ){
        throw invalid_argument( "Código de empresa no válido." );
    }
    this -> codigoEmpresa = codigoEmpresa;
}

// Obtiene el código de la empresa
int Empresa::obtenerCodigoEmpresa() const
{
    return codigoEmpresa;
}

// Establece la razón social de la empresa
void Empresa::establecerRazonSocial( std::string razonSocial )
{
    if( razonSocial.empty() ){
        throw invalid_argument( "No se ha registrado ninguna razón social." );
    }
    
    if( razonSocial.size() > 100 ){
        throw invalid_argument( "La razón social de la empresa excede el tamaño máximo (100 caracteres)." );
    }
    
    this -> razonSocial = razonSocial;
}

// Obtiene la razón social de la empresa
std::string Empresa::obtenerRazonSocial() const
{
    return razonSocial;
}

// Establece el teléfono de la empresa
void Empresa::establecerTelefono( std::string telefono, std::string extension )
{
    if( telefono.empty() ){
        throw invalid_argument( "No se ha registrado un número de teléfono." );
    }
    
    if( telefono.size() > 10 ){
        throw invalid_argument( "El número de teléfono es más largo de lo esperado (10 dígitos)." );
    }
    
    if( extension.size() > 6 ){
        throw invalid_argument( "El número de extensión es más largo de lo esperado (6 dígitos)." );
    }
    
    this -> telefono = telefono;
    this -> extension = extension;
}

std::string Empresa::obtenerTelefono() const
{
    return telefono;
}

std::string Empresa::obtenerExtension() const
{
    return extension;
}

// Establece el domicilio
void Empresa::establecerDomicilio( Domicilio domicilio )
{
    this -> domicilio = domicilio;
}

// Obtener el domicilio
Domicilio Empresa::obtenerDomicilio() const
{
    return domicilio;
}

