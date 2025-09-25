TARGETS = parser
TESTS = $(wildcard tests/*.mjava)
OUTPUTS := $(foreach test,$(TESTS),outputs/$(test:tests/%.mjava=%).out)
DIFFS_OUTPUTS := $(foreach test,$(TESTS),diffs_outputs/$(test:tests/%.mjava=%).diff)
DIFFS_ASTS := $(foreach test,$(TESTS),diffs_asts/$(test:tests/%.mjava=%).png)

CC = gcc
C++ = g++
FLEX = flex
YACC=yacc

all: build test
build: $(TARGETS)
test: $(OUTPUTS) $(DIFFS_OUTPUTS) $(DIFFS_ASTS)

parser: y.tab.o proj2.o table.o main.o
	$(CC) -g -o parser y.tab.o proj2.o table.o main.o -ll -lstdc++

y.tab.c: lex.yy.c proj2.h
y.tab.c: grammar.y
	$(YACC) -d -v  $< 

lex.yy.c: lex.l
	$(FLEX) $< 

%.o: %.c
	$(CC) -g -c $<
%.o: %.cpp
	$(C++) -g -c $<

define test_rules
outputs/$(1:tests/%.mjava=%).out: parser $(1)
	@echo "./parser -p asts/$(1:tests/%.mjava=%).gv $(1) > $$@"
	-@./parser -p asts/$(1:tests/%.mjava=%).gv $(1) > $$@
	@echo "gv -Tpng asts/$(1:tests/%.mjava=%).gv > asts/$(1:tests/%.mjava=%).png"
	-@dot -Tpng asts/$(1:tests/%.mjava=%).gv > asts/$(1:tests/%.mjava=%).png
endef
$(foreach test,$(TESTS),$(eval $(call test_rules,$(test))))

define diff_rules
diffs_outputs/$(1:tests/%.mjava=%).diff: outputs/$(1:tests/%.mjava=%).out
	@echo "diff -dy -W 170 $$< outputs_solution/$(1:tests/%.mjava=%).out > $$@"
	-@diff -d $$< outputs_solution/$(1:tests/%.mjava=%).out > $$@
diffs_asts/$(1:tests/%.mjava=%).png: asts/$(1:tests/%.mjava=%).gv
	@echo "awk -f dotdiff.awk $$< asts_solution/$(1:tests/%.mjava=%).gv > diffs_asts/$(1:tests/%.mjava=%).gv"
	-@awk -f dotdiff.awk $$< asts_solution/$(1:tests/%.mjava=%).gv > diffs_asts/$(1:tests/%.mjava=%).gv
	-@dot -Tpng diffs_asts/$(1:tests/%.mjava=%).gv > $$@
endef
$(foreach test,$(TESTS),$(eval $(call diff_rules,$(test))))

clean:
	rm -f parser *.o lex.yy.c y.tab.h y.tab.c y.output outputs/*.out asts/*.gv asts/*.png diffs_outputs/*.diff diffs_asts/*.gv diffs_asts/*.png