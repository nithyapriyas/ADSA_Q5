#include <bits/stdc++.h>
using namespace std;
 
struct Point
{
    int x;
    int y;
};

//Global variable
Point gPoint1;
 
//Swaps the given 2 points 
void SwapPoints( Point &x, Point &y)
{
    Point t = x;
    x = y;
    y = t;
}

//Return the distance between 2 points 
float GetDistance( Point a, Point b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + 0.0);
}

//For the given stack, it returns the element which lies next to the top 
Point GetNextToTopElement( stack<Point> &stk)
{
    //Obtained top
    Point top = stk.top();
    stk.pop();
    //Obtained next to top
    Point top1 = stk.top();
    //Now, push the top
    stk.push(top);
    //Return next to top
    return top1;
}

//Finds the cross product of 3 points
//If the result is 0, it means the points are linear
//If +ve, then ab lies clockwise from ac
//If -v1, then ab lies counter clockwise from ac 
int GetCrossProduct(Point point0, Point point1, Point point2)
{
    return (point1.x - point0.x) * (point2.y - point0.y) - (point1.y - point0.y) * (point2.x - point0.x);
}

//Sorts the points based on the orientation
bool ComparePoints(Point a, Point b)
{
    int res = GetCrossProduct(gPoint1, a, b);
    //If the points are linear, sort based on the distance from first point
    if(res == 0 )
    {
       return (GetDistance(gPoint1, a) < GetDistance(gPoint1, b));
    }
    //Case for clockwise
    else if(res > 0)
    {
        return true;
    }
    //Case for counter clock wise
    else
    {
        return false;
    }
}

//Prints convex hull of the given data points
void ConvexHullUsingGrahamScan(std::vector<Point> pnt)
{
    int n = pnt.size();
    int minY = pnt[0].y;
    int minIdx = 0;
    int m = 1;
    stack<Point> stk;
    //Find the point which is the bottom most/left most
    for (int j = 1; j < n; j++)
    {
        //If there is a tie, pick bottom most or left most
        if ( ( pnt[j].y < minY ) || ( minY == pnt[j].y && pnt[j].x < pnt[minIdx].x) )
        {
            minIdx = j;
            minY = pnt[j].y;

        }
    }

    //Swap the bottom/left most point with 0th index
    SwapPoints(pnt[0], pnt[minIdx]);
    //Assign the point as 1st point
    gPoint1 = pnt[0];
    //sort the points based on the orientation from the first point
    //i.e orientation is counter clock wise from the point1
    //If the points are linear, sort based on farthest distance from point1
    sort(pnt.begin()+1, pnt.end(), ComparePoints);

    //If more than one point has same angle from point1, then remove all and keep
    // the point which is farthest from point1
    for (int i=1; i<n; i++)
    {
        //If angle of point i and i+1 is same from point 1, then remove them
        while (i < n-1 && GetCrossProduct(gPoint1, pnt[i],  pnt[i+1]) == 0)
        {
            i++;
        }
        //m contains size of modified array
        pnt[m++] = pnt[i];
    }
    //Minimum thress points are needed for conex hull
    if (m < 3)
    {
        return;
    }

    //Push the 1,2,3 points to the empty stack
    stk.push(pnt[0]);
    stk.push(pnt[1]);
    stk.push(pnt[2]);

    //For the balance n-3 points continue the check
    for (int i = 3; i < m; i++)
    {
        //Remove the points if top, next to top and ith point doest make left turn
        while ( (stk.empty() == false)  && ( GetCrossProduct(GetNextToTopElement(stk), stk.top(), pnt[i])  <= 0))
        {
            stk.pop();

        }
        stk.push(pnt[i]);
    }
    printf("\nThe convex hull of the given data points are:");
    //Final output, print the stack
    while (stk.empty() == false)
    {
        Point p = stk.top();
        printf("\n\t(%d, %d)", p.x, p.y);
        stk.pop();
    }
}

int main()
{
    int n;
    std::vector<Point> p;

    //No of points
    printf("\nEnter the number of points to check convex hull =\t");
    scanf("%d", &n);

    printf("\nEnter the x,y coordinates in space seperated way like 5 10 ");
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        p.push_back({x,y});
    }
    //Using Graham scan algo, find convex hull of the given points
    ConvexHullUsingGrahamScan(p);
    return 0;
}