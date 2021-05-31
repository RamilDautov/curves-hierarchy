#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <random>
#include <ctime>
#include <omp.h>
#include "curves_hierarchy.h"

const double PI = M_PI;

using namespace std;
using namespace Curves;

Coordinates3D Circle::Get3Dpoint(const double t) const {
    Coordinates3D p = {};
    p.x = radius*cos(t);
    p.y = radius*sin(t);
    p.z = 0;
    return p;
}

Coordinates3D Circle::FirstDerivative(const double t) const {
    Coordinates3D v = {};
    v.x = radius*sin(t)*(-1);
    v.y = radius*cos(t);
    v.z = 0;
    return v;
}


Coordinates3D Ellipse::Get3Dpoint(const double t) const {
    Coordinates3D p = {};
    p.x = radius_X*cos(t);
    p.y = radius_Y*sin(t);
    p.z = 0;
    return p;
}

Coordinates3D Ellipse::FirstDerivative(const double t) const {
    Coordinates3D v = {};
    v.x = radius_X*sin(t)*(-1);
    v.y = radius_Y*cos(t);
    v.z = 0;
    return v;
}


Coordinates3D Helix::Get3Dpoint(const double t) const {
    Coordinates3D p = {};
    p.x = radius*cos(t);
    p.y = radius*sin(t);
    p.z = t * step / (2*PI);
    return p;
}

Coordinates3D Helix::FirstDerivative(const double t) const {
    Coordinates3D v = {};
    v.x = radius*sin(t)*(-1);
    v.y = radius*cos(t);
    v.z = step / (2*PI);
    return v;
}

vector<Curve*> PopulateAtRandom(int num){
    assert(("You've entered negative number of elements: ", num >= 0));
    vector<Curves::Curve*> result;
    srand((unsigned) time(0));
    for(size_t i = 0; i < num; ++i){
        CurveType item = static_cast<CurveType>(rand() % CurveType::last);
        switch (item) {
            case CurveType::Circle : result.push_back(new Curves::Circle((rand() % 100) + 1));
                break;
            case CurveType::Ellipse : result.push_back(new Curves::Ellipse((rand() % 100) + 1, (rand() % 100) + 1));
                break;
            case CurveType::Helix : result.push_back(new Curves::Helix((rand() % 100) + 1, (rand() % 10) + 1));
                break;
        }
    }
    return result;
}

std::vector<Curves::Circle*> FilterCircles(std::vector<Curve*>& curves){
    std::vector<Curves::Circle*> result;
    CurvesFilter cf;
    TypeSpecification circles(CurveType::Circle);
    for(auto& item : cf.filter(curves, circles)){
        result.push_back(dynamic_cast<Curves::Circle*>(item));
    }
    return result;
};

void SortCircles(std::vector<Curves::Circle*>& circles){
    if(circles.empty()) {
        cout << "There are no circles\n";
        return;
    }
    sort(circles.begin(), circles.end(), [](auto lhs, auto rhs){
        return lhs->GetRadius() < rhs->GetRadius();
    });
};

auto op = [](uint32_t lhs, const Curves::Circle* rhs){
    return lhs + rhs->GetRadius();
};

uint32_t SumOfRadii(const vector<Curves::Circle*>& v){

    ////// Using OpenMP ///////
    uint32_t result = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for reduction (+:result)
    for(int i = 0; i < v.size(); i++)
    {
        result += v[i]->GetRadius();
    }
    return result;

    ////// Or use this if you don't want to use parallelism ///////
    //return accumulate(v.begin(), v.end(),0, op);
}

std::ostream& operator<<(std::ostream& os, const Coordinates3D& p){
    os << "(x: " << std::setprecision(5) << p.x << ", " <<
          "y: " << std::setprecision(5) << p.y << ", " <<
          "z: " << std::setprecision(5) << p.z << ")\n";
    return os;
}


