# Contributing to The Engine Source Code
This file will help you avoid running into problems when trying to add new files to the engine source code

## Adding New functions or Classes
To add new functions or a new class to the engine, you need to:  
1. Write a header file.  
2. Write a source file.
3. Add your source file to the list of files to be compiled in tasks.json.  

## Writing a header file

A header file needs to have 2 things:

1. A header guard: This is to prevent the header from being included multiple times.  

2. Only forward declarations of the following:  
- functions.
- struct/class member variables and functions.

It is **very important** that you don't have any definitions/implementation in your header or ```#include``` any .cpp files. **Only forward declarations should be in a header**. 


### Writing a source file
Your source file need to ```#include``` the header that contains its forward declarations. Then you can define whatever functions or class/struct members you want to implement.

The header file effectively provides an interface, while the source file hides all the implementation details and private functions that aren't needed by outside code.
