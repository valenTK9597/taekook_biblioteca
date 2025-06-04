#include <iostream>
#include <memory>
#include <limits>

#include "include/usuarios/ModuloUsuarios.h"
#include "include/recursos/ModuloRecursos.h"
#include "include/prestamos/ModuloPrestamos.h"
#include "include/busqueda/ModuloBusqueda.h"
#include "include/notificaciones/ModuloNotificaciones.h"

int main() {
    ModuloUsuarios moduloUsuarios("data/usuarios.txt");
    ModuloRecursos moduloRecursos("data/recursos.txt");
    ModuloPrestamos moduloPrestamos("data/prestamos.txt", "data/usuarios.txt", "data/recursos.txt");
    ModuloBusqueda moduloBusqueda("data/recursos.txt");
    ModuloNotificaciones moduloNotificaciones("data/usuarios.txt");


    Usuario* usuarioActivo = nullptr;

    while (true) {
        std::cout << "\n Sistema de Biblioteca Virtual\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrarse\n";
        std::cout << "3. Salir\n";

        int opcion;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        if (opcion == 1) {
            usuarioActivo = moduloUsuarios.iniciarSesion();

            if (!usuarioActivo) {
                std::cout << " Usuario o contraseña incorrectos.\n";
                continue;
            }

           moduloNotificaciones.verNotificacionesUsuario(usuarioActivo->getId(), "app");

            bool enSesion = true;
            while (enSesion) {
                std::cout << "\n Bienvenido, " << usuarioActivo->getNombre()
                          << " (" << usuarioActivo->getTipo() << ")\n";

                // 🔹 Estudiante / Profesor
                if (usuarioActivo->getTipo() == "Estudiante" || usuarioActivo->getTipo() == "Profesor") {
                    std::cout << "\n1. Editar perfil\n";
                    std::cout << "2. Ver recursos disponibles\n";
                    std::cout << "3. Buscar recursos\n";
                    std::cout << "4. Préstamos\n";
                    std::cout << "5. Notificaciones\n";
                    std::cout << "6. Cerrar sesión\n";

                    int subopcion;
                    std::cout << "Seleccione una opción: ";
                    std::cin >> subopcion;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                    switch (subopcion) {
                        case 1:
                            moduloUsuarios.editarPerfilUsuario(usuarioActivo);
                            break;

                        case 2:
                            moduloRecursos.verRecursosDisponibles();
                            break;

                        case 3: {
                            bool buscando = true;
                            while (buscando) {
                                std::cout << "\n 🔍 Submenú de búsqueda:\n";
                                std::cout << "1. Buscar por título\n";
                                std::cout << "2. Buscar por autor\n";
                                std::cout << "3. Buscar por tipo\n";
                                std::cout << "4. Volver\n";

                                int b;
                                std::cout << "Seleccione una opción: ";
                                std::cin >> b;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                                switch (b) {
                                    case 1: moduloBusqueda.buscarPorTitulo(false); break;
                                    case 2: moduloBusqueda.buscarPorAutor(false); break;
                                    case 3: moduloBusqueda.buscarPorTipo(false); break;
                                    case 4: buscando = false; break;
                                    default: std::cout << " Opción inválida.\n";
                                }
                            }
                            break;
                        }

                        case 4: {
                            bool gestionando = true;
                            while (gestionando) {
                                std::cout << "\n 📚 Submenú de préstamos:\n";
                                std::cout << "1. Solicitar préstamo\n";
                                std::cout << "2. Ver mis préstamos\n";
                                std::cout << "3. Devolver un préstamo\n";
                                std::cout << "4. Ver reservas\n";
                                std::cout << "5. Cancelar una reserva\n";
                                std::cout << "6. Volver\n";

                                int p;
                                std::cout << "Seleccione una opción: ";
                                std::cin >> p;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                                switch (p) {
                                    case 1: moduloPrestamos.registrarPrestamo(); break;
                                    case 2: moduloPrestamos.verPrestamosPorUsuario(usuarioActivo->getId()); break;
                                    case 3: moduloPrestamos.devolverPrestamoPorId(); break;
                                    case 4: moduloPrestamos.verReservasUsuario(usuarioActivo->getId()); break;
                                    case 5: moduloPrestamos.cancelarReservaUsuario(usuarioActivo->getId()); break;
                                    case 6: gestionando = false; break;
                                    default: std::cout << " Opción inválida.\n";
                                }
                            }
                            break;
                        }

                        case 5:
                            moduloNotificaciones.gestionarNotificacionesUsuario(usuarioActivo->getId());
                            break;
                        case 6:
                            std::cout << " Sesion cerrada.\n";
                            enSesion = false;
                            break;

                        default:
                            std::cout << " Opción inválida.\n";
                    }

                // 🔸 Administrador
                } else if (usuarioActivo->getTipo() == "Administrador") {
                    std::cout << "\n1. Editar perfil\n";
                    std::cout << "2. Gestionar usuarios\n";
                    std::cout << "3. Gestionar recursos\n";
                    std::cout << "4. Gestionar préstamos\n";
                    std::cout << "5. Buscar recursos\n";
                    std::cout << "6. Ver notificaciones\n";
                    std::cout << "7. Cerrar sesión\n";

                    int subopcion;
                    std::cout << "Seleccione una opción: ";
                    std::cin >> subopcion;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


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
                        case 5: {
                            bool buscando = true;
                            while (buscando) {
                                std::cout << "\n 🔍 Submenú de búsqueda (Administrador):\n";
                                std::cout << "1. Buscar por título\n";
                                std::cout << "2. Buscar por autor\n";
                                std::cout << "3. Buscar por tipo\n";
                                std::cout << "4. Volver\n";

                                int b;
                                std::cout << "Seleccione una opción: ";
                                std::cin >> b;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                                switch (b) {
                                    case 1: moduloBusqueda.buscarPorTitulo(true); break;
                                    case 2: moduloBusqueda.buscarPorAutor(true); break;
                                    case 3: moduloBusqueda.buscarPorTipo(true); break;
                                    case 4: buscando = false; break;
                                    default: std::cout << " Opción inválida.\n";
                                }
                            }
                            break;
                        }
                        case 6:
                            moduloNotificaciones.gestionarNotificacionesUsuario(usuarioActivo->getId());
                            break;
                        case 7:
                            std::cout << " Sesión cerrada.\n";
                            enSesion = false;
                            break;
                        default:
                            std::cout << " Opción inválida.\n";
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
            std::cout << " Opción no válida.\n";
        }
    }

    return 0;
}
