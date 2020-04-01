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
	std::cout<<"Usage: simulator [-C <bench_path>] [-I <input_path>] [-T <num_threads>]\n";
	return 0;
}


int netlist_stats(int file_lines, int NAND, int AND, int OR,int NOR,int NOT,int BUFF,int INPUT,int OUTPUT){
	std::cout<<"\n";		
	std::cout<<"---- Netlist Stats ----\n";
	std::cout<<"- NAND: "<<NAND<<"\n";
	std::cout<<"- AND: "<<AND<<"\n";
	std::cout<<"- NOR: "<<NOR<<"\n";
	std::cout<<"- OR: "<<OR<<"\n";
	std::cout<<"- NOT: "<<NOT<<"\n";
	std::cout<<"- INPUT: "<<INPUT<<"\n";
	std::cout<<"- OUTPUT: "<<OUTPUT<<"\n";
	std::cout<<"- BUFF: "<<BUFF<<"\n";
	std::cout<<"-----------------------\n";
	return 0;
}

//Returns the edges when given a line
std::vector<std::string> get_edge(std::string line){


	int pos1 = line.find("(");
	int pos2 = line.find(",");
	int pos3 = line.find(")");
	
	//To be returned
	std::vector<std::string> Edge_V;

				
    if(pos2 == -1){
    	//Input,output,buff,not 
			pos1++;
			pos2++;
			pos3++;
	
			std::cout<<line.substr(pos1,pos3-pos1-1)<<std::endl;

		//	Edge_V.push_back();
	
    }else{
		//AND,NAND,OR,NOR
		//But there could be 3 input gates so this must be checked as well								
		pos1++;
		pos2++;
		pos3++;


			
    }
		
	return Edge_V;
}


int main(int argc, char *argv[]){
		
	// Opens the input file
 	std::ifstream bench_file;
	std::ifstream input_file;

	//User Arguments
	std::string file_path;
	std::string input_path;
	
	//Argument handling
	if(argc == 1){
		print_usage();
		return -1;
	}else if(argc == 2){
		print_usage();
		return -1;	
	}else if(argc == 3){		

		if((std::string)argv[1] == "-C"){
			file_path = argv[2];
		}
		else if((std::string)argv[1] == "-I"){
			input_path = argv[2];
		}
		else if((std::string)argv[1] == "-T"){
			std::cout<<"Not Implemented yet!"<<std::endl;
			return -1;
		}

	//Any other number of arguments
	}else{
		
		std::cout<<"Wrong Usage!"<<std::endl;
		print_usage();
		return -1;	
	}

  
  //INPUT FILE
  bench_file.open(file_path);

  //Initialization
  std::stringstream stream; //for "prints"

  //Declare file for algorithm1 output
  std::ofstream myfile1;

  //Output file
  myfile1.open ("output");

  std::string current_line;
	
	//Bench File Vector	
	std::vector<std::string> Lines;
	std::vector<std::string> NAND_V;
	std::vector<std::string> AND_V;
	std::vector<std::string> NOR_V;
	std::vector<std::string> OR_V;
	std::vector<std::string> NOT_V;
	std::vector<std::string> INPUT_V;
	std::vector<std::string> OUTPUT_V;
	std::vector<int> BUFF_V;

  //File opening
  if (!bench_file) {
    std::cout << "Error Opening Bench File" << std::endl;
		print_usage();
    return -1;
  }
  else{
    while(std::getline(bench_file, current_line)){
      Lines.push_back(current_line);
    }
  }
	

	int index = 0;
	int INPUT=0;
	int OUTPUT=0;
	int NAND=0;
	int AND=0;
	int BUFF=0;
	int OR=0;
	int NOR=0;
	int NOT=0;

 //Process file
	for(auto& line : Lines){
		
		//Remove whitespace
		line.erase(remove(line.begin(),line.end(),' '),line.end());
		line.erase(remove(line.begin(),line.end(),'\t'),line.end());

		//Ignore Comments
		if(line[0] == '#'){
		}
		//Ignore empty lines
		else if(line.empty() == 1){
		}			
		//Process Line
		else{
		
			//Print Line for debugging									
			std::cout<<line<<std::endl;

			//Add line
			Lines[index] = line;	

			if(line.substr(0,5) == "INPUT"){
				//std::cout<<line.substr(0,5)<<std::endl;
				INPUT++;


				get_edge(line);
			}


			
			//Check if OUTPUT
			else if(line.substr(0,6) == "OUTPUT"){
				
				//std::cout<<line.substr(0,6)<<std::endl;
				OUTPUT++;

			}
			//Gates
			else{
	
				int pos = line.find("=");
					
				pos++;

				//Check if NAND
				if(line.substr(pos,4) == "NAND"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					NAND++;
				}

				//Check if AND
				if(line.substr(pos,3) == "AND"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					AND++;
				}
			
				//Check if NOR
				if(line.substr(pos,3) == "NOR"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOR++;
				}

				//Check if OR
				if(line.substr(pos,2) == "OR"){
				
					//std::cout<<line.substr(pos,2)<<std::endl;
					OR++;

				}

				//Check ig BUFF
				if(line.substr(pos,4) == "BUFF"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					BUFF++;
				}


				//Check if NOT
				if(line.substr(pos,3) == "NOT"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOT++;

				}
			}
		}

		index++;
	}


netlist_stats(index,NAND,AND,OR,NOR,NOT,BUFF,INPUT,OUTPUT);


return 0;
}
