#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <chrono>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <set>


int print_usage(){




	return 0;
}


//Main Function
int main(int argc, char *argv[]){

  // Opens the input file
  std::ifstream myfile;

  //Get first argument as input
  std::string argument = argv[1];

  //INPUT FILE
  myfile.open(argument);

  //Initialization
  std::stringstream stream; //for "prints"

  //Declare file for algorithm1 output
  std::ofstream myfile1;

  //Output file
  myfile1.open ("output");

  std::string current_line;
	
	std::vector<std::string> Lines;

  //File opening
  if (!myfile) {
    std::cout << "Error Opening File" << std::endl;
		print_usage();
    return -1;
  }
  else{
    while(std::getline(myfile, current_line)){
      Lines.push_back(current_line);
    }
  }

 //Process file
 for(auto& line : Lines){


	}


return 0;


}
