#include "../include/notificaciones/SistemaNotificaciones.h"
#include "../include/notificaciones/UsuarioObserver.h"
#include <iostream>

int main() {
    std::cout << "\n PRUEBA - MÓDULO NOTIFICACIONES \n";

    // Crear el sistema
    SistemaNotificaciones sistema;

    // Crear observadores simulados
    NotificacionObserver* u1 = new UsuarioObserver("lucas@outlook.com");
    NotificacionObserver* u2 = new UsuarioObserver("admin@universidad.edu");
    NotificacionObserver* u3 = new UsuarioObserver("profe.literatura@uni.edu");

    // Agregarlos al sistema
    sistema.agregarObservador(u1);
    sistema.agregarObservador(u2);
    sistema.agregarObservador(u3);

    // Enviar notificación general
    sistema.notificarATodos(" Recuerda devolver los libros antes del viernes.");

    // Enviar segunda notificación
    sistema.notificarATodos(" Nuevos recursos están disponibles en la biblioteca.");

    std::cout << "\n FIN DE PRUEBA - NOTIFICACIONES FUNCIONANDO CORRECTAMENTE\n";
    return 0;
}
