#include "GeoGebraCAS.h"
#include <iostream>

#ifdef _WIN32
#include "tchar.h"
int _tmain(int argc, _TCHAR* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
        cout << "Starting GeoGebraCAS-demo" << endl;
        // initializeCAS();
        //string ret = evaluateCAS("factor(x^2-1)");
        //cout << ret << endl;
        //ret = evaluateCAS("evalf(7,13)");
        //cout << ret << endl;
        //ret = evaluateCAS("evalf(7,15)");
        //cout << ret << endl;
        //ret = evaluateCAS("expand((a+b)^3)");
        //cout << ret << endl;
        //ret = evaluateCAS("evalfa(when ( type(((x)^(2))+(1)) == DOM_SYMBOLIC && type(x) == DOM_SYMBOLIC , (assume(x),solve(((x)^(2))+(1),x))[size(assume(x),solve(((x)^(2))+(1),x))-1] , when ( type(((x)^(2))+(1)) == DOM_IDENT && type(x) == DOM_SYMBOLIC && ((x)^(2))+(1) == 'x', (assume(x),solve(((x)^(2))+(1)=0,x))[size(assume(x),solve(((x)^(2))+(1)=0,x))-1] ,when ( size(x) == 1,flatten1((normal([op(solve(((x)^(2))+(1),x))]))),(normal([op(solve(((x)^(2))+(1),x))])) ) ) ))");
        //cout << ret << endl;
        //ret = evaluateCAS("simplify(pow2exp(equal2diff([f*t*i*f*t*exp(1)*r*exp(1)*f*t*i*f*t*i*f*t*exp(1)*r*exp(1)*f*t*i*f*t*exp(1)*r*exp(1)*t*a*s*exp(1)*f*t*i*f*t*i*f*t*exp(1)*r*exp(1)*f*t*exp(1)*f*t*exp(1)*r*exp(1)*f*t*exp(1)*t*exp(1)*r*o*w*exp(1)*t*r*exp(1)*t*exp(1)*r*d_temp_043a718774c572bd8a25adbeb1bfcd5c0256ae11cecf9f9c3f925d0e52beaf89=(i*f*t*exp(1)*t*r*exp(1)*r*s_s)])))");
        //cout << ret << endl;
        //ret = evaluateCAS("solve(pow2exp(equal2diff([f^13*w*exp(1)^17-i*f*r^2*s_s*t^2*exp(1)^2])), [f])");
        //cout << ret << endl;
        //cin >> ret;
        //string ret = evaluateCAS("solve(pow2exp(equal2diff([exp(-2*x)*(2*x+1-1)=(2*x*exp(-2*x))])), [x])");
        //cout << ret << endl;
        //ret = evaluateCAS("solve(pow2exp(equal2diff([cos(x^3)*3*x^2=(3*x^2*cos(x^3))])), [x])");
        //cout << ret << endl;
        //ret = evaluateCAS("simplify(pow2exp(equal2diff([A+(-lambda)*I=([[0,-1],[1,0]]+[[-lambda,0],[0,-lambda]]),-lambda=lambda,-lambda=lambda])))");
        //cout << ret << endl;
        //ret = evaluateCAS("solve(pow2exp(equal2diff([A+(-lambda)*I=([[0,-1],[1,0]]+[[-lambda,0],[0,-lambda]]),-1=(-1-lambda),-lambda=(-lambda),-lambda=(-lambda)]), [t,lambda,I,d,A])");
        //cout << ret << endl;
        string ret = evaluateCAS("solve(pow2exp(equal2diff([D*i*exp(1)*v*n*t*exp(1)*r*exp(1)*s*exp(1)*i*t*exp(1)=(350*c*m),F*o*r*m*exp(1)*l/A=(200*m*150*m),200*m*150*m=(3000*c*m),A=(pi*200/4),pi*200/4=(119565709003/38006517*c*m*i*n),sin(d_temp_de7d1b721a1e0632b7cf04edf5032c8ecffa9f9a08492152b926f1a5a7e765d7*n*m)*exp(1)*l*exp(1)*r=(3*m)])), [b,A,D,F,c,d_temp_de7d1b721a1e0632b7cf04edf5032c8ecffa9f9a08492152b926f1a5a7e765d7,l,m,n,o,r,s,t,v])");
        cout << ret << endl;
        
        cout << "Finishing GeoGebraCAS-demo" << endl;
        return 0;
}
