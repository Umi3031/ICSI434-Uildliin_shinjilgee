#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Хамгийн бага зардлын аргаар тээвэрлэлтийн асуудлыг шийдэх функц
int** leastCost(int* supply, int* demand, int** costs, int numSuppliers, int numConsumers) {
    printf("\n=== Khamgiin baga zardal gargakha argaa khaij teeverleltiig ekhuulj baina ===\n");
    int** allocations = (int**)malloc(numSuppliers * sizeof(int*));
    for (int i = 0; i < numSuppliers; i++) {
        allocations[i] = (int*)calloc(numConsumers, sizeof(int));
    }

    int* remainingSupply = (int*)malloc(numSuppliers * sizeof(int));
    int* remainingDemand = (int*)malloc(numConsumers * sizeof(int));

    for (int i = 0; i < numSuppliers; i++) remainingSupply[i] = supply[i];
    for (int i = 0; i < numConsumers; i++) remainingDemand[i] = demand[i];

    int step = 1;
    
    while (1) {
        int minCost = INT_MAX;
        int minRow = -1, minCol = -1;
        printf("\nAlkham %d: Khamgiin baga zardliig khaij baina...\n", step);

        for (int i = 0; i < numSuppliers; i++) {
            for (int j = 0; j < numConsumers; j++) {
                if (remainingSupply[i] > 0 && remainingDemand[j] > 0) {
                    printf(" [%d][%d] Zardal = %d (Uldsen supply: %d, demand: %d)\n", i + 1, j + 1, costs[i][j], remainingSupply[i], remainingDemand[j]);

                    if (costs[i][j] < minCost || 
                        (costs[i][j] == minCost &&
                         (remainingSupply[i] + remainingDemand[j] >
                          remainingSupply[minRow] + remainingDemand[minCol]))) {
                        minCost = costs[i][j];
                        minRow = i;
                        minCol = j;
                    }
                }
            }
        }

        if (minRow == -1 || minCol == -1) {
            printf("Bukh shaardlagtai khuviarlalt hiigdlee!\n");
            break;
        }

        int teeverlelt = (remainingSupply[minRow] < remainingDemand[minCol])
                        ? remainingSupply[minRow] : remainingDemand[minCol];
        allocations[minRow][minCol] += teeverlelt;
        remainingSupply[minRow] -= teeverlelt;
        remainingDemand[minCol] -= teeverlelt;
        printf("\nAlkham %d: Teeverleltiin shiidel khiigdlee!\n", step);
        printf("  %d-r niiluulegchees %d-r khereglegch ruu %d negj ilgeelee.\n",minRow + 1, minCol + 1, teeverlelt);
        printf("Zardal: %d * %d = %d\n", costs[minRow][minCol], teeverlelt, costs[minRow][minCol] * teeverlelt);
        printf("Uldsen niiluulelt: ");
        for (int i = 0; i < numSuppliers; i++) printf("%d ", remainingSupply[i]);
        printf("\nUldsen erelt:     ");
        for (int i = 0; i < numConsumers; i++) printf("%d ", remainingDemand[i]);
        printf("\n---------------------------------------\n");

        step++;
    }


    free(remainingSupply);
    free(remainingDemand);
    return allocations;
}

int main() {
    int numSuppliers, numConsumers;
    printf("hichneen achaa yavuulah gazriin too : ");
    scanf("%d", &numSuppliers);
    printf("hichneen achaa huleen awah gazriin too: ");
    scanf("%d", &numConsumers);

    int* supply = (int*)malloc(numSuppliers * sizeof(int));
    for (int i = 0; i < numSuppliers; i++) {
        printf("Achaa yavuulah gazar %d : ", i + 1);
        scanf("%d", &supply[i]);
    }

    int* demand = (int*)malloc(numConsumers * sizeof(int));
    for (int i = 0; i < numConsumers; i++) {
        printf("Achaa huleen avah gazar %d : ", i + 1);
        scanf("%d", &demand[i]);
    }

    int** costs = (int**)malloc(numSuppliers * sizeof(int*));
    for (int i = 0; i < numSuppliers; i++) {
        costs[i] = (int*)malloc(numConsumers * sizeof(int));
    }

    for (int i = 0; i < numSuppliers; i++) {
        for (int j = 0; j < numConsumers; j++) {
            printf("a[%d][%d] zardal: ", i + 1, j + 1);
            scanf("%d", &costs[i][j]);
        }
    }
    printf("\n====================================\n");
    printf("Teeverleltiin tuluvlguug ekhluulj baina...\n");
    int** allocations = leastCost(supply, demand, costs, numSuppliers, numConsumers);
    int totalCost = 0;

    printf("Huwiarlalt:\n");
    for (int i = 0; i < numSuppliers; i++) {
        for (int j = 0; j < numConsumers; j++) {
            printf("%d\t", allocations[i][j]);
            totalCost += allocations[i][j] * costs[i][j];
        }
        printf("\n");
    }

    printf("\tNiit zardal : %d\n", totalCost);

    // Санах ойг чөлөөлөх
    for (int i = 0; i < numSuppliers; i++) {
        free(costs[i]);
        free(allocations[i]);
    }
    free(costs);
    free(allocations);
    free(supply);
    free(demand);

    return 0;
}
