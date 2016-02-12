//MIGKOTZIDIS PANAGIOTIS 2299

#include "define.h"

#define var 	    1
#define const       2
#define FUNCTION  	3
#define param		4
#define temp_var        5
    #define cv		    10
    #define ref		    20
    #define copy        30
#define notprog -1

struct parameter{//parameters linked list
    int mode;
    struct parameter *next;
};

struct Func{
  int starQuad;
  int ftype;
  char name[30];
  struct parameter *par_list;//a pointer to the parameters list(the above struct)
};

struct entity{//linked list of entities
	char name[30];//only for var param,temp and const NOT for function
	int type;//can be var,const,param,temo,func
	int offset;
	int mode;//way of passing arguments
	int value;//the value of the constant
	int nestingLevel;
    struct Func F;
	struct entity *next;
};

struct scope{
	char name[30];
	int nestinglevel;
	int framelength;
    struct entity *entity_ptr;
	struct scope *next;
};

//global variables
struct scope *scope_head=NULL;//the head of the scope list
struct parameter *par_head=NULL;

void add_scope(char name[30]){//adds to the beggining(push to list) of the list a new scope

	struct scope *new_node;
	new_node =malloc( sizeof(struct scope));

	strcpy(new_node->name,name);
	new_node->entity_ptr = NULL;
	if(scope_head==NULL){
		scope_head=new_node;
		new_node->nestinglevel=1;
		new_node->framelength=12;
		new_node->next = NULL;
	}
	else{
		new_node->nestinglevel=scope_head->nestinglevel + 1;
		new_node->framelength=12;
		new_node->next = scope_head;
		scope_head = new_node;

	}
}


void delete_scope(){//deletes a scope from the scope list

	if(scope_head==NULL){
		printf("list of scopes is empty\n");
		exit(1);
	}
	scope_head=scope_head->next;
}



void add_entity(char name[30], int type, int mode,int value){

	int last_offset=-1;//keeps the last offset
	struct entity *new_node;
	struct entity *cur;
	struct entity *previous;


	new_node=malloc(sizeof(struct entity));

    if(type==3){//case is function
        strcpy(new_node->F.name,name);

	}
	else{
        strcpy(new_node->name,name);
    }
	new_node->type = type;
	new_node->mode = mode;
	new_node->value =value;
    new_node->nestingLevel=scope_head->nestinglevel;//if equal to 0 its global variable if not it is not global
	new_node->next = NULL;

	previous=NULL;
	cur=scope_head->entity_ptr;//it must point to the entity list,which is being made throught the entity_ptr
	while(cur!=NULL){
		previous=cur;
		if(cur->type != FUNCTION){
			last_offset = cur->offset;
		}
		cur=cur->next;
	}
	if(previous==NULL){
		scope_head->entity_ptr = new_node;
		new_node->offset = 12;
		scope_head->framelength=16;

	}
	else{
		previous->next = new_node;
		new_node->offset=last_offset + 4;
		scope_head->framelength=new_node->offset+4;
	}
}



struct entity *look_up(char name[30]){//returns a pointer of the element searched and found in the symbol table,else return NULL

	struct entity *curr_entity;
	struct scope *curr_scope;
    curr_scope=scope_head;
	while(curr_scope!=NULL){
	    curr_entity = curr_scope->entity_ptr;
	    while(curr_entity!=NULL){//curr->scope name is used for recursive call of function
            if(strcmp(curr_entity->name,name)==0 || strcmp(curr_entity->F.name,name)==0 ||strcmp(curr_scope->name,name)==0){
                return curr_entity;
			}
			curr_entity=curr_entity->next;
		}
		curr_scope=curr_scope->next;
	}
	if(isdigit(name[0])){return NULL;}//for endcode when meeting digit at load and store functions

	printf("Entity was not identified in the table:%s \n",name);
	return NULL;

}


void print_table(){//prints the symbol table

    struct scope *curr_scope;//used for iterating throught the scope list,so do other curr_... variables
    struct entity *curr_entity;

    curr_scope=scope_head;

	printf("\nTHE SYMBOL TABLE IS:\n\n");
	while(curr_scope!=NULL){
            curr_entity=curr_scope->entity_ptr;
            printf("Scope_name : %s\n",curr_scope->name);
            printf("--------------------\n");

		while(curr_entity!=NULL){
                    if(curr_entity->type==var){//case variable
                        printf("(%s,%d) - \n",curr_entity->name, curr_entity->offset);
                    }
                    else if(curr_entity->type==param){//case parameter
                        printf("(parameter %s,%d) - \n",curr_entity->name, curr_entity->offset);
                    }
                    else if(curr_entity->type==const){//case constant,is not used in current code for stange compiler
                        printf("(constant:(%s,%d) - value:%d) - \n",curr_entity->name, curr_entity->offset,curr_entity->value);
                    }
                    else if(curr_entity->type==temp_var){//case for temporaty variables,(see in syntax.h the char *w)
                         printf("(temp:(%s,%d)) - \n",curr_entity->name, curr_entity->offset);
                    }
                    else{//case function

                        printf("%s - \n",curr_entity->F.name);
                    }
                    curr_entity=curr_entity->next;
		}

		printf("\n\n");
        curr_scope=curr_scope->next;
	}
}






