#include "genPermuta.h"
#include "tools/traza.h"
#include "mutation/opMutSimple1.h"
#include "mutation/opMutSimple2.h"
#include "mutation/opMutAleatorio.h"
#include "generation/opGenPermuta.h"
#include "problem/proPermuta.h"
#include "selection_replacement/opSelTorneo.h"
#include "fitness/opFitOrden.h"
#include "tools/crono.h"
#include "fitness/opFitOrdenPlus.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          implementacion de la clase genPermuta                     */
/*                                                                */
/******************************************************************/

genPermuta::genPermuta()
  : fichProb(0), fichHosts(0), nCruce(2), fichPobIni(0), fichSal(0), coment(0),
    esc(0), sel(0), cru(0), mut(0), fit(0)
{}


genPermuta::~genPermuta()
{
  if(fichProb)   delete []fichProb;
  if (fichHosts)   delete[]fichHosts;
  if(fichPobIni) delete []fichPobIni;
  if(fichSal)    delete []fichSal;
  if(coment)     delete []coment;
  borraOperadores();  
}


opSeleccion<crPermuta,TFit> & genPermuta::fijaSeleccion()
{
  // Tipo de escalado
  switch(tipoEscalado){
  case 0: esc = new escCte<crPermuta,TFit>(valorEscalado); break;
  case 1: esc = new escMattfeld<crPermuta,TFit>(valorEscalado); break;
        
  default: throw(valExc("opSeleccion<crPermuta> & genPermuta::fijaSeleccion()", "esc"));
  }

  // Operador de seleccion
  switch(tipoSeleccion){
//  case 0: sel = new  opSelRuleta<crPermuta,TFit>(genRnd, *esc, tamPob); break;
  case 1: sel = new  opSelTorneo<crPermuta,TFit>(*esc, tamPob, nCruce); break;

  default: throw(valExc("opSeleccion<crPermuta> & genPermuta::fijaSeleccion()", "sel"));
  }
  
  return *sel;
}
 

opCruce<poblacion<crPermuta>,crPermuta> & genPermuta::fijaCruce(problema & prob)
{
  // Operador de cruce
  switch(tipoCruce){
//  case 0: cru = new opCruGOX(genRnd, prob.getnTrabajos(), probCruce); break;
  case 1: cru = new opCruGPX(prob, probCruce); break;
//  case 2: cru = new opCruGYT(genRnd, prob, probCruce, nCruce, delta); break;
//  case 3: cru = new opCruJOX(genRnd, prob.getnTrabajos(), probCruce); break;
//  case 4: cru = new opCruPPX(genRnd, prob.getnTrabajos(), probCruce); break;

  default: throw(valExc("opCruce<poblacion<crPermuta>,crPermuta> & genPermuta::fijaCruce(problema & prob)", "cru"));
  }
  
  return *cru;  
}


opMutacion<poblacion<crPermuta>, crPermuta> & genPermuta::fijaMutacion(problema & prob)
{
  // Operador de mutacion
  switch(tipoMutacion){
  case 0: mut = new opMutSimple1(probMut); break;
  case 1: mut = new opMutSimple2(probMut); break;
  case 2: mut = new opMutAleatorio(prob ,probMut); break;

  default: throw(valExc("opMutacion<poblacion<crPermuta>, crPermuta> & genPermuta::fijaMutacion()", "mut"));
  }
  
  return *mut;
}


opFitness<crPermuta,problema>  & genPermuta::fijaFitness(const problema & elProblema)
{
  // Operador de fitness
  switch(tipoFitness){

  case 0: fit = new opFitOrden(elProblema); break;
  case 1: fit = new opFitOrdenPlus(elProblema); break;
  default: throw(valExc("opFitness<crPermuta,problema>  & genPermuta::fijaFitness(const problema & elProblema))", "fit"));
  }

  return *fit;
}


void genPermuta::ejecuta(const char* fich)
{
  double tIni = 0; // tiempo de inicio de la prueba actual
  
  fExp = fich;

  // Leer parametros del experimento
  cargaParametros();

  // Generador de numeros aleatorios (por defecto generador por secuencia)
  genRandomSingleton::init(tipoSemilla?fija:aleatoria, secuencia);

  // Problema
  proPermuta elProblema(fichProb, fichHosts);

  // Poblacion
  poblacion<crPermuta> laPoblacion(tamPob, elProblema.getTotalItems());

  // Crear el generador de la poblacion
  OpGenPermuta opGen(elProblema, fichPobIni);

  // Crear el operador de seleccion
  opSeleccion<crPermuta,TFit> & opSel = fijaSeleccion();

  // Crear el operador de cruce
  opCruce<poblacion<crPermuta>,crPermuta> & opCru = fijaCruce(elProblema);

  // Crear el operador de mutacion
  opMutacion<poblacion<crPermuta>,crPermuta> & opMut = fijaMutacion(elProblema);

  // Crear el operador de fitness
  opFitness<crPermuta,problema> & opFit = fijaFitness(elProblema);

  // Traza
  traza<TFit,poblacion<crPermuta>,crPermuta,problema> trz(numPruebas, numGen);

//  // Cromosoma para usar elitismo
//  crPermuta Elite(elProblema.getnTrabajos());

#ifdef PROGRESO
  unsigned int signal = numPruebas*numGen/100;
#endif

  for(unsigned int nPrueba = 0; nPrueba < numPruebas; nPrueba++){
    iter = 0; // Generacion actual

    cout << nPrueba;

    // si el operador de fitness lleva busqueda local se muestran los vecinos generados
    opFitnessBL<crPermuta,problema>* opFBL =
        dynamic_cast<opFitnessBL<crPermuta,problema>*>(&opFit);
    if(opFBL)
      cout <<"("<<opFBL->getVecinosEvaluados()<<")";

    cout<< endl;


	
    // restriccion de tiempo
    if(maxSecs > 0){
		crono::setTick();
    }
    
   




	    
    //////////////////////////////////////
    ////// EJECUCION DEL GENETICO ////////
    //////////////////////////////////////

    // Traza
    trz.iniciaPrueba(nPrueba);

    // Generar poblacion inicial
    opGen.aplica(laPoblacion); //  cout << "opGen:"<<endl << laPoblacion << endl << endl;

    // Evaluar la poblacion
    opFit.aplica(laPoblacion);	//cout << "opFit:"<<endl << laPoblacion << endl << endl;

    ofstream initial_population;
    initial_population.open("initial_population.txt");
    initial_population << laPoblacion;
    initial_population.close();

    // Traza
    trz.actualizaPrueba(nPrueba, 0, laPoblacion);

    // Avanzar la generacion
    ++iter;

    while(iter < numGen){
      //     cout << "    iter:"<< iter << endl;
      // restricion de tiempo
		
      if(maxSecs >0){
	
		  if(crono::readTick() >= maxSecs/numPruebas){
	  cout << "Superados los "<<maxSecs/numPruebas<<" segs en iteracion: " << iter << endl;
	  break; // si se excede el tiempo limite finalizamos la prueba actual
	}
      }
	  
	    
//      // Guardar el mejor cromosoma (para hacer elitismo)
//      Elite=laPoblacion[laPoblacion.mejorIndividuo()];

      // Aplicar seleccion
      opSel.aplica(laPoblacion); //cout << "opSel1:"<<endl << laPoblacion << endl << endl;

      // Aplicar cruce
      opCru.aplica(laPoblacion);

      // Aplicar mutacion
      opMut.aplica(laPoblacion);

      // Recuperar el cromosoma Elite
//      if (laPoblacion.mejorIndividuo()==laPoblacion.totalIndividuos()) {
//        laPoblacion[0]=Elite;
//        laPoblacion.actualizaMejor(0);
//      }
//      else {
//        laPoblacion[laPoblacion.mejorIndividuo()]=Elite;
//      }

      // Evaluar la poblacion
      opFit.aplica(laPoblacion); //cout << "PRE opSel:"<<endl << laPoblacion << endl << endl;

      // Aplicar de nuevo operador de seleccion (ej.: seleccion por torneo)
      opSel.aplica2(laPoblacion); //cout << "opSel:"<<endl << laPoblacion << endl << endl;

      // Traza
      trz.actualizaPrueba(nPrueba, iter, laPoblacion);

      // Avanzar a la siguiente generacion
      ++iter;

#ifdef PROGRESO
      if(iter % signal == 0)
	kill(getppid(), SIGUSR1);
#endif
    }


    // Traza
    trz.finPrueba(nPrueba, laPoblacion, opFit, opCru);
  }

  // Traza - genera salida
  trz.finaliza(elProblema, laPoblacion, fichSal, *this);
}


void genPermuta::cargaParametros(){
  ifstream f; // Fichero del experimento
  char aux[500];

  f.open(fExp);
  if(!f.good())
    throw(fichExc("void genPermuta::cargaParametros()", fExp));

  // Leer nombre del fichero del problema
  filtraComentario(f);
  f.getline(aux,500,'\n');
  fichProb = _strdup(aux);

  // Leer nombre del fichero de infraestructura
  filtraComentario(f);
  f.getline(aux, 500, '\n');
  fichHosts = _strdup(aux);
  cout << "Fichero infraestructura: <" << aux << ">" << endl;
  // Leer probabilidad de cruce
  filtraComentario(f);
  f >> probCruce;
  if(probCruce > 1)
    throw(valExc("void genPermuta::cargaParametros()", "probCruce"));

  // Leer probabilidad de mutacion
  filtraComentario(f);
  f >> probMut;
  if(probMut > 1)   
    throw(valExc("void genPermuta::cargaParametros()", "probMut"));

  // Leer tama�o de la poblacion
  filtraComentario(f);
  f >> tamPob;

  // Leer numero de generaciones
  filtraComentario(f);
  f >> numGen;

  // Leer numero de pruebas
  filtraComentario(f);
  f >> numPruebas;

  // Leer tipo de seleccion
  filtraComentario(f);
  f.getline(aux,500,'\n');

/*  if(!strcmp(aux,"Ruleta") )
    tipoSeleccion = 0;
  else
*/   if(!strcmp(aux, "Torneo") )
    tipoSeleccion = 1;
  else
    throw(valExc("void genPermuta::cargaParametros()", "tipoSeleccion("+string(aux)+")"));

  // Leer tipo de cruce
  filtraComentario(f);
  f.getline(aux,500,'\n');

  if(!strcmp(aux,"GOX") )
    tipoCruce = 0;
  else if(!strcmp(aux,"GPX") )
    tipoCruce = 1;
  else if(!strcmp(aux, "GYT") )
    tipoCruce = 2;
  else if(!strcmp(aux,"JOX") )
    tipoCruce = 3;
  else if(!strcmp(aux,"PPX") )
    tipoCruce = 4;
  else
    throw(valExc("void genPermuta::cargaParametros()", "tipoCruce"));

  // Leer tipo de mutacion
  filtraComentario(f);
  f.getline(aux,500,'\n');

  if(!strcmp(aux,"Simple1") )
    tipoMutacion = 0;
  else if(!strcmp(aux,"Simple2") )
    tipoMutacion = 1;
  else if(!strcmp(aux,"Aleatorio") )
    tipoMutacion = 2;
  else
    throw(valExc("void genPermuta::cargaParametros()", "tipoMutacion"));

  // Leer tipo de fitness
  filtraComentario(f);
  f.getline(aux,500,'\n');
  if(!strcmp(aux,"ORDEN") )
    tipoFitness = 0;
  else
      if(!strcmp(aux,"ORDENPLUS") )
    tipoFitness = 1;
  else
      if(!strcmp(aux,"OTRO") )
      tipoFitness = 2;
  
  
  else
    throw(valExc("void genPermuta::cargaParametros()", "tipoFitness"));

  // Leer el numero de cromosomas a cruzar para el cruce GYT
  filtraComentario(f);
  if(tipoCruce == 2)
    f >> nCruce;
  else
    filtraComentario(f, false);
  if(nCruce < 2)
    throw(valExc("void genPermuta::cargaParametros()", "nCruce"));


  // Leer el tipo de semilla (0 aleatoria, 1 fija)
  filtraComentario(f);
  f >> tipoSemilla;
  if(probMut > 1)
    throw(valExc("void genPermuta::cargaParametros()", "tipoSemilla"));

  // Leer el tipo de escalado (0 cte, 1 mattfeld) y valor
  filtraComentario(f);
  f >> tipoEscalado;
  f >> valorEscalado;
/*  if(!(valorEscalado==TFit()))
    valorEscalado = 1/valorEscalado;
  if(valorEscalado < TFit(0,0,0))
    throw(valExc("void genPermuta::cargaParametros()", "valorEscalado"));
*/
  // Leer la poblacion inicial
  filtraComentario(f);
  f.getline(aux,500,'\n');
  filtraComentario(f);
  if(aux[0] == '0')
    filtraComentario(f, false);
  else{
    f.getline(aux,500,'\n');
    if(aux[0] != '0')
      fichPobIni = _strdup(aux);
  }

  // Leer el nombre del fichero de salida
  filtraComentario(f);
  f.getline(aux,500,'\n');
  if(aux[0] != '0')
    fichSal = _strdup(aux);
  else{
    fichSal = _strdup("resultados.txt");
  }

  // Leer comentario del problema
  filtraComentario(f);
  f.getline(aux,500,'\n');
  coment = _strdup(aux);

  // Porcentaje poblacion para busqueda local
  filtraComentario(f);
  f >> perctBL;
  cout << "perctBL:" << perctBL <<endl;

  // % de iteraciones entre aplicaciones consecutivas de la BL
  f >> niterBL;
  cout << "%iterBL:" << niterBL <<endl;

  // tiempo limite 
  filtraComentario(f);
  f >> maxSecs;
  cout << "maxSecs:" << maxSecs <<endl;

   f.close();
}


void genPermuta::filtraComentario(ifstream & f,bool formal)
{
  char c;

  // Buscar inicio comentario formal
  if(formal)
    do{ 
      c = f.get();
      if(c == '/')
        c = f.get();
    } while(c != '/');
  
  // Buscar fin de linea
  do {
    c = f.get();
  }while(c != '\n');
}


void genPermuta::borraOperadores()
{
  // Eliminar operadores
  if (fit) delete  fit;
  if (sel) delete  sel;
  if (esc) delete  esc;
  if (cru) delete  cru;
  if (mut) delete  mut;
}
                                   
void genPermuta::tabla(ostream &out) const
{
 out << tamPob <<":"<< numGen << ":" << numPruebas << ":" << probCruce << ":";
 out << probMut << ":";
 switch(tipoSeleccion){
   case 0: out << "ruleta";
   break;
   case 1: out << "torneo";
   break;
 };
 out << ":";
 switch(tipoCruce){
   case 0: out << "gox";
   break;
   case 1: out << "gpx";
   break;
   case 2: out << "gyt";
   break;
   case 3: out << "jox";
   break;
   case 4: out << "ppx";
   break;
 };
 out << ":";
 switch(tipoMutacion){
   case 0: out << "simple1";
   break;
   case 1: out << "simple2";
   break;
   case 2: out << "aleatorio";
   break;
 };
 out << ":";
 switch(tipoFitness){
 case 0: out << "ORDEN";
   break;
 case 1: out << "bl";
   break;
 case 2: out << "D("<<objetivo<<")";
   break;
 case 3: out << "L("<<objetivo<<")";
   break;
 case 4: out << "BLyBrucker";
   break;
 case 5: out << "escalada";
   break;
 case 6: out << "GYT(f2)";
   break;
 case 7: out << "GYT(f3)";
   break;
 case 8: out << "GYT(f4)";
   break;

 };
 out << endl;


}
