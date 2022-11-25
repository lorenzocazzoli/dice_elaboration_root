// STANDARD LIBRARIES
#include <iostream>
#include <vector>
#include <random>

// ROOT LIBRARIES TO MANAGE AND GRAPH DATA
#include "TCanvas.h"
#include "TH1I.h"

// USING DECLARATIONS
using std::vector;
using std::cin;
using std::cout;

// NUMBER GENERATION WITH DEFAULT RANDOM ENGINE
vector<int> roll_initializer(int n, int f, int m, int b) {
    
    std::default_random_engine generator;
    //uniform distribution with range possible in dice roll
    std::uniform_int_distribution<int> distribution(1,f);

    vector<int> results;
    //fillinfg the results vector with sum of rolls
    for(int i=0; i<m; i++) {
        results.push_back(0);
        for(int j=0; j<n; j++) {
            results[i] += distribution(generator);
        }
        results[i] += b;
    }

    return results; 
}

void dicestats()
{   
    //------------------------------//
    //      STARTING INTERFACE      //
    //------------------------------//

    cout << "Number of dices per roll: ";
    //number of dices in each roll
    int n;
    cin >> n;
    cout << "Number of faces per dice: ";
    //number of faces on each dice rolled
    int f;
    cin >> f;
    cout << "Number of rolls: ";
    //number of rolls total
    int m;
    cin >> m;
    cout << "Bonus to the total: ";
    //int number to add to the total of each roll
    int b;
    cin >> b;

    //vector containing the results
    vector<int> dicevents = roll_initializer(n, f, m, b);

    //------------------------------//
    //   HISTOGRAM INIZIALIZATION   //
    //------------------------------//

    //number of bins in the histogram
    int bins = n*f-(n-1);
    //lowest value accepted in the histogram
    double start = n+b-0.5;
    //highest value accepted in the histogram
    double end = (n*f)+b+0.5;
    //inizialization of the histogram
    TH1 * h = new TH1I("h", "Result Distribution", bins, start, end);
    //filling of the histogram with values from results vector
    for(auto i=dicevents.begin(); i!=dicevents.end(); i++) {
        h->Fill(*i);
    }

    //inizialization of the canvas
    TCanvas *c = new TCanvas("Canvas");
    //drawing the histogram on the canvas
    h->Draw("HIST");
}
