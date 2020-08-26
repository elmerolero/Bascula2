#ifndef TICKET_H
#define TICKET_H
#include <string>

struct Registro
{
	int clave;
	std::string nombre;
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

		// El ticket se encuentra pendiente (verdad) o finalizado
		void establecerPendiente( bool pendiente );
		bool estaPendiente() const;

		// Permite establece la fecha de registro del ticket
		void establecerFecha( std::string fecha );
		std::string obtenerFecha() const;

		// Permite  establecer la hora de entrada
		void establecerHoraEntrada( std::string horaEntrada );
		std::string obtenerHoraEntrada() const;

		// Permite establecer la hora de salida
		void establecerHoraSalida( std::string horaSalida );
		std::string obtenerHoraSalida() const;

		// Imprime los datos del ticket
		void imprimir() const;
	
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
		std::string fechaRegistro;
		std::string horaEntrada;
		std::string horaSalida;
		bool pendiente;
};

#endif
