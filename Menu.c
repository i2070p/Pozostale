#include <stdio.h>
#include <stdlib.h>

struct Menu {
    unsigned char iloscOpcji;
	char * opcja; 
	struct Menu ** podMenu;
};


struct Menu* robMenu(int rozmiar, char *opcja) {
	struct Menu* noweMenu = (struct Menu*) malloc(sizeof(struct Menu));
	
	noweMenu->opcja=opcja;
	noweMenu->iloscOpcji=rozmiar;
    if (rozmiar!=0) {
       noweMenu->podMenu = (struct Menu**) malloc(sizeof(struct Menu*)*rozmiar);
    } else {
      noweMenu->podMenu=NULL;
    }
	return(noweMenu);
}

void dodajSubMenu(int indeks, struct Menu* menu, struct Menu *subMenu) {
	menu->podMenu[indeks]=subMenu;
}
/**te funkcje se musisz dostosowac do warunkow uC i swojego LCD**/
void wyswietlMenu(struct Menu * menu) {
     unsigned char i=0;
     for (i=0; i<menu->iloscOpcji; i++) {
         printf("%s\n", menu->podMenu[i]->opcja);    
     }
}

int main(int argc, char *argv[])
{
  /**przyklad towrzenia prostego menu**/
 
  //tworzymy 3 elementowe "menu glowne" 
  struct Menu * glowne = robMenu(3, "Glowne");
  
  //tworzymy 3 elementy dla menu glownego
  
  //element o nazwie pierwsze nie posiadajacy podmenu stad 0
  struct Menu * pierwsze = robMenu(0, "Pierwsze"); 
  
  //element o nazwie drugie posiadajacy 2 podmenu
  struct Menu * drugie = robMenu(2, "Drugie"); 
  
  //element o nazwie trzecie nie posiadajacy podmenu stad 0
  struct Menu * trzecie = robMenu(0, "Trzecie"); 
  
  //dodajemy wszystkie 3 menu do menu glowne (indeksy 0,1,2 to kolejne indeksy w tablicy podmenu
  dodajSubMenu(0, glowne, pierwsze);
  dodajSubMenu(1, glowne, drugie);
  dodajSubMenu(2, glowne, trzecie);
  
  //tworzymy 2 podmenu dla menu drugiego
  struct Menu * drugieA = robMenu(0, "Drugie A"); 
  struct Menu * drugieB = robMenu(0, "Drugie B");
    
  //dodajemy utworzone podmenu do menu drugiego
  dodajSubMenu(0, drugie, drugieA);
  dodajSubMenu(1, drugie, drugieB);
  
  //wyswietlamy menu glowne
  wyswietlMenu(glowne);
  
  //wyswietlamy menu drugie
  //wyswietlMenu(drugie);  
  
  
  /**
  Jak widac mozna w idiotycznie prosty sposob rozwijac to o kolejne menu, podmenu itp byle zgadzaly sie liczbyu xD
  **/
  system("PAUSE");	
  return 0;
}
