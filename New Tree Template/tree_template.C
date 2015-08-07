/********************INCOMPLETE*****************************/








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

template <class T, int B, int D>				
class TreeChunk;	
template <class T, int B, int D, typename USER>
class Tree
{
  private:
  long int MaxNodesPerChunk;
  int TotalChunks;
  TreeChunk<T,B,D> *CurrentChunk;
  
  public:
  Tree()
  {
    int i;
    TotalChunks = 1;
    MaxNodesPerChunk = 0;
    for(i = 0;i<=D;i++)								
      MaxNodesPerChunk = MaxNodesPerChunk + pow(B,i);
  }
  
  /*void GenerateNode(USER *worker)
  {
    register int condition;
    do
    {
      if(CurrentChunk->totalNodesInMyChunk == MaxNodesPerChunk)
      {
        TreeChunk<T,B,D> NewChunk;
        CurrentChunk = &NewChunk;
      }
      Node NewNode(worker->MakeMyNewNode());
      CurrentChunk->RegisterNode(&NewNode);
    }while(worker->DoWork(condition);*/

  bool RegisterNewChild(Node<T,B,D> *ChildToBeRegistered, int NodeCounter)
  {
    TreeChunk<T,B,D> *PreviousChunk = NULL;  
    bool NewChunkCreated = 0;
    bool SuccessfulInsertion;
    if( (NodeCounter == -1) ||  (CurrentChunk->totalNodesInMyChunk == MaxNodesPerChunk) )
    { 
      NewChunkCreated = 1;
      PreviousChunk = CurrentChunk;
      TreeChunk<T,B,D> NewChunk;
      CurrentChunk = &NewChunk;
    }      
    SuccessfulInsertion = (CurrentChunk->RegisterNewChildInChunk(ChildToBeRegistered,NewChunkCreated,PreviousChunk,CurrentChunk));







template <class T, int B, int D>					//Forward Declaration
class Node;								
template <class T, int B, int D>					//Nodes of the tree chunk are allocated in Depth-First fashion
class TreeChunk						
{
  private:
  long int nextAvailable;
  long int CurrentNodeIndex;

  public:
  long int totalNodesInMyChunk;

  Node<T,B,D> *nodes;

  TreeChunk()
  {
    int i,j,level,counter,nextIndexLevel;					//Depth-First Allocation.
    CurrentNodeIndex = 0;
    totalNodesInMyChunk = 0;
    counter = 0;
    level = 0;
    nextIndexLevel = 0;
    for(i = 0;i<=D;i++)								
      totalNodesInMyChunk = totalNodesInMyChunk + pow(B,i);	
    nextAvailable = 0;								//This is used to keep track of the next available location.
    long int Maxsize = totalNodesInMyChunk + pow(B,(D + 1));
    nodes = new Node<T,B,D>[Maxsize];					
    for(i = 0; (((i + 1) * B) < Maxsize); i++)					//Initialize all nodes of the tree.
    {
      nodes[i].mass = rand() % RANGE;						//Assigning random masses to each node.
      nodes[i].exist = 1;

      for(j = 1;j<=B;j++)
      {
        nodes[i].chunk[j - 1] = NULL;						//All nodes initially do not point to any other tree chunks.
        nodes[i * B + j].exist = 0;						//All nodes initially have no children.
      }
    } 
 
    for(i = 0;((i + 1)*B) < Maxsize; i++)						//Assign types to the nodes
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
    for(i = 1;(i<=B) && ((index * B + i) < totalNodesInMyChunk);i++)
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

  bool RegisterNewChildInChunk(Node<T,B,D> *ChildToBeRegistered, bool AssignChunkPointers, TreeChunk<T,B,D> *PreviousChunk, TreeChunk<T,B,D> *CurrentChunk) 
  {
    bool result;
    ChildToBeRegistered->exist = 1;
    if(AssignChunkPointers)
    {
      if((PreviousChunk->nodes[(PreviousChunk->CurrentNodeIndex)])->ChunkPointerCounter < (B - 1))
      {
        (PreviousChunk->nodes[(PreviousChunk->CurrentNodeIndex)])->chunk[(PreviousChunk->nodes[(PreviousChunk->CurrentNodeIndex)])->ChunkPointerCounter] = CurrentChunk;
        (PreviousChunk->nodes[(PreviousChunk->CurrentNodeIndex)])->ChunkPointerCounter++;
      }
      else 
        ChildToBeRegistered->chunk[(ChildToBeRegistered->ChunkPointerCounter)] = NULL;

    nodes[CurrentNodeIndex++] = *(ChildToBeRegistered);
    totalNodesInMyChunk++;
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
  int ChunkPointerCounter;
  typedef enum Type{ChunkInternalTreeLeaf,ChunkInternalNotTreeLeaf,ChunkBoundary}Type;
  Type nodeType;
  
  Node()
  {}

  Node(T *MyData)
  { 
    int i,j;
    for(i = 0;i<BUF_SIZE;i++)
      data[i] = MyData[i];
    mass = rand() % RANGE;						//Assigning random masses to each node.The field "mass" is not required
    exist = 1;
    for(i = 0;j<B;j++)
      chunk[i] = NULL;						//All nodes initially do not point to any other tree chunks.
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
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodesInMyChunk)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
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
      for(i = 0;(i<(tc->totalNodesInMyChunk)) && (worker->DoWork((tc->nodes[i]).GetNodeType()));i++)
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
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodesInMyChunk)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
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
      for(i = 1; i < (tc->totalNodesInMyChunk);i++)
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
    for(i = 1;(i<=B) && ((index * B + i) < (tc->totalNodesInMyChunk)) && (worker->DoWork((tc->nodes[index]).GetNodeType()));i++)
      BUpreorderTD<T,B,D,USER>(tc,(index * B + i), worker);
  }

};


class MyClass									//This is the user's class
{
  private:
  template <class T, int B, int D>
  bool Check(Node<T,B,D> *CheckThisNode)
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

  template <class T, int B, int D>
  void DoWork(Tree<T,B,D> *MyTree,int NodeCounter)
  { 
    bool CorrectChildInsertion;
    do
    {
      int i; 
      Node<T,B,D> *NewChildNode;
      NewChildNode->mass = rand() % RANGE;
      for(i = 0;i<BUF_SIZE;i++)
        NewChildNode->data[i] = rand() % RANGE;
      CorrectChildInsertion = MyTree->RegisterNewChild(NewChildNode, NodeCounter);
      if(CorrectChildInsertion)
        NodeCounter++;
    while(Check<T,B,D>(NewChildNode) && CorrectChildInsertion);
  }

  /*template <class T,int B, int D>
  Node<T,B,D> *MakeMyNewNode()
  {
    Node<T,B,D> *NewNode = new Node<T,B,D>;
    int i;
    for(i = 0;i<BUF_SIZE;i++)
      NewNode->data[i] = rand() % RANGE;					//user fills nodes data however he wants to..here we just use rand()
    NewNode->mass = rand() % RANGE;
    NewNode->exist = 1;
    NewNode->type
    return myData;
  }*/
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
    Tree<int,4,2,MyClass>MyTree;
    MyClass a;
    a.DoWork(&MyTree,-1);
	
    /*TreeChunk<int,4,2>tc;						//<User data type,Branching Factor,Depth>
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
    bu.DoTraversal<int,4,2,MyClass>(&tc,&a,2);*/
    CkExit();
  }
};
#include"tree_template.def.h"








