#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

// Fonction pour trouver le nœud avec la plus petite borneInf dans un sous-arbre
T_Sommet *min_value_node(T_Sommet *node)
{
    T_Sommet *current = node;
    while (current && current->filsGauche != NULL)
        current = current->filsGauche;
    return current;
}
// Fonction pour trouver le nœud avec la plus grande borneInf dans un sous-arbre
T_Sommet *max_value_node(T_Sommet *node)
{
    T_Sommet *current = node;
    while (current && current->filsDroit != NULL)
        current = current->filsDroit;
    return current;
}

// Fonction pour trouver le successeur d'un nœud
T_Sommet *successeur(T_Arbre root, T_Sommet *node)
{
    if (node->filsDroit != NULL)
        return min_value_node(node->filsDroit);

    T_Sommet *succ = NULL;
    T_Sommet *ancestor = root;
    while (ancestor != NULL)
    {
        if (node->borneSup < ancestor->borneInf)
        {
            succ = ancestor;
            ancestor = ancestor->filsGauche;
        }
        else
        {
            ancestor = ancestor->filsDroit;
        }
    }
    return succ;
}

// Fonction pour trouver le prédécesseur d'un nœud
T_Sommet *predecesseur(T_Arbre root, T_Sommet *node)
{
    if (node->filsGauche != NULL)
        return max_value_node(node->filsGauche);

    T_Sommet *pred = NULL;
    T_Sommet *ancestor = root;
    while (ancestor != NULL)
    {
        if (node->borneInf > ancestor->borneSup)
        {
            pred = ancestor;
            ancestor = ancestor->filsDroit;
        }
        else
        {
            ancestor = ancestor->filsGauche;
        }
    }
    return pred;
}
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
// Fonction récursive pour insérer un élément dans l'ABR::: ajouter la fusion des ensembles
T_Arbre insererElement(T_Arbre abr, int element)
{
    if (abr == NULL)
    {
        return creerSommet(element);
    }
    if (element < abr->borneInf)
    {
        if (abr->borneInf - 1 == element)
        {
            abr->borneInf--;
            // trouver le predecesseur et si les ensembles sont collés ,mixer les deux branches
            T_Sommet *pred = predecesseur(abr, abr); // A préciser dans le rapport, on juste besoin du sous arbre, si le predecesseur est plus haut dans l'arbre alors il n'est pas collé à l'élément
            if (abr->borneInf - 1 == pred->borneSup)
            {
                abr->borneInf = pred->borneInf;
                // fonction pour supprimer le sommet du pred
                supprimerSommet(abr, pred);
            }
            return abr;
        }
        else
        {
            abr->filsGauche = insererElement(abr->filsGauche, element);
        }
    }
    else if (element > abr->borneSup)
    {
        if (abr->borneSup + 1 == element)
        {
            abr->borneSup++;
            // trouver le successeur et si  suc = +1 de la branche ,mixer les deux branches
            T_Sommet *suc = successeur(abr, abr);
            if (abr->borneSup - 1 == suc->borneInf)
            {
                abr->borneSup = suc->borneSup;
                // fonction pour supprimer le sommet du pred
                supprimerSommet(abr, suc);
            }
            return abr;
        }
        else
        {
            abr->filsDroit = insererElement(abr->filsDroit, element);
        }
    }
    else
    {
        // L'élément est déjà dans un intervalle, aucune action nécessaire
    }
    return abr;
}

T_Sommet *supprimerSommet(T_Arbre *arbre, T_Sommet *sommet)
{
    T_Sommet *abr = arbre;
    if (abr == NULL)
    {
        return abr;
    }
    // prendre en compte les cas où un seul fils
    else if (abr->borneInf < sommet->borneSup && abr->filsDroit != sommet)
    {
        return supprimerSommet(abr->filsDroit, sommet);
    }
    else if (abr->borneSup >= sommet->borneInf && abr->filsGauche != sommet)
    {
        return supprimerSommet(abr->filsGauche, sommet);
    }
    else if (abr->filsDroit == sommet)
    {
        if (abr->filsDroit->filsDroit == NULL || abr->filsDroit->filsGauche == NULL)
        {
        }
    }
    else if (abr->filsDroit == sommet)
    {
    }
}

// Fonction récursive pour rechercher un élément dans l'ABR
T_Sommet *rechercherElement(T_Arbre abr, int element)
{
    if (abr == NULL || (element >= abr->borneInf && element <= abr->borneSup))
    {
        return abr;
    }
    if (element < abr->borneInf)
    {
        return rechercherElement(abr->filsGauche, element);
    }
    else if (element < abr->borneSup)
    {
        return rechercherElement(abr->filsDroit, element);
    }
    else // Peut être peut supprimer ça car si l'abr est null on le renvoie déjà plus haut
    {
        return NULL;
    }
}

// Fonction récursive pour afficher les sommets de l'ABR
void afficherSommets(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherSommets(abr->filsGauche);
        printf("[%d;%d] ", abr->borneInf, abr->borneSup);
        afficherSommets(abr->filsDroit);
    }
}

// Fonction récursive pour afficher les éléments de l'ABR
void afficherElements(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherElements(abr->filsGauche);
        for (int i = abr->borneInf; i <= abr->borneSup; i++)
        {
            printf("%d, ", i);
        }
        afficherElements(abr->filsDroit);
    }
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
        return rechercherElement(abr->filsGauche, element);
    }
    else if (element < abr->borneSup)
    {
        return rechercherElement(abr->filsDroit, element);
    }
    else
    {
        return NULL;
    }
}

// Fonction  pour supprimer un élément de l'ABR
T_Arbre *supprimerElement(T_Arbre abr, int element)
{
    T_Sommet *sommet = rechercherElement(abr, element);
    int bool;
    if (sommet == NULL)
    {
        return NULL;
    }
    else if (element == sommet->borneInf || element == sommet->borneSup)
    {
        if (element == sommet->borneInf && element == sommet->borneSup)
        {
            supprimerSommet(abr, sommet);
            return abr;
        }
        else if (element == sommet->borneInf)
        {
            sommet->borneInf++;
        }
        else if (element == sommet->borneSup)
        {
            sommet->borneSup--;
        }
    }
    else
    {
        int borneinf = element + 1, bornesup = sommet->borneSup;
        sommet->borneSup = element - 1;
        T_Sommet *filsdroit = sommet->filsDroit;
        sommet->filsDroit = creerSommet(borneinf);
        sommet->filsDroit->borneSup = bornesup;
        sommet->filsDroit->filsDroit = filsdroit;
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
                    // supprimerElement();
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