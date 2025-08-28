# How to compile

You will need the flex tool set to compile this code.  If you don't have it, please run the below on the terminal:

```
sudo apt-get update
sudo apt-get install flex
```

Then you can simply do make:

```
make
```

Which should result in:

```
$ make
flex lex.l
cc -c lex.yy.c 
cc -o lexer lex.yy.o -ll
```

# How to run

You can stream in whatever input you want to get parsed into stdin, as follows:

```
echo "hello world" | ./lexer
```

Which should result in:

```
$ echo "hello world" | ./lexer
type=string, lexeme: hello, len=5
type=space, lexeme:  , len=1
type=string, lexeme: world, len=5

EOF
```