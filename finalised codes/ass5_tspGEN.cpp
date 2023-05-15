#include<bits/stdc++.h>
using namespace std;
set<vector<int>>st;
vector<vector<int>> population;
int bestDistance_sofar=INT_MAX,generation_number=1;
vector<int> thatBestFar;
void displayTheBest(int best,vector<int>best_path){
       cout<<endl;
       cout<<"-----------------------------------------------------------"<<endl;
       cout<<"Generation Number "<<generation_number++<<endl;
       cout<<"The Best Distance achieved so far "<<best<<endl;
       for(int it:best_path){
          cout<<it<<"->";
       }
       cout<<endl;
       cout<<"-----------------------------------------------------------"<<endl;
}
vector<int> getPopulationShuffled(int n){
    vector<int>v(n),f(n,0),v1(n+1);
    iota(v.begin(),v.end(),0);
    int index;
    f[0]=1;
    for(int i=1;i<n;i++){
         do{
           index=rand()%(n);
        }while(f[index]!=0);
        f[index]=1;
        v1[i]=v[index];
    } 
    return v1;
}
void make_population(){
    int times=200;
    while(times--){
        vector<int>tmp;
        tmp=getPopulationShuffled(10);
        st.emplace(tmp);
    }
    for(auto it:st){
        population.push_back(it);
    }
}
vector<vector<int>> doCrossOvers(vector<int>&p1,vector<int>&p2){
    vector<vector<int>>container_for_parents;
    unordered_set<int>st_for_p1,st_for_p2;
    int n=p1.size();
    p1.erase(p1.begin());
    p1.pop_back();
    p2.erase(p2.begin());
    p2.pop_back();
   
    int k=2;
    vector<int>te1(p1.begin()+0,p1.begin()+k);
    vector<int>te2(p2.begin()+0,p2.begin()+k);
    for(int i=0;i<te1.size();i++){
            st_for_p1.insert(te1[i]);
            st_for_p2.insert(te2[i]);
    }

    for(int i=0;i<p1.size();i++){
        if(st_for_p1.count(p2[i])==0){
            te1.push_back(p2[i]);
        }
         if(st_for_p2.count(p1[i])==0){
            te2.push_back(p1[i]);
         }
    }
    te1.insert(te1.begin(),0);
    te1.push_back(0);
    te2.insert(te2.begin(),0);
    te2.push_back(0);
    container_for_parents.push_back(te1);
    container_for_parents.push_back(te2);
    return container_for_parents;
}
void mutate(vector<int> &child, double mutationRate)
{
    vector<int>indexes={1,2,3,4,5,6,7,8,9};
    for (int i = 1; i < child.size()-1; i++)
    {
        if ((float)rand() / RAND_MAX < mutationRate)
        {
            int randIdx = rand() % indexes.size();
            swap(child[i], child[indexes[randIdx]]);
        }
    }
}

int rouletteWheel(vector<float>&cumalative){
  float random_num=(float)rand() / RAND_MAX ;
    int index_for_mutation=0;
    for(int i=0;i<cumalative.size()-1;i++){
    if(cumalative[i]<=random_num && cumalative[i+1]>=random_num){
            index_for_mutation=i;
            return i;
    }
  }
  return 0;
}
void crossOverAndMutations( vector<vector<int>>&population,vector<float>&cumalative){

  vector<vector<int>> new_population(population.size()); 
  int currIdx=0;
  while(currIdx!=population.size()){
  int index_for_mutation=rouletteWheel(cumalative);
  int index_for_mutation1=rouletteWheel(cumalative);
  vector<int> p1=population[index_for_mutation];
  vector<int>p2=population[index_for_mutation1];
  float crossover_rate=0.80,mutation_rate=0.05;
  float value_for_mutation=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 if(value_for_mutation<crossover_rate){
    vector<vector<int>>tmp=doCrossOvers(p1,p2);
      mutate(tmp[0],mutation_rate);
     mutate(tmp[1],mutation_rate);
      new_population[currIdx++]=tmp[0];
      new_population[currIdx++]=tmp[1];
  }
  else{
   new_population[currIdx++]=p1;
  new_population[currIdx++]=p2;
  }
  }
  population=new_population;
}
vector<float>getFitnessandNormalized(const vector<vector<int>>&dist){
     vector<int>fitnessVals;
    for(int i=0;i<population.size();i++){
        int ans=0;
        for(int j=0;j<population[0].size()-1;j++){
            int tmp=dist[population[i][j]][population[i][j+1]];
            ans+=tmp;
        }
        if(ans<bestDistance_sofar){
            bestDistance_sofar=ans;
            thatBestFar=population[i];
        }
        fitnessVals.push_back(ans);
    }

    vector<double>nor;
    for(int it:fitnessVals){
        nor.push_back((float)1/it);
    }
    float totalOfnorm=accumulate(nor.begin(),nor.end(),0.0000);
    for(int i=0;i<nor.size();i++){
        nor[i]=(float)nor[i]/(float)totalOfnorm;
    }
    float one=accumulate(nor.begin(),nor.end(),float(0.0000));
    vector<float>cumalative(nor.size());
    cumalative[0]=nor[0];
    for(int i=1;i<nor.size();i++){
        cumalative[i]=nor[i]+cumalative[i-1];
    }
  displayTheBest(bestDistance_sofar,thatBestFar);
  return cumalative;
}
int main(){
   
    srand(time(0));
    make_population();
    vector<vector<int>> input = {
        {INT_MAX, 20, 30, 10, 11, 15, 13, 2, 12, 1},
        {15, INT_MAX, 16, 4, 2, 20, 1, 7, 18, 11},
        {3, 5, INT_MAX, 2, 4, 9, 21, 8, 9, 14},
        {19, 6, 18, INT_MAX, 3, 10, 9, 20, 15, 21},
        {16, 4, 7, 16, INT_MAX, 19, 1, 13, 11, 2},
        {1, 14, 8, 12, 20, INT_MAX, 2, 9, 13, 10},
        {5, 12, 9, 4, 8, 22, INT_MAX, 12, 19, 22},
        {19, 13, 5, 13, 11, 31, 8, INT_MAX, 11, 6},
        {13, 29, 17, 6, 9, 15, 7, 13, INT_MAX, 24},
        {6, 14, 9, 26, 29, 13, 3, 21, 12, INT_MAX},

    };
    cout<<endl;
    int maxGenerations=30;
    while(maxGenerations--){
    vector<float>cumalative=getFitnessandNormalized(input);
    crossOverAndMutations(population,cumalative);
    }
}
