 #ifndef ProductInformation_H
 #define ProductInformation_H
#include<iostream>
#include<fstream>
#include<vector>
#define BarcodeNum 20
using namespace std;
typedef struct  ProductInformation//��Ʒ��Ϣ�ṹ��
{
   char barcode[BarcodeNum];//��Ʒ������
   char name[20];  //��Ʒ����
   char uint[10];   //��Ʒ������λ
   char category[10];//��Ʒ���
   char subcategory[10];//��Ʒ�����
   float price;//��Ʒ����
   
}ProductInformation;
extern vector<ProductInformation> ProductInfor; //�洢��Ʒ��Ϣ����
int ReadProductFile(); //��ProductInformation.txt�ı��ж�ȡ��Ʒ��Ϣ
#endif