/*
  Name: Nirajan Acharya
  YID: Y00807637
  Course: Computer Architecture
  Project: Smith Branch Predictor
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include"smithCounter.h"
using namespace std;

int main(int argc,char ** argv){
  smithCounter  counter;
  vector<string> branchAddress;
  vector<string> actualPrediction;
  //This function reads branch address and actual prediction from branch_trace.dat file
  counter.readData(branchAddress,actualPrediction,argv[1]);
  //This function simulates as smith branch predictor
  counter.smithSimulation(branchAddress,actualPrediction);
  return 0;
}
//End of the program
