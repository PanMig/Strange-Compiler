//MIGKOTZIDIS PANAGIOTIS AM:2299

#include"symbol_table.h"
#include "intercode.h"

typedef struct endcode_list{//a list that keeps the endcode
    char str[100];
    struct endcode_list *next;
}endlist;

//global variables
endlist *endlist_head;
int par_counter=0;
int label_number=100;
char hold_program_name[30];//holds the program name


/*void print_endcode(){
    FILE *output;
    output=fopen("endcode.s","w");
    if(output==NULL){
            printf("\nerror open for writing to the endcode.s file\n");
            exit(EXIT_FAILURE);
    }

    //print to file from list
    endlist *cur=endlist_head;

    while(cur!=NULL){
        fprintf(output,"%s",cur->str);
        cur=cur->next;
    }

}*/

void print_endcode(){

        //print to file from list
        endlist *cur=endlist_head;

        while(cur!=NULL){
            fprintf(fe,"%s",cur->str);
            cur=cur->next;
        }

}



void insert_endlist(char sented_str[100]){
    endlist *cur,*new_node;
    cur=endlist_head;
    new_node=malloc(sizeof(endlist));
    strcpy(new_node->str,sented_str);
    if(endlist_head==NULL){
           endlist_head=new_node;
           new_node->next=NULL;
    }
    else{

        while(cur->next!= NULL){
            cur = cur -> next;
        }
         cur->next=new_node;
        cur->next->next=NULL;
    }

}

void free_end_list(){//makes the quad list empty
    endlist *cur1=endlist_head;
    endlist *cur2;
    while(cur1!=NULL){
        cur2=cur1->next;
        free(cur1);
        cur1 = cur2;
    }
    endlist_head = NULL;//This was made to avoid conflictions when multiple endlist had to be printed
}



void gnlvcode(char name[30]){//puts to R[255] the address of a NON local variable
    char code_str[100];
    struct entity *symbol;
    symbol=look_up(name);//returns the address of the symbol that was sent

    sprintf(code_str,"\t movi R[255],M[R[0]+4]\n");
    insert_endlist(code_str);

    while(symbol->nestingLevel!=scope_head->nestinglevel){
        sprintf(code_str,"\t movi R[255],M[4+R[255]]\n");
        insert_endlist(code_str);
        symbol->nestingLevel++;
    }

    sprintf(code_str,"\t movi R[254],%d\n",symbol->offset);
    insert_endlist(code_str);

    sprintf(code_str,"\t addi R[255],R[254],R[255]\n");
    insert_endlist(code_str);

}


void loadvr(char v[30],int r){
    //symbol lookup
    struct entity *symbol;
    symbol=look_up(v);
    char code_str[100];
    //cases

    if(isdigit(v[0])){//case v is number
            sprintf(code_str,"\t movi R[%d],%s\n",r,v);
            insert_endlist(code_str);
    }
    else{//case v is alpha

        if(symbol->nestingLevel==1 && symbol->type!=temp_var){//case is global variable
            sprintf(code_str,"\t movi R[%d],M[%d]\n",r,600+symbol->offset);
            insert_endlist(code_str);
        }
        else{
            if(symbol->nestingLevel==scope_head->nestinglevel){//for cases where nesting of an entity is equal to current scope
            //e.g topic variables

                if(symbol->type==var || symbol->type==param && symbol->mode==cv ||symbol->type==temp_var){//local var or param(cv) or tmp
                    sprintf(code_str,"\t movi R[%d],M[%d+R[0]]\n",r,symbol->offset);
                    insert_endlist(code_str);
                }

                else if(symbol->type==param && symbol->mode==ref){//param(ref)
                    sprintf(code_str,"\t movi R[255],M[%d+R[0]\n",symbol->offset);
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi R[%d],M[R[255]]\n",r);
                    insert_endlist(code_str);
                }

            }
            else if(symbol->nestingLevel < scope_head->nestinglevel){//for cases where nesting of an entity is lesser to current scope

                if(symbol->type==var || symbol->type==param &&symbol->mode==cv){
                    gnlvcode(symbol->name);
                    sprintf(code_str,"\t movi R[%d],M[R[255]]\n",r);
                    insert_endlist(code_str);

                }
                else if(symbol->type==param && symbol->mode==ref){
                    gnlvcode(symbol->name);
                    sprintf(code_str,"\t movi R[255],M[R[255]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi R[%d],M[R[255]]\n",r);
                    insert_endlist(code_str);
                }
            }
        }
    }


}

void store(int r,char v[30]){
    char code_str[100];
    struct entity *symbol;
    symbol=look_up(v);

    if(symbol->nestingLevel==1 && symbol->type!=temp_var){//if is global
        sprintf(code_str,"\t movi M[%d],R[%d]\n",600+symbol->offset,r);
        insert_endlist(code_str);
    }

    else{
            if(symbol->nestingLevel == scope_head->nestinglevel){

                if(symbol->type==var || symbol->type==param && symbol->mode==cv ||symbol->type==temp_var){
                    sprintf(code_str,"\t movi M[%d+R[0]],R[%d]\n",symbol->offset,r);
                    insert_endlist(code_str);
                }
                else if(symbol->type==param && symbol->mode==ref){
                    sprintf(code_str,"\t movi R[255],M[%d+R[0]]\n",symbol->offset);
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi M[R[255]],R[%d]\n",r);
                    insert_endlist(code_str);
                }
            }
            else if(symbol->nestingLevel < scope_head->nestinglevel){
                if(symbol->type==var || symbol->type==param &&symbol->mode==cv){
                        gnlvcode(symbol->name);
                        sprintf(code_str,"\t movi M[R[255]],R[%d]\n",r);
                        insert_endlist(code_str);
                }
                else if(symbol->type==param && symbol->mode==ref){
                        gnlvcode(symbol->name);
                        sprintf(code_str,"\t movi R[255],M[R[255]]\n");
                        insert_endlist(code_str);
                        sprintf(code_str,"\t movi M[R[255]],R[%d]\n",r);
                        insert_endlist(code_str);
                }

            }

    }


}


void create_endcode(){

    char code_str[100];//a string used to keep the lines that will be printed in the input file for metasim

    node *cur=head;//cur point to the head of the quadraples list

    while(cur!=NULL){

        sprintf(code_str,"L%d",cur->tetrada.label);
        insert_endlist(code_str);


        //jump commands
        if(strcmp(cur->tetrada.op,"jump")==0){
            sprintf(code_str,"\t jmp L%s\n",cur->tetrada.result);
            insert_endlist(code_str);
        }//jump compare commands
        else if(strcmp(cur->tetrada.op,"=")==0||
                strcmp(cur->tetrada.op,"<>")==0||
                strcmp(cur->tetrada.op,"<")==0||
                strcmp(cur->tetrada.op,"<=")==0||
                strcmp(cur->tetrada.op,">")==0||
                strcmp(cur->tetrada.op,">=")==0
        ){
        loadvr(cur->tetrada.arg1,1);
        loadvr(cur->tetrada.arg2,2);
        sprintf(code_str,"\t cmpi R[1],R[2]\n");
        insert_endlist(code_str);

        //different types of operators
        //its operator has a unique jump
        if(strcmp(cur->tetrada.op,"=")==0){sprintf(code_str,"\t je L%s\n",cur->tetrada.result);insert_endlist(code_str);}
        else if(strcmp(cur->tetrada.op,"<>")==0){sprintf(code_str,"\t jne L%s\n",cur->tetrada.result);insert_endlist(code_str);}
        else if(strcmp(cur->tetrada.op,">")==0){sprintf(code_str,"\t jb L%s\n",cur->tetrada.result);insert_endlist(code_str);}
        else if(strcmp(cur->tetrada.op,">=")==0){sprintf(code_str,"\t jbe L%s\n",cur->tetrada.result);insert_endlist(code_str);}
        else if(strcmp(cur->tetrada.op,"<")==0){sprintf(code_str,"\t ja L%s\n",cur->tetrada.result);insert_endlist(code_str);}
        else if(strcmp(cur->tetrada.op,"<=")==0){sprintf(code_str,"\t jae L%s\n",cur->tetrada.result);insert_endlist(code_str);}

        }

        //assignment operator
        else if(strcmp(cur->tetrada.op,":=")==0){
            loadvr(cur->tetrada.arg1,1);
            store(1,cur->tetrada.result);
        }

        //math commands

        //add(+)
        else if(strcmp(cur->tetrada.op,"+")==0){
            loadvr(cur->tetrada.arg1,1);
            loadvr(cur->tetrada.arg2,2);
            sprintf(code_str,"\t addi R[3],R[1],R[2]\n");
            insert_endlist(code_str);
            store(3,cur->tetrada.result);
        }
        //sub(-)
        else if(strcmp(cur->tetrada.op,"-")==0){
            loadvr(cur->tetrada.arg1,1);
            loadvr(cur->tetrada.arg2,2);
            sprintf(code_str,"\t subi R[3],R[1],R[2]\n");
            insert_endlist(code_str);
            store(3,cur->tetrada.result);
        }
        //multi(*)
        else if(strcmp(cur->tetrada.op,"*")==0){
            loadvr(cur->tetrada.arg1,1);
            loadvr(cur->tetrada.arg2,2);
            sprintf(code_str,"\t muli R[3],R[1],R[2]\n");
            insert_endlist(code_str);
            store(3,cur->tetrada.result);
        }
        //division(/)
        else if(strcmp(cur->tetrada.op,"/")==0){
            loadvr(cur->tetrada.arg1,1);
            loadvr(cur->tetrada.arg2,2);
            sprintf(code_str,"\t divi R[3],R[1],R[2]\n");
            insert_endlist(code_str);
            store(3,cur->tetrada.result);
        }

        //print command(out)
        else if(strcmp(cur->tetrada.op,"out")==0){
            loadvr(cur->tetrada.arg1,1);
            sprintf(code_str,"\t outi R[1]\n");
            insert_endlist(code_str);
        }
        //return command
        else if(strcmp(cur->tetrada.op,"retv")==0){
            loadvr(cur->tetrada.arg1,1);
            sprintf(code_str,"\t movi R[255],M[%d + R[0]]\n",8);
            insert_endlist(code_str);
            sprintf(code_str,"\t movi M[R[255]],R[1]\n");
            insert_endlist(code_str);
        }

        //function calling
        else if(strcmp(cur->tetrada.op,"call")==0){
            struct entity *symbol;
            symbol=look_up(cur->tetrada.arg1);

            if(symbol->nestingLevel==scope_head->nestinglevel){
                    sprintf(code_str,"\t movi R[255],M[4+R[0]]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi M[%d+R[0]],R[255]\n",scope_head->framelength+4);
                    insert_endlist(code_str);
            }
            else if(symbol->nestingLevel > scope_head->nestinglevel){

                    sprintf(code_str,"\t movi M[%d+R[0]],R[0]\n",scope_head->framelength+4);
                    insert_endlist(code_str);
            }
            //called function assembly commands
            sprintf(code_str,"\t movi R[255],%d\n",scope_head->framelength);
            insert_endlist(code_str);
            sprintf(code_str,"\taddi R[0],R[255],R[0]\n");
            insert_endlist(code_str);
            sprintf(code_str,"\t movi R[255],$\n");
            insert_endlist(code_str);
            sprintf(code_str,"\t movi R[254],%d\n",15);
            insert_endlist(code_str);
            sprintf(code_str,"\t addi R[255],R[255],R[254]\n");
            insert_endlist(code_str);
            sprintf(code_str,"\t movi M[R[0]],R[255]\n");
            insert_endlist(code_str);
            sprintf(code_str,"\t jmp L%d\n",symbol->F.starQuad);//TODO: find start quad
            insert_endlist(code_str);
            sprintf(code_str,"\t movi R[255],%d\n",scope_head->framelength);
            insert_endlist(code_str);
            sprintf(code_str,"\t subi R[0],R[0],R[255]\n");
            insert_endlist(code_str);

        }

        //parameters
        else if(strcmp(cur->tetrada.op,"par")==0){
                struct entity *symbol;
                symbol=look_up(cur->tetrada.arg1);

                //case CV
                if(strcmp(cur->tetrada.arg2,"CV")==0){
                    int d;
                    d=scope_head->framelength+12+4*par_counter;
                    par_counter++;
                    loadvr(cur->tetrada.arg1,255);
                    sprintf(code_str,"\t movi M[%d +R[0]],R[255]\n",d);
                    insert_endlist(code_str);

                }//case RET
                else if(strcmp(cur->tetrada.arg2,"RET")==0){
                    sprintf(code_str,"\t movi R[255],R[0]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi R[254],%d\n",symbol->offset);
                    insert_endlist(code_str);
                    sprintf(code_str,"\t addi R[255],R[254],R[255]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi M[%d+R[0]],R[255]\n",scope_head->framelength+8);
                    insert_endlist(code_str);
                }
                //case REF
                else if(strcmp(cur->tetrada.arg2,"REF")==0){
                        int d=scope_head->framelength+12+4*par_counter;
                        par_counter++;
                    if(symbol->nestingLevel==scope_head->nestinglevel){
                            if(symbol->type==var || symbol->type==param && symbol->mode==cv){

                                sprintf(code_str,"\t movi R[255],R[0]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi R[254],%d\n",symbol->offset);
                                insert_endlist(code_str);
                                sprintf(code_str,"\t addi R[255],R[254],R[255]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi M[%d+R[0]],R[255]\n",d);
                                insert_endlist(code_str);

                            }
                            else if(symbol->type==param && symbol->mode==ref){

                                sprintf(code_str,"\t movi R[255],R[0]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi R[254],%d",symbol->offset);
                                insert_endlist(code_str);
                                sprintf(code_str,"\t addi R[255],R[254],R[255]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi R[1],M[R[255]]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi M[%d+R[0]],R[1]\n",d);
                                insert_endlist(code_str);

                            }
                    }
                    else{
                         if(symbol->type==var || symbol->type==param && symbol->mode==cv){
                                //insert_endlist(code_str);
                                gnlvcode(symbol->name);
                                sprintf(code_str,"\t movi M[%d+R[0]],R[255]\n",d);
                                insert_endlist(code_str);
                                //insert_endlist(code_str);

                         }
                         else if(symbol->type==param && symbol->mode==ref){

                                gnlvcode(symbol->name);
                                sprintf(code_str,"\t movi R[1],M[R[255]]\n");
                                insert_endlist(code_str);
                                sprintf(code_str,"\t movi M[%d+R[0]],R[1]\n",d);
                                insert_endlist(code_str);

                         }
                    }
                }

                //case COPY
                if(strcmp(cur->tetrada.arg2,"COPY")==0){
                        int d=scope_head->framelength+12+4*par_counter;
                        par_counter++;
                    sprintf(code_str,"\t movi R[255],R[0]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi R[254],%d\n",symbol->offset);
                    insert_endlist(code_str);
                    sprintf(code_str,"\t addi R[255],R[254],R[255]\n");
                    insert_endlist(code_str);
                    sprintf(code_str,"\t movi M[%d+R[0]],R[255]\n",d);
                    insert_endlist(code_str);
                }
      }
      else if(strcmp(cur->tetrada.op,"halt")==0){
            sprintf(code_str,"\t halt\n");
            insert_endlist(code_str);

      }
      else if(strcmp(cur->tetrada.op,"end_block")==0){
            if(strcmp(cur->tetrada.arg1,hold_program_name)==0){
                    //just halt cause we are at main

            }
            else{
                sprintf(code_str,"\t jmp M[R[0]]\n");
                insert_endlist(code_str);
            }
      }
      else if(strcmp(cur->tetrada.op,"begin_block")==0){
                sprintf(code_str,"\n");
                insert_endlist(code_str);

      }

        cur=cur->next;


    }


}


