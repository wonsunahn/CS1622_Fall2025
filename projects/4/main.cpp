/** Code by @author Wonsun Ahn, Fall 2025
 *
 * The parser test driver file.
 */

// Declarations of LLVM global objects like TheContext, TheBuilder, TheModule
#include "llvm/LLVMGlobals.h"
#include <llvm/Support/raw_ostream.h>

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
#include "proj3.h"

/* input for yylex() */
extern FILE *yyin;
/* printTreeText file pointer */
extern FILE *treelst;
/* printTreeGraphviz file pointer */
extern FILE *treeimg;
/* Root of the syntax tree */
extern tree SyntaxTree;
/* Print syntax tree in text format */
void printTreeText(tree nd, int depth);
/* Print syntax tree in graphviz format */
void printTreeGraphviz(tree nd, std::string parentNodeId, std::string currentNodeId);
/* Make symbol table function */
void MkST(tree);
/* Code generation function */
void codegen();

void printUsage()
{
  printf("USAGE: codegen [OPTIONS] <source file path>\n");
  printf("Compiles MINI-JAVA source code to LLVM IR.\n\n");
  printf("  -h           this help screen.\n");
  printf("  -p <file>    output graphviz file for syntax tree.\n");
  printf("  -v           verbose output (displays symbol table and parse tree).\n");
  printf("  -l           prints line numbers for each symbol in symbol table.\n");
  printf("  -o <file>    output file where the LLVM IR will be stored.\n");
}

int main(int argc, char **argv)
{
  std::string outputFileName, inputFileName, graphVizFileName;
  bool verbose = false;
  bool printLineNo = false;
  int optionIndex = 0;
  int c;

  while ((c = getopt(argc, argv, "hp:vlo:0")) != -1)
  {
    switch (c)
    {
    case 'h':
      printUsage();
      return 0;
    case 'p':
      graphVizFileName = optarg;
      treeimg = fopen(graphVizFileName.c_str(), "w");
      if (treeimg == NULL)
      {
        fprintf(stderr, "Cannot open %s for writing.\n",
                graphVizFileName.c_str());
        exit(1);
      }
      break;
    case 'v':
      verbose = true;
      break;
    case 'l':
      printLineNo = true;
      break;
    case 'o':
      outputFileName = optarg;
      break;
    case '?':
      if (optopt == 'o')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
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
  if (inputFile == NULL)
  {
    fprintf(stderr, "Cannot open %s for reading.\n",
            inputFileName.c_str());
    exit(1);
  }

  /* make syntax tree */
  SyntaxTree = NULL;
  yyin = inputFile;
  yyparse();

  fclose(inputFile);

  if (SyntaxTree == NULL)
  {
    fprintf(stderr, "Syntax Tree not created, exiting...\n");
    exit(1);
  }

  /* Make symbol table */
  MkST(SyntaxTree);

  /* Generate the code */
  if (!outputFileName.empty())
  {
    TheModule = std::make_unique<llvm::Module>(outputFileName, TheContext);
    codegen();
    int fd = open(outputFileName.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (fd == -1)
    {
      fprintf(stderr, "Unable to open output file %s for writing.\n", outputFileName.c_str());
      exit(2);
    }
    llvm::raw_fd_ostream outputFile(fd, true, true);
    TheModule->print(outputFile, nullptr);
    outputFile.close();
  }

  /* If verbose, print out symbol table and parse tree. */
  if (verbose)
  {
    STPrint(stdout, printLineNo);
    treelst = stdout;
    printTreeText(SyntaxTree, 0);
  }

  /* Print out syntax tree to graphviz file if requested. */
  if (treeimg != NULL)
    printTreeGraphviz(SyntaxTree, "", "n");

  return 0;
}