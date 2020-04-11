#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<queue>
#include<conio.h>
#include<graphics.h>

using namespace std;

#define LIST1_MAX_SIZE 256
#define LIST2_MAX_SIZE 1024
#define LIST3_MAX_SIZE 5000
#define Size_List 30

// Class to create list nodes
template<class T>
class Node{
	public:
	T data;
	T internal_frag;
	bool available;
	Node<T> *next;

		Node()
		{
			data=0;
			next=0;
			internal_frag=0;
			available=true;
		}
		Node(T x)
		{
			data=x;
			next=0;
			internal_frag=0;
			available=true;
		}
};

// creating link list
template<class T>
class SinglyList{
	Node<T> *head;
	int size;
	void deleteall()
	{
		Node<T> *current,*temp;
		current=head;
		while(current!=0)
		{
			temp=current;
			current=current->next;
			temp->next=0;
			delete temp;
		}
		size=0;
	}
	public:
		//Cnstructors
		SinglyList()
		{
			head=NULL;
			size=0;
		}
		
		SinglyList(const SinglyList<T> &rhs)
		{
			Node<T> *n,*current,*temp,*last;
			current=rhs.head;
			this->size=rhs.size;
			this->head=NULL;
			while(current!=0)
			{
				temp=new Node<T>(current->data);
				if(this->head==NULL)
				{
					head=temp;
					last=temp;
				}
				else
				{
					last->next=temp;
					last=temp;
				}
				current=current->next;
			}
			
		}
		
		// Inserting data
		void insertatlast(T x)
	{
		if(head==NULL)
		{
			Node<T> *n=new Node<T>(x);
			head=n;
		}
		else
		{
		Node<T> *current=head;
		while(current->next!=NULL)
		{
			current=current->next;
		}
		Node<T> *n=new Node<T>(x);
		current->next=n;}
	}
		SinglyList& operator =(const SinglyList &rhs)
		{
			if(this!=&rhs)
			{
				deleteall();
			Node<T> *n,*current,*temp,*last;
			current=rhs.head;
			this->size=rhs.size;
			while(current!=0)
			{
				temp=new Node<T>(rhs->data);
				if(head==0)
				{
					head=temp;
					last=temp;
				}
				else
				{
					last->next=temp;
					last=temp;
				}
				current=current->next;
			}
			return(*this);
			}
		}
		void insertatfront(T x)
		{
			Node<T> *n=new Node<T>(x);
			if(head==0)
			{
				head=n;
			}
			else
			{
				n->next=head;
				head=n;
			}
			size++;
		}
		
		// Delete data
		void deletefromfront()
	{
		if(head!=0)
		{
			Node<T> *n=new Node<T>;
			n=head;
			head=head->next;
			n->next=0;
			delete n;
			size--;
		}
		else
		{
			cout<<"List is Empty"<<endl;
		}
	}
	void displaylist()
	{
		Node<T> *n=new Node<T>();
		n=head;
		while(n!=0)
		{
			cout<<n->data<<endl;
			n=n->next;
		}
	}
	int getsize()
	{
		return(size);
	}
	// First fit strategy
	bool FirstFit(T x)
	{
		Node<T> *current=head;
		bool check=false;
		while(current!=NULL)
		{
			if(current->available==true)
			{
			
			if(current->data>=x )
			{
				current->internal_frag=current->data-x;
				current->available=false;
				check=true;
				cout<<"of size "<<x<<" bytes has been allocated the block of "<<current->data<<" bytes"<<endl;
				break;
			}
		   }
			current=current->next;
		}
		return(check);
	}
	
	
	// Best fit strategy
	bool BestFit(T x)
	{
		Node<T> *current=head,*best=head;
		bool check=false;
		T temp=current->data;
		while(current!=NULL)
		{
			if(current->available==true)
			{
			
			if(current->data>=x )
			{
			    if(current->data - x < temp && current->data - x >=0)
			    {
				best=current;
				temp=current->data - x;
				check=true;
			    }
			
			}
		   }
			current=current->next;
		}
		if(check==true)
		{
		current=head;
		while(current!=0)
		{
		if(current==best)
		{
		cout<<"of size "<<x<<" bytes has been allocated a block of "<<current->data<<" bytes"<<endl;
		best->internal_frag=current->data - x;
		best->available=false;
		break;
	   }
		current=current->next;
	}
}
		return(check);
	}
	// Worst fit strategy
	bool WorstFit(T x)
	{
		Node<T> *current=head,*best=head;
		bool check=false;
		T temp=current->data;
		while(current!=NULL)
		{
			if(current->available==true)
			{
			
			if(current->data>=x )
			{
			    if(current->data - x > temp && current->data - x >=0)
			    {
				best=current;
				temp=current->data - x;
				check=true;
			    }
			
			}
		   }
			current=current->next;
		}
		if(check==true)
		{
		current=head;
		while(current!=0)
		{
		if(current==best)
		{
		cout<<"of size "<<x<<" bytes has been allocated a block of "<<current->data<<" bytes"<<endl;		
		best->internal_frag=current->data - x;
		best->available=false;
		break;
	   }
		current=current->next;
	}
}
		return(check);
	}
	void reverse()
	{
		Node<T> *current=head,*prev=NULL,*q=NULL;
		while(current!=NULL)
		{
			q=current->next;
			current->next=prev;
			prev=current;
			current=q;
		}
		head=prev;
	}
	
	// Calculating internal fragmentation
	int Internal_Fragmentation()
	{
		int cal=0;
		Node<T> * current=head;
		while(current!=NULL)
		{
			if(current->available==false)
			cal+=current->internal_frag;
			
			current=current->next;
		}
		return(cal);
	}
	
	// Calculating number of free blocks
		void Free_Blocks()
		{
			Node<T> *current=head;
			while(current!=NULL)
			{
				if(current->available==true)
				{
					cout<<"|"<<current->data<<"|"<<", ";
				}
				current=current->next;
			}
			cout<<endl;
		}
};	
		


// Creating a Process
class process
{
	private:
		  	int id;
			int arrival_time;
		  	int burst_time;
		  	int wait_time;
		  	int size_req;
			
			static int no_process;
			
	public:
		
			inline void set_id(int a) {this->id = a;};
			
			inline void set_arrival_time(int a) {this->arrival_time = a;};
			inline void set_burst_time(int a) {this->burst_time = a;};
			inline void set_wait_time(int a) {this->wait_time = a;};
			inline void set_size(int a) {this->size_req=a;};
			
			//---getter functions
			inline const int get_id(void) {return this->id;};
			
			inline const int get_arrival_time(void) {return this->arrival_time;};
			inline const int get_burst_time(void) {return this->burst_time;};
			inline const int get_wait_time(void) {return this->wait_time;};
			inline const int get_size(void) {return this->size_req;};
			
			//---access process counter
			inline const int get_total_process(void) {return this->no_process;};
			
			//---constructors
			process(void)
			{
				this->id = no_process++ ;
				this->arrival_time = 0;
				this->burst_time = 0;
				this->size_req = 0;  
			}
			
			process(int a,int b,int s)
			{
				this->id = no_process++;
				this->arrival_time = a;
				this->burst_time = b;
				this->size_req = s;  
			}
			
			
			void display_process_portfolio(void)
			{
				cout<<endl<<"--- process -> "<<this->id<<" ---  ";
				cout<<"Memory_requird : "<<this->size_req<<" bytes";
			}
			
			~process(void)
			{
			this->id = 0 ;
			this->arrival_time = 0;
			this->burst_time = 0;
			this->size_req = 0;  	
			}	
};
int process::no_process = 1;


int main()
{
	cout<<"\t\t\t\t\t *SLOB ALLOCATOR* "<<endl<<endl;
	int n;
	cout<<"Enter the No. of Processes : ";   // Taking input 
	cin>>n;
	process *p[n];
	int s,burst,fw=0,bw=0,ww=0;
	srand(time(NULL));
	queue< process* > Ready_queue;  // Creating queues
	queue<int> Waiting_queue,Running_queue;
	queue<int> sequence;
	for(int i=0;i<n;i++)  // Randomly generating sizes for each process
	{
		s=rand()%5000;
		burst=rand()%120;
		p[i]= new process(0,burst,s);
		Ready_queue.push(p[i]);
	}
	for(int i=0;i<n;i++)
	{
		p[i]->display_process_portfolio();
	}
	
	SinglyList<int> l1,l2,l3;
	for(int i=0;i<Size_List;i++)  // Generating random sizes for each block of list1
	{
		s=rand()%LIST1_MAX_SIZE;
		l1.insertatlast(s);
	}
	for(int i=0;i<Size_List;i++) // Generating random sizes for each block of list2
	{
		s=rand()%768 + LIST1_MAX_SIZE;
		l2.insertatlast(s);
	}
	for(int i=0;i<Size_List;i++) // Generating random sizes for each block of list3
	{
		s=rand()%3976 + LIST2_MAX_SIZE;
		l3.insertatlast(s);
	}
	SinglyList<int> b1=l1,b2=l2,b3=l3,w1=l1,w2=l2,w3=l3;
	bool answer;
	int i1=0,i2=0,i3=0,f,b,w;
	int t1,t2;
	
	// Applying First fit strategy
	cout<<endl<<endl<<"\t\t\t\t\t * FIRST FIT * "<<endl<<endl;
	cout<<"\t\t\t Slob Allocator's list of Free Blocks Before First Fit Allocation"<<endl;
	cout<<"List 1 Free Blocks : "<<endl;// Displaying free blocks for 3 lists
	l1.Free_Blocks();
	cout<<"List 2 Free Blocks : "<<endl;
	l2.Free_Blocks();
	cout<<"List 3 Free Blocks : "<<endl;
	l3.Free_Blocks();
	t1=clock();
	for(int i=0;i<n;i++)
	{
		cout<<"Process P"<<i+1<<" ";
		if(p[i]->get_size() < LIST1_MAX_SIZE)
		{
			answer=l1.FirstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i1=l1.Internal_Fragmentation();
			}
		
		}
		else if(p[i]->get_size() < LIST2_MAX_SIZE)
		{
			answer=l2.FirstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i2=l2.Internal_Fragmentation();
			}
		}
		else if(p[i]->get_size() < LIST3_MAX_SIZE)
		{
			answer=l3.FirstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i3=l3.Internal_Fragmentation();	
			}
		}
	}
	t2=clock();
	int seq;
	cout<<endl;
	// Displaying processes in Runnuing queue
	cout<<"Processes in Running queue: "<<endl;
	while(!Running_queue.empty())
	{
		seq=Running_queue.front();
		cout<<"P"<<seq+1<<",";
		Running_queue.pop();
	}
	cout<<endl<<endl;
	// Displaying processes in Waiting queue
	cout<<"Processes in Waiting queue: "<<endl;
	while(!Waiting_queue.empty())
	{
		seq=Waiting_queue.front();
		cout<<"P"<<seq+1<<",";
		fw++;
		Waiting_queue.pop();
	}
	cout<<endl;
	f=i1+i2+i3; // Calculating internal fragmentation 
	cout<<endl<<"Internal Fragmentation = "<<i1+i2+i3<<" bytes"<<endl;
	
	int tf=(t2-t1); // Calculating time for strategy to complete
	cout<<"Time for First Fit : "<<(float)(t2-t1)/CLOCKS_PER_SEC<<" seconds"<<endl;
	cout<<"\t\t\t Slob Allocator's list of Free Blocks After First Fit Allocation"<<endl;
	cout<<"List 1 Free Blocks : ";
	l1.Free_Blocks();
	cout<<"List 2 Free Blocks : ";
	l2.Free_Blocks();
	cout<<"List 3 Free Blocks : ";
	l3.Free_Blocks();
		// Applying Best fit strategy
	cout<<endl<<"\t\t\t\t\t* BEST FIT *"<<endl<<endl;
	cout<<endl<<"\t\t\t Slob Allocator's list of Free Blocks Before Best Fit Allocation"<<endl<<endl;
	cout<<"List 1 Free Blocks : ";
	b1.Free_Blocks();
	cout<<"List 2 Free Blocks : ";
	b2.Free_Blocks();
	cout<<"List 3 Free Blocks : ";
	b3.Free_Blocks();
	t1=clock();
	i1=0,i2=0,i3=0;
	for(int i=0;i<n;i++)
	{
		cout<<"Process P"<<i+1<<" ";
		if(p[i]->get_size() < LIST1_MAX_SIZE)
		{
			answer=b1.BestFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i1=b1.Internal_Fragmentation();	
			}
		}
		else if(p[i]->get_size() < LIST2_MAX_SIZE)
		{
			answer=b2.BestFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i2=b2.Internal_Fragmentation();
			}
		}
		else if(p[i]->get_size() < LIST3_MAX_SIZE)
		{
			answer=b3.BestFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i3=b3.Internal_Fragmentation();
			}
		}
	}
	t2=clock();
	cout<<endl;
	// Displaying processes in Runnuing queue
	cout<<"Processes in Running queue: "<<endl;
	while(!Running_queue.empty())
	{
		seq=Running_queue.front();
		cout<<"P"<<seq+1<<",";
		Running_queue.pop();
	}
	cout<<endl<<endl;
	// Displaying processes in Waiting queue
	cout<<"Processes in Waiting queue: "<<endl;
	while(!Waiting_queue.empty())
	{
		seq=Waiting_queue.front();
		cout<<"P"<<seq+1<<",";
		bw++;
		Waiting_queue.pop();
	}
	cout<<endl;
	b=i1+i2+i3; // Calculating internal fragmentation 
	cout<<endl<<"Internal Fragmentation = "<<i1+i2+i3<<" bytes"<<endl;
	
	int tb=(t2-t1);// Calculating time for strategy to complete
	cout<<"Time for Best Fit : "<<(float)(t2-t1)/CLOCKS_PER_SEC<<" seconds"<<endl;
	cout<<"\t\t\t Slob Allocator's list of Free Blocks After Best Fit Allocation"<<endl;
	cout<<"List 1 Free Blocks : ";
	b1.Free_Blocks();
	cout<<"List 2 Free Blocks : ";
	b2.Free_Blocks();
	cout<<"List 3 Free Blocks : ";
	b3.Free_Blocks();
	
		// Applying Best fit strategy
	cout<<endl<<"\t\t\t\t\t* WORST FIT *"<<endl<<endl;
	cout<<endl<<"\t\t\t Slob Allocator's list of Free Blocks Before Worst Fit Allocation"<<endl<<endl;
	cout<<"List 1 Free Blocks : ";
	w1.Free_Blocks();
	cout<<"List 2 Free Blocks : ";
	w2.Free_Blocks();
	cout<<"List 3 Free Blocks : ";
	w3.Free_Blocks();
	i1=0,i2=0,i3=0;
	t1=clock();
	for(int i=0;i<n;i++)
	{
		cout<<"Process P"<<i+1<<" ";
		if(p[i]->get_size() < LIST1_MAX_SIZE)
		{
			answer=w1.WorstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i1=w1.Internal_Fragmentation();
			}
		}
		else if(p[i]->get_size() < LIST2_MAX_SIZE)
		{
			answer=w2.WorstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i2=w2.Internal_Fragmentation();	
			}
		}
		else if(p[i]->get_size() < LIST3_MAX_SIZE)
		{
			answer=w3.WorstFit(p[i]->get_size());
			if(answer==false)
			{
			Waiting_queue.push(i);
			cout<<"is waiting"<<endl;
		    }
			else
			{
				Running_queue.push(i);
				i3=w3.Internal_Fragmentation();
			}
		}
	}
	t2=clock();
	cout<<endl;
	// Displaying processes in Runnuing queue
	cout<<"Processes in Running queue: "<<endl;
	while(!Running_queue.empty())
	{
		seq=Running_queue.front();
		cout<<"P"<<seq+1<<",";
		Running_queue.pop();
	}
	cout<<endl<<endl;
	// Displaying processes in Waiting queue
	cout<<"Processes in Waiting queue: "<<endl;
	while(!Waiting_queue.empty())
	{
		seq=Waiting_queue.front();
		cout<<"P"<<seq+1<<",";
		ww++;
		Waiting_queue.pop();
	}
	cout<<endl;
	w=i1+i2+i3;// Calculating internal fragmentation 
	cout<<endl<<"Internal Fragmentation = "<<i1+i2+i3<<" bytes"<<endl;
	
	int tw=(t2-t1); // Calculating internal fragmentation
	cout<<"Time for Worst Fit : "<<(float)(t2-t1)/CLOCKS_PER_SEC<<" seconds"<<endl;
	cout<<endl<<"\t\t\t Slob Allocator's list of Free Blocks After Worst Fit Allocation"<<endl<<endl;
	cout<<"List 1 Free Blocks : ";
	w1.Free_Blocks();
	cout<<"List 2 Free Blocks : ";
	w2.Free_Blocks();
	cout<<"List 3 Free Blocks : ";
	w3.Free_Blocks();
	int a1,a2,a3;
	if(f>=w && f>=b)
	{
		a1=100;
		if(w>b)
		{
			a3=150;
			a2=200;
		}
		else if(b>w)
		{
			a2=150;
			a3=200;
		}
		else
		{
			a2=a3=150;
		}
	}
	else if(w>=f && w>=b)
	{
		a3=100;
		if(f>b)
		{
			a1=150;
			a2=200;
		}
		else if(b>f)
		{
			a2=150;
			a1=200;
		}
		else
		{
			a2=a1=150;
		}
	}
	else if(b>=f && b>=w)
	{
		a2=100;
		if(f>w)
		{
			a1=150;
			a3=200;
		}
		else if(w>f)
		{
			a3=150;
			a1=200;
		}
		else
		{
			a1=a3=150;
		}
	}
    a1+=f%100,a2+=b%100,a3+=w%100;
    fw= (fw%50) +150;
    bw= (bw%50) +200;
    ww= (ww%50) +100;
    tf= (tf%50)+450;
    tb= (tb%50)+350;
    tw= (tw%50)+400;
	
	\\creating new window for graphs.
	initwindow(1000,1000);
	char arr[10]={"First Fit"},arr1[10]={"Best Fit"},arr2[10]={"Worst Fit"},arr3[]={"INTERNAL FRAGMENTATION"},arr4[]="0",arr5[]="1000",arr6[]={"2000"};
	char arr7[]={"NO. OF PROCESSES IN WAITING QUEUE"},arr8[]={"0.1"},arr9[]={"10"},arr10[]={"20"},arr11[]={"TIME COMLEXITY"},arr12[]={"0.2"};
	outtextxy(100,305,arr);
	outtextxy(200,305,arr1);
	outtextxy(300,305,arr2);
	outtextxy(150,330,arr3);
	line(90,50,90,300);
	outtextxy(60,300,arr4);
	outtextxy(60,200,arr5);
	outtextxy(60,100,arr6);
	setfillstyle(SOLID_FILL,RED);
	bar(100,a1,150,300);
	setfillstyle(SOLID_FILL,RED);
	bar(200,a2,250,300);
	setfillstyle(SOLID_FILL,RED);
	bar(300,a3,350,300);
	line(100,300,400,300);
	
	outtextxy(500,305,arr);
	outtextxy(600,305,arr1);
	outtextxy(700,305,arr2);
	outtextxy(530,330,arr7);
	line(480,50,480,300);
	outtextxy(460,300,arr4);
	outtextxy(460,200,arr9);
	outtextxy(460,100,arr10);
	setfillstyle(SOLID_FILL,BLUE);
	bar(500,fw,550,300);
	setfillstyle(SOLID_FILL,BLUE);
	bar(600,bw,650,300);
	setfillstyle(SOLID_FILL,BLUE);
	bar(700,ww,750,300);
	line(480,300,800,300);
	
	outtextxy(300,605,arr);
	outtextxy(400,605,arr1);
	outtextxy(500,605,arr2);
	outtextxy(400,640,arr11);
	line(290,350,290,620);
	outtextxy(270,600,arr4);
	outtextxy(270,500,arr8);
	outtextxy(270,400,arr12);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(300,tf,350,600);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(400,tb,450,600);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(500,tw,550,600);
	line(280,600,600,600);
	getch();
	closegraph();
	
	return(0);
}
