# CS 1622 Midterm 2 Exam Study Guide - Fall 2025

The midterm is going to be **open book** but **individual work**.  Again, open
book means only materials in paper form will be allowed.  The only electronic
device you will be using will be your laptop and the laptop should only show
the GradeScope exam at all times.

The midterm will cover everything starting from semantic analysis till the end.

The exam may have these types of questions:
  * True / False questions
  * Multiple choice questions (including multiple answer)
  * Short answer questions (mostly asking what and why)
  * Questions that ask you to apply a concept to a code snippet or grammar (see learning goals in **bold** below)

## SEMANTIC ANALYSIS
* Be able to define the following terms: binding, scope, type checking, SDD, SDTS.
* Be able to tell the difference between static and dynamic scoping.
* Be able to compare the pros and cons of static and dynamic scoping.
* Be able to explain the role of the active symbol table stack`during semantic analysis.
* Be able to calculate the address of an element in a 2-dimensional array for row-major and column-major addressing.
* Be able to explain why in the C language, the type declaration "int A[][100]" is allowed for a function parameter A, but not for a local variable A.
* Be able to tell the difference between static type checking and dynamic type checking.
* Be able to compare the pros and cons of static type checking and dynamic type checking.
* **Be able to perform type inference on a piece of code given a set of type rules.**
* **Be able to point out when a type rule is unsound or unusable.**
* Be able to explain why static type checking can sometimes fail sound programs.
* Be able to tell whether an attribute is synthesized or inherited.
* Be able to discuss what needs to be true about attributes for an SDD to be implemented through a parse tree traversal.
* Be able to discuss what needs to be true about attributes for an SDD to be implemented through an SDTS using LL or LR parsing.
* Be able to explain what type of parser (LL or LR) allows semantic actions in the middle of the RHS and why.
* Be able to explain what kind of attribute (inherited or synthesized) is more challenging for an LL parser and why.
* Be able to explain what kind of attribute (inherited or synthesized) is more challenging for an LR parser and why.
* Be able to explain the role of markers in an SDTS for LR parsers in resolving attribute dependencies.
* Be able to explain the role of action records and synthesize records in an SDTS for LL parsers.

## CODE GENERATION
* Be able to explain how a common low-level IR can cut down compiler implementation effort.
* Be able to give examples of high-level IR, low-level IR, and machine IR.
* Be able to recognize which IR is most appropriate for a given optimization.
* Be able to explain what Static Single Assignment (SSA) IR is, and why it helps with compiler analyses and optimixations.
* Be able to explain what a phi function is in SSA and why it is needed.
* **Be able to lay out local variables in memory taking scopes into consideration, given a code snippet.**
* Be able to explain how static memory and heap memory allocations are handled with respect to the compiler.
* Be able to explain in what situations backpatching is required during code generation.
* **Be able to write semantic actions to generate code using backpatching for boolean expressions under short circuit semantics.**
* **Be able to write semantic actions to generate code using backpatching for if statements and while loops.**

## COMPILER OPTIMIZATION
* Be able to explain the following optimizations: strength reduction, dead code elimination, loop invariant code motion, and data prefetching.
* **Be able to identify whether an optimization is local/global and intra-procedural/inter-procedural, given a code snippet.**
* **Be able to identify leader instructions and basic blocks, given a code snippet.**
* **Be able to identify control flow edges, given a code snippet.**
* Be able to explain what it means for a compiler optimization to be conservative and why it is important.
* **Be able to compute the GCP dataflow value at a given point in the control flow graph, given a code snippet.**
* **Be able to point out which instructions can be optimized based on the GCP dataflow analysis.**
* **Be able to compute the Liveness dataflow value at a given point in the control flow graph, given a code snippet.**
* **Be able to point out which instructions can be eliminated based on the Liveness dataflow analysis.**
* Be able to tell the difference between the maximum fixedpoint solution and the meet-over-paths solution.
* Be able to tell the difference between the meet-over-paths solution and the ideal solution.
* Be able to explain why Liveness Analysis is a distributive framework, but GCP is not.
* **Be able to compute the Register Interference Graph (RIG) from a Liveness Analysis result.**
* Be able to explain how the RIG is used for register allocation.
