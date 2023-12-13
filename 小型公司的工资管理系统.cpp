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
	virtual void pay() = 0;   //������н  ���麯��  �����Ϊ������
	
	~Employee() {};


protected:
	string name;			//����
	int num;				//���
	string post;			//����
	double salary;			//��н
	static int totalnum;    //��̬���ݳ�Ա

};

class Technician :public Employee		//��ְ������Ա
{
private:
	double hourlyrate;		//ÿСʱ���
	double workhours;		//���¹���Сʱ��
public:
	Technician() {};
	Technician(string n, double h)
	{
		name = n;
		hourlyrate = 100;	//ÿСʱ���̶�Ϊ100
		workhours = h;
		post = "��ְ������Ա";
	}
	void pay()
	{
		salary = hourlyrate * workhours;  //������н����Сʱ����
	}
};

class Saleman :virtual public Employee			//����Ա
{
protected:
	double commrate;		//�����۶���ȡ���İٷֱ�
	double sales;			//�������۶�
public:
	Saleman() {};
	Saleman(string n, double s)
	{
		commrate = 0.04;	//������ɱ���Ϊ4%
		name = n;
		sales = s;
		post = "����Ա";
	}
	void pay()				//��������Ա����н����
	{
		salary = sales * commrate;			//������н=�������۶�*������ɱ���
	}
};

class Manager :virtual public Employee			//����
{
protected:
	double monthlypay;		//�̶���н
public:
	Manager() {};
	Manager(string n)
	{
		name = n;
		post = "����";
		monthlypay = 8000;
	}
	void pay()
	{
		salary = monthlypay;
	}
};

class Salemanager :public Manager, public Saleman		//���۾���
{

public:
	Salemanager() {};
	Salemanager(string n, double s):Manager(n),Saleman(n,s)
	{
		monthlypay = 5000;		//�̶�����5000
		commrate = 0.005;		//������ɱ���0.5%
		post = "���۾���";
	}
	void pay()
	{
		salary = monthlypay + commrate * sales;		//��н=�̶���н+�������
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

int Employee::totalnum = Initnum()+1; //�ҵ��ļ������е����ݵ����ֵ����֤ÿ����ӱ������

int main()
{
	InitFile();
	
	SetMenu();
	return 0;
}

void InitFile()
{
	N = 0;
	FILE* fp = fopen("date.dat", "r");   //���û��ļ���ֻ��
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %s\n", &Image[N].FileNum, &Image[N].FileName, &Image[N].FilePost, &Image[N].FileSalary);
			N++;
		}
		if (fclose(fp))
		{
			printf("�ر��ļ�ʧ��!");
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
		//�������� ȷ�����ڴ�С
		initgraph(Lengh, Width);
		setfillcolor(WHITE);
		//���ñ���
		IMAGE img;
		loadimage(&img, "./picture.jpg", Lengh, Width);
		putimage(0, 0, &img);

		//�����
		char MainTitle[] = { "С�͹�˾�Ĺ��ʹ���ϵͳ" };


		//��������Ϊ�����Ч��
		LOGFONT f;//�������
		gettextstyle(&f);
		f.lfHeight = 48;
		strcpy(f.lfFaceName, "����");
		f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
		settextstyle(&f);
		outtextxy(230, 100, MainTitle);

		char text0[] = "��ʾְ��������Ϣ";
		char text1[] = "���ְ��������Ϣ";
		char text2[] = "ɾ��ְ��������Ϣ";
		char text3[] = "�޸�ְ��������Ϣ";
		char text4[] = "����ְ��������Ϣ";
		char text5[] = "�˳�����";
		

		//����7�����ο� 

		fillrectangle(330, 205, 660, 250);
		fillrectangle(330, 265, 660, 310);
		fillrectangle(330, 325, 660, 370);
		fillrectangle(330, 385, 660, 430);
		fillrectangle(330, 445, 660, 490);
		fillrectangle(330, 505, 660, 550);
		

		//�������� 
		setbkmode(TRANSPARENT);
		settextcolor(RGB(66, 75, 150));
		settextstyle(40, 0, "����");
		//��д����

		outtextxy(340, 210, text0);
		outtextxy(340, 270, text1);
		outtextxy(340, 330, text2);
		outtextxy(340, 390, text3);
		outtextxy(340, 450, text4);
		outtextxy(340, 510, text5);
		


		//������,����������Ĳ�ͬλ����ת����ͬ����
		MOUSEMSG m1;
		while (1)
		{
			m1 = GetMouseMsg();//��ȡ������
			if (m1.x >= 330 && m1.x <= 660 && m1.y >= 205 && m1.y <= 250)
			{

				if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
				{
					//��ʾְ��������Ϣ
					Show();
				}
			}

			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 265 && m1.y <= 310)
			{

				if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
				{
					//���ְ��������Ϣ
					Add();
				}
			}

			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 325 && m1.y <= 370)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//ɾ��ְ��������Ϣ
					
					Delete();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 385 && m1.y <= 430)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//�޸�ְ��������Ϣ

					Modify();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 445 && m1.y <= 490)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//��ѯְ��������Ϣ
					Find();
				}
			}
			else if (m1.x >= 330 && m1.x <= 660 && m1.y >= 505 && m1.y <= 550)
			{

				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					//�˳�����
					exit(0);
				}
			}
		}

		getchar();
		//�رմ���
		closegraph();
}


void ShowDraw()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "��ʾְ��������Ϣ");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture3.jpg", Lengh, Width);
	putimage(0, 0, &img);

	//�����
	char MainTitle[] = { "ְ��н�����" };


	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);
	outtextxy(600, 50, MainTitle);

	char text1[] = "ְ�����";
	char text2[] = "ְ������";
	char text3[] = "ְ��ְλ";
	char text4[] = "ְ��н��";
	char text5[] = "��һҳ";
	char text6[] = "����";
	char text7[] = "��һҳ";

	setlinecolor(BLACK);

	//���Ʊ��
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

	//�������� 
	setbkmode(TRANSPARENT);
	settextcolor(RGB(66, 75, 150));
	settextstyle(24, 0, "����");

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
		settextstyle(24, 0, "����");

		outtextxy(340, k, Image[i-1].FileNum);
		outtextxy(540, k, Image[i-1].FileName);
		outtextxy(740, k, Image[i-1].FilePost);
		outtextxy(940, k, Image[i-1].FileSalary);
		
		k += 50;
		i++;
	}
	EndBatchDraw();

	//������,����������Ĳ�ͬλ����ת����ͬ����
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 550  && msg.y >= 720 && msg.y <= 760 )
			{

				if (page == 1)
				{
					MessageBox(GetHWnd(), "���ǵ�һҳ", "ע�⣡����", MB_OK);
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

							//�������� 
							setbkmode(TRANSPARENT);
							settextcolor(RGB(66, 75, 150));
							settextstyle(24, 0, "����");

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
						
						//�������� 
						setbkmode(TRANSPARENT);
						settextcolor(RGB(66, 75, 150));
						settextstyle(24, 0, "����");

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
					MessageBox(GetHWnd(), "�������һҳ", "ע�⣡����", MB_OK);
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "���ְ��������Ϣ");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "��Ӿ���";
	char text2[] = "��Ӽ�ְ������Ա";
	char text3[] = "�������Ա";
	char text4[] = "������۾���";
	char text5[] = "����";


	fillrectangle(330, 120, 660, 180);
	fillrectangle(330, 240, 660, 300);
	fillrectangle(330, 360, 660, 420);
	fillrectangle(330, 480, 660, 540);
	fillrectangle(330, 600, 660, 660);



	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 130, text1);
	outtextxy(340, 250, text2);
	outtextxy(340, 370, text3);
	outtextxy(340, 490, text4);
	outtextxy(340, 610, text5);
	
	
	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 120 && m1.y <= 180)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
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
	//�رմ���
	closegraph();
}
void AddManager()
{
	
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "��Ӿ���");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "���뾭����Ϣ";
	char text2[] = "����";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("��������Ӿ��������");  //�Զ�ת���ַ�����
				InputBox(date1, 20, InputWindowFI1);				  //��ʾ�û�������Ϣdate1����Ϊ���������
				m[Num_m] = Manager(date1);							  //���ö������飬���ù��캯��
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "��Ӽ�ְ������Ա");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "�����ְ������Ա��Ϣ";
	char text2[] = "����";

	fillrectangle(330, 310, 760, 370);
	fillrectangle(330, 470, 760, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 760 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("��������Ӽ�ְ������Ա������");  //�Զ�ת���ַ�����
				InputBox(date1, 20, InputWindowFI1);	 //��ʾ�û�������Ϣdate1����Ϊ����Ա������

				char date2[64];
				TCHAR InputWindowFI2[] = _T("��������Ӽ�ְ������Ա�Ĺ���ʱ��");  //�Զ�ת���ַ�����
				InputBox(date2, 20, InputWindowFI2);	 //��ʾ�û�������Ϣdate1����Ϊ����Ա�ĵĹ���ʱ��
				double hour = atoi(date2);				//atoi�������Խ��ַ�������ת��Ϊ��������

				t[Num_t] = Technician(date1,hour);		//���ö������飬���ù��캯��
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "�������Ա");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "��������Ա��Ϣ";
	char text2[] = "����";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("�������������Ա������");  //�Զ�ת���ַ�����
				InputBox(date1, 20, InputWindowFI1);		//��ʾ�û�������Ϣdate1����Ϊ����Ա������

				char date2[64];
				TCHAR InputWindowFI2[] = _T("�������������Ա�ĵ������۶�");  //�Զ�ת���ַ�����
				InputBox(date2, 20, InputWindowFI2);		//��ʾ�û�������Ϣdate2����Ϊ����Ա�����۶�
				double sales = atoi(date2);					//atoi�������Խ��ַ�������ת��Ϊ��������

				s[Num_s] = Saleman(date1, sales);			//���ö������飬���ù��캯��
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "������۾���");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture.jpg", Lengh, Width);
	putimage(0, 0, &img);


	char text1[] = "�������۾�����Ϣ";
	char text2[] = "����";

	fillrectangle(330, 310, 660, 370);
	fillrectangle(330, 470, 660, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 40;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 320, text1);
	outtextxy(340, 480, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 660 && m1.y >= 310 && m1.y <= 370)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("������������۾��������");  //�Զ�ת���ַ�����
				InputBox(date1, 20, InputWindowFI1);			//��ʾ�û�������Ϣdate1����Ϊ���۾��������

				char date2[64];
				TCHAR InputWindowFI2[] = _T("������������۾������ܲ��ŵ����۶�");  //�Զ�ת���ַ�����
				InputBox(date2, 20, InputWindowFI2);			//��ʾ�û�������Ϣdate2����Ϊ���۾������ܲ��ŵ����۶�
				double sales = atoi(date2);						//atoi�������Խ��ַ�������ת��Ϊ��������

				sm[Num_sm] = Salemanager(date1, sales);			//���ö������飬���ù��캯��
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "ɾ��ְ��������Ϣ");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture4.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "����Ҫɾ����ְ���ı��";
	char text2[] = "        ����";

	fillrectangle(330, 200, 880, 280);
	fillrectangle(330, 450, 880, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(350, 460, text2);
	
	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 850 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("������Ҫɾ����ְ���ı��");  //�Զ�ת���ַ�����
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
		MessageBox(GetHWnd(), "��ְ������Ϣ��ɾ����", "��ʾ", MB_OK);
	}
	else
	{
		MessageBox(GetHWnd(), "δ�ҵ�����ɾ����ְ����Ϣ��", "��ʾ", MB_OK);
	}
}


void Modify()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "�޸�ְ��������Ϣ");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture5.jpg", Lengh, Width);
	putimage(0, 0, &img);

	char text1[] = "������Ҫ�޸ĵ�ְ���ı��";
	char text2[] = "        ����";

	fillrectangle(330, 200, 950, 280);
	fillrectangle(330, 450, 950, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(400, 460, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 950 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("������Ҫ�޸ĵ�ְ���ı�ţ���Ŵ�10000��ʼ��");  //�Զ�ת���ַ�����
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
			//��ȡ���ھ��
			HWND hnd = GetHWnd();
			//���ô��ڱ���
			SetWindowText(hnd, "����ְ��������Ϣ");
			//ͼƬ����
			IMAGE img;
			loadimage(&img, "./picture5.jpg", Lengh, Width);
			putimage(0, 0, &img);

			//�����
			char MainTitle[] = { "��Ҫ�޸ĵ�ְ����ϢΪ" };
			char text[] = "����";
			char text1[] = "ְ�����";
			char text2[] = "ְ������";
			char text3[] = "ְ��ְλ";
			char text4[] = "ְ��н��";
			char text5[] = "�޸�����";
			char text6[] = "�޸�ְλ";
			char text7[] = "�޸�н��";

			//�������� 
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(40, 0, "����");

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


			//������,����������Ĳ�ͬλ����ת����ͬ����
			MOUSEMSG m1;
			while (1)
			{
				m1 = GetMouseMsg();//��ȡ������
				if (m1.x >= 550 && m1.x <= 750 && m1.y >= 600 && m1.y <= 650)		//����
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
					{
						SaveAfterModify();
						Modify();
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 300 && m1.y <= 350)		//�޸�����
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
					{
						char date1[64];
						TCHAR InputWindowFI1[] = _T("�������޸ĺ������");  //�Զ�ת���ַ�����
						InputBox(date1, 20, InputWindowFI1);
						strcpy(Image[i].FileName , date1);
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 400 && m1.y <= 450)		//�޸�ְλ
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
					{
						char date2[64];
						TCHAR InputWindowFI1[] = _T("�������޸ĺ��ְλ");  //�Զ�ת���ַ�����
						InputBox(date2, 20, InputWindowFI1);
						strcpy(Image[i].FilePost, date2);
					}
				}
				else if (m1.x >= 550 && m1.x <= 750 && m1.y >= 500 && m1.y <= 550)		//�޸�н��
				{

					if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
					{
						char date3[64];
						TCHAR InputWindowFI1[] = _T("�������޸ĺ��н��");  //�Զ�ת���ַ�����
						InputBox(date3, 20, InputWindowFI1);
						strcpy(Image[i].FileSalary, date3);
					}
				}

			}

		}

	}

	if (!find)
	{
		MessageBox(GetHWnd(), "δ�ҵ������޸ĵ�ְ����Ϣ", "��ʾ", MB_OK);
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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "����ְ��������Ϣ");
	//ͼƬ����
	IMAGE img;
	loadimage(&img, "./picture2.jpg", Lengh, Width);
	putimage(0, 0, &img);

	setfillcolor(RGB(103,174,220));
	char text1[] = "����Ҫ��ѯ��ְ������";
	char text2[] = "        ����";

	fillrectangle(330, 200, 850, 280);
	fillrectangle(330, 450, 850, 530);

	//��������Ϊ�����Ч��
	LOGFONT f;//�������
	gettextstyle(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);


	outtextxy(340, 210, text1);
	outtextxy(340, 460, text2);

	//������,����������Ĳ�ͬλ����ת����ͬ����
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 330 && m1.x <= 850 && m1.y >= 200 && m1.y <= 280)
		{

			if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
			{
				char date1[64];
				TCHAR InputWindowFI1[] = _T("������Ҫ��ѯ��ְ������");  //�Զ�ת���ַ�����
				InputBox(date1, 20, InputWindowFI1);
				string str = date1;
				bool find = false;
				for (int i = 0; i < N; i++)
				{
					if (Image[i].FileName == str)
					{
						find = true;
						//��ȡ���ھ��
						HWND hnd = GetHWnd();
						//���ô��ڱ���
						SetWindowText(hnd, "����ְ��������Ϣ");
						//ͼƬ����
						IMAGE img;
						loadimage(&img, "./picture2.jpg", Lengh, Width);
						putimage(0, 0, &img);

						//�����
						char MainTitle[] = { "�����ҵ�ְ����ϢΪ" };
						char text[] = "����";
						char text1[] = "ְ�����";
						char text2[] = "ְ������";
						char text3[] = "ְ��ְλ";
						char text4[] = "ְ��н��";
						//�������� 
						setbkmode(TRANSPARENT);
						settextcolor(RED);
						settextstyle(40, 0, "����");

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

						//������,����������Ĳ�ͬλ����ת����ͬ����
						MOUSEMSG m1;
						while (1)
						{
							m1 = GetMouseMsg();//��ȡ������
							if (m1.x >= 550 && m1.x <= 650 && m1.y >= 600 && m1.y <= 650)
							{

								if (m1.uMsg == WM_LBUTTONDOWN) //�Ҽ�����һ�δ��� 
								{
									Find();
								}
							}

						}
					}
				}
				if(!find)
				MessageBox(GetHWnd(), "δ�ҵ���ְ����Ϣ", "��ʾ", MB_OK);
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
		cout << "�ļ���ʧ��" << endl;
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
		cout << "�ļ���ʧ��" << endl;
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
		cout << "�ļ���ʧ��" << endl;
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
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	for (int i = 0; i < Num_t; i++)
	{
		ofs << t[i].getno() << "    " << t[i].getname() << "    " << t[i].getpost() << "    " << t[i].getsalary() << endl;
	}
	ofs.close();
}