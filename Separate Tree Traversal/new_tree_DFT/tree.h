#ifndef __TREE_H__
#define __TREE_H__
#define RANGE 1000
#define DEPTH 10
#define ITERATIONS 100
#define CHOICE 1

/*class tree									//Sequential C++ Class
{
  private:
  typedef struct node
  {
    int mass;
    int buf[RANGE];
    struct node *left, *right;
  }node;
  node *root;*/

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
  tree();
   
  void init();
  
  void makeTree(node *p, int rem);
     
  void traverse()
  {
    int iterations = ITERATIONS;
    node *p = new node;
    p = root;
    switch (CHOICE)
    {
      case 1:
      {
        while(iterations--)
          preorder(p); 
	break;
      }
      case 2:
      {
        while(iterations--)
          inorder(p); 
	break;
      }
      case 3:
      {
        while(iterations--)
          postorder(p); 
        break;
      }
      default:
      {
        while(iterations--)
          preorder(p); 
	break;
      }
    }
  }
};

class main: public CBase_main
{
  public:
    main(CkMigrateMessage *msg);

    main(CkArgMsg *m);
};
#endif //__TREE_H__


