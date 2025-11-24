/** Code by @author Wonsun Ahn, Fall 2025
 *
 * The code generation implementation file.
 */

// stdlib headers
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Declarations of LLVM global objects like TheContext, TheBuilder, TheModule
#include "llvm/LLVMGlobals.h"

extern "C"
{
#include "proj2.h"
}
#include "proj3.h"

extern char *getString(int index);

// TODO: Add more helper functions as needed

static tree getTypeNode(int i)
{
  return (tree)GetAttr(i, TYPE_ATTR);
}

static tree getInitNode(int i)
{
  return IsAttr(i, INIT_ATTR) ? (tree)GetAttr(i, INIT_ATTR) : nullptr;
}

static llvm::Value *getObject(int i)
{
  return IsAttr(i, OBJECT_ATTR) ? (llvm::Value *)GetAttr(i, OBJECT_ATTR) : nullptr;
}

static bool isPredefined(int i)
{
  return IsAttr(i, PREDE_ATTR) ? GetAttr(i, PREDE_ATTR) : false;
}

static llvm::Type *getLLVMType(tree typenode, std::vector<int> *dimensions)
{
  llvm::Type *type = nullptr;
  if (NodeKind(LeftChild(typenode)) == INTEGERTNode)
    type = llvm::Type::getInt32Ty(TheContext);
  assert(type != nullptr);
  return type;
}

static llvm::Value *emitFunctionCall(tree t)
{
  // TODO: Modify to handle function calls in a generic way

  // Drill down to the STNode for the function being called
  tree selectOp = t->LeftC->RightC;
  assert(selectOp->NodeOpType == SelectOp);
  tree fieldOp = selectOp->LeftC;
  assert(fieldOp->NodeOpType == FieldOp);
  tree stNode = fieldOp->LeftC;
  assert(NodeKind(stNode) == STNode);
  // Index of symbol table entry for the function being called
  int idx = stNode->IntVal;

  if (isPredefined(idx))
  {
    if (strcmp(getString(GetAttr(idx, NAME_ATTR)), "println") == 0)
    {
      std::vector<llvm::Value *> callParams;
      llvm::Value *str = TheBuilder.CreateGlobalStringPtr("Hello World !!!", "string.const");
      callParams.push_back(str);
      TheBuilder.CreateCall((llvm::Function *)getObject(idx), callParams, "");

      static llvm::Value *newline = nullptr;
      if (newline == nullptr)
      {
        // To prevent redeclarations of the newline string.
        newline = TheBuilder.CreateGlobalStringPtr("\n", "printf.newline");
      }
      callParams.clear();
      callParams.push_back(newline);
      return TheBuilder.CreateCall((llvm::Function *)getObject(idx), callParams, "");
    }
  }

  assert(0);
  return nullptr;
}

static void emitCode(tree t)
{
  // TODO: Emit code for the tree node t

  assert(t != nullptr);

  switch (t->NodeKind)
  {
  case EXPRNode:
    switch (t->NodeOpType)
    {
    case RoutineCallOp:
      emitFunctionCall(t);
      break;
    case ReturnOp:
      if (!IsNull(LeftChild(t)))
        TheBuilder.CreateRet(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0)));
      else
        TheBuilder.CreateRet(nullptr);
      break;
    default:
      // Recursively emit code for children
      emitCode(t->LeftC);
      emitCode(t->RightC);
      break;
    }
    break;
  default:
    break;
  }
}

static llvm::Function *emitFunction(int idx)
{
  // TODO: Modify to handle function definitions in a generic way

  llvm::Function *func = nullptr;
  if (isPredefined(idx))
  {
    if (strcmp(getString(GetAttr(idx, NAME_ATTR)), "println") == 0)
    {
      llvm::FunctionType *funcPrintfType = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), true);
      func = llvm::Function::Create(funcPrintfType, llvm::Function::ExternalLinkage, "printf", TheModule.get());
      func->setCallingConv(llvm::CallingConv::C);

      // This is a predefined function, so no need to emit body.
    }
  }
  else
  {
    llvm::Type *retType = getLLVMType(getTypeNode(idx), nullptr);
    std::vector<llvm::Type *> params;
    llvm::FunctionType *funcType = llvm::FunctionType::get(retType, params, false);
    func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, getString(GetAttr(idx, NAME_ATTR)), TheModule.get());

    // Create a basic block to start populating the function body.
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(TheContext, "entry", func);
    TheBuilder.SetInsertPoint(bb);

    // Emit function body
    emitCode(getInitNode(idx));
  }
  assert(func != nullptr);
  return func;
}

static void emitSymbol(int idx)
{
  // TODO: Emit symbol in index idx in symbol table, other than functions

  switch ((int)GetAttr(idx, KIND_ATTR))
  {
  case FUNC:
  {
    // Emit function and initialize symbol table entry with the function object
    llvm::Function *func = emitFunction(idx);
    SetAttr(idx, OBJECT_ATTR, (uintptr_t)func);
    break;
  }
  default:
    break;
  }
}

void codegen()
{
  for (int i = 1; i < GetSymbolTableSize(); i++)
  {
    emitSymbol(i);
  }
}
