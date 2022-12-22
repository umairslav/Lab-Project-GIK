#include <iostream>   //Muhammad Umair Khan (2021473)
using namespace std;  //Abdulrehman Sajid (2021024)
                      //Muhammad Abdur Rahman Durrani (2021325)
                      //Instructor Usama Arshad Janjua
                      //FCSE Batch 31 Lab Project



class BillQueue  //this is a class which computes the bill for bought items by using a queue datastructure
{
    struct node
    {
        string item;
        int price;
        node *next;
    };
    public:
    node *head;
    void push(string a,int b)    //pushes a new node at the tail of queue
    {
        node *ptrnew = new node;
        ptrnew->item=a;
        ptrnew->price=b;
        if (head == nullptr)     //condition if the queue is totally empty
        {
            head = ptrnew;
        }
        else
        {
            node *ptrtemp = head;
            while(ptrtemp->next!=nullptr)   //traverses the pointer to the tail of the queue
            {
                ptrtemp=ptrtemp->next;
            }
            ptrtemp->next=ptrnew;   // stores the new node at the very tail of the queue
        }
    }
    BillQueue()   //constructor
    {
        head=nullptr;
    }
    node *qpop()   //this function pops the node at the head of queue and moves head to the next (return type node)
    {
        node *popnode = head;
        head = head->next;
        return popnode;
    }
    void billcompute()   //this function is used to compute the bill by popping and printing on the console while also showing total variable
    {

        cout<<"Item\tPrice"<<endl;
        int total=0;
        while(head!=nullptr)   //loop used to pop from queue and add to total
        {
            node *ptrbill = qpop();
            if (ptrbill==nullptr)  //exception condition if queue is empty
            {
                cout<<"Nothing bought yet...."<<endl;
                return;
            }
            cout<<ptrbill->item<<"\t"<<ptrbill->price<<endl;   //basic printing code
            total+=ptrbill->price;
        }
        cout<<"Total:\t"<<total<<endl;
        total=0;
    }
};

class MenuBST  //we use this class to store the menu items of a bakery and the quantity and price of those items
{
	struct node
    {
		node* left, * right;
		string data;
        int count,price;
	};
	node* newNode(string num,int count1,int price2)  //function used to create a new node in the BST
    {
		node *newPtr = new node;
		newPtr->data = num;
        newPtr->count = count1;
        newPtr->price = price2;
		newPtr->left = newPtr->right = nullptr;
		return newPtr;
	}
	void createNodeUtil(node*& root, string num,int count1,int price2)  //helps in distinguishing whether thr new node is to be stored to the right or left of a parent node
    {
		if (root == NULL) {   //if root is null, it stores the new node at root
			root = newNode(num,count1,price2);
			return;
		}
		else if (num > root->data)   //sends the new node to the right of root
			createNodeUtil(root->right, num,count1,price2);
		else if (num < root->data)   //sends the new node to the left of root
			createNodeUtil(root->left, num,count1,price2);
		else
			cout << "Duplicate item found.... "<<endl<<"Cant add item again...." << endl<<endl;  // if a duplicate value is found, condition is satisfied and node is not created
	}
public:
	node* root;
	MenuBST()  //constructor
    {
		root = nullptr;
	}
	void createNode(string num,int count1,int price2)  //calls the createnodeutil funtion to make the new node for BST
    {
		createNodeUtil(root, num,count1,price2);
	}
	void printInorder(node *root)  //funtion prints the BST in order to show the available items in menu which is stored in the BST
    {
		if (root == NULL)  //prints nothing if BST is empty
			return;
		printInorder(root->left);  //goes to the left node first
		cout <<"Item name : "<< root->data <<"\t" << "Price : "<<root->price<<"\tAvailable Quantity : "<<root->count<<endl;
		printInorder(root->right);  //goes to right node last
	}
	void search(node *b,string a,BillQueue &q)   //this search funtion is used to find a node in the BST and also push it into the queue
    {                                            //it also decreases the count variable of an item in the menu by 1 as it pushes it once into the queue
    	if (b == NULL || b->count<=0)
        {
			cout << "Not Found"<<endl<<endl;
			return;
		}
		if (a == b->data && b->count>=0) {      
			cout << "Found added to the List"<<endl<<endl;
            q.push(b->data,b->price);   // funtion to push to the queue
            b->count--;                 //count variable of the select item is decreased by 1
			return;
		}
		else if (a < b->data)           //conditions to search the tree in order to find the item
			search(b->left, a,q);
		else
			search(b->right, a,q);
	}
};

int main()    //main is used to create instances of the classes and a basic menu is implemented
{
	MenuBST a;
    BillQueue q;
    cout << "..... Bakery Counter Interface ....."<<endl;
    int n;
    do   //do while loop to keep executing the menu until user inputs 0 into the console
    {
        cout<<"1. Add items to Bakery Menu"<<endl;
        cout<<"2. Display all available items"<<endl;
        cout<<"3. Buy items"<<endl;
        cout<<"4. Compute Bill"<<endl;
        cout<<"0. Exit Program....."<<endl;
        cin>>n;
        switch(n)
        {
            case(1):
            {
                cout<<"Enter item name :"<<endl;
                string z;
                cin>>z;
                cout<<"Enter item available quantity :"<<endl;
                int x;
                cin>>x;
                cout<<"Enter price of item :"<<endl;
                int y;
                cin>>y;
                a.createNode(z,x,y);   //creates a node in MenuBST for the item
                break;
            }
            case(2):
            {
                a.printInorder(a.root); //prints all available items, their price and quantity alphabeticallt
                break;
            }
            case(3):
            {
                cout<<"What item do you want to buy :"<<endl;
                string z;
                cin>>z;
                a.search(a.root,z,q);   //searches the BST and finds the item to be bought decreasing its quantity by 1 in BST and pushing it into queue
                break;
            }
            case(4):
            {
                cout<<"Bill...."<<endl;
                q.billcompute();        //calls the billcompute function to finally compute the bill of all the bought items for a customer
                break;
            }
            case(0):    //condition to end the do while loop
                break;
            default:    //output if user inputs an option not given in menu
                cout<<"Enter valid option...."<<endl;
        }
    } while (n!=0);
}
