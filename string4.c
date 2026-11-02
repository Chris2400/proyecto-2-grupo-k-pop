#include <stdio.h>

// ==========================================
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    Cancion *cancion;
} Idol;

typedef struct {
    char nombre[30];
    Idol miembros[4];
    int n;
    Idol *lider;
} Grupo;

// ==========================================
// SPRINTS 1, 2 y 3: FUNCIONES BASE
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

int popularidad_total(const Idol *i) {
    if (i == NULL) return 0;
    int total = i->popularidad;
    if (i->cancion != NULL && i->cancion->vigencia > 0) {
        total += i->cancion->bonus;
    }
    return total;
}

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
// SPRINT 4: FUNCIONES NUEVAS
// ==========================================
// HU-21
void dar_concierto(Grupo *g) {
    if (g == NULL) return;
    printf("\n--- Concierto en vivo! ---\n");
    Idol *p = g->miembros;
    Idol *fin = g->miembros + g->n;
    
    while (p < fin) {
        if (esta_activa(p)) {
            int ganancia_fans = popularidad_total(p) * 10;
            p->fans += ganancia_fans;
            p->energia = limitar(p->energia - 30, 0, p->energia_max);
            
            if (p->cancion != NULL && p->cancion->vigencia > 0) {
                p->cancion->vigencia--;
                if (p->cancion->vigencia == 0) {
                    printf("Aviso: La cancion %s ya no esta vigente.\n", p->cancion->nombre);
                }
            }
        }
        p++;
    }
}

// HU-23
void mostrar_cancion_lider(const Grupo *g) {
    if (g == NULL) {
        printf("No hay grupo.\n");
        return;
    }
    if (g->lider == NULL) {
        printf("El grupo no tiene lider.\n");
        return;
    }
    if (g->lider->cancion == NULL) {
        printf("%s no tiene cancion asignada.\n", g->lider->nombre);
        return;
    }
    printf("La cancion de la lider %s es: %s\n", g->lider->nombre, g->lider->cancion->nombre);
}

// HU-24
void preparar_presentacion(Grupo *g) {
    if (g == NULL) return;
    
    printf("\n=== Preparando presentacion ===\n");
    
    Idol *cansada = idol_mas_cansada(g);
    if (cansada != NULL) {
        printf("Descansando a la mas cansada: %s\n", cansada->nombre);
        descansar(cansada);
    }
    
    dar_concierto(g);
    
    printf("\n--- Resumen del grupo ---\n");
    mostrar_grupo(g);
    printf("Integrantes activas: %d\n", contar_activas(g));
    mostrar_cancion_lider(g);
    
    // Verificación de que ninguna energía salió de rango
    Idol *p = g->miembros;
    Idol *fin = g->miembros + g->n;
    while (p < fin) {
        if (p->energia < 0 || p->energia > p->energia_max) {
            printf("ERROR: Energia fuera de rango en %s\n", p->nombre);
        }
        p++;
    }
}

// ==========================================
// MAIN (PRUEBAS FINALES)
// ==========================================
int main() {
    // Inicialización
    Idol jennie = {"jennie", 50, 80, 100, 12000, NULL};
    Idol rose = {"rose", 50, 40, 100, 10000, NULL};
    Idol lisa = {"lisa", 50, 100, 100, 15000, NULL};
    
    Cancion discos[2] = {{"Starlight", 10, 3}, {"Nova", 5, 6}};
    asignar_cancion(&jennie, &discos[0]);
    asignar_cancion(&rose, &discos[0]); // Canción compartida
    
    Grupo g = {"Lumina", {jennie, rose, lisa}, 3, NULL};
    cambiar_lider(&g, &g.miembros[0]); // Jennie es líder
    
    printf("========== PRUEBAS SPRINT 4 ==========\n");
    
    // HU-21 y HU-23
    printf("\n--- HU-23: Cancion de la lider ---\n");
    mostrar_cancion_lider(&g);
    
    // HU-24: Preparar presentación (varias veces para probar límites)
    printf("\n--- HU-24: Primera presentacion ---\n");
    preparar_presentacion(&g);
    
    printf("\n--- HU-24: Segunda presentacion ---\n");
    preparar_presentacion(&g);
    
    printf("\n--- HU-24: Tercera presentacion (probando limites) ---\n");
    preparar_presentacion(&g);
    
    // HU-23: Prueba de escenarios sin líder/canción
    printf("\n--- HU-23: Escenario sin lider ---\n");
    g.lider = NULL;
    mostrar_cancion_lider(&g);
    
    printf("\n--- HU-23: Escenario sin grupo ---\n");
    mostrar_cancion_lider(NULL);
    
    return 0;
}