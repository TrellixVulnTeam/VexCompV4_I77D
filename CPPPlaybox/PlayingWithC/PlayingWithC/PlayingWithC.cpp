#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef struct {
    double x;
    double y;
    const char* color;
} PointPair;

typedef struct{
    double x;
    double y;
    int v;
    const char* color;
} VectorPair;

class Graph{
public:
    PointPair* points = (PointPair*)malloc(0);
    VectorPair* vectors = (VectorPair*)malloc(0);
    int numOfPoints = 0;
    int numOfVectors = 0;

    ~Graph() {
        free(points);
        free(vectors);
    }

    void clear() {
        free(points);
        free(vectors);
        points = (PointPair*)malloc(0);
        vectors = (VectorPair*)malloc(0);
        numOfPoints = 0;
        numOfVectors = 0;
    }

    void addVector(VectorPair x) {
        numOfVectors++;
        vectors = (VectorPair*)realloc(vectors, sizeof(VectorPair) * numOfVectors);
        vectors[numOfVectors - 1] = x;
    }

    void addPoint(PointPair x) {
        numOfPoints++;
        points = (PointPair*)realloc(points, sizeof(PointPair) * numOfPoints);
        points[numOfPoints - 1] = x;
    }

    void output() {
        for (int i = 0; i < numOfVectors; i++) {
            VectorPair v = vectors[i];
            std::cout << "V:" << v.x << "," << v.y << "," << v.v << "," << v.color << std::endl;
        }
        for (int i = 0; i < numOfPoints; i++) {
            PointPair p = points[i];
            std::cout << "P:" << p.x << "," << p.y << "," << p.color << std::endl;
        }
        std::cout << "END:END" << std::endl;
    }
};

using namespace std;
int main(){
    Graph log = Graph();
    log.addPoint({ 5,5,"blue" });
    log.addPoint({ 5,6,"green" });
    log.addVector({ 5,7,13,"purple" });
    log.output();
    log.clear();
    log.addVector({ 0,75,1003,"purple" });
    log.addVector({ -15.0025452,17,13,"purple" });
    log.output();

    return 0;
}