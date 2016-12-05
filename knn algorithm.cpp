#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

class node{
public:
    vector<int> dimension;//the multi_dimen data
    int classtype;//the class type
    float distance;//the distance between the test node and original node,varies
    node(){}
    node(const int &i,const vector<int> &_dimension)://arg-constructor
    classtype(i),
    dimension(_dimension),
    distance(0)
    {}
    bool operator < (const node &a) const//over-load the comparison function
    {
        return a.distance > distance;
    }
};


void input(const int &n,const int &numberOfDimension,vector<node> &dataset){//the input function
    for(int i=0;i<n;++i){
        vector<int> tmp;
        for(int j=0;j<numberOfDimension;++j){
            int cval;
            cin>>cval;
            tmp.push_back(cval);
        }
        dataset.push_back(node(i,tmp));
    }
}

float calculateDistance(const node &n1,const node &n2,const int &numberOfDimension){//calculated the distance
    int ans=0;
    for(int i=0;i<numberOfDimension;++i){
        ans+=pow(abs(n1.dimension[i]-n2.dimension[i]),2);
    }
    return sqrt(ans);
}

void classification(node &curNode,priority_queue<node> &cqueue,int n){
    float dict[n];
    memset(dict,0,sizeof(dict));
    while(!cqueue.empty()){
        dict[cqueue.top().classtype]+=1/cqueue.top().distance;//power it
        cqueue.pop();
    }
    int tmp=0;
    int key=0;
    for(int i=0;i<n;++i){
        if(dict[i]>=tmp){
            tmp=dict[i];
            key=i;
        }
    }
    curNode.classtype=key;
}
void KNN(const int &k,vector<node> &dataset,const int &numberOfDimension){//the major algorithm
    for(int i=0;i<dataset.size();++i){
        priority_queue<node> cqueue;
        for(int j=0;j<dataset.size();++j){
            dataset[j].distance=calculateDistance(dataset[i],dataset[j],numberOfDimension);//calculate the distance of every node to the current node
        }
        for(int j=0;j<dataset.size();++j){//implement the priority queue
            if(j==i) continue;
            if(cqueue.size()<k){
                cqueue.push(dataset[j]);
            }
            else{
                if(dataset[j].distance<cqueue.top().distance){
                    cqueue.pop();
                    cqueue.push(dataset[j]);
                }
            }
        }
        classification(dataset[i],cqueue,int(dataset.size()));//classify the current node
    }
}

void show(vector<node> &dataset){//show the different class
    map<int , vector<int> > mydict;//the dictionary to store the different class
    for(int i=0;i<dataset.size();++i){
        mydict[dataset[i].classtype].push_back(i);
    }
    for(auto it=mydict.begin();it!=mydict.end();++it){
        cout<<"same class :";
        for(auto i:it->second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int n,k,numberOfDimension;
    cin>>n>>k>>numberOfDimension;
    vector<node> dataset;
    input(n, numberOfDimension, dataset);
    KNN(k, dataset, numberOfDimension);
    show(dataset);
}
