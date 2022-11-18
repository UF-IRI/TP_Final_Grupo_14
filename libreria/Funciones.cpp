#define _CRT_SECURE_NO_WARNINGS
#include "Funciones.h"
#include <string>

bool chequearfechas(ultConsulta Consulta)
{
    time_t auxiliar_fecha = time(0);
    tm* hoy = localtime(&auxiliar_fecha);
    tm fecha_hoy;
    fecha_hoy.tm_mday = hoy->tm_mday;
    fecha_hoy.tm_mon = hoy->tm_mon;
    fecha_hoy.tm_year = hoy->tm_year;
    int dif = 0;//

    time_t aux_fin = mktime(&fecha_hoy);
    time_t aux_inicio = mktime(&(Consulta.consulta.fecha));

    dif = difftime(aux_fin, aux_inicio) / (31536000); //calculo la diferencia de tiempo en segundos y lo transformamos a anios

    if (dif > 10)
        return false;//no puede volver
    else
        return true; //puede volver
}
void guardararchivo(fstream& archivo, Paciente pac)
{
    string aux;
    if (archivo.is_open())
    {
        getline(archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            archivo << "Dni" << ',' << "Nombre" << ',' << "Apellido" << ',' << "Sexo" << ',' << "Natalicio" << ',' << "Estado" << ',' << "id" << endl;
        }
        else
        {
            archivo << pac.nombre << ',' << pac.apellido << ',' << pac.sexo << ',' << pac.nacimiento.fecha.tm_mday << '/' << pac.nacimiento.fecha.tm_mon << '/' << pac.nacimiento.fecha.tm_year << '/' << pac.estado << ',' << pac.dni << endl; //todo preguntar
        }
        
    }
   
}
ultConsulta chequearUltFechaConsulta(Paciente pac, fstream& ArchConsultas)
{
	int dif;
	int n = 0;
	string encabezado;
	ultimaConsulta* aux = new ultimaConsulta[n];
	char coma = ',';
    char barra = '/';
    int i = 0;
	while (ArchConsultas)
	{
		if (i == 0) 
        {
			ArchConsultas >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> barra >> encabezado >> barra >> encabezado >> coma >> encabezado >> coma >> encabezado;
			i++;
		}
		ArchConsultas >> aux[i].dni_pac >> coma >> aux[i].consulta.fecha.tm_mday >> barra >> aux[i].consulta.fecha.tm_mon >> barra >> aux[i].consulta.fecha.tm_year >> barra >> aux[i].fecha_turno.fecha.tm_mday >> barra >> aux[i].fecha_turno.fecha.tm_mon >> barra >> aux[i].fecha_turno.fecha.tm_year >> barra >> aux[i].presento >> coma >> aux[i].matricula_med;
		resizeConsultas(aux,&n);
        i++;
	}
    for(int j=0;j<n;j++){
        if(aux[j].dni_pac==pac.dni) //la primera que se cumple es la ultima
        {
            return aux[j];
        }
    }
}
Paciente buscarPaciente(fstream& Archivocompleto, string _id) {
    char coma = ',';
    char barra = '/';
    Paciente aux;
    Paciente aux1;
    string encabezado;
    int i = 0;
    while (Archivocompleto)
    {
        if (i == 0)
        {
            Archivocompleto>>encabezado >> coma >> encabezado >> encabezado >> encabezado>> coma >> encabezado >> coma >> encabezado >> barra >> encabezado >> barra >>encabezado >> coma >>encabezado >> coma >> encabezado;
            i++;
        }
        Archivocompleto >> aux.dni >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.sexo >> coma >> aux.nacimiento.fecha.tm_mday >> barra >> aux.nacimiento.fecha.tm_mon >> barra >> aux.nacimiento.fecha.tm_year >> coma >> aux.estado >> coma >> aux.obra_social;
        if (aux.dni == _id)
        {
            aux1 = aux;
            return aux1;
        }
       
    }
    
     aux1.dni= "404";//not found
     return aux1;

}


void recuperarPaciente(fstream& ArchivoConsultas, fstream& ArchivoCompleto, fstream& Archivados, fstream& ArchivoPacientes, fstream& Archivocontactos) {
    ultimaConsulta aux;
    char coma = ',';
    char barra = '/';
    string encabezado;
    ArchivoConsultas >> encabezado >> coma >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> coma >> encabezado;//todo ver
    ArchivoConsultas >> aux.dni_pac >> coma >> aux.consulta.fecha.tm_mday >> barra >> aux.consulta.fecha.tm_mon >> barra >> aux.consulta.fecha.tm_year >> barra >> aux.fecha_turno.fecha.tm_mday >> barra >> aux.fecha_turno.fecha.tm_mon >> barra >> aux.fecha_turno.fecha.tm_year >> barra >> aux.presento >> coma >> aux.matricula_med; //posible error?
    paciente Pac = buscarPaciente(ArchivoCompleto, aux.dni_pac);
    ultConsulta aux2 = chequearUltFechaConsulta(Pac, ArchivoConsultas);
    if (Pac.dni == "404") //si el paciente esta vacio quiere decir q no lo encontre, aca hay q ver tema punteros.
    {
        cout << "No se encontro el paciente" << endl;
    }

    else if (chequearfechas(aux2) == true && Pac.asistencia == false) {
        if (Pac.estado == "fallecido") 
        {
            Pac.archivado = "Archivado";
            guardararchivo(Archivados, Pac); //lo mando al archivo q no se recuperan
        }
        else if (Pac.estado == "internado") 
        {
            cout << "El paciente se encuentra internado " << endl;
            guardararchivo(ArchivoPacientes, Pac);
        }
        else {
            informarsecretaria(Pac,Archivados,Archivocontactos); //se lo mando a secretaria para preguntarle al paciente si vuelve
            // lo guardo para despues preguntar si vuelve
        }
    }// si pasaron menos de 10 años y no reprogramo puede volver
}

bool informarsecretaria(Paciente pac, fstream& Archivados, fstream& Archivocontactos, fstream& archivopacientes)
{
    int n = 0;
    Contacto* contactoaux = new Contacto[n];
    Contacto contact;
    string aux;
    string encabezado;
    Paciente auxx;
    char coma = ',';
    int i = 0;
    int falso = -1;
    bool hola = vincularcontacto(pac, Archivocontactos); //funciona, puedo hacerlo por izquierda,falta vincular cont
    
    if (hola == true)
    {
       
        cout << "Llamando al paciente: " << pac.nombre << pac.apellido << "Su numero es: " << contact.celular << endl;
        cout << "Vuelve";
        cin >> aux;
        if (aux == "si" || aux == "Si" || aux == "SI" || aux == "sI")
        {
            cout << "Vuelve el paciente";
            pac.retorno = true;
            cout << "ingrese su nueva obra social";
            if (pac.obra_social != aux)
            {
                pac.obra_social = aux;
            }
            guardararchivo(archivopacientes, pac);
            return true;
        }
        else
        {
            cout << "No vuelve el paciente";
            pac.archivado = "archivado";
            guardararchivo(Archivados, pac);
            return false;
        }
    }
    else
        return false;

}
void guardararchivocontacto(fstream &Archivo, contacto Contacto)
{
    string aux;
    char coma = ',';
    if (Archivo.is_open())
    {
        getline(Archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            Archivo << "Dni" << coma << "telefono" << coma << "celular" << coma << "direccion" << coma << "mail" << endl;
        }
        else
        {
            Archivo << Contacto.dni_pac << coma << Contacto.telefono << coma << Contacto.celular << coma << Contacto.direccion << coma << Contacto.email << endl; //todo preguntar
        }
    }

}
void guardarmedicos(fstream &Archivo, medico medico)
{
    string aux;
    char coma = ',';
    if (Archivo.is_open())
    {
        getline(Archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            Archivo << "matricula" << coma << "nombre" << coma << "apellido" << coma << "telefono" << coma << "especialidad" << coma << "activo" << endl;
        }
        else
        {
            Archivo << medico.matricula << coma << medico.nombre << coma << medico.apellido << coma << medico.telefono << coma << medico.especialidad << coma << medico.activo << endl; //todo preguntar
        }
    }
}
void resizecontacto(Contacto*& vector, int* n)
{
    *n = *(n)+1; //aumento en uno mi contador de tamanio
    Contacto* aux = new Contacto[*(n)]; //me hago un auxiliar con un nuevo tamanio

    for (int i = 0; i < *n - 1; i++) //es hasta n-1 ya que mi vector todavia tiene tamanio n
    {
        aux[i] = vector[i]; //copio las cosas en el auxiliar
    }
    delete[]vector; //libero la memoria de donde estaba vector

    vector = aux; //le asigno la nueva memoria
}

void resizeMedico(Medico*& vector, int* n)
{
    *n = *(n)+1;
    Medico* aux = new Medico[*(n)];

    for (int i = 0; i < *n - 1; i++)
    {
        aux[i] = vector[i];
    }
    delete[]vector; 
    vector = aux; 
}

void resizeConsultas (ultimaConsulta*& vector, int* n)
{
    *n = *(n)+1;
    
    ultimaConsulta* aux = new ultimaConsulta[*(n)];

    for (int i = 0; i < *n - 1; i++)
    {
        aux[i] = vector[i];
    }
    delete[]vector; 
    vector = aux; 
}

bool vincularcontacto(Paciente pac, fstream& Archivocontactos) //puede desreferenciar 
{
    int n = 1;
    string aux;
    string encabezado;
    Contacto* contactoaux = new Contacto[n];
    char coma = ',';
    int i = 0;
    int falso = -1;
    Contacto contact;
    if (!Archivocontactos.is_open())
    {
        return false;
    }
    else {
        while (Archivocontactos) {
            if (i == 0)
            {
                Archivocontactos >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado;
                i++;
            }
            else
            {
                Archivocontactos >> contactoaux[n].dni_pac >> coma >> contactoaux[n].telefono >> coma >> contactoaux[n].celular >> coma >> contactoaux[n].direccion >> coma >> contactoaux[n].email;
                resizecontacto(contactoaux, &n);
            }
        }
        for (int k = 0; k < n; k++)
        {
            if (contactoaux[k].dni_pac == pac.dni)
            {
                contact = contactoaux[k];
                falso = 9;
                return true;
            }
            else return false;

            //hubo un problema para encontrar el contacto del paciente
        }
    }
}

bool archivarmedico(fstream& archivomedicoslistados, Paciente pac, fstream& archivo, fstream& consultas)
{
    
    int i = 0;
    string encabezado;
    int n = 1;
    ultimaConsulta* consultasaux = new ultimaConsulta[n];
    int m = 1;
    Medico* medicoaux = new Medico[m];
    char coma = ',';
    char barra = '/';
    Medico pasar;
    if (archivo.is_open())
    {
        while (!archivo.eof())
        {
            if (i == 0)
            {
                archivo >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado;
                i++;
            }
            else
            {
                archivo >> medicoaux[m].matricula >> coma >> medicoaux[m].nombre >> coma >> medicoaux[m].apellido >> coma >> medicoaux[m].telefono >> coma >> medicoaux[m].especialidad >> medicoaux[m].activo;
                resizeMedico(medicoaux, &m);
            }
        }
    }
    i = 0;
    if (consultas.is_open())
    {
        while (!consultas.eof())
        {
            if (i == 0)
            {
                consultas >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado;
                i++;
            }
            else
            {
                consultas >> consultasaux[n].dni_pac >> coma >> consultasaux[n].consulta.fecha.tm_mday >> barra >> consultasaux[n].consulta.fecha.tm_mon >> barra >> consultasaux[n].consulta.fecha.tm_year >> consultasaux[n].fecha_turno.fecha.tm_mday >> barra >> consultasaux[n].fecha_turno.fecha.tm_mon >> barra >> consultasaux[n].fecha_turno.fecha.tm_year >> coma >> consultasaux[n].presento >> coma >> consultasaux[n].matricula_med;
                resizeConsultas(consultasaux, &n);
            }
        }

    }
    for (int w = 0; w < n; w++)
    {
        for (int k = 0; k < m; k++)
        {
            
            if (chequearconymed(medicoaux[k], consultasaux[w])==true)
            {
                pasar = medicoaux[k];
            }
        }
    }
    if (pasar.activo == true)
    {
        string primerlinea;
        if (archivomedicoslistados.is_open())
        {
            while (!archivomedicoslistados.eof())
            {
                getline(archivomedicoslistados, primerlinea);
                if (primerlinea == "\0")
                {
                    archivomedicoslistados << "matricula" << ',' << "nombre" << ',' << "apellido" << ',' << "telefono" << ',' << "especialidad" << ',' << "activo" << endl;
                }
                else
                {
                   
                    archivomedicoslistados << pasar.matricula << ',' << pasar.nombre << ',' << pasar.apellido << ',' << pasar.telefono << ',' << pasar.especialidad << ',' << pasar.activo << endl;
                    return true;

                }
               
            }
        }

    }

}

bool chequearconymed(Medico med,ultimaConsulta consulta)
{
    if (med.matricula == consulta.matricula_med)
    {
        return true;
    }
    else return false;
}