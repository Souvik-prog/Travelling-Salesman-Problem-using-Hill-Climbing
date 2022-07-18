#include <bits/stdc++.h>
using namespace std;

int  source = 0, num_cities = 10;

vector<int> random_solution(int t[][4])
{
    vector<int> cities;
    int i;

    for (i=0; i<num_cities; i++)
    {
        if (i != source)
            cities.push_back(i);
    }
    next_permutation(cities.begin(),cities.end());
    
    return cities;
}

int RouteLength(int t[][4], vector<int> c)
{
    int current_pathweight = 0;
    int k = source;

    for (int i = 0; i<c.size(); i++)
    {
        current_pathweight += t[k][c[i]];
        k = c[i];

    }
    current_pathweight += t[k][source];

    return current_pathweight;
}

vector<vector<int>> getNeighbours(vector<int> cities)
{
    int i, j;
    vector <vector<int>> neighbours; 
    vector<int> neighbour;

    for(i=0; i<cities.size(); i++)
    {
        for(j=(i+1); j<cities.size(); j++)
        {
            neighbour = cities;
            neighbour[i] = cities[j];
            neighbour[j] = cities[i];
            neighbours.push_back(neighbour);

        }
    }

    return neighbours;
}

vector<vector<int>> GetBestNeighbour(int t[][4], vector<vector<int>> neighbours)
{
    vector<vector<int>> ret;
    vector<int> bestneighbour, v;

    int bestroutelength, currentRouteLength; 

    bestroutelength = RouteLength(t, neighbours[0]);
    bestneighbour = neighbours[0];

    for(int i=0; i<neighbours.size(); i++)
    {
        currentRouteLength = RouteLength(t, neighbours[i]);
        if (currentRouteLength < bestroutelength)
        {
            bestroutelength = currentRouteLength;
            bestneighbour = neighbours[i];
        }
    }
    v.push_back(bestroutelength);

    ret.push_back(bestneighbour);
    ret.push_back(v);

    return ret;
}

void hill_climbing(int t[][4])
{
    vector<int> current_solution = random_solution(t);
    int current_route_length = RouteLength(t, current_solution);
    vector<vector<int>> neighbours = getNeighbours(current_solution);
    vector<vector<int>> v = GetBestNeighbour(t, neighbours);
    vector<int> bestneighbour = v[0];
    int bestNeighbourRouteLength = v[1][0];

    while (bestNeighbourRouteLength < current_route_length)
    {
        current_solution = bestneighbour;
        current_route_length = bestNeighbourRouteLength;
        neighbours = getNeighbours(current_solution);
        v = GetBestNeighbour(t, neighbours);
        bestneighbour = v[0];
        bestNeighbourRouteLength = v[1][0];
    }

    cout<<"Best Solution :"<<endl;
    for(int i=0;i<bestneighbour.size();i++)
        cout<<bestneighbour[i]<<" ";
    
    cout<<"\n";
    cout<<"Minimum Cost Route : "<<bestNeighbourRouteLength;
}


int main(){
    int t[][4] = 
        {0,	12,	22,	11,	33,	4,	66,	88,	90,	10,
        12,	0,	75,	21,	57,	41,	87,	46,	37,	27,
        22,	75,	0,	64,	87,	90,	39,	98,	11,	29,
        11,	21,	64,	0,	61,	91,	5,	6,	5,	8,
        33,	57,	87,	61,	0,	82,	95,	87,	34,	84,
        4,	41,	90,	91,	82,	0,	66,	44,	23,	55,
        66,	87,	39,	5,	95,	66,	0,	44,	44,	99,
        88,	46,	98,	6,	87,	44,	44,	0,	22,	55,
        90,	37,	11,	5,	34,	23,	44,	22,	0,	22,
        10,	27,	29,	8,	84,	55,	99,	55,	22,	0,
    };

    hill_climbing(t);
    cout<<"\n"<<endl;
 return 1;   
}