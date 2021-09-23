/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Sevryn Napora, Jason Rossi
 * Date        : October 20, 2020
 * Description : Solving the water jug puzzle from Die Hard.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State* parent = nullptr;
	State (int _a, int _b, int _c, string _directions) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

		// String representation of state in tuple form.
		string to_string() {
			ostringstream oss;
			oss << "(" << a << ", " << b << ", " << c << ")";
			return oss.str();
		}

	};

void display_steps(State *s){
	if (s->parent != nullptr){
		display_steps(s->parent);
	}
	cout << s->directions << s->to_string() << endl;
}


void jugBFS (int Acap, int Bcap, int Ccap, int Atarget, int Btarget, int Ctarget) {
	//2D array that keeps track of parents.
	bool **visited = new bool*[Acap + 1];
	for (int i = 0; i < Acap + 1; i++){
		visited[i] = new bool[Bcap + 1];
		fill(visited[i], visited[i] + (Bcap + 1), false);
	}


	//Queue that keeps track of the states.
	queue<State*> q;

	//Initalize initial state
	State *s = new State(0, 0, Ccap, "Initial state. ");


	//Store initial state on queue
	q.push(s);

	//Boolean that checks if the puzzle is solvable with the given inputs.
	bool isSolvable = false;

	int pour_amt;
	int available_space;

	while (!q.empty()){
		State *current = q.front();
		q.pop();

    if (current->a == Atarget && current->b == Btarget && current->c == Ctarget) {
			isSolvable = true;
			display_steps(current);
			break;
		}


		//Check if state has already been visited
		if (visited[current->a][current->b] == true) {
			continue;
		}

		visited[current->a][current->b] = true;

			//1. Pour C into A
			if(current->c != 0){
				available_space = (Acap - current->a);
				if (current->c > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->c;
				}
				if (pour_amt != 0 && pour_amt != 1) {
					q.push(new State(pour_amt + current->a, current->b, current->c - pour_amt, "Pour " + to_string(pour_amt) + " gallons from C to A. "));
					q.back()->parent = current;
				}
				else if(pour_amt != 0 && pour_amt == 1){
					q.push(new State(pour_amt + current->a, current->b, current->c - pour_amt, "Pour " + to_string(pour_amt) + " gallon from C to A. "));
					q.back()->parent = current;
				}
			}

			//2. Pour B into A
			if(current->b != 0) {
				available_space = (Acap - current->a);
				if (current->b > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->b;
				}
				if (pour_amt != 0 && pour_amt != 1) {
					q.push(new State(pour_amt + current->a, current->b - pour_amt, current->c, "Pour " + to_string(pour_amt) + " gallons from B to A. "));
					q.back()->parent = current;
				}
				else if(pour_amt != 0 && pour_amt == 1){
					q.push(new State(pour_amt + current->a, current->b - pour_amt, current->c, "Pour " + to_string(pour_amt) + " gallon from B to A. "));
					q.back()->parent = current;
				}
			}

			//3. Pour C into B
			if(current->c != 0){
				available_space = (Bcap - current->b);
				if (current->c > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->c;
				}
				if (pour_amt != 0 && pour_amt != 1) {
					q.push(new State(current->a, current->b + pour_amt, current->c - pour_amt, "Pour " + to_string(pour_amt) + " gallons from C to B. "));
					q.back()->parent = current;
				}
				else if (pour_amt != 0 && pour_amt == 1) {
					q.push(new State(current->a, current->b + pour_amt, current->c - pour_amt, "Pour " + to_string(pour_amt) + " gallon from C to B. "));
					q.back()->parent = current;
				}

			}

			//4. Pour A into B
			if(current->a != 0){
				available_space = (Bcap - current->b);
				if (current->a > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->a;
				}
				if (pour_amt != 0 && pour_amt != 1) {
					q.push(new State{current->a - pour_amt, current->b + pour_amt, current->c, "Pour " + to_string(pour_amt) + " gallons from A to B. "});
					q.back()->parent = current;
				}
				else if (pour_amt !=0 && pour_amt == 1) {
					q.push(new State{current->a - pour_amt, current->b + pour_amt, current->c, "Pour " + to_string(pour_amt) + " gallon from A to B. "});
					q.back()->parent = current;
				}
			}

			//5. Pour B into C
			if(current->b != 0){
				available_space = (Ccap - current->c);
				if (current->b > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->b;
				}
				if (pour_amt != 0 && pour_amt != 1){
					q.push(new State{current->a, current->b - pour_amt, current->c + pour_amt, "Pour " + to_string(pour_amt) + " gallons from B to C. "});
					q.back()->parent = current;
				}
				else if (pour_amt != 0 && pour_amt == 1) {
					q.push(new State{current->a, current->b - pour_amt, current->c + pour_amt, "Pour " + to_string(pour_amt) + " gallon from B to C. "});
					q.back()->parent = current;
				}
			}

			//6. Pour A into C
			if(current->a != 0){
				available_space = (Ccap - current->c);
				if (current->a > available_space){
					pour_amt = available_space;
				}
				else {
					pour_amt = current->a;
				}
				if (pour_amt != 0 && pour_amt != 1){
					q.push(new State{current->a - pour_amt, current->b, current->c + pour_amt, "Pour " + to_string(pour_amt) + " gallons from A to C. "});
					q.back()->parent = current;
				}
				else if (pour_amt != 0 && pour_amt == 1) {
					q.push(new State{current->a - pour_amt, current->b, current->c + pour_amt, "Pour " + to_string(pour_amt) + " gallon from A to C. "});
					q.back()->parent = current;
				}
			}
	}

	if(isSolvable == false) {
		cout << "No solution." << endl;
	}

  //Deleting the array 'visited'
	for (int i = 0; i < Acap + 1; i++){
		delete [] visited[i];
	}
	delete [] visited;

}

int main(int argc, char * const argv[]) {
	int Acap, Bcap, Ccap, Atarget, Btarget, Ctarget, total_target;
	istringstream iss;

  if (argc != 7) {
    cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    return 1;
  }
	  iss.str(argv[1]);
	  if (!(iss >> Acap)) {
		  cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[1]) <= 0) {
			  cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
			  return 1;
	  	  }
		  iss.clear();
	  }

	  iss.str(argv[2]);
	  if (!(iss >> Bcap)) {
		  cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[2]) <= 0) {
			  cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
			  return 1;
		  }
		  iss.clear();
	  }



	  iss.str(argv[3]);
	  if (!(iss >> Ccap)) {
		  cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[3]) <= 0) {
			  cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
			  return 1;
		  }
		  iss.clear();
	  }


	  iss.str(argv[4]);
	  if (!(iss >> Atarget)) {
		  cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[4]) < 0){
			  cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
			  return 1;
		  }

		  iss.clear();
	  }



	  iss.str(argv[5]);
	  if (!(iss >> Btarget)) {
		  cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[5]) < 0) {
			 cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
			 return 1;
		  }
		  iss.clear();
	  }



	  iss.str(argv[6]);
	  if (!(iss >> Ctarget)) {
		  cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		  return 1;
	  }
	  else {
		  if (atoi(argv[6]) < 0) {
			  cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
			  return 1;
		  }
		  iss.clear();
	  }

	  if (atoi(argv[1]) < atoi(argv[4])){
		  cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		  return 1;
	  }

	  if(atoi(argv[2]) < atoi(argv[5])) {
		  cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		  return 1;
	  }

	  if(atoi(argv[3]) < atoi(argv[6])) {
		  cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		  return 1;
	  }

	  total_target = atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]);
	  if (total_target > atoi(argv[3]) || total_target < atoi(argv[3])) {
		  cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		  return 1;
	  }

	jugBFS(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
	return 0;
}

