#include "GeoGebraCAS.h"
#include <iostream>
#include <unistd.h>
#ifdef _WIN32
#include "tchar.h"
#include <unistd.h>
int _tmain(int argc, _TCHAR *argv[])
{
#else
int main(int argc, char *argv[])
{
#endif
        //char ch;
        //cin >> ch;
        //sleep(20);
        cout << "Starting GeoGebraCAS-demo" << endl;
        string ret;
        for (int ii = 0; ii < 100; ii++)
        {
                initializeCAS();
                ret = evaluateCAS("evalf(sum(1/(n!*1), n, 0,800))");
                cout << ii << "\t" << ret << endl;
                //evaluateCAS("rm_all_vars()");
                //clearContextCAS();
        }

        clearGlobalVars();

        cout << "Finishing GeoGebraCAS-demo" << endl;
        //char c;
        //cin >> c;
        return 0;
}
