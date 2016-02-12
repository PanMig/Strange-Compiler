//MIGKOTZIDIS PANAGIOTIS:2299


//FULL functions of intermediate code-------------------------------------------------------

#include "define.h"


struct quad{//a structure that creates a quad
	int label;
	char op[30];
	char arg1[30];
	char arg2[30];
	char result[30];
}tetrada;

typedef struct boolean_list{//the list tha stores only label numbers
    int etiketa;//The label of the quad
    struct boolean_list *next;
}label_node;

typedef struct list_node{/*The general list used to store quads,consists of two cell one for storing the quad and another
    for pointing to the next cell of the list*/
	struct quad tetrada;
	struct list_node *next;
}node;


//global variables
int nextquad=100;

node *head;//the head of list that contains quads
label_node *label_head;//the head of list that contains labels

char assign_value[30];//takes the variable where an expression is stored,location(statement,assignment_stat)
char add_symbol[30];//used to store the + or - symbol
char mul_symbol[30];//used to store the * or / symbol
char relop[30];//used to store relational operators
char help[30];//a string used for passing the value of a pointer that cannot be accessed by some functions
char *E_place;
char *T_place;
char *F_place;
int temp_num=1;//it's the number of the temp variable


//functions
char* new_temp(){/*creates a temp variable of type char[30] that looks like $i where i is increased it's time the
    fuction is called*/

    char *temp=(char*) malloc(sizeof(30));
    sprintf(temp,"T_%d",temp_num);//assign to temp temp_num
    temp_num+=1;
    return temp;
}


label_node* merge(label_node *list1,label_node *list2){//takes to pointers to lists and merge them,producing 1 sorted list
    if (!list1) return list2;
    if (!list2) return list1;

     label_node *tmp;

     // compare head nodes and swap lists to guarantee list1 has the smallest node
     if(list1->etiketa > list2->etiketa) {
        tmp = list2;
        list2 = list1;
        list1 = tmp;
    }

    label_node *tail = list1;

        do {
        // Advance the tail pointer skipping over all the elements in the result
        // which have smaller or equal etiketa(label) than the first node on list2
        while (tail->next && (tail->next->etiketa <= list2->etiketa)) {
            tail = tail->next;
        }
        // move list2 at tail of result and make the rest after tail list2
        tmp = tail->next;
        tail->next = list2;
        tail = list2;
        list2 = tmp;
    } while (list2);

    return list1;//return head of list1
}

void free_quad_list(){//makes the quad list empty
    node *cur1=head;
    node * cur2;
    while(cur2!=NULL){
        cur2=cur1->next;
        free(cur1);
        cur1 = cur2;
    }
    head = NULL;//This was made to avoid conflictions when multiple quad list had to be printed
}


void print_quad_list(){//prints the quad list

	node *cur=head;//it is a current variable that is used for iterating through the list
	if(cur==NULL){
		printf("list is empty");
	}
	while(cur!=NULL){

        fprintf(fc,"\n%d\t %s\t %s\t %s\t %s\t\n",cur->tetrada.label,cur->tetrada.op,cur->tetrada.arg1,cur->tetrada.arg2,cur->tetrada.result);
		cur=cur->next;
	}
}



void print_label_list(label_node *sented_head){//prints the label list

    label_node *cur=sented_head;//it is a current variable that is used for iterating through the list
	if(cur==NULL){
		printf("label list is empty");
	}
	while(cur!=NULL){
        printf("%d\n",cur->etiketa);
		cur=cur->next;

	}

}


void genquad(char op[30],char arg1[30],char arg2[30],char result[30]){//generades a quad and inserts it in the quad list
    node *cur=head;

    //create new node to be inserted at the end
    node *new_node=malloc(sizeof(node));
    //assign values to the new node
    new_node->tetrada.label=nextquad;
    nextquad+=10;
    strcpy(new_node->tetrada.op,op);
	strcpy(new_node->tetrada.arg1,arg1);
	strcpy(new_node->tetrada.arg2,arg2);
	strcpy(new_node->tetrada.result,result);
	new_node->next=NULL;

    if(head==NULL){//case list is empty
        head=new_node;

    }
    else if(head!=NULL){//case list is not empty
        while(cur -> next != NULL){
        cur = cur -> next;
        }
        cur->next = new_node;
        cur->next->next=NULL;
    }
}

label_node* emptylist(){//creates an empty list
    label_node *temp_list=NULL;
    return temp_list;
}

label_node* makelist(int quad_number){//creates a list with one int element
    label_node *temp_list=malloc(sizeof(label_node));
    temp_list->etiketa=quad_number;
    temp_list->next=NULL;
    return temp_list;
}

void backpatch(label_node *list,int label_number){
     node *cur=head;//head of quadruples list
     label_node *temp=list;//head of list containing labels
     while(cur!=NULL && temp!=NULL){
        if(temp->etiketa==cur->tetrada.label){
               sprintf(cur->tetrada.result,"%d",label_number);
                temp=temp->next;
        }
        cur=cur->next;
        //when the list of label has no more cell we break out of the while loop
    }

}


