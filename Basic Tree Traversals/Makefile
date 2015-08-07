CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = tree.o

all: tree

tree: $(OBJS)
	$(CHARMC) -language charm++ -o tree $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++  -tracemode projections -o tree.prj $(OBJS)

tree.decl.h: tree.ci
	$(CHARMC)  tree.ci

clean:
	rm -f *.decl.h *.def.h *.log *.prj.sts *.prj.projrc conv-host *.o tree charmrun tree.prj

tree.o: tree.C tree.decl.h
	$(CHARMC) -g -c -o3 tree.C


