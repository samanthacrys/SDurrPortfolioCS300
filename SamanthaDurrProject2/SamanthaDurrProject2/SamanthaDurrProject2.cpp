// SamanthaDurrProject2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

/*
* This class contains all the information that pertains to holding the courses from the
* courses file for their prerequisites, names, and course number. This also contains a method
* that displays the information when called upon.
*/
class Course
{
//Public variables that are accessible throughout the program.
public:
    string courseNum;
    string courseDescription;

    vector<string>prerequisites;

    //Default constructor.
    Course()
    {

    }

    //Implementation of the fields vector that contains information on the course number and the title.
    Course(vector<string> &fields)
    {
        courseNum = fields[0];
        courseDescription = fields[1];

        //For every index in the fields while less than the size of the field, add
        // a prerequisite to the prerequistes vector.
        for (int index = 2; index < fields.size(); ++index)
        {
            prerequisites.push_back(fields[index]);
        }
    }

    /*
    * This displasy a course's information when the course is searched for. It shows the course number,
    * course's title, and, if any, prerequisites that the course may have.
    */
    void Display()
    {
        cout << courseNum << ", " << courseDescription << endl;
        cout << "Prerequistes: ";
        for (int ii = 0; ii < prerequisites.size(); ++ii)
        {
            cout << prerequisites[ii];
            if (ii + 1 < prerequisites.size())
            {
                cout << ", ";
            }
        }
        cout << endl;
        cout << "\n";
    }
};

/*
* This class contains the nodes necessary for sorting the list of courses as a binary tree.
*/
class Node 
{
public:
    Course course;
    Node* left;
    Node* right;

    //Default constructor that sets left and right nodes to null.
    Node() 
    {
        left = nullptr;
        right = nullptr;
    }

    //Sets the course node to sCourse.
    Node(Course sCourse) : Node()
    {
        course = sCourse;
    }
};

/*
* This contains the information that is necessary for a binary search. The methods and variables that are
* necessary are found within this class to initialize the necessary methods.
 */
class BinarySearchTree 
{

//Private variables and methods that are not accessible by the system.
private:
    Node* root;

    void Add(Node* node, Course &course);
    void postOrder(Node* node);

//Public methods that are accessible by the to make changes,
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void PostOrder();
    void Insert(Course &course);
    Course *Search(string courseNum);
};

/**
 * Default constructor that initializes the root node to null.
 */
BinarySearchTree::BinarySearchTree() 
{
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() 
{
    // recurse from root deleting every node
}

//This method calls to the postOrder method and sorts the classes from last to first. 
void BinarySearchTree::PostOrder() 
{
    postOrder(root);
}

/*
* Param: Course with a pointer to the course variable in the Course class.
* 
* This method inserts a new node into the root of the tree.
*/
void BinarySearchTree::Insert(Course &course) 
{


    if (root == nullptr)
    {
        root = new Node();
        root->course = course;
    }
    else
    {
        Add(root, course);
    }
}

/**
 * Param: courseNum, the course to search for.
 * 
 * Takes in a course and searches for it when the user enters the course to search for.
 */
Course *BinarySearchTree::Search(string courseNum) 
{

    //Create a node called currentNode and assign it to what is in root.
    Node* currentNode = root;

    //While the currentNode is not null, search for the course number that was entered by the user.
    while (currentNode != nullptr)
    {
        //If the currentNode's coursenumber is equal to the entered course number, then return the course number.
        if (currentNode->course.courseNum == courseNum)
        {
            return &currentNode->course;
        }

        //If the course number is less than the course number, then assign the currentNode to the left
        //side. Otherwise, assign it to the right side.
        if (courseNum < currentNode->course.courseNum)
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }
    return nullptr;
}

/**
 *
 * Param: a node to store information in.
 * Param: course a pointer to the course variable in the Course Class
 */
void BinarySearchTree::Add(Node* node, Course &course) 
{

    //If the course's course number is less than the course's course number, then check on if the node is on the left
    //side or the right side of the binary tree.
    if (course.courseNum < node->course.courseNum)
    {

        //If the node on the left side of the tree is null, create a new node on the left side and assign
        //that node to the course. Otherwise, add a node to the left side and assign course to it.
        if (node->left == nullptr)
        {
            node->left = new Node();
            node->left->course = course;
        }
        else
        {
            Add(node->left, course);
        }
    }
    else
    {
        //If the node on the right is pointed at null, then create a new node and assign the course to it. Otherwise,
        //add the node to the right and assign course to it.
        if (node->right == nullptr)
        {
            node->right = new Node;
            node->right->course = course;
        }
        else
        {
            Add(node->right, course);
        }
    }
}

/**
 * Sorts the course into froim last to first in a post order method.
 */
void BinarySearchTree::postOrder(Node* node)
{

    //If the node is not null, then go left and then right. Display the information for the course number after that.
    if (node != nullptr)
    {
        postOrder(node->left);
        postOrder(node->right);

        cout << node->course.courseNum << ", " << node->course.courseDescription << endl;
    }
}

//Assign a new variable called bst and connect it to the BinarySearchTree constructor.
BinarySearchTree bst = BinarySearchTree();

/*
* Reads a single line from the course list file that contians the information for all of the courses
* and stores these into fields.
* 
* Param: cfs is the file that we are opening.
* Param: point to a vector called fields.
*/
void ReadFileLine(ifstream& cfs, vector<string>& fields)
{
    string field;
    char ch = ' ';

    //While the cfs file is good and there is not a new line, get the character in the file and add it
    //to the field vector from fields and then clear the line. Also make sure that there is no new line
    //or carriage return.
    while (cfs.good() && ch != '\n')
    {
        cfs.get(ch);

        //Check if there is a comma. If there is, then add the current string to the fields vector and clear.
        //Then start from there and continue.
        if (ch == ',')
        {
            fields.push_back(field);
            field.clear();
            continue;
        }
        //If the character is not equal to a carriage return and a new line, add the character to field.
        if (ch != '\r' && ch != '\n')
        {
            field += ch;
        }
    }

    fields.push_back(field);
}

/*
* A boolean method that reads in a file and checks that it is good and stores the strings into it for displaying.
* 
* Param: string fileName. This is the name of the file that is going to be read.
*/
bool ReadCoursesFile(string fileName)
{
    ifstream cfs(fileName);

    //If the file is open, then read through it and insert the courses into the proper nodes
    //for displaying and searching.
    if (cfs.is_open())
    {
        //While the file is good, create a vector called fields, call the ReadFileLine method, and make sure
        //that there are at least 2 fields for each element in field. Once that is done, close the file if
        //it is not. Then set the course to fields and insert that into course itself.
        while (cfs.good())
        {
            vector<string>fields;
            ReadFileLine(cfs, fields);
            //If the size of fields is less than two, close the file.
            if (fields.size() < 2)
            {
                cfs.close();

                return false;
            }
            Course course(fields);
            bst.Insert(course);
        }
        cfs.close();
    }

    return true;
}

/*
* Calls the PostOrder method to print the list in a bottom to top order.
*/
void PrintCoursesList()
{
    cout << "Here is a sample schedule of available classes:" << endl;
    cout << "\n";
    bst.PostOrder();
}

/*
* Prints the course that a user is searching for with all the necessary information on that course.
*/
void PrintCourse()
{
    cout << "What course do you want to know about? ";

    string userCourse;

    cin >> userCourse;

    Course* course = bst.Search(userCourse);

    //Make sure that course is not equal to null. If it is, then the course does not exist. Otherwise,
    //display the course.
    if (course == nullptr)
    {
        cout << "There is no such course." << endl;
    }
    else
    {
        course->Display();

    }
}

/*
* The main menu that displays the choices that the user can select.
*/
void MainMenu()
{
    int choice = 0;

    while (choice != 4)
    {
        cout << "Welcome to course planner." << endl;
        cout << "\n";
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "4. Exit" << endl;
        cout << "\n";
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            ReadCoursesFile("courseList.text");
            break;

        case 2:
            PrintCoursesList();
            break;

        case 3:
            PrintCourse();
            break;

        case 4:
            cout << "Thank you for making user of the course planner system!";
            break;

        default:
            cout << choice << " is not a valid option. Please pick a valid option." << endl;
            cout << "\n";
            break;

        }
    }

}


//The main method that calls the MainMenu.
int main()
{
    MainMenu();

    return 0;
}
