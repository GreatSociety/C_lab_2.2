// Используя функции и режим меню, создать бинарный файл из N структур,
//просмотреть файл, добавить в файл новую информацию и, применяя режим прямого
//доступа, выполнить задание по своему варианту.
//1. Структура имеет вид: фамилия, пол, год рождения и рост. Вывести данные о
//самом высоком спортсмене.

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char *surname; //[64]
    char *gender;
    int age;
    int height;
}Athlete;

void clearInputBuf(void);
void createFile(Athlete** list, unsigned int size);
void readFile(unsigned int size);
void changeFile(unsigned int size, const char* name);
void addFile(unsigned int* size);
void findFile(unsigned int size);

int main(){

    unsigned int size = 5;
    puts("How many data?");
    scanf("%ud", &size);
    clearInputBuf();

    Athlete** iAthlete = calloc(size,sizeof(Athlete));


    for(int i = 0; i < size; i++){

        iAthlete[i] = malloc(sizeof(Athlete));
        char* surname = malloc(64);
        char* gender = malloc(16);

        printf("Athlete surname:");
        fgets(surname,64,stdin);
        iAthlete[i]->surname = surname;

        printf("Athlete gender:");
        fgets(gender,16,stdin);
        iAthlete[i]->gender = gender;

        printf("Athlete's age:");
        scanf("%d",&iAthlete[i]->age);
        clearInputBuf();

        printf("Athlete's height:");
        scanf("%d",&iAthlete[i]->height);
        clearInputBuf();

    }

    createFile(iAthlete,size);

    //free
    for(int i = 0; i < size; i++){
        free(iAthlete[i]);
    }
    free(iAthlete);


    int choice = 0;
    do{

        puts("\nWhat you wanna do:\n"
             "1.View file data\n"
             "2.Change data of person in file\n"
             "3.Add new person\n"
             "4.Find the tallest person\n"
             "5.Exit.");
        scanf("%d", &choice);
        clearInputBuf();

        if(choice == 1){
            readFile(size);
        }
        else if(choice == 2){
            char* name = malloc(64);
            puts("What a person name?");
            fgets(name, 64, stdin);

            changeFile(size, name);
            free(name);
        }
        else if(choice == 3){
            addFile(&size);
        }
        else if(choice == 4){
            findFile(size);
        }
        else{
            if(choice == 5){
                puts("Goodbye");
            }
            else{
                puts("Nonsense");
            }
        }

    } while (choice != 5);

}

void createFile(Athlete** list, unsigned int size){

    FILE *newfile = fopen("structbin.dat","wb");

    if(!newfile){
        puts("Creat error.");
        return;
    }
    else{

        for(int i = 0; i < size; i++){
            fwrite(list[i],sizeof(Athlete), 1, newfile);
        }
    }

    fclose(newfile);
}

void readFile(unsigned int size){

    FILE *newfile = fopen("structbin.dat","rb");

    if(!newfile){
        puts("Read error.");
        return;
    }

    Athlete instance;

    for(int i = 0; i < size; i++){

        fread(&instance, sizeof(Athlete), 1, newfile);

        puts("\n---------------------");
        printf("Athlete surname: %s", instance.surname);
        printf( "Athlete gender: %s", instance.gender);
        printf("Athlete's age: %d", instance.age);
        printf( "\nAthlete's height: %d", instance.height);
    }
    puts("\n---------------------\n");

    fclose(newfile);
}

void changeFile(unsigned int size, const char* name){

    FILE *newfile = fopen("structbin.dat","rb+");
    if(!newfile){
        puts("Open error.");
        return;
    }

    Athlete instance;
    int choice = 0;

    for(int i = 0; i < size; i++){

        fread(&instance, sizeof(Athlete), 1, newfile);

        if(*instance.surname == *name){

            fseek(newfile,-(sizeof(Athlete)),SEEK_CUR);

            puts("\nWhat you wanna edit?\n"
                 "1.Surname\n"
                 "2.Gender\n"
                 "3.Age\n"
                 "4.Height");
            scanf("%d",&choice);
            clearInputBuf();

            if(choice == 1){
                char* surname = malloc(64);
                puts("New surname:");
                fgets(surname,64,stdin);
                instance.surname = surname;
            }
            else if(choice == 2){
                char* gender = malloc(16);
                puts("New gender:");
                fgets(gender,16,stdin);
                instance.gender = gender;
            }
            else if(choice == 3){
                puts("New age:");
                scanf("%d",&instance.age);
                clearInputBuf();

            }
            else if(choice == 4){
                puts("New height:");
                scanf("%d",&instance.height);
                clearInputBuf();
            }

            fwrite(&instance, sizeof(Athlete),1, newfile);

            break;
        }
    }

    if(choice == 0){
        puts("Not Found");
    }

    fclose(newfile);
}

void addFile(unsigned int* size){

    FILE *newfile = fopen("structbin.dat","ab+");

    if(!newfile){
        puts("Open error.");
        return;
    }

    Athlete instance;

    char* surname = malloc(64);
    char* gender = malloc(16);

    printf("Athlete surname:");
    fgets(surname,64,stdin);
    instance.surname = surname;

    printf("Athlete gender:");
    fgets(gender,16,stdin);
    instance.gender = gender;

    printf("Athlete's age:");
    scanf("%d",&instance.age);
    clearInputBuf();

    printf("Athlete's height:");
    scanf("%d",&instance.height);
    clearInputBuf();

    (*size)++;
    fwrite(&instance, sizeof(Athlete),1, newfile);

    fclose(newfile);
}

void findFile(unsigned int size){

    FILE *newfile = fopen("structbin.dat","rb");

    if(!newfile){
        puts("Open error.");
        return;
    }

    Athlete instance;
    fseek(newfile, sizeof(instance) - sizeof(instance.height),SEEK_SET);
    int array[size];

    for(int i = 0; i < size; i++){

        fread(&array[i], sizeof(int),1,newfile);
        fseek(newfile, sizeof(instance) - sizeof(instance.height),SEEK_CUR);
    }

    int max = array[0];
    int indexMax = 0;

    for(int i = 1; i < size; i++){

        if(array[i] > max){
            max = array[i];
            indexMax = i;
        }
    }

    fseek(newfile, sizeof(instance) * indexMax , SEEK_SET);
    fread(&instance, sizeof(Athlete), 1, newfile);

    puts("Tallest athlete");
    puts("\n---------------------\n");
    printf("Athlete surname: %s", instance.surname);
    printf( "Athlete gender: %s", instance.gender);
    printf("Athlete's age: %d", instance.age);
    printf( "\nAthlete's height: %d", instance.height);
    puts("\n---------------------\n");

    fclose(newfile);

}


void clearInputBuf()
{
    int garbageCollector;
    while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF);
}