#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sdetails{
    char firstname[100];
    char lastname[100];
    char major[100];
    char degree[100];
    float gpa;
    int credithrs;
    char ta[100];
    char advisor[100];
};
int main()
{
    char tempdata[1000],*sblock,tempstr[100];
    int recordswithhdr=0,tokenpos=0,totlrecords=0,structrecords=50,degcount=0;
    struct sdetails *s1 = malloc(structrecords* sizeof(struct sdetails));
    FILE *input = fopen("students_dataset.csv","r");
    if(input == NULL)
    {
        printf("File doesn't exist");
        return(-1);
    }
    while(fgets(tempdata,1000,input)!=NULL)
    {
        if(recordswithhdr > 0)
        {
            if(recordswithhdr >=structrecords)
            {
                structrecords = recordswithhdr + 50;
                s1 = (struct sdetails*)realloc(s1,structrecords);
            }
	        sblock = strtok(tempdata,",");
            for(tokenpos=0;tokenpos<8;tokenpos++)
            {
                if (tokenpos ==0 )
                {
                    strcpy(s1[recordswithhdr-1].firstname,sblock);
                }
                else if (tokenpos ==1 )
                {
                    strcpy(s1[recordswithhdr-1].lastname,sblock);
                }
                else if (tokenpos ==2 )
                {
                    strcpy(s1[recordswithhdr-1].major,sblock);
                }
                else if (tokenpos ==3 )
                {
                    strcpy(s1[recordswithhdr-1].degree,sblock);
                }
                else if (tokenpos ==4 )
                {
                    s1[recordswithhdr-1].gpa = atof(sblock);
                }
                else if (tokenpos ==5 )
                {
                    s1[recordswithhdr-1].credithrs = atoi(sblock);
                }
                else if (tokenpos ==6 )
                {
                    strcpy(s1[recordswithhdr-1].ta,sblock);
                }
                else if (tokenpos ==7 )
                {
                    strcpy(s1[recordswithhdr-1].advisor,sblock);
                }
                sblock = strtok(NULL,",");
            }
            recordswithhdr++;
        }
        else
        {
            recordswithhdr++;
        }
    }
    totlrecords = recordswithhdr-1;
    
    char temp[totlrecords][100];
    char temp1[totlrecords][100];
    // Total number of degrees
    for(int i=0;i<totlrecords;i++)
    {
        strcpy(temp[i],s1[i].degree);
    }
    for(int i=1;i<totlrecords;i++)
    {
        int j = i;
        while ((j > 0) && (strcmp(temp[j - 1],temp[j]) == 1)) { 
            strcpy(tempstr,temp[j - 1]);
            strcpy(temp[j - 1],temp[j]);
            strcpy(temp[j],tempstr);
            j--;
        }
    }
    
    for(int i=0;i<totlrecords;i++)
    {
        char tempdeg[100];
        if(strcmp(tempdeg,temp[i])!=0)
        {
            strcpy(tempdeg,temp[i]);
            degcount++;
            strcpy(temp1[degcount-1],temp[i]);
        }
    }
    printf("Total degrees:%d\n", degcount);
    for(int i=0;i<degcount;i++)
    {
        printf("%s\t",temp1[i]);
    }
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("Top student names with highest GPA \n");
    float tgpa[totlrecords];
    float tempgpa=0;
    int gpacount=0;
    for(int i=0;i<totlrecords;i++)
    {
        tgpa[i] = s1[i].gpa;
    }
    for(int i=1;i<totlrecords;i++)
    {
        int j = i;
        while ((j > 0) && (tgpa[j - 1]<tgpa[j])) { 
            tempgpa=tgpa[j - 1];
            tgpa[j - 1]=tgpa[j];
            tgpa[j]=tempgpa;
            j--;
        }
    }
    float tempcgpa=0;
    for(int i=0;i<totlrecords&&gpacount<3;i++)
    {
        if(tempcgpa != tgpa[i])
        {
            tempcgpa = tgpa[i];
            gpacount++;
            printf("GPA:%f\n",tempcgpa);
            for(int j=0;j<totlrecords;j++)
            {
                if(s1[j].gpa == tempcgpa)
                {
                    printf("%s %s\n",s1[j].firstname,s1[j].lastname);
                }
            }
        }
    }
    printf("----------------------------------------------------------\n");
    // Average credit hours
    float chours=0;
    for(int i=0;i<totlrecords;i++)
    {
        chours = chours + s1[i].credithrs;
    }
    printf("Average Credit hours: %f\n",chours/totlrecords);
    printf("----------------------------------------------------------\n");
    //Computer science average gpa
    float cgpa = 0;
    int crecords = 0;
    for(int i=0;i<totlrecords;i++)
    {
        if(strcmp("Computer Science",s1[i].major)==0)
        {
            cgpa = cgpa + s1[i].gpa;
            crecords++;
        }
    }
    printf("Computer Science Average GPA: %f\n",cgpa/crecords);
    printf("----------------------------------------------------------\n");
    // Total advisors
    printf("Total number of advisors along with department name \n");
    char temp2[totlrecords][100],tempadv[100],tempdeg[100];;
    int advisorcount=0;
    int advcount=0;
    for(int i=0;i<totlrecords;i++)
    {
        strcpy(temp[i],s1[i].major);
    }
    for(int i=1;i<totlrecords;i++)
    {
        int j = i;
        while ((j > 0) && (strcmp(temp[j - 1],temp[j]) == 1)) { 
            strcpy(tempstr,temp[j - 1]);
            strcpy(temp[j - 1],temp[j]);
            strcpy(temp[j],tempstr);
            j--;
        }
    }
    for(int i=0;i<totlrecords;i++)
    {
        if(strcmp(tempdeg,temp[i])!=0)
        {
            strcpy(tempdeg,temp[i]);
            advisorcount = 0;
            for(int j=0;j<totlrecords;j++)
            {
                if(strcmp(tempdeg,s1[j].major)==0)
                {
                    strcpy(temp2[advisorcount],s1[j].advisor);
                    advisorcount++;
                }
            }
            for(int i=1;i<advisorcount;i++)
            {
                int j = i;
                while ((j > 0) && (strcmp(temp2[j - 1],temp2[j]) == 1)) { 
                    strcpy(tempstr,temp2[j - 1]);
                    strcpy(temp2[j - 1],temp2[j]);
                    strcpy(temp2[j],tempstr);
                    j--;
                }
            }
            printf("%s:",tempdeg);
            advcount = 0;
            for(int i=0;i<advisorcount;i++)
            {
                if(strcmp(tempadv,temp2[i])!=0)
                {
                    strcpy(tempadv,temp2[i]);
                    advcount++;
                }
            }
            printf("%d\n",advcount);
            for(int i=0;i<totlrecords;i++)
            {
                strcpy(temp2[i],"");
            }
        }
        for(int i=0;i<advisorcount;i++)
            {
                strcpy(temp2[i],"");
            }
        strcpy(tempadv,"");
    }
    return 0;
}
