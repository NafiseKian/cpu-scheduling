
#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>




struct process{

int at ; //arrival time
int bt;  // burst time
int pr;  //priority
int tt ; //turnaround time
int wt ; //waiting time

struct process* next ;

};
//__________________________Functions____________________________



struct process *createProcess( int, int, int);
struct process *insertBack(struct process *, int, int, int);
struct process *deleteFront(struct process *);
struct process *swap (struct process * , struct process *);
struct process *copy(struct process *);
void display(struct process *header);
void schedulingMethod (int );
void fcfsScheduling(struct process *);
void sjfScheduling ();
void priorityScheduling();
void roundrobinScheduling();
void showOutput(struct process*);

//__________________________Variables____________________________

char* input  ;
char* output  ;
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
     int counter = 0;

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
			       fscanf(file, "%d:%d:%d\n", &arrival, &burst, &priority);
                   header = insertBack(header , arrival , burst , priority);
			       counter++;
		        }
	       }

         fclose(file);

        
         
		printf("1)Scheduling Method(none) \n2)Preemptive Mode(OFF/ON)\n3)showResult\n4)End Program \n type:");
		int choice ;
		scanf("%1d", &choice);

        switch (choice)
		{
		case 1 :
		      int mode; 
			  printf("\n1)none \n2)first come first serve \n3)shortest job first\n4)priority scheduling\n5)Round Robin\ntype:");
			  scanf("%1d" , &mode);
			  schedulingMethod (mode);
			break;

		case 2 :
			  preemptive = true;
			break;

		case 3 :
			  //call a function
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


struct process *insertBack(struct process *header, int burst , int arrival, int priority)
{
	struct process *temp = createProcess( burst, arrival, priority);
	struct process *ht;

	
	if (header == NULL)
	{
		header = temp;
		return header;
	}

	ht = header;

	while (ht->next != NULL) 
		ht = ht->next;

	ht->next = temp;
	
	return header;
}

//_____________________________delete_______________________________


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

//____________________________swap______________________________

struct process *swap (struct process *h1 , struct process *h2){

while (h1->next != h2)
    h1=h1->next;

struct process *t = h2->next->next;
h1->next = h2->next ;
h2->next = t;
h1->next->next=h2;

printf("im done");
return h1;

}

//___________________________Copy______________________________________

struct process *copy(struct process *h){

   struct process *t = h ;
   struct process *cp ;

   while (t->next!= NULL)
   {
	int a = t->at;
	int b = t->bt;
	int c = t->pr;
	
	cp = insertBack(cp ,  a , b ,c );
	t=t->next;
   }
   
 return cp ; 
}

//___________________________Display____________________________________

void display(struct process *h)
{
	struct process *temp = h ;

while (temp != NULL)
{
	printf("%d \n %d \n %d" ,temp->at , temp->bt, temp->wt );
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
	   fcfsScheduling(header);
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

void fcfsScheduling(struct process *h){

struct process *f ;

f = copy(h);


while (f->next!= NULL)
{
	if (f->at >= f->next->at )
	swap (h , f->next->next);

    f=f->next ; 

}







}

//___________________________sjf________________________________

void sjfScheduling (){


}

//_________________________priority______________________________

void priorityScheduling(){


}

//________________________round robin_____________________________

void roundrobinScheduling(){



}


//________________________show output____________________________________

void showOutput(struct process *h){




    FILE *f = fopen(output, "w");
    fprintf(f , "working ! ");
	fclose(f);


    exit(0);

}

