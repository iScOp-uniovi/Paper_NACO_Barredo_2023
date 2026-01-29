#include "opCruGPX.h"
#include "chromosome/crPermuta.h"
#include "problem/proPermuta.h"
#include <map>
#include <set>
#include <stdexcept>

using namespace std;

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opCruGPX                   */
/*                                                                */
/******************************************************************/

opCruGPX::opCruGPX(const problema& _pr, const double& prCru)
    : opCruce<poblacion<crPermuta>, crPermuta>(prCru), pr(_pr) {}

/* Genera un unico hijo y lo almacena en cr1
   para ello escribe directamente sobre cr1
 */
void opCruGPX::cruzaParIndividuos(crPermuta& cr1, crPermuta& cr2) {
  // Get random pos

  const auto& pro_pr = dynamic_cast<const proPermuta&>(pr);
  int n_hosts = pro_pr.getHosts().size();

  // Choose random cut
  unsigned int pos = r.rnd(0, cr1.numGenes() - 1);
  set<int> en_cr1;

  // Fill the fast part of the original cr
  for (unsigned i = 0; i < pos; i++) {
    en_cr1.insert(cr1[i].first);
  }

  // Create map with task to machine
  std::map<unsigned int, unsigned int> task_to_vm;
  for (unsigned int i = pos; i < cr1.numGenes(); i++) {
    task_to_vm[cr1[pos].first] = cr1[pos].second;
  }

  // Use the second part of the parent until cr1 is complete
  for (unsigned int i = 0; i < cr2.numGenes() && pos < cr1.numGenes(); i++) {
    if (en_cr1.find(cr2[i].first) == en_cr1.end()) {
      // Replace task order
      en_cr1.insert(cr2[i].first);
      cr1[pos].first = cr2[i].first;
      const unsigned int& vm_cr2 = cr2[i].second;

      // Choose VM
      unsigned int& vm_cr1 = task_to_vm[cr2[i].first];
      if (vm_cr1 == vm_cr2) {
        if (r.frandom() <= 0.1) {
          cr1[pos].second = r.rnd(0, n_hosts - 1);
        }

      } else {
        // Coin toss
        cr1[pos].second = r.rnd(0, 1) == 0 ? vm_cr2 : vm_cr1;
      }
      pos++;
    }
  }

  //	unsigned int xp1 = r.rnd(0, cr1.numGenes()-1);
  //	unsigned int xp2 = r.rnd(0, cr1.numGenes()-1);
  //
  //
  //	// xp1 debe ser menor que xp2
  //	if(xp1 > xp2)
  //		swap(xp1, xp2);
  //
  //	//cout << "ANTES: "<<xp1<<"-"<<xp2<<endl << cr1 << endl << cr2 << endl;
  //
  //
  //	// cjto de genes en subsecuencia de cr1
  //	set<TGen> enCr1;
  //
  //	for(unsigned int x = xp1; x < xp2; x++)
  //		enCr1.insert(cr1[x]);
  //	// rellena en cr1 los elementos previos y posteriores al rango
  //[xp1..xp2) con
  //	//	los elementos restantes de cr2
  //	for(unsigned int x = 0, y = 0; x < cr2.numGenes(); x++)
  //		if(enCr1.find(cr2[x]) == enCr1.end()){
  //			if(y == xp1)
  //				y = xp2;
  //			if(y>cr1.numGenes())
  //				throw runtime_error("fuera bolos");
  //			cr1[y] = cr2[x];
  //			//cout << "cr1["<<y<<"] = "<<cr2[x]<<endl;
  //			y++;
  //		}
  //
  //	//cout << "DESPUES:"<<endl << cr1 << endl << cr2 << endl;
}
