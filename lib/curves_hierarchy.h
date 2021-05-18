#pragma once

#include <ostream>
#include <memory>

struct Coordinates3D{
    double x;
    double y;
    double z;
};

enum CurveType{
    Circle,
    Ellipse,
    Helix,
    last
};


namespace Curves{


    class Curve{
    public:
        virtual ~Curve() = default;

        virtual Coordinates3D Get3Dpoint(const double t) const = 0;
        virtual Coordinates3D FirstDerivative(const double t) const = 0;
        virtual CurveType GetType() const = 0;
    };

    class Circle : public Curve{
    public:
        ~Circle() override = default;
        Circle(const uint32_t radius) : radius(radius), type(CurveType::Circle){};
        Coordinates3D Get3Dpoint(const double t) const override;
        Coordinates3D FirstDerivative(const double t) const override;
        CurveType GetType() const override { return type; }
        uint32_t GetRadius() const {return radius;}
    private:
        uint32_t radius;
        CurveType type;
    };

    class Ellipse : public Curve{
    public:
        ~Ellipse() override = default;
        Ellipse(const uint32_t radius_X, const uint32_t radius_Y) :
                                    radius_X(radius_X), radius_Y(radius_Y), type(CurveType::Ellipse){};
        Coordinates3D Get3Dpoint(const double t) const override;
        Coordinates3D FirstDerivative(const double t) const override;
        CurveType GetType() const override { return type; }
    private:
        uint32_t radius_X;
        uint32_t radius_Y;
        CurveType type;
    };

    class Helix : public Curve{
    public:
        ~Helix() override = default;
        Helix(const uint32_t radius, const uint32_t step) :
                                    radius(radius), step(step), type(CurveType::Helix){};
        Coordinates3D Get3Dpoint(const double t) const override;
        Coordinates3D FirstDerivative(const double t) const override;
        CurveType GetType() const override { return type; }
    private:
        uint32_t radius;
        uint32_t step;
        CurveType type;
    };


    //////////// Interface for the Filter (to satisfy Open-Closed principle) ////////////////

    template <typename T> struct Specification
    {
        virtual ~Specification() = default;
        virtual bool is_satisfied(T* item) const = 0;
    };


    template <typename T> struct Filter
    {
        virtual std::vector<T*> filter(std::vector<T*>& items,
                                       Specification<T>& spec) = 0;
    };



/////////////      Filters       //////////////

/* Here I implement only one filter, but the code can be easily extended */

    struct CurvesFilter : Filter<Curve>
    {
        std::vector<Curve*> filter(std::vector<Curve*>& items,
                                           Specification<Curves::Curve> &spec) override
        {
            std::vector<Curve*> result;
            for (auto& p : items)
                if (spec.is_satisfied(p))
                    result.push_back(p);
            return result;
        }
    };

    struct TypeSpecification : Specification<Curve>
    {
        CurveType type;

        TypeSpecification(CurveType type) : type(type) {}

        bool is_satisfied(Curve *item) const override {
            return item->GetType() == type;
        }
    };

}
std::vector<Curves::Curve*> PopulateAtRandom(int num);
std::vector<Curves::Circle*> FilterCircles(std::vector<Curves::Curve*>& curves);
void SortCircles(std::vector<Curves::Circle*>& circles);


void PrintAt(const std::vector<Curves::Curve*>& v, double t);
void PrintAt(const std::vector<Curves::Circle*>& v, double t);
void PrintAt(const std::vector<Curves::Ellipse*>& v, double t);
void PrintAt(const std::vector<Curves::Helix*>& v, double t);
uint32_t SumOfRadii(const std::vector<Curves::Circle*>& v);

std::ostream& operator<<(std::ostream& os, const Coordinates3D& p);



