//
// Created by Gavin on 2/14/2016.
//

#include <cmath>
#include <algorithm> //min, max

#include "Point.h"

namespace Clustering {

    // Static ID generator
    unsigned int Point::__idGen = 0;

    //  Constructors
    Point::Point(int dimensions) {
        // Assign ID and increment for next point
        __id = __idGen;
        ++__idGen;

        // Assign dimension number and create array
        __dim = dimensions;
        __values = new double[__dim];
    }

    Point::Point(int dimensions, double *array) {
        // Assign ID and increment for next point
        __id = __idGen;
        ++__idGen;

        __dim = dimensions;
        __values = array;
    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &origin) {
        __dim = origin.__dim;
        __values = new double[__dim];
        __id = origin.__id;

        for (int i = 0; i < __dim; ++i) {
            __values[i] = origin.__values[i];
        }
    }

    Point &Point::operator=(const Point &origin) {
        __dim = origin.__dim;
        __id = origin.__id;

        // If array was already assigned, delete first
        if (__values != nullptr)
            delete [] __values;

        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i) {
            __values[i] = origin.__values[i];
        }

        return *this;
    }

    Point::~Point() {
        delete [] __values;
    }

    // Accessors & mutators
    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int dim, double val) {
        // Must be valid dimension for point
        // or do nothing
        if (dim >= 0 && dim < __dim) {
            __values[dim] = val;
        }
    }
    double Point::getValue(int dim) const {
        // Must be valid dimension for point
        // or return 0
        if (dim >= 0 && dim < __dim)
            return __values[dim];
        else
            return 0;
    }

    //  distanceTo(const Point&)
    //  Estimate distance between calling point
    //  and a second point
    double Point::distanceTo(const Point &compPoint) const {
        int usedDim = std::min(__dim, compPoint.__dim);     // Dimensions to compare
        double sumOfProducts = 0;                           // Sum of (xn2 - xn1)^2

        for (int i = 0; i < usedDim; ++i) {
            sumOfProducts += pow(compPoint.getValue(i) - getValue(i), 2);
        }

        return sqrt(sumOfProducts);
    }

    // Overloaded operators

    // Members
    Point &Point::operator*=(double val) {
        for (int i = 0; i < __dim; ++i) {
            __values[i] *= val;
        }

        return *this;
    }

    Point &Point::operator/=(double val) {
        for (int i = 0; i < __dim; ++i) {
            __values[i] /= val;
        }

        return *this;
    }

    const Point Point::operator*(double val) const {
        Point p(*this);

        p *= val;

        return p;
    }

    const Point Point::operator/(double val) const {
        Point p(*this);

        p /= val;

        return p;
    }

    // Read and write index
    double &Point::operator[](int index) {
        //  Prevent access out of bounds
        if (index < 0 || index >= __dim)
            index = 0;

        return __values[index];
    }

    // Read-only index
    const double &Point::operator[](int index) const {
        //  Prevent access out of bounds
        if (index < 0 || index >= __dim)
            index = 0;

        return __values[index];
    }

    // Friends
    Point &operator+=(Point &lhs, const Point &rhs) {
        // Used dimensions is the greater of the two points
        int usedDims = std::max(lhs.getDims(), rhs.getDims());

        // Resize left array if right is larger
        if (lhs.__dim < usedDims) {
            delete [] lhs.__values;

            lhs.__values = new double[usedDims];
        }

        // Add values of right to values of left
        for (int i = 0; i < usedDims; ++i) {
            lhs[i] += rhs.getValue(i);      // note: getValue returns 0 if out of bounds
        }

        return lhs;
    }
    Point &operator-=(Point &lhs, const Point &rhs) {
        // Used dimensions is the greater of the two points
        int usedDims = std::max(lhs.getDims(), rhs.getDims());

        // Resize left array if right is larger
        if (lhs.__dim < usedDims) {
            delete [] lhs.__values;

            lhs.__values = new double[usedDims];
        }

        // Add values of right to values of left
        for (int i = 0; i < usedDims; ++i) {
            lhs[i] -= rhs.getValue(i);      // note: getValue returns 0 if out of bounds
        }

        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs) {
        Point p(lhs);

        p += rhs;

        return p;
    }

    const Point operator-(const Point &lhs, const Point &rhs) {
        Point p(lhs);

        p -= rhs;

        return p;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if (lhs.__id != rhs.__id)
            return false;   // ID's don't match, not the same

        for (int i = 0; i < std::max(lhs.__dim, rhs.__dim); ++i) {
            if (lhs.getValue(i) != rhs.getValue(i))
                return false; // Any dimensional value doesn't match
        }

        // ID's are the same, values are the same
        return true;
    }

    bool operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        int usedDims = std::max(lhs.__dim, rhs.__dim);

        for (int i = 0; i < usedDims; ++i) {
            if (lhs.getValue(i) != rhs.getValue(i)) { // Inequality exists, return < comparison
                return (lhs.getValue(i) < rhs.getValue(i));
            }
        }

        // All values equal, return false
        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        return (rhs < lhs);
    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        return !(lhs > rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        return !(lhs < rhs);
    }

    std::ostream &operator<<(std::ostream &out, const Point &p) {
        for (int i = 0; i < p.getDims(); ++i) {
            out << p[i];

            if (i != (p.getDims() - 1))
                out << ", "; // print out comma and space if not last element
        }
    }

    std::istream &operator>>(std::istream &in, Point &p) {
        for (int i = 0; i < p.getDims(); ++i) {
            in >> p[i];
        }
    }

}