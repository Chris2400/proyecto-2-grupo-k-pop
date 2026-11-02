#include <stdio.h>

// ==========================================
// SPRINT 2: SEGURIDAD Y ENLACE DE STRUCTS
// ==========================================

// HU-12: Estructura Cancion (Debe ir ANTES de Idol)
typedef struct {
    char nombre[30];
    int bonus;
    int vigencia;
} Cancion;

// HU-01 (Actualizado en Sprint 2): Estructura Idol con cancion opcional
typedef struct {
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    Cancion *cancion; // <--- Nuevo campo (HU-13)
} Idol;

// HU-04: Limitar
int limitar(int valor, int minimo, int maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

// HU-03: Mostrar
void mostrar(const Idol *i) {
    if (i == NULL) return;
    printf("Nombre: %s | Popularidad: %d | Energia: %d/%d | Fans: %d\n", 
           i->nombre, i->popularidad, i->energia, i->energia_max, i->fans);
}

// HU-05: Ensayar
void ensayar(Idol *i) {
    if (i == NULL) return;
    i->popularidad += 5;
    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}

// HU-06: Descansar
void descansar(Idol *i) {
    if (i == NULL) return;
    i->energia = limitar(i->energia + 30, 0, i->energia_max);
}

// HU-07: Esta activa
int esta_activa(const Idol *i) {
    if (i == NULL) return 0;
    return i->energia > 0 ? 1 : 0;
}

// HU-09: Colaboración segura (NUEVO SPRINT 2)
int colaboracion(Idol *a, Idol *b) {
    if (a == NULL || b == NULL || a == b) return 0; // Verificación antes de ->
    a->popularidad += 10;
    a->energia = limitar(a->energia - 15, 0, a->energia_max);
    b->popularidad += 10;
    b->energia = limitar(b->energia - 15, 0, b->energia_max);
    printf("Colaboracion exitosa entre %s y %s.\n", a->nombre, b->nombre);
    return 1;
}

// HU-14: Asignar y quitar canción (NUEVO SPRINT 2)
void asignar_cancion(Idol *i, Cancion *c) {
    if (i == NULL) return;
    i->cancion = c; // Si c es NULL, se la quita
}

int main() {
    // Inicialización con el nuevo campo cancion = NULL (HU-13)
    Idol jennie = {"jennie", 50, 100, 100, 12000, NULL};
    Idol rose = {"rose", 50, 100, 100, 10000, NULL};
    
    // HU-12: Crear canciones
    Cancion discos[2] = {{"Starlight", 10, 3}, {"Nova", 5, 6}};
    
    printf("--- PRUEBAS SPRINT 1 (Siguen funcionando) ---\n");
    mostrar(&jennie);
    
    printf("\n--- HU-09: Colaboracion segura ---\n");
    printf("Colaboracion consigo misma (debe ser 0): %d\n", colaboracion(&jennie, &jennie));
    printf("Colaboracion con NULL (debe ser 0): %d\n", colaboracion(NULL, &rose));
    printf("Colaboracion valida (debe ser 1): %d\n", colaboracion(&jennie, &rose));
    
    printf("\n--- HU-10: Dinamica por turnos ---\n");
    // Reiniciamos energias para la prueba
    jennie.energia = 50; rose.energia = 50; 
    Idol *turno = &jennie;
    Idol *otra = &rose;
    Idol *temp;
    
    while (esta_activa(turno) && esta_activa(otra)) {
        ensayar(turno);
        // Intercambio de apuntadores, NO de structs (HU-11)
        temp = turno;
        turno = otra;
        otra = temp;
    }
    printf("El ciclo termino. %s conserva energia.\n", esta_activa(turno) ? turno->nombre : otra->nombre);
    
    printf("\n--- HU-14: Asignar cancion ---\n");
    asignar_cancion(&jennie, &discos[0]);
    asignar_cancion(&rose, &discos[0]); // Canción compartida
    printf("Cancion asignada a Jennie: %s\n", jennie.cancion->nombre);
    printf("Cancion asignada a Rose: %s\n", rose.cancion->nombre);
    
    asignar_cancion(&jennie, NULL); // Quitar canción
    printf("Jennie tiene cancion?: %s\n", jennie.cancion == NULL ? "No" : "Si");
    
    return 0;
}