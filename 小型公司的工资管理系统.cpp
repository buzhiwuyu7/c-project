#include <iostream>
#include<string>
#include<stdlib.h>
#include<graphics.h>
#include<fstream>
#include <Windows.h>
const int Width = 800, Lengh = 1200;
using namespace std;
int N = 0;
const int Num = 100;
int Num_t = 0, Num_s = 0, Num_m = 0, Num_sm = 0;
class Employee
{
public:
	Employee()
	{
		num = totalnum++;
		salary = 0;
		name = "";
		post = "";
	}
	string getname()
	{
		return this->name;
	}
	int getno()
	{
		return this->num;
	}
	string getpost()
	{
		return this->post;
	}
	double getsalary()
	{
		return this->salary;
	}
	virtual void pay() = 0;   //计算月薪  纯虚函数  基类变为抽象类
	
	~Employee() {};


protected:
	string name;			//姓名
	int num;				//编号
	string post;			//部门
	double salary;			//月薪
	static int totalnum;    //静态数据成员

};

class Technician :public Employee		//兼职技术人员
{
private:
	double hourlyrate;		//每小时酬金
	double workhours;		//当月工作小时数
public:
	Technician() {};
	Technician(string n, double h)
	{
		name = n;
		hourlyrate = 100;	//每小时酬金固定为100
		workhours = h;
		post = "兼职技术人员";
	}
	void pay()
	{
		salary = hourlyrate * workhours;  //计算月薪，按小时计算
	}
};

class Saleman :virtual public Employee			//销售员
{
protected:
	double commrate;		//按销售额提取酬金的百分比
	double sales;			//当月销售额
public:
	Saleman() {};
	Saleman(string n, double s)
	{
		commrate = 0.04;	//销售提成比例为4%
		name = n;
		sales = s;
		post = "销售员";
	}
	void pay()				//计算销售员的月薪函数
	{
		salary = sales * commrate;			//计算月薪=本月销售额*销售提成比例
	}
};

class Manager :virtual public Employee			//经理
{
protected:
	double monthlypay;		//固定月薪
public:
	Manager() {};
	Manager(string n)
	{
		name = n;
		post = "经理";
		monthlypay = 8000;
	}
	void pay()
	{
		salary = monthlypay;
	}
};

class Salemanager :public Manager, public Saleman		//销售经理
{

public:
	Salemanager() {};
	Salemanager(string n, double s):Manager(n),Saleman(n,s)
	{
		monthlypay = 5000;		//固定工资5000
		commrate = 0.005;		//销售提成比例0.5%
		post = "销售经理";
	}
	void pay()
	{
		salary = monthlypay + commrate * sales;		//月薪=固定月薪+销售提成
	}

};

Technician t[Num];
Saleman s[Num];
Manager m[Num];
Salemanager sm[Num];

struct FileImag
{
	char FileNum[20];
	char FileName[20];
	char FileSalary[20];
	char FilePost[20];

}Image[100],ima;


void InitFile();
int Initnum();

void SetMenu();

void Show();
void ShowDraw();

void Add();
void AddManager();
void AddTechnician();
void AddSaleman();
void AddSalemanager();

void SaveManager();
void SaveSalemanager();
void SaveSaleman();
void SaveTechnician();

void Delete();
void Deletefile(string);

void Modify();
void ModifyFile(string);
void SaveAfterModify();

void Find();

int Employee::totalnum = Initnum()+1; //找到文件中已有的数据的最大值，保证每次添加编号有序

int main()
{
	InitFile();
	
	SetMenu();
	return 0;
}

void InitFile()
{
	N = 0;
	FILE* fp = fopen("date.dat", "r");   //打开用户文件，只读
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s\n", &Image[N].FileNum, &Image[N].FileName, &Image[N].FilePost, &Image[N].FileSalary);
			N++;
		}
		if (fclose(fp))
		{
			printf("关闭文件失败!");
		}
		fp = NULL;
	}
}

int Initnum()
{
	InitFile();
	if (N == 0)
	{
		return 9999;
	}
	else
	{
		int max = atoi(Image[0].FileNum);
		for (int i = 0; i < N; i++)
		{
			if (atoi(Image[i].FileNum) > max)
				max = atoi(Image[i].FileNum);
		}
		return max;
	}
}


void SetMenu()
{
		InitFile();
		//创建窗口 确定窗口大小
		initgraph(Lengh, Width);
		setfillcolor(WHITE);
		//设置背景
		IMAGE img;
		loadimage(&img, "./picture.jpg", Lengh, Width);
		putimage(0, 0, &img);

		//大标题
		char MainTitle[] = { "小型公司的工资管理系统" };


		//设置字体为抗锯齿效果
		LOGFONT f;//字体变量
		gettextstyle(&f);
		f.lfHeight = 48;
		strcpy(f.lfFaceName, "楷体");
		f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
		settextstyle(&f);
		outtextxy(230, 100, MainTitle);

		char text0[] = "显示职工工资信息";
		char text1[] = "添加职工工资信息";
		char text2[] = "删除职工工资信息";
		char text3[] = "修改职工工资信息";
		char text4[] = "查找职工工资信息";
		char text5[] = "退出程序";
		

		//设置7个矩形框 

		fillrectangle(330, 205, 660, 250);
		fillrectangle(330, 265, 660, 310);
		fillrectangle(330, 325, 660, 370);
		fillrectangle(330, 385, 660, 430);
		fillrectangle(330, 445, 660, 490);
		fillrectangle(330, 505, 660, 550);
		

		//设置字体 
		setbkmode(TRANSPARENT);
		settextcolor(RGB(66, 75, 150));
		settextstyle(40, 0, "楷体");
		//书写内容

		outtextxy(340, 210, text0);
		outtextxy(340, 270, text1);
		outtextxy(340, 330, text2);
		outtextxy(340, 390, text3);
		outtextxy(340, 450, text4);
		outtextxy(340, 510, text5);
		


		//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
		MOUSEMSG m1;
		while (1)
		{
			m1 = GetMouseMsg();//获取鼠标操作
			if (m1.x >= 330 && m1.x <= 660 && m1.y >= 205 && m1.y <= 250)
			{

				if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
				{
					//显示职工工资信息
					Show();
				}
			}

			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 265 && m1.y <= 310)
			{

				if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
				{
					//添加职工工资信息
					Add();
				}
			}

			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 325 && m1.y <= 370)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//删除职工工资信息
					
					Delete();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 385 && m1.y <= 430)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//修改职工工资信息

					Modify();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 445 && m1.y <= 490)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//查询职工工资信息
					Find();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 505 && m1.y <= 550)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//退出程序
					exit(0);
				}
			}
		}

		getchar();
		//关闭窗口
		closegraph();
}


void ShowDraw()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "显示职工工资信息");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture3.jpg", Lengh, Width);
	putimage(0, 0, &img);

	//大标题
	char MainTitle[] = { "职工薪资情况" };


	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);
	outtextxy(600, 50, MainTitle);

	char text1[] = "职工编号";
	char text2[] = "职工姓名";
	char text3[] = "职工职位";
	char text4[] = "职工薪资";
	char text5[] = "上一页";
	char text6[] = "返回";
	char text7[] = "下一页";

	setlinecolor(BLACK);

	//绘制表格
	fillrectangle(330, 100, 1150, 700);
	fillrectangle(400, 720, 550, 760);
	fillrectangle(650, 720, 800, 760);
	fillrectangle(900, 720, 1050, 760);
	line(330, 150, 1150, 150);
	line(330, 200, 1150, 200);
	line(330, 250, 1150, 250);
	line(330, 300, 1150, 300);
	line(330, 350, 1150, 350);
	line(330, 400, 1150, 400);
	line(330, 450, 1150, 450);
	line(330, 500, 1150, 500);
	line(330, 550, 1150, 550);
	line(330, 600, 1150, 600);
	line(330, 650, 1150, 650);
	line(330, 700, 1150, 700);
	line(530, 100, 530, 700);
	line(730, 100, 730, 700);
	line(930, 100, 930, 700);

	//设置字体 
	setbkmode(TRANSPARENT);
	settextcolor(RGB(66, 75, 150));
	settextstyle(24, 0, "楷体");

	outtextxy(340, 120, text1);
	outtextxy(540, 120, text2);
	outtextxy(740, 120, text3);
	outtextxy(940, 120, text4);
	outtextxy(435, 730, text5);
	outtextxy(700, 730, text6);
	outtextxy(935, 730, text7);
}
void Show()
{
	ShowDraw();
	int i = 1,k=155,j,page=1;
	bool fill = false;
	while (i <= N && i<=11)
	{
		setbkmode(TRANSPARENT);
		settextcolor(RGB(66, 75, 150));
		settextstyle(24, 0, "楷体");

		outtextxy(340, k, Image[i-1].FileNum);
		outtextxy(540, k, Image[i-1].FileName);
		outtextxy(740, k, Image[i-1].FilePost);
		outtextxy(940, k, Image[i-1].FileSalary);
		
		k += 50;
		i++;
	}
	EndBatchDraw();

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 550  && msg.y >= 720 && msg.y <= 760 )
			{

				if (page == 1)
				{
					MessageBox(GetHWnd(), "已是第一页", "注意！！！", MB_OK);
				}
				else
				{
					if (i > 0)
					{
						i -= 11;
						page--;
						ShowDraw();
						k = 155;
						j = 1 + 11 * (page - 1);
						while (j <= N)
						{

							//设置字体 
							setbkmode(TRANSPARENT);
							settextcolor(RGB(66, 75, 150));
							settextstyle(24, 0, "楷体");

							outtextxy(340, k, Image[j - 1].FileNum);
							outtextxy(540, k, Image[j - 1].FileName);
							outtextxy(740, k, Image[j - 1].FilePost);
							outtextxy(940, k, Image[j - 1].FileSalary);
							if (j % 11 == 0)
							{

								break;
							}

							k += 50;
							j++;
						}
						EndBatchDraw();
					}
					
				}
			}
	
			if (msg.x >= 900 && msg.x <= 1050  && msg.y >= 720 && msg.y <= 760)
			{

				if (i < N)
				{
					page++;
					ShowDraw();
					k = 150;
					i = (page - 1) * 11 + 1;
					while (i <= N )
					{
						
						//设置字体 
						setbkmode(TRANSPARENT);
						settextcolor(RGB(66, 75, 150));
						settextstyle(24, 0, "楷体");

						outtextxy(340, k, Image[i-1].FileNum);
						outtextxy(540, k, Image[i-1].FileName);
						outtextxy(740, k, Image[i-1].FilePost);
						outtextxy(940, k, Image[i-1].FileSalary);

						k += 50;
						if (i % 11 == 0)
						{
							
							i++;
							break;
						}
						i++;
					}
					EndBatchDraw();
				}
				else
				{
					MessageBox(GetHWnd(), "已是最后一页", "注意！！！", MB_OK);
				}
			}
			if (msg.x >= 650 && msg.x <= 800 && msg.y >= 720 && msg.y <= 760)
			{
				SetMenu();
			}
		}
	}
}


void Add()
{
	Num_t = 0, Num_s = 0, Num_m = 0, Num_sm = 0;
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "添加职工工资信息");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "添加经理";
	char text2[] = "添加兼职技术人员";
	char text3[] = "添加销售员";
	char text4[] = "添加销售经理";
	char text5[] = "返回";


	fillrectangle(330, 120, 660, 180);
	fillrectangle(330, 240, 660, 300);
	fillrectangle(330, 360, 660, 420);
	fillrectangle(330, 480, 660, 540);
	fillrectangle(330, 600, 660, 660);



	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 130, text1);
	outtextxy(340, 250, text2);
	outtextxy(340, 370, text3);
	outtextxy(340, 490, text4);
	outtextxy(340, 610, text5);
	
	
	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 120 && m1.y <= 180)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				AddManager();
			}
		}

		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 240 && m1.y <= 300)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				AddTechnician();
			}
		}
		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 360 && m1.y <= 420)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				AddSaleman();
			}
		}
		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 480 && m1.y <= 540)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				AddSalemanager();
			}
		}
		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 600 && m1.y <= 660)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				InitFile();
				SetMenu();
			}
		}
		
	}
	

	getchar();
	//关闭窗口
	closegraph();
}
void AddManager()
{
	
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "添加经理");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "输入经理信息";
	char text2[] = "返回";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入添加经理的姓名");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);				  //提示用户输入信息date1，作为经理的姓名
				m[Num_m] = Manager(date1);							  //利用对象数组，调用构造函数
				m[Num_m].pay();
				Num_m++;

			}
		}

		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 470 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SaveManager();
				Add();
			}
		}

	}

}
void AddTechnician()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "添加兼职技术人员");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "输入兼职技术人员信息";
	char text2[] = "返回";

	fillrectangle(330, 310, 760, 370);
	fillrectangle(330, 470, 760, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 760 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入添加兼职技术人员的姓名");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);	 //提示用户输入信息date1，作为技术员的姓名

				char date2[64];
				TCHAR InputWindowFI2[] = _T("请输入添加兼职技术人员的工作时间");  //自动转换字符类型
				InputBox(date2, 20, InputWindowFI2);	 //提示用户输入信息date1，作为技术员的的工作时间
				double hour = atoi(date2);				//atoi函数可以将字符型数据转换为整型数据

				t[Num_t] = Technician(date1,hour);		//利用对象数组，调用构造函数
				t[Num_t].pay();
				Num_t++;
			}
		}

		else if (m1.x >= 330 && m1.x <= 760 && m1.y >= 470 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SaveTechnician();
				Add();
			}
		}

	}

}
void AddSaleman()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "添加销售员");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "输入销售员信息";
	char text2[] = "返回";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入添加销售员的姓名");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);		//提示用户输入信息date1，作为销售员的姓名

				char date2[64];
				TCHAR InputWindowFI2[] = _T("请输入添加销售员的当月销售额");  //自动转换字符类型
				InputBox(date2, 20, InputWindowFI2);		//提示用户输入信息date2，作为销售员的销售额
				double sales = atoi(date2);					//atoi函数可以将字符型数据转换为整型数据

				s[Num_s] = Saleman(date1, sales);			//利用对象数组，调用构造函数
				s[Num_s].pay();
				Num_s++;
			}
		}

		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 470 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SaveSaleman();
				Add();
			}
		}

	}

}
void AddSalemanager()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "添加销售经理");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);


	char text1[] = "输入销售经理信息";
	char text2[] = "返回";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入添加销售经理的姓名");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);			//提示用户输入信息date1，作为销售经理的姓名

				char date2[64];
				TCHAR InputWindowFI2[] = _T("请输入添加销售经理所管部门的销售额");  //自动转换字符类型
				InputBox(date2, 20, InputWindowFI2);			//提示用户输入信息date2，作为销售经理所管部门的销售额
				double sales = atoi(date2);						//atoi函数可以将字符型数据转换为整型数据

				sm[Num_sm] = Salemanager(date1, sales);			//利用对象数组，调用构造函数
				sm[Num_sm].pay();
				Num_sm++;
			}
		}

		else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 470 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SaveSalemanager();
				Add();
			}
		}

	}

}


void Delete()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "删除职工工资信息");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture4.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "输入要删除的职工的编号";
	char text2[] = "        返回";

	fillrectangle(330, 200, 880, 280);
	fillrectangle(330, 450, 880, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(350, 460, text2);
	
	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 850 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入要删除的职工的编号");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);
				string str = date1;
				Deletefile(str);
			}
		}

		else if (m1.x >= 330 && m1.x <= 850 && m1.y >= 450 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SetMenu();
			}
		}
	}
}
void Deletefile(string str)
{
	bool find = false;
	for (int i = 0; i < N; i++)
	{
		if (Image[i].FileNum == str)
		{
			find = true;
			ofstream ofs("deletefile.txt", ios::trunc | ios::out);
			for (int i = 0; i < N; i++)
			{
				if (Image[i].FileNum != str)
				{
					ofs << Image[i].FileNum << "    " << Image[i].FileName << "    " << Image[i].FilePost << "    " << Image[i].FileSalary << endl;
				}
			}
			CopyFile("deletefile.txt", "date.dat", false);
			InitFile();
			ofs.close();
		}
	}
	if (find)
	{
		MessageBox(GetHWnd(), "该职工的信息已删除！", "提示", MB_OK);
	}
	else
	{
		MessageBox(GetHWnd(), "未找到你想删除的职工信息！", "提示", MB_OK);
	}
}


void Modify()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "修改职工工资信息");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture5.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "请输入要修改的职工的编号";
	char text2[] = "        返回";

	fillrectangle(330, 200, 950, 280);
	fillrectangle(330, 450, 950, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(400, 460, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 950 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入要修改的职工的编号（编号从10000开始）");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);
				string str = date1;
				ModifyFile(str);

			}
		}

		else if (m1.x >= 330 && m1.x <= 950 && m1.y >= 450 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SetMenu();
			}
		}

	}
}
void ModifyFile(string str)
{
	bool find = false;
	for (int i = 0; i < N; i++)
	{
		if (Image[i].FileNum == str)
		{
			find = true;
			//获取窗口句柄
			HWND hnd = GetHWnd();
			//设置窗口标题
			SetWindowText(hnd, "查找职工工资信息");
			//图片绘制
			IMAGE img;
			loadimage(&img, "./picture5.jpg", Lengh, Width);
			putimage(0, 0, &img);

			//大标题
			char MainTitle[] = { "您要修改的职工信息为" };
			char text[] = "返回";
			char text1[] = "职工编号";
			char text2[] = "职工姓名";
			char text3[] = "职工职位";
			char text4[] = "职工薪资";
			char text5[] = "修改姓名";
			char text6[] = "修改职位";
			char text7[] = "修改薪资";

			//设置字体 
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(40, 0, "楷体");

			outtextxy(400, 50, MainTitle);

			fillrectangle(550, 300, 750, 350);
			fillrectangle(550, 400, 750, 450);
			fillrectangle(550, 500, 750, 550);
			fillrectangle(550, 600, 750, 650);

			outtextxy(140, 120, text1);
			outtextxy(340, 120, text2);
			outtextxy(540, 120, text3);
			outtextxy(740, 120, text4);
			outtextxy(140, 170, Image[i].FileNum);
			outtextxy(340, 170, Image[i].FileName);
			outtextxy(540, 170, Image[i].FilePost);
			outtextxy(740, 170, Image[i].FileSalary);
			outtextxy(560, 310, text5);
			outtextxy(560, 410, text6);
			outtextxy(560, 510, text7);
			outtextxy(560, 610, text);


			//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
			MOUSEMSG m1;
			while (1)
			{
				m1 = GetMouseMsg();//获取鼠标操作
				if (m1.x >= 550 && m1.x <= 750 && m1.y >= 600 && m1.y <= 650)		//返回
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
					{
						SaveAfterModify();
						Modify();
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 300 && m1.y <= 350)		//修改姓名
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
					{
						char date1[64];
						TCHAR InputWindowFI1[] = _T("请输入修改后的姓名");  //自动转换字符类型
						InputBox(date1, 20, InputWindowFI1);
						strcpy(Image[i].FileName , date1);
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 400 && m1.y <= 450)		//修改职位
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
					{
						char date2[64];
						TCHAR InputWindowFI1[] = _T("请输入修改后的职位");  //自动转换字符类型
						InputBox(date2, 20, InputWindowFI1);
						strcpy(Image[i].FilePost, date2);
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 500 && m1.y <= 550)		//修改薪资
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
					{
						char date3[64];
						TCHAR InputWindowFI1[] = _T("请输入修改后的薪资");  //自动转换字符类型
						InputBox(date3, 20, InputWindowFI1);
						strcpy(Image[i].FileSalary, date3);
					}
				}

			}

		}

	}

	if (!find)
	{
		MessageBox(GetHWnd(), "未找到你想修改的职工信息", "提示", MB_OK);
	}

}
void SaveAfterModify()
{

	ofstream ofs("modifyfile.txt", ios::trunc|ios::out);

	for (int i = 0; i < N; i++)
	{
		ofs << Image[i].FileNum << "    " << Image[i].FileName << "    " << Image[i].FilePost << "    " << Image[i].FileSalary << endl;
	}
	
	CopyFile("modifyfile.txt", "date.dat", false);
	InitFile();
	ofs.close();
}


void Find()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "查找职工工资信息");
	//图片绘制
	IMAGE img;
	loadimage(&img, "./picture2.jpg", Lengh, Width);
	putimage(0, 0, &img);

	setfillcolor(RGB(103,174,220));
	char text1[] = "输入要查询的职工姓名";
	char text2[] = "        返回";

	fillrectangle(330, 200, 850, 280);
	fillrectangle(330, 450, 850, 530);

	//设置字体为抗锯齿效果
	LOGFONT f;//字体变量
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;//打磨字体 使字体变得更加光滑
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(340, 460, text2);

	//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 330 && m1.x <= 850 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("请输入要查询的职工姓名");  //自动转换字符类型
				InputBox(date1, 20, InputWindowFI1);
				string str = date1;
				bool find = false;
				for (int i = 0; i < N; i++)
				{
					if (Image[i].FileName == str)
					{
						find = true;
						//获取窗口句柄
						HWND hnd = GetHWnd();
						//设置窗口标题
						SetWindowText(hnd, "查找职工工资信息");
						//图片绘制
						IMAGE img;
						loadimage(&img, "./picture2.jpg", Lengh, Width);
						putimage(0, 0, &img);

						//大标题
						char MainTitle[] = { "您查找的职工信息为" };
						char text[] = "返回";
						char text1[] = "职工编号";
						char text2[] = "职工姓名";
						char text3[] = "职工职位";
						char text4[] = "职工薪资";
						//设置字体 
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						settextstyle(40, 0, "楷体");

						outtextxy(400, 50, MainTitle);

						fillrectangle(550, 600, 650, 650);

						outtextxy(140, 120, text1);
						outtextxy(340, 120, text2);
						outtextxy(540, 120, text3);
						outtextxy(740, 120, text4);
						outtextxy(140, 170, Image[i].FileNum);
						outtextxy(340, 170, Image[i].FileName);
						outtextxy(540, 170, Image[i].FilePost);
						outtextxy(740, 170, Image[i].FileSalary);
						outtextxy(560, 610, text);

						//鼠标操作,根据鼠标点击的不同位置跳转到不同函数
						MOUSEMSG m1;
						while (1)
						{
							m1 = GetMouseMsg();//获取鼠标操作
							if (m1.x >= 550 && m1.x <= 650 && m1.y >= 600 && m1.y <= 650)
							{

								if (m1.uMsg == WM_LBUTTONDOWN) //右键单击一次触发 
								{
									Find();
								}
							}

						}
					}
				}
				if(!find)
				MessageBox(GetHWnd(), "未找到该职工信息", "提示", MB_OK);
			}
		}

		else if (m1.x >= 330 && m1.x <= 850 && m1.y >= 450 && m1.y <= 530)
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				SetMenu();
			}
		}

	}
}


void SaveManager()
{
	ofstream ofs("date.dat", ios::out | ios::app);
	if (!ofs)
	{
		cout << "文件打开失败" << endl;
		return;
	}
	for (int i = 0; i < Num_m; i++)
	{
		ofs << m[i].getno() << "    " << m[i].getname() << "    " << m[i].getpost() << "    " << m[i].getsalary() << endl;
	}
	ofs.close();
}
void SaveSalemanager()
{
	ofstream ofs("date.dat", ios::out | ios::app);
	if (!ofs)
	{
		cout << "文件打开失败" << endl;
		return;
	}
	for (int i = 0; i < Num_sm; i++)
	{
		ofs << sm[i].getno() << "    " << sm[i].getname() << "    " << sm[i].getpost() << "    " << sm[i].getsalary() << endl;
	}
	ofs.close();
}
void SaveSaleman()
{
	ofstream ofs("date.dat", ios::out | ios::app);
	if (!ofs)
	{
		cout << "文件打开失败" << endl;
		return;
	}
	for (int i = 0; i < Num_s; i++)
	{
		ofs << s[i].getno() << "    " << s[i].getname() << "    " << s[i].getpost() << "    " << s[i].getsalary() << endl;
	}
	ofs.close();
}
void SaveTechnician()
{
	ofstream ofs("date.dat", ios::out | ios::app);
	if (!ofs)
	{
		cout << "文件打开失败" << endl;
		return;
	}
	for (int i = 0; i < Num_t; i++)
	{
		ofs << t[i].getno() << "    " << t[i].getname() << "    " << t[i].getpost() << "    " << t[i].getsalary() << endl;
	}
	ofs.close();
}