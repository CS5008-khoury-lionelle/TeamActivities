# Team Activity File Reading and Analyzing Assembly

This lab seeks to help you understand File I/O in c, along with seeing the basic assembly that is generated for programs before it goes into a binary form.

For this team activity, you will have multiple small programs to write. The goals for this team activity are as follows:
* Better understand command line program arguments
* Better understand reading files in c
* Better understand the assembly generated for a program, and the cost of various commands

## :star: Working in Teams :star:
When working in teams, remember do not let one person do all the work. Make sure to work together, and ask questions. It is also better if different people program, and you all take turns programming for various team assignments. 



## Program Arguments
Programs, especially command line programs, have arguments that are passed into them, and based on those arguments it changes how the program runs.  For example, 

* `ls -l` on the linux / macOS command line will list the files in the current directory in a long format. 
* `code my_file.c` will open the file my_file.c in Visual Studio Code.
* `gcc -g -Wall my_file.c -o my_file.out` will compile the file my_file.c into an executable called my_file.out

Everything after the program name, is an argument!  

In c programming, you will notice the main function as two optional arguments

```c
int main(int argc, char** argv){
    // code goes here
}
```

* argc - is the argument count. This is the number of arguments passed into the program. It is always at least 1
* argv - is an array of strings. Each string is an argument passed into the program. The first argument is always the program name.


👉🏽 **Your Task**  Write a program that prints out all of the arguments passed into it. Make it so at least one argument is passed into it. 

### Discussion
* What is the first argument passed into the program?
* Why would having program arguments be useful for programs?


## Reading a File
If you followed Mike Shaw's video, you will have a good idea of how to read a file. This follows a similar guideline. 

👉🏽 **Your Task**  Read the file passed in via program arguments, and print out its contents to the screen 

The standard c library stdlib provides a number of File access functions.  If you wanted to open a file using the first 
program argument, you could do it the following way

```c
FILE *input = fopen(argv[1],"r");
```

Now if you wanted to read a line of the file, you would use the following

```c
char buff[BUFF_SIZE];  // notice BUFF_SIZE is just a number declared at the top
int r;

r = fscanf(input, "%s", buff);
```

The above says read the line from input and store it into the buff. If you are at the end of the file, r will equal `EOF`.

As such, to loop through a file, we can use the following:

```c
char buff[BUFF_SIZE]; 
int r;


FILE *input = fopen(argv[1],"r");
char* line = malloc(BUFF_SIZE * sizeof(char));
while (fgets(line, BUFF_SIZE, input) != NULL) {
    // do the thing, line now has the line from input
    
}

free(line); // don't forget to free memory!
fclose(input); // don't forget to close a file!
```




## Generating Assembly Files (10 Minutes)

Both gcc and clang allow you to generate the assembly file for their code.  Looking at [simple.c], we see a program that
simply adds two numbers, and then ends. However, [simple.s] is the assembly built from this program. This was done using the following option.

> clang -S simple.c

👉🏽 **Your Task** Write a **simple** c program, and generate the assembly file.

To help you better understand, you should write a simple/small C program. After you have completed the program, run the compiler with the `-S` option, to see the assembly generated. 

### Discussion
* What are some of the assembly commands generated? 
* Was there more than you expected? 
* Can you find the functions you wrote easily?

## Writing Estimator

Go ahead and use [estimator.c] for your template. We will slowly work through building the estimator. 



👉🏽 **Your Task**  Go ahead and add reading the first program argument (if it exists to estimator)

#### Discussion
* Why would c need two values for program arguments? 

### Reading The File (15 minutes)
I

Using the outline above, add to your estimator.c to print out the contents of the file based on the file name passed into args. This is always a good task to accomplish before working on files. Can you simply dump the contents to the screen! 

### Now The Estimator (60 minutes)

You can read the file! That is half the battle. Now we are ready to define the estimator specifications. 

* Your program should output counts for ADD, SUB, MUL, DIV, MOV, LEA, PUSH, POP, RET, SHL, and SAR. 
* Your program should figure out the cycles for each command. You can use the following chart to match cycles on a per command basis (hint: these are already added as defines in your template)
  * ADD counts as 1 cycle
  * SUB counts as 1 cycle
  * MUL counts as 3 cycles
  * DIV counts as 24 cycles
  * MOV counts as 1 cycle
  * LEA counts as 3 cycles
  * PUSH counts as 1 cycle
  * POP counts as 1 cycle
  * RET counts as 1 cycle
  * SHL counts as 1 cycle
  * SAR counts as 1 cycle
  * For example, is MUL shows up twice, it will say MUL 2 and then later 6 cycles (2 * 3). Or as code:
    ```c
    total_mul_cycles = mul_counter * MUL_CYCLES
    ```
* For the sake of simplicity, your tools should treat all instructions of the same type as equivalent using the same cycle count for all of the different forms. For instance, ADD would include ADDQ, ADDB, ADDL, etc. and count them all as 1 cycle.
IMUL is equivalent to MUL, IDIV is equivalent to DIV.
* You may ignore other assembly instructions (i.e. incq, decq) that are not in the above list.
* We have implemented some of the code (as this is only a one hour lab), you should complete the missing functions. 

### Implementation Hints
* This will involve counters for each command (or an array, but keep it simple / easy at first!) 
* It will require a very large if/else statement. 
* Your `if/else if`  will also need to consider `or`, for example "MOV" or "mov" is valid for mov. 
* `strstr()` helps you find the 'needle in the haystack' of two strings. You will want to use this!
* First only make your estimator work with a single command (add for example), then work on other commands. 
* Loop through the file counting first. Then worry about printing at the end. 

As always remember to implement incrementally. 

#### Discussion
* What were some challenges?
* What do the cycles tell you about the difficulty of the process for the computer?
* Why does this/knowing assembly matter?
  * This right here is the hard one. It can be difficult to see the forest through the trees, so discuss some reasons that come to mind and share them with the class at the end. 
* If you have time, use the Godbolt tool (linked below) to try equivalent programs in various languages. 
  * How does python and c differ, even if it the code is "equivalent"?


## 📚 Resources

* [strstr() tutorial](https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm)
* [CString reference](https://cplusplus.com/reference/cstring/)
* [Compiler Explorer](https://godbolt.org/) - really neat tool to explore compiled code
* [Guide to Cycle Costs](https://www.agner.org/optimize/instruction_tables.pdf)


[simple.c]: simple.c
[simple.s]: simple.s
[estimator.c]: estimator.c