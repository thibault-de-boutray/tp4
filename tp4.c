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

// Fonction récursive pour rechercher un élément dans l'ABR
T_Sommet *rechercherPereElement(T_Arbre abr, int element)
{
    if (abr == NULL || (element >= abr->filsDroit->borneInf && element <= abr->filsDroit->borneSup) ||
        (element >= abr->filsGauche->borneInf && element <= abr->filsGauche->borneSup))
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

// Fonction  pour supprimer un élément de l'ABR
T_Sommet *supprimerElement(T_Sommet *sommet1, int element)
{
    T_Sommet *pere = rechercherPereElement(sommet1, element);
    int bool;
    if (pere == NULL)
    {
        return NULL;
    }
    if (element >= pere->filsDroit->borneInf && element <= pere->filsDroit->borneSup)
    {
        T_Sommet *sommet = pere->filsDroit;
        bool = 1;
    }
    else
    {
        T_Sommet *sommet = pere->filsGauche;
        bool = 0;
    }
    if (sommet == NULL)
    {
        return NULL;
    }
    else
    {
        // Si c'est element est égale à au moins une borne d'un ensemble
        if (sommet->borneInf == element || sommet->borneSup == element)
        {
            if (sommet->borneInf != element) // si égale à borne sup
            {
                sommet->borneSup--;
            }
            else if (sommet->borneSup != element) // si égale à borne inf
            {
                sommet->borneInf++;
            }
            else // si égale à borne sup et inf on doit supprimer le sommet
            {
                if (sommet->filsGauche == NULL && sommet->filsDroit == NULL) // si feuille
                {
                    free(sommet);
                    if (bool == 0)
                    {
                        pere->filsGauche == NULL;
                    }
                    else
                    {
                        pere->filsDroit == NULL;
                    }
                }
                else if (sommet->filsGauche == NULL || sommet->filsDroit == NULL) // si un seul fils
                {
                    T_Sommet *temp = sommet->filsDroit;
                    sommet->borneInf = temp->borneInf;
                    sommet->borneSup = temp->borneSup;
                    sommet->filsGauche = temp->filsGauche;
                    sommet->filsDroit = temp->filsDroit;
                    free(temp);
                }
                else
                { // si deux fils
                    T_Sommet *suc = trouverSuccesseur(sommet);
                    sommet->borneInf = suc->borneInf;
                    sommet->borneSup = suc->borneSup;
                    supprimerElement()
                }
            }
        }
        else if (NULL)
        {
        }

        // Si le sommet n'a qu'un seul enfant ou aucun enfant
        if (sommet->filsGauche == NULL || sommet->filsDroit == NULL)
        {
            T_Sommet *temp = sommet->filsDroit;
            sommet->borneInf = temp->borneInf;
            sommet->borneSup = temp->borneSup;
            sommet->filsGauche = temp->filsGauche;
            sommet->filsDroit = temp->filsDroit;
            free(temp);
            return sommet1;
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