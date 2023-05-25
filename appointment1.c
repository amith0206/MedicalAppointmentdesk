#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char name[50];
    char illness[50];
    struct node * link;
};

typedef struct node * NODE;

NODE getnode(){
    NODE x;
    x=(NODE)malloc(sizeof(struct node));
    if(x==NULL)
    {
        printf("Memory is not available\n");
        exit(0);
    }
    return x;
}

typedef struct user_authentication
{
    /* User authetication */
    char username[50];
    char password[50];
    char confirm_password[50];
}USER;

//Insertion of a node
void insertNode(NODE head){
    int i;
    char name_encrypted[50],ill_encrypted[50];
    NODE temp=getnode();
    temp->link=NULL;
    printf("Enter your name:\n");
    scanf("%s",name_encrypted);


    //Simple Caesar algorithm used to encrypt the data of the users
    for(i=0;name_encrypted[i]!='\0';i++)
        name_encrypted[i]=name_encrypted[i]+3;
    strcpy(temp->name,name_encrypted);
    printf("Enter what you are suffering from?\n");
    scanf("%s",ill_encrypted);
    for(i=0;ill_encrypted[i]!='\0';i++)
        ill_encrypted[i]=ill_encrypted[i]+3;
    strcpy(temp->illness,ill_encrypted);    
    if(head->link==NULL){
        head->link=temp;
        printf("Appointment time : 9:00\n");
        return;
    }
    NODE cur=head;
    int hour = 9, minute = 0;
    while(cur->link!=NULL  && hour < 18){
        cur=cur->link;
        minute += 30;
        if (minute == 60) {
            hour++;
            minute = 0;
        }
    }
    cur->link=temp;
    printf("Appointment time is : %02d:%02d\n", hour, minute);
}

//Delete node function
void deleteNode(NODE head,int pos) {
    if (head->link == NULL) {
        printf("Appointment List is empty\n");
        return;
    }
    NODE temp=head->link;
    if(pos==1){
        head->link=temp->link;
        free(temp);
        return;
    }
    NODE cur=head;
    for(int i=0;i<pos-1;i++){
        cur=cur->link;
        if(cur==NULL){
            printf("Invalid position\n");
            return;
        }
    }
    temp=cur->link;
    cur->link=temp->link;
    free(temp);
}

//Printing the list of employees
void printList(NODE head) {
    int i,hour = 9, minute = 0;
    char name[50],illness[50];
    NODE cur= head;
    
    while(cur->link!= NULL && hour < 18) {
        cur = cur->link;
        strcpy(name,cur->name);
        for(i=0;name[i]!='\0';i++)
            name[i]=name[i]-3;
        printf("Name : %s\n",name);
        strcpy(illness,cur->illness);
        for(i=0;illness[i]!='\0';i++)
            illness[i]=illness[i]-3;
        printf("Illness :%s\n",illness);
        printf("Appointment time is : %02d:%02d\n", hour, minute);
        minute += 30;
        if (minute == 60) {
            hour++;
            minute = 0;
        }
    } 
}

int main(){
    int flag=1,ch_flag=0,ch,i=-1;
    USER *a;
    while(1){
        printf("Enter 1: Sign Up\n2: Sign In\n3: Exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1: a=(USER *)malloc(sizeof(struct user_authentication));
                    if(a==NULL){
                    printf("Memory not available\n");
                    exit(0);
                    }
                    ++i;
                    printf("Enter username:\n");
                    scanf("%s",a[i].username);
                    printf("Enter password:\n");
                    scanf("%s",a[i].password);
                    printf("Enter confirm password:\n");
                    scanf("%s",a[i].confirm_password);
                    int c=3;
                    while(1 && c>0){
                        if(strcmp(a[i].confirm_password,a[i].password)==0){
                            break;
                        }
                        else{
                            c--;
                            printf("You have %d chances left\n",c);
                            printf("Wrong confirm password. Please enter it again\n");
                            scanf("%s",a[i].confirm_password);

                        }
                    }
                    break;
            case 2: {
                    char user[50],pass[50];
                    printf("Enter username\n");
                    scanf("%s",user);
                    printf("Enter password:\n");
                    scanf("%s",pass);
                    for(int j=0;j<50;j++){
                        if((strcmp(user,a[j].username)==0)&&strcmp(pass,a[j].password)==0){
                            flag=0;
                            break;
                        }
                    }        
                    if(flag==0){
                        printf("Login successful\n");
                        ch_flag=1;
                    } 
                    else{
                        printf("Login unsuccessful\n");
                        break;
                     }
                     break;
            }
            case 3: printf("Thank you\n");
                    exit(0);
            default: printf("Invalid option\n");                  
        }
        if(flag==0)
            break;
    }
    if(ch_flag==1){
            printf("Welcome to Appointment Desk\n");
            NODE head=getnode();
    head->link=NULL;
    int choice;
    //Menu driven approach
    while(1){
        printf("1. Add appointment\n");
        printf("2. Delete appointments\n");
        printf("3. Display appointments\n");
        printf("4. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insertNode(head);
                printf("Your appointment has been fixed\n");
                break;
            case 2:{
                int hr,min;
                printf("Enter the time of your appointment in HR,MIN format\n");
                scanf("%d%d",&hr,&min);
                hr=hr-9;
                min=hr*60+min;
                int pos=(min/30)+1;
                deleteNode(head,pos);
                printf("Your appointment has been successfully deleted\n");
                break;
            }
            case 3:
                printList(head);
                break;
            case 4:
                   printf("Thank you\n");
                   exit(0); 
            default:
                printf("Invalid choice.\n");
        }
    }
}
else
    exit(0);
}