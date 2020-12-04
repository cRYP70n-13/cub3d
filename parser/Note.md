# The Map parsing Notes

- [x] Check if the Map line starts with _1_ or _' '_
- [x] Calculate the Length of eache line and the hight of all the map using the counter
- [x] Check if the content Inside of the Map is one of those **_012NSEW_**
- [x] Check if the Map is valid else return and exit succesfully from the program
- [x] Allocate a 2D Array with the exact same width and height
- [x] Start Filling our Matrice with the content of the map in the config file

## Drawing the map

- [x] draw our map directly from the File
- [ ] Checking all the incomming errors !!
- [ ] Then we can start raycasting

## Some of the best practices in memory allocation in C (Allocate a 2D Array)

## <span style="color: red"> **_"Problem"_** </span>

- The normal way to allocate 10lignes and 3 columnes in C

```c
    int **arr = malloc(sizeof(int) * 10);
    for (int i = 0; i < 3; i++) {
        arr[i] = malloc(sizeof(int) * 3);
    }
```

## <span style="color: green"> **_"THE_SOLUTION"_** </span>

```c
    int **arr = malloc(sizeof(int) * 10 * 3);
```

___and make an array with the size of number of lines (height)___ </br>

```c
    int *array = malloc (sizeof(int) * 10);
```

___and points to every start of line of the first array___

```c
    for (int i = 0; i < 10; i++)
       array[i] = arr + 10 * i;
```
