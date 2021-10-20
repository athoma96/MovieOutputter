//
// Project 3 Part 3: C++ program to work with Netflix movie data as it takes the user input files  
// Outputs movies according to its movie Id, tile, and year.
// 
// Author: Allen Thomas, University of Illinois Chicago, Fall 2020
// 
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

struct Movie       // Struct with its list of variables 
{
   int movieId;
   int year ;
   string title;
   int reviewId;
   int movieId2;
   int rating;
   int Num5StarReviews;
   double totalReview;
   double average;
};

// Function to read the movies file and store its data in the struct array

void readMovies(string filename, Movie* movies)
{

   string firstLine,secLine;   
   int numMovies, movieId, year;
   string title;
   int size = 0;
  
   ifstream infile(filename);    // Opens to read the file 

   if(!infile.good()) {
       cout << "Unable to open file " << endl;
       
   }
   
   getline(infile,firstLine);   //Takes out the first line in the file
   infile >> secLine;
   infile >> numMovies;
   cout << "**Number_Movies: " << numMovies << endl; 
   
   
   while (!infile.eof())  // while program goes through the end of file, it gets the movie id, title, and year
{
   infile >> movieId;
   infile >> year;
   getline(infile,title);  

   if (!infile.fail())  // data was successfully input:
   {
       
       movies[size].movieId = movieId;
       movies[size].year = year;
       movies[size].title = title;
       size++;  
   }
}  
   
}


// Function to read the reviews file and to store the number of reviews each movie has

void readReviews(string Reviewfile, Movie* movies, int N)
{

   string frLine,srLine;
   int numReviews, movieId2, reviewId, rating;
  
   ifstream infile1(Reviewfile);    // Opens to read the file 

   if(!infile1.good()) {
       cout << "Unable to open file " << endl;
   }
   
   getline(infile1,frLine);   // Takes out the first line in the file
   infile1 >> srLine;
   infile1 >> numReviews;
   cout << "**Number_Reviews: " << numReviews << endl; 
   
   for(int i = 0; i < N; i++ ) {   // Loop which sets avg, rating, and reviews initially to 0 for movies which no reviews and ratings
       movies[i].average = 0;
       movies[i].rating  = 0;
       movies[i].totalReview = 0;  
       movies[i].Num5StarReviews = 0;
   }
   while (!infile1.eof())
    {
       string ID;
       
        infile1 >> reviewId;
        infile1 >> movieId2;
        infile1 >> rating;

   
     if (!infile1.fail())  // data was successfully input:
     {
        for(int i = 0; i < N; i++)
		{
			if(movieId2 == movies[i].movieId)
			{ // checks to see if the movie id in review file is equal to the one in movie
				movies[i].totalReview ++;  // increments thyoughout the loop to find the total number of reviews for each movie   
				movies[i].rating += rating;  // Adds 1 to the rating each time 
                if(rating == 5)
				{
					movies[i].Num5StarReviews ++;
                }
            }
         }
     }
    }
    
   
   
    
        for(int i = 0; i < N; i++) {   // Loops through the number of movies and finds the average of each movie
           if(movies[i].totalReview != 0){
               movies[i].average = movies[i].rating / movies[i].totalReview;
           }  
        }   
     
}   
   
// Function to sort the movies by ID
void sortById(Movie* movies, int N) {   // Uses selection sort
    int smallInd;
    
    for(int i = 0; i < N-1; i++ ) {    // Finds index of the smallest remaining element
        smallInd = i;
        for(int j = i+1; j < N; j++) {
            if(movies[j].movieId < movies[smallInd].movieId) {
                smallInd = j;
            }
        }
                if (smallInd != i)
      {
         Movie  temp;

         temp = movies[i];
         movies[i] = movies[smallInd];
         movies[smallInd] = temp;
      }
   }
   
}
       

// Function to sort the movies by their titles

void sortByTitle(Movie* movies, int N) {
    int smallInd;
    
    for(int i = 0; i < N-1; ++i) {   // Finds index of the smallest remaining element
        smallInd = i;
        for(int j = i+1; j < N; ++j) {
            if((movies[j].title) < (movies[smallInd].title)) {
                smallInd = j;
            }
        }
           
        if (smallInd != i)
      {
         Movie  temp;

         temp = movies[i];
         movies[i] = movies[smallInd];
         movies[smallInd] = temp;
      }
   }
   
}
    
    

//Function to check if the input is an integer

bool isNumber(string s)
{
    for (unsigned int i = 0; i < s.length(); i++){
        if (isdigit(s[i]) == false) {
            return false;
        }
    }
 
    return true;
}

// Function to search the user input in the array by movieId and output it

int searchByid(Movie* movies, int N, string s) {
    for(int i = 0; i < N; i++ ) {
            if(stoi(s) == movies[i].movieId ) {  // converts the string into int then checks if it similar to any movie id in the file
                cout << movies[i].movieId << " " << movies[i].year << " " << "'" << movies[i].title.substr(1) << "'" << " "
                 << movies[i].totalReview << " reviews" << " " << movies[i].average << " avg rating" << " (" << movies[i].Num5StarReviews << ")" << endl;
                return 0;
            }
        }
    return -1;
}


//Function to search the user input in the array by the movie title and output it

int searchByTitle(Movie* movies, int N, string s) {
    int count = 0;
    for(int i = 0; i < N; i++) {
            int pos = movies[i].title.find(s); // Uses the find function to see if the substring is in any movie title
            if( pos > -1) {
                cout << movies[i].movieId << " " << movies[i].year << " " << "'" << movies[i].title.substr(1) << "'" << " "
                  << movies[i].totalReview << " reviews" << " " << movies[i].average << " avg rating" << " (" << movies[i].Num5StarReviews << ")" << endl;
                count ++;
            }
    }
    if(count == 0){
        return -1;
    }
    else{
        return 0;
    }
}



// Function to find the most popular movie(Highest Avg Rating)

int findMp(Movie* movies, int N) { 
   double Avg = 0;
   double calcAvg;
   int index = 0;
    
    for(int i = 0; i < N; i++) {
     calcAvg = movies[i].rating / movies[i].totalReview;
       if(calcAvg > Avg) {
          Avg = calcAvg;
          index = i;
       }
}
    cout << movies[index].movieId << " " << movies[index].year << " " << "'" << movies[index].title.substr(1) << "'" << " "
    << movies[index].totalReview << " reviews" << " " << movies[index].average << " avg rating" << " (" << movies[index].Num5StarReviews << ")" << endl;
     
    return index;
}

int main()
{
   string firstLine, secLine, frLine, srLine;
   int numMovies;
   string filename, Reviewfile;
   int N;
   string key;
 
   cout << "Movies filename> ";
   cin >> filename;
   
   cout << "Reviews filename> ";
   cin >> Reviewfile;
    

   ifstream infile(filename);  // opens to read the file again
   getline(infile,firstLine);
   infile >> secLine;
   infile >> numMovies; // Stores the number of movies in the file
   N = numMovies;  
     
   Movie* movies;  
   movies = new Movie[N];   // Allocates the struct array with number of movies
    
   // calls in the functions created
   readMovies(filename, movies);  
   readReviews(Reviewfile, movies, N);
    
   string A;
       
   while(key != "q") {   // loops until the user inputs "q"
       
   cout << "\n" << "Enter command (f id, f title, l, mp, q): ";
   cin >> key; // Takes the user input for different commands
       
       if (key[0] == 'f') {  
           cin >> A;
           
           if(isNumber(A)) {   // uses the bool function created to check for number
               int ans = searchByid(movies, N, A);
               if (ans == -1){   // if the user inputs movie id which is not in the file 
                   cout<<"Movie not found..."<<endl;
               }
           }
           
           else {     
              sortByTitle(movies, N);
              int ans = searchByTitle(movies, N, A);
              if (ans == -1){   // if the user inputs movie title which is not in the file 
                   cout<<"Movie not found..."<<endl;
               }
           }     
       }
 
     else if (key == "l") // prints out the whole list of movies sorted by id and title
     {
       sortById(movies, N);
       cout << "**MOVIES BY ID**" << endl;
   
      for(int i=0; i < N; i++){
        cout << movies[i].movieId << " " << movies[i].year << " " << "'" << movies[i].title.substr(1) << "'" << " "
           << movies[i].totalReview << " reviews" << " " << movies[i].average << " avg rating" << " (" << movies[i].Num5StarReviews << ")" << endl;
   }
    
   sortByTitle(movies, N);
   cout << "**MOVIES BY TITLE**" << endl;
   for(int t=0; t < N; t++){
        cout << movies[t].movieId << " " << movies[t].year << " " << "'" << movies[t].title.substr(1) << "'" << " " 
            << movies[t].totalReview << " reviews" << " " << movies[t].average << " avg rating" <<  " (" << movies[t].Num5StarReviews << ")" << endl;
   }
    
       }
       
      else if (key == "mp") {  // if the user inputs to find the most popular movie
          findMp(movies, N);
      }
      else if (key == "q") {  // To end the loop when the user is done
          cout << "**Done**" << endl;
       delete[] movies;
       return 0;
   }
   }
    
    
   
   delete[] movies; // deletes the memory
   return 0;
}
