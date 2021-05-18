#include <iostream>
#include <cmath>
#include <vector>
#include "lib/curves_hierarchy.h"

using namespace std;

const double PI = M_PI;

int main() {
    // Number of Curves objects to create:
    const int N = 10;

    vector<Curves::Curve*> curves(N);

    //Populating vector of curves in random manner with random parameters
    curves = PopulateAtRandom(N);

    //Printing coordinates of points and derivatives of all curves in the container at t=PI/4
    cout << "Printing coordinates of points and derivatives of all curves at t=PI/4:\n";
    PrintAt(curves, PI / 4);
    cout << "\n\n";

    //Populating a vector of circles taken from vector of curves
    vector<Curves::Circle*> circles = FilterCircles(curves);
    //PrintAt(circles, PI / 4); // you can check that these are really circles from the curves vector
    //cout << "\n\n";

    //Sorting the second container in the ascending order of circles’ radii
    cout << "Sorting the circles in the ascending order of radii:\n";
    SortCircles(circles);
    PrintAt(circles, PI / 4);
    cout << "\n\n";

    //Compute the total sum of radii of all curves in the second container
    cout << "Sum of radii: " << SumOfRadii(circles);

    return 0;
}
