//Created By Dominic Flores
//Project for 3120
//Advanced DFS

#include <iostream>
using namespace std;

//Global Variables
const int hill_num = 5;
const int lost_poison = 5;
int poison[3] = {500 , 100 , 100};
int ant_num[hill_num] = {40 , 80 , 30 , 30 , 60};
int ant_num_copy[hill_num] = {40 , 80 , 30 , 30 , 60};
int global_visited[hill_num] = {0 , 0 , 0 , 0 , 0};
int visited[hill_num] = {0 , 0 , 0 , 0 , 0};
int flag = 0;
int total_killed = 0;

//Function Prototypes
void fillGraph(int , int[][5]);
void showGraph(int , int[][5]);
void drop_poison(int [][5], int , int, int);
int check_connections(int [][5] , int);

int main()
{
  int graph[hill_num][hill_num];
  fillGraph(hill_num , graph);
  showGraph(hill_num , graph);

  drop_poison(graph, 0, poison[0], 0);
  cout << "\nAnts Killed: " << total_killed << "\n\n";
  return 0;
}

//Function Definitions

//Fills adjacency matrix with input from file
void fillGraph(int num , int graph[][5])
{
  int input = 0;
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      cin >> input;
      graph[i][j] = input;
    }
  }
}

//Prints Adjacency Matrix
void showGraph(int num , int graph[][5])
{
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      cout << graph[i][j] << " ";
    }
    cout << endl;
  }
}

//This is the small dfs. It takes in the adjacency matrix, the index of the current node
//The amount of poison, and the index of the current poison vile
void drop_poison(int graph[][5] , int current , int current_poison, int poison_index)
{
  //Mark Node has been visited in this pass. 
  visited[current] = 1;
  cout << "\n\nVisited Node: " << current << endl;
  cout << "Current Poison: " << current_poison << endl;
  
  //Kill Ants. So far sums up the number of ants killed
  if (ant_num[current] - current_poison >= 0) {
    cout << "Ant Amount Before: " << ant_num[current] << endl;
    //Update Ant Number
    int place_holder = ant_num[current];
    ant_num[current] = ant_num[current] - current_poison;
    //Update Poison
    current_poison = current_poison - place_holder;
    cout << "Ant Amount After: " << ant_num[current] << endl;
    total_killed += place_holder - ant_num[current];
    cout << "Ants Killed " << total_killed << endl;
  }
  else {
    cout << "Ant Amount Before: " << ant_num[current] << endl;
    total_killed += ant_num[current];
    //Update Poison
    current_poison = current_poison - ant_num[current];
    //Update Ant Number
    ant_num[current] = 0;
    cout << "Ant Amount After: " << ant_num[current] << endl;
    cout << "Ants Killed " << total_killed << endl;
  }
  //Used to set poison to 0 if negative
  if (current_poison < 0) {
    current_poison = 0;
  }
  //Updates Poison vile value
  poison[poison_index] = current_poison;
  cout << "Poison left over: " << current_poison << "\n\n";
  //Ends if we run out of poison
  if (current_poison <= 15) {return;}

  int connections = 0;
  //Finds how many neighbors this node has
  connections = check_connections(graph, current);
  //Splits poison and uses some for traversal
  current_poison = (current_poison/connections) - lost_poison;

  //This loop is the basic dfs. It allows the poison to spread evenly
  for (int i = 0; i < hill_num; i++) {
    if (graph[current][i] == 1 && visited[i] == 0) {
      drop_poison(graph, i, current_poison, poison_index);
      visited[i] = 0;
    }
  }

  return;
}

//Returns number of neighbors
int check_connections(int graph[][5] , int current)
{
  int adjacent = 0;
  for (int i = 0; i < hill_num; i++) {
    if (graph[current][i] == 1) {
      adjacent += 1;
    }
  }
  return adjacent;
}
