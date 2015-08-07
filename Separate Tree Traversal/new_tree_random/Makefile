CHARMC=../../../../../../bin/charmc $(OPTS)

OBJS = tree_random.o

all: tree_random

tree_random: $(OBJS)
	$(CHARMC) -language charm++ -o tree_random $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++  -tracemode projections -o tree_random.prj $(OBJS)

tree_random.decl.h: tree_random.ci
	$(CHARMC)  tree_random.ci

clean:
	rm -f *.decl.h *.def.h *.log *.prj.sts *.prj.projrc conv-host *.o tree_random charmrun tree_random.prj

tree_random.o: tree_random.C tree_random.decl.h
	$(CHARMC) -g -c tree_random.C


