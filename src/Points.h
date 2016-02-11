//
// Created by dido-ubuntu on 09/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_POINTS_H
#define PARALLELSTREAMCLUSTER_POINTS_H

#include <iostream>
#include <memory>


using namespace std;

struct Point {
    Point(Point &&) = delete;  //move
    Point(const Point &) = delete;

    Point(Point &p) : weight(p.weight), coord(p.coord), assign(p.assign),
                      cost(p.cost), ID(p.ID) { }

    Point &operator=(const Point &p) {
        weight = p.weight;
        coord = p.coord;
        assign = p.assign;
        cost = p.cost;
        ID = p.ID;
        return *this;
    }

    Point() { }

    ~Point() { }

    float weight;
    float *coord;  //coord points to an array of dim long

    long assign;   // number of point where this one is assigned
    float cost;    // cost of that assignment, weight*distance
    long ID;       //point ID: the position on the stream (dido).
};

// this is the array of points
struct Points {
public:

    long num; // number of points; may not be N if this is a sample
    int dim;  // dimensionality

    //std::unique_ptr<Point[]> p;   // the array itself
    Point * p;

    Points(Points &&) = delete;

    Points(const Points &) = delete;

    Points(Points &) = delete;

    Points &operator=(const Points &) = delete;

    Points(int d, long n) : num{n}, dim{d}, p(new Point[n]) { }

    ~Points() { };

    void to_string() {
        for (int i = 0; i < num; ++i) {
            cout << p[i].ID << endl;
            cout << p[i].weight << endl;
            for (int k = 0; k < dim; ++k) {
                cout << p[i].coord[k] << " ";
            }
            cout << endl << endl;
        }
    }

};


#endif //PARALLELSTREAMCLUSTER_POINTS_H
