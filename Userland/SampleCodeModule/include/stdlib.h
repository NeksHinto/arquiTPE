#ifndef STDLIB_H
    #define STDLIB_H


/***************************************************************
 * Function: strcmp
 * Use: int boolean_value = strcmp(str1,str2);
 * -------------------------------------------------------------
 * Description: Compares two strings and returns 0 if they are
 *                equal and =/= 0 if they are not.
 * -------------------------------------------------------------
 * Pre-Condition: Strings passed as arguments.
 * Post-Condition: Boolean value of the string
***************************************************************/
int strcmp( char * s1,  char* s2);

/***************************************************************
 * Function: itoa
 * Use: itoa(num,base,str);
 * -------------------------------------------------------------
 * Description: Passes an integer to ASCII to a given string. 
 *              Doesn't check if the string has enough lenght.
 * -------------------------------------------------------------
 * Pre-Condition: Number passed as argument, with it's base
 *                        and a char array.
 * Post-Condition: Char array now has the number given in ASCII.
***************************************************************/
void itoa(int value,int base, char * buffer);

/***************************************************************
 * Function: reverse
 * Use: reverse(str, strlen(s));
 * -------------------------------------------------------------
 * Description: Reverses the given string.
 * -------------------------------------------------------------
 * Pre-Condition: String passed as argument.
 * Post-Condition: String reversed.
***************************************************************/
void reverse(char *s, int size);

/***************************************************************
 * Function: strlen
 * Use: int lenght = strlen(str);
 * -------------------------------------------------------------
 * Description: Return the given string's lenght.
 * -------------------------------------------------------------
 * Pre-Condition: String passed as argument.
 * Post-Condition: String lenght.
***************************************************************/
int strlen(char* s);

/***************************************************************
 * Function: atoi
 * Use: integer num = atoi(str);
 * -------------------------------------------------------------
 * Description: Transforms a string ASCII value from character
 *              to integer if the value is a number. Doesn't 
 *                    check if the string has only digits.
 * -------------------------------------------------------------
 * Pre-Condition: String passed as argument.
 * Post-Condition: Integer with string's value.
***************************************************************/
int atoi(char* str);

/***************************************************************
 * Function: is_digit
 * Use: int boolean_value = is_digit( c );
 * -------------------------------------------------------------
 * Description: Returns if the ASCII passed as argument is a
 *                                digit.
 * -------------------------------------------------------------
 * Pre-Condition: Character passed as argument.
 * Post-Condition: Truth value of is_digit.
***************************************************************/
int isdigit(char c);
#endif
