#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element{
    short int valeur;
    Element *e_suivant;
    Element *e_precedent;
};

typedef struct Liste Liste;
struct Liste{
    short int longueur;
    Element *p_tete;
    Element *p_tail;
};

Liste* initialize(){
  Liste *liste = malloc(sizeof(Liste));
  
  if (liste==NULL){
    exit(EXIT_FAILURE);
  }
  
  liste->longueur = 0;
  liste->p_tete = NULL;
  liste->p_tail = NULL;
  
  return liste;
}


void append(Liste *liste, short int valeur){
  Element *element = malloc(sizeof(Element));
  
  if(element == NULL || liste == NULL){
    exit(EXIT_FAILURE);
  }
  
  element->valeur = valeur;
  element->e_suivant = NULL;
  
  
  if(liste->p_tail == NULL){ //Si la liste est vide 
    element->e_precedent = NULL;
    liste->p_tete = element ;
    liste->p_tail = element ;
  }else{
    liste->p_tail->e_suivant = element;
    element->e_precedent = liste->p_tail;
    liste->p_tail = element;
  }
  
  liste->longueur++;
}


void ajouterEnDebut(Liste *liste, short int valeur){

  Element *element = malloc(sizeof(Element));
  
  if(liste == NULL || element == NULL ){
    exit(EXIT_FAILURE);
  }
  
  element -> valeur = valeur;
  element -> e_precedent = NULL;
  
  if(liste->p_tete == NULL ){ //La liste est vide
    element -> e_suivant = NULL ;
    liste->p_tete = element ;
    liste->p_tail = element;
  }else{
    liste->p_tete->e_precedent = element;
    element->e_suivant = liste->p_tete;
    liste->p_tete = element;
  }
  
  liste->longueur++;
}

void ajouterParPosition(Liste *liste, short int valeur, int position){
  if(liste == NULL) exit(EXIT_FAILURE);
  
  if(position < 1 || position > (liste->longueur)){
    fprintf(stderr,"Position non valable !!!!");
    exit(EXIT_FAILURE);
  }
  
  int i =1; //Compteur
  
  
  Element *elementCourant = liste->p_tete ;
  
  while(position <= liste->longueur && i < position ){
    i++;
    elementCourant = elementCourant->e_suivant;
  }
  
  if(i == position){
    if(elementCourant->e_suivant == NULL){ //Inserer a la fin
      append(liste, valeur);
    }else if(elementCourant->e_precedent == NULL) { //Inserer au debut 
      ajouterEnDebut(liste, valeur);
    }else{ //Ajouter l'element a la position i
      Element *nv = malloc(sizeof(Element));
      if(nv == NULL) exit(EXIT_FAILURE);
      printf("\n\t----Creation de lelement 'ajouterParPosition'----\n");
      
      nv -> valeur = valeur ;
      printf("\n\t----intialiser la valeur %d----\n", nv->valeur);
      
      nv->e_suivant = elementCourant ;
      printf("\n\t----fait pointer le nouveau element a l'element courant, il pointe sur: %d----\n", elementCourant->valeur);
      
      nv->e_precedent = elementCourant->e_precedent ;
      printf("\n\t----et il pointe aussi sur %d 'lelement precedent'----\n", elementCourant->e_precedent->valeur);
      
      elementCourant->e_precedent->e_suivant =nv;
      printf("\n\t---- et %d pointe sur %d----\n", elementCourant->e_precedent->valeur, nv->valeur);
      
      elementCourant->e_precedent = nv;
      printf("\n\t---- %d lelement courant pointe sur lelement precedent qui est le nouveau %d ----\n", elementCourant->valeur, nv->valeur);
      
      
      liste->longueur++;
    }
  }
}


void suppSvaleur(Liste *liste, int valeur) {
    if (liste == NULL || liste->p_tete == NULL) {
        printf("La liste est vide ou non initialisée.\n");
        return;
    }

    Element *elementCourant = liste->p_tete;

    while (elementCourant != NULL) {
        if (elementCourant->valeur == valeur) {
            if (elementCourant->e_precedent == NULL) { // il s'agit du Premier élément
                if (elementCourant->e_suivant != NULL) {
                    elementCourant->e_suivant->e_precedent = NULL;
                }
                liste->p_tete = elementCourant->e_suivant;
                if (liste->p_tete == NULL) {
                    liste->p_tail = NULL; // Liste vide après suppression
                }
            } else if (elementCourant->e_suivant == NULL) { // il s'agit du Dernier élément
                elementCourant->e_precedent->e_suivant = NULL;
                liste->p_tail = elementCourant->e_precedent;
            } else { // Élément au milieu
                elementCourant->e_precedent->e_suivant = elementCourant->e_suivant;
                elementCourant->e_suivant->e_precedent = elementCourant->e_precedent;
            }

            free(elementCourant);
            liste->longueur--;
            return;  // Sortir après suppression
        }
        elementCourant = elementCourant->e_suivant;
    }

    printf("La valeur %d n'a pas été trouvée dans la liste.\n", valeur);
}

void suppSposition(Liste *liste, int position){

  if(liste == NULL) exit(EXIT_FAILURE);
  
  if(position < 1 || position > (liste->longueur)){
    fprintf(stderr,"------Position non valable !!!!-----\n");
    exit(EXIT_FAILURE);
  }
  
  Element *elementCourant = liste->p_tete ;
  int i = 1;
  
  while(position <= liste->longueur && i < position ){
    i++;
    elementCourant = elementCourant->e_suivant;
  }
  
  if(i==position){
    if(elementCourant->e_suivant == NULL){ //suppression du dernier element
      if (elementCourant->e_precedent != NULL) {
         elementCourant->e_precedent->e_suivant = NULL;
      }
      liste->p_tail = elementCourant->e_precedent;
    }else if(elementCourant->e_precedent == NULL){ //suppression du premier element
      liste->p_tete = elementCourant->e_suivant ;
      elementCourant->e_suivant->e_precedent = NULL;
    }else{
      elementCourant->e_suivant->e_precedent = elementCourant->e_precedent ;
      elementCourant->e_precedent->e_suivant = elementCourant->e_suivant ;
    }
    free(elementCourant);
    liste->longueur--;
    return ;
  }
  
}

Liste *getElement(Liste *liste, int valeur){
  if (liste == NULL ){
    exit(EXIT_FAILURE);
  }
  
  Liste *retenus = initialize(); ;
  Element *elementCourant = liste->p_tete;
  while(elementCourant!=NULL){
    if(elementCourant->valeur == valeur){
      append(retenus, elementCourant->valeur);
      //break;
    }
    elementCourant = elementCourant->e_suivant ;
  }
  return retenus ;
}

void libererListe(Liste **liste){

  if (liste == NULL ) exit(EXIT_FAILURE);
  
  Element *elementCourant = (*liste) -> p_tete ;
  while(elementCourant != NULL ){
    Element *elementAsupprimer = elementCourant;
    elementCourant = elementCourant -> e_suivant ;
    free(elementAsupprimer);
  }
  free(*liste);
  *liste = NULL;
}

void afficherListe(Liste *liste){
  if(liste == NULL){
    fprintf(stderr,"---------------- La liste est vide !!!! ------------\n");
    exit(EXIT_FAILURE);
  }
  
  Element *elementCourant = liste->p_tete;
  printf("tete : ");
  while(elementCourant != NULL){
    printf("%d -> ", elementCourant->valeur);
    elementCourant = elementCourant->e_suivant;
  }
  
  printf("NULL");
}

void afficherListeRecursive(Liste *liste){
  if(liste == NULL){
    fprintf(stderr,"---------------- La liste est vide !!!! ------------\n");
    exit(EXIT_FAILURE);
  }
  
  Element *elementCourant = liste->p_tail;
  printf("tail : ");
  while(elementCourant != NULL){
    printf("%d -> ", elementCourant->valeur);
    elementCourant = elementCourant->e_precedent;
  }
  printf("NULL");
}

int main()
{

    Liste *liste = initialize();
    
    printf("I- Manipulation de la liste en utilisant la methode 'APPEND' :\n");
    
    printf("\t1- Ajouter l'element 40, 50 et enfin 60:\n");
    append(liste,40);
    append(liste,50);
    append(liste,60);
    
    
    printf("\t\t- Affichage normal de la liste :\n\t\t");
    afficherListe(liste);
    
    printf("\n\n\t\t- Affichage recursive de la liste :\n\t\t");
    afficherListeRecursive(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    
    printf("II- Manipulation de la liste en utilisant la methode 'ajouterEnDebut' :\n");
    printf("\t1- Ajouter l'element 30, 20 et enfin 10:\n");
    ajouterEnDebut(liste,30);
    ajouterEnDebut(liste,20);
    ajouterEnDebut(liste,10);
    
    
    printf("\t\t- Affichage normal de la liste :\n\t\t");
    afficherListe(liste);
    
    printf("\n\n\t\t- Affichage recursive de la liste :\n\t\t");
    afficherListeRecursive(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("III- Ajouter des éléments par position :\n");
    printf("\t1- Ajouter 45 a la position 5:\n");
    ajouterParPosition(liste, 45, 5);
    printf("\t\t-Affichage après l'ajout de 45 a la position 5 :\n\t\t");
    afficherListe(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("IV- supprimer un element selon la valeur:\n");
    printf("\t1- supprimer 45 de la liste :\n");
    suppSvaleur(liste, 45);
    printf("\t\t-Affichage après la suppression de 45 :\n\t\t");
    afficherListe(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("V- supprimer un element selon sa position:\n");
    printf("\t1- supprimer lelement a la position 6:\n");
    suppSposition(liste, 6);
    printf("\t\t-Affichage après la suppression delement a la position 6:\n\t\t");
    afficherListe(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("\n\t2- supprimer lelement a la position 1 :\n");
    suppSposition(liste, 1);
    printf("\t\t-Affichage après la suppression delement a la position 1:\n\t\t");
    afficherListe(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("\n\t2- supprimer lelement a la position 3 :\n");
    suppSposition(liste, 3);
    printf("\t\t-Affichage après la suppression delement a la position 3:\n\t\t");
    afficherListe(liste);
    printf("\nLa liste dispose de %d elements.\n", liste->longueur);
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("VI- rechercher element selon sa valeur :\n");
    printf("1- rechercher lelement 30:\n");
    Liste *nouvelleListe = getElement(liste, 30);
    printf("\t\t-Affichage de la nouvel liste avec la valeur 30:\n\t\t");
    afficherListe(nouvelleListe);
    printf("\nLa nouvelle liste dispose de %d elements.\n", nouvelleListe->longueur);
    printf("2-Ajouter 100 a la nouvelle liste 'Append' :\n");
    append(nouvelleListe, 100);
    printf("\t\t-Affichage de la nouvelle liste après l'ajout du 100:\n\t\t");
    afficherListe(nouvelleListe);
    printf("\nLa nouvelle liste dispose de %d elements.\n", nouvelleListe->longueur);
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("VII- Liberation de la liste :\n");
    libererListe(&liste);
    printf("\t\tAffichage de la liste aprés sa suppression :\n\t\t");
    afficherListe(liste);
    return 0;
}
