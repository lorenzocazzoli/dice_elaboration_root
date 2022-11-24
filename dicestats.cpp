// STANDARD LIBRARIES
#include <iostream>
#include <vector>
#include <random>

// ROOT LIBRARIES TO MANAGE AND GRAPH DATA
#include "TCanvas.h"
#include "TH1I.h"


using std::vector;
using std::cin;
using std::cout;

vector<int> roll_initializer(int n, int f, int m) {
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,f);

    vector<int> results;
    for(int i=0; i<m; i++) {
        results.push_back(0);
        for(int j=0; j<n; j++) {
            results[i] += distribution(generator);
        }
    }

    return results; 
}

void dicestats()
{   
    cout << "Number of dice per roll: ";
    int n;
    cin >> n;
    cout << "Number of faces per dice: ";
    int f;
    cin >> f;
    cout << "Number of rolls: ";
    int m;
    cin >> m;

    vector<int> dicevents = roll_initializer(n, f,m);

    int bins = n*f;
    double start = n;
    double end = (n*f);
    TH1 * h = new TH1I("h", "Result Distribution", bins, start, end);
    for(auto i=dicevents.begin(); i!=dicevents.end(); i++) {
        h->Fill(*i);
    }
    TCanvas *c = new TCanvas("Canvas");
    h->Draw("HIST");
}
