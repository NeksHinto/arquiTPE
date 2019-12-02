#include <stdlib.h>

int strcmp(char * s1, char* s2) {
	int i;
	for(i = 0; s1[i] != 0 || s2[i] != 0; i++){
		if(s1[i] != s2[i])
			return 0;
	}
	return 1;
}

int strlen(char* s) {
    int i;
    for(i=0; s[i] != '\0'; i++);
    return i;|
}


void itoa(int num, int base, char* str) {
    int i = 0; 
    int isNegative = 0; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = 1; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i);  
}

void reverse(char* s, int size) {
    char aux;
    for( int i=0; i< size/2; i++) {
        aux = s[i];
        s[i] = s[size - i -1];
        s[size -i -1] = aux;
    }
}

int atoi(char *str) { 
    int res = 0; // Initialize result 

    // Iterate through all characters of input string and 
    // update result 
    for (int i = 0; str[i] != '\0'; ++i) 
        res = res*10 + str[i] - '0'; 
   
    // return result. 
    return res; 
} 

int isdigit(char c) {
    return c >= '0' && c <= '9';
}
