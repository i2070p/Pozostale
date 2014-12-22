#include <stdio.h>
#include <stdlib.h>
    unsigned char b=0;
struct Menu {
    unsigned char iloscOpcji;
    char * opcja;
    struct Menu ** podMenu;
    struct Menu * rodzic;
};

struct Menu* robMenu(int rozmiar, char *opcja) {
    struct Menu* noweMenu = (struct Menu*) malloc(sizeof(struct Menu));
    noweMenu->opcja=opcja;
    noweMenu->iloscOpcji=rozmiar;
    noweMenu->rodzic=NULL;
    if (rozmiar!=0) {
        noweMenu->podMenu = (struct Menu**) malloc(sizeof(struct Menu*)*rozmiar);
        } else {
        noweMenu->podMenu=NULL;
    }
    return(noweMenu);
}
void dodajSubMenu(int indeks, struct Menu* menu, struct Menu *subMenu) {
    menu->podMenu[indeks]=subMenu;
    subMenu->rodzic=menu;
}
/**te funkcje se musisz dostosowac do warunkow uC i swojego LCD**/
void wyswietlMenu(struct Menu * menu) {
    unsigned char i=0;
    printf("MENU: \n");
    for (i=0; i<menu->iloscOpcji; i++) {
        printf("%s\n", menu->podMenu[i]->opcja);
    }
    printf("***********\n");
}

void zdarzenie(char * opcja) {
          /*ITD tu se definiujesz zdarzenia dla opcji*/
     if (opcja == "Pierwsze") {
        printf("Wybrano opcje pierwsza\n");          
     } else 
     
     if (opcja == "Drugie A") {
        printf("Wybrano drugie A\n");          
     } else 
     
     if (opcja == "Wyjscie") {
        printf("Wybrano wyjscie\n");    
        b=1;      
     } else printf("Nie wiem o huj chodzi\n");  
     

}

int main(int argc, char *argv[])
{

    struct Menu * glowne = robMenu(3, "Glowne");


    struct Menu * pierwsze = robMenu(0, "Pierwsze");

    struct Menu * drugie = robMenu(2, "Drugie");

    struct Menu * trzecie = robMenu(0, "Wyjscie");

    dodajSubMenu(0, glowne, pierwsze);
    dodajSubMenu(1, glowne, drugie);
    dodajSubMenu(2, glowne, trzecie);

    struct Menu * drugieA = robMenu(0, "Drugie A");
    struct Menu * drugieB = robMenu(0, "Drugie B");

    dodajSubMenu(0, drugie, drugieA);
    dodajSubMenu(1, drugie, drugieB);

    struct Menu * aktualneMenu = glowne;
    

    int licznik=0;
    
    while (!b) {
          wyswietlMenu(aktualneMenu);
          
          //*****
          /*u Ciebie zamiast tych dwoch polecen ponizej jest nawigacja gora/dol || lewo/prawo 
          zmieniajaca wartosc licznika w zakresie od 0 do aktualneMenu->iloscOpcji
          */
          printf("Wybierz opcje \n");
          scanf("%d", &licznik);
          //*****
          
          if (licznik >=0 && licznik < aktualneMenu->iloscOpcji) {
              if (aktualneMenu->podMenu[licznik]->iloscOpcji==0) {
                 zdarzenie(aktualneMenu->podMenu[licznik]->opcja);
              } else {
                aktualneMenu=aktualneMenu->podMenu[licznik];
              }
          }
    }


    system("PAUSE");
    return 0;
}
