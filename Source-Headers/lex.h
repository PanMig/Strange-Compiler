//MIGKOTZIDIS PANAGIOTIS:2299

#include "define.h"


//global variables used for lexical analyzer
char lexis[30];
FILE *fp;//read file pointer
FILE *fc;//write file pointer
FILE *fe;//for endcode
int token_id=0;//holds the id of the token that was read,used for the syntax analyzer
char ch;//a char used for reading the file

//prototypes
int lex();
int get_token();


bool isOperator(char ch)//if it is operator return true else false
{
 if(ch=='+'||ch=='-'|| ch=='*' ||ch=='/'||ch=='('||ch==')' ||ch=='[' || ch==']' || ch==',' || ch==';'||ch=='='||ch=='{'||ch=='}'){
     return true;
 }
 else{
  return  false;
 }
}


bool isBanned(char ch)//checks if the character that was read is not used in strange programming language
{
 if(ch=='!'||ch=='@'|| ch=='#' ||ch=='$'||ch=='%'||ch=='^' ||ch=='&' || ch=='|' || ch=='~' || ch=='"'||ch=='.'|| ch=='?'){
     return true;
 }
 else{
  return  false;
 }
}

int fpeek(FILE *fp)//takes a pick at the next character of the file without storing it,used only for the comments session of the compiling
{
  int c = getc(fp);

  return c == EOF ? EOF : ungetc(c, fp);
}

int get_token(){//returns the id of the token

      if(strlen(lexis)==1 && isOperator(lexis[0])){//checks if it is an  operator

		if(strcmp(lexis,"+")==0)  return PLUS;
		else if(strcmp(lexis,"-")==0)  return MINUS;
		else if(strcmp(lexis,"*")==0)  return MULTI;
		else if(strcmp(lexis,"/")==0)  return SLASH;
		else if(strcmp(lexis,"=")==0)  return EQ;
		else if(strcmp(lexis,"(")==0)  return OPEN_PARENTH;
		else if(strcmp(lexis,")")==0)  return CLOSE_PARENTH;
		else if(strcmp(lexis,"[")==0)  return OPEN_AGG;
		else if(strcmp(lexis,"]")==0)  return CLOSE_AGG;
		else if(strcmp(lexis,",")==0)  return COMMA;
		else if(strcmp(lexis,";")==0)  return QUESTMARK;
		else if(strcmp(lexis,"{")==0)  return OPEN_BRACKET;
		else if(strcmp(lexis,"}")==0)  return CLOSE_BRACKET;
 }

 else if(isdigit(lexis[0])){//if it is digit
  		return CONSTANTS_ID;


 }


 else{//if it is a word

 if(strcmp(lexis,"EOF")==0) return eof;


        else if(strcmp(lexis,"and")==0){
        		return and_id;

        }

         else if(strcmp(lexis,"declare")==0){
        		return declare_id;
        }



        else if(strcmp(lexis,"do")==0){
               return do_id;
        }



        else if(strcmp(lexis,"else")==0){
            return else_id;

        }

	else  if(strcmp(lexis,"enddeclare")==0){
		return enddeclare_id;
	}

	 else if(strcmp(lexis,"exit")==0){
		return exit_id;

	 }

	 else  if(strcmp(lexis,"procedure")==0){
		return procedure_id;
	}

	 else if(strcmp(lexis,"function")==0){
		return function_id;
	}

	else if(strcmp(lexis,"print")==0){
		return print_id;
	}

	else if(strcmp(lexis,"incase")==0){
		return incase_id;
	}

	else if(strcmp(lexis,"if")==0){
		return if_id;
	}

	else if(strcmp(lexis,"in")==0){
		return in_id;
	}

	else  if(strcmp(lexis,"inout")==0){
		return inout_id;
	}

	else  if(strcmp(lexis,"not")==0){
		return not_id;
	}

	else  if(strcmp(lexis,"forcase")==0){

		return forcase_id;
	}

	else if(strcmp(lexis,"program")==0){

		return program_id;

	}

	else if(strcmp(lexis,"or")==0){
		return or_id;

	}

	else if(strcmp(lexis,"return")==0){
		return  return_id;
	}

	else if(strcmp(lexis,"while")==0){
		return while_id;

	}

	else if(strcmp(lexis,"copy")==0){
		return copy_id;
	}

	else if(strcmp(lexis,"when")==0){
		return when_id;
	}

	else if(strcmp(lexis,"call")==0){
		return call_id;
	}

	else{//checks if it is an unknown word
		return variable;

    }


 	}

 }


int lex(){//identifies the input reading it char by char and return the id of the words,operators,symbols etc that recognizes


    char nextch;//gives next char
    int state;
    state= state0 ;
    int i=0;
    memset(lexis,0,strlen(lexis)); //makes the string empty

    while(state!=OK && state!=error){

        ch=fgetc(fp);
        nextch=fpeek(fp);

        if(state==state0 && isspace(ch)){// if finds whitespace stays at current state
                state=state0;
        }



        //STATE 1
        else if (state==state0 && isalpha(ch)){

           state=state1;
           lexis[i]=ch;
            i+=1;

	  }

        else if (state==state1 && (isalpha(ch) || isdigit(ch))){

        	lexis[i]=ch;
        	i+=1;


         }
       else if(state==state1) {//lexeme


       	       state=OK;
       	       ungetc(ch,fp);
       	       get_token();




      }
        //STATE 2

        else if (state==state0 && isdigit(ch)){

        state=state2;
        lexis[i]=ch;
        	i+=1;
        }

        else if (state==state2 && isdigit(ch)){

        	lexis[i]=ch;
        	i+=1;

        }
        else if (state==state2){//we have found a constant

           state=OK;
            ungetc(ch,fp);
           get_token();


         }
        //STATE 3
        else if (state==state0 && ch=='<'){
        state=state3;
        lexis[i]=ch;
        i+=1;
        }
        else if (state==state3 && ch=='='){//We have found the symbol <=
            lexis[i]=ch;
            i+=1;
            state=OK;
            return LESSER_EQ;

        }
        else if (state==state3 && ch=='>')//The symbol <>
        {
            lexis[i]=ch;
            i+=1;
            state=OK;
            return LESSER_GREATER;

        }
        else if (state==state3)//The symbol <
        {
          state=OK;
          ungetc(ch,fp);
          return LESSER;


        }

        //STATE 4
       else if (state==state0 && ch=='>'){

              state=state4;
              lexis[i]=ch;
              i+=1;


       }
        else if (state==state4 && ch=='=')
        {
            lexis[i]=ch;
            i+=1;
        	return GREATER_EQ;
        	state=OK;

        }
        else if (state==state4){
            state=OK;
          ungetc(ch,fp);
          return GREATER;
        }
        //STATE 5
        else if (state==state0 && ch==':'){

        state=state5;
        lexis[i]=ch;
        i+=1;
        }



        else if (state==state5 && ch=='=')
        {
        	return DOT_EQ;
        	state=OK;

        }

        else if (state==state5){state=error; printf("invalid operator: error");}

        //STATE 6

        else if (state==state0 && ch=='/'){

        	state=state6;
        	lexis[i]=ch;
        	i+=1;


        }
       //STATE 7
         else if (state==state6 && ch=='*'){
         state=state7;
            strcpy(lexis," ");
            i=0;

         }
       else if(state==state6){
            state=OK;
            ungetc(ch,fp);
        	get_token();

       }

        if (state==state7 && (ch=='*' && nextch=='/' ) ){
            ch=fgetc(fp);
        	  state=state0;



        }

        else if(state==state7&& (ch!='*' && nextch!='/' )){

        state = state7;
        }

        else if (state==state0 && isOperator(ch))
        {

        	state=OK;
        	lexis[i]=ch;
        	i+=1;
        	get_token();
        }


        else if (state==state0 && ch==EOF){
        	return eof;
        	//state=OK;
        	exit(1);
        }



        else if(state==state0 && isBanned(ch)){

        	printf("banned char\n");
        	state=error;
        }
         else if(state==error){
                return error;
        }

       }


}
