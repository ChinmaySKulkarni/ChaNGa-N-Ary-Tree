#include"tree_template.decl.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define RANGE 1000
#define BUF_SIZE 10
#define ITERATIONS 1
using namespace std;
									/****nodes have data of class "T", Branching factor given by "B", Depth 									* of tree chunk given by class "D". 
									* Node Types:
									* CITL: Chunk Internal, Tree Leaf		
									* CNTL: Chunk Internal, Not Tree Leaf		
									* CB: Chunk Boundary.						****/


/************ create the treechunk's nodes dynamically according to userclass worker function. See photo.
if the user wants to add a child to a node that is at the boundary of a chunk then request for the creation of a new chunk..similarly during traversal also, request for a chunk if at boundary of a chunk and next child is required.		

there is a 
Treeconstructor w;
treechunk<...> tc
traversal trav;
trav.visit(tc,w);
-->this w is a worker object and it performs work of the user defined type

Treeconstructor::work(node*n,treechunk *tc,...index..??){
  if(n->isLeaf && depth<DEPTH)
    chunk.createNewchild(n)------>
---------------------------------this creates a new child for the node "n"...here you must check that this is valid, i.e. if it is CB, you will have to ----------------------------------create a new chunk itself and suitably assign the poitner of ""CHUNKS[..]"" accordingly and use internal logic to ----------------------------------record nodes and the number of the child.
    return true;
  else if(depth == DEPTH)
    return false;
}


create a tree of many chunks. You should store the nodes internally using your logic in depth first fashion and give the user an interface to check whether he wants a node to be given a child or not.
	
*/












template <class T, int B, int D>					//Forward Declaration
class Node;								
template <class T, int B, int D>					//Nodes of the tree chunk are allocated in Depth-First fashion
class TreeChunk						
{
  private:
  long int nextAvailable;

  public:
  long int totalNodes;
  Node<T,B,D> *nodes;

  TreeChunk()
  {
    int i,j,level,counter,nextIndexLevel;					//Depth-First Allocation.
    totalNodes = 0;
    counter = 0;
    level = 0;
    nextIndexLevel = 0;
    for(i = 0;i<=D;i++)								
      totalNodes = totalNodes + pow(B,i);	
    nextAvailable = 0;								//This is used to keep track of the next available location.
    long int size = totalNodes + pow(B,(D + 1));
    nodes = new Node<T,B,D>[size];					
    for(i = 0; (((i + 1) * B) < size); i++)					//Initialize all nodes of the tree.
    {
      nodes[i].mass = rand() % RANGE;						//Assigning random masses to each node.
      nodes[i].exist = 1;

      for(j = 1;j<=B;j++)
      {
        nodes[i].chunk[j - 1] = NULL;						//All nodes initially do not point to any other tree chunks.
        nodes[i * B + j].exist = 0;						//All nodes initially have no children.
      }
    } 
 
    for(i = 0; ((i + 1)*B) < size; i++)						//Assign types to the nodes
    {
      nodes[i].SetNodeType(0);							//CITL

      for(j = 1;j<=B;j++)
      {
        if(nodes[i * B + j].exist) 	      
          nodes[i].SetNodeType(1);						//CNTL
      }
      
      if(level == D)
        nodes[i].SetNodeType(2);						//CB
      
      if(i == nextIndexLevel)
      {
        level++;
        nextIndexLevel = nextIndexLevel + pow(B,level);
      }
    }
  }

  void MakeTreeChunk(int index, int d)				       
  { 
    int i;
    if(d >= D )
      return;
    for(i = 1;(i<=B) && ((index * B + i) < totalNodes);i++)
    {
      nodes[index * B + i] = *(FindFreeDF());
      MakeTreeChunk((index * B + i), d+1);
    }
  }

  Node<T,B,D> *FindFreeDF()
  {
    int nextfreeDF = nextAvailable;
    nextAvailable++;
    return &(nodes[nextfreeDF]);
  }    

};


template <class T, int B, int D>					
class Node
{
  public:
  bool exist;
  T mass;
  T data[BUF_SIZE];
  TreeChunk<T,B,D> *chunk[B];
  typedef enum Type{ChunkInternalTreeLeaf,ChunkInternalNotTreeLeaf,ChunkBoundary}Type;
  Type nodeType;
  
  Node()
  { 
    int i;
    for(i = 0;i<BUF_SIZE;i++)
      data[i] = rand() % RANGE;
  }
  
  void SetNodeType(int type)
  {
    if(type == 0)
      this->nodeType = ChunkInternalTreeLeaf;
    else if(type == 1)
      this->nodeType = ChunkInternalNotTreeLeaf;
    else 
      this->nodeType = ChunkBoundary;
  }

  int GetNodeType()
  {
    if(nodeType == ChunkInternalTreeLeaf)
      return 0;
    else if(nodeType == ChunkInternalNotTreeLeaf)
      return 1;
    else 
      return 2;
  }
};


class DFT 									//Depth-First Traversal
{
  private:
  int iterations;

  public:
  DFT()
  {
    iterations = ITERATIONS - 1;
  }

  template <class T, int B, int D, typename USER>
  void DoTraversal(TreeChunk<T,B,D> *tc, USER *worker)
  { 
    do
      Preorder<T,B,D,USER>(tc,0,worker); 
    while(iterations--);
  }
  
  template <class T, int B, int D,typename USER>
  void Preorder(TreeChunk<T,B,D> *tc, int index, USER *worker) 
  {
    int i;
    if(!((tc->nodes[index]).exist))
      return;	//******************************NOT return, but request chunk for a parallel implementation.
    CkPrintf("DFT\tnodes[%d].mass = %d\n",index,(tc->nodes[index]).mass);
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodes)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
      Preorder<T,B,D,USER>(tc,(index * B + i),worker);
  }
};


class BFT 							//Breadth-First Traversal
{
  private:
  int iterations;

  public:
  BFT()
  {
    iterations = ITERATIONS - 1;
  }

  template <class T, int B, int D, typename USER>
  void DoTraversal(TreeChunk<T,B,D> *tc, USER *worker)
  {
    int i;
    do
    {
      for(i = 0;(i<(tc->totalNodes)) && (worker->DoWork((tc->nodes[i]).GetNodeType()));i++)
        CkPrintf("BFT\tnodes[%d].mass = %d\n",i,(tc->nodes[i]).mass);
    }while(iterations--);
  }
};


class TD 									//Top-Down Traversal
{
  private:
  int iterations;

  public:
  TD()
  {
    iterations = ITERATIONS - 1;
  }

  template <class T, int B, int D, typename USER>
  void DoTraversal(TreeChunk<T,B,D> *tc, USER *worker)
  { 
    do
      PreorderTD<T,B,D,USER>(tc,0,worker); 
    while(iterations--);
  }

  template <class T, int B, int D, typename USER>
  void PreorderTD(TreeChunk<T,B,D> *tc, int index, USER *worker) 
  {
    int i;
    if(!((tc->nodes[index]).exist))
      return;
    CkPrintf("TD\tnodes[%d].mass = %d \n",index,(tc->nodes[index]).mass);
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodes)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
      PreorderTD<T,B,D,USER>(tc,(index * B + i), worker);
  }
};


class BU 									//Bottom-Up Traversal
{
  private:
  int iterations;

  public:
  BU()
  {
    iterations = ITERATIONS - 1;
  }

  template <class T, int B, int D, typename USER>
  void DoTraversal(TreeChunk<T,B,D> *tc, USER *worker, int startIndex)		//user provides the "startIndex"
  {
    do 
    {
      CkPrintf("BU\tStarting Node: nodes[%d].mass = %d \n",startIndex,(tc->nodes[startIndex]).mass);
      BottomUp<T,B,D,USER>(tc,worker,startIndex);
    }
    while(iterations--);				
  }

  template <class T, int B, int D, typename USER>
  void BottomUp(TreeChunk<T,B,D> *tc, USER *worker, int index)
  {
    int i;
    if(index == 0)								//Root
      CkPrintf("BU\tnodes[%d].mass = %d \n",index,(tc->nodes[index]).mass);
    else
    {
      int siblingIndices[B -1];							//int array holding indices of all siblings
      int k = 0;
      for(i = 1; i < (tc->totalNodes);i++)
      {
        if( ((index - 1)/B == (i -1)/B) && (index != i) )
        siblingIndices[k++] = i;
      }
      for(k = 0;(k<(B-1)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));k++)
        BUpreorderTD<T,B,D,USER>(tc,siblingIndices[k],worker);
      BottomUp<T,B,D,USER>(tc,worker,(index -1)/B);
    }
 }

  template <class T, int B, int D, typename USER>
  void BUpreorderTD(TreeChunk<T,B,D> *tc, int index, USER *worker) 
  {
    int i;
    if(!((tc->nodes[index]).exist))
      return;
    CkPrintf("BU\tnodes[%d].mass = %d \n",index,(tc->nodes[index]).mass);
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodes)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
      BUpreorderTD<T,B,D,USER>(tc,(index * B + i), worker);
  }

};


class MyClass									//This is the user's class
{
  private:
  bool Check(int nodeType)
  {
    /*if(nodeType == 0)								//CITL so can not descend on this branch
      return 0;
    else/*(user defined condition)*/
      return 1;
  }	

  public:
  MyClass()
  {
    //user defined
  }

  bool DoWork(int nodeType)
  { 
    //user defined
    return Check(nodeType);
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
    CkPrintf("No. of iterations:\t%d\n",ITERATIONS );	
    srand(time(NULL));
    TreeChunk<int,4,2>tc;						//<User data type,Branching Factor,Depth>
    tc.MakeTreeChunk(0,0);
    MyClass a;
    DFT dft;
    BFT bft;
    TD td;
    BU bu;
    CkPrintf("Starting the traversals \n");
    dft.DoTraversal<int,4,2,MyClass>(&tc,&a);
    bft.DoTraversal<int,4,2,MyClass>(&tc,&a);
    td.DoTraversal<int,4,2,MyClass>(&tc,&a);
    bu.DoTraversal<int,4,2,MyClass>(&tc,&a,2);
    CkExit();
  }
};
#include"tree_template.def.h"








