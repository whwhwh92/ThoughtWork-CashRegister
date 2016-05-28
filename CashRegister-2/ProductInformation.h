 #ifndef ProductInformation_H
 #define ProductInformation_H
#include<iostream>
#include<fstream>
#include<vector>
#define BarcodeNum 20
using namespace std;
typedef struct  ProductInformation//商品信息结构体
{
   char barcode[BarcodeNum];//商品条形码
   char name[20];  //商品名字
   char uint[10];   //商品数量单位
   char category[10];//商品类别
   char subcategory[10];//商品子类别
   float price;//商品单价
   
}ProductInformation;
extern vector<ProductInformation> ProductInfor; //存储商品信息向量
int ReadProductFile(); //从ProductInformation.txt文本中读取商品信息
#endif