#include "Ticket.h"
#include <stdexcept>
#include <cmath>
using namespace std;

// Establece el folio del ticket
void Ticket::establecerFolio( int folio )
{
	if( folio < 1 ){
		throw invalid_argument( "Ah ocurrido un error estableciendo el folio del ticket." );
	}
	
	this -> folio = folio;
}

// Obtiene el folio del ticket
int Ticket::obtenerFolio() const
{
	return folio;
}

// Establece el numero del camion
void Ticket::establecerNumeroEconomico( string numeroEconomico )
{
	if( numeroEconomico.empty() ){
		throw invalid_argument( "Debe introducir un código de económico." );
	}
	
	if( numeroEconomico.size() > 10 ){
		throw invalid_argument( "El número económico no debe superar los 10 caracteres." );
	}
	
	this -> numeroEconomico = numeroEconomico;
}

// Obtiene el numero del camión
string Ticket::obtenerNumeroEconomico() const
{
	return numeroEconomico;
}

// Establece el numero de placas
void Ticket::establecerNumeroPlacas( std::string numeroPlacas )
{
	if( numeroPlacas.empty() ){
		throw invalid_argument( "Debe introducir el número de las placas del vehículo." );
	}
	
	if( numeroPlacas.size() > 7 ){
		throw invalid_argument( "El número de placa es muy largo." );
	}
	
	this -> numeroPlacas = numeroPlacas;
}

// Obtiene el numero de placas
string Ticket::obtenerNumeroPlacas() const
{
	return numeroPlacas;
}

// Establece el nombre del conductor
void Ticket::establecerNombreConductor( string nombreConductor )
{
	if( nombreConductor.empty() ){
		throw invalid_argument( "Debe introducir el nombre del conductor." );
	}

	if( nombreConductor.size() > 100 ){
		throw invalid_argument( "El nombre introducido es demasiado largo." );
	}
	
	this -> nombreConductor = nombreConductor;
}

// Obtiene el nombre del conductor
string Ticket::obtenerNombreConductor() const
{
	return nombreConductor;
}

// Establece la clave del tipo de caja
void Ticket::establecerClaveTipoCaja( int claveTipoCaja )
{
	// Es una clave positiva
	if( claveTipoCaja < 0 ){
		throw invalid_argument( "Se ha introducido una clave inválida." );
	}
	
	this -> claveTipoCaja = claveTipoCaja;
}

// Obtiene la clave del tipo de caja
int Ticket::obtenerClaveTipoCaja() const
{
	return claveTipoCaja;
}

// Establece el nombre del tipo de caja
void Ticket::establecerNombreTipoCaja( string nombreTipoCaja )
{
	if( nombreTipoCaja.empty() ){
		throw invalid_argument( "Debe introducir un tipo de caja existente." );
	}
	
	this -> nombreTipoCaja = nombreTipoCaja;
}

// Obtiene el nombre del tipo de caja
string Ticket::obtenerNombreTipoCaja() const
{
	return nombreTipoCaja;
}

// Establece la clave de la procedencia
void Ticket::establecerClaveProcedencia( int claveProcedencia )
{
	// Es una clave entera positiva
	if( claveProcedencia < 0 ){
		throw invalid_argument( "Debe introducir una clave\nde procedencia válida." );
	}
	
	this -> claveProcedencia = claveProcedencia;
}

// Obtiene la clave de procedencia
int Ticket::obtenerClaveProcedencia() const
{
	return claveProcedencia;
}

// Establece el nombre de procedencia
void Ticket::establecerNombreProcedencia( std::string nombreProcedencia )
{
	if( nombreProcedencia.empty() ){
		throw invalid_argument( "No esta siendo establecido ningún nombre de procedencia." );
	}
	
	this -> nombreProcedencia = nombreProcedencia;
}

// Obtiene el nombre de procedencia
std::string Ticket::obtenerNombreProcedencia() const
{
	return nombreProcedencia;
}

// Establece una zona
void Ticket::establecerZona( std::string zona )
{
	if( zona.size() > 100 ){
		throw invalid_argument( "El nombre de la zona especificado excede la cantidad de caracteres máximo (100)." );
	}
	
	this -> zona = zona;
}

// Obtiene una zona
std::string Ticket::obtenerZona() const
{
	return zona;
}

// Establece una zona
void Ticket::establecerSubzona( std::string subzona )
{
	if( subzona.size() > 100 ){
		throw invalid_argument( "El nombre de la subzona especificado excede la cantidad de caracteres máximo (100)." );
	}
	
	this -> subzona = subzona;
}

// Obtiene una zona
std::string Ticket::obtenerSubzona() const
{
	return subzona;
}

// Establece la clave del departamento
void Ticket::establecerClaveDepartamento( int claveDepartamento )
{
	if( claveDepartamento < 0 ){
		throw invalid_argument( "Clave de departamento no válida." );
	}
	
	this -> claveDepartamento = claveDepartamento;
}

// Obtiene la clave del departamento
int Ticket::obtenerClaveDepartamento() const
{
	return claveDepartamento;
}

// Establece el nombre del departamento
void Ticket::establecerNombreDepartamento( std::string nombreDepartamento )
{
	this -> nombreDepartamento = nombreDepartamento;
}

// Obtiene el nombre del departamento
std::string Ticket::obtenerNombreDepartamento() const
{
	return nombreDepartamento;
}

// Establece el peso bruto del ticket
void Ticket::establecerPesoBruto( double pesoBruto )
{
	if( pesoBruto < 0 ){
		throw invalid_argument( "Mala lectura de la báscula,\ninténtalo de nuevo." );
	}

	this -> pesoBruto = pesoBruto;
}

// Obtiene el peso bruto del ticket
double Ticket::obtenerPesoBruto() const
{
	return pesoBruto;
}

// Establece el peso tara del ticket
void Ticket::establecerPesoTara( double pesoTara )
{
	if( pesoBruto < 0 ){
		throw invalid_argument( "Mala lectura de la báscula,\ninténtalo de nuevo." );
	}

	this -> pesoTara = pesoTara;
}

// Obtiene el peso tara del ticket
double Ticket::obtenerPesoTara() const
{
	return pesoTara;
}

// Calcula el peso neto
void Ticket::calcularPesoNeto()
{
	establecerPesoNeto( abs( obtenerPesoBruto() - obtenerPesoTara() ) );
}

// Establece el peso bruto del ticket
void Ticket::establecerPesoNeto( double pesoNeto )
{
	if( pesoBruto < 0 ){
		throw invalid_argument( "El peso neto debe ser un valor absoluto positivo." );
	}

	this -> pesoNeto = pesoNeto;
}

// Obtiene el peso bruto del ticket
double Ticket::obtenerPesoNeto() const
{
	return pesoNeto;
}
