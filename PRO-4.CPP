//Programado en SublimeText3 y compilado en TurboC++
 #include <iostream.h>
 #include <stdio.h>
 #include <conio.h>
 #include <stdlib.h>
 #include <string.h> //para usar strcatÞ
 #include <ctype.h>
 #include <dos.h>
 #define lmax 25
 #define delayTime 90

char *menuBarra1[]={ " NUEVA LISTA DE PRODUCTOS ", 
		     "  CARGAR LISTA DE PRODUCTOS  ",
		     "         SALIR        "
		     };

char *menuBarra2[]={
	"ð  REGISTROS",
	" CONSULTAS ",
	"DESARROLLADOR", //"EN DESARROLLO"
	"  SALIR      "
};

char *menuRegistros[]={
	"  CARGAR PRODUCTO   ",
	"  MODIFICAR PRODUCTO",
	"  ELIMINAR PRODUCTO ",
	"  GUARDAR CAMBIOS   ",
	"  REGRESAR          "
};

char *menuConsultas[]={
	" VER LOS PRODUCTOS ",
	" BUSCAR POR NOMBRE ",
	" BUSCAR POR CODIGO ",
	" REGRESAR          "
};

char *opcionsiono[]={
	"     SI     ",
	"     NO     "
};

typedef struct dato {
	char descripcion[50];
	char marca[50];
	char proveedor[50];
	char procedencia[50];
	char seccion[50];
	char precio[50];
	char stock[50];
	char codigo[50];
	struct dato *sig;
	struct dato *ant;
};

 struct dato *p; 	  /*puntero auxiliar*/
 struct dato *final;  /* puntero al final de la lista */
 struct dato *inicio; /* puntero al inicio de la lista */
 int guardado = 0; 	  /* revisa si se ha modificado cambios en la lista */
 int nleidos = 0; 	  /* representa la cantidad de elementos presentes en la lista */
 int elimina_sm = 0;  /* elimina el archivo creado si no se han hecho modificaciones */
 


 /* -----------------------PROTOTIPO DE LAS FUNCIONES----------------------*/

 void menu_prin(void);					 /* menu principal para la crear o cargar archivo */
 void cargar(int clave);				 /* menu en donde se introduce el nombre de archivo */
 void carga(char *fname);				 /* lee el archivo y crea la lista enlazada si existen registros guardados */
 void inserta_reg(struct dato *p);		 /* inserta registros ordenadamente en la lista */
 void menu2(char *fname); 				 /* menu para crear,modificar,listar y eliminar registros */
 void agregar(void); 					 /* pide los datos del registro nuevo */
 void revisa(char *fname); 				 /* revisa si los registros de un archivo se han modificado */
 void guardar(char *fname); 			 /* guarda la lista dinÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â mica en el archivo */
 void listar(void); 					 /* busca o lista los registros que se han creado o leidos */
 void buscarnombre(void); 					 /* pide el nombre a buscar e imprime el registro si existe */
 void buscarcodigo(void);
 void eliminarcodigo(void);
 void modificarproducto(void);
 void modifica(struct dato *aux); 		 /* modifica el registro buscado */
 void elimina(struct dato *aux);
 char *minus(char nombre[]); 			 /* convierte las mayusculas en minusculas */
 struct dato *localiza2(char pcodigo[]);
 struct dato *localiza(char nombre[]);
 void libera(void);
 void desarrollo();
 void borde();
 void resalta1(int);
 void resalta2(int);
 void resalta3(int);
 void resalta4(int);
 void resalta5(int);
 void resalta6(int);
 void resalta7(int);
 void Marco(int X1,int X2,int Y1,int Y2,int sombra,char Titulo[20]);
/*******************[MAIN]***********************/
int main() {
	clrscr();
	menu_prin();
	return 1;
}

/****************[MENU PRINCIPAL]*****************/
void menu_prin(void){
	char opc;
	int y=0;
	//borde();
	do {
		clrscr();
		borde();
		textcolor(0); //0
		gotoxy(1,1);
		cprintf("%s   %s%s",
		menuBarra1[0],menuBarra1[1],menuBarra1[2]);
		textcolor(WHITE);//ADD 29 /0/
		resalta1(y); //envia el parametro y que inicializado en 0
		opc=getch();
		switch(opc){ //77 derecha    75 izquierda
			case 75: if(y==0) y=2; else y--; break;
			case 77: if(y==2) y=0; else y++; break;
			/*case 80: boton abajo
					 if(y==0){ registros(cab); break;} 
				else if(y==1){ menucons(aux); break;}
				else if(y==2){ break;} 
				else if(y==3){ band=1;break;}*/ 
			case 13: //enter
					 if(y==0){ cargar(0); break;} 
				else if(y==1){ cargar(1); break;}
				else if(y==2){ libera(); return;}
		}
	}while(1);
}

/****************[CARGAR - CREAR FICHERO]*****************/
void cargar(int clave) {
 char fname[20]; //nombre del archivo .txt
 char *cadena;
 FILE *f; //puntero a la estructura FILE
 char eleccion;
 int y=1,z=0, i, cont=5;

 cadena = new(char);

  if (clave)
  cadena = "cargar"; else
 if (!clave)
  cadena = "crear";

 elimina_sm = 0;
 for (;;) {
  clrscr();
  borde();
  textcolor(0);
  gotoxy(1,1);
  cprintf("%s   %s%s",
  menuBarra1[0],menuBarra1[1],menuBarra1[2]);
  textcolor(WHITE);//ADD 29 /0/
  if(clave){  resalta1(y); //envia el parametro 'y' que inicializado en 1
  }else resalta1(z);
  gotoxy(3,4);
  textcolor(0);
  cprintf("INTRODUZCA EL NOMBRE DEL ARCHIVO txt a %s: ",cadena);
  gets(fname);
  strcat(fname,".txt");//concatena la 2da. cadena a la variable de tipo char de 20 elementos
  f = fopen(fname,"rb");
  if (f == NULL) {/* el archivo no existe */
    if (!clave) {/* si el archivo no existe y se desea crear */
      f = fopen(fname,"wb");
      fclose(f);
      elimina_sm = 1;
      carga(fname);
      Marco(10,69,10,16,1,"");//add 14 MAYO--10-16
      gotoxy(18,13);
      textcolor(0);
      cprintf("ARCHIVO %s CREADO CON EXITO.", fname);
      gotoxy(80,25);
      getch();
      menu2(fname);
      return;
     } else if (clave) {/* si el archivo no existe y se desea a cargar */
		textcolor(0); //0
		gotoxy(1,1);
		cprintf("%s   %s%s",
		menuBarra1[0],menuBarra1[1],menuBarra1[2]);
		textcolor(WHITE);//ADD 29 /0/
		resalta1(y); //envia el parametro y inicializado en 1
      Marco(7,72,10,15,1,"");//add 14 MAYO--10-16
      gotoxy(10,12);
      textcolor(0);
      cprintf("El archivo %s no existe, verifique el nombre ingresado.", fname);
      gotoxy(10,13);
      cprintf("Presione (e) para salir o cualquier tecla para continuar");
      textcolor(WHITE);
      gotoxy(80,25);
      eleccion = tolower(getch());
      if (eleccion == 'e')
       return;
     } /**************************************************************/
   } else if (f != NULL) {/* el archivo ya existe */
    if (!clave) /* si se desea crear archivo y ya existe */
     {
	textcolor(0); //0
		gotoxy(1,1);
		cprintf("%s   %s%s",
		menuBarra1[0],menuBarra1[1],menuBarra1[2]);
		textcolor(WHITE);//ADD 29 /0/
		resalta1(z); //envia el parametro y inicializado en 1
      do {
       Marco(7,72,10,15,1,"");//add 16 MAYO--10-16
       gotoxy(10,12);
       textcolor(0);
       cprintf("El archivo %s ya existe, desea sobreescribirlo S/N : ", fname);
       gotoxy(26,13);
       cprintf("Presione (e) si quiere salir");
       textcolor(15);
       gotoxy(80,25);
       eleccion = tolower(getch());
       if (eleccion == 'e')
	return; else
       if (eleccion == 's')
       {
	f = fopen(fname,"wb");
	fclose(f);
	elimina_sm = 1;
	carga(fname);
	menu2(fname);
	return;
       } else
       if (eleccion == 'n')
	break;
	 } while (eleccion != 's');
     } else
    if (clave) {/* si se desea cargar archivo y el archivo existe */
      carga(fname);
	for(i=0;i<60;i++){//ADD
		delay(delayTime);
		gotoxy(33,8);
		cout<<"CARGANDO ARCHIVO ";
		textcolor(0);
		gotoxy(10+i,9); cprintf("°Û");//alt+219°
		cont+=5;
	   }
      Marco(10,69,10,16,1,"");//add 14 MAYO--10-16
      gotoxy(18,13);
      cprintf("ARCHIVO %s CARGADO CON EXITO.", fname);
      gotoxy(80,25);
      getch();
      menu2(fname);
      return;
     }
   }
  } /* finaliza for (;;) */
 } /* finaliza carga() */

/****************[CARGA]*****************/
void carga(char *fname) {
	FILE *f;
	int tam;
	struct dato *aux;

	p = final = inicio = NULL; //inicializa p, final, inicio en null
	f = fopen(fname, "rb"); // abre el archivo para lectura en modo binario
	rewind(f); //coloca el indicador de posicion del fichero al comienzo[rebobina]
	nleidos=0;
	for(;;) {
		aux = (struct dato *) malloc(sizeof(struct dato));
		if(fread(aux, sizeof(struct dato),1,f) !=1)
			break;
		nleidos++;
		inserta_reg(aux);
	} /*fin for*/
		fclose(f);
		if(nleidos==0)
			p=final=inicio=NULL;
}

/****************[INSERTA OPCION]*****************/
void inserta_reg(struct dato *p) {
	struct dato *aux; /*puntero auxiliar*/

	aux = inicio;
	if(inicio==NULL) { /* insertar el primer registro de una lista */
		inicio = p;
		inicio->ant=inicio;
		final=p;
		final->sig=inicio;
	} else 
		for(;;) {
			if(strcmp(p->codigo, aux->codigo) < 0) {
				if(aux == inicio) { /* insertar registro al principio de la lista */
					p->sig=aux;
					p->ant=final;
					aux->ant=p;
					final->sig=p;
					return;
				} else {
					p->ant=aux->ant; /* insertar registros en el medio de la lista */
					p->sig=aux;
					aux->ant->sig=p;
					aux->ant=p;
					return;
				} 
			} else if(aux->sig==inicio) { /* insertar registros al final de la lista */
				aux->sig=p;
				p->sig=inicio;
				inicio->ant=p;
				p->ant=aux;
				final=p;
				return;
			}
			aux=aux->sig;
	}/* fin de for(;;) */
}/* fin de la funcion */


/****************[MENU2]*****************/
void menu2(char *fname){
	int opc, opc2, y=0, z=0, band=0;
	borde();
	do {
		clrscr();
		borde();
		textcolor(0); //0
		gotoxy(5,23);
		cprintf("ARCHIVO ABIERTO: %s --- TOTAL PRODUCTOS REGISTRADOS: %d", fname, nleidos);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro 'y' inicializado en 0
		gotoxy(80,25);
		opc=getch();
		switch(opc){ //77 derecha    75 izquierda
			case 75: if(y==0) y=3; else y--; break;
			case 77: if(y==3) y=0; else y++; break;
			/*case 80: [OPCIONAL] al pulsar la flecha inferior despliega las opciones
					 if(y==0){ registros(cab); break;} 
				else if(y==1){ menucons(aux); break;}
				else if(y==2){ break;} 
				else if(y==3){ band=1;break;}*/ 
			case 13: //enter
					 if(y==0){
						int band2=0;
							  do{
								Marco(1,22,2,8,1,"");//add 11 MAYO
								for(int g=0;g<5;g++){
									textcolor(0); textbackground(15);
									gotoxy(2,3+g); cprintf(menuRegistros[g]);
								}
								resalta3(z);
								gotoxy(80,25);
								opc2=getch();
								switch(opc2){
									case 75: band2=1; break;
									case 77: band2=1; break;
									case 72: if(z==0) z=4; else z--; break;
									case 80: if(z==4) z=0; else z++; break;
									case 13: if(z==0) { agregar(); band2=1; break;}
									    else if(z==1) { modificarproducto(); band2=1; break;}
									    else if(z==2) { eliminarcodigo(); band2=1; break;}
									    else if(z==3) { guardar(fname); band2=1; break;}
									    else if(z==4) { band2=1;    break;}
								}
							  }while(band2!=1);
					  break;}
				else if(y==1){
						int band3=0;
							  do{
								Marco(20,40,2,7,1,"");//add 11 MAYO
								//clrscr();//add 1 mayo
					 		  	for(int h=0;h<4;h++){
					 		  		textcolor(0); textbackground(15);
									gotoxy(21,3+h); cprintf(menuConsultas[h]);
					 		  	}
								resalta4(z);
								gotoxy(80,25);
					 		  	opc2=getch();
					 		  	switch(opc2){
					 		  		case 75: band3=1; break;
									case 77: band3=1; break;
									case 72: if(z==0) z=3; else z--; break;
					 		  		case 80: if(z==3) z=0; else z++; break;
					 		  		case 13: if(z==0) { listar(); band3=1; break;}
					 		  		    else if(z==1) { buscarnombre(); band3=1; break;}
					 		  		    else if(z==2) { buscarcodigo(); band3=1;  break;}
					 		  		    else if(z==3) { band3=1;    break;}
					 		  	}
					 		  }while(band3!=1);					
					break;}
				else if(y==2){ desarrollo(); break;}
				else if(y==3){ band=1;break;}
		}
	} while(band!=1);
	//return;
	revisa(fname);
}

  /* --------------------PIDE LOS DATOS DEL REGISTRO NUEVO----------------- */
void agregar(void) {
	int y,x,Y=0;
	y = 7;
	x = y + 2;
	guardado=1;
	//nleidos++;
	p = new(struct dato);
	fflush(stdin); /* vacia el buffer del archivo stdin */
	borde();
	 	textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(Y); //envia el parametro y que inicializado en 0
	textcolor(RED);
	gotoxy(27,2);
	cprintf("\nC A R G A R   P R O D U C T O S\n");
	textcolor(0);
	gotoxy(x,5);  cprintf("Descripcion:     ");
	gotoxy(x,7);  cprintf("Marca:           ");
	gotoxy(x,9);  cprintf("Proveedor:       ");
	gotoxy(x,11); cprintf("Procedencia:     ");
	gotoxy(x,13); cprintf("Seccion:         ");
	gotoxy(x,15); cprintf("Precio Unitario: ");
	gotoxy(x,17); cprintf("Stock:           ");
	gotoxy(x,19); cprintf("Codigo Producto: ");
	gotoxy(x + 18,5);
	textcolor(15);
	gets(p->descripcion); gotoxy(x + 18,7);
	gets(p->marca); 	  gotoxy(x + 18,9);
	gets(p->proveedor);   gotoxy(x + 18,11);
	gets(p->procedencia); gotoxy(x + 18,13);
	gets(p->seccion);     gotoxy(x + 18,15);
	gets(p->precio);      gotoxy(x + 18,17);
	gets(p->stock); 

	struct dato *aux; //add 18 MAYO
	aux = inicio;
	int bandcodigo, bandcodigo2=0;
	do{
		bandcodigo=0;
		gotoxy(x + 18,19); gets(p->codigo); //lee el codigo ingresado por el usuario
		do{
			if(strcmp(p->codigo,aux->codigo)==0){ //compara los codigos
				bandcodigo=1; //activa la bandera si los codigos son iguales
				aux=inicio; //vuelve a iniciar aux en inicio para poder salir del ciclo
			} else {
				aux=aux->sig; //pasa al siguiente nodo, para seguir comparando los codigos
			}
		}while(aux != inicio);
	if(bandcodigo!=1){ //si el codigobandera no se activo
		    Marco(13,68,21,23,0,"");//add 14 MAYO
		    textcolor(RED);
			gotoxy(x+22,22);
			cprintf("PRODUCTO CARGADO...");
			nleidos++; //aumenta en 1 la cantidad de productos registrados
			bandcodigo2=1; //activa el codigobandera2 para salir del 1er. bucle
			gotoxy(80,25);
			textcolor(15);
			getch();
			inserta_reg(p);
		}else {
			Marco(13,68,21,23,0,"");//add 14 MAYO
		    textcolor(RED);
			gotoxy(x+19,22);
		    cprintf("EL CODIGO YA FU UTILIZADO...");
		    gotoxy(80,25);
			textcolor(15);
			getch();
		    gotoxy(x+18,19); cprintf("       ");
		    gotoxy(x+19,22); cprintf("                             ");
		}
	}while(bandcodigo2!=1);	 
}

/* --------------------MODIFICA LOS DATOS DEL REGISTRO----------------- */
void modificarproducto(void){
 char op;
 char pcodigo[50];
 struct dato *aux;
 int i, y=0;

 if (nleidos == 0) { /* comprueba que realemnte existe registros */
	clrscr();
	borde();
	gotoxy(23,20);
	printf("NO SE ENCUENTRAN REGISTROS GUARDADOS");
	gotoxy(80,25);
	getch();
	gotoxy(80,25);
	return;
 }
 for(;;) {
   borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
   gotoxy(17,3);
   textcolor(RED);
   cprintf("M O D I F I C A C I O N   D E   P R O D U C T O S");
   textcolor(0);
   gotoxy(4,5);
   cprintf("Introduzca el codigo del producto a modificar: ");
   textcolor(15);
   gets(pcodigo);

   if (!pcodigo[0])
    return;
  /* bloque de busqueda */
    aux = localiza2(pcodigo); /* busca el nombre en la lista */
if (aux) {/* si coinciden los nombres */
//borde();
    textcolor(0);
	gotoxy(15,7);  cprintf("Descripcion:     ");
	gotoxy(15,9);  cprintf("Marca:           ");
	gotoxy(15,11); cprintf("Proveedor:       ");
	gotoxy(15,13); cprintf("Procedencia:     ");
	gotoxy(15,15); cprintf("Seccion:         ");
	gotoxy(15,17); cprintf("Precio Unitario: ");
	gotoxy(15,19); cprintf("Stock:           ");
	gotoxy(15,21); cprintf("Codigo producto: ");
    textcolor(15);
	gotoxy(33,7);  cprintf(aux->descripcion);
	gotoxy(33,9);  cprintf(aux->marca);
	gotoxy(33,11); cprintf(aux->proveedor);
	gotoxy(33,13); cprintf(aux->procedencia);
	gotoxy(33,15); cprintf(aux->seccion);
	gotoxy(33,17); cprintf(aux->precio);
	gotoxy(33,19); cprintf(aux->stock);
	gotoxy(33,21); cprintf(aux->codigo);
	for (;;) {
		textcolor(RED);//ADD 16 MAYO
		gotoxy(3,23);
		cprintf("Presione (M) para modificar (ESC) para salir u otra tecla para continuar ");
		gotoxy(80,25);
		op = toupper(getch());
		if (op == 'M') {
			textcolor(15);
			modifica(aux);
			break;
			} else
			if (op == 27){
			textcolor(15);
			return;}
			else{
			textcolor(15);
			break;}
	}
} else { /* si no se encontro el codigo */
	borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
	gotoxy(19,11);
	printf("NO SE ENCONTRO REGISTROS CON ESE CODIGO");
	gotoxy(80,25);
	getch();
	return;
  } /* termina if */
 } /* termina for(;;) */
}/*FIN MODIFUCAPRODUCTO*/

/****************[LOCALIZA OPCIONES]*****************/
struct dato *localiza(char nombre[]) {
 struct dato *aux;
 register char temp2[50];
 char temp1[50];

 aux = inicio;
 strcpy(temp1,minus(nombre));

 do{
   strcpy(temp2,minus(aux->descripcion));
   if (!strcmp(temp1,temp2))
    return (aux);
   else
    aux = aux->sig;
  }while (aux != inicio);
 return (aux = NULL);
 }

/****************[LOCALIZA2 OPCIONES]*****************/
struct dato *localiza2(char pcodigo[]) {
struct dato *aux;
register char temp2[50];//registramos la variable para tener un acceso con mayor velocidad
char temp1[50];

aux = inicio;
strcpy(temp1,pcodigo); //copia el codigo buscado en temp1

do {
strcpy(temp2,aux->codigo); //copia el codigo actual a temp2
if (!strcmp(temp1,temp2)) //[COMPARA]si la funcion strcmp devuelve [0] los codigos son iguales
return (aux);
else
aux = aux->sig;//avanza, para comparar con el siguiente codigo
}while (aux != inicio);

return (aux = NULL);
}

/****************[FUNCION MODIFICA]*****************/
void modifica(struct dato *aux) {
 struct dato info;

 char op;
 int y=0, z1=0, siono;

   fflush(stdin);
   borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro 'y' inicializado en 0
   gotoxy(17,3);
   textcolor(RED);
   cprintf("M O D I F I C A C I O N   D E   P R O D U C T O S");
   textcolor(0);
   gotoxy(15,7);  cprintf("Descripcion:     ");
   gotoxy(15,9);  cprintf("Marca:           ");
   gotoxy(15,11); cprintf("Proveedor:       ");
   gotoxy(15,13); cprintf("Procedencia:     ");
   gotoxy(15,15); cprintf("Seccion:         ");
   gotoxy(15,17); cprintf("Precio Unitario: ");
   gotoxy(15,19); cprintf("Stock:           ");
   gotoxy(15,21); cprintf("Codigo producto: ");
   textcolor(15);
   gotoxy(33,7);  gets(info.descripcion);
   gotoxy(33,9);  gets(info.marca);
   gotoxy(33,11); gets(info.proveedor);
   gotoxy(33,13); gets(info.procedencia);
   gotoxy(33,15); gets(info.seccion);
   gotoxy(33,17); gets(info.precio);
   gotoxy(33,19); gets(info.stock);
   gotoxy(33,21); gets(info.codigo);
   for (;;) {
	    int bandz1=0;//13 MAYO
		Marco(14,68,17,23,0,"MODIFICAR");//add 13 MAYO
		textcolor(0);
		gotoxy(26,19); cprintf("Desea confirmar los cambios? ");
	    do{
		gotoxy(29,20); cprintf("%s%s", opcionsiono[0], opcionsiono[1]);
		textcolor(WHITE);//WHITE
		resalta6(z1);
		gotoxy(80,25);
		siono=getch();
		switch(siono){
			case 75: if(z1==0) z1=1; else z1--; break;
			case 77: if(z1==1) z1=0; else z1++; break;
			case 13: if(z1==0){ op='s'; bandz1=1; }
					 else{ 		op='n'; bandz1=1; }
		 }
		}while(bandz1!=1);
     //op = tolower(getch());
     if (op == 's'){
       guardado = 1;
       strcpy(aux->descripcion,info.descripcion);
       strcpy(aux->marca,info.marca);
       strcpy(aux->proveedor,info.proveedor);
       strcpy(aux->procedencia,info.procedencia);
       strcpy(aux->seccion,info.seccion);
       strcpy(aux->precio,info.precio);
       strcpy(aux->stock,info.stock);
       strcpy(aux->codigo,info.codigo);
       gotoxy(30,22); textcolor(RED); cprintf("CAMBIOS REALIZADOS..."); gotoxy(80,25); getch();
       textcolor(15);
       return;
      } else if (op == 'n')
      gotoxy(30,22); textcolor(RED); cprintf("CAMBIOS CANCELADOS..."); gotoxy(80,25); getch();
      textcolor(15);
      return;
    } /* fin de for(;;) */
 } /* fin de la funcion */

/* ------FUNCION ELIMINAR PRODUCTO POR CODIGO------- */
void eliminarcodigo(void){
 char op;
 char pcodigo[50];
 struct dato *aux;
 int i, y=0, z0=0, siono;

 if (nleidos == 0) { /* comprueba que realemnte existe registros */
	clrscr();
	borde();
	gotoxy(23,20);
	printf("NO SE ENCUENTRAN REGISTROS GUARDADOS");
	gotoxy(80,25);
	getch();
	gotoxy(80,25);
	return;
 }
 for(;;) {
   borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
   gotoxy(17,3);
   textcolor(RED);
   cprintf("E L I M I N A C I O N   D E   P R O D U C T O S");
   textcolor(0);
   gotoxy(12,5);
   cprintf("Introduzca el codigo del producto a eliminar: ");
   textcolor(15);
   gets(pcodigo);

   if (!pcodigo[0])
    return;
  /* bloque de busqueda */
     aux = localiza2(pcodigo); /* busca el nombre en la lista */
if (aux) {/* si coinciden los nombres */
//borde();
    textcolor(0);
	gotoxy(15,7);  cprintf("Descripcion:     ");
	gotoxy(15,9);  cprintf("Marca:           ");
	gotoxy(15,11); cprintf("Proveedor:       ");
	gotoxy(15,13); cprintf("Procedencia:     ");
	gotoxy(15,15); cprintf("Seccion:         ");
	gotoxy(15,17); cprintf("Precio Unitario: ");
	gotoxy(15,19); cprintf("Stock:           ");
	gotoxy(15,21); cprintf("Codigo producto: ");
	textcolor(15);
	gotoxy(33,7);  cprintf(aux->descripcion);
	gotoxy(33,9);  cprintf(aux->marca);
	gotoxy(33,11); cprintf(aux->proveedor);
	gotoxy(33,13); cprintf(aux->procedencia);
	gotoxy(33,15); cprintf(aux->seccion);
	gotoxy(33,17); cprintf(aux->precio);
	gotoxy(33,19); cprintf(aux->stock);
	gotoxy(33,21); cprintf(aux->codigo);
	//getch();
	for (;;) {
	    int bandz0=0;//13 MAYO
		Marco(14,68,17,23,0,"ELIMINAR");//add 13 MAYO**8--14
		textcolor(0);
		gotoxy(18,19); cprintf("Seguro que desea eliminar? "); //aux->descripcion
		textcolor(RED);
		gotoxy(45,19); cprintf(aux->descripcion);
		textcolor(15);
	    do{
		gotoxy(29,20); cprintf("%s%s", opcionsiono[0], opcionsiono[1]);//11
		textcolor(WHITE);//WHITE
		resalta6(z0);
		gotoxy(80,25);
		siono=getch();
		switch(siono){
			case 75: if(z0==0) z0=1; else z0--; break;
			case 77: if(z0==1) z0=0; else z0++; break;
			case 13: if(z0==0){
						op='s'; bandz0=1;
					} else{
						op='n'; bandz0=1;}
		 }
		}while(bandz0!=1);
		//op = toupper(getch());
		if (op == 's') {
		   guardado = 1;
		   elimina(aux);
		   textcolor(RED);
		   gotoxy(35,22);
		   cprintf("ELIMINADO...");
		   gotoxy(80,25);
		   getch();
		   nleidos--;
		   return;
		   //aux = aux->sig;
			} else
			if (op == 'n')
				textcolor(RED);
				gotoxy(35,22);
				cprintf("CANCELADO...");
				gotoxy(80,25);
				getch();
			return;
			//break;
	}
} else { /* si no se encontro el codigo */
	borde();
	gotoxy(19,11);
	printf("NO SE ENCONTRO REGISTROS CON ESE CODIGO");
	gotoxy(80,25);
	getch();
	return;
  } /* termina if */
 } /* termina for(;;) */
}/*fin eliminarcodigo*/

 /* ------ESCRIBE LOS REGISTROS EN EL ARCHIVO PARA SU POSTERIOR USO------- */
void guardar(char *fname){
 FILE *f;
 struct dato *p;
 int tam, y=0;

 tam = sizeof(struct dato);
 f = fopen(fname,"wb");
 p = inicio;
 for (;;)
  {
   fwrite(p,tam,1,f);
   p = p->sig;
   if (p == inicio)
    break;
  }
 fclose(f);
 //clrscr();
 borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
 Marco(13,68,10,16,1,"");//add 14 MAYO
 textcolor(0);
 gotoxy(25,13);
 cprintf(" SE HAN GUARDADO LOS CAMBIOS ");
 gotoxy(80,25);
 getch();
 guardado = 0;
 elimina_sm = 0;
 }

/* ----[BUSCA LOS REGISTROS PARA VER, MODIFICAR, ELIMINAR O VER EL LISTADO]---- */
void listar(void){
 char op,resp;
 struct dato *p;
 int i = 10, y=1, z2=0, siono;

 if (nleidos == 0) {
  //clrscr();
  borde();
  gotoxy(23,5);
  printf("NO SE ENCUENTRAN REGISTROS GUARDADOS");
  gotoxy(80,25);
  getch();
  return;
  }

 p = inicio;
 for (;;) {
  clrscr();
  if (nleidos == 0) {
	borde();
	gotoxy(18,10);
    printf(" SE HAN ELIMINADO TODOS LOS REGISTROS\n ");
    gotoxy(80,25);
    getch();
    inicio = p = final = NULL;
    return;
}
borde();
textcolor(0);
gotoxy(15,5);  cprintf("Descripcion:     ");
gotoxy(15,7);  cprintf("Marca:           ");
gotoxy(15,9);  cprintf("Proveedor:       ");
gotoxy(15,11); cprintf("Procedencia:     ");
gotoxy(15,13); cprintf("Seccion:         ");
gotoxy(15,15); cprintf("Precio Unitario: ");
gotoxy(15,17); cprintf("Stock:           ");
gotoxy(15,19); cprintf("Codigo producto: ");
textcolor(15);
gotoxy(33,5);  cprintf(p->descripcion);
gotoxy(33,7);  cprintf(p->marca);
gotoxy(33,9);  cprintf(p->proveedor);
gotoxy(33,11); cprintf(p->procedencia);
gotoxy(33,13); cprintf(p->seccion);
gotoxy(33,15); cprintf(p->precio);
gotoxy(33,17); cprintf(p->stock);
gotoxy(33,19); cprintf(p->codigo);
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
gotoxy(22,3);
textcolor(RED);
cprintf("L I S T A D O   D E   P R O D U C T O S");
gotoxy(i + 4,23);
cprintf("-");
gotoxy(i+29,23); cprintf("-");
gotoxy(i+44,23); cprintf("(D)");
gotoxy(i+57,23); cprintf("(ESC)");
textcolor(0);//15 add 14 mayo
gotoxy(i+7,23);  cprintf("ANTERIOR");
gotoxy(i+19,23); cprintf("SIGUIENTE");
gotoxy(i+35,23); cprintf("ELIMINAR");
gotoxy(i+51,23); cprintf("SALIR");
textcolor(15);
gotoxy(80,25);
op = toupper(getch());
  switch (op) {
    case 75: p = p->ant; break;
    case 77: p = p->sig; break;//'S'
    case 'D': {
	      for (;;){
	    int bandz2=0;//13 MAYO
		Marco(11,71,17,23,0,"ELIMINAR");//add 13 MAYO
		textcolor(0);
		gotoxy(18,19); cprintf("Seguro que desea eliminar? ");
		textcolor(RED);
		gotoxy(45,19); cprintf(p->descripcion);
		textcolor(15);
	    do{
		gotoxy(29,20); cprintf("%s%s", opcionsiono[0], opcionsiono[1]);
		textcolor(WHITE);//WHITE
		resalta5(z2);
		gotoxy(80,25);
		siono=getch();
		switch(siono){
			case 75: if(z2==0) z2=1; else z2--; break;
			case 77: if(z2==1) z2=0; else z2++; break;
			case 13: if(z2==0){ resp='s'; bandz2=1; }
				      else{ resp='n'; bandz2=1; }
		 }
		}while(bandz2!=1);

		textcolor(RED);
		textcolor(15);
		//resp = tolower(getch());
		 if (resp == 's'){
		   guardado = 1;
		   elimina(p);
		   gotoxy(35,22);
		   textcolor(RED);
		   cprintf("ELIMINADO...");
		   gotoxy(80,25);
		   getch();
		   nleidos--;
		   p = p->sig;
		   break;
		  } else
		 if (resp == 'n')
		   gotoxy(35,22);
		   textcolor(RED);
		   cprintf("CANCELADO...");
		   gotoxy(80,25);
		   getch();
		  break;
	       }
	      } break;
    case 27: return;
   } /* fin de switch */
  } /* fin de while */
 } /* fin de listar() */


 /* ------------------BUSQUEDA DE REGISTROS POR NOMBRE-------------------*/
void buscarnombre(void) {
 char op;
 char nombre[50];
 struct dato *aux;
 int i,y=1;


 if (nleidos == 0) { /* comprueba que realemnte existe registros */
	clrscr();
	borde();
	gotoxy(23,20);
	printf("NO SE ENCUENTRAN REGISTROS GUARDADOS");
	gotoxy(80,25);
	getch();
	return;
 }

 for(;;) {
   borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
   gotoxy(20,3);
   textcolor(RED);
   cprintf("B U S Q U E D A   D E   P R O D U C T O S");
   textcolor(0);
   gotoxy(3,4);
   cprintf("Introduzca el nombre del producto: ");
   textcolor(15);
   gets(nombre);
	/*for(i=0;i<60;i++){//ADD
		delay(delayTime);
		gotoxy(33,5);
		textcolor(0);
		cprintf("BUSCANDO PRODUCTO...");
		//textcolor(YELLOW);
		gotoxy(10+i,6); cprintf("°");
		cont+=5;
	}*/

   if (!nombre[0])
    return;
  /* bloque de busqueda */
     aux = localiza(nombre); /* busca el nombre en la lista */
if (aux) {/* si coinciden los nombres */
//borde();
    textcolor(0);
	gotoxy(15,6);  cprintf("Descripcion:     ");
	gotoxy(15,8);  cprintf("Marca:           ");
	gotoxy(15,10); cprintf("Proveedor:       ");
	gotoxy(15,12); cprintf("Procedencia:     ");
	gotoxy(15,14); cprintf("Seccion:         ");
	gotoxy(15,16); cprintf("Precio Unitario: ");
	gotoxy(15,18); cprintf("Stock:           ");
	gotoxy(15,20); cprintf("Codigo producto: ");
	textcolor(15);
	gotoxy(33,6);  cprintf(aux->descripcion);
	gotoxy(33,8);  cprintf(aux->marca);
	gotoxy(33,10); cprintf(aux->proveedor);
	gotoxy(33,12); cprintf(aux->procedencia);
	gotoxy(33,14); cprintf(aux->seccion);
	gotoxy(33,16); cprintf(aux->precio);
	gotoxy(33,18); cprintf(aux->stock);
	gotoxy(33,20); cprintf(aux->codigo);
	for (;;) {
		textcolor(RED);
		gotoxy(15,23);
		cprintf("Presione (ESC) para salir u otra tecla para continuar ");
		textcolor(15);
		gotoxy(80,25);
		op = toupper(getch());
		if(op == 27){
			return;
		 }
		  else
			break;
	}
} else { /* si no se encontro el nombre */
	borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
	gotoxy(19,11);
	printf("NO SE ENCONTRO REGISTROS CON ESE NOMBRE");
	gotoxy(80,25);
	getch();
	return;
  } /* termina if */
 } /* termina for(;;) */
} /* termina bloque de busqueda */

 /* ------------------BUSQUEDA DE REGISTROS POR CODIGO-------------------*/
void buscarcodigo(void){
 char op;
 char pcodigo[50];
 struct dato *aux;
 int i,y=1;

 if (nleidos == 0) { /* comprueba que realemnte existe registros */
	clrscr();
	borde();
	gotoxy(23,20);
	printf("NO SE ENCUENTRAN REGISTROS GUARDADOS");
	gotoxy(80,25);
	getch();
	return;
 }
 for(;;) {
   borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
   gotoxy(20,3);
   textcolor(RED);
   cprintf("B U S Q U E D A   D E   P R O D U C T O S");
   textcolor(0);
   gotoxy(3,4);
   cprintf("Introduzca el codigo del producto: ");
   textcolor(15);
   gets(pcodigo);

	/*for(i=0;i<60;i++){//ADD
		delay(delayTime);
		gotoxy(33,5);
		cout<<"BUSCANDO PRODUCTO...";
		//textcolor(YELLOW);
		gotoxy(10+i,6); cprintf("Û");
		cont+=5;
	}*/

   if (!pcodigo[0])
    return;
  /* bloque de busqueda */
     aux = localiza2(pcodigo); /* busca el nombre en la lista */
if (aux) {/* si coinciden los nombres */
//borde();
    textcolor(0);
	gotoxy(15,6);  cprintf("Descripcion:     ");
	gotoxy(15,8);  cprintf("Marca:           ");
	gotoxy(15,10); cprintf("Proveedor:       ");
	gotoxy(15,12); cprintf("Procedencia:     ");
	gotoxy(15,14); cprintf("Seccion:         ");
	gotoxy(15,16); cprintf("Precio Unitario: ");
	gotoxy(15,18); cprintf("Stock:           ");
	gotoxy(15,20); cprintf("Codigo producto: ");
	textcolor(15);
	gotoxy(33,6);  cprintf(aux->descripcion);
	gotoxy(33,8);  cprintf(aux->marca);
	gotoxy(33,10); cprintf(aux->proveedor);
	gotoxy(33,12); cprintf(aux->procedencia);
	gotoxy(33,14); cprintf(aux->seccion);
	gotoxy(33,16); cprintf(aux->precio);
	gotoxy(33,18); cprintf(aux->stock);
	gotoxy(33,20); cprintf(aux->codigo);
	for (;;) {
		textcolor(RED);
		gotoxy(15,23);
		cprintf("Presione (ESC) para salir u otra tecla para continuar ");
		textcolor(15);
		gotoxy(80,25);
		op = toupper(getch());
		if(op == 27){
			return;
		       }else
			break;
	}
} else { /* si no se encontro el codigo */
	borde();
			textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
	gotoxy(19,11);
	printf("NO SE ENCONTRO REGISTROS CON ESE CODIGO");
	gotoxy(80,25);
	getch();
	return;
  } /* termina if */
 } /* termina for(;;) */
}/*fin buscarcodigo*/


/****************[CONVIERTE OPCION]*****************/

 char *minus(char nombre[]){
 register int i;
 register char *temp;

 for (i = 0; i <= strlen(nombre) + 1; i++)
   temp[i] = tolower(nombre[i]);
  return(temp);
 }

/**********-----[ELIMINA OPCION]------************/
void elimina(struct dato *aux) {
  struct dato *q;

  q = aux->ant;
  q->sig = aux->sig;
  aux->sig->ant = q;
  free(aux);
 }

 /* ------[REVISA SI SE HAN HECHO CAMBIOS EN LOS REGISTROS DE LA LISTA]----- */

void revisa(char *fname) {
 char op;
 int y=3,siono;

 for (;;) {
  if (guardado == 1) {
    borde();
		textcolor(0);
		gotoxy(1,1);
		cprintf("    %s        %s         %s       %s",
		menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
		textcolor(WHITE);//ADD 29 /0/
		resalta2(y); //envia el parametro y que inicializado en 0
    Marco(9,76,10,16,1,"");//add 14 MAYO--10-16
    gotoxy(11,12);
    cprintf("LA LISTA SE HA MODIFICADO, DESEA GUARDAR LOS CAMBIOS ? [SI/NO]");
    op = tolower(getch());
    if (op == 's'){
     textcolor(RED); gotoxy(31,15); cprintf("CAMBIOS GUARDADOS..."); gotoxy(80,25); getch();
     guardar(fname);
   }else if (op == 'n') {
      if (elimina_sm == 1)
	  textcolor(RED); gotoxy(31,15); cprintf("CAMBIOS CANCELADOS..."); gotoxy(80,25); getch();
      remove(fname);
      return;
     }
   } else {
    //if (elimina_sm == 1)
     //remove(fname);
    return;
   }
  } /* fin de bucle infinito (for(;;)) */
 } /* fin de revisar(char *fname) */

/****************[LIBERA OPCION]*****************/
 void libera(void) {
 struct dato *aux;
 int y=2;

 if (inicio != NULL) {/* si realmente existe lista que ocupa espacio */
   final->sig = NULL;
   p = inicio;
   do { /* mientras que exista memoria ocupada */
     aux = p->sig;
     free(p); /* se libera la memoria ocupada */
     p = aux; /* pasa a la siguiente estructura */
    } while (p); /* fin de while */
  } /* fin de if */
     borde();
     textcolor(0);
	 gotoxy(1,1);
	 cprintf("%s   %s%s",
	 menuBarra1[0],menuBarra1[1],menuBarra1[2]);
	 textcolor(WHITE);//ADD 29 /0/
	 resalta1(y); //envia el parametro 'y' que inicializado en 2
	 Marco(13,68,10,16,1,"MEMORIA LIBERADA");//add 14 MAYO
	 textcolor(0);
     gotoxy(16,13); cprintf("La memoria utilizada en este programa fue liberada");
     gotoxy(80,25);
     getch();
 }

/****************[DESARROLLO OPCIONES]*****************/
void desarrollo(){
int y=2;
clrscr();
borde();
textcolor(0);
gotoxy(1,1);
cprintf("    %s        %s         %s       %s",
menuBarra2[0],menuBarra2[1],menuBarra2[2],menuBarra2[3]);
textcolor(WHITE);//ADD 29 /0/
resalta2(y); //envia el parametro y que inicializado en 0
Marco(10,72,7,19,0,"SOBRE ESTE PROGRAMA");//add 16 MAYO
textcolor(0);   gotoxy(12,9);  cprintf("Este programa fu‚ desarrollado por el alumno ");
textcolor(RED); gotoxy(57,9);  cprintf("Jos‚ Paredes");
textcolor(0);   gotoxy(12,10); cprintf("con la colaboraci¢n de ");
textcolor(RED); gotoxy(35,10); cprintf("Ivan Franco");
textcolor(0);	gotoxy(46,10); cprintf(", ambos alumnos del 2do.");
		gotoxy(12,11); cprintf("a¤o, 4to. m¢dulo de la carrera de Ingenier¡a Inform tica");
		gotoxy(12,12); cprintf("para la c tedra de Laboratorio I.");
textcolor(RED); gotoxy(34,14); cprintf("VERSION 1.0");
textcolor(0);   gotoxy(22,16); cprintf("Universidad Aut¢noma del Sur - UNASUR");
		gotoxy(31,17); cprintf("Asunci¢n - Paraguay");
		gotoxy(39,18); cprintf("2016");
		gotoxy(80,25);
 textcolor(15);
 getch();
}

/****************[RESALTAR OPCIONES]*****************/

void resalta1(int y) {
	//textcolor(15);
	textbackground(3);
	gotoxy(1+(y*29),1); cprintf("%s", menuBarra1[y]);//26
	//textcolor(0);
	textbackground(WHITE);//white add 13 mayo
	textcolor(0);
	       if(y==0){ gotoxy(29,23); cprintf("   Crea un nuevo fichero"); gotoxy(80,25);
	} else if(y==1){ gotoxy(29,23); cprintf("Carga un fichero ya existente"); gotoxy(80,25);
	} else if(y==2){ gotoxy(29,23); cprintf("     Salir del programa"); gotoxy(80,25); }
	textcolor(15);
}

void resalta2(int y) {
	//textcolor(15);
	textbackground(3);
	gotoxy(1+(y*20),1); cprintf("    %s   ", menuBarra2[y]);
	//textcolor(0);
	textbackground(WHITE);//white add 13 mayo
}

void resalta3(int z){
	textcolor(15);//15
	textbackground(3);
	gotoxy(2,3+z); cprintf("%s",menuRegistros[z]);
	//textcolor(0);//0
	textbackground(WHITE);//white add 13 mayo
}

void resalta4(int z){
	textcolor(15);
	textbackground(3);
	//gotoxy(20,1); cprintf("     %s   ",menuBarra2[1]);
	gotoxy(21,3+z); cprintf("%s",menuConsultas[z]);
	//textcolor(0);
	textbackground(WHITE);
}

void resalta5(int z2){
	//textcolor(15);//15
	textbackground(3);
	gotoxy(29+(z2*12),20); cprintf("%s", opcionsiono[z2]);//gotoxy(29,11);
	textbackground(WHITE);//WHITE
	textcolor(0);
}

void resalta6(int z0){
	//textcolor(15);//15
	textbackground(3);
	gotoxy(29+(z0*12),20); cprintf("%s", opcionsiono[z0]);//gotoxy(29,11);
	textbackground(WHITE);//WHITE
	textcolor(0);
}

void resalta7(int z0){
	//textcolor(15);//15
	textbackground(3);
	gotoxy(29+(z0*12),13); cprintf("%s", opcionsiono[z0]);//gotoxy(29,11);
	textbackground(WHITE);//WHITE
	//textcolor(0);
}

void Marco(int X1,int X2,int Y1,int Y2,int sombra,char Titulo[20]){
	int Cont1=0;
	int Cont2=0;
	int Medio=(X1+((X2-X1)/2)-(strlen(Titulo)/2))-1;
	for(Cont1=X1+1; Cont1<X2; Cont1++){
		gotoxy(Cont1,Y1); cprintf("Ä");//Í
		gotoxy(Cont1,Y2); cprintf("Ä");//Í
	}
	for(Cont2=Y1+1; Cont2<Y2; Cont2++){
		gotoxy(X1,Cont2); cprintf("³");//º
		gotoxy(X2,Cont2); cprintf("³");//º
	}
	for(Cont1=X1+1; Cont1<=X2-1; Cont1++){
		for(Cont2=Y1+1; Cont2<=Y2-1; Cont2++){
			gotoxy(Cont1,Cont2); cprintf(" ");
		}
	}
	gotoxy(X2,Y1); cprintf("¿");
	gotoxy(X1,Y2); cprintf("À");
	gotoxy(X1,Y1); cprintf("Ú");
	gotoxy(X2,Y2); cprintf("Ù");
	if(sombra){
		textcolor(15);
		for(int Cont1=X1+1; Cont1<=X2+1; Cont1++){
			gotoxy(Cont1,Y2+1); cprintf("°");//alt+223--alt+176
		}
		for(int Cont2=Y1+1; Cont2<=Y2+1; Cont2++){
			gotoxy(X2+1,Cont2); cprintf("°");//alt+219
		}
	}
	if(strlen(Titulo)!=0)
		gotoxy(Medio,Y1); cout <<" "<<Titulo<<" ";
}


void borde(){
clrscr();
textcolor(WHITE);//0
//textbackground(0);
window (1,1,80,25);

	for (int i=1;i<=80;i++){  //2-78
	 gotoxy(i,3);//2
	 cout<<"°";}//alt + 223  --alt + 178

	for (int j=3;j<=24;j++)	{//2-24
	gotoxy(1,j);//2
	cout<<"°";
	gotoxy(80,j);//79
	cout<<"°";}//alt + 219

	for (int k=1;k<=80;k++)	{ //2-78
	gotoxy(k,25);
	cout<<"°";}//alt + 220  Þ

	//gotoxy(79,25);//188
	//cout<<"¼";//
	//gotoxy(1,25);//200
	//cout<<"È";//

	gotoxy(2,25);
	cout<<"UNIVERSIDAD AUTONOMA DEL SUR ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿";
	gotoxy(59,25);
	cout<<"ING. INFORMATICA 2016";
	textbackground(15);
}
