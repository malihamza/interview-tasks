#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<thread> 
#include <mutex>
#include<string>

std::mutex g_mutex;

using namespace std;
class Operation
{
public:
    string operator_task;
    float operand1;
    float operand2;

    Operation(string op,string op1,string op2)
    {
        this->operator_task = op;
        this->operand1 = stof(op1);
        this->operand2 = stof(op2);
    }

    void operator()() 
    {        
        std::lock_guard<std::mutex> guard(g_mutex);
        if(operator_task=="add")
        {
            cout<<operand1<<"+"<<operand2<<"="<<operand1+operand2<<"\n";
        }
        else if(operator_task=="sub")
        {
            cout<<operand1<<"-"<<operand2<<"="<<operand1-operand2<<"\n";
        }
        else if(operator_task=="mul")
        {
            cout<<operand1<<"*"<<operand2<<"="<<operand1*operand2<<"\n";
        }
        else if(operator_task=="div")
        {
            cout<<operand1<<"/"<<operand2<<"="<<operand1/operand2<<"\n";
        }
    }
};
vector<string> read_record() 
{ 
  
    fstream fin; 
  
    fin.open("input.csv", ios::in); 
  
    vector<string> tokenized_data; 
    string temp; 
    fin >> temp;
  
    while (fin >> temp) 
    { 
        
        stringstream ss(temp); 
        string temp_str;

        while(getline(ss, temp_str, ','))
        { 
            tokenized_data.push_back(temp_str);
        }
        
    } 

    return tokenized_data;
} 
void execute_and_tokenized_data_stores_in_csv(Operation operation)
{

}
int main()
{


    vector<string> tokenized_data = read_record();
    vector<thread> threads;

    for(int i=0;i<tokenized_data.size()-2;i+=3)
    {   
        
        Operation oper(tokenized_data[i],tokenized_data[i+1],tokenized_data[i+2]);
        threads.push_back(thread(oper));
    }
    for(auto& t: threads)
    {
        if(t.joinable())
            t.join();

    }   
   

    return 0;
}