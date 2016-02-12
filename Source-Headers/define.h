#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>//used for isalpha and isdigit
#include <string.h>

//states
#define OK -2
#define error -1
#define state0 0
#define state1 1
#define state2 2
#define state3 3
#define state4 4
#define state5 5
#define state6 6
#define state7 7
#define state8 8
#define state9 9


//sensitive words

#define and_id 1
#define declare_id 2
#define do_id 3
#define else_id 4
#define enddeclare_id 5
#define exit_id 6
#define procedure_id 7
#define function_id 8
#define print_id 9
#define incase_id 10
#define if_id 11
#define in_id 12
#define inout_id 13
#define not_id 14
#define forcase_id 15
#define program_id 16
#define or_id 17
#define return_id 18
#define while_id 19
#define copy_id 20
#define when_id 21
#define call_id 22



//constants
#define CONSTANTS_ID 23

//operators

#define PLUS 24
#define MINUS 25
#define MULTI 26
#define SLASH 27
#define LESSER 28
#define GREATER 29
#define LESSER_EQ 30
#define GREATER_EQ 31
#define EQ 32

//symbols

#define QUESTMARK 33
#define COMMA 34
#define OPEN_BRACKET 35
#define CLOSE_BRACKET 36
#define OPEN_AGG 37
#define CLOSE_AGG 38
#define OPEN_PARENTH 39
#define CLOSE_PARENTH 40
#define LESSER_GREATER 41
#define DOTS 42
#define DOT_EQ 43

//comments symbols

#define OPEN_COMM 44
#define CLOSE_COMM 45

//variable
#define variable 46

//EOF
#define eof 47
