#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.c"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
    system("chcp 65001");
#else
    system("clear");
#endif
}

void waitForEnter()
{
    printf("\nAppuyez sur Entrée pour revenir au menu...");
    while (getchar() != '\n')
        ;
    getchar();
}

void afficherMenu()
{
    printf("\nMenu:\n");
    printf("1. Insérer N éléments\n");
    printf("2. Rechercher un élément\n");
    printf("3. Afficher tous les sommets\n");
    printf("4. Afficher tous les éléments\n");
    printf("5. Supprimer un élément\n");
    printf("6. Afficher la taille en mémoire\n");
    printf("7. Quitter\n");
    printf("Choisissez une option: ");
}

int main()
{
    T_Arbre abr = NULL;
    int choix, element, N;

    do
    {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Combien d'éléments voulez-vous insérer ? ");
            scanf("%d", &N);
            for (int i = 0; i < N; i++)
            {
                printf("Entrez l'élément %d: ", i + 1);
                scanf("%d", &element);
                abr = insererElement(abr, element);
            }
            break;

        case 2:
            printf("Entrez l'élément à rechercher: ");
            scanf("%d", &element);
            T_Sommet *recherche = rechercherElement(abr, element);
            if (recherche != NULL)
            {
                printf("L'élément %d se trouve dans l'ensemble [%d, %d]\n", element, recherche->borneInf, recherche->borneSup);
            }
            else
            {
                printf("L'élément %d n'a pas été trouvé dans l'ABR\n", element, 130, 130, 130);
            }
            break;

        case 3:
            printf("Affichage de tous les sommets:\n");
            printTree(abr, 0);
            break;

        case 4:
            printf("Affichage de tous les écléments:\n");
            afficherElements(abr);
            printf("\n");
            break;

        case 5:
            printf("Entrez l'élément à supprimer: ");
            scanf("%d", &element);
            abr = supprimerElement(abr, element);
            printf("\n");
            break;
        case 6:
            tailleMemoire(abr);
            break;

        case 7:
            printf("Quitter...\n");
            liberermemoire(abr);
            break;

        default:
            printf("Option invalide, veuillez réessayer.\n");
            break;
        }
        if (choix != 7)
        {
            waitForEnter();
        }
    } while (choix != 7);

    return 0;
}
