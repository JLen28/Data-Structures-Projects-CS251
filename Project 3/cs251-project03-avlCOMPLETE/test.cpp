/*test.cpp*/

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) AVL tree with 4 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) empty tree") 
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(3) just one node") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 123);
	REQUIRE(values[0] == 88);
  REQUIRE(heights[0] == 0);
}

TEST_CASE("(4) test case 1 of 4 (insert to left of k1) ")
{
	avltree<int,int> avl;
	
	avl.insert(100,1);
	avl.insert(400,2);
	avl.insert(50,3);
	avl.insert(60,4);
	avl.insert(25,5);
	avl.insert(10,6);
	
	REQUIRE(avl.size() == 6);
	REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

    keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 10 );
	REQUIRE(values[0] == 6);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 25);
	REQUIRE(values[1] == 5);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 50);
	REQUIRE(values[2] == 3);
	REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 60);
	REQUIRE(values[3] == 4);
	REQUIRE(heights[3] == 0);
	
	REQUIRE(keys[4] == 100);
	REQUIRE(values[4] == 1);
	REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 400);
	REQUIRE(values[5] == 2);
	REQUIRE(heights[5] == 0);
	
	
	
	
}

TEST_CASE("(5) test case 4 of 4 (insert to the right of k1)")
{
	avltree<int,int> avl;
	
	avl.insert(100,1);
	avl.insert(50,2);
	avl.insert(200,3);
	avl.insert(150,4);
	avl.insert(300,5);
	avl.insert(400,6);
	
	REQUIRE(avl.size() == 6);
	REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

    keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 50 );
	REQUIRE(values[0] == 2);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 100);
	REQUIRE(values[1] == 1);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 150);
	REQUIRE(values[2] == 4);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 200);
	REQUIRE(values[3] == 3);
	REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[4] == 300);
	REQUIRE(values[4] == 5);
	REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 400);
	REQUIRE(values[5] == 6);
	REQUIRE(heights[5] == 0);
	
	
	
}

TEST_CASE("(6) test case 2 of 4")
{
	avltree<int,int> avl;
	
	avl.insert(600,1);
	avl.insert(700,2);
	avl.insert(500,3);
	avl.insert(525,4);
	avl.insert(550,5);
	avl.insert(540,6);
	avl.insert(560,7);
	avl.insert(570,8);
	
	REQUIRE(avl.size() == 8);
	REQUIRE(avl.height() == 3);
	
	vector<int>  keys, values, heights;

    keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 500 );
	REQUIRE(values[0] == 3);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 525);
	REQUIRE(values[1] == 4);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 540);
	REQUIRE(values[2] == 6);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 550);
	REQUIRE(values[3] == 5);
	REQUIRE(heights[3] == 3);
	
	REQUIRE(keys[4] == 560);
	REQUIRE(values[4] == 7);
	REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 570);
	REQUIRE(values[5] == 8);
	REQUIRE(heights[5] == 0);
	
	REQUIRE(keys[6] == 600);
	REQUIRE(values[6] == 1);
	REQUIRE(heights[6] == 2);
	
	REQUIRE(keys[7] == 700);
	REQUIRE(values[7] == 2);
	REQUIRE(heights[7] == 0);
	
	
	
}
TEST_CASE("(7) test case 3 of 4")
{
	avltree<int,int> avl;
	
	avl.insert(100,1);
	avl.insert(50,2);
	avl.insert(125,3);
	avl.insert(130,4);
	avl.insert(110,5);
	avl.insert(115,6);
	avl.insert(105,7);
	avl.insert(117,8);
	
	REQUIRE(avl.size() == 8);
	REQUIRE(avl.height() == 3);
	
	vector<int>  keys, values, heights;

    keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 50 );
	REQUIRE(values[0] == 2);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 100);
	REQUIRE(values[1] == 1);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 105);
	REQUIRE(values[2] == 7);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 110);
	REQUIRE(values[3] == 5);
	REQUIRE(heights[3] == 3);
	
	REQUIRE(keys[4] == 115);
	REQUIRE(values[4] == 6);
	REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 117);
	REQUIRE(values[5] == 8);
	REQUIRE(heights[5] == 0);
	
	REQUIRE(keys[6] == 125);
	REQUIRE(values[6] == 3);
	REQUIRE(heights[6] == 2);
	
	REQUIRE(keys[7] == 130);
	REQUIRE(values[7] == 4);
	REQUIRE(heights[7] == 0);
	
	
	
}











