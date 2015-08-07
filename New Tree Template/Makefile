CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = tree_template.o

all: tree_template

tree_template: $(OBJS)
	$(CHARMC) -language charm++ -o tree_template $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++  -tracemode projections -o tree_template.prj $(OBJS)

tree_template.decl.h: tree_template.ci
	$(CHARMC)  tree_template.ci

clean:
	rm -f *.decl.h *.def.h *.log *.prj.sts *.prj.projrc conv-host *.o tree_template charmrun tree_template.prj

tree_template.o: tree_template.C tree_template.decl.h
	$(CHARMC) -g -c -o3 tree_template.C


