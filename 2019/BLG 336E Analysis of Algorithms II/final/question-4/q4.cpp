#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Node {
public:
	int element;
	Node* next;
	Node* prev;
};

int main(int argc, char** argv) {
	ifstream testfile;
	testfile.open(argv[1]); //read the inputs from test file

	int capacity; //capacity is the maximum number of elements in the cache, defined as k in pdf
	int element_number; //number of different elements that can possibly requested, equals to k+1 in our case
	int request_number; //number of requests, defined as n in pdf

	testfile >> capacity;
	element_number = capacity + 1;

	int cache_size = 0; //cache size keeps number of elements in the cache, initially zero
	vector<int> cache(element_number, 0); //cache is created as empty as all indexes are 0

	testfile >> request_number;
	vector<int> requests(request_number);
	for (int i = 0; i < request_number; i++)
		testfile >> requests[i];
	
	vector<int> fif(requests.size()); //to keep the farthest element for each request

	vector<int> elements(element_number); //elements array {0, 1, ... , k}
	for (int i = 0; i < element_number; i++)
		elements[i] = i;

	vector<Node*> addresses; //array for keeping the address of double linked list nodes of elements
	//addresses[i] keeps the node address for elements[i]

	/* IMPLEMENT HERE */

		// 1. create the double linked list for elements vector, you can use Node class defined above
		// keep each node's address in addresses array

	 
		// 2. fill the fif (farthest-in-future) array considering the pseudocode given in pdf.
	

		// 3. process the requests and print out necessary outputs, you can use following syntax:
		// cout << "cache miss" << endl;
		// cout << "cache is full, element " << fif[i] << " is evicted" << endl;
		// cout << "element " << requests[i] << " is added into the cache" << endl;
		// cout << "cache hit" << endl;
	

	/*IMPLEMENT HERE*/

	return 0;


}