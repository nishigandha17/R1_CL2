#include<iostream>
#include<fstream>

using namespace std;

class node
{
	char name;
	node *next;
	bool visited;
public:
	friend class uninformed;
	node()
	{
		name=' ';
		next=NULL;
		visited=0;
	}
};

class uninformed
{
	node *nodesptr;
	ifstream fin;
public:
	uninformed();
	~uninformed();
	void BFSnodes();
	void DFScycle(int,int,int,char);
	int push(char[],char[],char,int*,int*,int*,int*);
	int search(char[],node *,int);
	void Clean();
};

uninformed::uninformed()
{
	nodesptr=new node[5];
	for(int i=0;i<5;i++)
		nodesptr[i].name=65+i;
	fin.open("assing1.txt",ios::in);
	char line[3];
	node *ptr;
	fin.getline(line,3);
	while(fin)
	{
		cout<<line<<"\n";
		ptr=&nodesptr[line[0]-65];
		while(ptr->next!=NULL)
			ptr=ptr->next;
		ptr->next=new node;
		ptr=ptr->next;
		ptr->name=line[1];
		ptr->next=NULL;

		ptr=&nodesptr[line[1]-65];
		while(ptr->next!=NULL)
			ptr=ptr->next;
		ptr->next=new node;
		ptr=ptr->next;
		ptr->name=line[0];
		ptr->next=NULL;
		fin.getline(line,3);
	}
	cout<<"\nDisplay\n";
	for(int i=0;i<5;i++)
	{
		ptr=&nodesptr[i];
		while(ptr!=NULL)
		{
			cout<<ptr->name<<"---";
			ptr=ptr->next;
		}
		cout<<"\n";	
	}
}

uninformed::~uninformed()
{
	delete[] nodesptr;
	fin.close();
}

void uninformed::BFSnodes()
{
	node *ptr;
	char visited[5];
	int attached[5];
	char queue[20];
	int start=0,end=0,hop=0,temp;
	int count=0,level=2,levelnext=0,nodeatt=0;
	char source[2],destination[2];
	cout<<"\nEnter source node=";
	cin>>source;
	cout<<"\nEnter destination node=";
	cin>>destination;
	for(int i=0;i<5;i++)
		attached[i]=0;
	if(source[0]==destination[0])
		hop=0;
	else
	{
		ptr=&nodesptr[source[0]-65];
		queue[end]=ptr->name;
		visited[count]=ptr->name;
		count++;
		while(start<=end)
		{
			temp=push(queue,visited,destination[0],&end,&start,&count,&nodeatt);
			attached[start]=nodeatt;
			nodeatt=0;
			if(temp==1)
			{
				int num=0;
				int num2=0,num3;
				for(int k=1;k<5;k++)
					num=num+attached[k];
					
				if(num==0)
				{
					cout<<"\nNo of hops=1\n";
					return;
				}
				num=attached[0];
				num3=num;
				while(num3!=0)
				{
					num3=0;
					for(int j=num;j>num2;j--)
						num3=num3+attached[j];
					num2=num;
					num=num3+num;
					hop++;					
				}
				//hop++;
				cout<<"\nNo of hops="<<hop<<"\n";
				for(int i=0;i<5;i++)
					cout<<attached[i]<<"\n";
				return;
			}
			else
			{
				start++;
			}
		}
		cout<<"\nNode not found\n";		
	}
	
}

int uninformed::push(char queue[],char visited[],char destination,int *end,int *start,int *count,int *nodeatt)
{
	node *ptr=&nodesptr[queue[*start]-65];
	ptr=ptr->next;
	while(ptr!=NULL)
	{
		int temp=search(visited,ptr,*count);
		if(temp==1)
		{	
			ptr=ptr->next;
			continue;
		}
		else
		{
			(*nodeatt)++;
			if(ptr->name==destination)
				return 1;
			else
			{
				(*end)++;
				queue[*end]=ptr->name;
				visited[*count]=ptr->name;
				(*count)++;
				ptr=ptr->next;
			}
		}
	}
	return 0;
}



int uninformed::search(char visited[],node *ptr,int count)
{
	for(int i=0;i<count;i++)
	{
		if(visited[i]==ptr->name)
			return 1;
	}
	return 0;
}

void uninformed::DFScycle(int nodeno,int count,int nodenum,char previous)
{
	static node *ptr;
	node *prev;
	if(count<5)
	{
		ptr=&nodesptr[nodeno];
		prev=ptr;
		count++;
		if(ptr->visited==1)
		{
			cout<<"\nCycle is present in the graph\n";
			return;
		}		
		else
		{
			ptr=ptr->next;
			while(ptr!=NULL)
			{
				while(ptr->visited!=0)
				{
					ptr=ptr->next;
					if(ptr==NULL)
						break;
				}
				if(ptr->name==previous)
				{
					ptr->visited=1;
					ptr=ptr->next;
					ptr->visited=1;
					nodeno=ptr->name-65;				
					DFScycle(nodeno,count,nodenum,previous);
				}
				else
				{
					ptr->visited=1;
					nodeno=ptr->name-65;				
					DFScycle(nodeno,count,nodenum,previous);
				}
			}
		}
		
	}
	else
	{
		nodenum++;
		DFScycle(nodenum,0,nodenum,'A');
	}
}

void uninformed::Clean()
{
	node *ptr;
	for(int i=0;i<5;i++)
	{
		ptr=&nodesptr[i];		
		while(ptr!=NULL)
		{
			ptr->visited=0;
			ptr=ptr->next;
		}
	}
}

int main()
{
int ch;
uninformed obj;
do{
	cout<<"\n\tTwo uninformed search methods\n";
	cout<<"1.No. of nodes reachable(BFS)\n"<<"2.Cycle in a graph(DFS)\n"<<"3.Exit\n";
	cout<<"Enter your choice=";
	cin>>ch;
	switch(ch)
	{
		case 1: obj.BFSnodes();
			break;
		case 2: obj.DFScycle(0,0,0,'A');
			obj.Clean();
			break;
		case 3:	cout<<"\nProgram exiting\n";
			break;
		default:
			cout<<"\nPlease enter correct choice\n";
	}
}while(ch!=3);
return 0;
}
