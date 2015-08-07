CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = tree_dft.o

all: tree_dft

tree_dft: $(OBJS)
	$(CHARMC) -language charm++ -o tree_dft $(OBJS)

tree_dft.decl.h tree_dft.def.h : tree_dft.ci
	$(CHARMC)  tree_dft.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o tree_dft charmrun

tree_dft.o: tree_dft.C tree_dft.decl.h
	$(CHARMC) -g -c tree_dft.C


