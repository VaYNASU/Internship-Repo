// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph. 


#include "Map.h"

using namespace std;

void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance);

int main()
{
    //Maximum possible sites and route number
    const int MAX_SITE_NUM = 50, MAX_ROUTE_NUM = 100;
    int numOfSites = 0, numOfRoutes = 0;  //counter used to track actual number of sites and routes


   //create an array of Site which store all Sites (vertex of the graph)
   //----
   Site array_of_sites[MAX_SITE_NUM];

   //create an array of Route which store all Routes (edges of the graph)
   //----
   Route array_of_routes[MAX_ROUTE_NUM];

   string oneLine;

   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line from the input, extract the first token
      //create a Site object if it does not exist in site array,
      //insert it inside the site array. This will be first point of the 'aNewRoute'
      //----
      //----
      string delimiter = ",";
      int comma_position = oneLine.find(delimiter);

      string departure_site = oneLine.substr(0,comma_position);

      //extract the arrival site info. check whether it exists in
      //site array or not, if not, create a new Site object, add it inside.
      //This site will be the second point of the 'aNewRoute'
      //----
      //----

      int departure_site_index = -1; //this is used to check to see if the departure site even exists in the array.

      int index = 0; //this is used to go through the loop.

      while(index < numOfSites){

         if(array_of_sites[index].siteName == departure_site){ //this checks to see if the departure site exists or not.

            departure_site_index = index; //this sets the departure site index to index if it does exist.
            break;
         }

         index++; //this just increments index.
      }

      if(departure_site_index == -1){ //this checks to see if a site has to be created.

         array_of_sites[numOfSites] = Site(departure_site); //this creates a new site.
         departure_site_index = numOfSites; //this sets the departure site's index to the number of sites. 
         numOfSites++; //this increments the number of sites.
      }



      //by using the two sites we got above, create a new route, add
      //it inside route array
      //----
      //----
      string new_site = oneLine.substr(comma_position + 1); //this extracts waht is after the comma. 
      int start_position = 0;
      int end_position = 0;

      while((end_position = new_site.find(delimiter,start_position)) != -1){

         string site_token = new_site.substr(start_position,end_position-start_position); //this extract what is between the start posistion and before the end positoin.
         string arrival_site_name;

         double distance;
         getArrSiteInfo(site_token,arrival_site_name,distance); //this gets the arrival site info.

         if(arrival_site_name.empty()){ //this checks to see if get info function come up as empty.

            start_position = end_position + 1; //this sets the start position to whatever is after the end posistion. 
            continue;
         }

         int arrival_site_index = -1;

         int index = 0; //this is used to go through the loop.

         while(index < numOfSites){

            if(array_of_sites[index].siteName == arrival_site_name){ //this checks to see if the arrival site exists or not.

               arrival_site_index = index; //this sets the arrival site index to index if it does exist.
               break;
            }

            index++; //this just increments index.
         }


         if(arrival_site_index == -1){ //this checks to see if a site has to be created.

            array_of_sites[numOfSites] = Site(arrival_site_name); //this creates a new site.
            arrival_site_index = numOfSites; //this sets the arrival site's index to the number of sites. 
            numOfSites++; //this increments the number of sites.
         }
         


         array_of_routes[numOfRoutes] = Route(&array_of_sites[departure_site_index], &array_of_sites[arrival_site_index], distance); //this creates the route and adds that to the array.
         numOfRoutes++; //this increments the number of routes.

         start_position = end_position + 1; //this sets the start position to whatever is right after the comma.

      }


      string site_token = new_site.substr(start_position);
      
      if(!site_token.empty()){

         double distance;
         string arrival_site_name;
         
         getArrSiteInfo(site_token,arrival_site_name,distance); //this gets the arrival site info.


         int arrival_site_index = -1;

         int index = 0; //this is used to go through the loop.

         while(index < numOfSites){

            if(array_of_sites[index].siteName == arrival_site_name){ //this checks to see if the arrival site exists or not.

               arrival_site_index = index; //this sets the arrival site index to index if it does exist.
               break;
            }

            index++; //this just increments index.
         }


         if(arrival_site_index == -1){ //this checks to see if a site has to be created.

            array_of_sites[numOfSites] = Site(arrival_site_name); //this creates a new site.
            arrival_site_index = numOfSites; //this sets the arrival site's index to the number of sites. 
            numOfSites++; //this increments the number of sites.
         }
         


         array_of_routes[numOfRoutes] = Route(&array_of_sites[departure_site_index], &array_of_sites[arrival_site_index], distance); //this creates the route and adds that to the array.
         numOfRoutes++; //this increments the number of routes.

         
      }
      
      //get next line
      getline(cin, oneLine);

   } //repeat until the 'End'

   //Create a Map object by using site array and route array
   //----
   Map site_map(numOfSites,numOfRoutes,array_of_sites,array_of_routes); //this creates the map.
   
   cout << "Total historical sites you will visit: " << numOfSites << endl;

   //Run Kruskal MST algorithm on above map
   //----
   site_map.MST_Kruskal(); //this runs the algorithm.

}

//****************************************************************
//By giving a string, for example 'Pantheon(300.5)', this function
//extract the arrival site name 'Pantheon' and distance '300.5' meters
//****************************************************************
void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance)
{
   //----
   //----

   oneArrSiteInfo.erase(0,oneArrSiteInfo.find_first_not_of(" ")); //this trims off the lead spaces. 
   oneArrSiteInfo.erase(oneArrSiteInfo.find_last_not_of(" ") + 1); //this trims off the trail spaces. 

   if(oneArrSiteInfo.empty()){ //this checks to see if the string is empty.

      arrSiteName = "";
      distance = 0.0;
      return;
   }

   int left_parenthesis_location = (int)oneArrSiteInfo.find("("); //this gets the location of the left parenthesis if its there.
   int right_parenthesis_location = (int)oneArrSiteInfo.find(")"); //this gets the location of the right parenthesis if its there.


   if(left_parenthesis_location == -1 || right_parenthesis_location == -1){ //this checks to see if the parenethesis even exist or not. 

      arrSiteName = "";
      distance = 0.0;
      return;
   }


   arrSiteName = oneArrSiteInfo.substr(0,left_parenthesis_location); //this extracts the left parenthesis. 
   string distance_parenthesis = oneArrSiteInfo.substr(left_parenthesis_location + 1,right_parenthesis_location - left_parenthesis_location - 1); //this just extracts what is inside the parenthesis.
   
   
   distance_parenthesis.erase(0,distance_parenthesis.find_first_not_of(" ")); //this trims off the lead spaces. 
   distance_parenthesis.erase(distance_parenthesis.find_last_not_of(" ") + 1); //this trims off the trail spaces. 
   
   if(distance_parenthesis.empty()){ //this checks to see if the distance is empty or not. 
      
      arrSiteName = "";
      distance = 0.0;
      return;
   }


   distance = stod(distance_parenthesis); //this converts what was in between the parenthesis into a double so it can be printed.
   
}

