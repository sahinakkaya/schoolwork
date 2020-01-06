#ifndef HW3
#define HW3

struct HW3_Result
{
        int packageCount;	//40 pts
        int redNodeCount;	//30 pts
        int blackNodeCount;	//30 pts
};

HW3_Result hw3(  int eastWarehousePackageCount,
                 int eastWarehousePackageSizes [],
                 int eastWarehousePackageOrdinals [],
                 int westWarehousePackageCount,
                 int westWarehousePackageSizes [],
                 int westWarehousePackageOrdinals [] );

#endif //HW3
