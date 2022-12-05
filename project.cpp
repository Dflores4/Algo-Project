//Created By Dominic Flores and Jesus Quinonez
//Project for 3120
//Advanced DFS

#include <iostream>
using namespace std;

//Global Variables
const int hill_num = 10;
const int lost_poison = 5;
int poison[3] = {170 , 170 , 170};
int ant_num[hill_num] = {40 , 80 , 30 , 60 , 30, 75, 49, 22, 88, 33};
int ant_num_copy[hill_num] = {40 , 80 , 30 , 60 , 30, 75, 49, 22, 88, 33};
int global_visited[hill_num] = {0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0};
int visited[hill_num] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int small_visited[hill_num] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int flag = 0;
int total_killed = 0;

//Function Prototypes
void fillGraph(int , int[][10]);
void showGraph(int , int[][10]);
void drop_poison(int [][10], int , int, int);
void drop_poison_official(int [][10], int , int, int);
int check_connections(int [][10] , int);
void bigD(int start, int graph[][10]);
void reset_values();
int main()
{
    int graph[hill_num][hill_num];
    fillGraph(hill_num , graph);
    showGraph(hill_num , graph);
    bigD(0, graph);
    //drop_poison(graph, 0, poison[0], 0);
    //cout << "\nAnts Killed: " << total_killed << "\n\n";
    return 0;
}

//Function Definitions

//Fills adjacency matrix with input from file
void fillGraph(int num , int graph[][10])
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
void showGraph(int num , int graph[][10])
{
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            //cout << graph[i][j] << " ";
        }
        //cout << endl;
    }
}

//This is the small dfs. It takes in the adjacency matrix, the index of the current node
//The amount of poison, and the index of the current poison vile
void drop_poison(int graph[][10] , int current , int current_poison, int poison_index)
{
    //Mark Node has been visited in this pass. 
    small_visited[current] = 1;
    //cout << "\n\nVisited Node: " << current+1 << endl;
    //cout << "Current Poison: " << current_poison << endl;

    //Kill Ants. So far sums up the number of ants killed
    if (ant_num[current] - current_poison >= 0) {
        //cout << "Ant Amount Before: " << ant_num[current] << endl;
        //Update Ant Number
        int place_holder = ant_num[current];
        ant_num[current] = ant_num[current] - current_poison;
        //Update Poison
        current_poison = current_poison - place_holder;
        //cout << "Ant Amount After: " << ant_num[current] << endl;
        total_killed += place_holder - ant_num[current];
        //cout << "Ants Killed " << total_killed << endl;
    }
    else {
        //cout << "Ant Amount Before: " << ant_num[current] << endl;
        total_killed += ant_num[current];
        //Update Poison
        current_poison = current_poison - ant_num[current];
        //Update Ant Number
        ant_num[current] = 0;
        //cout << "Ant Amount After: " << ant_num[current] << endl;
        //cout << "Ants Killed " << total_killed << endl;
    }
    //Used to set poison to 0 if negative
    if (current_poison < 0) {
        current_poison = 0;
    }
    //Updates Poison vile value
    poison[poison_index] = current_poison;
    //cout << "Poison left over: " << current_poison << "\n\n";
    //Ends if we run out of poison
    if (current_poison <= 5) {return;}

    int connections = 0;
    //Finds how many neighbors this node has
    connections = check_connections(graph, current);
    //Splits poison and uses some for traversal
    current_poison = (current_poison/connections) - lost_poison;

    //This loop is the basic dfs. It allows the poison to spread evenly
    for (int i = 0; i < hill_num; i++) {
        if (graph[current][i] == 1 && small_visited[i] == 0) {
            drop_poison(graph, i, current_poison, poison_index);
            small_visited[i] = 0;

        }
    }

    return;
}

//Returns number of neighbors
int check_connections(int graph[][10] , int current)
{
    int adjacent = 0;
    for (int i = 0; i < hill_num; i++) {
        if (graph[current][i] == 1) {
            adjacent += 1;
        }
    }
    return adjacent;
}

//resets global values
void reset_values() {

    for(int i = 0; i < hill_num; i++) {
        visited[i] = global_visited[i];
        small_visited[i] = 0;
        ant_num[i] = ant_num_copy[i];
    }
    for(int i = 0; i < 3; i++) {
        poison[i] = 170;
    }
    total_killed = 0;
}

//iterates small dfs on the entire graph 3 times finding the optimal node drop each time
//saves the previous best drop placement info and uses that info to drop the next best optimal drop
void bigD(int start, int graph[][10]) {
    int killed_ants[hill_num];
    int drop_place[3] = {-1, -1, -1};
    int max;
    int max_index;
    //Iterates through each poison vial 
    for(int i = 0; i < 3; i++) {
        cout << "===================================================================" << endl;
        //Drops vial into every node in the graph
        for(int j = 0; j < hill_num; j++) {

            //drops poison at node j
            drop_poison(graph, j, poison[i], i);

            //Records total ants killed in an array
            if (j == 0) {
                cout << "Total Ants Killed if Vile " << i+1 << " is dropped on them: " << endl;
            }
            killed_ants[j] = total_killed;
            cout << killed_ants[j] << "   ";
            //resets visited array back to how it was after previous drop
            reset_values();
        }
        cout << endl;
        max = 0;
        //Finds the node that killed most ants and saves it inot max_index
        for(int j = 0; j < hill_num; j++) {
            if(killed_ants[j] > max) {
                max = killed_ants[j];
                max_index = j;
            }
        }
        cout << "\nDropping in Hill " << max_index+1 << " results in most ants killed!\n" << endl;
        //Before ants were killed
        cout << "Ants before vile " << i+1 << " was dropped into anthill " << max_index+1 << endl;
        for (int d = 0; d < 10; d++) {
            cout << ant_num_copy[d] << " ";
        }
        cout << endl;
        cout << endl;
        //Recording the optimal node drop placement into an array
        drop_place[i] = max_index;
        //Update Actual data by dropping poison into the original data
        drop_poison_official(graph, max_index, poison[i], i);
        //Show New Values
        cout << "Ants after vile " << i+1 << " was dropped into anthill " << max_index+1 << endl;
        for (int d = 0; d < 10; d++) {
            cout << ant_num_copy[d] << " ";
        }
        cout << endl;
        cout << endl;
        reset_values();
        //Drops poison on the best node
        drop_poison(graph, max_index, poison[i], i);

        //Records visited nodes after dropping poison in the best node into global visited
        for(int j = 0; j < hill_num; j++) {
            global_visited[j] = visited[j];
        }

        //Resets visited now with the global visited nodes 
        reset_values();
    }
    cout << "\nBest Nodes to drop poison in: " << endl;
    //Prints final solution of where to make the three drops of poison
    for(int i = 0; i < 3; i++) {
        cout << "Drop in hill: " << drop_place[i]+1 << endl;
    }
}

void drop_poison_official(int graph[][10] , int current , int current_poison, int poison_index)
{
    //Mark Node has been visited in this pass. 
    small_visited[current] = 1;
    //cout << "\n\nVisited Node: " << current+1 << endl;
    //cout << "Current Poison: " << current_poison << endl;

    //Kill Ants. So far sums up the number of ants killed
    if (ant_num_copy[current] - current_poison >= 0) {
        //cout << "Ant Amount Before: " << ant_num[current] << endl;
        //Update Ant Number
        int place_holder = ant_num_copy[current];
        ant_num_copy[current] = ant_num_copy[current] - current_poison;
        //Update Poison
        current_poison = current_poison - place_holder;
        //cout << "Ant Amount After: " << ant_num[current] << endl;
        total_killed += place_holder - ant_num_copy[current];
        //cout << "Ants Killed " << total_killed << endl;
    }
    else {
        //cout << "Ant Amount Before: " << ant_num[current] << endl;
        total_killed += ant_num_copy[current];
        //Update Poison
        current_poison = current_poison - ant_num_copy[current];
        //Update Ant Number
        ant_num_copy[current] = 0;
        //cout << "Ant Amount After: " << ant_num_copy[current] << endl;
        //cout << "Ants Killed " << total_killed << endl;
    }
    //Used to set poison to 0 if negative
    if (current_poison < 0) {
        current_poison = 0;
    }
    //Updates Poison vile value
    poison[poison_index] = current_poison;
    //cout << "Poison left over: " << current_poison << "\n\n";
    //Ends if we run out of poison
    if (current_poison <= 5) {return;}

    int connections = 0;
    //Finds how many neighbors this node has
    connections = check_connections(graph, current);
    //Splits poison and uses some for traversal
    current_poison = (current_poison/connections) - lost_poison;

    //This loop is the basic dfs. It allows the poison to spread evenly
    for (int i = 0; i < hill_num; i++) {
        if (graph[current][i] == 1 && small_visited[i] == 0) {
            drop_poison_official(graph, i, current_poison, poison_index);
            small_visited[i] = 0;

        }
    }

    return;
}


