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
        
        void actualizarTicketsPendientes();
        void limpiarTicketsPendientes();
        const std::vector< TicketPendiente * > &obtenerTicketsPendientes() const;
                
        void establecerFolioTicketActual();
        Ticket *obtenerTicket();
        void cerrar();
        

    private:
        Usuario usuario;
        Empresa empresa;
        std::string fecha;
        std::vector< TicketPendiente * >ticketsPendientes;
        Ticket ticket;

        Widget *ventana;
        Widget *contenido;
        bool validarCadena( std::string cadena, std::regex expresion, size_t tamano );
};

#endif

