#include"tree_dynamic.decl.h"
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
    int buf[RANGE];
    struct node *left, *right;
  }node;
  node *root;

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
    root = new node;
  }
   
  void init()
  {
    root->mass = rand()%RANGE;
    root->left = NULL;
    root->right = NULL;
    makeTree(root,DEPTH);
  }

  void makeTree(node *p, int rem)
  {  
    if(rem == 0)
    {
      p->left = NULL;
      p->right = NULL;
      return;
    }
    p->left = new node; 
    p->right = new node;
    p->left->mass = rand()%RANGE;   
    p->right->mass = rand()%RANGE;
    makeTree(p->left,rem-1);
    makeTree(p->right, rem-1); 
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
      srand(time(NULL));
      tree t;
      t.init();
      double startTime = CmiWallTimer();
      t.traverse(); 
      long double execTime = CmiWallTimer() - startTime;
      CkPrintf("Execution time:  %1.9Lf \n",execTime);
      CkExit();
    };
};
#include"tree_dynamic.def.h"





			
