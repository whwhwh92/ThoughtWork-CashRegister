#include"ProductInformation.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int ReadProductFile()
{
    ifstream fin("ProductInformation.txt");
	ProductInformation ReadInformation;
    char buf[100] = {0};
	if (! fin.is_open())
	{
	  cout<<"ProductInformation file´ò¿ªÊ§°Ü"<<endl;
	  return 0;
	}
	while(!fin.eof())
	{
	   
	   fin>>ReadInformation.barcode>>ReadInformation.name>>ReadInformation.uint>>ReadInformation.category>>ReadInformation.subcategory>>ReadInformation.price;
	   ProductInfor.push_back(ReadInformation);
	}
	fin.close();
	return 1;
}