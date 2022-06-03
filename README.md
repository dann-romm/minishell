# minishell

Simple implementation of Unix bash with pure C

# features

- built-in commands
    - echo with -n option
    - cd with absolute or relative path
    - pwd
    - export
    - unset
    - env
    - exit
- prompt depending on PS1 PS2 variables
- commands history
- redirects
- pipes
- evironment variables stored in the hashtable
- exit status $?
- signals
    - ctrl-C
    - ctrl-D
    - ctrl-\
- && and ||
- wilcard * matching

# Usage

there is a Makefile for compiling sources
to compile binary, you should run `make` command

```bash
$ make
$ ./minishell
```

## examples

1. pipes and child processes
```bash
minishell > ls -la | wc -l
      13
minishell > yes | head -n 3
y
y
y
```

2. redirects
```bash
minishell > < input.txt > output.txt cat
```

3. wildcards
```bash
minishell > ls hash**t*le* | cat
hash.c
hashtable.c
hashtable_to_sorted_array.c
insert_hashtable.c
pair.c
```

4. prompt
```bash
minishell > PS1="new_prompt > "
new_prompt > 
```

5. && and ||
```bash
minishell > echo -n "Hello, " && echo "world" || echo "!!!!!!!"
Hello, world
```
