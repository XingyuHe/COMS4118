NAME: Xingyu He
UNI:  xh2513

Part1: 
OSTEP Questions: 

What actions does a kernel perform to context switch between processes?

The interrupt handler is called and decides which process to perform next. If it 
does decide to switch to another process (let’s say from A to B), it explicitly 
saves the current register values of A to the process structure of A, restores the
registers from the process structure of B, and changing the stack pointer to use 
B’s kernel stack. Finally, it calls return-from-trap into process B. 


What process state does a process enter immediately after it terminates? What is
this state for, and when does it leave this state?

It goes into a zombie state. This state is where a process has exited but hasn’t 
been cleaned up. This allows other processes (e.g. parent process) to examine the
finished process for the completion status and other relevant statuses. By calling
wait(), the parent process can tell the OS to clean up any relevant data structures
that refer to the zombie process

LKD Questions: 

Questions
What is typeof? Is it C language keyword, function, or macro? What does it do?

It is a keyword. It can operate on an expression and acts semantically like a type
name output by the operator typedef on that expression. 


What is offsetof? Is it keyword, function, or macro? What does it do?

It is a macro that returns the byte offset between a member and the beginning of
the structure. 


What does the container_of() macro do?

It returns the pointer to the parent structure given a pointer to a member. It 
takes the member name in the structure, the type name of the structure, and a pointer
of the member. 


The container_of() macro, in the way it’s written in LKD, is not portable across 
C compilers because it uses GNU-specific language extensions. Can you identify what they are?

It statements expression, typeof extension, and offset extension. 


The container_of() macro in LKD has two lines. Is the 1st line (the declaration of __mptr)
really necessary? Is it possible to rewrite the macro without it? What is the purpose
of that 1st line?

It is not really necessary. We can just use ptr to replace __mptr in the second 
line. The purpose of the first line is to declare a pointer with the same value as ptr. 


Part2: 
The part is working. Some of the bugs I encountered are 
1. strcpy is needed to use to assign values of a character array to another character array
2. kfree is needed to avoid memory leak.

Part3:
This part is working. I added my own header file mylist.h to write my own list macros. 
All macros follow the same naming scheme my_[old macro name] and follow the same 
previous behaviors. 

Part4:
This part is working. A major bug that I encountered was using list_for_each_entry. 
The important point is that sibling is a headlist that leads to the peer nodes in the 
list where children is the head of the list. 


This file should contain:

  - Your name & UNI (or those of all group members for group assignments)
  - Homework assignment number
  - Description for each part

The description should indicate whether your solution for the part is working
or not. You may also want to include anything else you would like to
communicate to the grader, such as extra functionality you implemented or how
you tried to fix your non-working code.
