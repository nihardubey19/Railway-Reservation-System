#include <stdio.h>
#include "conio2.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "rlyres.h"

int enterchoice()
{
    int choice;
    textbackground(BLUE);
    textcolor(WHITE);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    textbackground(BLACK);
    textcolor(WHITE);
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    /* */
    textcolor(BLUE);
    textbackground(WHITE);
    printf("\nSelect an option");
    textbackground(BLACK);
    textcolor(LIGHTBLUE);
    printf("\n1- View Trains \n2- Book Ticket \n3- View Ticket \n4- Search Ticket No \n5- View All Bookings \n6- View Train Bookings \n7- Cancel Ticket \n8- Cancel Train \n9- Quit");
    textbackground(WHITE);
    textcolor(BLUE);
    printf("\n\nEnter choice");
    textbackground(BLACK);
    printf(" : ");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}

void add_trains()
{
    Train alltrains[4]=
            {
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
            };
    FILE* fp;
    fp=fopen("alltrains.dat","rb");
    if(fp == NULL)
    {
        fp=fopen("alltrains.dat","wb");
        fwrite(alltrains,4 * sizeof(Train),1,fp);
        //printf("File created and saved!\n");
    }
    //else
      //  printf("File already present!\n");
    fclose(fp);
}


void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=0;i<80;i++)
        printf("-");
    FILE* fp;
    fp=fopen("alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(Train),1,fp) == 1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n");
    fclose(fp);
}

int check_train_no(char* trainno)
{
    FILE* fp=fopen("alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }
    }
fclose(fp);
return 0;
}

int check_mob_no(char* p_mob)
{
    if(strlen(p_mob) != 10)
        return 0;
    while(*p_mob != '\0')
    {
        if(isdigit(*p_mob) == 0)
        return 0;
        p_mob++;
    }
    return 1;
}


Passenger* get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(LIGHTBLUE);
    printf("Enter passenger name:");
	static Passenger P;
	fflush(stdin);
	textcolor(WHITE);
	fgets(P.p_name,20,stdin);
	char* pos;
	pos=strchr(P.p_name,'\n');
	*pos='\0';
	if(strcmp(P.p_name,"0") == 0)
	{
		gotoxy(1,25);
		textcolor(RED);
		printf("Reservation Canceled");
		getch();
		textcolor(LIGHTBLUE);
		clrscr();
		return NULL;
	}
	int valid;
	textcolor(LIGHTBLUE);
	printf("Enter gender(M/F):");
    do
	{
	    valid=1;
        fflush(stdin);
        textcolor(WHITE);
        scanf("%c",&P.gender);
        if(P.gender == 48)
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Canceled");
            getch();
            textcolor(LIGHTBLUE);
            clrscr();
            return NULL;
        }
        if(P.gender != 'M' && P.gender != 'F')
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("Error! Gender should be M or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \b");
            textcolor(LIGHTBLUE);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");

    gotoxy(1,3);
    textcolor(LIGHTBLUE);
    printf("Enter train number:");
	do
	{
		fflush(stdin);
		textcolor(WHITE);
		scanf("%s",P.train_no);
		if(strcmp(P.train_no,"0") == 0)
		{
			gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Canceled");
            getch();
            textcolor(LIGHTBLUE);
            clrscr();
            return NULL;
		}
		valid=check_train_no(P.train_no);
		if(valid == 0)
		{
		    textcolor(RED);
		    gotoxy(1,25);

		    printf("Error!Invalid Train No");
		    getch();
		    gotoxy(20,3);
		    printf("\t\t\t\t\t\t\t");
		    gotoxy(20,3);
		    textcolor(LIGHTBLUE);
		}
    }while(valid == 0);

	gotoxy(1,25);
	printf("\t\t\t\t\t\t\t");

	gotoxy(1,4);
	textcolor(LIGHTBLUE);
	printf("Enter travelling class(First AC-F,Second AC-S):");
    do
    {
		valid=1;
        fflush(stdin);
        textcolor(WHITE);
		scanf("%c",&P.p_class);
		if(P.p_class == 48)
		{
			gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Canceled");
            getch();
            textcolor(LIGHTBLUE);
            clrscr();
            return NULL;
		}
		if(P.p_class != 'F' && P.p_class != 'S')
		{
		    textcolor(RED);
			gotoxy(1,25);
			printf("Error! Travelling class should be F or S(in uppercase)");
			valid=0;
			getch();
			gotoxy(48,4);
			printf(" \b");
			textcolor(LIGHTBLUE);
		}
	}while(valid == 0);

	gotoxy(1,25);
	printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,5);
    textcolor(LIGHTBLUE);
    printf("Enter address:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(P.address,30,stdin);
    pos=strchr(P.address,'\n');
    *pos='\0';
    if(strcmp(P.address,"0") == 48)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Canceled");
        getch();
        textcolor(LIGHTBLUE);
        clrscr();
        return NULL;
    }
    textcolor(LIGHTBLUE);
	printf("Enter age:");
    do
	{
		valid=1;
		textcolor(WHITE);
		scanf("%d",&P.age);
		if(P.age == 0)
		{
			gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Canceled");
            getch();
            textcolor(LIGHTBLUE);
            clrscr();
            return NULL;
		}
        if(P.age<=0)
		{
            textcolor(RED);
            gotoxy(1,25);
            printf("Error! Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t\t");
            gotoxy(11,6);
            textcolor(LIGHTBLUE);
		}
    }while(valid == 0);

    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");

    gotoxy(1,7);
    textcolor(LIGHTBLUE);
    printf("Enter mobile number:");
	// accept mobile number from the user.
    do
    {
        fflush(stdin);
        textcolor(WHITE);
        fgets(P.mob_no,12,stdin);
        pos=strchr(P.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(P.mob_no,"0") == 0)
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Canceled");
            getch();
            textcolor(LIGHTBLUE);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(P.mob_no);
        if(valid == 0)
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("Error!Invalid mobile no");
            valid=0;
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(LIGHTBLUE);
        }
    }while(valid == 0);
return &P;
}

int get_booked_ticket_count(char* train_no, char tc) // tc ---> ticket class
{
    FILE* fp;
    fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class == tc)
        {
        count++;
        }
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
	FILE* fp;
	fp=fopen("allbookings.dat","rb");
	if(fp == NULL)
	return 0;
	Passenger pr;
	fseek(fp,-1L * sizeof(pr),SEEK_END);
	fread(&pr,sizeof(pr),1,fp);
	fclose(fp);
	return pr.ticketno;
}

int book_ticket(Passenger p)
{
    int ticket_count;
    ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count == 2)
    {
	textcolor(RED);
	printf("All seats full in train no %s in %c class!",p.train_no,p.p_class);
	return -1;
    }

    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE* fp;
    fp=fopen("allbookings.dat","ab");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("Sorry!File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}


int accept_ticket_no()
{
    int ticket_no, valid;
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(WHITE);
    printf("Enter a valid ticket no:");
    do
    {
    valid=1;
    textcolor(LIGHTBLUE);
    scanf("%d",&ticket_no);
    if(ticket_no == 0)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Cancelling Input!");
        textcolor(YELLOW);
        return 0;
    }
    if(ticket_no<0)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("Error!Ticket number should be positive");
        valid=0;
        getch();
        gotoxy(25,1);
        printf("\t\t\t\t");
        gotoxy(25,1);
        textcolor(YELLOW);
    }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t");
    clrscr();
    return ticket_no;
}


void view_ticket(int ticket_no)
{
    FILE* fp;
    fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("Sorry!File cannot be opened");
        return;
    }
    Passenger pr;
    gotoxy(1,2);
    int found=0;
    textcolor(LIGHTRED);
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(pr.ticketno == ticket_no)
        {
            printf("\nName: %s\nGender: %c\nTrain No: %s\nTrain class: %c\nAddress: %s\nAge: %d\nMobile no: %s\nTicket No: %d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }
    }
    textcolor(YELLOW);
    if(!found)
    {
        gotoxy(1,24);
        textcolor(RED);
        printf("No details of the ticket found.");
    }
    fclose(fp);
    getch();
}


char* accept_mob_no()
{
    static char mob_no[12];
    char* pos;
    int valid;
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        textcolor(BLUE);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos != NULL)
        *pos='\0';
        textcolor(YELLOW);
        if(strcmp(mob_no,"0") == 0)
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input..!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid == 0)
        {
            gotoxy(1,25);
            textcolor(RED);
            printf("Error!Invalid mobile no");
            valid=0;
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid == 0);
    clrscr();
    return mob_no;
}

int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    FILE* fp;
    fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("Sorry!File cannot be opened");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp) ==1)
    {
        if(strcmp(pr.mob_no,p_mob_no) == 0)
        ++count;
    }
    if(count == 0)
    {
        fclose(fp);
        return NULL;
    }

    rewind(fp);
    int* p=(int*)malloc((count+1) * sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.mob_no,p_mob_no) == 0)
        {
        *(p+i)=pr.ticketno;
        i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

void view_all_tickets(char* pmob_no, int* pticket_no)
{
    if(pticket_no == NULL)
    {
        textcolor(RED);
        printf("Sorry!No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    textcolor(LIGHTMAGENTA);
    printf("Following are tickets booked for the mobile number %s",pmob_no);
    int i;
    textcolor(LIGHTGREEN);
    printf("\n\nTICKET NUMBERS\n");
    printf("-------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        textcolor(LIGHTBLUE);
        printf("\n%d",*(pticket_no+i));
    }
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}


char* accept_train_no()
{
	gotoxy(60,1);
 	textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(WHITE);
    static char trainno[10];
    int valid;
    printf("Enter train number:");
    do
    {
        valid=1;
        fflush(stdin);
        textcolor(LIGHTBLUE);
        fgets(trainno,20,stdin);
        char* pos=strchr(trainno,'\n');
        if(pos!=NULL)
        *pos='\0';

        if(strcmp(trainno,"0") == 0)
        {
        gotoxy(1,25);
        textcolor(RED);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Cancelling Input");
        textcolor(YELLOW);
        return NULL;
        }
        valid=check_train_no(trainno);
        if(valid == 0)
        {
            textcolor(RED);
            gotoxy(1,25);
            printf("Error!Invalid train number");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");
    clrscr();
    return trainno;
}


void view_booking(char* trainno)
{
    clrscr();
    textcolor(YELLOW);
    FILE* fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No bookings done yet");
        return;
    }
    Passenger pr;
    int found=0;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        textcolor(6);
        if(strcmp(pr.train_no,trainno) == 0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(found == 0)
    {
        clrscr();
        textcolor(RED);
        gotoxy(1,24);
        printf("No details of bookings in train no %s found",trainno);
    }
    textcolor(WHITE);
    printf("\nPress any key to go back to the main screen");
    fclose(fp);
    return;
}


int cancel_ticket(int ticket_no)
{
	FILE* fp;
	fp=fopen("allbookings.dat","rb");
	if(fp == NULL)
	{
		textcolor(RED);
		printf("\nNo bookings done yet");
		return -1;
	}
	FILE* sp;
	sp=fopen("temp.dat","wb");
	Passenger pr;
	int found=0;
	while(fread(&pr,sizeof(pr),1,fp) == 1)
	{
		if(pr.ticketno == ticket_no)
			found=1;
		else
			fwrite(&pr,sizeof(pr),1,sp);
    }
	fclose(fp);
    fclose(sp);
	int result;
	if(found == 0)
	{
        remove("temp.dat");
	}
    else
    {
        result=remove("allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("temp.dat","allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

void view_all_bookings()
{
    clrscr();
    FILE* fp;
    fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No bookings done yet!");
        return;
    }
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    Passenger pr;
    textcolor(6);
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        printf("%d->%s\t\t%c\t%s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
        gotoxy(41,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
    }
    fclose(fp);
}


int cancel_train(char* trainno)
{
    FILE* fp=fopen("alltrains.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No trains are Running");
        return -1;
    }
    Train tp;
    int found=0;
    while(fread(&tp,sizeof(tp),1,fp)==1)
    {
        if(strcmp(tp.train_no,trainno) == 0)
            found=1;
    }
    fclose(fp);
    if(!found)
    {
        return found;
    }
    else
    {
        FILE* fp=fopen("allbookings.dat","rb");
        FILE* sp=fopen("temp1.dat","wb");
        Passenger pr;
        int result=0;
        while(fread(&pr,sizeof(pr),1,fp) == 1)
        {
            if(strcmp(trainno,pr.train_no) == 0)
                result=1;
            else
                fwrite(&pr,sizeof(pr),1,sp);
        }
        fclose(fp);
        fclose(sp);
        if(!result)
        {
            remove("temp1.dat");
        }
        else
        {
            result=remove("allbookings.dat");
            if(result!=0)
                return 2;
            result=rename("temp1.dat","allbookings.dat");
            if(result!=0)
                return 2;
        }
    }
    return found;
}





