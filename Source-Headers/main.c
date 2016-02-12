#include "syntax.h"

int main(){

         char filename[30];//keeps the input file name
         char output_filename[30];//keeps the output file name
         char end_output_filename[30];
         int i;

        for(i=1;i<=5;i++){

          nextquad=100;
          temp_num=1;
          sprintf(filename,"test%d.st",i);//define filename

        //file to read intercode
         fp=fopen(filename,"r");
                  if( fp == NULL ){//case file is empty
                        perror("\nError while opening the file for intercode.\n");
                        exit(EXIT_FAILURE);
                }
          sprintf(output_filename,"2299_test%d.int",i);

          sprintf(end_output_filename,"endcode_%d.s",i);

          //file to write
          fc=fopen(output_filename,"w");
                   if( fc == NULL ){//case file is empty
                        perror("\nError while opening the output file.\n");
                        exit(EXIT_FAILURE);
                    }
        //file for metasim
         fe=fopen(end_output_filename,"w");
                   if( fe == NULL ){//case file is empty
                        perror("\nError while opening the output file for endcode.\n");
                        exit(EXIT_FAILURE);
                    }


        token_id=lex();//read the first token from file,which is being used to the syntax analyzer
        program();//the first function of the syntax analyzer
        print_endcode();
        free_end_list();
        printf("\nsuccess\n,program %d has NO syntax errors\n\n",i);
        printf("========================================================================\n");
        printf("========================================================================\n");
        printf("\n\n");
        fclose(fp);
        fclose(fe);

      }


}




   /*fp=fopen("test_5.st","r");
    if( fp == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

     fc=fopen("2299_outputfile.int","w");
                   if( fp == NULL ){//case file is empty
                        perror("\nError while opening the output file.\n");
                        exit(EXIT_FAILURE);
                    }

        token_id=lex();
        program();
        //fprintf(fc,"The quad list is:\n\n");
        print_endcode();
        printf("\nsuccess\n,program has NO syntax errors\n\n");


   //erase here to use

}*/

