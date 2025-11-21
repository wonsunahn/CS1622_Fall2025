CXXSOURCES = $(shell find . -not -path './examples/*' -and -not -path './project_3_solution/*' -and -not -path './table.cpp' -and -not -path './proj3.cpp' -and -not -path './semantic.cpp' -name '*.cpp')
CSOURCES = $(shell find . -not -path './y.tab.c' -and -not -path './lex.yy.c' -name '*.c')
#CSOURCES += y.tab.c
HEADERS = $(shell find . -not -path './y.tab.h' -name '*.h')
HEADERS += y.tab.h
OBJ += $(CXXSOURCES:%.cpp=%.o)
OBJ += $(CSOURCES:%.c=%.o)


TESTS = $(wildcard tests/*.mjava)
OUTPUTS := $(foreach test,$(TESTS),outputs/$(test:tests/%.mjava=%).out)
OUTPUT_DIFFS := $(foreach test,$(TESTS),output_diffs/$(test:tests/%.mjava=%).diff)
LOGS := $(foreach test,$(TESTS),logs/$(test:tests/%.mjava=%).log)
LOG_DIFFS := $(foreach test,$(TESTS),log_diffs/$(test:tests/%.mjava=%).diff)
ASTS := $(foreach test,$(TESTS),asts/$(test:tests/%.mjava=%).png)
AST_DIFFS := $(foreach test,$(TESTS),ast_diffs/$(test:tests/%.mjava=%).png)

EXAMPLES = $(wildcard examples/*.cpp)
EXAMPLE_OUTPUTS = $(foreach example,$(EXAMPLES),examples_outputs/$(example:examples/%.cpp=%).codegen.out)

CXX = clang++-12 -stdlib=libc++
CC = clang-12
CFLAGS = -g -I .
LLVMCXXFLAGS = `llvm-config-12 --cxxflags`
LLVMCFLAGS = `llvm-config-12 --cflags`
LLVMFLAGS = `llvm-config-12 --cxxflags --ldflags --system-libs --libs all`

FLEX = flex
YACC = yacc

all: build test asts examples
build: codegen
test: $(OUTPUTS) $(OUTPUT_DIFFS) $(LOGS) $(LOG_DIFFS)
asts: $(ASTS) $(AST_DIFFS)
examples: $(EXAMPLE_OUTPUTS)

codegen: ${OBJ}
	${CXX} ${CFLAGS} ${LLVMFLAGS} -o codegen y.tab.o table.o proj3.o semantic.o ${OBJ} -lfl

lex.yy.c: lex.l
	$(FLEX) lex.l

#y.tab.h: grammar.y lex.yy.c
#	$(YACC) -d -v grammar.y

#y.tab.c: grammar.y lex.yy.c
#	$(YACC) -d -v grammar.y

%.o: %.cpp ${HEADERS}
	${CXX} ${CFLAGS} ${LLVMCXXFLAGS} -c $< -o $@

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} ${LLVMCFLAGS} -c $< -o $@

define example_rules
examples_outputs/$(1:examples/%.cpp=%).exe: $(1) llvm/LLVMGlobals.o
	@${CXX} ${CFLAGS} ${LLVMFLAGS} llvm/LLVMGlobals.o $$< -o $$@
examples_outputs/$(1:examples/%.cpp=%).codegen.ll: examples_outputs/$(1:examples/%.cpp=%).exe
	@echo "$$< > $$@"
	-@$$< > $$@
examples_outputs/$(1:examples/%.cpp=%).codegen.s: examples_outputs/$(1:examples/%.cpp=%).codegen.ll
	@echo "${CC} -Wno-override-module -S -c $$< -o $$@"
	-@${CC} -Wno-override-module -S -c $$< -o $$@
examples_outputs/$(1:examples/%.cpp=%).codegen.exe: examples_outputs/$(1:examples/%.cpp=%).codegen.s
	@echo "${CC} $$< -o $$@"
	-@${CC} $$< -o $$@
examples_outputs/$(1:examples/%.cpp=%).codegen.out: examples_outputs/$(1:examples/%.cpp=%).codegen.exe
	@echo "$$< > $$@"
	-@$$< > $$@
endef
$(foreach example,$(EXAMPLES),$(eval $(call example_rules,$(example))))

define output_rules
outputs/$(1:tests/%.mjava=%).ll: $(1) codegen
	@echo "./codegen -v -o $$@ $(1) > /dev/null"
	-@./codegen -v -o $$@ $(1) > /dev/null
outputs/$(1:tests/%.mjava=%).s: outputs/$(1:tests/%.mjava=%).ll
	@echo "${CC} -Wno-override-module -S -c $$< -o $$@"
	-@${CC} -Wno-override-module -S -c $$< -o $$@
outputs/$(1:tests/%.mjava=%).o: outputs/$(1:tests/%.mjava=%).s
	@echo "${CC} -c $$< -o $$@"
	-@${CC} -c $$< -o $$@
outputs/$(1:tests/%.mjava=%).exe: outputs/$(1:tests/%.mjava=%).o
	@echo "${CC} $$^ -o $$@"
	-@${CC} $$^ -o $$@
ifneq ("$(wildcard tests/$(1:tests/%.mjava=%).in)","")
outputs/$(1:tests/%.mjava=%).out: outputs/$(1:tests/%.mjava=%).exe
	@echo "$$< < tests/$(1:tests/%.mjava=%).in > $$@"
	-@$$< < tests/$(1:tests/%.mjava=%).in > $$@
else
outputs/$(1:tests/%.mjava=%).out: outputs/$(1:tests/%.mjava=%).exe
	@echo "$$< > $$@"
	-@$$< > $$@
endif
endef
$(foreach test,$(TESTS),$(eval $(call output_rules,$(test))))

define output_diff_rules
output_diffs/$(1:tests/%.mjava=%).diff: outputs/$(1:tests/%.mjava=%).out
	@echo "diff -d $$< outputs_solution/$(1:tests/%.mjava=%).out > $$@"
	-@diff -d $$< outputs_solution/$(1:tests/%.mjava=%).out > $$@
endef
$(foreach test,$(TESTS),$(eval $(call output_diff_rules,$(test))))

define log_rules
logs/$(1:tests/%.mjava=%).log: $(1) codegen
	@echo "./codegen -v -o /dev/null $(1) > logs/$(1:tests/%.mjava=%).log || ./codegen -v $(1) > logs/$(1:tests/%.mjava=%).log"
	-@./codegen -v -o /dev/null $(1) > logs/$(1:tests/%.mjava=%).log || ./codegen -v $(1) > logs/$(1:tests/%.mjava=%).log
endef
$(foreach test,$(TESTS),$(eval $(call log_rules,$(test))))

define log_diff_rules
log_diffs/$(1:tests/%.mjava=%).diff: logs/$(1:tests/%.mjava=%).log
	@echo "diff -d $$< logs_solution/$(1:tests/%.mjava=%).log > $$@"
	-@diff -d $$< logs_solution/$(1:tests/%.mjava=%).log > $$@
endef
$(foreach test,$(TESTS),$(eval $(call log_diff_rules,$(test))))

define ast_rules
asts/$(1:tests/%.mjava=%).png: codegen $(1)
	@echo "./codegen -v -p asts/$(1:tests/%.mjava=%).gv $(1) > /dev/null"
	-@./codegen -v -p asts/$(1:tests/%.mjava=%).gv $(1) > /dev/null
	@echo "gv -Tpng asts/$(1:tests/%.mjava=%).gv > asts/$(1:tests/%.mjava=%).png"
	-@dot -Tpng asts/$(1:tests/%.mjava=%).gv > asts/$(1:tests/%.mjava=%).png
endef
$(foreach test,$(TESTS),$(eval $(call ast_rules,$(test))))

define ast_diff_rules
ast_diffs/$(1:tests/%.mjava=%).png: asts/$(1:tests/%.mjava=%).gv
	@echo "awk -f dotdiff.awk $$< asts_solution/$(1:tests/%.mjava=%).gv > ast_diffs/$(1:tests/%.mjava=%).gv"
	-@awk -f dotdiff.awk $$< asts_solution/$(1:tests/%.mjava=%).gv > ast_diffs/$(1:tests/%.mjava=%).gv
	@echo "dot -Tpng ast_diffs/$(1:tests/%.mjava=%).gv > $$@"
	-@dot -Tpng ast_diffs/$(1:tests/%.mjava=%).gv > $$@
endef
$(foreach test,$(TESTS),$(eval $(call ast_diff_rules,$(test))))

clean:
	rm -f codegen lex.yy.c ${OBJ} outputs/* output_diffs/* logs/* log_diffs/*

distclean: clean
	rm -f asts/*.png ast_diffs/*.png asts/*.gv ast_diffs/*.gv examples_outputs/*