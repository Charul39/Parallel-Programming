// CUDA -First Programs: “Hello, world” is traditionally the first program we write. We can do the same for CUDA. Here it is:

// In file hello.cu:

#include "stdio.h"
int main()
{
 printf("Hello, world\n");
 return 0;
}

// On your host machine, you can compile and this with: 

// $ nvcc hello.cu

// Execution on GPU equipped server
// $ ./a.out


// Discussion: 
// You can change the output file name with the –o flag: nvcc –o hello hello.cu
// If you edit your .bashrc file you can also add your current directory to your path if you don’t want to have to type the preceding . all of the time, which refers to the current working directory. 
// Add export PATH=$PATH:.
// To the .bashrc file. Some would recommend not doing this for security purposes.

// The point is that CUDA C programs can do everything a regular C program can do.




// Flow of Program: Open text editor (like vi/vim) open a new file - call it whatever you'd like.  It should do the following:
// •	Use the appropriate .cu include file
// •	compile and this with: $ nvcc hello.cu
// •	Print a hello message that includes its task rank and processor name Execution on       
// •	GPU equipped server$ ./a.out
// •	Terminate the Connection  environment
