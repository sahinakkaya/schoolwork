#include <iostream>
#include "hw3.h"
using namespace std;
int main()
{
    // int eastWarehousePackageCount = 10;
    // int eastWarehousePackageSizes[] = {1,5,34,6,7,23,5,6,34,5};
    // int eastWarehousePackageOrdinals[] = {7,43,59,80,925,89,27,45,89,72};
    // int westWarehousePackageCount = 10;
    // int westWarehousePackageSizes[] = {10,38,51,7,38,47,8,53,2,94};
    // int westWarehousePackageOrdinals[] = {5,62,86,73,74,83,68,35,7,95};


    int eastWarehousePackageCount = 3;
    int eastWarehousePackageSizes[] = {2, 2, 3};
    int eastWarehousePackageOrdinals[] = {3, 4, 5};
    int westWarehousePackageCount = 5;
    int westWarehousePackageSizes[] = {1, 1, 1, 5, 6};
    int westWarehousePackageOrdinals[] = {4, 5, 7, 1, 2};


    // int eastWarehousePackageCount = 7;
    // int eastWarehousePackageSizes[] = {2,2,3,4,5,6,7};
    // int eastWarehousePackageOrdinals[] = {3,4,5,4,5,6,7};
    // int westWarehousePackageCount = 5;
    // int westWarehousePackageSizes[] = {1,1,1,5,6};
    // int westWarehousePackageOrdinals[] = {4,5,7,1,2};
    auto ans = hw3(eastWarehousePackageCount, 
                eastWarehousePackageSizes,
                eastWarehousePackageOrdinals, 
                westWarehousePackageCount,
                westWarehousePackageSizes,
                westWarehousePackageOrdinals);
    cout << ans.packageCount << " " << ans.redNodeCount << " " << ans.blackNodeCount<<endl;
}