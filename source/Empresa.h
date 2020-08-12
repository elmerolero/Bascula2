#ifndef EMPRESA_H
#define EMPRESA_H
#include <string>
#include "Domicilio.h"

class Empresa
{
    public:
        Empresa();
        
        /* Manipuladores de acceso */
        // Codigo empresa
        void establecerCodigoEmpresa( int codigoEmpresa );
        int obtenerCodigoEmpresa() const;

        // Razón social
        void establecerRazonSocial( std::string razonSocial );
        std::string obtenerRazonSocial() const;
        
        // Teléfono
        void establecerTelefono( std::string telefono, std::string extension );
        std::string obtenerTelefono() const;
        std::string obtenerExtension() const;

        // Domicilio
        void establecerDomicilio( Domicilio domicilio );
        Domicilio obtenerDomicilio() const;
    
    private:
        int codigoEmpresa;
        std::string razonSocial;
        std::string telefono;
        std::string extension;
        Domicilio domicilio;
};

#endif

