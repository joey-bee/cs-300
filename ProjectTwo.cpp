//*================================================*
//* Name        : ProjectTwo.cpp	    			*
//* Author      : Joseph Opheim					*
//* Version     : 1.0							    *
//* Copyright   : Copyright ? 2023 SNHU COCE 	    *
//* Description : CS300 Project Two				*
//*================================================*

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
#include <time.h>

//https:stackoverflow.com/questions/17335816/clear-screen-using-c
//#include <conio.h> //i have windows and using possibly to clear screen

using namespace std;

//forward declarations
double strToDouble(string str, char ch);


//course structure to store info
struct Course {
	string course_id;
	string course_title;
	string pre_req_one;
	string pre_req_two;
	vector<string>prerequisites;
};

//tree node internal struct
struct Node {
	Course course;
	Node* left;
	Node* right;

	//constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	//initializing with a course
	Node(Course acourse) {
		left = nullptr;
		right = nullptr;
		course = acourse;
	}
};

//class with methods to hold information
class BinarySearchTree {
private:
	Node* root;
	void inOrder(Node* node);
	void add_node(Node* node, Course course);

public:
	BinarySearchTree();
	virtual~BinarySearchTree();
	void in_order();
	void insert_course(Course course);
	Course search_course(string course_id);
};

//constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

//destructor
BinarySearchTree::~BinarySearchTree() {
	//delete root->left;
	//delete root->right;
	//FIX ME!!!
	//DO I NEED A WHILE LOOP LIKE PREVIOUS ASSIGNMENT?
	//while (root != nullptr) {
		//Remove(root->course.course_id);
	//there is no remove in this assignment
}

//creating a new node with its course
void BinarySearchTree::insert_course(Course course) {
	//Node* newNode = new Node;
	//newNode->course = course;

	//if conditional of root = nullptr
	//then root is equal to new node course
	if (root == nullptr) {
		root = new Node(course);
		//newNode->left = nullptr;
		//newNode->right = nullptr;
	}

	//else creating a new node equal to root node
	else {
		this->add_node(root, course);
	}
}

//below is what i had originally but it was not working
//i decided to leave it in just in case i need it or
//for future reference

	//here we are continuing to loop through the tree
	//until it is placed correctly
	//while (currNode != nullptr) {

		//if no left node then set to new node
/*if (newNode->course.course_id < currNode->course.course_id) {
	if (currNode->left == nullptr) {
		currNode->left = newNode;
		currNode = nullptr;
	}
*/
//in order
void BinarySearchTree::in_order() {
	this->inOrder(root);
}

//searching for course to print
Course BinarySearchTree::search_course(string course_id) {

	//current is now equal to the root
	Node* currNode = root;

	//while loop to search until course id match
	while (currNode != nullptr) {

		//if we find a match then return the match
		if (currNode->course.course_id.compare(course_id) < 0) {
			return currNode->course;
		}

		//if small than the current then traverse to the left
		else if (course_id.compare(currNode->course.course_id)) {
			currNode = currNode->left;
		}

		//but if its larger then go right
		else {
			currNode = currNode->right;
		}
	}

	//if no match is found then return empty course
	Course course;
	return course;
}

void BinarySearchTree::add_node(Node* node, Course course) {

	//if the node is larger then add it to the left
	if (node->course.course_id.compare(course.course_id) > 0) {

		//if no left node then it becomes left
		if (node->left == nullptr) {
			node->left = new Node(course);
		}

		else {

			//go down the left side
			this->add_node(node->left, course);
		}
	}

	else {

		//if no right node then it becomes right
		if (node->right == nullptr) {
			node->right = new Node(course);
		}

		//go down the right node
		else {
			this->add_node(node->right, course);
		}
	}
}

void BinarySearchTree::inOrder(Node* node) {
	//if node != null ptr
	//return
	if (node != nullptr) {
		//return;


	//in order to the left
		inOrder(node->left);

		//display course identification and course title
		std::cout << node->course.course_id << ", " << node->course.course_title << endl;

		//in order to the right
		inOrder(node->right);
	}
}

//loading courses and information from the file
void load_course_info(string csvPath, BinarySearchTree* bst) {

	Course course;

	std::cout << "Loading the file " << csvPath << endl;

	//cout << csvPath;

	ifstream file;
	string read_line;

	try {
		file.open(csvPath);

		//if the file opens
		if (file.is_open()) {

			//while the file is good
			while (file.good()) {
				std::cout << read_line << endl;

				//read file
				while (getline(file, read_line)) {

					//https:stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do
					//parsing the csv file with string stream
					//formatiing the strings
					stringstream ss(read_line);

					//new variables but same as above
					string courseID;
					string courseTitle;
					string pre_req_one;
					string pre_req_two;

					//read the lines and seperate with ',' (token)
					getline(ss, courseID, ',');
					getline(ss, courseTitle, ',');
					getline(ss, pre_req_one, ',');
					getline(ss, pre_req_two, ',');


					//now we marry the variables from above
					course.course_id = courseID;
					course.course_title = courseTitle;
					course.pre_req_one = pre_req_one;
					course.pre_req_two = pre_req_two;

					//pushbacks for prerequisites vector
					course.prerequisites.push_back(pre_req_one);
					course.prerequisites.push_back(pre_req_two);

					//insert into tree
					bst->insert_course(course);

					//clear the string stream
					ss.clear();
				}
			}
		}

		else {
			std::cout << "File not loaded. Try again!" << endl;
		}
	}
	catch (exception& e) {

		//display error message but dont store for later

		cerr << e.what() << endl;
	}
}
//again i tried this route below these comments and could not get the file to load properly and the courses


		/*
	//creating fstream variable
	fstream ABCU;

	//creating a file stream object then
	//fstream abc;

	//while(! eof){

	ABCU.open(csvPath, fstream::in);

	//if the file doesnt exist then return and display error message
	if (!ABCU.is_open()) {
		cout << "Error loading file. Please try again!" << endl;
		return;
	}

	//while not end of file
	while (!ABCU.eof()) {

		//creating variables to hold each line and split it
		string read_line;
		string token_line;
		vector<string>file_vector;

		//getting enitre line and new iteration
		getline(ABCU, read_line);
		Course course;


		//https:stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do
		//parsing the csv file with string stream
		//formatiing the strings
		stringstream stream(read_line);

		//streaming the object to split by the comma
		while (getline(stream, token_line, ',')) {

			//inserting into vector
			file_vector.push_back(token_line);
		}

		*/

//display the courses
void course_display(Course& course) {
	std::cout << course.course_id << ", " << course.course_title << endl;

	//with the prerequisites, if the variable is not empty
	//then print with its course id
	if (!(course.pre_req_two == "")) {
		std::cout << "Prerequisites: " << course.pre_req_one << ", " << course.pre_req_two;
	}

	else {
		std::cout << "Prerequisites: " << course.pre_req_one;
	}
	std::cout << endl;
}

//forward decs from above
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

//main
int main(int argc, char* argv[]) {

	//variables
	string csvPath;
	string courseKey;
	Course course;

	//switch cases setting up coursekey and course id
	switch (argc) {
	case 2:
		csvPath = argv[1];

		break;

	case 3:
		csvPath = argv[1];

		break;

	default:
		csvPath = "ABCU.csv";
		//course id
		//cout << argc;
	}


	//defining the search tree to hold course info
	BinarySearchTree* bst;
	bst = new BinarySearchTree();

	//initializing char user_choice
	char user_choice = '0';

	//while loop for user choices to validate
	while (user_choice != '9') {


		//main menu display
		std::cout << endl;
		std::cout << "Welcome to the course planner." << endl;
		std::cout << endl;
		std::cout << "  1. Load Data Structure" << endl;
		std::cout << "  2. Print Course List." << endl;
		std::cout << "  3. Print Course." << endl;
		std::cout << "  9. Exit" << endl;
		std::cout << endl;
		std::cout << "What would you like to do? ";

		//taking in user input
		std::cin >> user_choice;
		std::cout << endl;

		//if choice is between 1, 2, 3
		//switched to char to ensure only these digits work
		if(user_choice != '1' && user_choice != '2' && user_choice != '3') {

			//print message that number is not valid
			std::cout << endl;
			std::cout << user_choice << " is not a valid option." << endl;
			std::cout << endl;
			continue;
		}

		//validating they are using a digit before case switches
		//else if (!(isdigit(user_choice))) {
		//	cout << "Please enter 1, 2, 3, or 9!" << endl;
		//}

		//return 0;


		//switch cases for user input
		switch (user_choice) {
		case '1':
			//call load course method
			load_course_info(csvPath, bst);

			//break switch
			break;

		case '2':

			//if search tree is empty
			if (bst == NULL) {
				std::cout << "Error loading file." << endl;
			}

			else {

				//sample schedule display message
				std::cout << "Here is a sample schedule: " << endl;

				//print the search tree in order
				bst->in_order();

				//break switch
				break;
			}

		case '3':

			// course info display message
			std::cout << "What course do you want to know about?" << endl;

			//course key in
			std::cin >> courseKey;
			std::cout << endl;

			//In C++, transform() is a built-in STL function used to apply the given 
			// operation to a range of elements and store the result in another range.
			//https:www.geeksforgeeks.org/transform-c-stl-perform-operation-elements
			//also since the output is all in caps, we are using to upper
			std::transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

			//having it search for couse key = course id
			course = bst->search_course(courseKey);

			//if the course matches or if it is NOT an empty return
			if (!course.course_id.empty()) {

				//display the course found
				course_display(course);
			}

			else {
				std::cout << "Course " << courseKey << " not found." << endl;
			}

			//break switch
			break;
		}
	}
	//exit display message
	std::cout << "Thank you for using the course planner!" << endl;

	return 0;
}