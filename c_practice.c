#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static const char *lowercase = "abcdefghijklmnopqrstuvwxyz";
static const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char encrypt(char char_to_encrypt, int offset) {
    int x;
    char encrypted_char;
    if (isupper(char_to_encrypt)) {
        x = char_to_encrypt - 'A';
        encrypted_char = uppercase[(x + offset) % 26];
    } else {
        x = char_to_encrypt - 'a';
        encrypted_char = lowercase[(x + offset) % 26];
    }
    return encrypted_char;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./caesar filename offset.\n");
        return 1;
    }

    // 0x0 (start) c
    // 0x1         a
    // 0x2         e
    // 0x3         s
    // 0x4         a
    // 0x5         r
    // 0x6         \0
    const char *program_name = argv[0];
    

    // 0x7         s
    // 0x8         e
    // 0x9         n
    // 0xa         t
    // 0xb         e
    // 0xc         n
    // 0xa         c
    // 0xb         e
    // 0xc         .
    // 0xd         t
    // 0xe         x
    // 0xf         t
    // 0x10        \0
    const char *file_to_encrypt_name = argv[1];

    // 0x11        3
    // 0x12        \0
    int caesar_offset = atoi(argv[2]);
    
    FILE *file_to_encrypt = fopen(file_to_encrypt_name, "r");
    
    // Error message not important
    if (file_to_encrypt == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_to_encrypt_name);
        return 1;
    }
    //
    
    const char *encrypt_filename = "encrypted.txt";
    FILE *encryption_file = fopen(encrypt_filename, "w");
    
     // Error message not important
    if (encryption_file == NULL) {
        fprintf(stderr, "Error opening file to write encrpytion to.");
        return 1;
    }    
    //
    
    char read_buffer[1024];

    size_t bytes_read = fread(read_buffer, sizeof(char), 1024, file_to_encrypt);
    printf("Bytes read from %s: %zu\n", file_to_encrypt_name, bytes_read);
    
    char *write_buffer = malloc(bytes_read * sizeof(char));
    for (int i = 0; i < bytes_read; i++) {
        char current_char = read_buffer[i];
        if (isalpha(current_char)) {
            char encrypted = encrypt(current_char, caesar_offset);
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
