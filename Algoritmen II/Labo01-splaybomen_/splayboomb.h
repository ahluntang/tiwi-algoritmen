#ifndef __SPLAYBOOM_H
#define __SPLAYBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include "zoekboom.h"
using namespace std;
using std::ostream;


/**********************************************************************

   klasse: splayboom
   auteur: Verstraeten Cédric
   beschrijving: Dit is een overerving van de Zoekboom klasse,
                 die ervoor zorgt dat de na het toevoegen aan de binboom
				 de splay operatie wordt uitgevoerd ahv rotaties
   
***************************************************************************/

template <class Sleutel,class Data>
class Splayboom : public Zoekboom<Sleutel,Data>{
public:
	
	// check if plaats is left child from parent or not
	bool isLeftChild(Binknoop<Sleutel,Data>*& plaats, Binknoop<Sleutel,Data>*& parent){
		return (plaats == parent->links.k);
	};
	
	// splay operatie
	void splay(Binboom<Sleutel,Data>*& plaats, Binknoop<Sleutel,Data>*& parent, Binboom<Sleutel,Data>*& debinb){
		// Not @ root 
		while(parent!=0)
		{
			//Main 1: rotate root
			// 
			if(parent->ouder==0)
			{
				// Symmetrie left child from root
				// Zig
				debinb->roteer(!isLeftChild(plaats->k,parent));
				parent = 0;
			}

			//Main 2: rotate intern
			else {
				
				Binknoop<Sleutel,Data> * grandparentcpy = parent->ouder->ouder;
				Binboom<Sleutel,Data> * grootouder = 0;
				
				if(grandparentcpy==0)
					grootouder = debinb;
				else{	
					if(isLeftChild(parent->ouder,grandparentcpy))
						grootouder = &(grandparentcpy->links);
					else
						grootouder = &(grandparentcpy->rechts);
				}
				
				// Symmetrie Parent left child from grandparent
				if(isLeftChild(parent,parent->ouder))
				{
					//
					// Main 2A: if left child from parent
					// ZigZig
					//
					if(isLeftChild(plaats->k,parent)){	
						// if mag weg als debinboom probleem opgelost
						grootouder->roteer(false);
						grootouder->roteer(false);
					}
					//
					// Main 2B: if right child from parent
					// ZigZag
					//
					else {
						parent->ouder->links.roteer(true);	
						grootouder->roteer(false);
					}
				}
				
				
				// Symmetrie Parent right child from grandparent
				else {
					//
					// Main 2A: if left child from parent
					// ZigZag
					//
					if(isLeftChild(plaats->k,parent)){
						parent->ouder->rechts.roteer(false);
						grootouder->roteer(true);
					}
					//
					// Main 2B: if right child from parent
					// ZigZig
					//
					else {
						grootouder->roteer(true);
						grootouder->roteer(true);
					}
				}
				
				// replace for while
				plaats = grootouder;	
				parent = grootouder->k->ouder;

			}
		}
	};
	
	// overide function Zoekboom
	virtual void voegtoe(const Sleutel& sl,const Data& data){
	    Binboom<Sleutel,Data>* plaats;
	    Binknoop<Sleutel,Data>* ouder;
	    zoekplaats(sl,plaats,ouder);
	    if (plaats->k == 0){
	        plaats->k=new Binknoop<Sleutel,Data>(sl,data);
	        plaats->k->ouder=ouder;
	    }
		Binboom<Sleutel,Data>* debinb = &(this->debinboom);
		splay(plaats,ouder,debinb);
	}
};

#endif



