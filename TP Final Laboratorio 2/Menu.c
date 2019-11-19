#include "Menu.h"

void imprimirCabecera()  ///Printea el nombre del juego
{
    system("COLOR 02");
    printf ("CARGANDO");
    printf ("     ");
    for (int i=0; i<30; i++){
        printf ("%c", 178);
        Sleep(50);
    }
    printf ("\n\n");
    system ("cls");
    char cabecera[]="  _________          ____          _________         __________    ";
    char cabecera2[] =" |         |        |    |        |         |       |   ____   | ";
    char cabecera3[] =" |    _____|        |    |        |    _____|       |  |    |  | ";
    char cabecera4[] =" |   |              |    |        |   |             |  |    |  | ";
    char cabecera5[] =" |   |              |    |        |   |             |  |    |  | ";
    char cabecera6[] =" |   |_____         |    |        |   |_____        |  |____|  | ";
    char cabecera7[] =" |         |        |    |        |         |       |          | ";
    char cabecera8[] =" |    _____|        |    |        |    _____|       |          | ";
    char cabecera9[] =" |    |             |    |        |    |            |   ____   | ";
    char cabecera10[]=" |    |             |    |        |    |            |  |    |  | ";
    char cabecera11[]=" |    |             |    |        |    |            |  |    |  | ";
    char cabecera12[]=" |____|             |____|        |____|            |__|    |__| ";
    int i;
    printf("%c", 201);
    for(i=0; i<70; i++)
    {
        printf("%c",205);
        Sleep(20);
    }
    printf("%c\n", 187);
    printf("%c%40s%4c\n", 186,cabecera,186);
    Sleep(50);
    printf("%c%40s%6c\n", 186,cabecera2,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera3,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera4,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera5,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera6,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera7,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera8,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera9,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera10,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera11,186);
    Sleep(50);
    printf("%c%32s%6c\n", 186,cabecera12,186);
    Sleep(50);
    printf("%c", 200);
    for(i=0; i<70; i++)
    {
        printf("%c",205);
        Sleep(20);
    }
    printf("%c", 188);
    printf("\n");
    system("pause");
    system("cls");
    crearVariables();
}

///Inicializa y carga las listas de ligas, mercado y usuario
void crearVariables(){
    nodoLiga * listaLigas = inicListaliga();
    listaLigas = cargarListaLigas(listaLigas);
    nodoMercado * listaMercado = iniclistaMercado();
    listaMercado = cargarListaMercado(listaMercado);
    nodoUsuario * listaUsuarios = inicListaUsuarios();
    listaUsuarios = cargarListaUsuarios(listaUsuarios);
    ejecutarMenu(listaLigas,listaMercado,listaUsuarios);
}

///Permite ingresar como usuario o administrador. Dependiendo la opción elegida nos lleva al menu de los anteriormente nombrados.
void ejecutarMenu (nodoLiga * listaLigas,nodoMercado * listaMercado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    printf ("Bienvenido al Simulador de Mercado de FIFA 20!\n Opciones disponibles:");
    printf ("\n  1. Para ingresar como administrador.");
    printf ("\n  2. Para ingresar como usuario.");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>2){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch (opcion){
        case 1:
            listaLigas = menuAdministrador(listaLigas,listaMercado,listaUsuarios);
            break;
        case 2:
            verificarUsuario(listaLigas,listaMercado,listaUsuarios);
            break;
        default:
            printf("\n Gracias por haber usado el Simulador de Mercado de FIFA 20. Nos vemos pronto!\n\n\n\n");
    }
}
