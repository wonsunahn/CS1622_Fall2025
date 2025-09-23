/** Code by @author Wonsun Ahn, Fall 2024
 *
 * The parser test driver file.
 */

// stdlib headers
#include <string>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

extern "C"
{
#include "proj2.h"
#include "y.tab.h"
}

/* input for yylex() */
extern FILE *yyin;
/* printtree output direction */
extern FILE *treelst;
/* Root of the syntax tree */
extern tree SyntaxTree;
/* Make symbol table function */
void MkST(tree);

void printUsage()
{
  printf("USAGE: parser [OPTIONS] <source file path>\n");
  printf("Builds syntax tree and symbol table out of MINI-JAVA source code.\n\n");
  printf("  -h           this help screen.\n");
}

int main(int argc, char **argv)
{
  std::string outputFileName, inputFileName;
  bool verbose = false;
  bool printLineNo = false;
  char c;

  while ((c = getopt(argc, argv, "hl0")) != -1)
  {
    switch (c)
    {
    case 'h':
      printUsage();
      return 0;
    case '?':
      if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      printUsage();
      return 0;
    default:
      abort();
    }
  }
  if (optind != argc - 1)
  {
    printUsage();
    return 0;
  }
  inputFileName = argv[optind];
  FILE *inputFile = fopen(inputFileName.c_str(), "r");

  /* Make syntax tree */
  SyntaxTree = NULL;
  yyin = inputFile;
  yyparse();

  fclose(inputFile);

  if (SyntaxTree == NULL)
  {
    fprintf(stderr, "Syntax Tree not created, exiting...\n");
    exit(1);
  }

  /* Print out syntax tree. */
  treelst = stdout;
  printtree(SyntaxTree, 0);

  return 0;
}