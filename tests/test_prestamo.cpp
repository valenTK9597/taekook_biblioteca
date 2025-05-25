#include "../include/prestamos/Prestamo.h"
#include "../include/prestamos/PrestamoFactory.h"
#include "../include/prestamos/EstadoDisponible.h"
#include "../include/prestamos/EstadoPrestado.h"
#include "../include/prestamos/EstadoVencido.h"
#include "../include/prestamos/EstadoDevuelto.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string rutaArchivo = "data/prestamos.txt";
    std::string fechaActual = "2025-06-10";  // Simulación de hoy

    std::cout << "\n🔧 INICIO DE PRUEBAS DEL MÓDULO PRESTAMO\n";

    // Crear préstamos con distintos estados
    Prestamo* p1 = new Prestamo("P001", "U001", "R001", "2025-06-01", "2025-06-08", new EstadoDisponible());
    Prestamo* p2 = new Prestamo("P002", "U002", "R002", "2025-06-01", "2025-06-10", new EstadoPrestado());
    Prestamo* p3 = new Prestamo("P003", "U003", "R003", "2025-05-20", "2025-05-25", new EstadoVencido());
    Prestamo* p4 = new Prestamo("P004", "U004", "R004", "2025-05-15", "2025-05-20", new EstadoDevuelto());

    // Mostrar detalle y calcular multas
    std::cout << "\n Préstamo 1:\n";
    p1->mostrarDetalle();
    std::cout << "Multa: " << p1->calcularMulta(fechaActual) << "\n";

    std::cout << "\n Préstamo 2:\n";
    p2->mostrarDetalle();
    std::cout << "Multa: " << p2->calcularMulta(fechaActual) << "\n";

    std::cout << "\n Préstamo 3:\n";
    p3->mostrarDetalle();
    std::cout << "Multa: " << p3->calcularMulta(fechaActual) << "\n";

    std::cout << "\n Préstamo 4:\n";
    p4->mostrarDetalle();
    std::cout << "Multa: " << p4->calcularMulta(fechaActual) << "\n";

    // Guardar préstamos
    PrestamoFactory::guardarPrestamoEnArchivo(p1, rutaArchivo);
    PrestamoFactory::guardarPrestamoEnArchivo(p2, rutaArchivo);
    PrestamoFactory::guardarPrestamoEnArchivo(p3, rutaArchivo);
    PrestamoFactory::guardarPrestamoEnArchivo(p4, rutaArchivo);

    delete p1;
    delete p2;
    delete p3;
    delete p4;

    // Cargar desde archivo
    std::cout << "\n Cargando préstamos desde archivo:\n";
    std::vector<Prestamo*> cargados = PrestamoFactory::cargarPrestamosDesdeArchivo(rutaArchivo);

    for (Prestamo* prestamo : cargados) {
        prestamo->mostrarDetalle();
        std::cout << "Multa al " << fechaActual << ": " << prestamo->calcularMulta(fechaActual) << "\n";
        delete prestamo;
    }

    
    return 0;
}
