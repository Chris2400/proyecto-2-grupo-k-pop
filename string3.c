#include <stdio.h>

// ==========================================
// SPRINT 1 y 2: ESTRUCTURAS BASE
// ==========================================
typedef struct {
    char nombre[30];
    int bonus;
    int vigencia;
} Cancion;

typedef struct {
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    Cancion *cancion;
} Idol;

// ==========================================
// SPRINT 3: GRUPO
// ==========================================
typedef struct {
    char nombre[30];
    Idol miembros[4];
    int n;
    Idol *lider;
} Grupo;

// ==========================================
// FUNCIONES DE LOS SPRINTS 1 Y 2
// ==========================================
int limitar(int valor, int minimo, int maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}

void mostrar(const Idol *i) {
    if (i == NULL) return;
    printf("Nombre: %s | Popularidad: %d | Energia: %d/%d | Fans: %d\n", 
           i->nombre, i->popularidad, i->energia, i->energia_max, i->fans);
}

void ensayar(Idol *i) {
    if (i == NULL) return;
    i->popularidad += 5;
    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}

void descansar(Idol *i) {
    if (i == NULL) return;
    i->energia = limitar(i->energia + 30, 0, i->energia_max);
}

int esta_activa(const Idol *i) {
    if (i == NULL) return 0;
    return i->energia > 0 ? 1 : 0;
}

int colaboracion(Idol *a, Idol *b) {
    if (a == NULL || b == NULL || a == b) return 0;
    a->popularidad += 10;
    a->energia = limitar(a->energia - 15, 0, a->energia_max);
    b->popularidad += 10;
    b->energia = limitar(b->energia - 15, 0, b->energia_max);
    return 1;
}

void asignar_cancion(Idol *i, Cancion *c) {
    if (i == NULL) return;
    i->cancion = c;
}

// ==========================================
// FUNCIONES NUEVAS DEL SPRINT 3
// ==========================================
// HU-15
int popularidad_total(const Idol *i) {
    if (i == NULL) return 0;
    int total = i->popularidad;
    if (i->cancion != NULL && i->cancion->vigencia > 0) {
        total += i->cancion->bonus;
    }
    return total;
}

// HU-17
int cambiar_lider(Grupo *g, Idol *nueva) {
    if (g == NULL || nueva == NULL) return 0;
    for (int i = 0; i < g->n; i++) {
        if (&g->miembros[i] == nueva) {
            g->lider = nueva;
            return 1;
        }
    }
    return 0;
}

// HU-18
void mostrar_grupo(const Grupo *g) {
    if (g == NULL) return;
    printf("Grupo: %s\n", g->nombre);
    const Idol *p = g->miembros;
    const Idol *fin = g->miembros + g->n;
    while (p < fin) {
        mostrar(p);
        p++;
    }
}

// HU-19
int contar_activas(const Grupo *g) {
    if (g == NULL || g->n == 0) return 0;
    int cont = 0;
    const Idol *p = g->miembros;
    const Idol *fin = g->miembros + g->n;
    while (p < fin) {
        if (esta_activa(p)) cont++;
        p++;
    }
    return cont;
}

// HU-20
Idol *idol_mas_cansada(Grupo *g) {
    if (g == NULL || g->n == 0) return NULL;
    Idol *mas_cansada = g->miembros;
    Idol *p = g->miembros + 1;
    Idol *fin = g->miembros + g->n;
    while (p < fin) {
        if (p->energia < mas_cansada->energia) {
            mas_cansada = p;
        }
        p++;
    }
    return mas_cansada;
}

// ==========================================
// MAIN (Pruebas del Sprint 3)
// ==========================================
int main() {
    Idol jennie = {"jennie", 50, 80, 100, 12000, NULL};
    Idol rose = {"rose", 50, 30, 100, 10000, NULL}; // La más cansada
    Idol lisa = {"lisa", 50, 100, 100, 15000, NULL};
    
    Cancion discos[2] = {{"Starlight", 10, 3}, {"Nova", 5, 6}};
    asignar_cancion(&jennie, &discos[0]);
    
    Grupo g = {"Lumina", {jennie, rose, lisa}, 3, NULL};
    
    printf("--- PRUEBAS SPRINT 3 ---\n");
    mostrar_grupo(&g);
    
    printf("\nActivas: %d\n", contar_activas(&g));
    
    Idol *cansada = idol_mas_cansada(&g);
    if (cansada != NULL) {
        printf("La mas cansada es: %s (Energia: %d)\n", cansada->nombre, cansada->energia);
        descansar(cansada);
        printf("Despues de descansar:\n");
        mostrar_grupo(&g);
    }
    
    return 0;
}