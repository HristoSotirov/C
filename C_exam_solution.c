#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// задача 1
#define LEN 31
#define CH_LEN 8

typedef struct {
    char name[LEN];
    char chip[CH_LEN];
    float price;
} TPet;

// Функция за въвеждане на информация за домашен любимец
TPet inputPet(void)
{
    TPet pet;
    FILE *f;

    printf("Name: ");
    fgets(pet.name, LEN, stdin);
    fflush(stdin);
    pet.name[strcspn(pet.name, "\n")] = '\0';    // Премахване на новия ред от името
    
    printf("Chip: ");
    fgets(pet.chip, CH_LEN, stdin);
    fflush(stdin);
    pet.chip[strcspn(pet.chip, "\n")] = '\0';   // Премахване на новия ред от името

    printf("Price: ");
    scanf("%f", &pet.price);
    fflush(stdin);

    // Отваряне на текстовия файл за добавяне на информацията
    if ((f = fopen("animalsText.txt", "a")) == NULL) {
        perror("Open error: ");   // Ако неуспешно отваряне, извежда грешка и излиза от програмата
        exit(2);
    }
    fprintf(f, "%s,%.2f\n", pet.name, pet.price);   // Запис на информацията във файла
    fclose(f);
    return pet;
}

// задача 2
// Функция за извеждане на информацията за домашни любимци с определена цена
void printPetsByPrice(TPet pets[], unsigned len, float fprice)
{
    bool isFound = false;

    for (int i = 0; i < len; i++) {
        if (pets[i].price == fprice) {
            isFound = true;
            printf(" %s - %s\n", pets[i].name, pets[i].chip);   // Извеждане на информацията за домашния любимец
        }
    }
    if (!isFound) {
        puts("No such data...\n");   // Ако няма намерена информация, извежда съобщение
    }
}

// задача 3
void printPets(float ffprice)
{
    FILE *f;                      // Дефиниране на указател към файл
    unsigned len;                 // Променлива за дължината на името на домашния любимец
    TPet pet;                     // Структура, която съдържа информация за домашен любимец
    bool isFirst = true;          // Флаг, който показва дали е първият извик на функцията

    // Отваряне на бинарния файл за четене
    if ((f = fopen("animalsBin.bin", "rb")) == NULL) {
        perror("Open Bin error: ");   // Ако неуспешно отваряне, извежда грешка и излиза от програмата
        exit(4);
    }

    // Цикъл за четене на информацията за домашните любимци от файла
    while (true) {
        // Четене на дължината на името от файла
        if (fread(&len, sizeof(unsigned), 1, f) != 1) {
            if (!feof(f)) {
                perror("Reading bin error: ");   // Ако неуспешно четене, извежда грешка и затваря файла
                fclose(f);
                exit(10);
            } else
                break;   // Ако срещнат край на файла, излиза от цикъла
        }

        // Четене на името на домашния любимец от файла
        if (fread(&pet.name, sizeof(char), len, f) != len) {
            perror("Reading bin error: ");   // Ако неуспешно четене, извежда грешка и затваря файла
            fclose(f);
            exit(11);
        }
        pet.name[len] = '\0';   // Добавяне на терминираща нула към края на името

        // Четене на чипа на домашния любимец от файла
        if (fread(&pet.chip, sizeof(char), CH_LEN-1, f) != CH_LEN-1) {
            perror("Reading bin error: ");   // Ако неуспешно четене, извежда грешка и затваря файла
            fclose(f);
            exit(12);
        }
        pet.chip[CH_LEN-1] = '\0';   // Добавяне на терминираща нула към края на чипа

        // Четене на цената на домашния любимец от файла
        if (fread(&pet.price, sizeof(float), 1, f) != 1) {
            perror("Reading bin error: ");   // Ако неуспешно четене, извежда грешка и затваря файла
            fclose(f);
            exit(13);
        }

        // Проверка дали цената на домашния любимец е по-висока или равна на дадена цена
        if (pet.price >= ffprice) {
            if (!isFirst) {
                puts("----------");   // Ако не е първият извик на функцията, извежда разделителна линия
            } else
                isFirst = false;   // Ако е първият извик на функцията, задава флага isFirst на false

            // Извежда информацията за домашния любимец на екрана
            printf("Bin Owner Name: %s\n", pet.name);
            printf("Bin Chip: %s\n", pet.chip);
            printf("Bin Price: %.2f\n", pet.price);
            
        }
    }

    fclose(f);   // Затваряне на файла
}


int main()
{
    // задача 1
    unsigned SIZE = 4;
    TPet pets[SIZE];
    for(int i=0;i<SIZE;i++){
        pets[i] = inputPet();
    }

    // задача 2
    printPetsByPrice(pets,SIZE,99.99);
    
    // задача 3
    printPets(25.00);
    return 0;
}
