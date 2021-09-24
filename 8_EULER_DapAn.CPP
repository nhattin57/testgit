
// Chi ap dung voi Do thi vo huong, co the co trong so
// Dua vao Tinh bac Chan - Le

#include<stdio.h>
#include<conio.h>

#define MAX 20	//max so dinh cua do thi
#define MAXSTACK 100	//max SATCK

typedef struct GRAPH
{ 	int n;
	int a[MAX][MAX];
}DOTHI;

struct STACK
{	int array[MAXSTACK];
	int top;
};
//==============================================================
int DocMaTranKe(const char* TenFile,DOTHI &g)
{	FILE* f;
	f = fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	fclose(f);
	return 1;
}
//==============================================================
void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//==============================================================
int KiemTraMaTranKeHopLe(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		if(g.a[i][i] != 0)
			return 0;
	return 1;
}
//==============================================================
int KiemTraDoThiVoHuong(DOTHI g)
{
	for(int i=1;i<g.n;i++)
		for(int j=0;j<i;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1;
}
//==============================================================
int BacCuaDinh_VoHuong (int k, DOTHI g)
{	int bac = 0;
	for(int j=0;j<g.n;j++)
		if(g.a[k][j] != 0)
			bac++;
	return bac;
}
//==============================================================
void SoLuongBacChanLe_VoHuong(DOTHI g,int &soBacChan,int &soBacLe)
{
	soBacChan = soBacLe = 0;
	for(int i=0 ; i<g.n; i++)
	{
		if(BacCuaDinh_VoHuong(i, g) %2 != 0)
			soBacLe++;
		else soBacChan++;
	}
}
//==============================================================
void InitStack(STACK &stack) 
{	stack.top = -1;
}
//==============================================================
int IsEmpty(STACK stack)
{
	if(stack.top == -1) return 1;
	return 0;
}
//==============================================================
int IsFull(STACK stack)
{
	if(stack.top == MAXSTACK-1) return 1;
	return 0;
}
//==============================================================
int Push(STACK &stack, int value) 
{	if(IsFull(stack)) return 0; 
	stack.array[++stack.top] = value;
	return 1;
}
//==============================================================
int Pop(STACK &stack,int &d)
{
	if(IsEmpty(stack)) return 0;
	d = stack.array[stack.top--];
	return 1;
}
//==============================================================
void TimDuongDi(int i, DOTHI &g, STACK &stack)
{
	for(int j=0;j<g.n;j++)
	{	if(g.a[i][j] !=0)
		{	g.a[i][j]=g.a[j][i] =0; // xoa canh
			TimDuongDi(j, g, stack);
		}
	}
	Push(stack,i);
}
//==============================================================
void XuatKetQua(STACK &stack)
{
	int d;
	while( ! IsEmpty(stack))
	{
		Pop(stack, d);
		printf("%d->", d);
	}
	printf("\b\b. \n\n");
//==============================================================
void Euler(DOTHI g, int x)
{
	DOTHI temp = g;//thong qua do thi trung gian
	
	STACK stack;
	InitStack(stack);
	
	TimDuongDi(x,temp,stack);
	XuatKetQua(stack);
}
//==============================================================
int main()
{
	DOTHI g;
			
	char inputfile[100];
	char ch;
	do
	{
		printf("\n\nNhap ten file do thi: ");
		gets(inputfile);
		if(DocMaTranKe(inputfile, g) ==0) return 0;
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		XuatMaTranKe(g);
		if(KiemTraMaTranKeHopLe(g) ==0)
		{
			printf("Do thi khong hop le.\n");
			return 0;
		}
		if(KiemTraDoThiVoHuong(g)==0)
		{
			printf("Do thi co huong nen chua xet Euler.\n");
			return 0;
		}
		printf("Do thi vo huong.\n");
			
		int soBacChan, soBacLe;
		SoLuongBacChanLe_VoHuong( g, soBacChan, soBacLe);
		if(soBacLe >2 )
		{
			printf("Do thi khong Euler.\n");
			return 0;
		}
		
		if(soBacLe ==2 )
		{
			printf("\n\n\t\t\t Duong di Euler:\n\n");
			for(int dinhBD=0; dinhBD<g.n; dinhBD++)
				if(BacCuaDinh_VoHuong(dinhBD, g) %2 )
					Euler(g, dinhBD);
		}
		else //Cac dinh co bac toan chan hoac co dinh bac 0
		{
			printf("\n\n\t\t\t Chu trinh Euler:\n\n");
			for(int dinhBD=0; dinhBD<g.n; dinhBD++)
				if(BacCuaDinh_VoHuong(dinhBD, g) >0 )
					Euler(g, dinhBD);
		}
	
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}

