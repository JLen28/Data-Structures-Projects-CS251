/*bst.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey,typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
    TValue Value;
    NODE* Left;
    NODE* Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }

  void _construct(NODE* cur) // private member builds copy... 
  {
    if (cur == nullptr){
      return;
    }
    else
    {
      insert(cur->Key,cur->Value);
      _construct(cur->Left);
      _construct(cur->Right);
    }
  }




public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
  
  //
  // copy constructor:
  //
  //
  //
  binarysearchtree(const binarysearchtree& other){
    NODE* temp = new NODE();
    temp = other.Root;
    this->Root = nullptr;
     _construct(temp);
    this->Size = other.Size;
 
  } // end copy constructor...

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
     return _height(Root);
  }
  
  int  _height(NODE* cur){
     if(cur == nullptr){
        return -1;
     }
     else{
        int heightL= _height(cur->Left); 
        int heightR = _height(cur->Right);
        
        if (heightL> heightR){
           return heightL + 1;
           }
           else{
              return heightR + 1;
           }
     }
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key){  // already in tree
 
        return &(cur->Value);
      }
      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key,TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 

    //
    // TODO: allocate a new node, store key, initialize
    // pointer fields:
     NODE* fresh = new NODE;
     fresh->Key = key;
     fresh->Value = value;
     fresh->Left = nullptr;
     fresh->Right = nullptr;
     

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if(prev == nullptr){
       Root = fresh;
    }
    else if(prev->Key > fresh->Key){
       prev->Left = fresh;
    }
    else if(prev->Key < fresh->Key){
       prev->Right = fresh;
    }

    //
    // TODO: link in the new node, updating Root 
    // pointer as appropriate
    //

    // 
    // 4. update size and we're done:
    //
    Size++;
    //
    // TODO:
    //
  }

  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

};


