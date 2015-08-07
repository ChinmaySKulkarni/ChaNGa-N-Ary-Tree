#include"tree.decl.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE 1000
#define BUF_SIZE 100
#define DEPTH 15
#define ITERATIONS 100

class Tree									
{
  protected:
  typedef struct node
  {
    int mass;
    int used;
    int buf[BUF_SIZE];
    struct node *left, *right;
  }node;
  node *root;
  long int treeSize;

  void Inorder(node *p) 
  {
    if(p == NULL)
      return;
    Inorder(p->left);
    CkPrintf("%d \n", p->mass);
    Inorder(p->right);
  }

  void Preorder(node *p) 
  {
    if(p == NULL)
      return;
    //CkPrintf("%d \n", p->mass);
    Preorder(p->left);
    Preorder(p->right);
  }

  void Postorder (node *p) 
  {
    if(p == NULL)
      return;
    Postorder(p->left);
    Postorder(p->right);
    CkPrintf("%d \n", p->mass);
  }
 
  public:
  void Traverse()
  {
    int iterations = ITERATIONS;
    while(iterations--)
      Preorder(root); 
  }
};


class TreeNew: public Tree
{
  private:
  void MakeTreeNew(node *p, int rem)
  {  
    p->mass = rand() % RANGE;
    if(rem == 0)
    {
      p->left = NULL;
      p->right = NULL;
      return;
    }
    p->left = new node; 
    p->right = new node;
    MakeTreeNew(p->left,rem-1);
    MakeTreeNew(p->right, rem-1); 
  }
  
  public:
  TreeNew()
  {
    CkPrintf("Size of node: %d bytes\n",sizeof(node));
    root = new node;
  }

  void Init()
  {
    MakeTreeNew(root,DEPTH);
  }
};


class TreeRandom: public Tree				//Random Allocation.
{
  private:
  void MakeTree(node *p, int d)				       
  { 
    if(d >= DEPTH )
      return;
    p->left = FindFree();
    MakeTree(p->left,d+1);
    p->right = FindFree();
    MakeTree(p->right,d+1); 
  }

  node *FindFree()					//Finds a random index that is free.
  {
    int nextfree;
    do 
      nextfree = rand() % treeSize;
    while(BT[nextfree].used);
    BT[nextfree].used = 1;
    return &(BT[nextfree]);
  }

  protected:
  node *BT;

  public:
  TreeRandom()
  {
    int i;						
    treeSize = 0;
    for(i = 0;i<=DEPTH;i++)
      treeSize = treeSize + pow(2,i);
    BT = new node[treeSize];				//This is used in the random and depth first allocation.
    for(i = 0; i<treeSize; i++)				//Initialize all nodes of the tree.
    {
      BT[i].mass = rand() % RANGE;			//Assigning random masses to each node.
      BT[i].left = NULL;				//All nodes initially have NULL children.
      BT[i].right = NULL;
      BT[i].used = 0;			 		//used 0 indicates that node has not been used.
    }
  }

  void Init()
  {
    root = FindFree();
    MakeTree(root,0);
  }
};


class TreeDF: public TreeRandom
{
  private:
  long int nextAvailable;

  void MakeTree(node *p, int d)				       
  { 
    if(d >= DEPTH )
      return;
    p->left = FindFreeDF();
    MakeTree(p->left,d+1);
    p->right = FindFreeDF();
    MakeTree(p->right,d+1); 
  }

  node *FindFreeDF()
  {
    int nextfreeDF = nextAvailable;
    nextAvailable++;
    return &(BT[nextfreeDF]);
  }    

  public:
  TreeDF()
  {
    int i;							//Random Allocation and Depth-First Allocation.
    treeSize = 0;
    for(i = 0;i<=DEPTH;i++)
      treeSize = treeSize + pow(2,i);
    nextAvailable = 0;					//This is used in depth first allocation to keep track of the next available location.
    BT = new node[treeSize];				//This is used in the random and depth first allocation.
    for(i = 0; i<treeSize; i++)				//Initialize all nodes of the tree.
    {
      BT[i].mass = rand() % RANGE;				//Assigning random masses to each node.
      BT[i].left = NULL;					//All nodes initially have NULL children.
      BT[i].right = NULL;
    }
  }

  void Init()
  {
    root = FindFreeDF();
    MakeTree(root,0);
  }
};


class Main: public CBase_Main
{
  public:
  Main(CkMigrateMessage *msg)
  {};

  Main(CkArgMsg *m)
  {
    delete m;
    CkPrintf("No. of iterations:\t%d\tDepth:\t%d\n",ITERATIONS,DEPTH);	
    srand(time(NULL));
    CkPrintf("Allocating nodes using 'new' \n");
    TreeNew tn;
    tn.Init();
    double startTime1 = CmiWallTimer();
    tn.Traverse(); 
    long double execTime1 = CmiWallTimer() - startTime1;
    CkPrintf("Execution time:  %1.9Lf \n",execTime1);

    CkPrintf("Allocating nodes using Random Allocation \n");
    TreeRandom tr;
    tr.Init();
    double startTime2 = CmiWallTimer();
    tr.Traverse(); 
    long double execTime2 = CmiWallTimer() - startTime2;
    CkPrintf("Execution time:  %1.9Lf \n",execTime2);

    CkPrintf("Allocating nodes using Depth-First Allocation \n");
    TreeDF td;
    td.Init();
    double startTime3 = CmiWallTimer();
    td.Traverse(); 
    long double execTime3 = CmiWallTimer() - startTime3;
    CkPrintf("Execution time:  %1.9Lf \n",execTime3); 	
    CkExit();
  };
};
#include"tree.def.h"







