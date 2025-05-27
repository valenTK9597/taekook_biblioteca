#ifndef USUARIOFACTORY_H
#define USUARIOFACTORY_H

#include "Usuario.h"
#include <vector>

class UsuarioFactory {
public:
    static Usuario* crearUsuario(const std::string& tipo, const std::string& id,
                                 const std::string& nombre, const std::string& correo,
                                 const std::string& contrasena);

    static void guardarUsuarioEnArchivo(Usuario* usuario, const std::string& rutaArchivo);
    static std::vector<Usuario*> cargarUsuariosDesdeArchivo(const std::string& rutaArchivo);
    static bool correoExistente(const std::string& correo, const std::string& rutaArchivo);
    static Usuario* obtenerUsuarioPorId(const std::string& id, const std::string& rutaArchivo);

};

#endif
