/*
  ˵��1:��Ʒ����Ϣ����ProductInformation.txt�ı��� 
            ��Ա�����Żݵ����������DiscountBarcode.txt�ı���
  ˵��2:�ڿ���̨����������������� ���������ַ���#���ڰ��س������������Ʒ�嵥
*/
#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include"ProductInformation.h"
#include"DiscountBarcode.h"
#include"stdlib.h"
using namespace std;
#define BarcodeNum 20  //��������ַ���
#define DiscounBuyNum  3  //������ٸ���Ʒ�����Ż�
#define  DiscounNum   1   //�Żݶ��ٸ���Ʒ
#define FALSE   0
#define TRUE    1
bool IsDiscount = FALSE; //IsDiscount TRUE ���� FALSE������
typedef struct InputBarcode//������������Ϣ
{
  char barcode[BarcodeNum];//������
  int BarcodeCount;                //������������Ӧ������
  int AfterDiscountNum;        //�Żݺ������������Ӧ��Ʒ����
}InputBarcode;
typedef struct DiscountProductInformation//������Ʒ����Ҫ������Ʒ����Ϣ
{
   char IsDiscountbarcode[BarcodeNum];//������
   int DiscountNum; //�Żݵ�����
}DiscountProductInformation;
vector<ProductInformation> ProductInfor; //�洢��Ʒ��Ϣ����
vector<DiscountBarcode> DiscountBar;    //�洢��Ա���õ��Ż�����������
vector<InputBarcode> InBarcodeVector;//�洢�ӿ���̨���������������
vector<DiscountProductInformation> DiscountProductInfor;//�洢���ϡ�������һ����������Ʒ��Ϣ����
/*
  �ַ��ָ� ���������������ʽΪ barcode-num �򽫰��մ˺����ָ�
*/
InputBarcode CutString(char str[])
{
	  InputBarcode TempInbarcode;
   	char *psplit = strtok(str,"-");//���ա�-���ָ�
	memset(TempInbarcode.barcode,0,BarcodeNum);
	strcpy(TempInbarcode.barcode,psplit);
        while(psplit != NULL)
		{
		psplit = strtok(NULL,"-");
		if( psplit != NULL)
		{
			char Num[5]={0};
			strcpy(Num,psplit);
			TempInbarcode.BarcodeCount = Num[0]-48;
			TempInbarcode.AfterDiscountNum = TempInbarcode.BarcodeCount;
		}
	}
		return TempInbarcode;
}
/*
  �ӿ���̨�ж�ȡ�����룬����ȡ���������Ϣ�洢��InBarcodeVector
  ע�⣺�����������������Ҫ�ڸ��������ַ���#��s˵������������
*/
int SetInputBarcode()
{
  InputBarcode Inbarcode;

   while (1)
   {
	   cin.getline(Inbarcode.barcode,100);
	    bool BarcodeRepeatFlag= FALSE ;//������������Ƿ���֮ǰ������ı�־λ
		if(strcmp(Inbarcode.barcode,"#")==NULL)//���롰#�� �����������
		{
		   break;
		}
		if(strstr(Inbarcode.barcode,"-"))//����barcode-num��ʽ ��Ϣ�Ķ�ȡ
	     {
				
				 InBarcodeVector.push_back(CutString(Inbarcode.barcode));
				 memset(Inbarcode.barcode,0,BarcodeNum);
		}
		else
		{
		  if(InBarcodeVector.size()==0)
		{
		   Inbarcode.BarcodeCount = 1;
		   Inbarcode.AfterDiscountNum =  Inbarcode.BarcodeCount;
		   InBarcodeVector.push_back(Inbarcode);
		} 
		else
		{
			
		   for(int i =0;i<InBarcodeVector.size();i++)//���ڸ��������Ѿ���֮ǰ������ ���ڸ�������������ϼ�1 ���ýṹ�岻��ѹ��vector
	      {
		   if(strcmp(Inbarcode.barcode,InBarcodeVector[i].barcode)==0)//�ж�������������Ƿ��Ѿ����� 
		    {
				
				   InBarcodeVector[i].BarcodeCount++;  
			       InBarcodeVector[i].AfterDiscountNum = InBarcodeVector[i].BarcodeCount;
			      BarcodeRepeatFlag = TRUE;
				
		     
		    }
	     }
		if(BarcodeRepeatFlag == FALSE)//�������������֮ǰû������ �������뼰������ѹ��vector
		 {
		       Inbarcode.BarcodeCount = 1;
			   Inbarcode.AfterDiscountNum =Inbarcode.BarcodeCount;
			   InBarcodeVector.push_back(Inbarcode);
		  }
		}
		memset(Inbarcode.barcode,0,BarcodeNum);
		}
		
   }
  
   return 1;
}
/*
   �ú����ж���������������Ƿ��з��ϡ�������һ������Ʒ��
   �������Ʒ�������������ѹ��DiscountProductInfor������
*/
int  DiscountJudge()
{
	DiscountProductInformation DiscountProduct;
    for(int i =0;i<InBarcodeVector.size();i++)
		for(int j =0;j<DiscountBar.size()-1;j++)
		{
			if(strcmp(InBarcodeVector[i].barcode,DiscountBar[j+1].barcode)==NULL)//�ж�������������Ƿ����Ż�������
			{
				
				if(InBarcodeVector[i].BarcodeCount>=DiscounBuyNum)//�жϸ���Ʒ����������Ƿ�>=3
				{
					strcpy(DiscountProduct.IsDiscountbarcode,InBarcodeVector[i].barcode);
					int multiple = InBarcodeVector[i].BarcodeCount/DiscounBuyNum;//��3��1 ��6��2 .......
					InBarcodeVector[i].AfterDiscountNum -= multiple;
					DiscountProduct.DiscountNum = multiple;
				    IsDiscount = TRUE;//������Ʒ����Ϊ�Ż���Ʒ
					DiscountProductInfor.push_back(DiscountProduct);//ѹ�뵽����
				    memset(DiscountProduct.IsDiscountbarcode,0,BarcodeNum);
				}
				
			}
			
		}
		return 1;
}
/*
 �ú����Ǵ�ӡ��Ʒ�嵥ģ�� �����ݿ���̨����������������ProductInformation.txt�е���Ʒ��Ϣ
 ���бȽϲ���ӡ��Ʒ�嵥��������ڡ�������һ����Ʒ�����ӡ�Ż��嵥
*/
int PrintList()
{
	   float Total = 0;//������Ʒ�ܼۣ��ܼƣ�
	   float SaveTotal = 0;//ÿ����Ʒ���ܼۣ�С�ƣ�
	   cout<<"*****<ûǮ׬�̵�>�����嵥*****"<<endl;
        for(int i =0;i<InBarcodeVector.size();i++)
			for(int j =0;j<ProductInfor.size();j++)
			{
			if(strcmp(InBarcodeVector[i].barcode,ProductInfor[j].barcode)==0)//�������������ProductInformation.txt�Ƚ�
				                                                                                                     //ProductInformation.txt���ڸ���Ʒ����ȡ��Ʒ����Ϣ
			{
				cout.setf(ios::fixed);
				float SubTotal = ProductInfor[j].price*InBarcodeVector[i].AfterDiscountNum;
				Total += SubTotal;
				cout<<"���ƣ�"<<ProductInfor[j].name<<", ����: "<<InBarcodeVector[i].BarcodeCount<<ProductInfor[j].uint
					<<", ����: "<<setprecision(2)<<ProductInfor[j].price<<"(Ԫ), С�ƣ�"<<setprecision(2)<<SubTotal<<"(Ԫ)"<<endl;
				}
			}
	  if(IsDiscount == TRUE)//����з����Żݵ������������Żݵĸ�ʽ��ӡ�嵥
	 {
		   IsDiscount = FALSE;
		   
			cout<<"-----------------------------"<<endl;
			cout<<"��"<<DiscounBuyNum<<"��"<<DiscounNum<<"��Ʒ��"<<endl;
			for(int i =0; i < DiscountProductInfor.size();i++)
				for(int j =0;j<ProductInfor.size();j++)
			{
				
				if(strcmp(DiscountProductInfor[i].IsDiscountbarcode,ProductInfor[j].barcode)==0)
				{
					SaveTotal += ProductInfor[j].price*DiscountProductInfor[i].DiscountNum;//�����ʡ��Ǯ
					cout<<"���ƣ�"<<ProductInfor[j].name<<",���� "<<DiscountProductInfor[i].DiscountNum<<ProductInfor[j].uint<<endl;
				}
			  
			}
			cout<<"-----------------------------"<<endl;
			cout<<"�ܼƣ�"<<setprecision(2)<<Total<<"(Ԫ)"<<endl;
			cout<<"��ʡ�� "<<setprecision(2)<<SaveTotal<<"(Ԫ)"<<endl;
			cout<<"****************************"<<endl;
		}
		else
		{
				
			cout<<"--------------------------"<<endl;
			cout<<"�ܼƣ�"<<setprecision(2)<<Total<<"(Ԫ)"<<endl;
			cout<<"*************************"<<endl;
		}
	return 1;
}

int main()
{
	ReadProductFile();  //��ȡProductInformation.txt�ı����� ���ı�Ϊ��Ʒ����Ϣ�ı�
	ReadDiscountFile();//��ȡDiscountBarcode.txt�ı� ���ı�����Ϊ���õ��Ż�������
	cout<<"����������Ʒ������"<<endl;
	while(1)
	{
	   SetInputBarcode();
	   DiscountJudge();
	   PrintList();
	   cout<<"����������Ʒ������"<<endl;
	   InBarcodeVector.clear();//���vector
	   DiscountProductInfor.clear();
	}
	return 1;
}