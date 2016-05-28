
#ifndef DiscountBarcode_H
#define DiscountBarcode_H
#include<vector>

#define BarcodeNum 20
using namespace std;
typedef struct  DiscountBarcode //店员设置优惠条形码信息
{
   char type[50];  //设置的类型
   char barcode[BarcodeNum];//设置优惠条形码
}DiscountBarcode;
extern vector<DiscountBarcode> DiscountBar;//存储店员设置的优惠条形码向量
int ReadDiscountFile();//从DiscountBarcode.txt文本中读取设置的优惠条形码
#endif