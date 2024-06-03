#include <stdio.h>
#include <stdlib.h>
#include "tp4.c"

void afficherMenu()
{
    printf("\nMenu:\n");
    printf("1. Ins%crer N %cl%cments\n", 130, 130, 130);
    printf("2. Rechercher un %cl%cment\n", 130, 130);
    printf("3. Afficher tous les sommets\n");
    printf("4. Afficher tous les %cl%cments\n", 130, 130);
    printf("5. Supprimer un %cl%cment\n", 130, 130);
    printf("6. Afficher la taille en m%cmoire\n", 130);
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
            printf("Combien d'%cl%cments voulez-vous ins%crer ? ", 130, 130, 130);
            scanf("%d", &N);
            for (int i = 0; i < N; i++)
            {
                printf("Entrez l'%cl%cment %d: ", 130, 130, i + 1);
                scanf("%d", &element);
                abr = insererElement(abr, element);
            }
            break;

        case 2:
            printf("Entrez l'%cl%cment %c rechercher: ", 130, 130, 133);
            scanf("%d", &element);
            T_Sommet *recherche = rechercherElement(abr, element);
            if (recherche != NULL)
            {
                printf("L'%cl%cment %d se trouve dans l'ensemble [%d, %d]\n", 130, 130, element, recherche->borneInf, recherche->borneSup);
            }
            else
            {
                printf("L'%cl%cment %d n'a pas %ct%c trouv%c dans l'ABR\n", 130, 130, element, 130, 130, 130);
            }
            break;

        case 3:
            printf("Affichage de tous les sommets:\n");
            printTree(abr, 0);
            break;

        case 4:
            printf("Affichage de tous les %cl%cments:\n", 130, 130);
            afficherElements(abr);
            printf("\n");
            break;

        case 5:
            printf("Entrez l'%cl%cment %c supprimer: ", 130, 130, 133);
            scanf("%d", &element);
            abr = supprimerElement(abr, element);
            break;

        case 7:
            printf("Quitter...\n");
            liberermemoire(abr);
            break;

        default:
            printf("Option invalide, veuillez r%cessayer.\n", 130);
            break;
        }
    } while (choix != 7);

    return 0;
}
