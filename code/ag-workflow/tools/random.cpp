#include "random.h"

genRandom* genRandomSingleton::gr = NULL;
tipoSemilla genRandomSingleton::tipo = aleatoria;
tipoGenerador genRandomSingleton::tipoG = secuencia;


genRandom::genRandom(const tipoSemilla & tipo, const tipoGenerador & tipoG)
    : tSemilla(tipo),tGenerador(tipoG)
{
  // inicializamos el generador de numeros aleatorios
  
  switch(tGenerador){
      case sistema: TipoRandom = 1; break;
      case secuencia: TipoRandom = 0; break;
	
      //      default:
      //throw(valExc("genRandom::genRandom(const tipoSemilla & tipo, const tipoGenerador & tipoG)", "tGenerador"));
  };
  
  switch(tSemilla){
      case aleatoria: own_randomize(((time(NULL)%1000)/1000.0)); break;
      case fija: own_randomize(1.0); break;

      //default:
      //throw(valExc("genRandom::genRandom(const tipoSemilla & tipo, const tipoGenerador & tipoG)", "tSemilla"));
  }  
}

//---------------------------------------------------------------------------
void genRandom::advance_random()
{
  double n_random;
  for( int j1 = 1; j1 < 25; j1++){
    n_random = oldrand[j1 - 1] - oldrand[j1 + 30];
    if (n_random < 0.0)
      n_random += 1.0;
    oldrand[j1 - 1] = n_random;
  }

  for( int j1 = 25; j1 < 55; j1++){
    n_random = oldrand[j1 - 1] - oldrand[j1 - 25];
    if (n_random < 0.0)
      n_random += 1.0;
    oldrand[j1 - 1] = n_random;
  }
}

//---------------------------------------------------------------------------
void genRandom::warmup_random(double random_seed)
{
  double p_rand = random_seed;
  double n_rand = exp((double)-9);
  int ii;
  oldrand[54] = random_seed;
  for(int j1 = 1; j1 < 55; j1++){
    ii = (21 * j1)%55;
    oldrand[ii - 1 ] = n_rand;
    n_rand = p_rand - n_rand;
    if (n_rand < 0.0)
      n_rand += 1.0;
    p_rand = oldrand[ii - 1];
  }
  
  advance_random();
  advance_random();
  advance_random();
  jrand = 0;
}

//---------------------------------------------------------------------------
int genRandom::rnd(int low, int high)
{
  if (low == high)
    return low;
  
  switch(tGenerador){
      case secuencia:
      {
        int i;
      
        if (low >= high)
          return -1;
        i = (int)floor(low + frandom() *((high - low) + 1) );
      
        if (i > high)
          return(high);
        else return(i);
      }
      case sistema:
        return (low + (int)( ((double)(high-low))* rand() /(RAND_MAX + 1.0) ));
  }
  return 0;  
}

//---------------------------------------------------------------------------
void genRandom::own_randomize(double randomseed)
{

  switch(tGenerador){
      case sistema:
        if (randomseed < 1)
          srand((int)time(NULL));
        else
          srand((int) randomseed);
        break;
      case secuencia:
        warmup_random(randomseed);
        break;
  }
}

//---------------------------------------------------------------------------
double genRandom::frandom()
{
  switch(tGenerador){
      case sistema:
        return (double) rand()/(RAND_MAX+1.0);
      case secuencia:
      {
        jrand++;
        if(jrand == 55){
          jrand = 1;
          advance_random();
        }
        return(oldrand[jrand - 1]);
      }
      default:
        return 0;        
  }
  
}
 
