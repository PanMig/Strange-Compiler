//MIGKOTZIDIS PANAGIOTIS:2299

#include "lex.h"
#include "endcode.h"

//function prototypes
void program(); void block();void varlist();void subprograms();void func();void funcbody();void formalpars();
void formalparitem();void formalparlist();void declarations();void sequence();void statement();void sequence();void brackets_seq();void brack_or_stat();
void assignment_stat();void if_stat();void while_stat();void do_while_stat();void exit_stat();void incase_stat();void call_stat();void forcase_stat();
void boolfactor();void expression();void boolterm();void condition();void actualparitem();void actualparlist();void actualpars();void elsepart();
void term(); void factor();void idtail();void relational_oper();void add_oper();void mul_oper();void optional_sign();void return_stat();void print_stat();

int begin_quad=0;
int main_quad;
int flag=0;
char help_idtail[30];

//syntax analyzer
void program(){

	if(token_id==program_id){
		token_id=lex();
		if(token_id==variable){
            char program_name[30];//holds the program name from the st.file
            strcpy(program_name,lexis);
            strcpy(hold_program_name,program_name);
            add_scope(program_name);//we add the main function scope
            token_id=lex();
			block(program_name);
            print_table();
            print_quad_list();
            create_endcode();
            free_quad_list();
            delete_scope();//delete the main function scope

		}
		else{
			printf("program name expected\n");
			exit(1);
		}

	}
	else{
			printf("keyword program expected\n");
			exit(1);
	}
	if(token_id==eof){

		    	//printf("\nsuccess\n,program has NO syntax errors\n\n");

	}
	else{
		printf("program has syntax errors,check for possible missing open brackets\n");
		    	exit(1);

	}

}


void block(char program_or_function_name[30]){

	if(token_id==OPEN_BRACKET){
        token_id=lex();
		//used for finding the main start quad of the program
        if(begin_quad==0){
            main_quad=nextquad;
        }
        genquad("begin_block",program_or_function_name,"_","_");
        declarations();
        subprograms();
		sequence();
		if(scope_head->nestinglevel==1){
            genquad("halt","_","_","_");
		}
		genquad("end_block",program_or_function_name,"_","_");


		if(token_id != CLOSE_BRACKET){
			printf("Bracket is not closed in program block\n");
			exit(1);

		}
		else{
			token_id=lex();
		 }

	}

	else{
		printf("expected open bracket after program or function/procedure name declaration\n");
		exit(1);
	}
}


void declarations(){

	if(token_id==declare_id){
		token_id=lex();
		varlist();
		if(token_id != enddeclare_id){
			printf("keyword enddeclare was expected\n");
			exit(1);
		}
		else{
			token_id=lex();

		}
	}

}


void varlist(){

	if(token_id==variable){

        add_entity(lexis,1,0,0);//add a variable to the current scope
		token_id=lex();

		while(token_id==COMMA){

			token_id=lex();
			if(token_id!=variable){
				printf("variable was expected\n");
				exit(1);
			}

			else{
                add_entity(lexis,1,0,0);//add a variable to the current scope
				token_id=lex();
            }
		}

	}
}

void subprograms(){

	while(token_id==procedure_id || token_id==function_id){
		token_id=lex();
		func();
	}

}

void func(){

	if(token_id == variable){
	    char func_name[30];
        strcpy(func_name,lexis);
        add_entity(func_name,3,0,0);//add the function name to the current scope
        //find name of program or function
            struct entity *symbol;
            symbol=look_up(func_name);
            symbol->F.starQuad=nextquad;//put the begin_block quad to the fuction struct,used for endcode when we want to jump to the beggining quad
            symbol->F.ftype=notprog;//not used currently in this code,for future use
        //found
        token_id=lex();
        add_scope(func_name);//add a new scope,which is the last entity that we added in the previous scope
		funcbody(func_name);
		print_table();
		create_endcode();
		print_quad_list();
		free_quad_list();
		delete_scope();//deletes the function or procedure scope


	}
	else{
		printf("variable was expected after keyword function or procedure\n");
		exit(1);
	}
}

void funcbody(char func_proc_name[30]){

	formalpars();
	block(func_proc_name);

}

void formalpars(){
	if(token_id==OPEN_PARENTH){
		token_id=lex();
		formalparlist();
		if(token_id!=CLOSE_PARENTH){

			printf("expected ')' in formal parameters declaration \n");
			exit(1);
		}
		else{

			token_id=lex();

		}
	}
	else{
        printf("expected open parenthesis before parameters delcaration /n");
        exit(1);
	}
}

void formalparlist(){
	formalparitem();
	while(token_id==COMMA){
		token_id=lex();
		formalparitem();
	}
}

void formalparitem(){
	if(token_id==in_id){
            token_id=lex();
		if(token_id!=variable){
			printf("expected variable name after in \n");
			exit(1);
		}
		else{
		    add_entity(lexis,4,10,0);//add the type cv parameter


			token_id=lex();

		}
	}
	else if(token_id==inout_id){
		token_id=lex();
		if(token_id!=variable){
			printf("expected variable name after inout \n");
			exit(1);
		}
		else{
            add_entity(lexis,4,20,0);//add the type ref parameter

            token_id=lex();
        }
	}
	else if(token_id==copy_id){
		token_id=lex();
		if(token_id!=variable){
			printf("expected variable name after copy \n");
			exit(1);
		}
		else{
            add_entity(lexis,4,30,0);//add the type copy parameter

			token_id=lex();
        }

	}
	/*else{
		printf("parameters where expected\n");
		exit(1);
	}*/
}

void sequence(){

	statement();
	while(token_id==QUESTMARK){
		token_id=lex();
		statement();
	}

}

void brackets_seq(){

		sequence();
        if(token_id!=CLOSE_BRACKET){
			printf("expected '}' in brackets_seq \n");
			exit(1);
		}
		else{

			token_id=lex();

		}
	}



void brack_or_stat(){

	if(token_id==OPEN_BRACKET){
		token_id=lex();
		brackets_seq();
    }
	else{
		statement();
	}
}

//function calling statements
void statement(){


    while( token_id==print_id || token_id==return_id || token_id==variable || token_id==if_id ||token_id==while_id||token_id==do_id||token_id==forcase_id||token_id==incase_id
    ||token_id==call_id||token_id==exit_id)
    {

             if(token_id==variable){
                strcpy(assign_value,lexis);//takes the variable where an expression is stored
                token_id=lex();
                assignment_stat();
            }

             if(token_id==if_id){

                token_id=lex();
                if_stat();
            }
             if(token_id==while_id){
                token_id=lex();
                while_stat();

            }
             if(token_id==do_id){
                token_id=lex();
                do_while_stat();

            }

            if(token_id==forcase_id){
                token_id=lex();
                forcase_stat();

            }
             if(token_id==incase_id){
                token_id=lex();
                incase_stat();
            }
            if(token_id==call_id){
                token_id=lex();
                call_stat();
            }

            if(token_id==return_id){
                token_id=lex();
                return_stat();
            }

            if(token_id==print_id){
                token_id=lex();
                print_stat();
            }

            if(token_id==exit_id){
                token_id=lex();
                exit_stat();
            }


    }

}

//statements

void assignment_stat(char *E_place){

		if(token_id!=DOT_EQ){
			printf("':=' expected \n ");
			exit(1);
		}
		else{

			token_id=lex();

			expression(&E_place);
            genquad(":=",E_place,"_",assign_value);

		}


}

void if_stat(){// p1,p2,p3 are the markers where code for the intermediate code must be fitted,

    if(token_id==OPEN_PARENTH){
			token_id=lex();
			label_node *b_true;
			label_node *b_false;
			condition(&b_true,&b_false);
			//p1
			backpatch(b_true,nextquad);
			//end of p1
			if(token_id != CLOSE_PARENTH){
				printf(" ')' was expected in if_stat \n");
				exit(1);
			}
			else{
				token_id=lex();
				brack_or_stat();
				//p2
				label_node *iflist=makelist(nextquad);
				genquad("jump","_","_","_");
				backpatch(b_false,nextquad);
				//end of p2
				elsepart();
				//p3
				backpatch(iflist,nextquad);
				//end of p3
			}
		}


	else{
		printf(" parenthesis expected after the if statement \n ");
		exit(1);
	}

}

void elsepart(){

    if (token_id==else_id){
		token_id=lex();
		brack_or_stat();
	}
}

void do_while_stat(){
        //p1
        int S_quad;
        S_quad=nextquad;
        //end of p1
		brack_or_stat();
		if(token_id!=while_id){
			printf("while expected after the close bracket of do or bracket is not closed in do\n");
			exit(1);
		}
		else{
			token_id=lex();
			if(token_id==OPEN_PARENTH){
				token_id=lex();
				label_node *b_true;
				label_node *b_false;
				condition(&b_true,&b_false);
                //p2
                backpatch(b_true,S_quad);
                backpatch(b_false,nextquad);
                //end of p2
				if(token_id != CLOSE_PARENTH){
					printf(" ')' was expected after while condition \n");
					exit(1);
				}
				else token_id=lex();


			}
			else {
				printf(" '(' was expected before while condition\n"); exit(1);
			}

		}
}

void exit_stat(){
    genquad("exit","_","_","_");
}

void return_stat(){

		if(token_id == OPEN_PARENTH){
             token_id=lex();
			expression(&E_place);
			genquad("retv",E_place,"_","_");
			if(token_id!=CLOSE_PARENTH){
				printf(" ')' was expected in return_stat ");
				exit(1);
			}
			token_id=lex();
		}
		else{
			printf(" '(' was expected after return keyword \n ");
			exit(1);
		}


}

void print_stat(){

		if(token_id==OPEN_PARENTH){
            token_id=lex();
			expression(&E_place);
            genquad("out",E_place,"_","_");
			if(token_id!=CLOSE_PARENTH){
				printf(" ')' was expected after print\n ");
				exit(1);
			}
			token_id=lex();

		}
		else{
			printf(" '(' was expected after print \n ");
			exit(1);
		}


}

void while_stat(){
        //p1
        int B_quad;//keeps the start of the loop
        B_quad=nextquad;
       //end of p1
		if(token_id==OPEN_PARENTH){
			token_id=lex();
			label_node *b_true;
			label_node *b_false;
			condition(&b_true,&b_false);
			//p2
			backpatch(b_true,nextquad);
            //end of p2
			if(token_id!=CLOSE_PARENTH){
				printf(" ')' was expected in while_stat \n");
				exit(1);
			}
			else{
                token_id=lex();
                char while_quad[30];
                sprintf(while_quad,"%d",B_quad);//genquads accepts type char [30] and B_quad is type int so we use sprintf
                brack_or_stat();
                genquad("jump","_","_",while_quad);
                backpatch(b_false,nextquad);
            }
		}
		else{
			printf("parenthesis expected after while \n ");
			exit(1);
		}


}

void incase_stat(){
    //p0
    int P_quad=nextquad;//keep the quad where the loop starts
    genquad(":=","1","_","flag");//flag is used for telling the program when to return,it's value has values 1 or 0
    //end of p0
   if(token_id==OPEN_BRACKET){
           token_id=lex();
           while(token_id==when_id){
               token_id=lex();
               if(token_id==OPEN_PARENTH){
               	     token_id=lex();
               	     label_node *b_true;
                     label_node *b_false;
                     condition(&b_true,&b_false);//p1 starts after condition
                     //p1
                     backpatch(b_true,nextquad);
                     genquad(":=","0","_","flag");
                     //end of p1
                     if(token_id==CLOSE_PARENTH){
                      token_id=lex();
                      brack_or_stat();
                      //p2
                      backpatch(b_false,nextquad);
                      //end of p2
                      	if(token_id==CLOSE_BRACKET){
                      		token_id=lex();
                      	}
                      	else{
                      		printf("close bracket expected in incase stat\n");
                      		exit(1);
                      	}
                     }
                     else{
                      printf("close parenthesis expected after while stat\n");
                      exit(1);
                     }
               }
               else{
               		printf("close parenthesis expected after when in incase stat\n");
               		exit(1);
               }

           }
           //p3
           char incase_quad[30];
           sprintf(incase_quad,"%d",P_quad);
           genquad("=","0","flag",incase_quad);
           //end of p3
       }
       else{
            printf("open bracket expected after incase\n");
            exit(1);
       }

}

void forcase_stat(){
    //p0
    int start_quad=nextquad;
    //end of p0
   if(token_id==OPEN_BRACKET){
           token_id=lex();

           while(token_id==when_id){
               token_id=lex();

               if(token_id==OPEN_PARENTH){
               	     token_id=lex();
               	     label_node *b_true;
                     label_node *b_false;
                     condition(&b_true,&b_false);
                     //p1
                     backpatch(b_true,nextquad);
                     //end of p1
                     if(token_id==CLOSE_PARENTH){
                      token_id=lex();
                      brack_or_stat();
                      //p2
                      char forcase_quad[30];
                      sprintf(forcase_quad,"%d",start_quad);
                      genquad("jump","_","_",forcase_quad);
                      backpatch(b_false,nextquad);
                      //end of p2
                      	if(token_id==CLOSE_BRACKET){
                      		token_id=lex();
                      	}
                      	else{
                      		printf("close bracket expected in forcase stat\n");
                      		exit(1);
                      	}
                     }
                     else{
                      printf("close parenthesis expected after when stat\n");
                      exit(1);
                     }
               }
               else{
               		printf("close parenthesis expected after when in forcase stat\n");
               		exit(1);
               }

           }
       }
       else{
            printf("open bracket expected after forcase\n");
            exit(1);
       }

}




void call_stat(){

		if(token_id==variable){
            char func_name[30];//the name of the procedure or function that we call
            strcpy(func_name,lexis);
            token_id=lex();

                if(token_id==OPEN_PARENTH){

                      actualpars();
                      genquad("call",func_name,"_","_");
				  	  if(token_id != CLOSE_PARENTH){
				  	  	printf(" ')' was expected call_stat \n");
				  	  	exit(1);
				  	  }
				  	  else{
				  	  	token_id=lex();
				  	  }
                }
                else{
				printf("open parenthesis was expected after fuction calling\n");
				exit(1);
                }
		}
		else{
			printf("variable name of fuction was expected after call\n");
			exit(1);
		}

}

void actualpars(){

	if(token_id==OPEN_PARENTH){
		token_id=lex();

		actualparlist();
		if(token_id != CLOSE_PARENTH){
			printf(" ')' was expected  actualpars");
			exit(1);

		}

	}

}

void actualparlist(){
	actualparitem();
	while(token_id==COMMA){
		token_id=lex();
		actualparitem();

	}

}

void actualparitem(){

	if(token_id==in_id){
		token_id=lex();
		char in_parameter[30];
		strcpy(in_parameter,lexis);
		genquad("par",in_parameter,"CV","_");
		if(token_id != variable){
			printf("id was expected after in\n");
			exit(1);
		}
		else{

			token_id=lex();

		}
	}
	else if(token_id==inout_id){
		token_id=lex();
		char inout_parameter[30];
		strcpy(inout_parameter,lexis);
		genquad("par",inout_parameter,"REF","_");
		if(token_id != variable){
			printf("id was expected after inout\n");
			exit(1);
		}
		else{

			token_id=lex();

		}
	}
	else if(token_id==copy_id){
		token_id=lex();
		char copy_parameter[30];
		strcpy(copy_parameter,lexis);
		genquad("par",copy_parameter,"COPY","_");
		if(token_id != variable){
			printf("id was expected after copy \n");
			exit(1);
		}
		else{
			token_id=lex();
		}
	}
	/*else{
		printf("parameters where expected  after call stat\n");
		exit(1);
	}*/

}
/*
if "or" exists in condition then if true we jump inside the code of the condition else if false we jumo to next condition
   However in "and" if true we jump to next condition and if false we jump outside of condition,because to get inside the code
   of the conditions we want both conditions to be true,whereas in or we want one of them.
*/
void condition(label_node **B_true,label_node **B_false){//pointer to pointer is being used at parameters because i change the
    //value of pointer of pointer
    label_node *Q1_true;
    label_node *Q1_false;
    boolterm(&Q1_true,&Q1_false);
	//P1
    *B_true=Q1_true;
    *B_false=Q1_false;
    //end of p1

while(token_id==or_id){
		token_id=lex();
        //p2
		backpatch(*B_false,nextquad);
		//end of p2
		label_node *Q2_true;
        label_node *Q2_false;
		boolterm(&Q2_true,&Q2_false);
		//p3
		*B_true=merge(*B_true,Q2_true);
        *B_false=Q2_false;
        //end of p3
	}


}

void boolterm(label_node **Q_true,label_node **Q_false){
    label_node *R1_true;
    label_node *R1_false;
    boolfactor(&R1_true,&R1_false);
    //P1
    *Q_true=R1_true;
    *Q_false=R1_false;
    //end of p1
	while(token_id==and_id){
		token_id=lex();
		//p2
		backpatch(*Q_true,nextquad);
		//end of p2
		label_node *R2_true;
        label_node *R2_false;
		boolfactor(&R2_true,&R2_false);
		//p3
		*Q_false=merge(*Q_false,R2_false);
		*Q_true=R2_true;
		//end of p3
	}

}

void boolfactor(label_node **R_true,label_node **R_false){

    if(token_id==not_id){
		token_id=lex();
		if(token_id==OPEN_AGG){
			token_id=lex();
			label_node *b_true;
			label_node *b_false;
			condition(&b_true,&b_false);
			//rule->(Expression){p1}
			//p1
			*R_true=b_true;
			*R_false=b_false;
			//end of p1
			if(token_id != CLOSE_AGG){
				printf(" ']' was expected after condition of not\n");
				exit(1);
			}
			else{
				token_id=lex();
			}
		}
		else{
			printf(" '[' was expected after not\n");
				exit(1);
		}
	}
	else if(token_id==OPEN_AGG){
            token_id=lex();
            label_node *b_true;
			label_node *b_false;
			condition(&b_true,&b_false);
			//rule->(Expression){p1}
			//p1
			*R_true=b_true;
			*R_false=b_false;
			//end of p1
			if(token_id != CLOSE_AGG){
				printf(" ']' was expected\n");
				exit(1);
			}
			else{
				token_id=lex();
			}
	}
	else{

        char* E1_place=NULL;//used to store E_place
        E1_place=malloc(sizeof(30));
        expression(&E1_place);
        relational_oper();
        char* E2_place=NULL;
        E2_place=malloc(sizeof(30));
        expression(&E2_place);//used to store E_place
        *R_true=makelist(nextquad);
        genquad(relop,E1_place,E2_place,"_");//its the true jump
		*R_false=makelist(nextquad);
		genquad("jump","_","_","_");//false jump

    }

}

void expression(char **E_place){
    optional_sign();
	static char *T1_place;
	T1_place=malloc(sizeof(30));
	strcpy(T1_place,lexis);
	term(&T1_place);
    while(token_id==PLUS || token_id==MINUS){
			add_oper();
            static char *T2_place;
            T2_place=malloc(sizeof(30));
            strcpy(T2_place,lexis);
            term(&T2_place);
            char *w=new_temp();
            add_entity(w,5,0,0);//for adding temporary variables to current scope
            genquad(add_symbol,T1_place,T2_place,w);
            T1_place=w;

	}
	*E_place=malloc(sizeof(30));
	strcpy(*E_place,T1_place);
    strcpy(help,*E_place);//used for printing the values only,cause E_place cannot be accessed
}

void term(char **T_place){

    static char *F1_place;
    F1_place=malloc(sizeof(30));
    strcpy(F1_place,lexis);
    factor(&F1_place);
	while(token_id==MULTI || token_id==SLASH){
		mul_oper();
        static char *F2_place;
        F2_place=malloc(sizeof(30));
        strcpy(F2_place,lexis);
        factor(&F2_place);
		char *w=new_temp();
		add_entity(w,5,0,0);
		genquad(mul_symbol,F1_place,F2_place,w);
		F1_place=w;
	}
	*T_place=malloc(sizeof(30));
	strcpy(*T_place,F1_place);
}

void factor(char **F_place){
    if(token_id==OPEN_PARENTH){
        token_id=lex();
		expression(&E_place);
        if(token_id != CLOSE_PARENTH){
			printf(" ')' was expected\n");
			exit(1);

		}
		else{
            *F_place=malloc(sizeof(30));
            strcpy(*F_place,help);
            token_id=lex();
        }
	}
	else if(token_id==variable){
            char *id_place;
            id_place=malloc(sizeof(30));
            strcpy(id_place,lexis);
            strcpy(*F_place,id_place);
            token_id=lex();
            idtail(id_place);
            if(flag==1){
                strcpy(*F_place,help_idtail);
                flag=0;
            }
            return;

	}
	else if(token_id==CONSTANTS_ID){
        //int const_value=atoi(lexis);
	    //add_entity(assign_value,2,0,const_value);
		token_id=lex();

    }
    else{
        printf("expression was expected\n");
        exit(1);
	}

}

void idtail(char *id_place){

	if(token_id==OPEN_PARENTH){
        flag=1;
		actualpars();
		token_id=lex();
		char *w=new_temp();
		add_entity(w,5,0,0);
		genquad("par",w,"RET","_");
		genquad("call",id_place,"_","_");
        strcpy(help_idtail,w);

	}
}


void relational_oper(){
	if(token_id==EQ||token_id==LESSER ||token_id==GREATER||token_id==GREATER_EQ||token_id==LESSER_EQ||token_id==LESSER_GREATER){
         strcpy(relop,lexis);
         token_id=lex();
    }
	else{
		printf("relation operator was expected after condition\n");
		exit(1);
	}
}

void add_oper(){

	if(token_id==PLUS || token_id==MINUS){
        strcpy(add_symbol,lexis);
        token_id=lex();
	}
	else{
		printf("add or minus operator was expected after condition\n");
		exit(1);
	}
}

void mul_oper(){

	if(token_id==MULTI || token_id==SLASH){
        strcpy(mul_symbol,lexis);
		token_id=lex();
	}
	else{
		printf("multi or divide operator was expected after condition\n");
		exit(1);
	}

}


void optional_sign(){

	if(token_id==PLUS||token_id==MINUS){
        add_oper();
	}

}

