#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "numberinformation.h"

double *data = NULL;            //Pointer to the data, initialized at NULL
int data_allocated = 0;         //Data allocated at start, will change later
int data_count = 0;             //Counter, to keep track of where we are in data
bool sorted = true;             //No data yet, so leaving sorted as true because technically sorted as of now

//Read doubles to memory

int readfile(const char *filename)  {
    FILE *f = fopen(filename, "r");
    if (f == NULL)  {
        fprintf(stderr, "Can't open %s\n", filename);
        return 1;                           //Fails to open file
    }
    double datum;
    int status;
    while ((status = fscanf(f, "%lf", &datum)) == 1)   {
        
            // This is to find out if there is enough space for datum
        
        if (data_count >= data_allocated) {
            
            //Not enough space, have to allocate more
            
            data_allocated = (data_allocated+1)*2;
            data = realloc(data, data_allocated * sizeof(data[0]));
            if (data == 0)   {
                fprintf(stderr, "reallocate to %d failed\n", data_allocated);
                return 2;                    //Fails to reallocate more space
            }
        }
        data[data_count++] = datum;          //Increment data_count and use as adress of data array, store value in datum
    }
    fclose(f);
    sorted = false;                          //Have the data now, but isn't sorted so change to false
    
    if (status == 0)    {
        fprintf(stderr, "Non-number found in %s\n", filename);
        return 1;                           //Fails because file is of bad type (not numbers, etc)
    }
    return 0;                               //Success 
}
int main()  {                               //This was just included so I could compile on x86
};

double total()  {                           //Initialize sum as a double at 0.0, for every data_count adrress take the value, add to sum and store back in sum
    double sum = 0.0;
    for (int i=0; i<data_count; i++)
        sum += data[i];
    return sum;
}

                                            // Compare two doubles for qsort
int compare_doubles(const void *va, const void *vb) {
    const double *a = va, *b = vb;
    if (*a < *b) return -1;
    if (*a > *b) return 1;
    return 0;
}

double value(int index) {
    if (!sorted)    {
        qsort(data, data_count, sizeof(data[0]), compare_doubles);
        sorted = true;
    }
    if (index < 0 || index >= data_count)
        return 0.0;
    else
        return data[index];
}
                                           // How much data was read?
int count() {
    return data_count;
}
                                           //This is called before anything happens, and is defined in the header file
void initialize()   {
}
                                           //done, free the memory now
void terminate()    {
    free(data);                            //gives up allocated memory
}
