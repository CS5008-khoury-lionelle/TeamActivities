# Dynamic Programming

In this activity we will explore dynamic programming. It is a fancy term, often taught in overly mathematical ways to say:

> If we already calculated an answer, save it, so we don't have to calculate it again!

Really, that is the heart of it. The idea we are willing to spend more on memory, to save time on speed. While there are some complexities, 
the idea of [memoization] is at the heart of it. If a function is a [pure function], it is relatively easy store the result? 
Why because with pure functions, you have the following properties (source wikipedia):

1. the function return values are identical for identical arguments 
2. the function has no side effects 

In this lab, you will explore adding [memorization] to Pascal's Triangle and exploring the differences
in speed. This will help you practice for the midterm project. 


## Dynamic Programming Warm Up Discussion

As a team, **find three to four algorithms** that use dynamic programming. You do not need to implement them, or even fully understand them, but you should work together to understand how dynamic programming is being used to help with the algorithm. 

Now that you are thinking about what is dynamic programming, it is time to work together on a sample problem.


## Khayyam (مثلث خیام) / Yang Hui (杨辉三角; 楊輝三角) / Pingala / Pascal's Triangle

Known to the western world as Pascal's Triangle, this triangle of numbers has been known to many cultures often many years before Pascal. It is based on binomial coefficients, a topic covered in 5002. 

Here is a cool video for [Pascal's Triangle] (that hopefully you watched before this team activity): [Pascal's Triangle - Numberphile]

The idea behind Pascal's triangle is that starting 1 for spot 0,0 (first row, single element), each following row is sum of two numbers directly above it. All outer edges are always 1. 

![Triangle Animated]

Mathematically, this is represented as 


$$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$$

or a way to look at it code wise:
```c
unsigned long long pascalr(int n, int k) {
   if (n == k || k == 0)
      return 1;
   else
      return pascalr(n - 1, k) + pascalr(n - 1, k - 1);
}
```

You then have to loop through $n$ and $k$ calling your generator. 
```c
for (int i = 0; i < n; i++) {
   for (int j = 0; j <= i; j++) {              
      unsigned long long tmp = pascalr(i, j);
      printf("%llu ", tmp);
   }
   printf("\n");
}
```

However, while this algorithm is mathematically sound and easier to write, it is extremely inefficient.

There are solutions that are cheaper, and your next step is to add memoization to reduce the cost of this algorithm. 

## Updating Pascal.c
You will see [pascal.c](pascal.c) already has the above recursive version and an iterative version that
is more expensive on memory, but is faster. There is an even faster iterative version, but it struggles with
larger numbers due a multiplication and division calculation [ref](https://en.wikipedia.org/wiki/Binomial_coefficient#In_programming_languages). 

### Discussion and Code 
Take this time to compile the given code, and play with the code. For example if your compile
command[^1^] is:

[^1^]: Depending on if you compile on linux or windows, your warnings may change! This is a difference
in the definition of uint64. You can safely ignore the warning for this team activity, but worth
noting for future reference.



```text
gcc -Wall pascal.c -o pascal.exe
```

You could run the following to produce the following output:

```text
./pascal.exe 10 0 print
iterative version
1 10 45 120 210 252 210 120 45 10 1 
time: 0.000007(55)
```

or

```text
./pascal.exe 10 1 print
recursive version
1 10 45 120 210 252 210 120 45 10 1 
time: 0.000005(1013)
```

Both will run relatively quickly, but if you increase your number to ~35, you will see a noticeable increase in time to finish for the recursive version as compared to the iterative solution. You can also see the number of operations each algorithm is doing (roughly) by looking at the value in the parenthesis. As such, the iterative has 55 operations and the recursive has 1013 operations.

👉🏽 **Task**: Discuss the following together:
* What is the Big O for each version, and 
* What are observations about the code? 
  * For example, why use uint64 -what does that even mean!? 
  * Why use typedef? 
* You can also look up solutions online (there are a plenty of them) and discuss what you find.   



### Dynamic Programming
👉🏽 **Task**: Use [pascal.c](pascal.c) to write a dynamic programming variation of how to solve Pascal's Triangle for the Nth row.

Take a moment to discuss and describe dynamic programming in your own words to your team.  What are some things you are going to need to write a dynamic version of pascal's triangle. 

1. Make sure you declare a multidimensional array. As a static array using MAX as the size.
2. Then for each value of  `[n][k]` store that answer in the table, if it isn't already in the table.   
   Hint: since Pascal's triangle always has positive values 1 or higher, you can do the following for a check
   ```c
    if (table[n][k] > 0)  return table[n][k];
   ```

## Analysis

Writing "scripts" such as [test_runner.py](test_runner.py) is a very common practice. In this case, it is setup to help generate comparable data between the different types of implementations. Take a moment to explore the script, and generate some data. 

The following files were generated running the script with the following command:

```text
python test_runner.py 4000
```

* [timings_pascal_run.csv](timings_pascal_run.csv)
* [ops_pascal_run.csv](ops_pascal_run.csv)


### Script Review
Review the script and make sure everyone in the team activity fully understands what is going on! (Hint you may end up using something similar for your midterm project).

👉🏽 **Task**: Use either the provided CSV data, or data you generate to build a line graph comparing the various speeds (note you  may need to build separate line graphs for a better comparison). Discuss with your team. 


## Thinking Deeper
These are not the most efficient implementations! If you have time, study different ways you can improve the implementation of pascals triangle. 


## Technical Interview Practice
Take time practicing some of the past modules challenge problems. While you may not have time for everyone to do this, have a couple people practice "live coding". Live coding is a skill in interviews were you are asked to describe code **while** you are writing it. It can be a challenging skill, and it takes practice. I recommend that you setup a rotation of people to practice this skill within your team, ideally a couple every week. The other teams members can offer support, and then do a code review after a solution is generated. Then, as a group work a technical interview problem to discuss possible solutions.


## 📚 Resources
* [Geek for Geeks Pascal Triangle](https://www.geeksforgeeks.org/pascal-triangle/)
* [Dynamic Programming Examples (python)](https://www.makeuseof.com/dynamic-programming-tutorial/)
* [Memoization A "complete" tutorial](https://www.geeksforgeeks.org/what-is-memoization-a-complete-tutorial/)
* [Leet Code - Dynamic Programming](https://leetcode.com/tag/dynamic-programming/) -note: sort for easy ones first...
* [CSV to Markdown Converter](https://tableconvert.com/csv-to-markdown) - one of many online


[memoization]: https://en.wikipedia.org/wiki/Memoization
[pure function]: https://en.wikipedia.org/wiki/Pure_function
[Pascal's Triangle - Numberphile]: https://www.youtube.com/watch?v=0iMtlus-afo
[Pascal's Triangle]: https://en.wikipedia.org/wiki/Pascal%27s_triangle
[Triangle Animated]: https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif