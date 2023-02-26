#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct openListNode{
    int label;
    int f;
    int g;
};

class Graph{
    vector< vector< pair<int, int> > > grp;
    vector<int> hueristic;
    int nodes;
    int edges;
    public:
    Graph(){ nodes = 0;}
    Graph(int, int);
    void initGraph();
    void drawGraph();
    int AStar(int, int);
};

Graph :: Graph(int n, int e){
    nodes = n;
    edges = e;

    for(int i = 0; i < n; i++){
        vector< pair<int, int> > temp;
        grp.emplace_back(temp);
    }
}

void Graph :: initGraph(){
    int n1 = 0, n2 = 0, cost = 0;
    char isDirected = 'n';
    cout<<"Is graph directed: (y/n ?)";
    cin>>isDirected;

    for(int i = 0; i < edges; i++){
        if(isDirected == 'y')
            cout<<"enter src des ('0 indexed') cost: ";
        else
            cout<<"enter n1 n2 ('0 indexed') cost: ";
        
        cin>>n1>>n2>>cost;
        pair<int, int> pr;
        pr.first = n2;
        pr.second = cost;
        grp[n1].emplace_back(pr);

        if(isDirected == 'n'){
            pr.first = n1;
            grp[n2].emplace_back(pr);
        }
    }

    int val = 0;
    for(int i = 0; i < nodes; i++){
        cout<<"enter h("<<i<<"): ";
        cin>>val;
        hueristic.emplace_back(val);
    }
}

void Graph :: drawGraph(){
    for(int i = 0; i < nodes; i++){
        cout<<i<<" :";
        for(auto n : grp[i])
            cout<<" <"<<n.first<<", "<<n.second<<">";
        cout<<endl;
    }
    
    for(int i = 0; i < nodes; i++){
        cout<<i<<": "<<hueristic[i]<<endl;
    }
}

int Graph :: AStar(int startNode, int goalNode){

    auto cmp = [](openListNode n1, openListNode n2){
        return n1.f < n2.f;
    };

    vector<openListNode> openList;
    vector<int> closeList(nodes, 0);

    int minimumCost = 0;
    openListNode currentNode;
    currentNode.label = startNode;
    currentNode.g = 0;
    currentNode.f = hueristic[currentNode.label];

    openList.emplace_back(currentNode);

    while(openList.size() > 0){
        currentNode = openList[0];
        openList.erase(openList.begin());

        cout<<currentNode.label<<" "<<currentNode.g<<" "<<currentNode.f<<endl;
        
        if(currentNode.label != goalNode){

            for(auto pr : grp[currentNode.label]){
                
                if(closeList[pr.first] != 1){
                    openListNode newNode;
                    newNode.label = pr.first;
                    newNode.g = currentNode.g + pr.second;
                    newNode.f = newNode.g + hueristic[newNode.label];

                    openList.emplace_back(newNode); 
                }
            }

            closeList[currentNode.label] = 1;
            sort(openList.begin(), openList.end(), cmp);
        }

        else{
            minimumCost = currentNode.f;
            break;
        }

    }

    return minimumCost;
}

int main(){
    int nodes = 0, edges = 0;
    cout<<"Ente nodes and edges: ";
    cin>>nodes>>edges;
    Graph g1(nodes, edges);
    g1.initGraph();
    cout<<endl;
    g1.drawGraph();
    int startNode = 0, goalNode = 0;
    cout<<"Enter start and goal node: ";
    cin>>startNode>>goalNode; 
    cout<<"Ans: "<<g1.AStar(startNode, goalNode);
    
    return 0;
}