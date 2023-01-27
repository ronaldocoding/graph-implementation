#include <iostream>
#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int> >  adj_list[7];  

vector<bool> visited(7,false);  

vector<int> connection(7,-1);  

vector<int> value(7, INT_MAX); 

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que; 

void prims() {
    que.push(make_pair(0, 1));  
    
    value[1]=0;                  
    while (!que.empty()) {      
        int node = que.top().second;  
        visited[node] = true;         
        que.pop();                    
        for (auto neighbor : adj_list[node]) {   
            int weight = neighbor.second;        
            int vertex = neighbor.first;         

            if (!visited[vertex] && value[vertex] > weight) {   
                value[vertex] = weight;                         
                connection[vertex] = node;
                que.push(make_pair(value[vertex], vertex));     
            }
        }
    }
}

void print_graph() {
    for (int i = 2; i < 7; ++i)
        printf("%d - %d\n", connection[i], i);  
}

void makegraph(int m, int n, int wght) {
    adj_list[m].push_back(make_pair(n, wght));    
    adj_list[n].push_back(make_pair(m, wght));     
}

int main() {
    makegraph(5, 4, 5);   
    makegraph(5, 1, 3);   
    makegraph(1, 2, 3);   
    makegraph(1, 4, 7);   
    makegraph(2, 5, 11);  
    makegraph(6, 4, 1);   
    makegraph(5, 6, 7);   
    makegraph(3, 1, 3);   
    makegraph(3, 2, 7);   

    prims();              
    print_graph();        

    return 0;
}