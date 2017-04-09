#include "pointquadtree.h"
#include "scribblearea.h"

PointQuadtree::PointQuadtree()
{
    root = NULL;
    target = NULL;
}

struct Node* PointQuadtree::makeNode(int x, int y)
{
    struct Node* temp = new Node;
    temp->x = x;
    temp->y = y;
    temp->NW = NULL;
    temp->NE = NULL;
    temp->SE = NULL;
    temp->SW = NULL;
    return temp;
}

bool PointQuadtree::equalCoordinates(struct Node* temp, struct Node* target)
{
    return (temp->x == target->x && temp->y == target->y);
}

struct Node* PointQuadtree::getQuadrant(struct Node* temp, struct Node* target)
{
    if(temp->x < target->x)
    {
        if(temp->y < target->y)
        {
            return temp->SE;
        }
        else
        {
            return temp->NE;
        }
    }

    else if(temp->y < target->y)
    {
        return temp->SW;
    }
    else
    {
        return temp->NW;
    }
}

void PointQuadtree::insertPointInFinalQuadrant(struct Node* temp, struct Node* target)
{
    if(temp->x < target->x)
    {
        if(temp->y < target->y)
        {
            temp->SE = target;
            target->LN = temp->y;
            target->LW = temp->x;
            target->LS = temp->LS;
            target->LE = temp->LE;
        }
        else
        {
            temp->NE = target;
            target->LN = temp->LN;
            target->LW = temp->x;
            target->LS = temp->y;
            target->LE = temp->LE;
        }
    }

    else if(temp->y < target->y)
    {
        temp->SW = target;
        target->LN = temp->y;
        target->LW = temp->LW;
        target->LS = temp->LS;
        target->LE = temp->x;
    }
    else
    {
        temp->NW = target;
        target->LN = temp->LN;
        target->LW = temp->LW;
        target->LS = temp->y;
        target->LE = temp->x;
    }
    cout << "insert(" << target->x << "," << target->y << ")" << endl;
}

bool PointQuadtree::insert(int x, int y)
{
    target = makeNode(x,y);

    if(root == NULL)
    {
        root = target;
        root->LN = 0;
        root->LS = 500;
        root->LW = 0;
        root->LE = 500;

        cout << "insert(" << target->x << "," << target->y << ")" << endl;
        return true;
    }

    struct Node *temp = root;
    while(temp != NULL && !equalCoordinates(temp, target))
    {
        struct Node* quadrant = getQuadrant(temp, target);
        if(quadrant == NULL)
        {
            insertPointInFinalQuadrant(temp, target);
            temp = NULL;
            return true;
        }
        else
        {
            temp = quadrant;
        }
    }
    return false;
}

void PointQuadtree::randomize(int N)
{
    srand((unsigned)time(0));
    int random1, random2;
    int lowest=0, highest=MAX;
    int range=(highest-lowest)+1;
    for(int i=0; i<N; i++)
    {
        random1 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        random2 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        PointQuadtree::insert(random1,random2);
        QPoint p = QPoint(random1,random2);
    }
}

int PointQuadtree::dist(int x1, int y1, int x2, int y2)
{
    int distx = (x2-x1)*(x2-x1);
    int disty = (y2-y1)*(y2-y1);
    return (int)sqrt(distx+disty);
}

bool PointQuadtree::inCircle(int x, int y, int r, struct Node* target)
{
    return(dist(x,y,target->x,target->y)<r);
}

bool PointQuadtree::search(int x, int y)
{
    struct Node* target = makeNode(x,y);

    if(root == NULL)
    {
        return false;
    }

    if(equalCoordinates(root, target))
    {
        return true;
    }

    struct Node *temp = root;
    while(temp != NULL)
    {
        if(equalCoordinates(temp, target))
        {
            return true;
        }
        else
        {
            temp = getQuadrant(temp, target);
        }
    }
    return false;
}

void PointQuadtree::checkCircle(int x, int y, int r)
{
    cout << endl;
    queue<struct Node*> q;
    if(q.empty())
        q.push(root);

    while(!q.empty())
    {
        struct Node* popped = q.front();
        q.pop();
        if(inCircle(x, y, r, popped))
            cout << "found(" << popped->x <<", " << popped->y << ") " << endl;

        if(popped->NE != NULL)
            q.push(popped->NE);
        if(popped->NW != NULL)
            q.push(popped->NW);
        if(popped->SW != NULL)
            q.push(popped->SW);
        if(popped->SE != NULL)
            q.push(popped->SE);
    }
    cout << endl;
}
