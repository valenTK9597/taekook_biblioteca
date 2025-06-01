#ifndef MODULOUSUARIOS_H
#define MODULOUSUARIOS_H

#include "Usuario.h"
#include <string>

class ModuloUsuarios {
private:
    std::string rutaArchivoUsuarios;

public:
    // Constructor
    ModuloUsuarios(const std::string& ruta);

    // Métodos
    void registrarUsuario();
    Usuario* iniciarSesion();                       
    void editarPerfilUsuario(Usuario* usuario);
    
    //  para administrador
    void gestionarUsuariosAdministrador();
    void verUsuariosRegistrados();
    void eliminarUsuarioPorId();
    void editarUsuarioPorId();

};

#endif



