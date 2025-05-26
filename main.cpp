#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // std::quoted
#include <sstream>

#include "include/usuarios/UsuarioFactory.h"
#include "include/usuarios/Usuario.h"
#include "include/usuarios/Estudiante.h"
#include "include/usuarios/Profesor.h"
#include "include/usuarios/Administrador.h"
#include "include/recursos/RecursoFactory.h"
#include "include/recursos/Recurso.h"

// Función para cargar usuarios desde archivo
std::vector<Usuario*> cargarUsuariosDesdeArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    std::vector<Usuario*> usuarios;

    if (!archivo.is_open()) {
        std::cerr << "❌ No se pudo abrir el archivo de usuarios.\n";
        return usuarios;
    }

    std::string tipo, id, nombre, correo, contrasena;
    while (!archivo.eof()) {
        archivo >> std::ws;
        if (archivo.peek() == EOF) break;

        archivo >> std::quoted(tipo) >> std::quoted(id) >> std::quoted(nombre)
                >> std::quoted(correo) >> std::quoted(contrasena);

        if (tipo.empty() || id.empty() || correo.empty()) continue;

        Usuario* u = UsuarioFactory::crearUsuario(tipo, id, nombre, correo, contrasena);
        if (u) usuarios.push_back(u);
    }

    archivo.close();
    return usuarios;
}

// Registro de usuario
void registrarUsuario(const std::string& ruta) {
    std::vector<Usuario*> usuarios = cargarUsuariosDesdeArchivo(ruta);
    std::string tipo, id, nombre, correo, contrasena;

    std::cout << "\n📋 Registro de nuevo usuario\n";
    std::cout << "Tipo (Estudiante / Profesor / Administrador): ";
    std::cin >> tipo;

    std::cout << "ID: "; std::cin >> id;
    std::cout << "Nombre: "; std::cin >> nombre;
    std::cout << "Correo: "; std::cin >> correo;

    // Validar correo único
    for (Usuario* u : usuarios) {
        if (u->getCorreo() == correo) {
            std::cout << "❌ Ya existe un usuario con ese correo.\n";
            for (Usuario* x : usuarios) delete x;
            return;
        }
    }

    std::cout << "Contraseña: "; std::cin >> contrasena;

    Usuario* nuevo = UsuarioFactory::crearUsuario(tipo, id, nombre, correo, contrasena);
    if (!nuevo) {
        std::cout << "❌ Tipo de usuario inválido.\n";
        for (Usuario* x : usuarios) delete x;
        return;
    }

    std::ofstream archivo(ruta, std::ios::app);
    if (!archivo.is_open()) {
        std::cout << "❌ No se pudo abrir el archivo para guardar.\n";
        delete nuevo;
        for (Usuario* x : usuarios) delete x;
        return;
    }

    archivo << std::quoted(tipo) << " "
            << std::quoted(id) << " "
            << std::quoted(nombre) << " "
            << std::quoted(correo) << " "
            << std::quoted(contrasena) << "\n";

    archivo.close();
    delete nuevo;
    for (Usuario* x : usuarios) delete x;

    std::cout << "✅ Usuario registrado exitosamente.\n";
}

// Mostrar recursos disponibles
void verRecursosDisponibles() {
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo("data/recursos.txt");

    if (recursos.empty()) {
        std::cout << "\n⚠️ No hay recursos disponibles en este momento.\n";
        return;
    }

    std::cout << "\n📚 Recursos disponibles:\n";
    for (const auto& recurso : recursos) {
        std::cout << " - [" << recurso->getTipo() << "] "
                  << recurso->getTitulo() << " | Autor: "
                  << recurso->getAutor() << "\n";
    }

    for (auto r : recursos) delete r;
}

// Mostrar menú personalizado
void mostrarMenu(Usuario* usuario) {
    std::cout << "\n👤 Bienvenido, " << usuario->getNombre()
              << " (" << usuario->getTipo() << ")\n";

    if (usuario->getTipo() == "Estudiante" || usuario->getTipo() == "Profesor") {
        std::cout << "1. Ver recursos disponibles\n";
        std::cout << "2. Solicitar préstamo\n";
        std::cout << "3. Buscar recursos\n";
        std::cout << "4. Ver recomendaciones\n";
        std::cout << "5. Salir\n";
    } else if (usuario->getTipo() == "Administrador") {
        std::cout << "1. Gestionar usuarios\n";
        std::cout << "2. Gestionar recursos\n";
        std::cout << "3. Ver préstamos\n";
        std::cout << "4. Enviar notificaciones\n";
        std::cout << "5. Salir\n";
    }
}

// Función para iniciar sesión (devuelve copia viva)
Usuario* iniciarSesion(const std::string& rutaUsuarios) {
    std::vector<Usuario*> usuarios = cargarUsuariosDesdeArchivo(rutaUsuarios);

    if (usuarios.empty()) {
        std::cout << "\n Todavía no hay usuarios registrados. Registre uno primero.\n";
        return nullptr;
    }

    std::string correoInput, contrasenaInput;
    std::cout << "\n📥 Inicia sesión\nCorreo: ";
    std::cin >> correoInput;
    std::cout << "Contraseña: ";
    std::cin >> contrasenaInput;

    // Limpiar espacios invisibles
    correoInput.erase(correoInput.find_last_not_of(" \n\r\t") + 1);
    contrasenaInput.erase(contrasenaInput.find_last_not_of(" \n\r\t") + 1);

    Usuario* usuarioEncontrado = nullptr;

    for (Usuario* u : usuarios) {
        if (u->getCorreo() == correoInput && u->getContrasena() == contrasenaInput) {
            usuarioEncontrado = UsuarioFactory::crearUsuario(
                u->getTipo(), u->getId(), u->getNombre(), u->getCorreo(), u->getContrasena()
            );
            break;
        }
    }

    for (Usuario* u : usuarios) delete u;

    return usuarioEncontrado;
}

int main() {
    const std::string rutaUsuarios = "data/usuarios.txt";
    Usuario* usuarioActivo = nullptr;

    while (true) {
        std::cout << "\n📚 Sistema de Biblioteca Virtual\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrarse\n";
        std::cout << "3. Salir\n";

        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (opcion == 1) {
            usuarioActivo = iniciarSesion(rutaUsuarios);

            if (!usuarioActivo) continue;

            mostrarMenu(usuarioActivo);

            int opcionUsuario;
            std::cout << "\nSeleccione una opción del menú: ";
            std::cin >> opcionUsuario;

            if (usuarioActivo->getTipo() == "Estudiante" || usuarioActivo->getTipo() == "Profesor") {
                if (opcionUsuario == 1) {
                    verRecursosDisponibles();
                }
            } else if (usuarioActivo->getTipo() == "Administrador") {
                if (opcionUsuario == 2) {
                    verRecursosDisponibles(); // Temporal
                }
            }

            delete usuarioActivo;
            usuarioActivo = nullptr;
        }

        else if (opcion == 2) {
            registrarUsuario(rutaUsuarios);
        }

        else if (opcion == 3) {
            std::cout << "👋 Hasta pronto.\n";
            break;
        }

        else {
            std::cout << "❌ Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}