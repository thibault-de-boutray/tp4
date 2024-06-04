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
            if (pred != NULL && abr->borneInf - 1 == pred->borneSup)
            {
                int temp = pred->borneInf;
                printf("arrive jusqu'a l'appel de la fonction suppr\n");
                // fonction pour supprimer le sommet du pred
                supprimerSommet(abr, pred);
                abr->borneInf = temp;
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
            if (suc != NULL && abr->borneSup + 1 == suc->borneInf)
            {
                int temp = suc->borneSup;
                // fonction pour supprimer le sommet du pred
                printf("arrive jusqu'a l'appel de la fonction suppr\n");
                supprimerSommet(abr, suc);
                abr->borneSup = temp;
                return abr;
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

T_Sommet *supprimerSommet(T_Arbre arbre, T_Sommet *sommet)
{
    if (arbre == NULL)
    {
        printf("arbre null");
        return arbre;
    }
    else if (sommet->borneSup < arbre->borneInf)
    {
        printf("gauche %d\n", arbre->borneSup);
        arbre->filsGauche = supprimerSommet(arbre->filsGauche, sommet);
    }
    else if (sommet->borneInf > arbre->borneSup)
    {
        printf("droite  %d\n", arbre->borneInf);
        arbre->filsDroit = supprimerSommet(arbre->filsDroit, sommet);
    }
    else
    {

        printf("wtf?%d\n", arbre->borneInf);

        // Si le sommet n'a qu'un seul fils ou aucun
        if (arbre->filsGauche == NULL && arbre->filsDroit == NULL)
        {
            printf("suppr feuille %d: %d\n", arbre->borneInf, arbre->borneSup);
            free(arbre);
            printf("return null\n");
            return NULL;
        }
        else if (arbre->filsGauche == NULL)
        {
            T_Sommet *temp = arbre->filsDroit;
            printf("suppr avec filsdroit");

            free(arbre);
            return temp;
        }
        else if (arbre->filsDroit == NULL)
        {
            T_Sommet *temp = arbre->filsGauche;
            free(arbre);
            printf("suppr avec filsgauche");
            return temp;
        }
        else
        {
            printf("sense suppr\n");
            // Si le sommet a deux enfants, trouver le successeur (le plus petit dans le sous-arbre droit)
            T_Sommet *temp = min_value_node(arbre->filsDroit);
            printf("borne inf du suc%d et borne sup du suc %d", temp->borneInf, temp->borneSup);

            // Copier les valeurs du successeur dans le sommet à supprimer
            arbre->borneInf = temp->borneInf;
            arbre->borneSup = temp->borneSup;

            // Supprimer le successeur
            arbre->filsDroit = supprimerSommet(arbre->filsDroit, temp);

            printf("fin de la fonction suppr");
            return arbre;
        }
    }
    return arbre;
}

void printTree(T_Sommet *root, int space)
{
    if (root == NULL)
        return;

    // Augmenter la distance entre les niveaux
    space += 10;

    // Afficher le sous-arbre gauche
    printTree(root->filsDroit, space);

    // Imprimer le nœud courant après l'espace
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("[%d;%d]\n", root->borneInf, root->borneSup);

    // Afficher le sous-arbre droit
    printTree(root->filsGauche, space);
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
    else
    {
        return rechercherElement(abr->filsDroit, element);
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

// Fonction  pour supprimer un élément de l'ABR
T_Arbre supprimerElement(T_Arbre abr, int element)
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
            return abr;
        }
        else if (element == sommet->borneSup)
        {
            sommet->borneSup--;
            return abr;
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
        return abr;
    }
}

void liberermemoire(T_Arbre arbre)
{
    if (arbre != NULL)
    {
        T_Sommet *sommet = arbre;
        liberermemoire(sommet->filsGauche);
        liberermemoire(sommet->filsDroit);
        free(sommet);
    }
}

int tailleMemoireensemble(T_Arbre abr)
{
    if (abr != NULL)
    {
        return 2 * sizeof(int) + 2 * sizeof(&abr->filsDroit) + tailleMemoireensemble(abr->filsDroit) + tailleMemoireensemble(abr->filsGauche);
    }
    else
    {
        return 0;
    }
}

int tailleMemoireclassique(T_Arbre abr)
{
    if (abr != NULL)
    {
        int sup = abr->borneSup + 1, inf = abr->borneInf;
        return sup - inf + tailleMemoireclassique(abr->filsGauche) + tailleMemoireclassique(abr->filsDroit);
    }
    else
    {
        return 0;
    }
}

void tailleMemoire(T_Arbre abr)
{
    if (abr == NULL)
    {
        printf("ABR null");
    }
    else
    {
        int ensemble = tailleMemoireensemble(abr);
        int abrclassique = tailleMemoireclassique(abr) * (sizeof(int) + 2 * sizeof(&abr->filsDroit));
        int gain = abrclassique - ensemble;
        printf("taille en octets de l'ABR avec ensemble: %d\n", ensemble);
        printf("taille en octets de l'ABR classique: %d\n", abrclassique);
        if (gain >= 0)
        {
            printf("Vous avez gagn%c %d octets!", 130, gain);
        }
        else
        {
            printf("Vous avez perdu %d octets :/", -gain);
        }
    }
}