// Description: This is the header file that defines an undirected graph
//              with an array of sites and routes
//********************************************************************

#include "Route.h"

using namespace std;

class Map
{
   private:
      int numOfSites, numOfRoutes;
      Site* setOfSites;   //an array of Site. Note: NOT allowed to change it to Site**
      Route* setOfRoutes; //an array of Route. Note: NOT allowed to change it to Route**

   public:
      Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray);
     ~Map();
      void make_set(Site* oneSite);
      Site* find_set(Site* oneSite);
      void link(Site* aSite, Site* bSite);
      void Union(Site* aSite, Site* bSite);
      void sortRoutes();
      void MST_Kruskal();

      //add any auxiliary functions in case you need them
      //----
      void quick_sort(int left_index, int right_index); //this is the helper method for the quick sort algorithm.
      int partition(int left_index, int right_index); //this is the partition for quick sort.
};


//finish each function according to above definition
//----
//----

Map::Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray){

   this->numOfRoutes = numOfRoutes; //this sets the number of routes to what has been passed.
   this->numOfSites = numOfSites; //this sets the number of sites to what has been passed.

   this->setOfSites = siteArray; //this sets the member variable to what siteArray which was passed into. 
   this->setOfRoutes = routeArray; //this sets the member variable to what routeArray which was passed into. 

   int site_index = 0; 

   while(site_index < numOfSites){ //this sets up all the sets. 

      make_set(&setOfSites[site_index]); //this calls make_set so that the set can be created based on the set of sites.
      site_index++; //this just increments the index.
   }


}


Map::~Map(){ //this just sets the arrays to nullptr. 

   setOfSites = nullptr;
   setOfRoutes = nullptr;
}


void Map::make_set(Site* oneSite){

   Site* set_site = oneSite; //this sets set site as oneSite. 

   set_site->parent = set_site; //this makes the set and the first memeber as the parent. 
   set_site->rank = 0; //this sets up the rank at the beginning as 0.
}


Site* Map::find_set(Site* oneSite){

   Site* set_site = oneSite; //this sets set site as oneSite.
    

   if(set_site != set_site->parent){ //this checks to see if the site is not equal to what its parent is. 

      set_site->parent = find_set(set_site->parent); //this then sets the parent to whatever find set returns back with parent passed. 
   }

   return set_site->parent; //this return the  site parent if the set is equal to its parent. 
}


void Map::link(Site* aSite, Site* bSite){

   Site* first_site = aSite; //this sets the first site as aSite.
   Site* second_site = bSite; //this sets the second site as bSite.

   if(first_site->rank > second_site->rank){ //this compares to see if the rank of the first site is bigger than the rank of the second site. 

      second_site->parent = first_site; //this stes the second site's parent as the first site. 
   }else if(first_site->rank < second_site->rank){
      
      first_site->parent = second_site; //this sets the first site's parent to the second site.
   }else{

      second_site->parent = first_site; //this sets teh second site's parent to the first site.
      first_site->rank = first_site->rank + 1; //this increases the first site's rank by 1. 
   }


}


void Map::Union(Site* aSite, Site* bSite){

   Site* first_site = find_set(aSite); //this finds the set of the first site. 
   Site* second_site = find_set(bSite); //this then finds the set of the second site. 

   if(first_site != second_site){ //this checks to see if the first site is the same as the second site or not. 

      link(first_site,second_site); //this then links both sets together cause its union.
   }
}


void Map::quick_sort(int left_index, int right_index){ //this is the quick sort algorithm.

   if(left_index < right_index){ //this compares the left index and the right index. 

      int pivot_index = partition(left_index,right_index); //this sets the pivot index by calling partition.

      quick_sort(left_index, pivot_index - 1); //this calls quicksort on the left side.
      quick_sort(pivot_index + 1, right_index); //this calls quicksort on the right side.
   }
   
}


void Map::sortRoutes(){

   quick_sort(0,numOfRoutes-1); //this calls quick sort by passing in 0 which is at the start index and  number of routes - 1 which is the ending index. 
}



int Map::partition(int left_index, int right_index){

   double pivot_value = setOfRoutes[right_index].getDistance(); //this is literally the pivot value.

   int last_position = left_index - 1; //this is basically the i in parition that is used to swap positions with j if it needs to.

   int partition_index = left_index; //this is pretty much j in partition and is used to check to move in the partition and to see if its less than or equal to the partition value. 

   while(partition_index < right_index){

      if(setOfRoutes[partition_index].getDistance() <= pivot_value){ //this checks to see if the current value is less than or equal to the partition value.

         last_position++; //this increments the last posisiton. 

         Route value_swap = setOfRoutes[last_position]; //this is just a temporary array so that the values can be swapped.

         setOfRoutes[last_position] = setOfRoutes[partition_index]; //this is basically swapping the values of i and j.
         setOfRoutes[partition_index] = value_swap;

      }

      partition_index++; //this increments partition index so that the partition can keep going. 
   }

   Route swap_pivot_value = setOfRoutes[last_position + 1]; //this basically moves the last_position value forward by 1 then it swaps the pivot value with the value its at currently.

   setOfRoutes[last_position + 1] = setOfRoutes[right_index]; 
   setOfRoutes[right_index] = swap_pivot_value;

   return last_position + 1; //this returns the final index of the pivot value.
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Map::MST_Kruskal()
{
   cout << "\nMST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;

   //----
   //----
   //----

   int index = 0;

   while(index < numOfSites){ //this makes the set for every site.

      make_set(&setOfSites[index]); 
      index++; //this just increments index.
   }

   sortRoutes(); //this sorts the edges into nondecreasing order.

   int edge_index = 0;

   while(edge_index < numOfRoutes){ //this goes through each edge in non decreasing order. 

      Site* first_site = setOfRoutes[edge_index].getSite1(); //this gets the route of the first site.
      Site* second_site = setOfRoutes[edge_index].getSite2(); //this gets the route of the second site. 

      if(find_set(first_site) != find_set(second_site)){ //this checks to see if the first and second site are in different sets or not. 

         setOfRoutes[edge_index].printRoute(); //this prints out the route. 
         totalDistance = totalDistance + setOfRoutes[edge_index].getDistance(); //this adds the total distance together. 

         Union(first_site, second_site); //this does the union of both of the sites. 
      }

      edge_index++; //this just increments sort index.
   }


   cout << "=====================================================================================" << endl;
   cout << "Total Distance: " << totalDistance << " meters" << endl;
}
