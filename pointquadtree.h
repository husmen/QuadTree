#ifndef POINTQUADTREE_H
#define POINTQUADTREE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <queue>

#define MAX 500

using namespace std;

struct Node
    {
        int x;
        int y;
        int colour;
        struct Node* NW;
        struct Node* NE;
        struct Node* SE;
        struct Node* SW;
        int LN;
        int LS;
        int LE;
        int LW;
    };


class PointQuadtree
{
public:

    int xc, yc, xc2, yc2, rc;

    struct Node* root;
    struct Node* target;

    PointQuadtree();

    struct Node* makeNode(int x, int y);

    struct Node* makeNode(int x, int y, int colr);

    //check to see if two Nodes are equal
    bool equalCoordinates(struct Node* temp, struct Node* target);

    //return the successive quadrant where toBeInserted will be further inserted
    struct Node* getQuadrant(struct Node* temp, struct Node* target);
    //insert into the final quadrant found
    void insertPointInFinalQuadrant(struct Node* temp, struct Node* target);

    //insert: @return true for successful search, false for unsuccessful search
    bool insert(int x, int y);

    //randomize: gfgfgf
    void randomize(int N);

    int dist(int x1, int y1, int x2, int y2);


    bool inCircle(int x, int y, int r, struct Node* target);


    //searching: @return true for successful search, false for unsuccessful search
    bool search(int x, int y);

//function for level order traversal using BFS + checking for existence inside a circle or not
    void checkCircle(int x, int y, int r);

protected:

private:
};

#endif // POINTQUADTREE_H
