#include <stdbool.h>
#include <stdio.h>

#define MAXFILENAME 20+1
#define NUM_EQUIPMENT_TYPES 6
typedef enum {DESKTOP=1, LAPTOP, PRINTER, MONITOR, KEYBOARD, MOUSE} tEquipmentType;
#define MIN_REQUIREMENT 5

int main() {

    tEquipmentType equipmentType[NUM_EQUIPMENT_TYPES];
    tEquipmentType equipmentNotice[NUM_EQUIPMENT_TYPES];
    int availablePerType[NUM_EQUIPMENT_TYPES];
    float minPrice[NUM_EQUIPMENT_TYPES];
    float maxPrice[NUM_EQUIPMENT_TYPES];
    float avgPrice[NUM_EQUIPMENT_TYPES];
    float restockPrice[NUM_EQUIPMENT_TYPES];
    char filename[MAXFILENAME];
    int i;
    int numNotices;
    int requiredTmp;
    float totalRestockCost;
    FILE* fileToRead;
    
    // ENTRADA DE DATOS
    // pregunta por el nombre de fichero
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");    
    scanf("%s", filename);

    // abre el fichero
    fileToRead = fopen(filename, "r");
    
    // leer datos del archivo
    for(i = 0; i < NUM_EQUIPMENT_TYPES; i++){

        fscanf(fileToRead, "%u", &equipmentType[i]);
        fscanf(fileToRead, "%d", &availablePerType[i]);
        fscanf(fileToRead, "%f", &minPrice[i]);
        fscanf(fileToRead, "%f", &maxPrice[i]);
    }
    
    fclose(fileToRead);
    
    // PROCESO DE DATOS
    // ver si los tipos de equipamiento estan por debajo del stock
    
    totalRestockCost = 0;
    numNotices = 0;
    
    printf("MINIMUM STOCK NOTICES (1-DESKTOP, 2-LAPTOP, 3-PRINTER, 4-MONITOR, 5-KEYBOARD, 6-MOUSE)\n");

  
    for(i = 0; i < NUM_EQUIPMENT_TYPES; i++) {
         if (availablePerType[i] < MIN_REQUIREMENT) {
             

             avgPrice[i] = (minPrice[i] + maxPrice[i])/2.0;
             
             //store calculated values
             
             requiredTmp = MIN_REQUIREMENT - availablePerType[i];
             
             equipmentNotice[i] = requiredTmp;             
             
             restockPrice[i] = avgPrice[i] * (float)requiredTmp;
             
             //update notice counter
             numNotices = numNotices + 1;             
             
             //update total cost
             
             totalRestockCost = restockPrice[i] + totalRestockCost;
             

             
         }
    } 
    if(numNotices > 0){
        printf("EQUIPMENT - REQUIRED - RESTOCK COST [EUR]\n");  
        for(i = 0; i < NUM_EQUIPMENT_TYPES; i++) {
             if (availablePerType[i] < MIN_REQUIREMENT) {
                 
                 printf("%u - ", equipmentType[i]);
                 printf("%d - ", equipmentNotice[i]);
                 printf("%.2f \n", restockPrice[i]);
             }
        } 
        printf("TOTAL RESTOCK COST [EUR]: %.2f \n", totalRestockCost);  
    }
    else {
        printf("NO NOTICES.\n");
    }
        

    return 0;
}