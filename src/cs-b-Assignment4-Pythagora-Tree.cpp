#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "gtypes.h"


#include <cmath>
#include "gwindow.h"
#include "gobjects.h"

using namespace std;
/*
 * Constants display settings
*/
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 350;

/*
 *Constant density of the rendering tree
*/
const int COUNT = 11;

const double Pi = 3.14159;

/*
 *The function recursively draws Pythagoras Tree with a given density.
 *function used to display the polar line
 *@param gw - object reference of the graphics window
 *@param leftPoint - object starting point of the left line
 *@param rightPoint - object starting point of the right line
 *@param startLench - starting line length
 *@param angle - starting angle of slope line
 *@param count - count the recursion depth
*/

void recursivTree(GWindow &gw,
                  GPoint leftPoint,
                  GPoint rightPoint,
                  double startLench,
                  double angle,
                  int count){

    if (count == 0) return;
    double newLineLench = startLench * cos( 45 * Pi / 180);
    gw.setColor("BLUE");

    GPoint lineLeft = gw.drawPolarLine(leftPoint, newLineLench, angle +45);
    GPoint longLineLeft = gw.drawPolarLine(leftPoint, newLineLench * 2, angle -45);

    gw.drawLine(rightPoint, leftPoint);

    GPoint longLineRight = gw.drawPolarLine(rightPoint, newLineLench * 2, angle +45);
    GPoint lineRight = gw.drawPolarLine(rightPoint, newLineLench, angle -45);

    GPoint newleftPoint1(lineLeft.getX(),
                         lineLeft.getY());

    GPoint newrightPoint1(longLineRight.getX(),
                          longLineRight.getY());

    GPoint newleftPoint2(longLineLeft.getX(),
                         longLineLeft.getY());

    GPoint newrightPoint2(lineRight.getX(),
                          lineRight.getY());

    gw.drawLine(newleftPoint1, newrightPoint1);
    gw.drawLine(newleftPoint2, newrightPoint2);

    count--;
    recursivTree(gw,
                 newleftPoint1,
                 newrightPoint1,
                 newLineLench,
                 angle+45, count);

    recursivTree(gw,
                 newleftPoint2,
                 newrightPoint2,
                 newLineLench,
                 angle-45, count);
}

/*
 *Function sets and draws start parameters for drawing Pythagoras Tree
 *Also runs the a recursive drawing the Pythagorean tree entirely.
*/
void drawPythagorTree(){
    GWindow graphicsWindow(WINDOW_WIDTH,WINDOW_HEIGHT);
    graphicsWindow.setColor("BLUE");


    double angle = 90;
    double startLineLength = graphicsWindow.getHeight() / 4;

    GPoint leftPoint((graphicsWindow.getWidth() - startLineLength) / 2,
                     graphicsWindow.getHeight());

    GPoint rightPoint((graphicsWindow.getWidth() + startLineLength) / 2,
                      graphicsWindow.getHeight());

    GPoint treeLineLeft = graphicsWindow.drawPolarLine(leftPoint, startLineLength, angle);
    GPoint treeLineRight = graphicsWindow.drawPolarLine(rightPoint, startLineLength, angle);

    GPoint leftTopPoint(treeLineLeft.getX(),
                        treeLineLeft.getY());

    GPoint rightTopPoint(treeLineRight.getX(),
                         treeLineRight.getY());

    recursivTree(graphicsWindow,
                 leftTopPoint,
                 rightTopPoint,
                 startLineLength,
                 angle, COUNT);
}

int main()
{
    drawPythagorTree();
    return 0;
}
