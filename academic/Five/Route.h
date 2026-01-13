#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Site represents one vertex of the map
struct Site
{
    string siteName;
    int rank;
    struct Site* parent;

   //C++ doesn't provide a default constructor, need it here.
   Site()
   {
        //----
        //----
      this->siteName = ""; //this just sets an empty site name by default. 
      this->parent = this; //this sets the parent back to itself because it is the only element in the set.
      this->rank = 0; //this just simply sets the rank to 0. 

   }

   //overloaded constructor
   Site(string name)
   {
      //----
      //----
      this->siteName= name; //this just sets the site name as the name that is passed to the constructor.
      this->parent = this; //this sets the parent back to itself because it starts off as the only element in the set. 
      this->rank = 0; //this just simply sets the rank to 0. 

   }
};

//Route represents one edge of the map which connects two historical sites of Rome
class Route
{
    private:
       struct Site* site1;
       struct Site* site2;
       double distance;

	public:
	   Route();
       Route(Site* site1, Site* site2, double distance);
       Site* getSite1();
       Site* getSite2();
       double getDistance();
       void printRoute();
};

//finish each function according to above definition
//----
//----

Route::Route(){ //this is the default constructor. 

   this->site1 = nullptr; //this just sets an empty pointer for site 1.
   this->site2 = nullptr; //this just sets an empty pointer for site 2.
   this->distance = 0.0; //this sets the default distance as 0. 
}

Route::Route(Site* site1, Site* site2, double distance){ //this is the overloaded constructor.

   this->site1 = site1; //this just sets site 1 as the site 1 that was passed into the construcotr. 
   this->site2 = site2; //this just sets site 2 as the site 2 that was passed into the constructor. 
   this->distance = distance; //this sets distance as the distance passed into the constructor. 
}


Site* Route::getSite1(){ //this just gets site 1. 

   return site1; //this  simply just returns the site 1.
}


Site* Route::getSite2(){ //this just gets site 2.

   return site2; //this simply just return the site 2.
}


double Route::getDistance(){ //this just gets the distance. 

   return distance; //this just returns the distance. 
}


void Route::printRoute()
{
    cout << left;
    cout << setw(33) << site1->siteName
         << setw(8) << "<--->"
         << setw(33) << site2->siteName
         << setw(3) << " = "
         << setw(8) << right << fixed << setprecision(1) << getDistance()
         << endl;
}

