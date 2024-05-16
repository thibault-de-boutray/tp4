#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

// Fonction pour créer un sommet à partir d'un entier entré en paramètre
T_Sommet *creerSommet(int element)
{
    T_Sommet *nouveauSommet = (T_Sommet *)malloc(sizeof(T_Sommet));
    if (nouveauSommet != NULL)
    {
        nouveauSommet->borneInf = element;
        nouveauSommet->borneSup = element;
        nouveauSommet->filsGauche = NULL;
        nouveauSommet->filsDroit = NULL;
    }
    return nouveauSommet;
}

// Fonction récursive pour insérer un élément dans l'ABR ajouter la fusion des ensembles
T_Arbre insererElementRec(T_Arbre abr, int element)
{
    if (abr == NULL)
    {
        return creerSommet(element);
    }
    if (element < abr->borneInf)
    {
        abr->filsGauche = insererElementRec(abr->filsGauche, element);
    }
    else if (element > abr->borneSup)
    {
        abr->filsDroit = insererElementRec(abr->filsDroit, element);
    }
    else
    {
        // L'élément est déjà dans un intervalle, aucune action nécessaire
    }
    return abr;
}

// Fonction récursive pour rechercher un élément dans l'ABR
T_Sommet *rechercherElementRec(T_Arbre abr, int element)
{
    if (abr == NULL || (element >= abr->borneInf && element <= abr->borneSup))
    {
        return abr;
    }
    if (element < abr->borneInf)
    {
        return rechercherElementRec(abr->filsGauche, element);
    }
    else if (element < abr->borneSup)
    {
        return rechercherElementRec(abr->filsDroit, element);
    }
    else
    {
        return NULL;
    }
}

// Fonction récursive pour afficher les sommets de l'ABR
void afficherSommetsRec(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherSommetsRec(abr->filsGauche);
        printf("[%d;%d] ", abr->borneInf, abr->borneSup);
        afficherSommetsRec(abr->filsDroit);
    }
}

// Fonction récursive pour afficher les éléments de l'ABR
void afficherElementsRec(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherElementsRec(abr->filsGauche);
        printf("%d ", abr->borneInf);
        afficherElementsRec(abr->filsDroit);
    }
}

// Fonction auxiliaire pour trouver le successeur dans l'ABR
T_Sommet *trouverSuccesseur(T_Sommet *sommet)
{
    T_Sommet *courant = sommet->filsDroit;
    while (courant->filsGauche != NULL)
    {
        courant = courant->filsGauche;
    }
    return courant;
}

// Fonction récursive pour supprimer un élément de l'ABR
T_Sommet *supprimerElementRec(T_Sommet *sommet, int element)
{
    if (sommet == NULL)
    {
        return sommet;
    }

    if (element < sommet->borneInf)
    {
        sommet->filsGauche = supprimerElementRec(sommet->filsGauche, element);
    }
    else if (element > sommet->borneSup)
    {
        sommet->filsDroit = supprimerElementRec(sommet->filsDroit, element);
    }
    else
    {
        // Trouvé l'élément à supprimer

        // Si le sommet n'a qu'un seul enfant ou aucun enfant
        if (sommet->filsGauche == NULL)
        {
            T_Sommet *temp = sommet->filsDroit;
            free(sommet);
            return temp;
        }
        else if (sommet->filsDroit == NULL)
        {
            T_Sommet *temp = sommet->filsGauche;
            free(sommet);
            return temp;
        }

        // Si le sommet a deux enfants, obtenir le successeur
        T_Sommet *successeur = trouverSuccesseur(sommet);

        // Copier les données du successeur au sommet courant
        sommet->borneInf = successeur->borneInf;
        sommet->borneSup = successeur->borneSup;

        // Supprimer le successeur
        sommet->filsDroit = supprimerElementRec(sommet->filsDroit, successeur->borneInf);
    }
    return sommet;
}

// Fonction pour supprimer un élément de l'ABR
T_Arbre supprimerElement(T_Arbre abr, int element)
{
    return supprimerElementRec(abr, element);
}

// Fonction pour calculer la taille mémoire occupée par l'ABR
void tailleMemoireRec(T_Arbre abr, int *taille)
{
    if (abr != NULL)
    {
        *taille += sizeof(T_Sommet);
        tailleMemoireRec(abr->filsGauche, taille);
        tailleMemoireRec(abr->filsDroit, taille);
    }
}

// Fonction pour afficher la taille mémoire
void tailleMemoire(T_Arbre abr)
{
    int tailleReelle = 0;
    int tailleClassique = 0;
    tailleMemoireRec(abr, &tailleReelle);
    tailleClassique = sizeof(T_Sommet) * (abr == NULL ? 0 : 2);
    printf("Taille réelle de l'ABR en octets : %d\n", tailleReelle);
    printf("Taille d'un ABR classique en octets : %d\n", tailleClassique);
}