
#ifndef DiscountBarcode_H
#define DiscountBarcode_H
#include<vector>

#define BarcodeNum 20
using namespace std;
typedef struct  DiscountBarcode //��Ա�����Ż���������Ϣ
{
   char type[50];  //���õ�����
   char barcode[BarcodeNum];//�����Ż�������
}DiscountBarcode;
extern vector<DiscountBarcode> DiscountBar;//�洢��Ա���õ��Ż�����������
int ReadDiscountFile();//��DiscountBarcode.txt�ı��ж�ȡ���õ��Ż�������
#endif