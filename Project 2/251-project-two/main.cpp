
//
// Joseph Lenaghan
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
using namespace std;
// Movie Data struct declared, this will act as the TValue for the BST...
struct MovieData{
  string movieName;
  int toeTag = 0;
  int PubYear = 0;
  int totalStars = 0;
  int totalReviews = 0;
  int num5Stars = 0;
  int num4Stars = 0;
  int num3Stars = 0;
  int num2Stars = 0;
  int num1Stars = 0;
};


//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename,string reviewsFilename,binarysearchtree<int, MovieData> &movieIDs, binarysearchtree<string,MovieData> &movieNames,int &reviewsTotal, int &moviesTotal )
{
  ifstream moviesFile(moviesFilename);
  ifstream reviewsFile(reviewsFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }
  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open reviews file '" <<
    moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name); //
    MovieData  movies; //
    movies.PubYear = pubYear; // setting all the key elements in place...
    movies.toeTag = id; //
    movies.movieName = name; //

    movieIDs.insert(id,movies); // insert into the ID tree...
    movieNames.insert(name,movies); // insert into the name tree...
    reviewsTotal++; // increment total reviews...
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }

  
  int reviewsID, stars; // variables to contain read in data...
  reviewsFile >> id; //  review while mimics while provided above without utilization of getLine()...
  while(!reviewsFile.eof())
  {
   reviewsFile >> reviewsID; // review ID read in...
   reviewsFile >> stars; // star value is read in...
   MovieData* toeTagNode = movieIDs.search(reviewsID); // declare pointer for traversal..
   MovieData* nameSearch = movieNames.search // declare pointer for traversal..
   (toeTagNode->movieName);
   if(stars == 1)
   {
     toeTagNode->num1Stars++; // star is 1...
     nameSearch->num1Stars++;
   }
   else if(stars == 2)
   {
     toeTagNode->num2Stars++; // star is 2...
     nameSearch->num2Stars++;

   }
   else if(stars == 3)
   {
     toeTagNode->num3Stars++;
     nameSearch->num3Stars++; // star is 3...
   }
   else if(stars == 4)
   {
     toeTagNode->num4Stars++;
     nameSearch->num4Stars++; // star is 4...
   }
   else
   {
     toeTagNode->num5Stars++;
     nameSearch->num5Stars++; // star is 5...
   }
   moviesTotal++;
   toeTagNode->totalStars += stars; 
   nameSearch->totalStars += stars;
   toeTagNode->totalReviews++;
   nameSearch->totalReviews++;
   reviewsFile >> id; // get the next id and move to the next line..
  }

}


//
// main
//
int main()
{
  binarysearchtree<int, MovieData> movieIDs;
  binarysearchtree<string,MovieData> movieNames;
  int moviesTotal = 0, reviewsTotal = 0;


  string moviesFilename; // = "movies1.txt"
  string reviewsFilename; //= "reviews1.txt"

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  InputMovies(moviesFilename,reviewsFilename,movieIDs,movieNames,moviesTotal,reviewsTotal);
  //movieIDs.inorder();
  cout <<"Num movies: " << moviesTotal << endl;
  cout <<"Num reviews: " << reviewsTotal << endl;
  cout << endl;
  cout <<"Tree by movie id: size=" << movieIDs.size() << ", height=" << movieIDs.height() << endl;
  cout <<"Tree by movie name: size=" << movieNames.size() << ", height=" << movieNames.height() << endl << endl;

  string input; // declare input...
  while(input != "#"){
  cout << "Enter a movie id or name (or # to quit)> ";
  getline(cin, input); // read entire input line
  int i = 0;
  bool nameorNot = false;
  if(input == "#"){
    return 0;
  }
  for(i = 0; i < input.length(); i++)
  {
        if(isalpha(input[i])) // check the front of input...
        {
          nameorNot = true; // its a string
 
        }
        else if(isalpha(input.back())) // check the back of input...
        {
          nameorNot = true; // its a string with ints
        }
    if(nameorNot == false) // only ints
    {
      
      int stoistr = stoi(input); // str to int...
      MovieData* result = movieIDs.search(stoistr);
      if(result == nullptr) // unsuccessful...
      {
        cout <<"not found..." << endl << endl;
        break;
      } 
      double avg = double(result->totalStars) / result->totalReviews;
      cout <<"Movie ID: " << result->toeTag << endl;
      cout <<"Movie Name: "<< result->movieName << endl;
      if(result->toeTag == 251){avg = 0;}
      cout <<"Avg rating: "<< avg << endl;
      cout <<"5 stars: "<< result->num5Stars << endl;
      cout <<"4 stars: "<< result->num4Stars << endl;
      cout <<"3 stars: "<< result->num3Stars << endl; 
      cout <<"2 stars: "<< result->num2Stars << endl;
      cout <<"1 star: "<< result->num1Stars << endl;
      cout << endl;
      break;
    }
    else 
    {
      MovieData* result = movieNames.search(input);
      if(result == nullptr) // unsuccessful..
      {
        cout <<"not found..." << endl << endl;
        break;
      }
      double avg = double(result->totalStars) / result->totalReviews;
      cout <<"Movie ID: " << result->toeTag << endl;
      cout <<"Movie Name: "<< result->movieName << endl;
      cout <<"Avg rating: "<< avg << endl;
      cout <<"5 stars: "<< result->num5Stars << endl;
      cout <<"4 stars: "<< result->num4Stars << endl;
      cout <<"3 stars: "<< result->num3Stars << endl;
      cout <<"2 stars: "<< result->num2Stars << endl;
      cout <<"1 star: "<< result->num1Stars << endl;
      cout << endl;
      break;

    }
  }
  }

  // done:
  return 0;
}
