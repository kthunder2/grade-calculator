#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct StudentTable
{
    char name[25];
    char surname[25];
    float lab;
    float assignment;
    float midterm;
    float final_grade;
    float total;
};

struct StudentTable *Load_StudentTable(char*, int *);
void display_StudentTable(struct StudentTable*, int);
int Search(struct StudentTable*, int, char[]);
void Sort(struct StudentTable*, int);

int main(int argc, char *argv[])
{
    int total_student=0, number;


    struct StudentTable *a1;

    a1=Load_StudentTable(argv[1], &total_student);
    display_StudentTable(a1, total_student);

    char name[20]; //used in search to get name input
    int checker;


    do
    {
        printf("\nPress 1 for search, 2 for sort and 3 for exit:");
        scanf("%d", &number);
        fflush(stdin);
        if(number==1)
        {
            do
            {
                printf("\n\nEnter the name of the student:");
                gets(name);
                checker=Search(a1, total_student, name);
            }
            while(checker==-1);
            printf("\n%s %s has %.2f from Lab, %.2f from Assignments, %.2f from Midterm and %.2f from Final, with the total of %.2f.", a1[checker].name, a1[checker].surname, a1[checker].lab, a1[checker].assignment, a1[checker].midterm, a1[checker].final_grade, a1[checker].total);

        }
        else if(number==2)
        {
            Sort(a1, total_student); //used bubble sort for both Final and Total scores. very long.
            display_StudentTable(a1, total_student);
        }
        else if(number==3)
        {
            printf("\nGoodbye!");
        }
        else
        {
            printf("\nInvalid input!\n");
        }

    }
    while(number<2);


    free(a1);

    return 0;
}

struct StudentTable * Load_StudentTable(char* argument, int *total_student)
{
    char a[15], b[15]; //non-important variables to assist counting total student
    float c, d, e, f;
    int i; //for populating structure


    FILE *openfile;
    struct StudentTable *a1;

    openfile=fopen(argument, "r");
    if(openfile==NULL)
    {
        do
        {
            printf("\nThis file does not exist, please enter again:");
            scanf("%s", argument);
            fflush(stdin);
        }
        while(openfile==NULL);

    }
    while(fscanf(openfile, "%s %s %f %f %f %f", a, b, &c, &d, &e, &f)!=EOF) //counting total student
    {
        (*total_student)++;
    }



    printf("Total student=%d \n\n", *total_student);

    printf("Student records file (%s) has been successfully loaded!\nFollowing records have been loaded:\n\n", argument);

    a1=(struct StudentTable *)malloc(*(total_student)*sizeof(struct StudentTable));

    if(a1==NULL)
    {
        printf("\nAllocation unsuccessful!\n\nExiting program...");
        exit(1);
    }

    rewind(openfile); //revert back to the start of the file

    for(i=0; i<(*total_student); i++)
    {
        fscanf(openfile, "%s %s %f %f %f %f", a1[i].name, a1[i].surname, &a1[i].lab, &a1[i].assignment, &a1[i].midterm, &a1[i].final_grade);
        a1[i].total=a1[i].lab+ a1[i].assignment + (0.3*a1[i].midterm) + (0.35*a1[i].final_grade);
    }

    fclose(openfile);

    return (a1);


}

void display_StudentTable(struct StudentTable *a2, int total_student)
{
    int x;

    printf("Name Surname Lab Assignment Midterm Final Total\n\n");

    for(x=0; x<total_student; x++)
    {
        printf("%s %s %.2f %.2f %.2f %.2f %.2f \n", a2[x].name, a2[x].surname, a2[x].lab, a2[x].assignment, a2[x].midterm, a2[x].final_grade, a2[x].total);
    }

}

int Search(struct StudentTable *a1, int total_student, char name[20])
{
    int checker=-1, loop;
    int check2=0; // check2 is for the for loop
    char fullname[50]; //takes name and surmane of person

    for(loop=0; loop<total_student && check2==0; loop++)
    {
        //fills the fullname with the name
        strcpy(fullname, a1[loop].name);
        strcat(fullname, " ");
        strcat(fullname, a1[loop].surname);
        if(strcmp(fullname, name)==0)
        {
            checker=loop;
            check2=1;  //if the name is found, it will exit for loop thanks to new check2 value
        }

    }

    if(checker==-1)
    {
        printf("\nThat student is unknown! Please try again!");

    }
    return checker;
}

void Sort(struct StudentTable *a1, int total_student)
{
    char sort;

    //asks for input again until T or F is given
    do
    {
        printf("\nSort by (F: Final, T: Total):");
        scanf("%c", &sort);
        fflush(stdin);
        if((sort!='T' || sort!='t') || (sort!='F' || sort!='f'))
        {
            printf("\nInvaid input!");
        }

    }while((sort!='T' || sort!='t') || (sort!='F' || sort!='f'));

    int x,y;
    float temp; //for storing swapped number values
    char name[50], surname[50]; //for storing swapped names and surnames

    if(sort=='T' || sort=='t')
    {
        for(y=0; y<=total_student; y++) //very long loop to change list based on total score
        {
            for(x=0; x<total_student; x++)
            {
                if(a1[x].total>a1[x+1].total)
                {
                    temp=a1[x].total;
                    a1[x].total=a1[x+1].total;
                    a1[x+1].total=temp;

                    temp=a1[x].final_grade;
                    a1[x].final_grade=a1[x+1].final_grade;
                    a1[x+1].final_grade=temp;

                    temp=a1[x].lab;
                    a1[x].lab=a1[x+1].lab;
                    a1[x+1].lab=temp;

                    temp=a1[x].midterm;
                    a1[x].midterm=a1[x+1].midterm;
                    a1[x+1].midterm=temp;

                    temp=a1[x].assignment;
                    a1[x].assignment=a1[x+1].assignment;
                    a1[x+1].assignment=temp;

                    strcpy(name, a1[x].name);
                    strcpy(a1[x].name, a1[x+1].name);
                    strcpy(a1[x+1].name, name);

                    strcpy(surname, a1[x].surname);
                    strcpy(a1[x].surname, a1[x+1].surname);
                    strcpy(a1[x+1].surname, surname);


                }
            }
        }



    }

    if(sort=='F' || sort=='f')
    {
        for(y=0; y<=total_student; y++) //very long loop to change list based on final exam score
        {
            for(x=0; x<total_student-1; x++)
            {
                if(a1[x].final_grade>a1[x+1].final_grade)
                {
                    temp=a1[x].final_grade;
                    a1[x].final_grade=a1[x+1].final_grade;
                    a1[x+1].final_grade=temp;

                    temp=a1[x].total;
                    a1[x].total=a1[x+1].total;
                    a1[x+1].total=temp;

                    temp=a1[x].lab;
                    a1[x].lab=a1[x+1].lab;
                    a1[x+1].lab=temp;

                    temp=a1[x].midterm;
                    a1[x].midterm=a1[x+1].midterm;
                    a1[x+1].midterm=temp;

                    temp=a1[x].assignment;
                    a1[x].assignment=a1[x+1].assignment;
                    a1[x+1].assignment=temp;

                    strcpy(name, a1[x].name);
                    strcpy(a1[x].name, a1[x+1].name);
                    strcpy(a1[x+1].name, name);

                    strcpy(surname, a1[x].surname);
                    strcpy(a1[x].surname, a1[x+1].surname);
                    strcpy(a1[x+1].surname, surname);
                }



            }


        }



    }



}
