#include"tree_random.decl.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE 1000
#define DEPTH 10
#define ITERATIONS 100
#define CHOICE 1

class tree									//Sequential C++ Class
{
  private:
  typedef struct node
  {
    int mass;
    int used;
    int buf[RANGE];
    struct node *left, *right;
  }node;
  node *root;
  node *BT;
  long int treeSize;

  void inorder(node *p) 
  {
    if(p == NULL)
      return;
    inorder(p->left);
    CkPrintf("%d \n", p->mass);
    inorder(p->right);
  }

  void preorder(node *p) 
  {
    if(p == NULL)

      return;
    //CkPrintf("%d \n", p->mass);
    preorder(p->left);
    preorder(p->right);
  }

  void postorder (node *p) 
  {
    if(p == NULL)
      return;
    postorder(p->left);
    postorder(p->right);
    CkPrintf("%d \n", p->mass);
  }

  public:
  tree()
  {
    int i;
    treeSize = 0;
    for(i = 0;i<=DEPTH;i++)
      treeSize = treeSize + pow(2,i);
    //nextAvailable = 0;						This is used in depth first allocation
    BT = new node[treeSize];					//This is used in the random and depth first allocation
    srand(time(NULL));
    for(i = 0; i<treeSize; i++)					//Initialize all nodes of the tree.
    {
      BT[i].mass = rand() % RANGE;				//Assigning random masses to each node.
      BT[i].used = 0;						//used 0 indicates that node has not been used.
      //CkPrintf("BT[%d].used = %d \n",i,BT[i].used);
      BT[i].left = NULL;					//All nodes initially have NULL children.
      BT[i].right = NULL;
    }
  }

  void init()
  { 
    root = findFree();
    makeTree(root,0);
  }

  node *findFree()						//finds a random index that is free.
  {
    int nextfree;
    do 
      nextfree = rand() % treeSize;
    while(BT[nextfree].used);
    BT[nextfree].used = 1;
    return &(BT[nextfree]);
  }

  /*node *findFreeDF()
  {
    int nextfreeDF = nextAvailable;
    nextAvailable++;
    return &(BT[nextfreeDF]);
  } */   


  void makeTree(node *p, int d)				       //Starts with passing BT[0] and totalSize
  { 
    if(d >= DEPTH )
      return;
    p->left = findFree();
    makeTree(p->left,d+1);
    p->right = findFree();
    makeTree(p->right,d+1); 
  }

  void traverse()
  {
    int iterations = ITERATIONS;
    switch (CHOICE)
    {
      case 1:
      {
        while(iterations--)
          preorder(root); 
	break;
      }
      case 2:
      {
        while(iterations--)
          inorder(root); 
	break;
      }
      case 3:
      {
        while(iterations--)
          postorder(root); 
        break;
      }
      default:
      {
        while(iterations--)
          preorder(root); 
	break;
      }
    }
  }
};


class main: public CBase_main
{
  public:
    main(CkMigrateMessage *msg)
    {};

    main(CkArgMsg *m)
    {
      delete m;
      tree t;
      t.init();
      double startTime = CmiWallTimer();
      t.traverse(); 
      long double execTime = CmiWallTimer() - startTime;
      CkPrintf("Execution time:  %1.9Lf \n",execTime);
      CkExit();
    };
};
#include"tree_random.def.h"


