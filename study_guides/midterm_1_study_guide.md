# CS 1622 Midterm 1 Exam Study Guide - Fall 2025

The midterm is going to be **open book** but **individual work**.  

The midterm will cover everything up to and including LR parsers (but excluding
YACC parsers chapter.)  Please review all the homework questions as well as the
lecture slides.  Also, JFLAP is your friend.  You will not be allowed to use
JFLAP during the exam as you are expected to have learned all the concepts
demonstrated by it, but it is a great practice tool.

The exam may have these types of questions:
  * True / False questions
  * Multiple choice questions (including multiple answer)
  * Short answer questions (mostly asking what and why)
  * Fill-in-the-table questions (for the various tables we learned)
  * Regular expression and NFA/DFA related questions (both analysis and writing)
  * Grammar and derivation related questions (both analysis and writing)

## INTRODUCTION
* Be able to define what interpreters are.
* Be able to define what compilers are.
* Be able to recognize the pros/cons of interpreters, AOT compilers, and JIT compilers

## LEXICAL ANALYSIS
* Be able to define what a language is.
* Be able to define what a regular language is.
* Be able to construct simple regular expressions given a language specification.
* Be able to describe the relationship between the set of languages RL (Regular Languages), L(RE), L(NFA), and L(DFA).
* Be able to recognize whether a string is a member of a language expressed using a regular expressions, an NFA, or a DFA.
* Be able to recognize whether a state machine is an NFA or DFA.
* Be able to describe the process that allows auto-generation of a lexer from a regular expression (RE -> NFA -> DFA -> minimization -> table-driven code).
* Be able to convert a regular expression to an NFA using the McNaughton-Yamada-Thompson Algorithm.
* Be able to convert an NFA to a DFA taking into consideration epsilon closures.
* Be able to minimize a DFA and explain when state merging is allowed.
* Be able to convert an NFA or DFA to tabular format that can be access by table-driven code.
* Be able to discuss the time and space complexity of NFA vs. DFA lexical analysis.

## SYNTAX ANALYSIS
* Be able to name what Type 0, Type 1, Type 2, or Type 3 grammars are in the Chomsky Hierarchy.
* Be able to categorize a grammar into a Type 0, Type 1, Type 2, or Type 3 grammar.
* Be able to describe the relationship between the languages expressed by Type 0, Type 1, Type 2, and Type 3 grammars.
* Be able to explain why programming languages like Java are not context free.
* Be able to perform a leftmost or rightmost derivation of a string given a grammar.
* Be able to explain what an ambiguity in a grammar means in terms of parse trees and derivations.
* Be able to demonstrate ambiguity by showing multiple leftmost or rightmost derivations of a string.
* Be able to remove ambiguity in a grammar by enforcing precedence and associativity in the grammar rules.
* Be able to differentiate between a parse tree and an abtract syntax tree.
* Be able to explain why top-down parsers do a leftmost derivation and bottom-up parsers do a rightmost derivation.

## SYNTAX ANALYSIS - TOP DOWN PARSERS
* Be able to discuss the pros/cons of backtracking and predictive parsers.
* Be able to explain the difference between recursive descent and table-driven parsers.
* Be able to explain what happens when a token cannot be matched in a backtracking parser.
* Be able to explain why recursive descent parsers have a problem with left-recursion.
* Be able to remove left-recursion given a grammar.
* Be able to explain what each component of LL(k) means (the first L, second L, and the k).
* Be able to explain when terminal "matching" and non-terminal "expansion" are performed in the LL parse process.
* Be able to perform left-factoring to change a non-LL(1) grammar to an LL(1) grammar.
* Be able to tell whether a grammar is an LL(1) grammar.
* Be able to point out the conflict if a grammar is not an LL(1) grammar.
* Be able to calculate the First sets of RHSs to explain conflicts in an LL(1) parse table.
* Be able to calculate the Follow sets of non-terminals to explain conflicts in an LL(1) parse table.
* Be able to explain why LL parsers have a problem with left-recursion.
* Be able to discuss LL(1) and LL(k) time and space complexity.
* Be able to explain how ANTLR is able to LL(k) grammars while minimizing parse table size.

## SYNTAX ANALYSIS - BOTTOM-UP PARSERS
* Be able to explain what each component of LR(k) means (the L, the R, and the k).
* Be able to explain when terminal "shifting" and non-terminal "reduction" are performed in the LR parse process.
* Be able to explain when a RHS found at the top of the LR parse stack is not a handle.
* Be able to do a reverse of a rightmost derivation indicating the top of the LR parse stack using a #.  
(id1#+id2\*id3 ⇒ E#+id2\*id3 ⇒ E+#id2\*id3 ⇒ E+id2#\*id3 ⇒ E+E#\*id3 ⇒ E+E\*#id3 ⇒ E+E\*id3# ⇒ E+E\*E# ⇒ E+E# ⇒ E)
* Be able to discuss the pros/cons of LR in comparison with LL parsers.
* Be able to write the LR(0) items in a given state of an SLR parser DFA, given a grammar.
* Be able to tell whether a grammar is an SLR(1) or SLR(k) grammar.
* Be able to point out the shift-reduce or reduce-reduce conflict using LR(0) items in a non-SLR(1) grammar, taking into consideration Follow sets.
* Be able to point out the shift-reduce or reduce-reduce conflict using LR(0) items in a non-SLR(k) grammar, taking into consideration Follow sets.
* Be able to discuss the pros/cons of SLR vs. LALR vs. LR parsers.
* Be able to convert the LR(0) items in an SLR parser to LR(1) items in an LR parser, potentially splitting the state.
* Be able to tell whether a grammar is an LR(1) grammar.
* Be able to point out the shift-reduce or reduce-reduce conflict using LR(1) items in a non-LR(1) grammar, taking into consideration lookahead components.
* Be able to convert the LR(1) items in an LR parser to LR(1) items in an LALR parser, potentially merging states.
* Be able to tell whether a grammar is an LALR(1) grammar.
* Be able to point out the shift-reduce or reduce-reduce conflict using LR(1) items in a non-LALR(1) grammar, taking into consideration lookahead components.
* Be able to discuss the effects of converting an LR parser to an LALR parser by merging states, in terms of conflicts and error reporting. 

## SYNTAX ANALYSIS - WRAP UP
* Be able to describe the relationship between LL(1), SLR(1), LALR(1), LR(1), LL(k), SLR(k), LALR(k), LR(k).
(Also, be able to come up with grammars that demonstrate the above relationships.)
* Be able to describe how GLR and GLL are able to parse all Context Free Grammars.
