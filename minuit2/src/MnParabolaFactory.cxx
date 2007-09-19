// @(#)root/minuit2:$Id: MnParabolaFactory.cxx,v 1.3 2006/07/03 22:06:42 moneta Exp $
// Authors: M. Winkler, F. James, L. Moneta, A. Zsenei   2003-2005  

/**********************************************************************
 *                                                                    *
 * Copyright (c) 2005 LCG ROOT Math team,  CERN/PH-SFT                *
 *                                                                    *
 **********************************************************************/

#include "Minuit2/MnParabolaFactory.h"
#include "Minuit2/MnParabola.h"
#include "Minuit2/MnParabolaPoint.h"

namespace ROOT {

   namespace Minuit2 {


// #include <iostream>

MnParabola MnParabolaFactory::operator()(const MnParabolaPoint& p1, 
                                         const MnParabolaPoint& p2, 
                                         const MnParabolaPoint& p3) const {
   // construct the parabola from 3 points p1,p2,p3                                      
   double x1 = p1.x();
   double x2 = p2.x();
   double x3 = p3.x();
   double dx12 = x1-x2;
   double dx13 = x1-x3;
   double dx23 = x2-x3;
   
   //   std::cout<<"MnParabolaFactory x1, x2, x3: "<<x1<<" "<<x2<<" "<<x3<<std::endl;
   
   double xm = (x1+x2+x3)/3.;
   x1 -= xm;
   x2 -= xm;
   x3 -= xm;
   
   double y1 = p1.y();
   double y2 = p2.y();
   double y3 = p3.y();
   //   std::cout<<"MnParabolaFactory y1, y2, y3: "<<y1<<" "<<y2<<" "<<y3<<std::endl;
   
   double a = y1/(dx12*dx13) - y2/(dx12*dx23) + y3/(dx13*dx23);
   double b = -y1*(x2+x3)/(dx12*dx13) + y2*(x1+x3)/(dx12*dx23) - y3*(x1+x2)/(dx13*dx23);
   double c = y1 - a*x1*x1 - b*x1;
   
   c += xm*(xm*a - b);
   b -= 2.*xm*a;
   
   //   std::cout<<"a,b,c= "<<a<<" "<<b<<" "<<c<<std::endl;
   return MnParabola(a, b, c);
}

MnParabola MnParabolaFactory::operator()(const MnParabolaPoint& p1, 
                                         double dxdy1, 
                                         const MnParabolaPoint& p2) const {
   // construct the parabola from 2 points + derivative at first point dxdy1
   double x1 = p1.x();
   double xx1 = x1*x1;
   double x2 = p2.x();
   double xx2 = x2*x2;
   double y1 = p1.y();
   double y12 = p1.y() - p2.y();
   
   double det = xx1-xx2 - 2.*x1*(x1-x2);
   double a = -(        y12 +   (x2-x1)*dxdy1)/det;
   double b = -( -2.*x1*y12 + (xx1-xx2)*dxdy1)/det;
   double c = y1 - a*xx1 - b*x1;
   
   return MnParabola(a, b, c);
}


   }  // namespace Minuit2

}  // namespace ROOT
