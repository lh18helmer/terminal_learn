#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *lowercase = "abcdefghijklmnopqrstuvwxyz";
static const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";





// chaning indvidual letter using offset given by user 
char change_letter(char char_to_encrypt, int offset) {
    int x;
    char encrypted_char;
    
    if (isupper(char_to_encrypt)) {
        x = char_to_encrypt - 'A';
        x = x + 26 * 80;
        encrypted_char = uppercase[(x + offset) % 26];
    } else {
        x = char_to_encrypt - 'a';
        x = x + 26 * 80;
        encrypted_char = lowercase[(x + offset) % 26];
    }
    return encrypted_char;
}

// encryption function
int encrypt(char *file_to_encrypt_name, int caesar_offset) {


    //opening the file the already exists to encrypt
    FILE *file_to_encrypt = fopen(file_to_encrypt_name, "r");
    // Error message not important
    if (file_to_encrypt == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_to_encrypt_name);
        return 1;
    }
    
    char *encrypt_filename = "encrypted_shit";

    
    FILE *encryption_file = fopen(encrypt_filename, "w");
    
     // Error message not important
    if (encryption_file == NULL) {
        fprintf(stderr, "Error opening file to write encrpytion to.");
        return 1;
    }    

    char read_buffer[1024];

    size_t bytes_read = fread(read_buffer, 1, 1024, file_to_encrypt);
    printf("Bytes read from the file %s: %zu\n", file_to_encrypt_name, bytes_read);
    
    char *write_buffer = malloc(bytes_read);
    for (int i = 0; i < bytes_read; i++) {
        char current_char = read_buffer[i];
        if (isalpha(current_char)) {
            char encrypted = change_letter(current_char, caesar_offset);
            write_buffer[i] = encrypted;
        } else {
            write_buffer[i] = current_char;
        }
    }

    fwrite(write_buffer, sizeof(char), bytes_read, encryption_file);
    free(write_buffer);
    
    fclose(file_to_encrypt);
    fclose(encryption_file);
    return 0;
}



int decrypt(char *file_to_decrypt_name, int caesar_offset) {
    //openning already existing file
    FILE *file_to_decrypt = fopen(file_to_decrypt_name, "r");
    
 // Error message not important
    if (file_to_decrypt == NULL) {
        fprintf(stderr, "Error opening file to decrypt.");
        return 1;
    }    
// opening the file that will hold decrypted shit
    char *decrypted_file_name = "decrypted_file";
    FILE *decrypted_file = fopen(decrypted_file_name, "w");
    if (decrypted_file == NULL) {
        fprintf(stderr, "Error opening file to write decryption to.");
        return 1;
    }   

    //stealing bullshit from file that needs to be decrypted 
    char read_buffer[1024];
    size_t bytes_read = fread(read_buffer, 1, 1024, file_to_decrypt);
    printf("Bytes read from the file %s: %zu\n", file_to_decrypt_name, bytes_read);
    
    //looping thorugh every letter and changing it according to the letter offset. and then putting it in the write buffer
    char *write_buffer = malloc(bytes_read + 5);
    for (int i = 0; i < bytes_read; i++) {
        char current_char = read_buffer[i];
        if (isalpha(current_char)) {
            char encrypted = change_letter(current_char, -caesar_offset);
            write_buffer[i] = encrypted;
        } else {
            write_buffer[i] = current_char;
        }
    }

    //finally writing the shit into the decrypted file 
    fwrite(write_buffer, 1, bytes_read, decrypted_file);
    free(write_buffer);
    fclose(file_to_decrypt);
    fclose(decrypted_file);

    return 0;
}

//main function



int main(int argc, char **argv)
{
    //checking if the moron spelled correctly
    if (argc < 4) {
        fprintf(stderr, "give more arguments dumb ass\n");
        return 1;
    }
    
    int caesar_offset = atoi(argv[2]);
    char *operation_type = argv[3];
    char *encrypt_str = "encrypt";
    char *decrypt_str = "decrypt";
    // checking to see if we should encrypt or decrypt using strings
    if (strcmp(operation_type, encrypt_str) == 0) {
        //encrypt
        char *file_to_encrypt_name = argv[1];
        encrypt(file_to_encrypt_name, caesar_offset);
        return 0;
    } 
    
    else if (strcmp(operation_type, decrypt_str) == 0)
    {
        //decrypt
        char *file_to_decrypt_name = argv[1];
        decrypt(file_to_decrypt_name, caesar_offset);
        return 0;
    }
    else {
        //if the retard didnt spell correctly 
        fprintf(stderr, "your a dumb ass, spell correctly");
    }


    
    return 0;
}






