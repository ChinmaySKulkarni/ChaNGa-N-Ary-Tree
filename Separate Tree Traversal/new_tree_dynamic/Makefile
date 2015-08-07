CHARMC=../../../../../../bin/charmc $(OPTS)

OBJS = tree_dynamic.o

all: tree_dynamic

tree_dynamic: $(OBJS)
	$(CHARMC) -language charm++ -o tree_dynamic $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++  -tracemode projections -o tree_dynamic.prj $(OBJS)

tree_dynamic.decl.h: tree_dynamic.ci
	$(CHARMC)  tree_dynamic.ci

clean:
	rm -f *.decl.h *.def.h *.log *.prj.sts *.prj.projrc conv-host *.o tree_dynamic charmrun tree_dynamic.prj

tree_dynamic.o: tree_dynamic.C tree_dynamic.decl.h
	$(CHARMC) -g -c tree_dynamic.C


