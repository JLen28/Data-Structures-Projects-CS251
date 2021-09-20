/*avl.h*/
////////////////////////////////////////////////////////
///////// Joseph Lenaghan | UIN: 676805596
// University of Illinois at Chicago
//  AVL tree class with rebalancing and distance function
////////////////////////////////////////////////////////
/////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE // node definition...
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
	
	
  //function handles the 4 cases of the AVL tree using if else conditionals...
  void _RotateToFix(NODE* Parent, NODE* N) // 
  {
		assert(N != nullptr);
		
      int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
      int hR = (N->Right == nullptr) ? -1 : N->Right->Height;
		
		assert(std::abs(hL-hR) > 1);
			
		if(hL > hR) // cases 1 or 2 
		{
			int outer = (N->Left->Left != nullptr) ? N->Left->Left->Height : -1;
	        int inner = (N->Left->Right != nullptr) ? N->Left->Right->Height : -1;
			
			
			if(outer > inner)  // case 1..
			{
				
				_RightRotate(Parent,N);
			}
			else  // case 2...
			{
			     _LeftRotate(N,N->Left);
				 _RightRotate(Parent,N);
			}
		}
		else 
		{
			int outer = (N->Right->Right != nullptr) ? N->Right->Right->Height : -1;
	        int inner = (N->Right->Left != nullptr) ? N->Right->Left->Height : -1;
			
			if(outer > inner) // cases 3 
			{
				
				_LeftRotate(Parent,N);
			}
			else // case 4
			{
				
				_RightRotate(N,N->Right);
				_LeftRotate(Parent,N);
			}
			
		}
  }// end RotateToFix...	

  // 
  // Varius formats of inorder defined below..
  //
  void _inorder(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }// end inorder...

  void _inorder_keys(NODE* cur, std::vector<TKey>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_keys(cur->Left, V);
      V.push_back(cur->Key);
      _inorder_keys(cur->Right, V);
    }
  }// end inorder_keys...

  void _inorder_values(NODE* cur, std::vector<TValue>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_values(cur->Left, V);
      V.push_back(cur->Value);
      _inorder_values(cur->Right, V);
    }
  }// end inorder_values...

  void _inorder_heights(NODE* cur, std::vector<int>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_heights(cur->Left, V);
      V.push_back(cur->Height);
      _inorder_heights(cur->Right, V);
    }
  }// end inorder_values...

  //
  // Copy Constructor helper function..
  //
  void _copytree(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {

      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
    }
  }

  //
  // _RightRotate
  // 
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    NODE* L = N->Left;
    NODE* B = L->Right;
   
    N->Left = B;
    L->Right = N;
   
    if(Parent == nullptr)
    {
      Root = L;
    }
    else if(L->Key < Parent->Key)
    {
      Parent->Left = L;
    }
    else
    {
       Parent->Right = L;
    }
    if((N->Left != nullptr) && (N->Right != nullptr)) 
    {
	   N->Height = 1 + max(N->Left->Height,N->Right->Height);
      
    }
    else if((N->Left == nullptr) && (N->Right == nullptr))
    {
       N->Height = 0;
    }
    else if(N->Right == nullptr)
    {
      N->Height = N->Left->Height + 1;
    }
    else
    {
		N->Height = N->Right->Height + 1;
    }
    if((L->Left != nullptr) && (L->Right != nullptr))
    {
	   L->Height = 1 + max(L->Left->Height,L->Right->Height);
      
    }
    else if((N->Left == nullptr) && (N->Right == nullptr))
    {
	   L->Height = 0;
    }
    else if(L->Right == nullptr)
    {
       L->Height = L->Left->Height + 1;
    }
    else
    {
        L->Height = L->Right->Height + 1;
    }

  } // end RightRotate...
	
  //
  // _LeftRotate
  // 
  //
  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);

    NODE* L = N->Right;
    NODE* B = L->Left;
   
    N->Right = B;
    L->Left = N;
	  
	
   
if(Parent == nullptr)
    {
      Root = L;
    }
    else if(L->Key < Parent->Key)
    {
      Parent->Left = L;
    }
    else
    {
       Parent->Right = L;
    }
    if((N->Left != nullptr) && (N->Right != nullptr)) 
    {
	   N->Height = 1 + max(N->Left->Height,N->Right->Height);
      
    }
    else if((N->Left == nullptr) && (N->Right == nullptr))
    {
       N->Height = 0;
    }
    else if(N->Right == nullptr)
    {
      N->Height = N->Left->Height + 1;
    }
    else
    {
		N->Height = N->Right->Height + 1;
    }
    if((L->Left != nullptr) && (L->Right != nullptr))
    {
	   L->Height = 1 + max(L->Left->Height,L->Right->Height);
      
    }
    else if((N->Left == nullptr) && (N->Right == nullptr))
    {
	   L->Height = 0;
    }
    else if(L->Right == nullptr)
    {
       L->Height = L->Left->Height + 1;
    }
    else
    {
        L->Height = L->Right->Height + 1;
    }
  } // end LeftRotate
	

	// Destructor helper function...
  void _destroy(NODE* cur)
  {
    if(cur == nullptr){
	  return;
	}
	else{
	  _destroy(cur->Left);
	  _destroy(cur->Right); // Post-Order Traversal...
	  delete cur;
	}
  } // end destroy...

/////
//
//PUBLIC FUNTIONS DEFINED BELOW...
//
///////
public:
  //
  // initializer
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  } // end initializer..

  //
  // copy constructor:
  // calls to copytree in private...
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  } // end copy constructor
	
  // destructor allows for the proper memory deallocation...
  virtual ~avltree()
  {
		NODE* cur = Root;
		_destroy(cur);
		
  }// end destructor....

  // 
  // size
  //
  int size()
  {
    return Size;
  }// end Size...

  //
  // height
  //
  // 
  //
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  } // end height...

  //
  //clear 
  //
  void clear()
  {
		NODE* cur = Root;
		_destroy(cur);
		
		Root = nullptr; // resetting the Root...
		Size = 0;	// reinitializing size...
   } // end clear..


  // 
  // search:
  //
  // 
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
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
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;
	NODE* parent = nullptr;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      nodes.push(cur);  // stack so we can return later:

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
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    // 
    // 4. update size:
    //
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodes.empty())
    {
      cur = nodes.top();
      nodes.pop();
	  if(!nodes.empty())
	  {
		  parent = nodes.top();
	  }
	  else
	  {
		  parent = nullptr;
	  }
      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
	  if(std::abs(hL-hR) > 1){
		  _RotateToFix(parent,cur);
	  }
	  else
	  {
		  
	  
      int hCur = 1 + std::max(hL, hR);
			  

      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;
	  }
    }//while

    //
    // done!
    //
    return;
  }
	

  // function purposed for the distance function
  // accepts the two relevant keys and searchs for a common
  // ancestor amongst them and returning it for use in distance..
  NODE* findAncestor(NODE* anc, TKey k1, TKey k2)
  {
        anc = Root;
        
        while (anc != nullptr)
        {
            if (anc->Key > k1 && anc->Key > k2) // not found, search left...
            {
                anc = anc->Left;
            }
            else if (anc->Key < k1 && anc->Key < k2) // not found, search right...
            {
                anc = anc->Right;
            }
            else
            {
                break; // there exists no common ancestor, break...
            }
        }
        return anc; // ancestor found! return it!...
   } // end findAncestor...

//
// distance
// function utilizes the aforementioned findAncestor function
// and creates two nodes to trickle down and find either key in
// question, using a counter the entire way. distance traveled
// by the two nodes added together and returned for total distance...
int distance(TKey k1,TKey k2)
  {
	if(Root == nullptr) // failsafe function...
	{
		return -1;
	}
	if(search(k1) == nullptr || search(k2) == nullptr) // do k1 and k2 exist?...
	{
		return -1;
	}
	NODE* anc = nullptr; // declare the Node to hold ancestor...


	 anc = findAncestor(anc,k1,k2); // find the ancestor of k1 and k2...
	NODE* r = anc; // traversal node 1...
	NODE* l = anc; // traversal node 2...
	int i = 0; // counter 1...
	int j = 0; // counter 2...
	while(r->Key != k1)
	{
		if(r->Key > k1) // k1 is smaller
		{

			r = r->Left; // move left

		}
		else // k1 is larger
		{

			r = r->Right; // move right
			
		}
		i++; // increment counter		
	}

	while(l->Key != k2)
	{
		if(l->Key > k2) // k2 is smaller
		{

			l = l->Left; // move left

		}
		else // k2 is larger...
		{

			l = l->Right; // move left...
			
		}
		j++; // increment counter...	
	}
	if(k1 == k2) // looking for the same key twice, return zero...
	{
		return 0;
	}
	int result = i + j; // result holds the total distance...
	return result;

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
  } // end inorder...

  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  } // end inorder_keys...

  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  } // end inorder_values...

  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  } // end inorder_heights...


}; // end class definition...

