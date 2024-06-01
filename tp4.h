#ifndef TP4_H
#define TP4_H

// Structure de données pour un sommet de l'arbre binaire de recherche (ABR)
typedef struct Sommet
{
    int borneInf;
    int borneSup;
    struct Sommet *filsGauche;
    struct Sommet *filsDroit;
} T_Sommet;

typedef T_Sommet *T_Arbre; // Type pour un ABR

// Fonctions de base
T_Sommet *creerSommet(int element);
T_Arbre *insererElement(T_Arbre abr, int element);
T_Sommet *rechercherElement(T_Arbre abr, int element);
void afficherSommets(T_Arbre abr);
void afficherElements(T_Arbre abr);
T_Arbre *supprimerElement(T_Arbre abr, int element);
void tailleMemoire(T_Arbre abr);
// Fonctions ajoutées
T_Sommet *min_value_node(T_Sommet *node);
T_Sommet *max_value_node(T_Sommet *node);
T_Sommet *successeur(T_Arbre root, T_Sommet *node);
T_Sommet *predecesseur(T_Arbre root, T_Sommet *node);
T_Sommet *supprimerSommet(T_Arbre *arbre, T_Sommet *sommet);

#endif
