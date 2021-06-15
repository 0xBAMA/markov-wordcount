#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <random>

std::map<std::string, std::map<std::string, int>> model;
std::ifstream in;

void countWords() 
{
    std::string curr, prev;
    in >> curr;
    
    do  //create the model 
    {   ++model[prev][curr];
        prev=curr;
    }while(in >> curr);
}       


void spew(int count)
{
    int num = model.size();
    int run;
    
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dis(0, num-1);

    dis.reset();

    run = dis(gen);

    std::string curr;

    for(std::map<std::string, std::map<std::string, int>>::iterator p = model.begin(); p != model.end() && run > 0; ++p, --run)
    {
        curr = p->first;
    }

    std::cout << std::endl << std::endl;
    
    while(--count)
    {
        //where should you go? very similar to above, but with fewer entries in the map
        std::vector<std::string> where_to;
        where_to.clear();

        std::string temp = curr;
        for(std::map<std::string,int>::iterator p = model[temp].begin(); p != model[temp].end(); p++)
            for(int i = 0; i < p->second; i++)
                where_to.push_back(p->first);

        std::uniform_int_distribution<int> inner_dis(0, where_to.size()-1);
        inner_dis.reset();

        curr = where_to[inner_dis(gen)];

        std::cout << curr << " ";
    }

    std::cout << std::endl;
}


int main(int argc, char** argv) 
{
    if(argc < 2) 
        return(EXIT_FAILURE);
    
    in.open(argv[1]);

    if(!in.is_open()) 
        return(EXIT_FAILURE);

    //stream is good, read it
    countWords();

    //report results
    for(std::map<std::string, std::map<std::string, int>>::iterator p = model.begin(); p != model.end(); ++p)
    {
        int total_count = 0;

        for(std::map<std::string, int>::iterator q = model[p->first].begin(); q!=model[p->first].end(); ++q)
            total_count += q->second;
        
        std::cout << "\'"<< p->first << "\' has " << total_count << " occurrence(s)." << std::endl;

        for(std::map<std::string, int>::iterator q = model[p->first].begin(); q!=model[p->first].end(); ++q)
            std::cout << "  followed by: \'" << q->first << "\' " << q->second << " time(s)." << std::endl; 
    }

    spew(atoi(argv[2]));
}
