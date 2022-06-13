///Prims


#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<windows.h>
#include <vector>

using namespace std;



 class Lebel{

 private:
    int cost;
    int parent_field;
    bool flag;


  public:


      void set_cost(int x){

      cost=x;
      }


      void set_parent_field(int y){

      parent_field=y;
      }

      void set_flag(bool z){

      flag=z;
      }

      int get_cost(){
            return cost;
      }

      int get_parent_field(){
            return parent_field;
      }

      bool get_flag(){
            return flag;

      }

  };



///Prototypes
void create_graph(int** &, int );
void populate_graph(int** X,int s,int low,int high,int parcentage);
void display_graph(int** X,int s,int mx,int p);
int max(int *A, int n);
int max(int** X, int s);
int num_dig(int n);
void prim_s(int** G,int n);
int findMinVertex(Lebel* lebel,int n);
void print_path(Lebel* &lebel,bool& desicion,int n);


int main(){
   int **G;
   int n;
   int p;
   int low;
   int high;
   int s;
   int d;
   bool desicion=false;
   cout<<"Enter number of nodes :";
   cin>>n;
   create_graph(G,n);
   srand(time(0));
   p=50+rand()%(100+1-50);
   cout<<"Enter the lowest weight :";
   cin>>low;
   cout<<"Enter the highest weight :";
   cin>>high;
   populate_graph(G,n,low,high,p);
   display_graph(G,n,max(G,n),p);
   prim_s(G,n);
   system("pause");
   return 0;

}

void create_graph(int** &X, int sz){
	X =new int*[sz];
    for(int i = 0; i < sz; i++)
    X[i] = new int[sz];
}

void populate_graph(int** X,int s,int low,int high,int parcentage){

 int count=0;

 double edges=parcentage/100.0;
 int max_edges=(s*(s-1))/2;
 double estimated_edges=(parcentage*max_edges)/100.00;

 if((estimated_edges-(int)estimated_edges)>=0.50)estimated_edges=(int)estimated_edges+1;


 cout<<parcentage<<"% densely graph is creating..........";

 clock_t start;
 double duration;

 start = clock(); // get current time


 while(true){
   srand(time(0));
   for(int i=0;i<s;i++){
     for(int j=0;j<s;j++){
        if(j==i){
            X[i][j]=0;
        }

        else if(j<i){
            X[i][j]=X[j][i];
        }

        else if(j>i){
              double val=(double)rand()/RAND_MAX;
               if(val<=edges){
                        X[i][j] = low+rand()%(high+1-low);
                        count++;
            }
            else {
                X[i][j]=-1;
            }
        }

      }

    }

    if(count==(int)estimated_edges){

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    system("cls");
    cout << "Your graph generation took "<< duration << " seconds" <<endl;
    break;

       }
   count=0;

   }

}


int max(int** X, int s){
	int mx=X[0][0];
	for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
		if(X[i][j]>mx)mx=X[i][j];
	}
	}
	return mx;
}


int max(int *A, int n){
	int mx=A[0];
	for(int i=1;i<n;++i){
		if(A[i]>mx)mx=A[i];
	}
	return mx;
}


int num_dig(int n){
	if(n<10)return 1;
	return 1+num_dig(n/10);
}

void display_graph(int** X,int s,int mx,int p){
  cout<<endl;
  cout<<"This graph is "<<p<<" % dense"<<endl<<endl;
  for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
            cout<<setw(num_dig(mx)+2)<<X[i][j];
      }
      cout<<endl;
  }

}





void prim_s(int** G,int n){


bool desicion=false;
Lebel* lebel=new Lebel[n];
for(int i=0;i<n;i++){
    lebel[i].set_cost(-1);
    lebel[i].set_parent_field(-1);
    lebel[i].set_flag(false);
}

    lebel[0].set_cost(0);
    lebel[0].set_parent_field(0);
    lebel[0].set_flag(false);





for(int i =0; i<n; i++){
    int minVertex=findMinVertex(lebel,n);

     if(lebel[minVertex].get_cost()==-1 ){
        break;
    }

    lebel[minVertex].set_flag(true);
    for(int j=0;j<n;j++){
        if(G[minVertex][j]>0 && !lebel[j].get_flag()){
                if(G[minVertex][j]<lebel[j].get_cost() || lebel[j].get_cost()==-1){
                lebel[j].set_cost(G[minVertex][j]);
                lebel[j].set_parent_field(minVertex);
             }
        }
    }
}

print_path(lebel,desicion,n);

if (desicion==false){
    cout<<"Graph is disconnected"<<endl;
}

}

int findMinVertex(Lebel* lebel,int n){
        int minVertex=-1;

        for(int i=0;i<n;i++){
              if(!lebel[i].get_flag() && (minVertex==-1||(lebel[i].get_cost()>=0 && lebel[minVertex].get_cost()==-1) ||(lebel[i].get_cost()>=0 && lebel[minVertex].get_cost()>=0 && lebel[i].get_cost()<=lebel[minVertex].get_cost()))){
                minVertex=i;
            }
        }
        return minVertex;
}




void print_path(Lebel* &lebel,bool& desicion,int n){

  desicion=true;
  int cost=0;

  int a[n];///Parent Array
  int b[n];///Weight Array

  ///Populate a[n]
  for(int i=0;i<n;i++){
    a[i]=lebel[i].get_parent_field();
  }

  ///Populate b[n]
  for(int i=0;i<n;i++){
    b[i]=lebel[i].get_cost();
  }

  ///Calculating total cost
  for(int i=0;i<n;i++){
    cost=cost+lebel[i].get_cost();
  }
  cout<<endl;
  cout<<"Total cost= "<<cost<<endl<<endl;

  cout<<setw(num_dig(max(a,n))+5)<<"Vertex"<<setw(num_dig(max(a,n))+10)<<"Parent"<<setw(num_dig(max(b,n))+10)<<"Weight"<<endl;
  for(int i=0;i<n;i++){
    cout<<setw(num_dig(max(a,n))+2)<<i+1<<setw(num_dig(max(a,n))+10)<<lebel[i].get_parent_field()+1<<setw(num_dig(max(b,n))+10)<<lebel[i].get_cost()<<endl;
  }

}


