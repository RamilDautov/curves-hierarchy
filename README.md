# curves-hierarchy

This project implements a support of a few types of 3D geometric curves: circles, ellipses and 3D helixes. 
The code can be easily extended and new types of curves can be added.


Types of curves are represented as enumeration:
```cpp
enum CurveType{
    Circle,
    Ellipse,
    Helix,
    last
};
```

3D points and vectors are represented as structure `Coordinates3D`:
```cpp
struct Coordinates3D{
    double x;
    double y;
    double z;
};
```

Classes `Circle`, `Ellipse` and `Helix` are inherited from the base class `Curve`.

### Functions available:
Functions are defined in `lib/curves_hierarchy.cpp`

+ Populating vector of curves in random manner with random parameters:
```cpp 
std::vector<Curves::Curve*> PopulateAtRandom(int num);
```


+ Printing coordinates of points and derivatives of all curves in the container at parameter value `t`:
```cpp 
void PrintAt(const std::vector<Curves::Curve*>& v, double t);
```

+ Populating a vector of circles taken from vector of curves
```cpp
std::vector<Curves::Circle*> FilterCircles(std::vector<Curves::Curve*>& curves);
```

+ Sorting vector of circles in the ascending order of circles’ radii
```cpp
void SortCircles(std::vector<Curves::Circle*>& circles);
```

+ Computing the total sum of radii of all circles in vector. Function is parallelized using OpenMP library.
```cpp
uint32_t SumOfRadii(const std::vector<Curves::Circle*>& v);
```
### Examples of implementation
Example of implementation can be found in main.cpp file.
```cpp
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
```


 
