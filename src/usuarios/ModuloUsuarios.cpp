#include "../../include/usuarios/ModuloUsuarios.h"
#include "../../include/usuarios/UsuarioFactory.h"
#include "../../include/usuarios/Estudiante.h"
#include "../../include/usuarios/Profesor.h"
#include "../../include/usuarios/Administrador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

// Constructor
ModuloUsuarios::ModuloUsuarios(const std::string& ruta) : rutaArchivoUsuarios(ruta) {}

// Método para registrar usuario
void ModuloUsuarios::registrarUsuario() {
    std::string tipo, id, nombre, correo, contrasena;

    std::cout << "\n📋 Registro de nuevo usuario\n";
    std::cout << "Tipo (Estudiante / Profesor / Administrador): ";
    std::cin >> tipo;

    std::cout << "ID: ";
    std::cin >> id;
    std::cout << "Nombre: ";
    std::cin >> nombre;
    std::cout << "Correo: ";
    std::cin >> correo;

    if (UsuarioFactory::correoExistente(correo, rutaArchivoUsuarios)) {
        std::cout << " Ya existe un usuario con ese correo.\n";
        return;
    }

    std::cout << "Contrasena: ";
    std::cin >> contrasena;

    Usuario* nuevo = UsuarioFactory::crearUsuario(tipo, id, nombre, correo, contrasena);
    if (!nuevo) {
        std::cout << " Tipo de usuario invalido.\n";
        return;
    }

    UsuarioFactory::guardarUsuarioEnArchivo(nuevo, rutaArchivoUsuarios);
    std::cout << " Usuario registrado exitosamente.\n";
    delete nuevo;
}

// Método para iniciar sesión
Usuario* ModuloUsuarios::iniciarSesion() {
    std::vector<Usuario*> usuarios = UsuarioFactory::cargarUsuariosDesdeArchivo(rutaArchivoUsuarios);

    if (usuarios.empty()) {
        std::cout << " No hay usuarios registrados.\n";
        return nullptr;
    }

    std::string correo, contrasena;
    std::cout << "\n Iniciar sesion\nCorreo: ";
    std::cin >> correo;
    std::cout << "Contrasena: ";
    std::cin >> contrasena;

    for (Usuario* u : usuarios) {
        if (u->getCorreo() == correo && u->getContrasena() == contrasena) {
            Usuario* copia = UsuarioFactory::crearUsuario(u->getTipo(), u->getId(), u->getNombre(), u->getCorreo(), u->getContrasena());
            for (Usuario* temp : usuarios) delete temp;
            return copia;
        }
    }

    std::cout << " Usuario o contrasena incorrectos.\n";
    for (Usuario* u : usuarios) delete u;
    return nullptr;
}

// Método para editar datos del usuario
void ModuloUsuarios::editarPerfilUsuario(Usuario* usuario) {
    int opcion;
    std::cout << "\n Editar perfil de usuario:\n";
    std::cout << "1. Cambiar nombre\n";
    std::cout << "2. Cambiar correo\n";
    std::cout << "3. Cambiar contraseña\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

    std::string nuevoValor;
    switch (opcion) {
        case 1:
            std::cout << "Nuevo nombre: ";
            std::getline(std::cin, nuevoValor);
            usuario->setNombre(nuevoValor);
            break;
        case 2:
            std::cout << "Nuevo correo: ";
            std::getline(std::cin, nuevoValor);
            usuario->setCorreo(nuevoValor);
            break;
        case 3:
            std::cout << "Nueva contrasena: ";
            std::getline(std::cin, nuevoValor);
            usuario->setContrasena(nuevoValor);
            break;
        default:
            std::cout << " Opcion no valida.\n";
            return;
    }

    // Actualizar en archivo
    std::ifstream archivoIn(rutaArchivoUsuarios);
    std::ofstream archivoOut("data/temp_usuarios.txt");
    std::string linea;

    while (getline(archivoIn, linea)) {
        std::stringstream ss(linea);
        std::string idLeido, nombre, correo, contrasena, tipo;
        getline(ss, idLeido, '|');
        getline(ss, nombre, '|');
        getline(ss, correo, '|');
        getline(ss, contrasena, '|');
        getline(ss, tipo, '|');

        if (idLeido == usuario->getId()) {
            archivoOut << usuario->getId() << "|"
                       << usuario->getNombre() << "|"
                       << usuario->getCorreo() << "|"
                       << usuario->getContrasena() << "|"
                       << usuario->getTipo() << "\n";
        } else {
            archivoOut << idLeido << "|"
                       << nombre << "|"
                       << correo << "|"
                       << contrasena << "|"
                       << tipo << "\n";
        }
    }

    archivoIn.close();
    archivoOut.close();
    std::remove(rutaArchivoUsuarios.c_str());
    std::rename("data/temp_usuarios.txt", rutaArchivoUsuarios.c_str());

    std::cout << " Perfil actualizado correctamente.\n";
}

// Ver usuarios - métodos de administrador
void ModuloUsuarios::verUsuariosRegistrados() {
    std::ifstream archivo(rutaArchivoUsuarios);
    if (!archivo.is_open()) {
        std::cout << " No se pudo abrir el archivo.\n";
        return;
    }

    std::string linea;
    int contador = 0;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, correo, contrasena, tipo;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, contrasena, '|');
        std::getline(ss, tipo, '|');

        std::cout << "---------------------------\n";
        std::cout << "Tipo: " << tipo << "\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Correo: " << correo << "\n";
        contador++;
    }

    if (contador == 0) {
        std::cout << " No hay usuarios registrados.\n";
    }

    archivo.close();
}

// Eliminar usuario
void ModuloUsuarios::eliminarUsuarioPorId() {
    std::string idEliminar;
    std::cout << "\n Eliminar usuario\nIngrese el ID del usuario: ";
    std::cin >> idEliminar;

    std::ifstream archivoOriginal(rutaArchivoUsuarios);
    std::ofstream archivoTemporal("data/temp_usuarios.txt");
    bool eliminado = false;

    std::string linea;
    while (std::getline(archivoOriginal, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, correo, contrasena, tipo;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, contrasena, '|');
        std::getline(ss, tipo, '|');

        if (id != idEliminar) {
            archivoTemporal << id << "|"
                            << nombre << "|"
                            << correo << "|"
                            << contrasena << "|"
                            << tipo << "\n";
        } else {
            eliminado = true;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (eliminado) {
        std::remove(rutaArchivoUsuarios.c_str());
        std::rename("data/temp_usuarios.txt", rutaArchivoUsuarios.c_str());
        std::cout << " Usuario eliminado correctamente.\n";
    } else {
        std::remove("data/temp_usuarios.txt");
        std::cout << " No se encontro un usuario con ese ID.\n";
    }
}


// Editar usuario
void ModuloUsuarios::editarUsuarioPorId() {
    std::string idEditar;
    std::cout << "\n Editar datos de usuario\nIngrese el ID del usuario: ";
    std::cin >> idEditar;

    std::ifstream archivoOriginal(rutaArchivoUsuarios);
    std::ofstream archivoTemporal("data/temp_usuarios.txt");
    bool editado = false;

    std::string linea;
    while (std::getline(archivoOriginal, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, correo, contrasena, tipo;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, contrasena, '|');
        std::getline(ss, tipo, '|');

        if (id == idEditar) {
            std::cout << "Nuevo nombre: "; std::cin >> nombre;
            std::cout << "Nuevo correo: "; std::cin >> correo;
            std::cout << "Nueva contrasena: "; std::cin >> contrasena;
            editado = true;
        }

        archivoTemporal << id << "|"
                        << nombre << "|"
                        << correo << "|"
                        << contrasena << "|"
                        << tipo << "\n";
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (editado) {
        std::remove(rutaArchivoUsuarios.c_str());
        std::rename("data/temp_usuarios.txt", rutaArchivoUsuarios.c_str());
        std::cout << " Usuario actualizado exitosamente.\n";
    } else {
        std::remove("data/temp_usuarios.txt");
        std::cout << " No se encontro un usuario con ese ID.\n";
    }
}


// Menú principal para administrar usuarios
void ModuloUsuarios::gestionarUsuariosAdministrador() {
    bool continuar = true;

    while (continuar) {
        std::cout << "\n Gestion de usuarios (Administrador):\n";
        std::cout << "1. Ver usuarios registrados\n";
        std::cout << "2. Registrar nuevo usuario\n";
        std::cout << "3. Eliminar usuario por ID\n";
        std::cout << "4. Editar datos de usuario\n";
        std::cout << "5. Volver al menu principal\n";

        int opcion;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: verUsuariosRegistrados(); break;
            case 2: registrarUsuario(); break;
            case 3: eliminarUsuarioPorId(); break;
            case 4: editarUsuarioPorId(); break;
            case 5: continuar = false; break;
            default: std::cout << " Opcion invalida.\n";
        }
    }
}



