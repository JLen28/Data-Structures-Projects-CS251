/*

void clear()
  {
		NODE* cur = Root;
		_destroy(cur);
		
		Root = nullptr;
		Size = 0;	
   }


	
  virtual ~avltree()
  {
		NODE* cur = Root;
		_destroy(cur);
		
   }		
		
		
  void _destroy(NODE* cur)
  {
    if(cur == nullptr){
	  return;
	}
	else{
	  _destroy(cur->Left);
	  _destroy(cur->Right);
	  delete cur;
	}
  }
  
  
  
 
   void _RotateToFix(NODE* Parent, NODE* N)
   {
		assert(N != nullptr);
		
      int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
      int hR = (N->Right == nullptr) ? -1 : N->Right->Height;
		
		assert(std::abs(hL-hR) > 1);
			
		if(hL > hR) // cases 1 or 2 
		{
			if(N->Left->Left != nullptr)  // case 1..
			{
				//_LeftRotate(N,N->Left);
				_RightRotate(Parent,N);
			}
			else  // case 2...
			{
			     // _LeftRotate(N,N->Left);
				 // _RightRotate(Parent,N);
			}
		}
		else // cases 3 or 4
		{
			if(N->Right->Left->Height > 1)
			{
				//_RightRotate(N,N->Right);
				//_LeftRotate(Parent,N);
			}
			else
			{
				
				//_LeftRotate(Parent,N);
			}
			
		}
  }	