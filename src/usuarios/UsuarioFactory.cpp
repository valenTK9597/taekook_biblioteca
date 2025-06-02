#include "../../include/usuarios/UsuarioFactory.h"
#include "../../include/usuarios/Estudiante.h"
#include "../../include/usuarios/Profesor.h"
#include "../../include/usuarios/Administrador.h"
#include <algorithm> 

Usuario* UsuarioFactory::crearUsuario(const std::string& tipo, const std::string& id, const std::string& nombre,
                                      const std::string& correo, const std::string& contrasena) {
    if (tipo == "Estudiante") {
        return new Estudiante(id, nombre, correo, contrasena);
    } else if (tipo == "Profesor") {
        return new Profesor(id, nombre, correo, contrasena);
    } else if (tipo == "Administrador") {
        return new Administrador(id, nombre, correo, contrasena);
    } else {
        return nullptr;
    }
}

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip> // std::quoted

// Guardar usuario en archivo
void UsuarioFactory::guardarUsuarioEnArchivo(Usuario* usuario, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo, std::ios::app);
    if (archivo.is_open()) {
        archivo << usuario->getId() << "|"
                << usuario->getNombre() << "|"
                << usuario->getCorreo() << "|"
                << usuario->getContrasena() << "|"
                << usuario->getTipo() << "\n";
        archivo.close();
    } else {
        std::cerr << "⚠️ No se pudo abrir el archivo para guardar el usuario.\n";
    }
}

// Cargar usuarios desde archivo
std::vector<Usuario*> UsuarioFactory::cargarUsuariosDesdeArchivo(const std::string& rutaArchivo) {
    std::vector<Usuario*> usuarios;
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, correo, contrasena, tipo;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, contrasena, '|');
        std::getline(ss, tipo, '|');

        Usuario* nuevo = crearUsuario(tipo, id, nombre, correo, contrasena);
        if (nuevo) usuarios.push_back(nuevo);
    }

    archivo.close();
    return usuarios;
}

// Verificar si correo ya existe
bool UsuarioFactory::correoExistente(const std::string& correo, const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, correoLeido;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correoLeido, '|');

        if (correoLeido == correo) {
            return true;
        }
    }

    return false;
}

Usuario* UsuarioFactory::obtenerUsuarioPorId(const std::string& id, const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string idArchivo, nombre, correo, contrasena, tipo;

        std::getline(ss, idArchivo, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, contrasena, '|');
        std::getline(ss, tipo, '|');

        // Limpieza de espacios por si los hay
        idArchivo.erase(std::remove_if(idArchivo.begin(), idArchivo.end(), ::isspace), idArchivo.end());
        std::string idBuscado = id;
        idBuscado.erase(std::remove_if(idBuscado.begin(), idBuscado.end(), ::isspace), idBuscado.end());

        if (idArchivo == idBuscado) {
            return crearUsuario(tipo, idArchivo, nombre, correo, contrasena);
        }
    }

    return nullptr;
}


