# EN Template

This is a C program *template* tailored for:

- GCC, GDB, MAKE, VALGRING and DOXYGEN
- VS CODE editor


## :warning: 

**You're not supposed to *clone* this repository directly!** The GitHub's Classroom assignment repository will be created automatically from this template. 

Check the *GitHub Classroom How-To* at: <https://github.com/estsetubal-atad/Docs/blob/master/GitClassroom.pdf>

## Contents

The folder `dataset` contains the CSV files with the available information to work with:

- `earthquakes.csv`
- `world_country_locations.csv`
- `world_country_statistics.csv`

This template contains the following modules:

- `ADT List` - Collection;
- `ADT Map` - Collection;
- `StringWrap` - a type *wrapper* for when storing strings inside collections; 
- `Input` - Various *user input* routines (see **Input Module** section at the end)


## Development

Firstly, you must:

1. Start by defining your data types in their own modules, i.e., `date`, `time`, `earthquake`, etc.

2. Start importing data! You'll need to read CSV files. Below is an example of a function that opens the `earthquake.csv` file and prints out the coordinates of non-earthquakes:

```cpp
void printNonEarthquakeCoordinates() {
    FILE* stream = fopen("dataset/earthquakes.csv", "r");
    
    // Check if file was open (i.e., if it exists)
    if(stream == NULL) {
        printf("File not found.\n");
        return;
    }
    
    char line[1024];

    // Read and discard the header line
    fgets(line, 1024, stream);
    
    // Process file contents, line by line
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 9, ";");
        
        float latitude = atof(tokens[3]);
        float longitude = atof(tokens[4]);
        
        if(strcmp("Earthquake", tokens[5]) != 0) {
            printf("Type: %s | Latitude = %.6f | Longitude = %.6f \n", tokens[5], latitude, longitude);

        }
        
        free(tokens);
        free(tmp);
    }
    fclose(stream);
}
```

## Compiling and executing

Edit the `makefile` to comply with your source files and then, e.g.:

```console
$> make
```

If you didn't change the name of the *executable* (by default, `prog`), then:

```console
$> ./prog
```

## Using valgrind

*Valgrind* is very useful to detect "memory leaks" if your program uses *dynamic memory allocation*. You must compile the program with *debug* symbols and then run the executable through `valgrind`:

```console
$> make debug
$> valgrind --leak-check=full ./prog 
```

Alternatively, you can use the *bash script* already included:

```console
$> make debug
$> bash mem_check.sh
```

**When the program exits** it will present you with memory leak information.

## Debugging

In the **Run** tab (left side) you should see a green play icon ▶️ at the top beside "gdb - Debug project". Click on it and the debug will start. Do not forget to set your *breakpoints*.

## Generating documentation

You'll need `doxygen` installed and follow the doxygen documentation format. A `Doxyfile` is already provided that is suited for the C language. Use:

```bash
$> doxygen Doxyfile
```

and you'll end up with a `html` folder containing the generated documentation.

## Input Module

This template project includes the `input` module. You should use it for *user input* as it provides a relatively robust mechanism to read mixed data and performs validation.

Below is a sample program which exemplifies the usage of this module:

```cpp
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int main() {

    /* simple data formats with validation examples */
    int value = 0;
    do {
        printf("Integer Value? ");
    } while(!readInteger(&value)); /* loops while invalid */
        
    printf("Integer Value = %d \n", value);

    double value2 = 0;
    do {
        printf("Double Value? ");
    } while(!readDouble(&value2)); /* loops while invalid */
        
    printf("Double Value = %lf \n", value2);

    /* Strings are consumed as-is */
    char text[100];
    printf("Text? ");
    readString(text, 100);
    printf("Text = %s \n", text);

    /* Example of the spliting function; use with CSV files later */
    char line[100] = "Bruno Silva;bruno.silva@estsetubal.ips.pt;;2020/21";

    char** tokens = splitString(line, 4, ";");
    for(int i=0; i<4; i++) {
        printf("Token[%d] = %s \n", i, tokens[i]);
    }

    free(tokens); 

    return EXIT_SUCCESS;
}
```

and an example *user interaction* session:

```console
Integer Value? 12d
Integer Value? - 3
Integer Value? -3
Integer Value = -3 
Double Value? 12.4.5
Double Value? -3.14159
Double Value = -3.141590 
Text? This some text and a number 7 
Text = This some text and a number 7 
Token[0] = Bruno Silva 
Token[1] = bruno.silva@estsetubal.ips.pt 
Token[2] =  
Token[3] = 2020/21
```
