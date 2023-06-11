//Defining header file for smith counter
#ifndef SMITHCOUNTER_H
#define SMITHCOUNTER_H
#include<vector>
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
using namespace std;

//Class for smithcounter
class smithCounter{
  private: int counterValue[32];
  public: smithCounter(){
     for(int i=0;i<32;i++) counterValue[i]=0;
  }
  //This function are used to update the counter value
  public: void updateCounter(int index,int value);
  //This function is used to get the array of counter values
  public: int* getCounterValue();
  //Declaration of the function readData which helps to read data from the trace file
  public: void readData(vector<string>&,vector<string>&,char*);
  //Declaration of the smithcounter simulation Function
  public: void smithSimulation(vector<string>,vector<string>);
};

//This function updates counter value based on prediction
void smithCounter:: updateCounter(int index,int value){
  if(counterValue[index]<3 && counterValue[index]>-1 && value==1)
    counterValue[index] +=value;
  if(counterValue[index]<=3 && counterValue[index]>0 && value==-1)
    counterValue[index] +=value;
}
//Function defination of getCounterValue
int * smithCounter:: getCounterValue(){
  return counterValue;
}
//Defination of the function readData
void smithCounter:: readData(vector<string>&branchAddress,vector<string>&actualPrediction,char*fileName){
  string line;
  string temp1 , temp2;
  //variables declrations
  fstream fout;
  //It will ask for the argument during the execution argument= location of file
  fout.open(fileName);
  //Reading the data from the data file
  while(fout){
    getline(fout,line);
    if(line!=""){
      std::stringstream ss(line);
      ss>>temp1;
      ss>>temp2;
      branchAddress.push_back(temp1);
      actualPrediction.push_back(temp2);
    }
  }
}
//Defination of function smithSimulation
void smithCounter:: smithSimulation(vector<string>branchAddress,vector<string>actualPrediction){
  //Variables declaration
  int index,
      notTaken=0,
      taken=0,
      takenCorrect=0,
      notTakenCorrect=0,
      totalBranches=0,instruction;

  //this loops simulates smith counter and does the branch prediction
  for( int i=0;i<branchAddress.size();i++){
    //This line converts the value into binary value
    std::string binary = std::bitset<16>(stoi(branchAddress[i])).to_string();
	  index = stoi(binary.substr( 9,5),0,2);
    //If the counter value is less than 2 then predict it as not taken
    if(counterValue[index]==0||counterValue[index]==1){
      if(actualPrediction[i]=="T"){
        updateCounter(index,1);
      }
      else{
        updateCounter(index,-1);
        notTakenCorrect++;
      }
    }
    //If the counter value is greater or equal to 2 predict as taken
    else {
      if(actualPrediction[i]=="T"){
        updateCounter(index,1);
        takenCorrect++;
      }
      else{
        updateCounter(index,-1);
      }
    }
    if(actualPrediction[i]=="T")taken++;
    if(actualPrediction[i]=="N")notTaken++;
    totalBranches++;
  }
  //Printing out the results that we got from the loop
  cout<<"Number of branches: "<<totalBranches<<endl;
  cout<<"Number of branches taken: "<<taken<<endl;
  cout<<"Number taken branches correctly predicted: "<<takenCorrect<<endl;
  cout<<"Number of branches not taken: "<<notTaken<<endl;
  cout<<"Number not taken branches correctly predicted: "<<notTakenCorrect<<endl;
  cout<<"Overall rate of correct predictions: "<<((takenCorrect+notTakenCorrect)/(float)totalBranches)*100.00<<"%"<<endl;
}

#endif  //End of smithCounter
