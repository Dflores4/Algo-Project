//Created By Dominic Flores
//Project for 3120
//Advanced BFS

#include <iostream>
using namespace std;

//Global Variables
const int hill_num = 5;
const int lost_poison = 5;
int poison[3] = {100 , 100 , 100};
int ant_num[hill_num] = {40 , 80 , 30 , 60 , 30};
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

void showGraph(int num , int graph[][5])
{
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      cout << graph[i][j] << " ";
    }
    cout << endl;
  }
}

void drop_poison(int graph[][5] , int current , int current_poison, int poison_index)
{
  //Mark Node has been visited in this pass. Clean up in next pass
  visited[current] = 1;
  cout << "\n\nVisited Node: " << current << endl;
  cout << "Current Poison: " << current_poison << endl;
  //Kill Ants
  if (ant_num[current] - current_poison >= 0) {
    cout << "Ant Amount Before: " << ant_num[current] << endl;
    total_killed += current_poison;
    cout << "Ants Killed " << total_killed << endl;
  }
  else {
    cout << "Ant Amount Before: " << ant_num[current] << endl;
    total_killed += ant_num[current];
    cout << "Ants Killed " << total_killed << endl;
  }
  //Used Poison
  current_poison = current_poison - ant_num[current];
  if (current_poison < 0) {
    current_poison = 0;
  }
  poison[poison_index] = current_poison;
  cout << "Poison in current vile: " << poison[poison_index] << "\n\n";;
  if (current_poison == 0) {return;}

  int connections = 0;
  connections = check_connections(graph, current);
  current_poison = (current_poison/connections) - lost_poison;

  for (int i = 0; i < hill_num; i++) {
    if (graph[current][i] == 1) {
      drop_poison(graph, i, current_poison, poison_index);
    }
  }

  return;
}

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
