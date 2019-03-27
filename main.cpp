/**************************************************************************************************
    PROGRAMA DE ADMINISTRACION DE CONDOMINIOS 0.1 CREADO POR JEFFREY MUÑOZ CASTRO - AGOSTO 2016
**************************************************************************************************/

#include <iostream>     // funciones de entrada y salida
#include <cstdlib>      // funciones del sistema
#include <fstream>      // funciones para manejar archivos
#include <iomanip>      // funciones para manipular el flujo
#include <cstring>      // funcion de la clase string

using namespace std;

int recibo = 1; // variable local que asignará un comprobante a cada pag (para que cada recibo sea unico)
int comprobante = 1; // variable global de comprobante (para que cada combrobante sea unico)

/*********************************************************************************************
    ESTRUCTURAS DE REGISTROS PARA TENER MAS CONTROL SOBRE LAS VARIABLES DE LAS FUNCIONES
**********************************************************************************************/
struct FILIALES
{
    int No_Filial;
    string nombre;
};

struct COBROS
{
    int No_Filial;
    int No_Recibo;
    char mesCobro[10];
    int anioCobro;
    double montoCancelar;
};

struct Pagos
{
    int No_Filial;
    int No_Recibo;
    double montoPagado;
    int No_Comprobante;
    int diaPago;
    char mesPago[10];
    int anioPago;
};

struct historicoCobro
{
    int noFilial;
    char mesCobro[10];
    int anioCobro;
    double montoCancelar;
};

/***********************************************************************/

//PROTOTIPOS
void ingresarFilial();
bool verificarExiste(const int, string);
void generarCobros();
void registrarPago();
void filialesAlDia();
void filialesMorosas();
void pagosFilial();
void pendientesFilial();
void menu();

int main()
{

    menu();
    system("pause");
    return 0;
}

// función para ingresar la filial
void ingresarFilial()
{
    system("cls"); //limpia la pantalla

    string name;
    int codigo;
    bool var = false;

    //encabezado
    cout<<"\n\n\t\t\t***REGISTRO DE FILIALES***\n";
    cout<<"\t\t__________________________________________\n\n";

    do
    {

        cout << "\t\tPor favor ingrese el numero de filial: ";
        cin >> codigo;

        cout << "\t\tPor favor ingrese el nombre del propietario: ";
        cin >> name;

        var = verificarExiste(codigo, name);

    }while(var != true);

    system("pause");

}

//Funcion para verificar que la filial no exista
bool verificarExiste(int filial, string propietario)
{
   ofstream salida("Filiales.txt", ios::app); //se crea el archivo
   ifstream entrada("Filiales.txt");
   int a;
   string b;

   //verifica  que el archivo este bien
   if(!entrada)
   {
       cout << "\nError abriendo el archivo o el archivo no existe" << endl;
       exit(1);
   }

    //lee el archivo para buscar coincidencias
       while(entrada >> a >> b)
       {
           if(a == filial)
            {
                cout << "\n\t\tLA FILIAL YA EXISTE\n\n";
                entrada.close();
                return false;
            }
       }

    entrada.close(); //cierra el archivo de filiales

    //esta parte se ejecuta si el archivo está vacio o si la filial no existe
    //ofstream salida("Filiales.txt", ios::app);

    //verifica  que el archivo este bien
   if(!salida)
   {
       cout << "\nError abriendo el archivo o el archivo no existe" << endl;
       exit(1);
   }
    //se ingreda el registro en el archivo
    salida << filial <<" "<< propietario << endl;
    cout << "\n\t\tSE INGRESARON LOS DATOS CORRECTAMENTE\n" << endl;
    cout <<"\t\t___________________________________________\n\n\n";

    salida.close(); //cierra el archivo de filiales


    return true;

}

//funcion para generar cobro
void generarCobros()
{
    system("cls"); //limpia la pantalla

    //encabezado
    cout <<"\n\n\t\t\t***COBROS A FILIALES***"<<endl;
    cout <<"\t\t_______________________________________\n\n";

    //se crea el archivo historico de cobros
    ifstream entradaHistorico("Historico de cobros.txt", ios::app);
    // se abre en lectura el archivo de filiales
    ifstream entradaFiliales("Filiales.txt");
    // se crea el archivo de cobros
    ofstream salidaCobros("Cobros.txt", ios::app);


    //se verifica que se abra el archivo de Filiales.txt
    if(!entradaFiliales)
    {
        cout <<"\nError al abrir el archivo" << endl;
        exit(1);
    }
    //se verifica que se cree el archivo Cobros.txt
    if(!salidaCobros)
    {
        cout <<"\nError al abrir el archivo" << endl;
        exit(1);
    }

    //se cierra el archivo historico de cobros para

    // se crea una variable de tipo historicoCobros
    historicoCobro p;
    //se crean variables para recorrer el archivo historico
    char mes[10];
    int anio;
    double cantidad;

    //se seguirá preguntando mientras los datos sean erroneos
    do
    {

        cout <<"\n\t\tPor favor ingrese el mes a cobrar: ";
        cin >> mes;

        //pasa el mes a minuscula en caso de que el usuario lo haya escrito de otra manera
        for(int i=0; i != '\0'; i++)
        {
            mes[i] = tolower(mes[i]);
        }
        cout <<"\t\tPor favor ingrese el anio a cobrar: ";
        cin >> anio;

        //se recorre el archivo para verficar que el cobro no esté hecho
        while(entradaHistorico >> p.mesCobro >> p.anioCobro >> p.montoCancelar)
        {
            if(mes == p.mesCobro && anio == p.anioCobro)
            {
                cout << "\n\t\tEL COBRO YA EXISTE" << endl;
                break;
            }
        }
    }//fin del do
    while(mes == p.mesCobro && anio == p.anioCobro);

    //cierra el archivo historico de cobros y lo vuelve a abrir en modo escritura
    entradaHistorico.close();
    ofstream salidaHistorico("Historico de cobros.txt", ios::app);

        // se toma el dato de la cantidad a cobrar
        cout <<"\t\tPor favor ingrese el monto a cobrar: ";
        cin >> cantidad;

        cout<<"\n\t\tEL COBRO SE REALIZO EXITOSAMENTE\n\n";
        cout<<"\t\t___________________________________\n";

    //ingresará los datos al historico de cobros
    salidaHistorico << mes << " " << anio << " " << cantidad << endl;

    //cierra el archivo historico de cobros
    salidaHistorico.close();

    //crea variable de tipo filiales
    FILIALES f;

    //hace el respectivo cobro a todas las filiales
    while(entradaFiliales >> f.No_Filial >> f.nombre)
    {
       //ingresa el cobro al archivo de cobros
       salidaCobros << f.No_Filial << " "<< comprobante <<" "<< mes <<" "<< anio <<" "<< cantidad <<endl;
       comprobante++;  //aumenta el numero de comprobante
    }//fin del while

    //cierra el archivo de cobros
    salidaCobros.close();
    //cierra el archivo de filiales
    entradaFiliales.clear();
    entradaFiliales.close();

    system("pause");

}// fin de la funcion

//funcion para registrar un pago
void registrarPago()
{
    system("cls"); //limpia la pantalla

    //ENCABEZADO
    cout <<"\n\n\t\t\t***REGISTRO DE PAGOS***\n";
    cout <<"\t\t______________________________________\n\n";

    COBROS p;  //crea un varibale de tipo COBROS
    int numero; //variable para el numero de filial
    int pago; //monto del pago que se hará
    int diaPago, anioPago; //fecha de pago
    char  mesPago[10];
    bool var = false; //variable que indica si existe la filial o no
    historicoCobro h; //variable de tipo historico de cobros


    ifstream entrada("Cobros.txt");//Abre el archivo de cobros
    ofstream aux("Temporal.txt");  //crea un archivo temporal para modificar Cobros.txt
    ofstream salidaPago("Pagos.txt", ios::app);  //se crea el archivo con el historial de pagos
    ifstream entradaHistorial("Historico de cobros.txt");

    //comprueba que el archivo se abra sin problema
    if(!entrada)
    {
        cerr << "Error al abrir archivo";
        exit(1);
    }

    //comprueba el archivo salidaPago
    //verifica  que el archivo este bien
   if(!salidaPago)
   {
       cout << "\nError abriendo el archivo o el archivo no existe" << endl;
       exit(1);
   }

   //comprueba que el archivo se abra sin problema
    if(!entradaHistorial)
    {
        cerr << "Error al abrir archivo";
        exit(1);
    }


    cout <<"\t\tIngrese el numero de filial: "; //pide el numero de filial para validarlo luego
    cin >> numero;
    cin.ignore();

    cout << "\t\tIngrese el mes de pago: "; //pide el mes para validar que se encuentre el pago
    cin >> mesPago;
    cin.ignore();
    //pasa el mes a minuscula en caso de que el usuario lo haya escrito de otra manera
    for(int i=0; i != '\0'; i++)
    {
        mesPago[i] = tolower(mesPago[i]);
    }



    //guarda el numero de filial para buscarlo en el archivo de Cobros
    entrada >> p.No_Filial;

    while(entrada>> p.No_Recibo >> p.mesCobro >> p.anioCobro >> p.montoCancelar) //se toman los datos del archivo de cobros
    {

        //si existe el numero de filial y el mes a pagar se hace el trámite
        if((numero == p.No_Filial) && strcmp(mesPago, p.mesCobro)== 0)
        {
           //ciclo do while para verificar que el mes de pago exista
           do
           {
                //ingresar fecha de pago
                do
                {
                    cout <<"\n\t\tPor favor ingrese el dia de pago: ";
                    cin >> diaPago;
                    cin.ignore();
                }while(diaPago < 1 || diaPago > 31);

                //sí día de pago es mayor a 10 se le cambia el valor a interes
                if(diaPago > 10)
                    p.montoCancelar = (p.montoCancelar*1.1); //se le agrega el interes del 10%

                //ingreso del año
                do
                {
                    cout<<"\n\t\tPor favor ingrese el anio de pago: ";
                    cin>>anioPago;
                    cin.ignore();
                }while(anioPago < 2000 && anioPago >2100);

                //se recorre el historico de Cobros para verificar que exista el cobro
                while(entradaHistorial >> h.mesCobro>>h.anioCobro>>h.montoCancelar)
                {
                    //si los datos no coinciden se sale del ciclo y vuelve a pedir los datos
                    if(anioPago != h.anioCobro && mesPago != h.mesCobro)
                    {
                        cout <<"\n\t\tEl cobro que indica no existe, intente nuevamente"<<endl;
                        break;
                    }
                }

            }while(anioPago != h.anioCobro && mesPago != h.mesCobro);

            int auxMonto; //auxiliar para tomar el monto (ya que comparar doubles genera errrores)

            //pedirá el pago mientras sea diferente al cobro
            do
            {
                cout << "\n\t\tEl monto a cancelar es de: " << p.montoCancelar << endl;
                cout << "\n\t\tPor favor ingrese el monto del pago: ";
                cin >> pago;

                auxMonto = p.montoCancelar;  //se pasa el valor del monto a cancelar a auxMonto (int para no generar errores)


                if(pago == auxMonto)
                {
                    cout <<"\n\t\tEL PAGO SE REALIZO EXISTOSAMENTE\n"<<endl;
                    cout <<"\t\t_____________________________________\n";
                }

            }while(pago != auxMonto);

            //si el numero es igual al numero de filial se registra en el archivo de pagos
                if(numero == p.No_Filial)
                {
                    salidaPago << p.No_Filial<<" "<< p.No_Recibo <<" "<<p.montoCancelar<<" "<<comprobante<<" "<<diaPago<<" "<<mesPago<<" "<<anioPago<<endl;
                    comprobante++; //se le suma uno al comprobante
                    var = true;  //indica que si existe la filial
                }


        }//fin del IF externo


               //si no es igual al numero de filial ingresado se registra en el archivo temporal
               if(numero != p.No_Filial)
                aux << p.No_Filial<<" "<<p.No_Recibo<<" "<<p.mesCobro<<" "<<p.anioCobro<<" "<<p.montoCancelar<< endl;

                entrada >> p.No_Filial; //toma el numero de filial y continua el ciclo

    }//Fin del while externo


        //si la filial no existe lo indica
    if(var != true && entrada.eof())
    {
        cout << "\n\t\tLA FILIAL NO EXISTE O LA FILIAL ESTA AL DIA"<<endl;
        cout << "\t\t______________________________________________\n\n";
    }


    //se cierran los archivos
    entrada.close();
    aux.close();
    salidaPago.close();
    entradaHistorial.close();

    // se elimina el archivo de cobros, se renombra aux a cobros
    remove("Cobros.txt");
    rename("Temporal.txt", "Cobros.txt");

    recibo++; //se le suma 1 a la varibale global recibo

    system("pause");

}//FIN DE LA FUNCION

//funcion para mostrar filial al dia
void filialesAlDia()
{
    system("cls"); //limpia la pantalla

    //encabezado
    cout <<"\n\n\t\t\t\t***FILIALES AL DIA***\n";
    cout <<"\t\t______________________________________________________\n\n";

    //se crea variable de tipo pagos
    Pagos p;
    //crea variable de tipo FILIALES
    FILIALES f;

    //abre el archivo de filiales en modo lectura
    ifstream entradaFilial("Filiales.txt");
    //abre el archivo de pagos en modo lectura
    ifstream entradaPagos("Pagos.txt");

    //se verifica que el archivo se haya abierto sin problemas
    if(!entradaPagos)
    {
        cout <<"\nError abriendo el archivo"<<endl;
        exit(1);
    }

    //se verifica que el archivo filiales se haya abierto sin problemas
    if(!entradaFilial)
    {
        cout <<"\nError abriendo el archivo"<<endl;
        exit(1);
    }

    char mes[10]; //variable para guardar el mes

    //se pide el mes a consultar para ver los pendientes
    cout <<"\n\t\tPor favor ingrese el mes a consultar (en minuscula): ";
    cin >> mes;

    //pasa el mes a minuscula en caso de que el usuario lo haya escrito de otra manera
    for(int i=0; i != '\0'; i++)
    {
        mes[i] = tolower(mes[i]);
    }

    //muestra encabezado de las filiales al día
    cout <<"\n\t\t__________________________________________________"<<endl;
    cout <<"\t\t"<<left<<setw(10) <<"FILIAL" <<setw(20)<<"NOMBRE"<<endl<<endl;

    //mostrará todas las filiales al día
    while(entradaPagos >> p.No_Filial >> p.No_Recibo >>p.No_Comprobante>>p.montoPagado>>p.diaPago>>p.mesPago>>p.anioPago)
    {
        if(strcmp(mes, p.mesPago) == 0)
        {
            while(entradaFilial >> f.No_Filial >> f.nombre)
            {
                if((f.No_Filial) == (p.No_Filial))
                    cout <<"\t\t"<<left<<setw(10)<<f.No_Filial<<f.nombre<<endl;
            }

        }
            entradaFilial.clear();
            entradaFilial.seekg(0); // pone el cursor (apuntador al inicio del archivo

    }//fin del while

    cout <<"\n\t\t__________________________________________________"<<endl<<endl;

    //cierra los archivos
    entradaPagos.close();
    entradaFilial.close();

    system("pause");
}

//funcion para mostrar filial morosa
void filialesMorosas()
{
    system("cls"); //limpia la pantalla

    //encabezado
    cout <<"\n\n\t\t\t\t***FILIALES MOROSAS***\n";
    cout <<"\t\t_______________________________________________________\n\n";

    //se crea variable de tipo cobro
    COBROS p;
    //crea variable de tipo FILIALES
    FILIALES f;
    //se abre el archivo de cobros en lectura
    ifstream entradaCobros("Cobros.txt");
    //abre el archivo de filiales en modo lectura
    ifstream entradaFilial("Filiales.txt");

    //se verifica que el archivo se haya abierto sin problemas
    if(!entradaCobros)
    {
        cout <<"\nError abriendo el archivo"<<endl;
        exit(1);
    }

    //se verifica que el archivo filiales se haya abierto sin problemas
    if(!entradaFilial)
    {
        cout <<"\nError abriendo el archivo"<<endl;
        exit(1);
    }

    char mes[10]; //variable para guardar el mes

    //se pide el mes a consultar para ver los pendientes
    cout <<"\n\t\tPor favor ingrese el mes a consultar (en minuscula): ";
    cin >> mes;

    //pasa el mes a minuscula en caso de que el usuario lo haya escrito de otra manera
    for(int i=0; i != '\0'; i++)
    {
        mes[i] = tolower(mes[i]);
    }


    //muestra encabezado de las filiales morosas
    cout <<"\n\t\t__________________________________________________"<<endl;
    cout <<"\t\t"<<setw(11)<< "No. Filial"<<setw(10)<<"NOMBRE" <<setw(24)<<"Monto a cancelar"<<endl<<endl;

    //mostrará todas las filiales al día
    while(entradaCobros >> p.No_Filial >> p.No_Recibo >> p.mesCobro>> p.anioCobro >> p.montoCancelar)
    {

        if(strcmp(mes, p.mesCobro) == 0)
        {
            while(entradaFilial >> f.No_Filial >> f.nombre)
            {
                if((p.No_Filial) == (f.No_Filial))
                //muestra las filiales morosas
                cout<<"\t\t"<<setw(11)<<p.No_Filial<< setw(10)<<f.nombre<<setw(24)<<p.montoCancelar<<endl;
            }

        }
        entradaFilial.clear();
        entradaFilial.seekg(0); // pone el cursos (apuntador al inicio del archivo
    }//fin del while


    cout <<"\t\t__________________________________________________\n\n"<<endl;

    //cierra los archivos
    entradaCobros.close();
    entradaFilial.close();

    system("pause");
}

//funcion para mostrar pagos de una filial
void pagosFilial()
{
    system("cls"); //limpia la pantalla

    //encabezado
    cout <<"\n\n\t\t\t\t***PAGOS DE FILIAL***\n";
    cout <<"\t\t______________________________________________\n\n";

    //se abre el de pagos en modo lectura
    ifstream entradaPago("Pagos.txt");
    //se avre el archivo filiales en modo lectura
    ifstream entradaFilial("Filiales.txt");

    //se verifica que el archivo se abra sin problemas
    if(!entradaFilial)
    {
        cout << "Error abriendo el archivo"<<endl;
        exit(1);
    }

    //se verifica que el archivo se abra sin problemas
    if(!entradaPago)
    {
        cout << "Error abriendo el archivo"<<endl;
        exit(1);
    }
    //se crea una variable de tipo pago
    Pagos p;
    //se crea variable de tipo filiales
    FILIALES f;
    int numero; //numero de filial

    do
    {
        //se pide el numero de filial
        cout <<"\t\tPor favor ingrese el numero de filial: ";
        cin >> numero;

        //se busca el numero de filial
        while(entradaFilial >> f.No_Filial >> f.nombre)
        {
            //Si no coincide el numero de filial se lo indica
            if((numero != f.No_Filial) && entradaFilial.eof())
                cout <<"\t\tEl numero de filial no existe. Vuelva a interntarlo\n\n";

            if(f.No_Filial == numero)
            break;

        }

        entradaFilial.clear(); //se inicializar el indicador de archivo

    }while(numero != f.No_Filial);

    //encabezado
    cout <<"\n\t\t___________________________________________________________\n"<<endl;
    cout <<"\n\t\t***PAGOS DE LA FILIAL NO. "<<numero<<"***"<<endl << endl;
    cout <<"\t\tPROPIETARIO: "<<f.nombre<<endl<<endl;
    cout <<"\t\t"<<setw(11)<<"NO. RECIBO"<<setw(10)<<"MONTO"<<setw(15)<<"COMPROBANTE"<<setw(15)<<"FECHA"<<endl<<endl;

    //se comienza a mostrar los pagos
    while(entradaPago >> p.No_Filial >> p.No_Recibo >> p.montoPagado >> p.No_Comprobante >> p.diaPago >> p.mesPago >>p.anioPago)
    {
        if(f.No_Filial == p.No_Filial)
        cout <<"\t\t"<<setw(11)<<p.No_Recibo<<setw(10)<<p.montoPagado<<setw(15)<<p.No_Comprobante<<setw(5)<<p.diaPago<<"-"<<p.mesPago<<"-"<<p.anioPago<<endl;
    }

    cout <<"\n\t\t___________________________________________________________\n"<<endl;
    //se cierran los archivos
    entradaFilial.close();
    entradaPago.close();

    system("pause");

}//FIN DE LA FUNCION

//funcion para mostrar pendientes de una filial
void pendientesFilial()
{
    system("cls"); //limpia la pantalla

    //encabezado
    cout <<"\n\n\t\t\t\t***PENDIENTES DE FILIAL***\n";
    cout <<"\t\t________________________________________________\n\n";

    //se abre el de pagos en modo lectura
    ifstream entradaCobros("Cobros.txt");
    //se avre el archivo filiales en modo lectura
    ifstream entradaFilial("Filiales.txt");

    //se verifica que el archivo se abra sin problemas
    if(!entradaFilial)
    {
        cout << "Error abriendo el archivo"<<endl;
        exit(1);
    }

    //se verifica que el archivo se abra sin problemas
    if(!entradaCobros)
    {
        cout << "Error abriendo el archivo"<<endl;
        exit(1);
    }
    //se crea una variable de tipo pago
    COBROS c;
    //se crea variable de tipo filiales
    FILIALES f;
    int numero; //numero de filial

    do
    {
        //se pide el numero de filial
        cout <<"\t\tPor favor ingrese el numero de la filial: ";
        cin >> numero;

        //se busca el numero de filial
        while(entradaFilial >> f.No_Filial >> f.nombre)
        {
            if(numero == f.No_Filial)
                break;
        }

        //se inicializa el indicador de inicio de archivo
        entradaFilial.clear();

        //Si no coincide el numero de filial se lo indica
        if((numero != f.No_Filial) && entradaFilial.eof())
        cout <<"\t\tEl numero de filial no existe. Vuelva a interntarlo\n\n";

    }//fin dek do
    while(numero != f.No_Filial);

    //encabezado
    cout <<"\n\t\t___________________________________________________\n"<<endl;
    cout <<"\t\t***PENDIENTES DE LA FILIAL NO. "<<numero<<"***"<<endl << endl;
    cout <<"\t\tPROPIETARIO: "<<f.nombre<<endl<<endl;
    cout <<"\t\t"<<setw(11)<<"NO. RECIBO"<<setw(10)<<"MONTO"<<setw(15)<<"MES"<<setw(10)<<"ANIO"<<endl<<endl;


    //se comienza a mostrar los pagos
    while(entradaCobros >> c.No_Filial>>c.No_Recibo>>c.mesCobro>>c.anioCobro>>c.montoCancelar)
    {
        if(f.No_Filial == c.No_Filial)
        cout <<"\t\t"<<setw(11)<<c.No_Recibo<<setw(10)<<c.montoCancelar<<setw(15)<<c.mesCobro<<setw(10)<<c.anioCobro<<endl;
    }
    cout <<"\n\t\t___________________________________________________\n"<<endl;
    //se cierran los archivos
    entradaFilial.close();
    entradaCobros.close();

    system("pause");
}

//menu principal
void menu()
{

    int opcion; //variable que el usuario introducirá
    char select[10]; // variable para obtener lo que ingresa el usuario y luego validarlo

    //se crea un ciclo y se termina hasta que el usuario seleccione salir
    do
    {
        system("cls"); //limpia la pantalla

        cout <<"\t\t____________________________________________"<<endl;
        cout <<"\t\t***ADMINISTRACION DE CONDOMINIOS VER. 0.1***\n\n"; //ENCABEZADO


        //se muestran las opciones del programa
        cout <<"\t\tPor favor introduzca la opcion que desea realizar: \n\n"
             <<"\t\t1. Ingresar filial\n"
             <<"\t\t2. Generar cobro del mes\n"
             <<"\t\t3. Registrar pago de filial\n"
             <<"\t\t4. Mostrar lista de filiales al dia\n"
             <<"\t\t5. Mostrar lista de filiales morosas\n"
             <<"\t\t6. Mostrar pagos de una filial\n"
             <<"\t\t7. Mostrar pendientes de una filial\n"
             <<"\t\t8. Salir\n\n\t\t";

             //se toma la pcion digitada
            cin >> select;

            // se convierte lo ingresado a entero (si es una cadena devuelve 0)
            opcion = atoi(select);

            if(opcion == 0)
            {
                cout <<"\n\t\tNo ingreso una opcion valida. Intentelo de nuevo\n\n";
                system("pause");
            }



        //se abre un switch para llamar a la funcion que el usuario seleccionó
        switch(opcion)
        {
        case 1: ingresarFilial();
                break;
        case 2: generarCobros();
                break;
        case 3: registrarPago();
                break;
        case 4: filialesAlDia();
                break;
        case 5: filialesMorosas();
                break;
        case 6: pagosFilial();
                break;
        case 7: pendientesFilial();
                break;
        case 8: cout <<"\t\tGRACIAS POR UTILIZAR EL PROGRAMA\n\n";
                break;
        default: cout <<"\t\tNo ingreso una opcion valida. Intentelo de nuevo\n\n";
                break;
        }//FIN DEL SWITCH

    }while(opcion != 8);
}//FIN DE LA FUNCION
