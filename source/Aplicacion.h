#ifndef APLICACION_H
#define APLICACION_H
#include <vector>
#include <regex>
#include "Widget.h"
#include "Usuario.h"
#include "Empresa.h"
#include "Domicilio.h"
#include "Database.h"
#include "Ticket.h"

class Aplicacion
{
    public:
        Aplicacion();
        int iniciar();
        void establecerFecha( std::string fecha );
        std::string obtenerFecha() const;
        Widget *obtenerWidget() const;
        void establecerVistaContenido( std::string archivo );
        Widget *obtenerVistaContenido() const;
        
        // Ticket
        void establecerFolioTicketActual();
        Ticket *obtenerTicket();
        void cerrar();

        // Registro de tickets pendientes
        void actualizarTicketsPendientes();
        const std::vector< Ticket* > &obtenerTicketsPendientes() const;
        void limpiarTicketsPendientes();
                
        // Registro de procedencias
        void actualizarRegistrosProcedencias();
        const std::vector< Registro * > &obtenerRegistrosProcedencias() const;
        void limpiarRegistrosProcedencias();

        // Registro de departamentos
        void actualizarRegistrosDepartamentos();
        const std::vector< Registro * > &obtenerRegistrosDepartamentos() const;
        void limpiarRegistrosDepartamentos();

        // Registro de departamentos
        void actualizarRegistrosTiposCaja();
        const std::vector< Registro * > &obtenerRegistrosTiposCaja() const;
        void limpiarRegistrosTiposCaja();

    private:
        Usuario usuario;
        Empresa empresa;
        std::string fecha;
        std::vector< Ticket * >ticketsPendientes;
        std::vector< Registro * >registrosProcedencias;
        std::vector< Registro * >registrosDepartamentos;
        std::vector< Registro * >registrosTiposCaja;
        Ticket ticket;

        Widget *ventana;
        Widget *contenido;
        bool validarCadena( std::string cadena, std::regex expresion, size_t tamano );
        void limpiarRegistros( std::vector< Registro * > &registros );
};

#endif

