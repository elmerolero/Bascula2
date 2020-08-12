#ifndef TICKET_H
#define TICKET_H
#include <string>

struct TicketPendiente
{
	int folio;
	double pesoBruto;
	std::string numeroEconomico;
};

class Ticket
{
	public:
		// Folio
		void establecerFolio( int folio );
		int obtenerFolio() const;
		
		// Numero económico
		void establecerNumeroEconomico( std::string numeroEconomico );
		std::string obtenerNumeroEconomico() const;
		
		// Numero de placas
		void establecerNumeroPlacas( std::string numeroPlacas );
		std::string obtenerNumeroPlacas() const;
		
		// Tipo caja
		void establecerClaveTipoCaja( int claveTipoCaja );
		int obtenerClaveTipoCaja() const;
		
		void establecerNombreTipoCaja( std::string tipoCaja );
		std::string obtenerNombreTipoCaja() const;
		
		// Nombre del conductor
		void establecerNombreConductor( std::string nombreConductor );
		std::string obtenerNombreConductor() const;
		
		// Procedencia
		void establecerClaveProcedencia( int claveProcedencia );
		int obtenerClaveProcedencia() const;
		
		void establecerNombreProcedencia( std::string nombreProcedencia );
		std::string obtenerNombreProcedencia() const;
		
		// Zona
		void establecerZona( std::string zona );
		std::string obtenerZona() const;
		
		// Subzona
		void establecerSubzona( std::string subzona );
		std::string obtenerSubzona() const;
		
		// Departamento
		void establecerClaveDepartamento( int claveDepartamento );
		int obtenerClaveDepartamento() const;
		
		void establecerNombreDepartamento( std::string nombreDepartamento );
		std::string obtenerNombreDepartamento() const;
		
		// Peso bruto
		void establecerPesoBruto( double pesoBruto );
		double obtenerPesoBruto() const;
		
		// Peso tara
		void establecerPesoTara( double pesoTara );
		double obtenerPesoTara() const;
		
		// Peso neto
		void calcularPesoNeto();
		double obtenerPesoNeto() const;
	
	private:
		// Permite establecer el peso neto usando calcularPesoNeto
		void establecerPesoNeto( double pesoNeto );
		
		int folio;
		std::string numeroEconomico;
		std::string numeroPlacas;
		std::string nombreConductor;
		int claveTipoCaja;
		std::string nombreTipoCaja;
		int claveProcedencia;
		std::string nombreProcedencia;
		std::string zona;
		std::string subzona;
		int claveDepartamento;
		std::string nombreDepartamento;
		double pesoBruto;
		double pesoTara;
		double pesoNeto;
};

#endif
