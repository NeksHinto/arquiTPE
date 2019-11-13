#ifndef STD_BUFFERS_H
#define STD_BUFFERS_H
    #include <stdint.h>
    #define STD_IN 0
    #define STD_OUT 1
    #define STD_ERR 2
    #define BUFFER_SIZE 1024
    #define STANDARD_BUFFERS_AMOUNT 3

    /***************************************************************
     * Buffer: Buffer struct to save information regarding the
     *                             buffer.
    ***************************************************************/
    typedef struct Buffer {
        char buffer[BUFFER_SIZE];
        int start;
        int size;
    }  Buffer;

    /***************************************************************
    * Function: set_up_buffers
    * Use: set_up_buffers();
    * -------------------------------------------------------------
    * Description: Initializes stdin, stdout and stderr buffers
    *                             to be used.
    * -------------------------------------------------------------
    * Pre-Condition: -
    * Post-Condition: Buffers operational.
    ***************************************************************/
    void set_up_buffers();

    /***************************************************************
    * Function: clear_buffer
    * Use: clear_buffer( buffer_index )
    * -------------------------------------------------------------
    * Description: Resets the indexed buffer to its original
    *                             state.
    * -------------------------------------------------------------
    * Pre-Condition: -
    * Post-Condition: Indexed buffer clean.
    ***************************************************************/
    void clear_buffer(int buffer_index);

    /***************************************************************
    * Function:write_char_in_buffer
    * Use: int fails = write_char_in_buffer(index, c );
    * -------------------------------------------------------------
    * Description: If the buffer index is valid, the given 
    *                      char is printed in it.
    * -------------------------------------------------------------
    * Pre-Condition: Buffer given is at an initial state.
    * Post-Condition: Buffers given now has the char printed
    *                               in it.
    ***************************************************************/
    int write_char_in_buffer(int buffer_index, char c);

    /***************************************************************
    * Function: write_string_in_buffer
    * Use: int fails = write_string_in_buffer(index, str);
    * -------------------------------------------------------------
    * Description: If the buffer index is valid, the given
    *                     string is printed in it.
    * -------------------------------------------------------------
    * Pre-Condition: Buffer given is at an initial state.
    * Post-Condition: Buffer given now has the str printed
    *                              in it.
    ***************************************************************/
    int write_string_in_buffer(int buffer_index, char* str);

    /***************************************************************
    * Function: write_int_in_buffer
    * Use: int fails = write_int_in_buffer(index,number);
    * -------------------------------------------------------------
    * Description: If the buffer index is valid, the given
    *                    number is printed in it.
    * -------------------------------------------------------------
    * Pre-Condition: Buffer given is at an initial state.
    * Post-Condition: Buffer given now has the number printed
    *                              in it.
    ***************************************************************/
    int write_int_in_buffer(int index, uint64_t value,int base);

    //Reads a character and removes it from the buffer.
    /***************************************************************
    * Function: read_char_from_buffer
    * Use: char read_char = read_char_from_buffer(index);
    * -------------------------------------------------------------
    * Description: Reads a char from the given buffer.
    * -------------------------------------------------------------
    * Pre-Condition: -
    * Post-Condition: read_char now has the last char from
    *                        the given buffer.
    ***************************************************************/
    char read_char_from_buffer(int index);

    /***************************************************************
    * Function: read_string_from_buffer
    * Use: int fails = read_string_from_buffer(index, str, strlen)
    * -------------------------------------------------------------
    * Description: Stores the first strlen chars from the buffer
    *                         in the given string.
    * -------------------------------------------------------------
    * Pre-Condition: -
    * Post-Condition: str now has buffer information loaded.
    ***************************************************************/
    int read_string_from_buffer(int index, char * str,int size);

#endif
