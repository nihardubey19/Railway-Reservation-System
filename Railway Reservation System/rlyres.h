#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED

struct Train
{
    char train_no[10];
    char from[25];
    char to[25];
    int fac_fare;
    int sac_fare;
};

struct Passenger
{
    char p_name[20];
    char gender;
    char train_no[20];
    char p_class;
    char address[30];
    int age;
    int ticketno;
    char mob_no[12];
};

typedef struct Train Train;
typedef struct Passenger Passenger;

int enterchoice();
void add_trains();
void view_trains();
int book_ticket(Passenger);
int* get_ticket_no(char*);
void view_ticket(int);
void view_all_bookings();
int cancel_ticket(int);
int cancel_train(char*);
Passenger* get_passenger_details();
int check_train_no(char*);
int check_mob_no(char*);
int last_ticket_no();
int get_booked_ticket_count(char*, char);
int accept_ticket_no();
char* accept_mob_no();
void view_all_tickets(char*, int*);
char* accept_train_no();
void view_booking(char*);
#endif // RLYRES_H_INCLUDED
