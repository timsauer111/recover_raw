#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <filename>.raw\n");
        return 1;
    }
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Not able to open File.\n");
        return 1;
    }
    uint8_t *buffer = malloc(sizeof(uint8_t)*512);
    if (buffer == NULL)
    {
        printf("Unable to allocate Heap Storage.\n");
        return 1;
    }
    int blockcounter = 0;
    int filecounter = 0;

    while (fread(buffer, sizeof(uint8_t)*512, 1, raw))
    {
        blockcounter++;
        if (buffer[0] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            filecounter++;
            //write_file(blockcounter, filecounter);
        }
        if (filecounter > 0)
        {
            char *filename = malloc(sizeof(char)*8);
            if (filecounter > 99)
            {
                sprintf(filename, "%i.jpg", filecounter-1);
            }
            else if (filecounter > 9)
            {
                sprintf(filename, "0%i.jpg", filecounter-1);
            }
            else
            {
                sprintf(filename, "00%i.jpg", filecounter-1);
            }
            FILE *out = fopen(filename, "a");
            if (out == NULL)
            {
                return 1;
            }
            fwrite(buffer, sizeof(uint8_t)*512, 1, out);
            free(filename);
            fclose(out);
        }



    }

    free(buffer);
    fclose(raw);
    return 0;
}


