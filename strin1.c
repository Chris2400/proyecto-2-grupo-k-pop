#include <stdio.h>

// ==========================================
// SPRINT 1: CIMIENTOS (HU-01 a HU-08)
// ==========================================

// HU-01: Estructura Idol
typedef struct {
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
} Idol;

// HU-04: Limitar un valor a un rango
int limitar(int valor, int minimo, int maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

// HU-03: Mostrar una integrante (lleva const porque solo lee)
void mostrar(const Idol *i) {
    if (i == NULL) return; // Verificación DoD
    printf("Nombre: %s | Popularidad: %d | Energia: %d/%d | Fans: %d\n", 
           i->nombre, i->popularidad, i->energia, i->energia_max, i->fans);
}

// HU-05: Ensayar (modifica, no lleva const)
void ensayar(Idol *i) {
    if (i == NULL) return;
    i->popularidad += 5;
    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}

// HU-06: Descansar (modifica, no lleva const)
void descansar(Idol *i) {
    if (i == NULL) return;
    i->energia = limitar(i->energia + 30, 0, i->energia_max);
}

// HU-07: Saber si está activa (lleva const porque solo lee)
int esta_activa(const Idol *i) {
    if (i == NULL) return 0;
    return i->energia > 0 ? 1 : 0;
}

int main() {
    // HU-01: Crear a Jennie
    Idol jennie = {"jennie", 50, 100, 100, 12000};
    
    // HU-02: Leer campos con punto, desreferencia y flecha
    Idol *p = &jennie;
    printf("--- HU-02: Tres formas de leer fans ---\n");
    printf("Con punto: %d\n", jennie.fans);
    printf("Con desreferencia: %d\n", (*p).fans);
    printf("Con flecha: %d\n", p->fans);
    printf("Direccion de p: %p\n", (void *)p);
    printf("Direccion de jennie: %p\n", (void *)&jennie);
    
    // HU-03: Mostrar
    printf("\n--- HU-03: Mostrar integrante ---\n");
    mostrar(&jennie);
    
    // HU-05 y HU-06: Ensayar y Descansar
    printf("\n--- HU-05 y HU-06: Ensayar y Descansar ---\n");
    ensayar(&jennie);
    printf("Despues de ensayar: ");
    mostrar(&jennie);
    descansar(&jennie);
    printf("Despues de descansar: ");
    mostrar(&jennie);
    
    // Prueba de límites (HU-05 y HU-06)
    for(int i = 0; i < 20; i++) ensayar(&jennie);
    printf("\nEnergia despues de 20 ensayos: %d (no debe ser negativa)\n", jennie.energia);
    
    for(int i = 0; i < 20; i++) descansar(&jennie);
    printf("Energia despues de 20 descansos: %d (no debe pasar de %d)\n", jennie.energia, jennie.energia_max);
    
    // HU-07: Esta activa
    printf("\n--- HU-07: Esta activa ---\n");
    printf("¿Jennie esta activa?: %d\n", esta_activa(&jennie));
    
    return 0;
}