#include "Usuario.h"
#include <string>
#include <stdexcept>
using namespace std;

// Constructor
Usuario::Usuario():
    administrador( false )
{
    // Nada que hacer
}

// Destructor
Usuario::~Usuario()
{
    
}

// Establece el nombre del usuario
void Usuario::establecerUsuario( string nombreUsuario )
{
    this -> nombreUsuario = nombreUsuario;
}

// Obtiene el nombre del usuario
string Usuario::obtenerUsuario() const
{
    return nombreUsuario;
}

// Establece el nombre real del usuario
void Usuario::establecerNombre( string nombre )
{
    this -> nombre = nombre;
    
    // Actualiza el nombre de la interfaz
    interfaz.establecerTextoEtiqueta( "Nombre", this -> nombre );
}

// Obtiene el nombre real del usuario
string Usuario::obtenerNombre() const
{
    return nombre;
}

// Establece los apellidos del usuario
void Usuario::establecerApellidos( string apellidos )
{
    this -> apellidos = apellidos;
    
    // Actualiza el el apellido en la interfaz
    interfaz.establecerTextoEtiqueta( "Apellidos", this -> apellidos );
}

// Obtiene los apellidos del usuario
string Usuario::obtenerApellidos() const
{
    return apellidos;
}

// Establece los permisos de administrador
void Usuario::establecerAdministrador( bool permiso )
{
    this -> administrador = permiso;
}

// Revisa si el usuario tiene permisos de administrador
bool Usuario::esAdministrador() const
{
    return administrador;
}

// Carga una interfaz desde el archivo indicado
void Usuario::cargarInterfaz( string archivo )
{
    interfaz.cargarWidget( archivo );
}

// Obtiene el apuntador hacia la interfaz del usuario
const Widget *Usuario::obtenerInterfaz() const
{
    return &interfaz;
}
