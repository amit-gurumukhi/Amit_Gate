// #include<iostream>
#include<bits/stdc++.h>
using namespace std;
static int Cap=11;
void knapsack(int capacity,int profit[],int weight[],int no_of_objects){
    int i=0;
    int j=0;
    int ks[no_of_objects+1][capacity+1];
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<=no_of_objects; i++){
        for(int j=0; j<=capacity; j++){
            if(i==0||j==0){
                ks[i][j]=0;
            }
            else if(weight[i-1]>j){
                ks[i][j]=ks[i-1][j];
            }
            else{
                ks[i][j]=max(profit[i-1]+ks[i-1][j-weight[i-1]],ks[i-1][j]);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    cout<<"knapsack array: "<<endl;
    for(int i=0; i<=no_of_objects; i++){
        for(int j=0; j<=capacity; j++){
            cout<<ks[i][j]<<" ";
        }
        cout<<endl;
    }
    //tracing elements..
    i=no_of_objects;
    j=capacity;
    int trace[no_of_objects];
    while(i>0||j>0){
        if(ks[i][j]==ks[i-1][j]){
            trace[i-1]=0;
            i--;
        }
        else{
            trace[i-1]=1;
            i--;
            j=j-weight[i];
        }
    }
    cout<<"tracing elements: "<<endl;
    for(int i=0; i<no_of_objects; i++){
        cout<<trace[i]<<" ";
    }
    cout<<endl;
    cout<<"max value using dynamic programming: "<< ks[no_of_objects][capacity]<<endl;
    cout << "execution time using dynamic programming: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds"<<endl ;
    
}

int knapsack_recursion(int no_of_objects,int capacity, int weight[],int profit[]){
    if(no_of_objects ==0 || capacity ==0){
        return 0;
    }
    else if(weight[no_of_objects-1]>capacity){
        return knapsack_recursion(no_of_objects-1, capacity,weight,profit);
    }
    else{
        return max(profit[no_of_objects-1]+knapsack_recursion(no_of_objects-1,capacity-weight[no_of_objects-1],weight,profit),knapsack_recursion(no_of_objects-1, capacity,weight,profit));
    }
}


int main(){
    int capacity=6;
    int profit[]={20,30,40,50};
    int weight[]={2,3,4,5};
    int n=4;  //number of the objects.   
    knapsack(capacity,profit,weight,n);      //knapsack using dynamic programming algorithm.
    auto start1 = chrono::high_resolution_clock::now();
    cout<<"max value using recursion: "<<knapsack_recursion(n,capacity,weight,profit)<<endl; // knapsack using recursion.
    auto end1 = chrono::high_resolution_clock::now();   
    cout << "execution time using recursion: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " nanoseconds" << endl;
    return 0;
}
