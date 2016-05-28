/*
  说明1:商品的信息存在ProductInformation.txt文本中 
            店员设置优惠的条形码存在DiscountBarcode.txt文本中
  说明2:在控制台中输入条形码结束后 换行输入字符“#”在按回车键即可输出商品清单
*/
#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include"ProductInformation.h"
#include"DiscountBarcode.h"
#include"stdlib.h"
using namespace std;
#define BarcodeNum 20  //条形码的字符数
#define DiscounBuyNum  3  //买入多少个商品就有优惠
#define  DiscounNum   1   //优惠多少个商品
#define FALSE   0
#define TRUE    1
bool IsDiscount = FALSE; //IsDiscount TRUE 打折 FALSE不打折
typedef struct InputBarcode//输入条形码信息
{
  char barcode[BarcodeNum];//条形码
  int BarcodeCount;                //该条形码所对应的数量
  int AfterDiscountNum;        //优惠后该条形码所对应商品数量
}InputBarcode;
typedef struct DiscountProductInformation//买入商品中需要打折商品的信息
{
   char IsDiscountbarcode[BarcodeNum];//条形码
   int DiscountNum; //优惠的数量
}DiscountProductInformation;
vector<ProductInformation> ProductInfor; //存储商品信息向量
vector<DiscountBarcode> DiscountBar;    //存储店员设置的优惠条形码向量
vector<InputBarcode> InBarcodeVector;//存储从控制台输入的条形码向量
vector<DiscountProductInformation> DiscountProductInfor;//存储符合“买三免一”的买入商品信息向量
/*
  字符分割 如果输入的条形码格式为 barcode-num 则将按照此函数分割
*/
InputBarcode CutString(char str[])
{
	  InputBarcode TempInbarcode;
   	char *psplit = strtok(str,"-");//按照“-”分割
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
  从控制台中读取条形码，将读取条形码的信息存储在InBarcodeVector
  注意：在输入完条形码后，需要在隔行输入字符“#”s说明这次输入结束
*/
int SetInputBarcode()
{
  InputBarcode Inbarcode;

   while (1)
   {
	   cin.getline(Inbarcode.barcode,100);
	    bool BarcodeRepeatFlag= FALSE ;//输入的条形码是否在之前就输入的标志位
		if(strcmp(Inbarcode.barcode,"#")==NULL)//输入“#” 本次输入结束
		{
		   break;
		}
		if(strstr(Inbarcode.barcode,"-"))//输入barcode-num样式 信息的读取
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
			
		   for(int i =0;i<InBarcodeVector.size();i++)//若在该条形码已经在之前输入了 则在该条形码的数量上加1 而该结构体不在压入vector
	      {
		   if(strcmp(Inbarcode.barcode,InBarcodeVector[i].barcode)==0)//判断输入的条形码是否已经存在 
		    {
				
				   InBarcodeVector[i].BarcodeCount++;  
			       InBarcodeVector[i].AfterDiscountNum = InBarcodeVector[i].BarcodeCount;
			      BarcodeRepeatFlag = TRUE;
				
		     
		    }
	     }
		if(BarcodeRepeatFlag == FALSE)//输入的条形码在之前没有输入 则将条形码及其数量压入vector
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
   该函数判断输入的条形码中是否有符合“买三免一”的商品，
   如果有商品则将条形码和数量压入DiscountProductInfor向量中
*/
int  DiscountJudge()
{
	DiscountProductInformation DiscountProduct;
    for(int i =0;i<InBarcodeVector.size();i++)
		for(int j =0;j<DiscountBar.size()-1;j++)
		{
			if(strcmp(InBarcodeVector[i].barcode,DiscountBar[j+1].barcode)==NULL)//判断输入的条形码是否是优惠条形码
			{
				
				if(InBarcodeVector[i].BarcodeCount>=DiscounBuyNum)//判断该商品买入的数量是否>=3
				{
					strcpy(DiscountProduct.IsDiscountbarcode,InBarcodeVector[i].barcode);
					int multiple = InBarcodeVector[i].BarcodeCount/DiscounBuyNum;//买3免1 买6免2 .......
					InBarcodeVector[i].AfterDiscountNum -= multiple;
					DiscountProduct.DiscountNum = multiple;
				    IsDiscount = TRUE;//将该商品设置为优惠商品
					DiscountProductInfor.push_back(DiscountProduct);//压入到向量
				    memset(DiscountProduct.IsDiscountbarcode,0,BarcodeNum);
				}
				
			}
			
		}
		return 1;
}
/*
 该函数是打印商品清单模块 将根据控制台输入的条形码与存在ProductInformation.txt中的商品信息
 进行比较并打印商品清单，如果存在“买三免一”商品，则打印优惠清单
*/
int PrintList()
{
	   float Total = 0;//买入商品总价（总计）
	   float SaveTotal = 0;//每个商品的总价（小计）
	   cout<<"*****<没钱赚商店>购物清单*****"<<endl;
        for(int i =0;i<InBarcodeVector.size();i++)
			for(int j =0;j<ProductInfor.size();j++)
			{
			if(strcmp(InBarcodeVector[i].barcode,ProductInfor[j].barcode)==0)//输入的条形码与ProductInformation.txt比较
				                                                                                                     //ProductInformation.txt存在该商品就提取商品的信息
			{
				cout.setf(ios::fixed);
				float SubTotal = ProductInfor[j].price*InBarcodeVector[i].AfterDiscountNum;
				Total += SubTotal;
				cout<<"名称："<<ProductInfor[j].name<<", 数量: "<<InBarcodeVector[i].BarcodeCount<<ProductInfor[j].uint
					<<", 单价: "<<setprecision(2)<<ProductInfor[j].price<<"(元), 小计："<<setprecision(2)<<SubTotal<<"(元)"<<endl;
				}
			}
	  if(IsDiscount == TRUE)//如果有符合优惠的条件，则按照优惠的格式打印清单
	 {
		   IsDiscount = FALSE;
		   
			cout<<"-----------------------------"<<endl;
			cout<<"买"<<DiscounBuyNum<<"免"<<DiscounNum<<"商品："<<endl;
			for(int i =0; i < DiscountProductInfor.size();i++)
				for(int j =0;j<ProductInfor.size();j++)
			{
				
				if(strcmp(DiscountProductInfor[i].IsDiscountbarcode,ProductInfor[j].barcode)==0)
				{
					SaveTotal += ProductInfor[j].price*DiscountProductInfor[i].DiscountNum;//计算节省的钱
					cout<<"名称："<<ProductInfor[j].name<<",数量 "<<DiscountProductInfor[i].DiscountNum<<ProductInfor[j].uint<<endl;
				}
			  
			}
			cout<<"-----------------------------"<<endl;
			cout<<"总计："<<setprecision(2)<<Total<<"(元)"<<endl;
			cout<<"节省： "<<setprecision(2)<<SaveTotal<<"(元)"<<endl;
			cout<<"****************************"<<endl;
		}
		else
		{
				
			cout<<"--------------------------"<<endl;
			cout<<"总计："<<setprecision(2)<<Total<<"(元)"<<endl;
			cout<<"*************************"<<endl;
		}
	return 1;
}

int main()
{
	ReadProductFile();  //读取ProductInformation.txt文本内容 该文本为商品的信息文本
	ReadDiscountFile();//读取DiscountBarcode.txt文本 该文本内容为设置的优惠条形码
	cout<<"输入买入商品条形码"<<endl;
	while(1)
	{
	   SetInputBarcode();
	   DiscountJudge();
	   PrintList();
	   cout<<"输入买入商品条形码"<<endl;
	   InBarcodeVector.clear();//清除vector
	   DiscountProductInfor.clear();
	}
	return 1;
}