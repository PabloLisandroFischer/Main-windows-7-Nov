#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QStandardItemModel>
#include <iostream>
#include <fstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("path");
    ui->lineEdit_2->setText("Palabra a buscar");
    char *auxpath="0";
    this->directorio.cargaPath(auxpath);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_commandLinkButton_clicked()
{
    QDir directory(this->ui->lineEdit->text());
    QStringList files = directory.entryList(QStringList() << "*.txt",QDir::Files);
    QStandardItemModel * model = new QStandardItemModel();
    QString path = this->ui->lineEdit->text(); //tomo el path de la ui
    QString pal = this->ui->lineEdit_2->text();
    QString PathCompleto;
    //this->directorio = new Directorio(path.toLocal8Bit().data());
    //directorio = new Directorio(path.toLocal8Bit().data());

    if(strcmp(this->directorio.getPath(), "0")==0)
    {
        this->directorio.cargaPath(path.toLocal8Bit().data());
    }// E:/archivos   E:/testarchi //1 o -1 y si son iguales me da 0
    else if (!(strcmp(this->directorio.getPath(), path.toLocal8Bit().data())==0))
    {
        this->directorio.limpiarVector();
        this->directorio.cargaPath(path.toLocal8Bit().data());
    //hacer funcion que me limpie el vector de archivos para crearlo de nuevo.
    }


    int i = 0;
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("cantidad bien"));
    model->setHorizontalHeaderItem(2, new QStandardItem("pathcompleto bien"));
    model->setHorizontalHeaderItem(3, new QStandardItem("cantidad del index"));
    model->setHorizontalHeaderItem(4, new QStandardItem("pathcompleto del index"));


    foreach(QString filename, files)
       {
           PathCompleto=directory.absoluteFilePath(files.at(i));
           this->directorio.agregarArchivo(PathCompleto.toLocal8Bit().data());
           this->directorio.InvocarCargaVec();

           //
           QStandardItem * item = new QStandardItem(filename);
           model->setItem(i, 0, item);
           //
           QStandardItem * item1 = new QStandardItem
                (QString::number(this->directorio.contarPalVecArch(pal.toLocal8Bit().data(),i)));
           model->setItem(i, 1, item1);
           //
           QStandardItem * item2 = new QStandardItem(PathCompleto);//aca esta andando mal me tira HOLA
           model->setItem(i, 2, item2);
           //
           QStandardItem * item3 = new QStandardItem
                (QString::number(this->directorio.getCantDeRepe
                             (PathCompleto.toLocal8Bit().data(),pal.toLocal8Bit().data())));
           model->setItem(i, 3, item3);
           //
           QStandardItem * item4 = new QStandardItem(this->directorio.getPath(i));//aca esta andando mal me tira HOLA
           model->setItem(i, 4, item4);

           i++;

        }



    //this->directorio.crearBinario(path.toLocal8Bit().data());

    //this->directorio.leerBinario(PathCompleto.toLocal8Bit().data());

    //this->directorio.CrearArchTxt(path.toLocal8Bit().data());
    //this->directorio.addPalEnArchTxt(path.toLocal8Bit().data(),pal.toLocal8Bit().data());

    this->ui->tableView->setModel(model);


    //this->ui->tableView->update();
//    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QVariant item = this->ui->tableView->model()->data(index);
    QString filename = this->ui->lineEdit->text() + "/" + item.toString();
    std::ifstream archivo;
    archivo.open (filename.toStdString().c_str());
    std::string line;
    std::string totalline="";
    if (archivo.is_open())
    {
        while ( getline (archivo,line) )
        {
              totalline = totalline + line + '\n';
        }
        this->ui->textEdit->setText(QString(totalline.c_str()));
    }
    archivo.close();
}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

    ModelCompleter = new QCompleter(this);
    ModelCompleter->setModel(new QDirModel(ModelCompleter));
    ui->lineEdit->setCompleter(ModelCompleter);

}


void MainWindow::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    QStringList CompletionList;
    CompletionList <<"Alexis" << "Pablo" << "Rodrigo"<<"hola"<<"mundo"
        <<"Ver"<<"Veces"<<"Embargo"<<"Partido"<<"Personas"<<"Hola"
        <<"Grupo"<<"Cuenta"<<"Pueden"<<"Tienen"<<"Misma"<<"Mundo"
        <<"Nueva"<<"Cual"<<"Fueron"<<"Mujer"<<"Frente"<<"auto"
        <<"José"<<"Tras"<<"Cosas"<<"Fin"<<"Ciudad"<<"He"<<"pato"
        <<"Social"<<"Manera"<<"Tener"<<"Sistema"<<"Será"<<"perro"
        <<"Historia"<<"Muchos"<<"Juan"<<"Tipo"<<"Cuatro"<<"gato"
        <<"Dentro"<<"Nuestro"<<"Punto"<<"Dice"<<"Ello"<<"electroencefalografista"
        <<"Cualquier"<<"Noche"<<"Aún"<<"Agua"<<"Parece"
        <<"Haber"<<"Situación"<<"Fuera"<<"Bajo"<<"Grandes"
        <<"Nuestra"<<"Ejemplo"<<"Acuerdo"<<"Habían"<<"Usted"
        <<"Estados"<<"Hizo"<<"Nadie"<<"Países"<<"Horas"
        <<"Posible"<<"Tarde"<<"Ley"<<"Importante"<<"Guerra"
        <<"Desarrollo"<<"Proceso"<<"Realidad"<<"Sentido"
        <<"Lado"<<"Mí"<<"Tu"<<"Cambio"<<"Allí"<<"Mano"
        <<"Eran"<<"Estar"<<"San"<<"Número"<<"Sociedad"
        <<"Unas"<<"Centro"<<"Padre"<<"Gente"<<"Final"
        <<"Relación"<<"Cuerpo"<<"Obra"<<"Incluso"
        <<"Través"<<"Último"<<"Madre"<<"Mis"<<"Modo"
        <<"Problema"<<"Cinco"<<"Carlos"<<"Hombres"
        <<"Información"<<"Ojos"<<"Muerte"<<"Nombre"
        <<"Algunas"<<"Público"<<"Mujeres"<<"Siglo"
        <<"Todavía"<<"Meses"<<"Mañana"<<"Esos"<<"Nosotros"
        <<"Hora"<<"Muchas"<<"Pueblo"<<"Alguna"<<"Dar"
        <<"Problema"<<"Don"<<"Da"<<"Tú"<<"Derecho"
        <<"Verdad"<<"María"<<"Unidos"<<"Podría"
        <<"Sería"<<"Junto"<<"Cabeza"<<"Aquel"
        <<"Luis"<<"Cuanto"<<"Tierra"<<"Equipo"
        <<"Segundo"<<"Director"<<"Dicho"<<"Cierto"
        <<"Casos"<<"Manos"<<"Nivel"<<"Podía"<<"Familia"
        <<"Largo"<<"Partir"<<"Falta"<<"Llegar"<<"Propio"
        <<"Ministro"<<"Cosa"<<"Primero"<<"Seguridad"
        <<"Hemos"<<"Mal"<<"Trata"<<"Algún"<<"Tuvo"
        <<"Respecto"<<"Semana"<<"Varios"<<"Real"<<"Sé"
        <<"Voz"<<"Paso"<<"Señor"<<"Mil"<<"Quienes"<<"Proyecto"
        <<"Mercado"<<"Mayoría"<<"Luz"<<"De"<<"La"<<"Que"
        <<"El"<<"En"<<"Y"<<"A"<<"Los"<<"Se"<<"Del"<<"Las"<<"Un"
        <<"Por"<<"Con"<<"No"<<"Una"<<"Su"<<"Para"<<"Es"<<"Al"<<"Lo"
        <<"Como"<<"Más"<<"O"<<"Pero"<<"Sus"<<"Le"<<"Ha"<<"Me"<<"Si"
        <<"Sin"<<"Sobre"<<"Este"<<"Ya"<<"Entre"<<"Cuando"<<"Todo"
        <<"Esta"<<"Ser"<<"Son"<<"Dos"<<"También"<<"Fue"<<"Había"
        <<"Era"<<"Muy"<<"Años"<<"Hasta"<<"Desde"<<"Está"<<"Mi"
        <<"Porque"<<"Qué"<<"Sólo"<<"Han"<<"Yo"<<"Hay"<<"Vez"<<"Puede"
        <<"Todos"<<"Así"<<"Nos"<<"Ni"<<"Parte"<<"Tiene"<<"Él"<<"Uno"
        <<"Donde"<<"Bien"<<"Tiempo"<<"Mismo"<<"Ese"<<"Ahora"<<"Cada"
        <<"E"<<"Vida"<<"Otro"<<"Después"<<"Te"<<"Otros"<<"Aunque"
        <<"Esa"<<"Eso"<<"Hace"<<"Otra"<<"Gobierno"<<"Tan"<<"Durante"
        <<"Siempre"<<"Día"<<"Tanto"<<"Ella"<<"Tres"<<"Sí"<<"Dijo"
        <<"Sido"<<"Gran"<<"País"<<"Según"<<"Menos"<<"Año"<<"Antes"
        <<"Estado"<<"Contra"<<"Sino"<<"Forma"<<"Caso"<<"Nada"<<"Hacer"
        <<"General"<<"Estaba"<<"Poco"<<"Estos"<<"Presidente"<<"Mayor"
        <<"Ante"<<"Unos"<<"Les"<<"Algo"<<"Hacia"<<"Casa"<<"Ellos"<<"Ayer"
        <<"Hecho"<<"Primera"<<"Mucho"<<"Mientras"<<"Además"<<"Quien"
        <<"Momento"<<"Millones"<<"Esto"<<"España"<<"Hombre"<<"Están"
        <<"Pues"<<"Hoy"<<"Lugar"<<"Madrid"<<"Nacional"<<"Trabajo"<<"Pesar"
        <<"Otras"<<"Mejor"<<"Nuevo"<<"Decir"<<"Algunos"<<"Entonces"
        <<"Todas"<<"Días"<<"Debe"<<"Política"<<"Cómo"<<"Casi"<<"Toda"
        <<"Tal"<<"Luego"<<"Pasado"<<"Primer"<<"Medio"<<"Va"<<"Estas"
        <<"Sea"<<"Tenía"<<"Nunca"<<"Poder"<<"Aquí"<<"Claro"<<"Iba"<<"Zona"
        <<"Éste"<<"Pesetas"<<"Orden"<<"Español"<<"Buena"<<"Quiere"
        <<"Aquella"<<"Programa"<<"Palabras"<<"Internacional"<<"Van"
        <<"Esas"<<"Segunda"<<"Empresa"<<"Puesto"<<"Ahí"<<"Propia"<<"Calle"
        <<"M"<<"Libro"<<"Igual"<<"Político"<<"Persona"<<"Últimos"
        <<"Ellas"<<"Total"<<"Creo"<<"Tengo"<<"Dios"<<"C"<<"Española"
        <<"Condiciones"<<"México"<<"Fuerza"<<"Solo"<<"Único"<<"Acción"
        <<"Amor"<<"Policía"<<"Interior"<<"Tampoco"<<"Música"<<"Ningún"<<"Vista"
        <<"Buen"<<"Hubiera"<<"Saber"<<"Obras"<<"Razón"<<"Ex"<<"Niños"<< "Puerta"
        <<"Presencia"<<"Tema"<<"Dinero"<<"Comisión"<<"Antonio"<<"Servicio"
        <<"Hijo"<<"Última"<<"Ciento"<<"Estoy"<<"Hablar"<<"Dio"<<"Minutos"
        <<"Producción"<<"Camino"<<"Seis"<<"Quién"<<"Fondo"<<"Dirección"<<"Campo"
        <<"Papel"<<"Demás"<<"Barcelona"<<"Idea"<<"Especial"<<"Diferentes"
        <<"Dado"<<"Base"<<"Capital"<<"Ambos"<<"Europa"<<"Libertad"<<"Relaciones"
        <<"Espacio"<<"Medios"<<"Ir"<<"Actual"<<"Población"<<"Empresas"<<"Estudio"
        <<"Salud"<<"Servicios"<<"Haya"<<"Principio"<<"Siendo"<<"Cultura"<<"Anterior"
        <<"Alto"<<"Media"<<"Mediante"<<"Primeros"<<"Arte"<<"Paz"<<"Sector"<<"Sabe"
        <<"Imagen"<<"Medida"<<"Deben"<<"Datos"<<"Consejo"<<"Personal"<<"Interés"<<"Julio"
        <<"Grupos"<<"Miembros"<<"Ninguna"<<"Existe"<<"Cara"<<"Edad"<<"Etc."<<"Movimiento"
        <<"Visto"<<"Llegó"<<"Puntos"<<"Actividad"<<"Bueno"<<"Uso"<<"Niño"<<"Difícil"
        <<"Joven"<<"Futuro"<<"Aquellos"<<"Mes"<<"Pronto"<<"Soy"<<"Hacía"<<"Nuevos"
        <<"Nuestros"<<"Estaban"<<"Posibilidad"<<"Sigue"<<"Cerca"<<"Resultados"<<"Educación"
        <<"Atención"<<"González"<<"Capacidad"<<"Efecto"<<"Necesario"<<"Valor"<<"Aire"
        <<"Investigación"<<"Siguiente"<<"Figura"<<"Central"<<"Comunidad"<<"Necesidad"
        <<"Serie"<<"Organización"<<"Nuevas"<<"Calidad"<<"alexis" << "pablo" << "rodrigo"<<"ver"<<"veces"<<"embargo"<<"partido"<<"personas"
        <<"grupo"<<"cuenta"<<"pueden"<<"tienen"<<"misma"
        <<"nueva"<<"cual"<<"fueron"<<"mujer"<<"frente"
        <<"josé"<<"tras"<<"cosas"<<"fin"<<"ciudad"<<"he"
        <<"social"<<"manera"<<"tener"<<"sistema"<<"será"
        <<"historia"<<"muchos"<<"juan"<<"tipo"<<"cuatro"
        <<"dentro"<<"nuestro"<<"punto"<<"dice"<<"ello"
        <<"cualquier"<<"noche"<<"aún"<<"agua"<<"parece"
        <<"haber"<<"situación"<<"fuera"<<"bajo"<<"grandes"
        <<"nuestra"<<"ejemplo"<<"acuerdo"<<"habían"<<"usted"
        <<"estados"<<"hizo"<<"nadie"<<"países"<<"horas"
        <<"posible"<<"tarde"<<"ley"<<"importante"<<"guerra"
        <<"desarrollo"<<"proceso"<<"realidad"<<"sentido"
        <<"lado"<<"mí"<<"tu"<<"cambio"<<"allí"<<"mano"
        <<"eran"<<"estar"<<"san"<<"número"<<"sociedad"
        <<"unas"<<"centro"<<"padre"<<"gente"<<"final"
        <<"relación"<<"cuerpo"<<"obra"<<"incluso"
        <<"través"<<"último"<<"madre"<<"mis"<<"modo"
        <<"problema"<<"cinco"<<"carlos"<<"hombres"
        <<"información"<<"ojos"<<"muerte"<<"nombre"
        <<"algunas"<<"público"<<"mujeres"<<"siglo"
        <<"todavía"<<"meses"<<"mañana"<<"esos"<<"nosotros"
        <<"hora"<<"muchas"<<"pueblo"<<"alguna"<<"dar"
        <<"problema"<<"don"<<"da"<<"tú"<<"derecho"
        <<"verdad"<<"maría"<<"unidos"<<"podría"
        <<"sería"<<"junto"<<"cabeza"<<"aquel"
        <<"luis"<<"cuanto"<<"tierra"<<"equipo"
        <<"segundo"<<"director"<<"dicho"<<"cierto"
        <<"casos"<<"manos"<<"nivel"<<"podía"<<"familia"
        <<"largo"<<"partir"<<"falta"<<"llegar"<<"propio"
        <<"ministro"<<"cosa"<<"primero"<<"seguridad"
        <<"hemos"<<"mal"<<"trata"<<"algún"<<"tuvo"
        <<"respecto"<<"semana"<<"varios"<<"real"<<"sé"
        <<"voz"<<"paso"<<"señor"<<"mil"<<"quienes"<<"proyecto"
        <<"mercado"<<"mayoría"<<"luz"<<"de"<<"la"<<"que"
        <<"el"<<"en"<<"y"<<"a"<<"los"<<"se"<<"del"<<"las"<<"un"
        <<"por"<<"con"<<"no"<<"una"<<"su"<<"para"<<"es"<<"al"<<"lo"
        <<"como"<<"más"<<"o"<<"pero"<<"sus"<<"le"<<"ha"<<"me"<<"si"
        <<"sin"<<"sobre"<<"este"<<"ya"<<"entre"<<"cuando"<<"todo"
        <<"esta"<<"ser"<<"son"<<"dos"<<"también"<<"fue"<<"había"
        <<"era"<<"muy"<<"años"<<"hasta"<<"desde"<<"está"<<"mi"
        <<"porque"<<"qué"<<"sólo"<<"han"<<"yo"<<"hay"<<"vez"<<"puede"
        <<"todos"<<"así"<<"nos"<<"ni"<<"parte"<<"tiene"<<"él"<<"uno"
        <<"donde"<<"bien"<<"tiempo"<<"mismo"<<"ese"<<"ahora"<<"cada"
        <<"e"<<"vida"<<"otro"<<"después"<<"te"<<"otros"<<"aunque"
        <<"esa"<<"eso"<<"hace"<<"otra"<<"gobierno"<<"tan"<<"durante"
        <<"siempre"<<"día"<<"tanto"<<"ella"<<"tres"<<"sí"<<"dijo"
        <<"sido"<<"gran"<<"país"<<"según"<<"menos"<<"año"<<"antes"
        <<"estado"<<"contra"<<"sino"<<"forma"<<"caso"<<"nada"<<"hacer"
        <<"general"<<"estaba"<<"poco"<<"estos"<<"presidente"<<"mayor"
        <<"ante"<<"unos"<<"les"<<"algo"<<"hacia"<<"casa"<<"ellos"<<"ayer"
        <<"hecho"<<"primera"<<"mucho"<<"mientras"<<"además"<<"quien"
        <<"momento"<<"millones"<<"esto"<<"españa"<<"hombre"<<"están"
        <<"pues"<<"hoy"<<"lugar"<<"madrid"<<"nacional"<<"trabajo"<<"pesar"
        <<"otras"<<"mejor"<<"nuevo"<<"decir"<<"algunos"<<"entonces"
        <<"todas"<<"días"<<"debe"<<"política"<<"cómo"<<"casi"<<"toda"
        <<"tal"<<"luego"<<"pasado"<<"primer"<<"medio"<<"va"<<"estas"
        <<"sea"<<"tenía"<<"nunca"<<"poder"<<"aquí"<<"claro"<<"iba"<<"zona"
        <<"éste"<<"pesetas"<<"orden"<<"español"<<"buena"<<"quiere"
        <<"aquella"<<"programa"<<"palabras"<<"internacional"<<"van"
        <<"esas"<<"segunda"<<"empresa"<<"puesto"<<"ahí"<<"propia"<<"calle"
        <<"m"<<"libro"<<"igual"<<"político"<<"persona"<<"últimos"
        <<"ellas"<<"total"<<"creo"<<"tengo"<<"dios"<<"c"<<"española"
        <<"condiciones"<<"méxico"<<"fuerza"<<"solo"<<"único"<<"acción"
        <<"amor"<<"policía"<<"interior"<<"tampoco"<<"música"<<"ningún"<<"vista"
        <<"buen"<<"hubiera"<<"saber"<<"obras"<<"razón"<<"ex"<<"niños"<< "puerta"
        <<"presencia"<<"tema"<<"dinero"<<"comisión"<<"antonio"<<"servicio"
        <<"hijo"<<"última"<<"ciento"<<"estoy"<<"hablar"<<"dio"<<"minutos"
        <<"producción"<<"camino"<<"seis"<<"quién"<<"fondo"<<"dirección"<<"campo"
        <<"papel"<<"demás"<<"barcelona"<<"idea"<<"especial"<<"diferentes"
        <<"dado"<<"base"<<"capital"<<"ambos"<<"europa"<<"libertad"<<"relaciones"
        <<"espacio"<<"medios"<<"ir"<<"actual"<<"población"<<"empresas"<<"estudio"
        <<"salud"<<"servicios"<<"haya"<<"principio"<<"siendo"<<"cultura"<<"anterior"
        <<"alto"<<"media"<<"mediante"<<"primeros"<<"arte"<<"paz"<<"sector"<<"sabe"
        <<"imagen"<<"medida"<<"deben"<<"datos"<<"consejo"<<"personal"<<"interés"<<"julio"
        <<"grupos"<<"miembros"<<"ninguna"<<"existe"<<"cara"<<"edad"<<"etc."<<"movimiento"
        <<"visto"<<"llegó"<<"puntos"<<"actividad"<<"bueno"<<"uso"<<"niño"<<"difícil"
        <<"joven"<<"futuro"<<"aquellos"<<"mes"<<"pronto"<<"soy"<<"hacía"<<"nuevos"
        <<"nuestros"<<"estaban"<<"posibilidad"<<"sigue"<<"cerca"<<"resultados"<<"educación"
        <<"atención"<<"gonzález"<<"capacidad"<<"efecto"<<"necesario"<<"valor"<<"aire"
        <<"investigación"<<"siguiente"<<"figura"<<"central"<<"comunidad"<<"necesidad"
        <<"serie"<<"organización"<<"nuevas"<<"calidad";

       StringCompleter = new QCompleter(CompletionList, this );
       StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
       ui->lineEdit_2->setCompleter(StringCompleter);


}

