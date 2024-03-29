#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <chrono>
#include <string>
#include <set>
#include <bitset>
#include <utility>
#include <list> 
#include <stack> 
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <iomanip>

//For printing thread info
std::mutex g_display_mutex;

//For saving thread results
std::mutex g_fault_mutex;

//For saving thread results
std::mutex g_set_mutex;


//Vector with Results (Single Threaded)
std::vector <std::pair<std::vector<int>,std::vector<int>>> Response_Vector_Single;

//Vector with Results (Multithreaded Threaded)
std::vector <std::pair<std::vector<int>,std::vector<int>>> Response_Vector_Multi;


//#define SOFR

//If you want verbose output uncomment the following line
//#define VERBOSE

//If you want G2 graph instead of G1 uncomment the following line
#define G2

//If you want Part B to be enabled uncomment the following line
#define PARTB

//Global Initializations
int time_choice = 2; //default is ms
bool show_time = false;
bool test_given = false;
bool print_stats = false;	
bool argument_flag = false;
bool print_graphviz = false;
bool percentage_bar = false;
int threads = -2;
bool fault_dropping = false;
bool gentest = false;
bool save_faults = false;

//For Parallel Simulation
std::set<std::pair<int,int>> Global_Faults_Set;
std::vector<std::pair<int,int>> Global_Faults_Vector;
std::vector<int> Skipped_Faults_Vector;

//Timer Class for performance evaluation
class Timer{
	public:
	//Start timer
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<float> duration;

	//Constructor
	Timer()
	{
		start = std::chrono::steady_clock::now();
	}

	//Destructor
	~Timer()
	{
		end = std::chrono::steady_clock::now();
		duration = end-start; //duration in seconds
		float ms = duration.count() * 1000.0f;
	}
};

// Prints correct usage
int print_usage(){
	std::cout<<"Usage: simulator [-C <bench_path>] [-I <input_path>] [-T <time>] [-P <number_of_threads>] [-S ] [-G ] [-B ]\n";
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
	//Input/Output Edges
	std::vector<int> inputs; //Edges that are the inputs of said component
	int output; //Edge that is the output of said component
	//Component relationship
	std::vector<int> predecessors; //The ids of the components that are said gate's immediate pred.
	std::vector<int> successors; //The ids of the components that are said gate's immediate succ.
	int paths; //# of paths leading up to this node
	//Simulation
	std::vector<int> input_values; //Boolean 1,0 or 2 = X (for simulation)
	int output_value;	//Boolean 1,0 or 2 = X (for simulation)
	//For Stuck at fault modeling
	std::vector<int> stuck_at_input; //-1 = no fault, 1 = stuck at 1, 0 = suck at 0
	int stuck_at_output;	//-1 = no fault, 1 = stuck at 1, 0 = suck at 0


};

// A utility function to add an edge in a directed graph. 
void addEdge(std::vector<std::vector<int>>& adj, int u, int v){ 
    adj[u].push_back(v); 
} 

// A utility function to delete an edge in a directed graph. 
void deleteEdge(std::vector<std::vector<int>>& adj, int u, int v){ 
	
    //adj[u].push_back(v); 
		int index = 0;
		
		for(auto& entry : adj[u]){
			if(entry == v){
				break;
			}
			index++;
		}

	adj[u].erase(adj[u].begin()+index);
		
} 
   
// A utility function to print the adjacency list representation of graph 
void printGraph(std::vector<std::vector<int>>& adj, std::vector <struct VertexData> Vertices_Vector){ 
    for (int v = 0; v < Vertices_Vector.size(); ++v) 
    { 
        std::cout << "\n Adjacency list of vertex "
             << Vertices_Vector[v].component_name << " "<<v <<"\n head "; 
        for (auto x : adj[v]){ 
           std::cout << "-> " << Vertices_Vector[x].component_name << " " << x ;
				}
        printf("\n"); 
    } 
} 

// Prints all vertices
void printVertexVector(std::vector <struct VertexData> Vertices_Vector){
	
	std::cout	<< "---- Vertices ----\n";

	for (auto& vertex : Vertices_Vector) 
  { 
		std::cout << vertex.component_id << " | " << vertex.component_name << " | " << " in: ";

		//Itterate through inputs
		for(auto& input : vertex.inputs){
			std::cout << input << " ";			
		}
		
		std::cout << " | " << vertex.output << std::endl;

	}
	std::cout	<< "------------------\n";


}

// Adds gate to Vertex Matrix
struct VertexData AddToGraph(std::string line, int index, std::vector<std::vector<int>>& adj, std::string component){

	std::vector<std::string> IO =  get_edge(line);

	struct VertexData temp_vertex;
	
	temp_vertex.component_id = index;
	temp_vertex.component_name = component;
	temp_vertex.paths = 0;	
	temp_vertex.output_value = 0;

	std::vector<int> inputs_vector;

	
	if(component == "INPUT"){

		inputs_vector.push_back(-1);
		temp_vertex.inputs = inputs_vector;
		temp_vertex.output = std::stoi(IO[0]);
		temp_vertex.paths = 1;	
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

	return temp_vertex;

}

// Print Graphviz
void printGraphviz(std::vector<std::vector<int>>& adj, std::vector <struct VertexData> Vertices_Vector){ 

	std::ofstream myfile;
  myfile.open ("netlist.dot");
	
	myfile << "digraph {\n";

	for(int i = 0; i < Vertices_Vector.size(); i++){
		
		struct VertexData vertex = Vertices_Vector[i];

		myfile << vertex.component_id << " [label=\""<<vertex.component_name<<"-"<<vertex.component_id<<"\",shape=circle];\n";

	}
	
	for (int v = 0; v < Vertices_Vector.size(); ++v) 
  { 
    for (auto x : adj[v]){ 
    	myfile << v << " -> " << x << "[label=\""<<Vertices_Vector[v].output << "\"];\n";
		}
  } 



	myfile << "}\n";
  myfile.close();


}

//Prints a queue
void print_queue(std::queue<int> q){
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

//Returns a node's indegree
int getIndegree(std::vector<std::vector<int>>& adj,int node){

	int counter = 0;
	for(auto& vertex : adj){
		for(auto& neighbour : vertex){

			if(neighbour == node){
				counter++;
			}
		}
	}
	

	return counter;
} 

//Print adj
void printGraph1(std::vector<std::vector<int>>& adj){

	int vertex_num = 0;
	for(auto& vertex : adj){

		std::cout << vertex_num;

		for(auto& neighbour : vertex){
			std::cout <<" -> "<<neighbour<<" ";

		}
		std::cout << std::endl;
		vertex_num++;
	}

}

//Progress Bar function
void progressBar(std::string message, unsigned long x, unsigned long y){	
	int percentage = (int)((x+1)*100.0/y);	
	std::cout << "\r"<< "["<<message<<"]["<<percentage<<"%]"<<std::flush;

}

//Topological sort function
std::vector<int> topologicalSort(std::vector<std::vector<int>> adj, std::vector <struct VertexData>& Vertices_Vector){ 
		
	std::vector<int> Sorted;	
	std::queue<int> waiting;	

	//Declare and initialize visited vector
	std::vector<int> visited(Vertices_Vector.size());

	for(auto& vertex : visited){
		vertex = 0;
	}
	
	//Add inputs (i.e. indegree = 0 in queue)
	for(auto& vertex : Vertices_Vector){
		if(vertex.component_name == "INPUT"){
			waiting.push(vertex.component_id);
			visited[vertex.component_id] = 1;
		}
	}
	
	
	//Initialize progress counter	
	int progress = 0;

	//Actually start topological sort
	while (!waiting.empty())
  {
   		int p = waiting.front(); 
     	waiting.pop();
			
			if(percentage_bar){
				if((progress == 0) || (progress % 100 == 0) || (progress == Vertices_Vector.size() -1))
					progressBar("Topological Sort",progress,Vertices_Vector.size());
			}

	
			std::vector<int> neighbours = adj[p];

			//Remove all edges that start from  p
			adj[p].clear();

			for(auto& neighbour : neighbours){

				if((visited[neighbour] == 0) && getIndegree(adj,neighbour) == 0){	
					visited[neighbour] = 1;
					waiting.push(neighbour);
				}
			}

			//Process p
			Sorted.push_back(p);	

			int node_paths = Vertices_Vector[p].paths;

//			std::cout << "Working on node "<<p <<std::endl;
			for(auto& predecessor : Vertices_Vector[p].predecessors){	

//				std::cout << predecessor << std::endl;
//				std::cout << node_paths<< " += " << 	Vertices_Vector[predecessor].paths << std::endl;
				node_paths = node_paths + Vertices_Vector[predecessor].paths;			
			}
			
			Vertices_Vector[p].paths = node_paths;
			//std::cout << "Node " <<p <<" has " << node_paths <<std::endl; 
			//std::cout << Vertices_Vector[p].paths << std::endl;


			//Update progress counter
			progress++;
  }
	
	
	if(percentage_bar)
		std::cout << std::endl;
	

	return Sorted;
}

//Print graph's successors
void printSucessors(std::vector<std::vector<int>>& adj, std::vector <struct VertexData> Vertices_Vector){ 

	std::cout << "---- Printing Sucessors ----\n";

	for(auto& vertex : Vertices_Vector){

					std::cout << "Node " << vertex.component_name << "(" << vertex.component_id << ") has the following successors : ";

					for(auto& succ : vertex.successors){
						std::cout << succ << " ";
					}

					std::cout << std::endl;

	}
	std::cout << "----------------------------\n";
}

//Print graph's predecessors
void printPredecessors(std::vector<std::vector<int>>& adj, std::vector <struct VertexData> Vertices_Vector){ 
	
	std::cout << "---- Printing Predecessors ----\n";

	for(auto& vertex : Vertices_Vector){

					std::cout << "Node " << vertex.component_name << "(" << vertex.component_id << ") has the following predecessors : ";

					for(auto& pred : vertex.predecessors){
						std::cout << pred << " ";
					}

					std::cout << std::endl;

	}
std::cout << "-------------------------------\n";


}

//Returns the size in bytes of the entire graph
int getGraphSize(std::vector<std::vector<int>>& adj, std::vector <struct VertexData> Vertices_Vector){ 
	
				int counter = 0;
				for(auto& vertex : adj){
					counter = counter + vertex.size();
				}

			return ((sizeof(int) * counter) + (sizeof(struct VertexData) * Vertices_Vector.size())); 	
}

//Returns the netlist's paths
int countPaths(std::vector <struct VertexData> Vertices_Vector){ 

	int circuit_paths = 0;

	for(auto& vertex : Vertices_Vector){
		if(vertex.component_name == "OUTPUT"){
			circuit_paths = circuit_paths + vertex.paths;
		}
	}




	return circuit_paths;


}

//Prints the Topological Order of the netlist
void printTopological(std::vector<int> Sorted, std::vector <struct VertexData> Vertices_Vector){ 

	std::cout << "---- Topological Order ----\n";

	for(auto& node : Sorted){
		std::cout << Vertices_Vector[node].component_id << " - " << Vertices_Vector[node].component_name << "\n";
	}	
	std::cout << "---------------------------\n";


}

//Evaluates a single gate
int evaluateGate(std::vector<int> input_vector,std::string component_name){
	
	int output = -1;
	
	//Check if input vector is empty
	if(input_vector.empty()){
		return -1;
	}

	//Check if gates have > 2 inputs
	if(input_vector.size() == 1){
		if(component_name == "NAND" || component_name == "AND" || component_name == "OR" || component_name == "NOR"){
			std::cout << "Gate with only 1 input\n";
			return -1;
		}
	}


	if(component_name == "NAND"){
		
		output = 0;	

		if(std::find(input_vector.begin(), input_vector.end(), 0) != input_vector.end())
		{
    	return 1;
		}
		else if(std::find(input_vector.begin(), input_vector.end(), 2) != input_vector.end())
		{
			return 2;
		}
		else
		{
			return 0;
		}

		//Old Code
				for(auto& in : input_vector){
					if(in == 0){
						output = 1;	
						break;
					}
				}

	}

	else if(component_name == "AND"){

		if(std::find(input_vector.begin(), input_vector.end(), 0) != input_vector.end())
		{
    	return 0;
		}
		else if(std::find(input_vector.begin(), input_vector.end(), 2) != input_vector.end())
		{
			return 2;
		}
		else
		{
			return 1;
		}

				output = 1;	
				for(auto& in : input_vector){
					if(in == 0){
						output = 0;	
						break;
					}
				}	

	}

	else if(component_name == "OR"){

		if(std::find(input_vector.begin(), input_vector.end(), 1) != input_vector.end())
		{
    	return 1;
		}
		else if(std::find(input_vector.begin(), input_vector.end(), 2) != input_vector.end())
		{
			return 2;
		}
		else
		{
			return 0;
		}



				output = 0;	
				for(auto& in : input_vector){
					if(in == 1){
						output = 1;	
						break;
					}
				}	
	}

	else if(component_name == "NOR"){

		if(std::find(input_vector.begin(), input_vector.end(), 1) != input_vector.end())
		{
    	return 0;
		}
		else if(std::find(input_vector.begin(), input_vector.end(), 2) != input_vector.end())
		{
			return 2;
		}
		else
		{
			return 1;
		}


				output = 1;	
				for(auto& in : input_vector){
					if(in == 1){
						output = 0;	
						break;
					}
				}	
	}

	else if(component_name == "NOT"){
		
		if(input_vector.size() != 1){
			std::cout << " NOT GATE WITH MULTIPLE INPUTS !!!" << std::endl;
			return -1;
		}


		if(input_vector[0] == 0)
			output = 1;
		if(input_vector[0] == 1)
			output = 0;
		if(input_vector[0] == 2)
			output = 2;

	}

	else if(component_name == "BUFF" || component_name == "BUFFs"){
		if(input_vector.size() != 1){
			std::cout << " BUFF GATE WITH MULTIPLE INPUTS !!!" << std::endl;
			return -1;
		}
		output = input_vector[0];
	}

	else if(component_name == "INPUT" || component_name == "INPUTs"){
		if(input_vector.size() != 1){
			std::cout << " INPUT GATE WITH MULTIPLE INPUTS !!!" << std::endl;
			return -1;
		}
		output = input_vector[0];	
	}

	else if(component_name == "OUTPUT" || component_name == "OUTPUTs"){
		if(input_vector.size() != 1){
			std::cout << " OUTPUT GATE WITH MULTIPLE INPUTS !!!" << std::endl;
			return -1;
		}
		output = input_vector[0];
	}

	else if(component_name == "NANDs" || component_name == "ANDs" || component_name == "ORs" || component_name == "NORs" || component_name == "NOTs"){
		if(input_vector.size() != 1){
			std::cout << " STEM GATE WITH MULTIPLE INPUTS !!!" << std::endl;
			return -1;
		}
		output = input_vector[0];
	}

 return output;
}			

//Helper print function
std::string printVector(std::vector<int> input_vector){	
		std::string out = "";
		for(auto& i : input_vector)
				out = out + std::to_string(i);	

		return out;
}

//Evaluate Netlist for a given Input Pattern
std::vector<int> evaluate(std::vector<std::vector<int>> adj, std::vector <struct VertexData> Vertices_Vector, std::vector<int> Sorted, std::vector<int> input, bool faulty, std::pair<int,int> fault){ 

	std::vector<int> output;
	int i = 0;
	
	//Propagate results
	for(auto gate : Sorted){

		if(Vertices_Vector[gate].component_name == "INPUT"){
			Vertices_Vector[gate].input_values.push_back(input[i]);
		}
	
		int gate_output = -1;
	
		std::vector<int> input_vector =  Vertices_Vector[gate].input_values;

		std::string gate_type = Vertices_Vector[gate].component_name;

		//Fault Injection
		if(faulty){
		
			if(fault.first == Vertices_Vector[gate].component_id){
				gate_output = fault.second;
			}
			else{
			gate_output = evaluateGate(input_vector,gate_type);
			}

		}
		//Normal Operation
		else{

			gate_output = evaluateGate(input_vector,gate_type);

		}

		Vertices_Vector[gate].output_value = gate_output;

		//For each successor add the output value to it's input values	
		for(auto succ: Vertices_Vector[gate].successors){
			Vertices_Vector[succ].input_values.push_back(gate_output);	
		}

		
		if(Vertices_Vector[gate].component_name == "OUTPUT"){
			output.push_back(gate_output);
		}	

		i++;
	}
	
	/*
	if(faulty)
		std::cout << "  FAULTY  " << printVector(output) << std::endl;	
	else
		std::cout << "  NORMAL  " << printVector(output) << std::endl;	
	
	*/
	return output;
}

//Progress bar for simulation
void progressSim(unsigned long long i, unsigned long long N, Timer timer, bool multithreaded, unsigned long long n){


			std::chrono::duration<float> duration = timer.duration;

			//Duration of 1 input pattern in ms
			float pattern_time = (float) std::chrono::duration_cast<std::chrono::microseconds>(timer.duration).count()/1000;
				
			float time = (float)1000.0/pattern_time;

			int percentage = (int)((i+1)*100.0/N);
			
			int x = (int)(1000/pattern_time);
			
			//Avoid Floating point exception (core dumped)	
			if(x == 0){
						x = 1;	
			}

			//Update every second
			if((i == 1) || (i % x == 0) || (i == N - 1)){
				
				if(pattern_time!= 0){

					unsigned long long done_in_s = (int)((N-i)*pattern_time/1000);
					unsigned long long done_in_m = (int)((N-i)*pattern_time/1000/60);
					unsigned long long done_in_h = (int)((N-i)*pattern_time/1000/60/60);
					unsigned long long done_in_d = (int)((N-i)*pattern_time/1000/60/60/24);
					unsigned long long done_in_mon = (int)((N-i)*pattern_time/1000/60/60/24/30);
					unsigned long long done_in_y = (int)((N-i)*pattern_time/1000/60/60/24/30/12);

					if(multithreaded){
						time = time * n;
						i = i * n;
					}


					std::string padding = "                   ";

					if(done_in_s < 180)
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_s << " sec]"<< padding <<std::flush;

					else if(done_in_m < 180)
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_m << " min]"<< padding <<std::flush;

					else if(done_in_h < 48)
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_h << " hours]"<< padding <<std::flush;

					else if(done_in_d < 90)
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_d << " days]"<< padding <<std::flush;

					else if(done_in_mon < 24)
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_mon << " months]"<< padding <<std::flush;

					else
						std::cout << "\r" << "[" << (unsigned long long)time<< " P/s]"<< "[total "<<i << "]"<< "[" << percentage << "% done][100% in " << done_in_y << " years]"<< padding << std::flush;

				}
			}



}

//Main Simulation Loop for bruteforce
void doWork(unsigned long long start, unsigned long long end, std::vector<std::vector<int>> adj, std::vector <struct VertexData> Vertices_Vector, std::vector<int> Sorted, std::vector<std::string> Tests, bool updateScreen, unsigned long long n, bool fault_dropping, bool percentage_bar){


		unsigned long long N = end-start;
		unsigned long long i = 0;
		unsigned long long j = 0;	

		
		//g_display_mutex.lock();
			//std::thread::id this_id = std::this_thread::get_id();
  		//std::cout << "thread " << this_id << " starting with range "<<start<<" - "<<end << " total: "<< N << std::endl;
		//g_display_mutex.unlock();

		//Sleep for 1 second
		//std::this_thread::sleep_for (std::chrono::seconds(1));
	
		//For each test vector
		for(unsigned long long k = start; k <= end; k++){
			
			std::string pattern = Tests[k];
		
			/*	
			g_display_mutex.lock();
				std::cout << this_id << " Checking :" << pattern << std::endl;
			g_display_mutex.unlock();
			*/

			//Declarations
			std::vector<int> input_vector;

			//Stuck at fault model
			std::pair<int,int> empty_fault;
			
			//Construct input vector
			for(int i = 0; i < pattern.size(); i++){
		
				if(pattern[i] == '0'){
					input_vector.push_back(0);
				}
				else if(pattern[i] == '1'){
					input_vector.push_back(1);
				}
				else if(pattern[i] == '2'){
					input_vector.push_back(2);
					//Don't care
					//std::cout << "Encountered a Don't Care\n";
					//return ;
				}
			}
			
			//Evaluate Netlist (non faulty conditions)
			std::vector<int> correct_output = evaluate(adj,Vertices_Vector,Sorted,input_vector,false,empty_fault);
	
			
			//For each Global Fault	
			for (unsigned long long p = 0; p < Global_Faults_Vector.size(); p++){

	
				std::pair<int,int> current_fault = Global_Faults_Vector[p];


				//If fault not in global vector skip it
				if(std::find(Skipped_Faults_Vector.begin(), Skipped_Faults_Vector.end(), p) == Skipped_Faults_Vector.end())
				{
					//Measure time
					Timer timer;			
	
					std::vector<int> faulty_output = evaluate(adj,Vertices_Vector,Sorted,input_vector,true,current_fault);			

					if(faulty_output != correct_output){
						#ifdef DEBUG
							std::cout << "I CAN DETECT BUG WITH Input:" << printVector(input_vector) << " "; 
							std::cout << "Correct Output:" << printVector(correct_output) << " ";
							std::cout << "Faulty Output: "  <<Vertices_Vector[(current_fault).first].component_name << "-"<<(current_fault).first << " sa-" <<(current_fault).second <<": " << printVector(faulty_output) << std::endl;
						#endif


						g_set_mutex.lock();
							Global_Faults_Set.insert(current_fault);
						g_set_mutex.unlock();

						if(fault_dropping){
							g_fault_mutex.lock();
								Skipped_Faults_Vector.push_back(p);
							g_fault_mutex.unlock();
						}
						
					}
					
				
							
					if(updateScreen && percentage_bar){	
						// For progress bar	
						int F = (end-start)*Global_Faults_Vector.size();
//					std::cout << "Itteration  "<< (*it).first << " - " << (*it).second << "\n";
						//Pretty Printing (inaccurate)
						progressSim(j,F,timer,true,n);
					}
					j++;	
			}

			}
			
			i++;
		}

}

//Helper print function
void printFaultStats(int circuit_faults, int faults_set_size){
	
	std::cout << "\n---- Fault Stats ----\n";
	std::cout << "Fault Coverage: " << (float)(faults_set_size)/(circuit_faults)*100 <<"%"<< std::endl;
	std::cout << "---------------------\n";

}

//Helper Function, return coverage percentage
float getFaultCoverage(int circuit_faults,int faults_set_size){

		return (float)(faults_set_size)/(circuit_faults)*100; 
}

//Generate random test patterns for no apparent reason
void generateRandomTests(std::string fileName, int numOfInputs,int numOfTests)
{
		std::string inputVector = "";

		std::ofstream myfile1;
		myfile1.open (fileName+".txt");

    for (int i = 0; i < numOfTests; i++)
    {
        for (int j = 0; j < numOfInputs; j++)
        {
            float p = rand() % 100 + 1;
            if (p < 50)
            {
                inputVector += '1';
            }
            else
            {
                inputVector += '0';
            }
        }
        myfile1 << inputVector << "\n";
        inputVector = "";
    }
		myfile1.close();    
}

//Save which test vectors detect which faults
void saveFaults(std::vector<std::string> Saved_Test_Faults)
{
		std::ofstream myfile;
		myfile.open ("detected_faults.txt");


		for(auto& line : Saved_Test_Faults)
		{
			myfile << line << std::endl;
		}

		myfile.close();

}

//Main Function
int main(int argc, char *argv[]){
	
	//Start timer	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

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
	}

	//If any argument is given
	else{	
		//Itterate through the arguments
		for (int i = 1; i < argc; ++i){
			
			//Bench File path
			if((std::string)argv[i] == "-C"){
				argument_flag = true;
				if(argc == 2){
					std::cout << "Specify .bench path\n";
					print_usage();
					return -1;
				}else{
					if(argc > i+1)					
						file_path = argv[i+1];
					else{
						std::cout << "Specify a .bench path\n";
						print_usage();
						return -1;
					}
				}
			}

			//Measure time
			else if((std::string)argv[i] == "-T" && argument_flag == true){
				show_time = true;
				if(argc == 2){
					std::cout << "Specify ns,us,ms,s\n";
					print_usage();
					return -1;
				}else if((std::string)argv[i+1] != "ns" && (std::string)argv[i+1] != "us" && (std::string)argv[i+1] != "ms" && (std::string)argv[i+1] != "s"){

					std::cout << "Specify ns,us,ms,s\n";
					print_usage();
					return -1;
				}
				else {
					if((std::string)argv[i+1] == "ns"){
						time_choice = 0;
					}
	
					if((std::string)argv[i+1] == "us"){
						time_choice = 1;
					}

					if((std::string)argv[i+1] == "ms"){
						time_choice = 2;
					}
					if((std::string)argv[i+1] == "s"){
						time_choice = 3;
					}


				}
			}
			
	 		//Input File path
			else if((std::string)argv[i] == "-I" && argument_flag == true){
				test_given = true;
				if(argc == 2){
					std::cout << "Specify input file path\n";
					print_usage();
					return -1;
				}else{
					if(argc > i+1)					
						input_path = argv[i+1];
					else{
						std::cout << "Specify an input path\n";
						print_usage();
							return -1;
					}
				}
			}
	
			//Circuit Statistics
			else if((std::string)argv[i] == "-S" && argument_flag == true){
				print_stats = true;
			}		

			//Fault Dropping or not
			else if((std::string)argv[i] == "-D" && argument_flag == true){
				fault_dropping = true;
			}		

			//Graphviz
			else if((std::string)argv[i] == "-G" && argument_flag == true){
				print_graphviz = true;
			}

			//Percentage Bar
			else if((std::string)argv[i] == "-B" && argument_flag == true){
				percentage_bar = true;
			}

			//Generate Random vectors
			else if((std::string)argv[i] == "-V" && argument_flag == true){
				gentest = true;
			}

			//Save which test vectors detect which faults
			else if((std::string)argv[i] == "-H" && argument_flag == true){
				save_faults = true;
				fault_dropping = false;
			}


			//Threads argument
			if((std::string)argv[i] == "-P"){
				threads = -1; //Use all available threads
				if(argc == 2){
					std::cout << "Specify .bench path\n";
					print_usage();
					return -1;
				}else{
					if(argc > i+1)					
						threads = atoi(argv[i+1]);
					else{
						//std::cout << "Using all available threads\n";
					}
				}
			}

		}
	}
	
	//At least specify an input file
	if(argument_flag == false){
		std::cout << "Please specify an input file\n";
		print_usage();
		return -1;
	}
			
	//Check if input input is a bench file
	if(file_path.substr(file_path.length() - 6) != ".bench"){
		std::cout << "Wrong file type!" << std::endl;
		print_usage();
		return -1;
	}

  //BENCH FILE
  bench_file.open(file_path);
		
	//INPUT FILE
  input_file.open(input_path);


  //Initialization
  std::stringstream stream; //for "prints"
	
	//For bench file
	std::string current_line;
	
	//Bench File Vector	
	std::vector<std::string> Lines;
	std::vector<std::string> Temp;
	

  //File opening (bench_file)
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
	

	//Test Inputs delcarations
	int file_type = -1; // 0 = .txt 1 = .vec 2 = .comp.10 3 = .benchtest.in

	//Vector where input tests are saved	
	std::vector<std::string> Tests;

	//If input vector file not given
	if(!test_given){
		std::cout << "No test/input file given.\n";
		print_usage();
		return -1;
	}

	//If input vector file is given
	else{
		//Parse input/test file
  	if (!input_file) {
    	std::cout << "Error Opening Vector File" << std::endl;
			print_usage();
    	return -1;
  	}
  	else{
    	while(std::getline(input_file, current_line)){
      	Tests.push_back(current_line);
			}
  	}

		// Four types of input file
		// .txt .vec .comp.10 .benchtest.in
		
		//Check if input file is one of the 4 types		
		if(input_path.substr(input_path.length() - 4) == ".txt" ){
		
			file_type = 0;	

		}	
		else if(input_path.substr(input_path.length() - 4) == ".vec"){

			file_type = 1;	

		}		
		else if(input_path.substr(input_path.length() - 8) == ".comp.10"){

			file_type = 2;	

		}	
		else if(input_path.substr(input_path.length() - 13) == ".benchtest.in"){

			file_type = 3;	

		}

		//Not a valid filetype
		if(file_type == -1){
			std::cout << "Wrong input file type!" << std::endl;
			print_usage();
			return -1;
		}
	}

	//Done saving input file
	
	//Netlist Statistics Counters
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
		
		if(percentage_bar){
			if((index == 0) || (index % 100 == 0) || (index == Lines.size()-1))
				progressBar("Preprocessing File",index,Lines.size());			
		}	
	
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

		index++;
	}

	//Cleaned up file
	Lines = Temp;

	//Declare Graph
	int V = Lines.size(); 
	
	//Vertex Data	
	std::vector<struct VertexData> Vertices_Vector;
	
	//Graph datastructure
  //std::vector<int> adj[V]; 

	std::vector<std::vector<int>> adj(V);
	
	if(percentage_bar)
		std::cout << std::endl;
	
		
	//Reinit index		
	index = 0;

 	//Parse clean file
	for(auto& line : Lines){
			
		if(percentage_bar){
			if((index == 0) || (index % 100 == 0) || (index == Lines.size() - 1))
				progressBar("Identifying Gates",index,Lines.size());			
		}
		

			if(line.substr(0,5) == "INPUT"){

				//std::cout<<line.substr(0,5)<<std::endl;
				INPUT++;
				Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(0,5)));	

			}


			//Check if OUTPUT
			else if(line.substr(0,6) == "OUTPUT"){
				
				//std::cout<<line.substr(0,6)<<std::endl;
				OUTPUT++;

				
				Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(0,6)));	

				
			}
			//Gates
			else{
	
				int pos = line.find("=");
					
				pos++;

				//Check if NAND
				if(line.substr(pos,4) == "NAND"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					NAND++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,4)));	


				}

				//Check if AND
				if(line.substr(pos,3) == "AND"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					AND++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,3)));	


				}
			
				//Check if NOR
				if(line.substr(pos,3) == "NOR"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOR++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,3)));	


				}

				//Check if OR
				if(line.substr(pos,2) == "OR"){
				
					//std::cout<<line.substr(pos,2)<<std::endl;
					OR++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,2)));	

				}

				//Check ig BUFF
				if(line.substr(pos,4) == "BUFF"){
				
					//std::cout<<line.substr(pos,4)<<std::endl;
					BUFF++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,4)));	


				}


				//Check if NOT
				if(line.substr(pos,3) == "NOT"){
				
					//std::cout<<line.substr(pos,3)<<std::endl;
					NOT++;

					Vertices_Vector.push_back(AddToGraph(line,index,adj,line.substr(pos,3)));	


				}
			}

		index++;
	}
	

	index = 0;	

	if(percentage_bar)
		std::cout << std::endl;
	

	//Construct Actual Graph (G1)
	//For each component
	for(auto& vertex : Vertices_Vector){

		if(percentage_bar){
			if((index == 0) || (index % 100 == 0) || (index == Vertices_Vector.size()-1))
				progressBar("Constructing G1 Graph",index,Vertices_Vector.size());			
		}
	
		//std::cout <<vertex.component_name << std::endl;	

		if(vertex.component_name != "INPUT"){		

			//For each component input
			for(auto& input : vertex.inputs){
				
				//Find which components have the input as output
				for(auto& vertexx : Vertices_Vector){
					
					if(vertexx.output == input){
						
						addEdge(adj,vertexx.component_id,vertex.component_id);
						
					}
				}	
			}
		}
		index++;
	}
	

	if(percentage_bar)
		std::cout << std::endl;
	
	//Graph is now G1

	//This portion of the code will convert it to G2

	//Algorithm Steps

	//1. Itterate through all components

	//2. If a component's output is connected to > 2 components

	//3. Delete edges from component to other components
	
	//4. Create new vertices (as many as the component's connected outputs)

	//5. Connect component -> new_vertice -> other_component (for all components that our component was conncted to via it's output) 
	
	#ifdef G2	
	
	//Save edges that will be deleted from graph	
	std::vector<std::pair < int, int > > saved_edges;

	index = 0;
	
	//Saving Edges with stems
	for(auto& vertex_neighbours : adj){


		if(percentage_bar)
				if((index == 0) || (index % 100 == 0) || (index == adj.size()-1))
					progressBar("Collecting Stems",index,adj.size());
		

		if(vertex_neighbours.size() > 1){
		

			for(auto& neighbour : vertex_neighbours){

				//save the edges
				std::pair < int, int > edge_pair;
				edge_pair.first = Vertices_Vector[index].component_id;
				edge_pair.second = neighbour;
				saved_edges.push_back(edge_pair);
									
			}
	
		}

		index++;
	}	
		

	//Counter
	int number = 0;	
	
	//Start from here
	index = Vertices_Vector.size();
	
	//Index must not be reset here

	//Converts Graph from G1 to G2
	for(auto& saved_pair : saved_edges){
		
		//Delete edge
		deleteEdge(adj,saved_pair.first,saved_pair.second);

		//Create new vertex
		struct VertexData stem;

		stem.component_id = index;
		stem.component_name = Vertices_Vector[saved_pair.first].component_name + "s";
		stem.inputs.push_back(saved_pair.first);
		stem.output = saved_pair.second;		
		

		Vertices_Vector.push_back(stem);
			
		std::vector<int> empty_vector;

		adj.push_back(empty_vector);	

		//Add 2 edges
		addEdge(adj,saved_pair.first,index);
		addEdge(adj,index,saved_pair.second);
			
			
		number++;
		index++;
	}
	
	#endif //G2


	//Calculate Sucessors and Predecessors
	int x = 0;
	for(auto& node : adj){
		for(auto& y : node){
			Vertices_Vector[x].successors.push_back(y);
			Vertices_Vector[y].predecessors.push_back(x);	
		}
		x++;
	}


	if(percentage_bar)
		std::cout << std::endl;

	
	//Calculate Topological Order
	std::vector<int> Sorted = topologicalSort(adj,Vertices_Vector);

	//Returns the circuit's paths
	int PATHS = countPaths(Vertices_Vector);


	#ifdef VERBOSE

	//Print Netlist in Topological Order
	printTopological(Sorted,Vertices_Vector);
	
	//Print Sucessors
	printSucessors(adj,Vertices_Vector);

	//Print Predecessors
	printPredecessors(adj,Vertices_Vector);

	netlist_stats(index,NAND,AND,OR,NOR,NOT,BUFF,INPUT,OUTPUT);
	
	//Print Vertices in stdout (std::vector)	
	printVertexVector(Vertices_Vector);

	//Print the whole graph
	printGraph(adj,Vertices_Vector);

	//Print the whole graph
	printGraph1(adj);
	#endif


	//Generate random vectors
	if(gentest){
		
		std::size_t found = file_path.find_last_of("/\\");
		std::string test=  file_path.substr(found+1);

		std::size_t found1 = test.find_last_of(".");
		std::string test1 =  test.substr(0,found1);
		
		int numOfTests = Tests.size();
		generateRandomTests(test1+"",INPUT,numOfTests);
		return 0;
	}


	#ifdef PARTB // Part B starts here

	
	//Preprocess Input File
	if(test_given){	
		//File Parsing	
		//.txt
		if(file_type == 0){

		}
		//.vec
		else if(file_type == 1){
			
			//Delete first and last line
			Tests.erase(Tests.begin()); //delete first item
			Tests.erase(Tests.end()); //delete last item

		}
		//.comp.10
		else if(file_type == 2){
						std::vector<std::string> Tests1;

						for(auto & line : Tests)
						{
							std::string fixed_line = line.substr(3,line.size());

//							std::cout << fixed_line << std::endl;

							Tests1.push_back(fixed_line);
						}	
						Tests.clear();
						Tests = Tests1;
		}
		///benchtest.in
		else if(file_type == 3){

						std::vector<std::string> Tests1;

						for(auto & line : Tests)
						{
							if((line.find("1") != std::string::npos) || (line.find("0") != std::string::npos)   || (line.find("2") != std::string::npos))
							{
								std::string fixed_line = line;

								std::size_t found = fixed_line.find_last_of(":");
								std::string test =  fixed_line.substr(found+2);

//								std::cout << test << std::endl;

								Tests1.push_back(test);
							}
						}	
						Tests.clear();
						Tests = Tests1;
	

		}
	}

	//Find ALL possible stuck at faults in circuit = 2*N, where N is the number of lines (or edges)
	
	//Saves all Possible Faults 
	std::vector<std::pair<int,int>> Faults_Vector;

	int fault_sites = 0;
	
	// Detecting all possible fault sites
	for(auto& node : Vertices_Vector){
		
			if(node.component_name != "OUTPUT"){
				fault_sites++;
			
				std::pair<int,int> fault;
				fault.first = node.component_id;
				fault.second = 0;
			
				//sa-0
				Faults_Vector.push_back(fault);

				fault.second = 1;
				//sa-1
				Faults_Vector.push_back(fault);
		}
	}	
	
	int max_faults = fault_sites * 2;
	
	int checkpoint_fault_sites = 0;	

	int skipped_fault_sites = 0;

	//Checkpoint Theorem
	bool checkpoint = true; 

	
	if(checkpoint){
		
		//Restart Vector
		Faults_Vector.erase(Faults_Vector.begin(),Faults_Vector.end());

		// Detecting checkpoint fault sites
		for(auto& node : Vertices_Vector){
			
			std::size_t found = node.component_name.find("s");

			if((node.component_name == "INPUT") || (found!=std::string::npos)){
				
				checkpoint_fault_sites++;

				std::pair<int,int> fault;
				fault.first = node.component_id;
				fault.second = 0;
			
				//sa-0
				Faults_Vector.push_back(fault);

				fault.second = 1;
				//sa-1
				Faults_Vector.push_back(fault);

		}else if(node.component_name != "OUTPUT"){
				skipped_fault_sites++;
			}
	}	
	

	} //Done with checkpoint theorem


	//Parallel Initializations (Checkpoint Theorem Fault List)
	Global_Faults_Vector = Faults_Vector;


	int circuit_faults = checkpoint_fault_sites * 2;

	//Faults that Test Vectors are able to detect
	//First = id of gate's output that is stuck at either 0 or 1	
	//Second = 1 or 0
	std::set<std::pair<int,int>> Faults_Set;

	//Vector that holds which test vector detected which fault
	std::vector<std::string> Saved_Test_Faults;


	//Serial Fault Simulation	
	if(threads == -2){
		//Single Threaded Simulation for input file
		if(test_given){

			unsigned long long N = Tests.size();	
			unsigned long long i = 0;
			unsigned long long j = 0;	
		
			if(percentage_bar)
				std::cout << "Max Patterns: " << N * Faults_Vector.size() << std::endl;

			//For each test vector
			for(auto& pattern : Tests){
				
				
				//Declarations
				std::vector<int> input_vector;

				//Stuck at fault model
				std::pair<int,int> empty_fault;

				//Construct input vector
				for(int i = 0; i < pattern.size(); i++){

					if(pattern[i] == '0'){
						input_vector.push_back(0);
					}
					else if(pattern[i] == '1'){
						input_vector.push_back(1);
					}
					else if(pattern[i] == '2'){
						input_vector.push_back(2);
						//Don't care
						//std::cout << "Encountered a Don't Care\n";
						//return -1;
					}
				}
			
				//Evaluate Netlist (non faulty conditions)
				std::vector<int> correct_output = evaluate(adj,Vertices_Vector,Sorted,input_vector,false,empty_fault);
	

				#ifdef SOFR
				for(int i = 0; i < correct_output.size(); i++)
				{
					std::cout << correct_output[i];
				}
				std::cout << std::endl;
				#endif


				//For each Fault	
				for (std::vector<std::pair<int,int>>::iterator it = Faults_Vector.begin() ; it != Faults_Vector.end();){

					//Measure time
					Timer timer;			
	
					std::vector<int> faulty_output = evaluate(adj,Vertices_Vector,Sorted,input_vector,true,(*it));			
					#ifdef DEBUG 
					std::cout << printVector(input_vector) << " "; 
					std::cout << " " << printVector(faulty_output);
					std::cout << " vs " << printVector(correct_output);
					
					if(faulty_output != correct_output)
					{
						std::cout << " != ";				
					}else
					{
						std::cout << " == ";;				
					}
					#endif

					if(faulty_output != correct_output){
	
						//#define DEBUG
						#ifdef DEBUG
							std::cout << "I CAN DETECT BUG WITH Input:" << printVector(input_vector) << " "; 
							std::cout << "Correct Output:" << printVector(correct_output) << " ";
							std::cout << "Faulty Output: "  <<Vertices_Vector[(*it).first].component_name << "-"<<(*it).first << " sa-" <<(*it).second <<": " << printVector(faulty_output) << std::endl;
						#endif

						Faults_Set.insert(*it);

						//Save which test vector detected which fault
						if(save_faults)
						{
							
							std::string temp_line;
							temp_line = printVector(input_vector) + "," + std::to_string((*it).first) + "," + std::to_string((*it).second);
							Saved_Test_Faults.push_back(temp_line);	
						}

						if(fault_dropping){
							it = Faults_Vector.erase(it);
						}else{
							++it;
						}

					}else{
						++it;
					}
				
					if(percentage_bar){	
						// For progress bar	
						int F = N * circuit_faults;

						//Pretty Printing (inaccurate)
						progressSim(j,F,timer,false,0);
					}
					j++;	

				}

				i++;
			}

		//Pretty Printing
		std::cout << std::endl;

		}
	}//if serial

	//Print Fault stats 
	//printFaultStats(circuit_faults,Faults_Set.size());

	if(save_faults)
	{
		saveFaults(Saved_Test_Faults);
	}


	//Multithreaded Simulation
	if(threads > -2 && test_given){
		
		//std::cout << "Parallel Simulation\n";

		unsigned long long n;

		if(threads == -1){
			n = std::thread::hardware_concurrency();
		}else{
			n = threads;
		}
		//std::cout << "Threads Used: " << n << std::endl;

		//Construct Ranges
		unsigned long long start_range = 0;
		unsigned long long end_range = 0;

		unsigned long long N = Tests.size();

		//std::cout << "Tests: " << N << "\n";	

		std::vector <std::pair<unsigned long long , unsigned long long>> Range_Vector;

		//Split work "equally" for N threads
		for(int i = 1; i<(n+1); i++)
		{		
			if(i == n){
				end_range = N-1;
			}
			
			else{
				end_range = start_range+(N/n)-1;
			}

			std::pair<unsigned long long,unsigned long long> temp_pair;
			temp_pair.first = start_range;
			temp_pair.second = end_range;
			Range_Vector.push_back(temp_pair);
			start_range = end_range+1;
		}
	
		//Thread objects are stored here
		std::vector <std::thread> Thread_Vector;
	
		//Start n threads
		for(unsigned long long i = 0; i < n; i++)
		{		
			//Special thread ;)
			if(i == n-1){
				Thread_Vector.emplace_back(doWork,Range_Vector[i].first,Range_Vector[i].second, adj, Vertices_Vector, Sorted, Tests, true, n, fault_dropping, percentage_bar);

			}
			
			else{
				Thread_Vector.emplace_back(doWork,Range_Vector[i].first,Range_Vector[i].second, adj, Vertices_Vector, Sorted, Tests, false, n, fault_dropping, percentage_bar);

			}
		}
		

		//Wait for all threads to finish
		for(auto& t : Thread_Vector)
		{		
			t.join();	
		}

		std::cout << std::endl;

	}
	//Single Threaded Simulation
	
	#endif //PartB

	//End time
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	
	std::string time_unit = "";
	std::string stats = "";

	//Returns Netlist stats in std out
	if(print_stats){

		//Calculate Graph Size 
		int bytes = getGraphSize(adj,Vertices_Vector);
		float fault_coverage;

		if(threads == -2){
			fault_coverage = getFaultCoverage(circuit_faults, Faults_Set.size());
		}
		else{
			fault_coverage = getFaultCoverage(circuit_faults,Global_Faults_Set.size());
		}

		std::string Dropping = "";
		if(fault_dropping){
			Dropping = " Dropping:YES";
		}
		else{
			Dropping = " Dropping:NO";
		}

		std::string Mode = "";

		if(threads == -2){
			Mode = " Thr:1";
		}else if(threads > -2){
			Mode = " Thr:"+std::to_string(threads);
		}
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << fault_coverage;
		std::string s = stream.str();

		std::size_t found = input_path.find_last_of("/\\");
		std::string test=  input_path.substr(found+1);

		stats = " LINES:"+std::to_string(index)+" NAND:"+std::to_string(NAND)+" AND:"+std::to_string(AND)+" OR:"+std::to_string(OR)+" NOR:"+std::to_string(NOR)+" NOT:"+std::to_string(NOT)+" BUFF:"+std::to_string(BUFF)+" INPUT:"+std::to_string(INPUT)+" OUTPUT:"+std::to_string(OUTPUT)+" KB:"+std::to_string(bytes/1024)+" PATHS:"+std::to_string(PATHS)+" COVERAGE:"+s+"%"+Dropping+Mode+" TEST:"+test;
	}

	//Print to Graphviz file
	if(print_graphviz){
		//Write Graphviz file
		if(adj.size() > 100){
			std::cout << "No graphviz for large graphs\n";
		}else
			printGraphviz(adj,Vertices_Vector);	
	}

	//From command line argument	
	if(show_time){	
		if(time_choice == 0)		
			std::cout << file_path << " = " << (float) std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << " [ns]" << stats <<std::endl;

		if(time_choice == 1)
			std::cout << file_path <<" = " << (float) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]" << stats <<std::endl;

		if(time_choice == 2)
			std::cout << file_path << " = " << (float) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000 << " [ms]" << stats <<std::endl;

		if(time_choice == 3)
			std::cout << file_path << " = " << (float) std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000 << " [s]" << stats <<std::endl;

	}

	//Print Netlist Statistics	
	else if(print_stats){
		std::cout << stats << std::endl;	
	}

	return 0;
}
