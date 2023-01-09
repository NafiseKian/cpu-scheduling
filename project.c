
#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>




struct process{

int at ; //arrival time
int bt;  // burst time
int pr;  //priority
int tt ; //turnaround time
int wt ; //waiting time
bool done ; //to check if its finished
int parts ; // rr parts 
int remain; 

struct process* next ;

};
//__________________________Functions____________________________


void menu();
struct process *createProcess( int, int, int);
struct process *insertBack(struct process *, int, int, int);
struct process *deleteFront(struct process *);
void swapp (struct process * , struct process *);
struct process *copy(struct process *);
void display(struct process *header);
void schedulingMethod (int );
void fcfsScheduling();
void sjfScheduling ();
void priorityScheduling();
void roundrobinScheduling();
void show();
void showOutput(struct process*);
bool check(struct process *);
struct process *smallest(struct process *, int );
struct process *worst(struct process * , int );

//__________________________Variables____________________________


#define SIZE 999999
char buff[SIZE];
char buffer_output[SIZE * 6];
char* input  ;
char* output  ;
int counter = 0;
double average =0 ;
int quantum ; 
bool preemptive = 0 ; 
struct process *header =NULL;
bool fcfs;
bool sjf  ;
bool priority;
bool roundrobin;



//__________________________Main_Function_________________________


int main (int args , char* argv[]){

     
     int opt;
     
     while((opt = getopt(args , argv , "f:o:")) != -1 )
     {

        switch (opt){
            case 'f' : input= optarg ; break;
            case 'o' : output= optarg  ;break ;
            default : printf("\nplease enter a valid form of input! ") ;break ; 
        }

     }

       
  
         FILE *file = fopen(input,"r");
  
	      if (feof(file))
	       {
		       printf("\nyour input file is empty!!!");
		       exit(1);
	       }
	       else
	       {
		       while (!feof(file)) 
		        {
			       int arrival, burst, priority;
			       fscanf(file, "%d:%d:%d\n", &burst, &arrival, &priority);
                   header = insertBack(header , arrival , burst , priority);
			       counter++;
		        }
	       }

         fclose(file);

		 menu();

    

}
 //___________________________menu_____________________________________

        void menu(){

			printf("\n1)Scheduling Method(none) \n2)Preemptive Mode(OFF/ON)\n3)showResult\n4)End Program \n type:");
		int choice ;
		scanf("%1d", &choice);

        switch (choice)
		{
		case 1 :
		      int mode; 
			  printf("\n1)none \n2)first come first serve \n3)shortest job first\n4)priority scheduling\n5)Round Robin\ntype:");
			  scanf("%1d" , &mode);
			  schedulingMethod (mode);
			  menu();
			break;

		case 2 :
		      if (preemptive == false ){
                preemptive = true;
				printf("preemptive mode is ON ");
			  }
			 
			  else preemptive = false ;
			  
			  menu();
			break;

		case 3 :
		    show();
			break;

		case 4 :
			 showOutput(header);
			break;

		default:
		  printf("wrong choice!!!!");
			break;
		}		



		}
         
//_____________________________________________________________________



//________________________________create________________________________

struct process *createProcess( int arrival, int burst,  int priority)
{
	struct process  *temp;

	temp = (struct process *)malloc(sizeof(struct process));
	


	temp->at = arrival;
	temp->bt = burst;
	temp->pr = priority;
	temp->tt = 0;
	temp->wt = 0;
	
	

	return temp;
}

//_______________________________insert_________________________________


struct process *insertBack(struct process *h, int burst , int arrival, int priority)
{
	struct process *temp = createProcess( burst, arrival, priority);
	struct process *ht;

	
	if (h == NULL)
	{
		h = temp;
		return h;
	}

	ht = h;

	while (ht->next != NULL) 
		ht = ht->next;

	ht->next = temp;
	
	return h;
}

//_____________________________deleteFront_______________________________


struct process *deleteFront(struct process *header)
{
	struct process *temp;

	if (header == NULL)
	{
		return header;
	}

	temp = header;
	header = header->next;
	free(temp);
	return header;
}

//____________________________deleteAfter_______________________________

void deleteAfter(struct process *afternode){

	struct process *t ;

	if(afternode->next == NULL || afternode == NULL)
	  return;

	t=afternode->next;
	afternode->next=t->next;
	free(t);
}

//___________________________Display____________________________________

void display(struct process *h)
{
	struct process *temp = h ;

while (temp != NULL)
{
	printf("\n arrival : %d burst:  %d priority : %d \n" ,temp->at , temp->bt, temp->pr );
	temp=temp->next;
}



}

//_______________________Scheduling Method______________________________

void schedulingMethod (int m){


switch (m)
{
    case 1:  
	break;

	case 2 :  
	   fcfsScheduling();
	break;

	case 3 :
	   sjfScheduling();  
	break;

	case 4 :  
	   priorityScheduling();
	break;

	case 5 :  
	   roundrobinScheduling();
	break;


    default:
	printf("ops !!! wrong choice ! ");
	break;
}

}



//___________________________fcfs_______________________________________

void fcfsScheduling(){

fcfs =true ;

int timer =0;
double avg ; 
double sum = 0 ;

struct process *f = copy (header);
struct process *t1 =f;
struct process *t2 =f;

while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  
	 f=f->next; 
}
//finding the avg waiting time 

strcpy(buff, "");
strcat(buff, "Scheduling Method: First Come First Served\n");
strcat(buff, "Process Waiting Times:\n");

    char buff1[20] = "";

    timer += t1->bt ;
    t1->tt = timer ;
	

	t1->wt = (timer - t1->bt)  ;
	snprintf(buff1, 19, "waiting time  %d \n", t1->wt);
	strcat(buff, buff1);
	sum += t1->wt ;
	t1=t1->next ;





while (t1 != NULL)
{


	timer += t1->bt ;
    t1->tt = timer ;
	

	t1->wt = (timer - t1->bt) - t1->at  ;

    char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t1->wt);
	strcat(buff, buff1);


	sum += t1->wt ;
	
	t1=t1->next ;
}



avg = sum / counter ;


char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);





}

//___________________________sjf________________________________

void sjfScheduling (){

sjf = true ;

if (preemptive==0){


int timer = 0;

double avg , sum ; 

struct process *f = copy (header);
struct process *ff =f;
struct process *t =f;
struct process *tt =f;
struct process *t11 =f;

while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}






for (int i=0 ; i<counter ; i++){

	timer = 0;
     t=ff;

 for (int j = 0; j < counter - 1 - i; j++){
    
	struct process *t1 =t;
    struct process *t2 =t->next;


	 if (t1->at <= timer && t2->at <= timer){
            if (t1->bt > t2->bt)
			{
                swapp(t1 , t1->next);
				
			}
        timer += t1->bt ;
	}else {
		timer += t1->bt ;
		
	}
   
  t=t->next;
 }

 

}

strcpy(buff, "");
strcat(buff, "Scheduling Method: Shortest Job First(NON Preemptive) \n");
strcat(buff, "Waiting Times:\n");

timer = 0;

   timer += t11->bt ;
    t11->tt = timer ;
	

	t11->wt = (timer - t11->bt)  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t11->wt);
	strcat(buff, buff1);


	sum += t11->wt ;
	t11=t11->next ;


while (t11 != NULL)
{


	timer += t11->bt ;
    t11->tt = timer ;
	

	t11->wt = (timer - t11->bt) - t11->at  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t11->wt);
	strcat(buff, buff1);
	sum += t11->wt ;
	t11=t11->next ;
}



avg = sum / counter ;

char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);








//__________________________preemptive mode_________________________________


}else{

int timer = 0;
double sum =0 ;
double avg = 0 ;

int c = counter ;
int j ;

struct process *f = copy (header);
struct process *ff =f;
struct process *t =f;
struct process *tt =f;
struct process *t1 =f;
struct process *t2 =f;
struct process *temp =f;



while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}





while (t1 != NULL)
	{
		t1->parts = t1->bt ;

		t1 = t1->next;
	}






for (int i=0 ; i<counter ; i++){

	tt=ff;
	timer =0;

 for (int j = 0; j < counter - 1 - i; j++){
    
	struct process *t11 =tt;
    struct process *t12 =tt->next;


	 if (t11->at <= timer && t12->at <= timer){
            if (t11->bt > t12->bt)
			{
                swapp(t11 , t11->next);
				
			}
        timer += t11->bt ;
	}else {
		timer += t11->bt ;
		
	}
   
  tt=tt->next;
 }


}



timer = 0 ;



while ( ! check(t))
{
	struct process *c = smallest(t, timer );

	bool flag = true;
		if (c == NULL)
		{
			
			temp = t;
			while (temp != NULL)
			{
				if (!temp->done)
				{
					if (temp->at > timer && flag)
					{
						flag = false;
						timer = temp->at;
						c = smallest(t, timer);
						c->parts--;
						timer++;
						if (c->parts == 0)
						{
							c->tt= timer;
							c->done = true;
						}
					}
				}

				temp = temp->next;
			}
			
		    
		}
		else
		{
			timer++;
			c->parts--;

			if (c->parts == 0)
			{
				c->tt = timer;
				c->done= true;
			}
			 
		}
   
	
}





strcpy(buff, "");
strcat(buff, "Scheduling Method: Shortest Job First (Preemptive) \n");
strcat(buff, "Waiting Times:\n");






	

	t2->wt = t2->tt - t->bt ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);

	sum += t2->wt ;
	t2=t2->next ;





while (t2 != NULL)
{

	

	t2->wt = (t2->tt - t2->bt) - t2->at  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);
	sum += t2->wt ;
	
	t2=t2->next ;
}



avg = sum / counter ;


char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);







}



}

//_________________________priority______________________________

void priorityScheduling(){

	priority = true ;

if (preemptive==0){
  

int timer = 0;
double sum = 0 ;
double avg  ; 

struct process *f = copy (header);
struct process *t =f;
struct process *ff =f;
struct process *tt =f;
struct process *t11 =f;

while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}




timer = 0;

for (int i=0 ; i<counter ; i++){

timer = 0;
t=ff;

 for (int j = 0; j < counter  - 1 - i; j++){
    
	struct process *t1 =t;
    struct process *t2 =t->next;


	 if (t1->at <= timer && t2->at <= timer){
            if (t1->pr > t2->pr)
			{
                swapp(t1 , t1->next);

			}
        timer += t1->bt ;
	}else {
	
		timer = t1->bt ;
		
	}
  t=t->next;
 }
 

}



timer = 0;

strcpy(buff, "");
strcat(buff, "Scheduling Method: Priority (NON Preemptive)\n");
strcat(buff, "Waiting Times:\n");


    timer += t11->bt ;
    t11->tt = timer ;
	

	t11->wt = (timer - t11->bt)   ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t11->wt);
	strcat(buff, buff1);


	sum += t11->wt ;
	t11=t11->next ;


while (t11 != NULL)
{


	timer += t11->bt ;
    t11->tt = timer ;
	

	t11->wt = (timer - t11->bt) - t11->at  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t11->wt);
	strcat(buff, buff1);


	sum += t11->wt ;
	t11=t11->next ;
}

avg = sum / counter ;

char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);
  

}else{

//____________________________Preemptive_____________________________________

int timer = 0;
double sum =0 ;
double avg = 0 ;

int c = counter ;
int j ;

struct process *f = copy (header);
struct process *ff =f;
struct process *t =f;
struct process *tt =f;
struct process *t1 =f;
struct process *t2 =f;
struct process *temp =f;



while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}





while (t1 != NULL)
	{
		t1->parts = t1->bt ;

		t1 = t1->next;
	}







for (int i=0 ; i<counter ; i++){

timer = 0;
t=ff;

 for (int j = 0; j < counter  - 1 - i; j++){
    
	struct process *t1 =t;
    struct process *t2 =t->next;


	 if (t1->at <= timer && t2->at <= timer){
            if (t1->pr > t2->pr)
			{
                swapp(t1 , t1->next);

			}
        timer += t1->bt ;
	}else {
	
		timer = t1->bt ;
		
	}
  t=t->next;
 }
 

}



timer = 0 ;



while ( ! check(t))
{
	struct process *c = worst(t, timer );

	bool flag = true;
		if (c == NULL)
		{
			
			temp = t;
			while (temp != NULL)
			{
				if (!temp->done)
				{
					if (temp->at > timer && flag)
					{
						flag = false;
						timer = temp->at;
						c = worst(t, timer);
						c->parts--;
						timer++;
						if (c->parts == 0)
						{
							c->tt= timer;
							c->done = true;
						}
					}
				}

				temp = temp->next;
			}
			
		    
		}
		else
		{
			timer++;
			c->parts--;

			if (c->parts == 0)
			{
				c->tt = timer;
				c->done= true;
			}
			 
		}
   
	
}





strcpy(buff, "");
strcat(buff, "Scheduling Method: Priority (Preemptive) \n");
strcat(buff, "Waiting Times:\n");






	

	t2->wt = t2->tt - t->bt ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);

	sum += t2->wt ;
	t2=t2->next ;





while (t2 != NULL)
{

	

	t2->wt = (t2->tt - t2->bt) - t2->at  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);
	sum += t2->wt ;
	
	t2=t2->next ;
}



avg = sum / counter ;


char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);









}


}

//________________________round robin_____________________________

void roundrobinScheduling(){


roundrobin = true ; 


if (quantum == NULL){

	printf("enter the time quamtum ");
    scanf("%1d" , &quantum);
}

int timer = 0;
double sum =0 ;
double avg = 0 ;

int c = counter ;
int j ;

struct process *f = copy (header);
struct process *t =f;
struct process *t1 =f;
struct process *t2 =f;


while ( f->next != NULL)
{
	if (f->at > f->next->at){
     swapp (f , f->next);

	}
	  

	 f=f->next; 
}

while (t1 != NULL)
	{
		t1->parts = t1->bt / quantum;
		t1->remain  = t1->bt % quantum;
		t1 = t1->next;
	}


while (t != NULL)
{
	if (!t->done)
	{
       if (t->parts ==0 ){
           timer += t->remain ;
		   t->tt = timer ; 
		   t->wt = t->tt - t->bt - t->at ;

		   if (t->wt < 0) t->wt = 0 ;

		   t->done = true ;
		
	   }else 
	   {
		   timer += quantum ; 
		   t->parts -- ;
		   t->tt = timer ; 
	   }
	   



	}

	t=t->next ;
}


    
strcpy(buff, "");
strcat(buff, "Scheduling Method: Round Robin  \n");
strcat(buff, "Process Waiting Times:\n");


timer = 0;

    timer += t2->bt ;
    t2->tt = timer ;
	

	t2->wt = (timer - t2->bt) ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);


	sum += t2->wt ;
	t2=t2->next ;


while (t2!= NULL)
{


	timer += t2->bt ;
    t2->tt = timer ;
	

	t2->wt = (timer - t2->bt) - t2->at  ;

	char buff1[20] = "";
	snprintf(buff1, 19, "waiting time  %d \n", t2->wt);
	strcat(buff, buff1);


	sum += t2->wt ;
	t2=t2->next ;
}

avg = sum / counter ;

char buff2[40];
snprintf(buff2, 39, "Average Waiting Time: %.3f ms\n\n", avg);
strcat(buff, buff2);
strcat(buffer_output, buff);

}


//________________________show output____________________________________

void showOutput(struct process *h){


    

  
	if (quantum == 0){

		printf("\nenter the time quantum please\n");
		scanf("%1d" , &quantum);
	}
		preemptive = 0 ;
	
		fcfsScheduling();
		sjfScheduling();
		priorityScheduling();
		roundrobinScheduling();

		preemptive = 1; 
		sjfScheduling();
		priorityScheduling();

	
	

	printf("%s", buffer_output);
	FILE *f = fopen(output, "w");
	fprintf(f, "%s", buffer_output);
	fclose(f);

   



	exit(0);
}

//____________________________swap______________________________

void swapp (struct process *h, struct process *afternode){

int a = h->at ;
int b = h->bt ;
int c = h->pr ;

h->at = afternode->at ;
h->bt = afternode->bt;
h->pr= afternode->pr;

afternode->at = a ;
afternode->bt = b;
afternode->pr = c; 

}

//___________________________Copy______________________________________

struct process* copy(struct process *h){


  if (h==NULL)
    return h ;
  else {

   struct process *t= (struct process *)malloc(sizeof(struct process));
   t->at = h->at ;
   t->bt = h->bt ;
   t->pr = h->pr ;


   t->next = copy(h->next);
   return t ;
  }

}

//__________________________check____________________________________



bool check(struct process *h)
{
	bool d = true;
	while (h!= NULL)
	{
		if (!h->done){
          h = h->next;
		  d = false ;

		}else h=h->next;
		
	}

	return d;
}

//___________________________smallest______________________________


struct process *smallest(struct process *h, int l)
{
	struct process *temp = NULL ;
	int x = 99999;
	while (h != NULL)
	{
		if (!h->done)
		{
			if (h->at <= l)
			{
				if (h->parts <= x)
				{
					temp = h;
					x = h->parts;
				}
			}
		}
		h = h->next;
	}

	return temp;
}


//________________________worst_____________________________________

struct process *worst(struct process *h, int l)
{
	struct process *temp = NULL ;
	int y = 99999;
	while (h != NULL)
	{
		if (!h->done)
		{
			if (h->at <= l)
			{
				if (h->pr <= y)
				{
					temp = h;
					y = h->pr;
				}
			}
		}
		h = h->next;
	}

	return temp;
}

//_______________________show__________________________________________

void show (){

	if (fcfs){
        
	}

	if(sjf){

	}

	if(priority){

	}

	if(roundrobin){

	}
}