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
#include <utility>
#include <list> 
#include <stack> 

//If you want verbose output uncomment the following line
//#define VERBOSE


// Prints correct usage
int print_usage(){
	std::cout<<"Usage: simulator [-C <bench_path>] [-I <input_path>] [-T <num_threads>]\n";
	return 0;
}

// Print netlist statistics
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
	std::cout<<"- Total Gates: "<<NAND+AND+NOR+OR+NOT+INPUT+OUTPUT+BUFF<<"\n";
	std::cout<<"-----------------------\n";
	return 0;
}

// Returns the edges when given a line
std::vector<std::string> get_edge(std::string line){


	int pos1 = line.find("(");
	int pos2 = line.find(",");
	int pos3 = line.find(")");
	int pos4 = line.find("=");
	
	//To be returned
	std::vector<std::string> Edge_V;

				
    if(pos2 == -1){
    	//Input,output,buff,not 
			pos1++;
			pos2++;
			pos3++;
			pos4++;	

			//std::cout<<line.substr(pos1,pos3-pos1-1)<<std::endl;

			Edge_V.push_back(line.substr(pos1,pos3-pos1-1));
	
    }else{
			//AND,NAND,OR,NOR
			//But there could be 3 input gates so this must be checked as well								
			pos1++;
			pos2++;
			pos3++;
			pos4++;
		
			//std::cout<<line.substr(pos1,pos3-pos1-1)<<std::endl;
		
			//Tokenize String
			// Vector of string to save tokens 
    	std::vector <std::string> tokens; 
      
    	// stringstream class check1 
    	std::stringstream check1(line.substr(pos1,pos3-pos1-1)); 
      
    	std::string intermediate; 
      
    	// Tokenizing w.r.t. comma ',' 
    	while(getline(check1, intermediate, ',')) 
    	{ 
        tokens.push_back(intermediate); 
    	} 
      
    	// Printing the token vector 
    	for(int i = 0; i < tokens.size(); i++){
        //std::cout << tokens[i] << '\n'; 
				Edge_V.push_back(tokens[i]);
			}
			
    }
		
	//Adding componennt output
	//std::cout<<line.substr(0,pos4-1)<<std::endl;
	//Always the last item is the component output	
	if(pos4 > 0)
		Edge_V.push_back(line.substr(0,pos4-1));
	return Edge_V;
}

// Data that represents a vertex
struct VertexData{
	int component_id;
	std::string component_name;
	std::vector<int> inputs; //multiple inputs
	int output; //one output
};

// A utility function to add an edge in an undirected graph. 
void addEdge(std::vector<int> adj[], int u, int v){ 
    adj[u].push_back(v); 
} 
  
// A utility function to print the adjacency list representation of graph 
void printGraph(std::vector<int> adj[], int V, struct VertexData Vertices_Array[]){ 
    for (int v = 0; v < V; ++v) 
    { 
        std::cout << "\n Adjacency list of vertex "
             << Vertices_Array[v].component_name << " "<<v <<"\n head "; 
        for (auto x : adj[v]){ 
           std::cout << "-> " << Vertices_Array[x].component_name << " " << x ;
				}
        printf("\n"); 
    } 
} 

// Prints all vertices
void printVertexArray(struct VertexData Vertices_Array[], int V){
	
	std::cout	<< "---- Vertices ----\n";

	for (int i = 0; i < V; i++) 
  { 
		std::cout << Vertices_Array[i].component_id << " | " << Vertices_Array[i].component_name << " | " << " in: ";

		//Itterate through inputs
		for(auto& input : Vertices_Array[i].inputs){
			std::cout << input << " ";			
		}
		
		std::cout << " | " << Vertices_Array[i].output << std::endl;

	}
	std::cout	<< "------------------\n";


}

// Adds gate to Vertex Matrix
struct VertexData AddToGraph(std::string line, int index, std::vector<int> adj[], std::string component){

	std::vector<std::string> IO =  get_edge(line);

	struct VertexData temp_vertex;
	
	temp_vertex.component_id = index;
	temp_vertex.component_name = component;
	
	std::vector<int> inputs_vector;

	
	if(component == "INPUT"){

		inputs_vector.push_back(-1);
		temp_vertex.inputs = inputs_vector;
		temp_vertex.output = std::stoi(IO[0]);
	}

	else if(component != "OUTPUT"){
	
		for(int i = 0; i < IO.size() - 1; i++){
			inputs_vector.push_back(std::stoi(IO[i]));
		}

		temp_vertex.inputs = inputs_vector;
		temp_vertex.output = std::stoi(IO.back());

	}
	else{
		
		//OUTPUT case where the output vector is empty
		temp_vertex.inputs.push_back(std::stoi(IO[0]));
		temp_vertex.output = -1;

	}

		//Verbose
		#ifdef VERBOSE
		std::cout << "out: " << temp_vertex.output << std::endl; 

		for(auto& input : temp_vertex.inputs){

			std::cout << "in: " << input << std::endl;

		}
		#endif
	return temp_vertex;

}

// Print Graphviz
void printGraphviz(std::vector<int> adj[], int V, struct VertexData Vertices_Array[]){ 

	std::ofstream myfile;
  myfile.open ("netlist.dot");
	
	myfile << "digraph {\n";

	for(int i = 0; i < V; i++){
		
		struct VertexData vertex = Vertices_Array[i];

		myfile << vertex.component_id << " [label=\""<<vertex.component_name<<" "<<vertex.component_id<<"\",shape=circle];\n";

	}
	
	for (int v = 0; v < V; ++v) 
  { 
    for (auto x : adj[v]){ 
    	myfile << v << " -> " << x << ";\n";
		}
  } 



	myfile << "}\n";
  myfile.close();


}



//Main Function
int main(int argc, char *argv[]){
		
	/*	
	//Graph Test
	int V = 5; 

	//Array that holds the data of each vertex
	struct VertexData Vertices_Array[V];
		
	//Graph has the relationships between nodes
	//Vertices_Array has the data of each node

  std::vector<int> adj[V]; 
  addEdge(adj, 0, 1); 
  addEdge(adj, 0, 4); 
  addEdge(adj, 1, 2); 
  addEdge(adj, 1, 3); 
  addEdge(adj, 1, 4); 
  addEdge(adj, 2, 3); 
  addEdge(adj, 3, 4); 
  //printGraph(adj, V);	
	*/


	
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
	std::vector<std::string> Temp;
	

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
			

	//File preprocessing
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
		else{

			//Add line
			Temp.push_back(line);
		}

	}

	//Cleaned up file
	Lines = Temp;

	//Declare Graph
	int V = Lines.size(); 
	
	//Vertex data 
	struct VertexData Vertices_Array[V];
	
	//Graph datastructure
  std::vector<int> adj[V]; 
	
	//Reinit index		
	index = 0;

 	//Parse clean file
	for(auto& line : Lines){
		
			//Print Line for debugging									
			std::cout<<line<<std::endl;

			if(line.substr(0,5) == "INPUT"){

				//std::cout<<line.substr(0,5)<<std::endl;
				INPUT++;
				
				Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(0,5));
														
			}


			//Check if OUTPUT
			else if(line.substr(0,6) == "OUTPUT"){
				
				//std::cout<<line.substr(0,6)<<std::endl;
				OUTPUT++;
				Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(0,6));

				
			}
			//Gates
			else{
	
				int pos = line.find("=");
					
				pos++;

				//Check if NAND
				if(line.substr(pos,4) == "NAND"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					NAND++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,4));
				

				}

				//Check if AND
				if(line.substr(pos,3) == "AND"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					AND++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,3));


				}
			
				//Check if NOR
				if(line.substr(pos,3) == "NOR"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOR++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,3));


				}

				//Check if OR
				if(line.substr(pos,2) == "OR"){
				
					//std::cout<<line.substr(pos,2)<<std::endl;
					OR++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,2));


				}

				//Check ig BUFF
				if(line.substr(pos,4) == "BUFF"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					BUFF++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,4));


				}


				//Check if NOT
				if(line.substr(pos,3) == "NOT"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOT++;
					Vertices_Array[index] = AddToGraph(line,index,adj,line.substr(pos,3));


				}
			}

		index++;
	}
	
	//Print Netlist Statistics
	#ifdef VERBOSE
	netlist_stats(index,NAND,AND,OR,NOR,NOT,BUFF,INPUT,OUTPUT);
	
	//Print Vertices in stdout
	printVertexArray(Vertices_Array,V);
		
	#endif

	//For each component
	for(auto& vertex : Vertices_Array){
	
		//std::cout <<vertex.component_name << std::endl;
	
		if(vertex.component_name != "INPUT"){		

			//For each component input
			for(auto& input : vertex.inputs){
				
				//Find which components have the input as output
				for(auto& vertexx : Vertices_Array){
					
					if(vertexx.output == input){
						
						addEdge(adj,vertexx.component_id,vertex.component_id);


					}
				}	
			}
		}
	}
	
	#ifdef VERBOSE		
	//Print Netlist
	printGraph(adj,V,Vertices_Array);
	
	//Write Graphviz file
	printGraphviz(adj,V,Vertices_Array);
	
	#endif

return 0;
}
