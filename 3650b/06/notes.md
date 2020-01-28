
# CS3650: Lecture 6

System Calls

 - OS blocks access to shared resources
 - Provides interface (System calls) to access them safely.

File Descriptor Table

 - This is an array in kernel memory that tracks open files.

Default open files:

 - 0: Standard Input
 - 1: Standard Output
 - 2: Standard Error
 - so 3 is the first file opened by the user



