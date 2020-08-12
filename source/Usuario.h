#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <gtk/gtk.h>
#include "Widget.h"

class Usuario
{
    public:
        Usuario();
        ~Usuario();

        /* Modificadores de acceso */
        // Nombre de usuario
        void establecerUsuario( std::string nombreUsuario );
        std::string obtenerUsuario() const;

        // Nombre de la persona
        void establecerNombre( std::string nombre );
        std::string obtenerNombre() const;

        // Apellidos
        void establecerApellidos( std::string apellidos );
        std::string obtenerApellidos() const;

        // Permisos de administrador
        void establecerAdministrador( bool permiso );
        bool esAdministrador() const;
        
        // Interfaz del usuario
        void cargarInterfaz( std::string archivo );
        const Widget *obtenerInterfaz() const;

    private:
        /* Campos del usuario */
        std::string nombreUsuario;
        std::string nombre;
        std::string apellidos;
        bool administrador;
        
        /* Interfaz del usuario */
        Widget interfaz;
};

#endif

