# Simple_shell project 0x16. C - Simple Shell.

## Simple UNIX command interpreter.

### Description
This is a small and simple shell based on Unix command interpreter **sh** (/bin/sh) or **bash** (/bin/bash) 

### Usage
To compile this shell and use it as interactive mode use these commands below:
```
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
$ ./hsh
#simpleshell$ /bin/ls
/bin /etc /root /tmp /home /var /usr ...
#simpleshell$ ls -a
. .. /bin /etc /root /tmp /home /var /usr .hiddenFiles ...
#simpleshell$ somecmd
./hsh: 1: somecmd: not found
```
Or in non-interactive mode:
```
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
$ echo "/bin/ls" | ./hsh
$ /bin /etc /root /tmp /home /var /usr ...
$ echo "echo 'Simple shell'" | ./hsh
```

## Contributors & Authors
Wafae Chamour <[Chamour15](https://github.com/Chamour15)>
Mohammed Dakhamat <[dakhamohammed](https://github.com/dakhamohammed)>


