#include <iostream>
#include <memory>
#include "include/usuarios/ModuloUsuarios.h"
#include "include/recursos/ModuloRecursos.h"
#include "include/prestamos/ModuloPrestamos.h"

int main() {
    ModuloUsuarios moduloUsuarios("data/usuarios.txt");
    ModuloRecursos moduloRecursos("data/recursos.txt");
    ModuloPrestamos moduloPrestamos(
        "data/prestamos.txt",
        "data/usuarios.txt",
        "data/recursos.txt"
    );

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

                // 🔹 Menú para Estudiante y Profesor
                if (usuarioActivo->getTipo() == "Estudiante" || usuarioActivo->getTipo() == "Profesor") {
                    std::cout << "1. Editar perfil\n";
                    std::cout << "2. Ver recursos disponibles\n";
                    std::cout << "3. Buscar recurso por título\n";
                    std::cout << "4. Buscar recurso por autor\n";
                    std::cout << "5. Solicitar préstamo\n";
                    std::cout << "6. Ver mis préstamos\n";
                    std::cout << "7. Devolver un préstamo\n";
                    std::cout << "8. Ver reservas\n";
                    std::cout << "9. Cancelar una reserva\n";
                    std::cout << "10. Cerrar sesión\n";

                    int subopcion;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;

                    switch (subopcion) {
                        case 1:
                            moduloUsuarios.editarPerfilUsuario(usuarioActivo);
                            break;
                        case 2:
                            moduloRecursos.verRecursosDisponibles();
                            break;
                        case 3:
                            moduloRecursos.buscarPorTitulo();
                            break;
                        case 4:
                            moduloRecursos.buscarPorAutor();
                            break;
                        case 5:
                            moduloPrestamos.registrarPrestamo();
                            break;
                        case 6:
                            moduloPrestamos.verPrestamosPorUsuario(usuarioActivo->getId());
                            break;
                        case 7:
                            moduloPrestamos.devolverPrestamoPorId();
                            break;
                        case 8:
                            moduloPrestamos.verReservasUsuario(usuarioActivo->getId());
                            break;
                        case 9:
                            moduloPrestamos.cancelarReservaUsuario(usuarioActivo->getId());
                            break;
                        case 10:
                            std::cout << " Sesion cerrada.\n";
                            enSesion = false;
                            break;
                        default:
                            std::cout << " Opcion invalida.\n";
                    }

                //  Menú para Administrador
                } else if (usuarioActivo->getTipo() == "Administrador") {
                    std::cout << "\n1. Editar perfil\n";
                    std::cout << "2. Gestionar usuarios\n";
                    std::cout << "3. Gestionar recursos\n";
                    std::cout << "4. Gestionar prestamos\n";
                    std::cout << "5. Cerrar sesion\n";

                    int subopcion;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;

                    switch (subopcion) {
                        case 1:
                            moduloUsuarios.editarPerfilUsuario(usuarioActivo);
                            break;
                        case 2:
                            moduloUsuarios.gestionarUsuariosAdministrador();
                            break;
                        case 3:
                            moduloRecursos.gestionarRecursosAdministrador();
                            break;
                        case 4:
                            moduloPrestamos.gestionarPrestamosAdministrador();
                            break;
                        case 5:
                            std::cout << " Sesion cerrada.\n";
                            enSesion = false;
                            break;
                        default:
                            std::cout << " Opcion invalida.\n";
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
            std::cout << " Hasta pronto.\n";
            break;
        }

        else {
            std::cout << " Opción no valida.\n";
        }
    }

    return 0;
}

