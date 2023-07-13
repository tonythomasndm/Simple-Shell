# SimpleShell

Linux (and other Unix like OSes), have “shells” or programs which present
a command line interface to users to type commands in. In this assignment
you need to use standard C libraries, including Linux system calls such as
fork(),exec() family system calls and wait() family of system calls.
There are two kinds of commands – “internal” and “external”. Internal

commands are those which are interpreted by the shell program itself, with-
out requiring a different program to handle the expected operations (of the
said command). Examples of internal commands are like ‘cd’, ‘pwd’, ‘exit’
etc. External commands on the other hand relate to commands which are not
handled directly by the shell program but by an external program. Common
examples include ‘ls’, ‘cat’, ‘grep’ etc.
In this assignment, you have two tasks:

1. You need to design a simple shell that can handle three, internal com-
mands – ‘cd’, ‘echo’ and ‘pwd’. These commands would be handled

directly by the shell. Your shell should also be able to handle five exter-
nal commands – ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’. For these

external commands you need to write individual programs to handle these
commands. To handle these external commands, the shell should typically

create a new process, using the fork() system ‘call and within each pro-
cess you need to use the execl() family system call to run the individual

program. The parent program must also wait for the child program to
terminate using the wait() family of system calls.
For each of these commands, you need not handle all the command line
options. Two options per command is sufficient. You need to document

which two options you are handling and need to demonstrate correct func-
tioning of the command with respect to (atleast) your chosen options. You

also need to handle corner cases such as invalid options (graceful degra-
dation).

2. The second task would be the achieve the above functionality of the shell
using pthread create() (instead of fork()) and system() (instead of
execl() family of functions). The thread based execution would be per-
formed if the command is followed by the characters, “&t”. The rest of

the functionalities should remain the same. Note: you only need one set
of external command programs which could be used with either versions
of the shell, be it the that uses fork()/execl() or the one that uses
pthread create()/system().
