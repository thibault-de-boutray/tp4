#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

T_Sommet *min_value_node(T_Sommet *node)
{
    T_Sommet *current = node;
    while (current && current->filsGauche != NULL)
        current = current->filsGauche;
    return current;
}

T_Sommet *max_value_node(T_Sommet *node)
{
    T_Sommet *current = node;
    while (current && current->filsDroit != NULL)
        current = current->filsDroit;
    return current;
}

T_Sommet *successeur(T_Arbre root, T_Sommet *node)
{
    if (node->filsDroit != NULL)
        return min_value_node(node->filsDroit);

    /*T_Sommet *succ = NULL;
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
    return succ;*/
    return NULL;
}

T_Sommet *predecesseur(T_Arbre root, T_Sommet *node)
{
    if (node->filsGauche != NULL)
        return max_value_node(node->filsGauche);

    /*T_Sommet *pred = NULL;
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
    return pred;*/
    return NULL;
}

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
            T_Sommet *pred = predecesseur(abr, abr);
            if (pred != NULL && abr->borneInf - 1 == pred->borneSup)
            {
                int temp = pred->borneInf;
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
            T_Sommet *suc = successeur(abr, abr);
            if (suc != NULL && abr->borneSup + 1 == suc->borneInf)
            {
                int temp = suc->borneSup;
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
        arbre->filsGauche = supprimerSommet(arbre->filsGauche, sommet);
    }
    else if (sommet->borneInf > arbre->borneSup)
    {
        arbre->filsDroit = supprimerSommet(arbre->filsDroit, sommet);
    }
    else
    {
        if (arbre->filsGauche == NULL && arbre->filsDroit == NULL)
        {
            return NULL;
        }
        else if (arbre->filsGauche == NULL)
        {
            T_Sommet *temp = arbre->filsDroit;
            free(arbre);
            return temp;
        }
        else if (arbre->filsDroit == NULL)
        {
            T_Sommet *temp = arbre->filsGauche;
            free(arbre);
            return temp;
        }
        else
        {
            T_Sommet *temp = min_value_node(arbre->filsDroit);
            printf("borne inf du suc%d et borne sup du suc %d", temp->borneInf, temp->borneSup);
            arbre->borneInf = temp->borneInf;
            arbre->borneSup = temp->borneSup;
            arbre->filsDroit = supprimerSommet(arbre->filsDroit, temp);
            return arbre;
        }
    }
    return arbre;
}

void  afficherSommets(T_Sommet *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
     afficherSommets(root->filsDroit, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("[%d;%d]\n", root->borneInf, root->borneSup);
     afficherSommets(root->filsGauche, space);
}

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

void afficherSommets(T_Arbre abr)
{
    if (abr != NULL)
    {
        afficherSommets(abr->filsGauche);
        printf("[%d;%d] ", abr->borneInf, abr->borneSup);
        afficherSommets(abr->filsDroit);
    }
}

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

T_Arbre supprimerElement(T_Arbre abr, int element)
{
    T_Sommet *sommet = rechercherElement(abr, element);
    if (sommet == NULL)
    {
        return abr;
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
            printf("Vous avez gagné %d octets!", gain);
        }
        else
        {
            printf("Vous avez perdu %d octets :/", -gain);
        }
    }
}
