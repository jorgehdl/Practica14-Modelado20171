#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %lu elementos\n", longitud(lista));
    imprime_lista_int(lista);
    
    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %lu elementos\n", longitud(lista));
    imprime_lista_int(lista);
    
    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 10);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %lu elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %lu elementos\n", longitud(lista));
    
    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);
    
    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);
    
    //Se libera la memoria ocupada
    borra_lista(lista);
    //printf("La lista tiene %lu elementos\n", longitud(lista));
    //imprime_lista_int(lista);
    
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice <20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

Lista crea_lista(){
    Lista lista= calloc(0,sizeof(Lista));
    return lista; 
}

size_t longitud(Lista lista){
    if(*lista == NULL) return 0;

    int num= 0;
    Elemento* elem= (*lista);

    while(elem != NULL){
        num++;
        elem= elem -> siguiente;
    } 
    return num;
}

int inserta_elemento(Lista lista, void *valor){
    Elemento *new = malloc(sizeof(Elemento));
    Elemento* elem= (*lista);
    
    new->valor=valor;
    new->siguiente=elem;
    *lista=new;

    return longitud(lista);
}

Elemento* quita_elemento(Lista lista, size_t posicion){
    if(posicion<0)return;
    if(posicion>=longitud(lista)) return;

    int reps = longitud(lista);
    int i;
    Elemento* curr= (*lista);
    Elemento* prev= NULL;

    if(posicion==0){
        *lista=curr->siguiente;
        return curr;
    }


    for (i=0;i<reps;i++){
        curr= curr -> siguiente;
        if(i==posicion-1){
            prev->siguiente=curr->siguiente;
        }
        prev=curr;
    }
    return curr;
}

void imprime_lista_int(Lista lista){
    if(*lista == NULL) printf("La lista es vacia \n");

    int reps = longitud(lista);
    int i;
    Elemento* elem= (*lista);

    for (i=0;i<reps;i++){
        printf("El elemento %d es %d\n", i, *((int*)elem->valor));
        elem= elem -> siguiente;
    }
}

int cmp_int(const void *a, const void *b){
    int x, y;
    x=*((int*)a);
    y=*((int*)b);
    if(x<y) return -1;
    else if(x>y) return 1;
    else return 0;
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
    int i;
    int *arr;
    arr = (int*)malloc(longitud(lista)*sizeof(int));
    Elemento* elem= (*lista);

    for (i=0;i<longitud(lista);i++){
        //printf("El elemento jajajajajajaj %d es %d\n", i, *((int*)elem->valor));
        arr[i]=*((int*)elem->valor);
        elem= elem -> siguiente;
    }

    qsort(arr, longitud(lista), sizeof(int), *cmp);
    elem= (*lista);

    for (i=0;i<longitud(lista);i++){
        //printf("estoy intentando %d es %d\n", i, *((int*)elem->valor));
        *((int*)elem->valor)=arr[i];
        //printf("help please %d es %d\n", i, *((int*)elem->valor));
        elem=elem->siguiente;
    }
    //imprime_lista_int(lista);
    free(arr);
}

void borra_lista(Lista lista){
    Elemento* deleted= (*lista);
    int i;
    for(i=0;i<longitud(lista);i++){
        deleted = quita_elemento(lista, i);
        free(deleted->siguiente);
        free(deleted->valor);
    }

}