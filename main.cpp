#include <iostream>
#include <memory>
#include "include/usuarios/ModuloUsuarios.h"
#include "include/usuarios/UsuarioFactory.h"
#include "include/usuarios/Usuario.h"
#include "include/usuarios/ModuloUsuarios.h"
#include "include/recursos/ModuloRecursos.h"
#include "include/recursos/RecursoFactory.h"



int main() {
    ModuloUsuarios moduloUsuarios("data/usuarios.txt");
    ModuloRecursos moduloRecursos("data/recursos.txt");

    Usuario* usuarioActivo = nullptr;

    while (true) {
        std::cout << "\n Sistema de Biblioteca Virtual\n";
        std::cout << "1. Iniciar sesion\n";
        std::cout << "2. Registrarse\n";
        std::cout << "3. Salir\n";

        int opcion;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            usuarioActivo = moduloUsuarios.iniciarSesion();

            if (!usuarioActivo) {
                std::cout << " Usuario o contrasena incorrectos.\n";
                continue;
            }

            bool enSesion = true;
            while (enSesion) {
                std::cout << "\n Bienvenido, " << usuarioActivo->getNombre()
                          << " (" << usuarioActivo->getTipo() << ")\n";

                // Menú según tipo
                if (usuarioActivo->getTipo() == "Estudiante" || usuarioActivo->getTipo() == "Profesor") {
                    std::cout << "1. Editar perfil\n";
                    std::cout << "2. Ver recursos disponibles\n";
                    std::cout << "3. Buscar recurso por título\n";
                    std::cout << "4. Buscar recurso por autor\n";
                    std::cout << "5. Cerrar sesión\n";

                    int subopcion;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        moduloUsuarios.editarPerfilUsuario(usuarioActivo);
                    } else if (subopcion == 2) {
                        moduloRecursos.verRecursosDisponibles();
                    } else if (subopcion == 3) {
                        moduloRecursos.buscarPorTitulo();
                    } else if (subopcion == 4) {
                        moduloRecursos.buscarPorAutor();
                    } else if (subopcion == 5) {
                        std::cout << " Sesion cerrada.\n";
                        enSesion = false;
                    } else {
                        std::cout << " Opcion invalida.\n";
                    }

                } else if (usuarioActivo->getTipo() == "Administrador") {
                    std::cout << "1. Editar perfil\n";
                    std::cout << "2. Gestionar usuarios\n";
                    std::cout << "3. Gestionar recursos\n";
                    std::cout << "4. Cerrar sesion\n";

                    int subopcion;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        moduloUsuarios.editarPerfilUsuario(usuarioActivo);
                    } else if (subopcion == 2) {
                        moduloUsuarios.gestionarUsuariosAdministrador();
                    } else if (subopcion == 3) {
                        moduloRecursos.gestionarRecursosAdministrador();
                    } else if (subopcion == 4) {
                        std::cout << "👋 Sesion cerrada.\n";
                        enSesion = false;
                    } else {
                        std::cout << "⚠️ Opcion invalida.\n";
                    }

                }
            }

            delete usuarioActivo;
            usuarioActivo = nullptr;
        }

        else if (opcion == 2) {
            moduloUsuarios.registrarUsuario();
        }

        else if (opcion == 3) {
            std::cout << "👋 Hasta pronto.\n";
            break;
        }

        else {
            std::cout << "⚠️ Opcion no valida.\n";
        }
    }

    return 0;
}
