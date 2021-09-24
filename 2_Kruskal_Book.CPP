// Ap dung do thi vo huong, co trong so
#include<stdio.h>
#include<conio.h>

#define MAX 50

typedef struct GRAPH
{
	int n;
	int a[MAX][MAX];
}DOTHI;
typedef struct EDGE
{
	int u,v,value;
}CANH;

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
void BubbleTang(CANH E[], int tongsocanh)
{
	CANH canhtam;
	for(int i=0;i<tongsocanh-1; i++)
		for(int j=tongsocanh-1; j>i; j--)
			if(E[j-1].value > E[j].value)
			{	canhtam=E[j-1];
				E[j-1]=E[j];
				E[j]=canhtam;
			}
}
//==============================================================
void Kruskal(DOTHI g)
{
	CANH listEdge[MAX];
	int tongsocanh=0; //tong so CANH trong do thi
	int i,j;

	for(i=0;i<g.n;i++) //tien hanh them cac CANH trong do thi vao listEdge
	{   for(j=i+1;j<g.n;j++)
			if(g.a[i][j] > 0)
			{	listEdge[tongsocanh].u=i;
				listEdge[tongsocanh].v=j;
				listEdge[tongsocanh].value=g.a[i][j];
				tongsocanh++;
			}
	}
	
	BubbleTang(listEdge, tongsocanh);//sap xep cac CANH co trong so tang dan

	int nT=0;//Khoi tao so luong cac CANH cua cay khung
	CANH T[MAX]; //chua cac CANH cua cay khung
	int nhan[MAX];//chua cac NHAN cua cac dinh trong do thi theo thuat toan

	for(i=0;i<g.n;i++) nhan[i]=i;
	
	int canhdangxet=0;//CANH dang xet thu may trong danh sach
	while(nT<g.n && canhdangxet < tongsocanh)
	{
		if(nhan[listEdge[canhdangxet].u] != nhan[listEdge[canhdangxet].v])
		{	T[nT++]=listEdge[canhdangxet];
			int giatri=nhan[listEdge[canhdangxet].v];
			for(j=0;j<g.n;j++)
				if(nhan[j] == giatri)
					nhan[j] = nhan[listEdge[canhdangxet].u];
		}
		canhdangxet++;
	}
	if(nT != g.n-1) printf("\nDo thi khong lien thong nen khong co Kruskal\n");
	else
	{	int TongTrongSoCuaCayKhung =0;
		printf("\nDo thi lien thong\n");
		printf("Cay khung nho nhat cua do thi la:\n");
		for(i=0;i<nT;i++)
		{	printf("[%d,%d(%d)], ", T[i].u,T[i].v,T[i].value);
			TongTrongSoCuaCayKhung += T[i].value;
		}
		printf("\nTong trong so cua cay khung la: %d\n",TongTrongSoCuaCayKhung);
	}
}
//==============================================================
int main()
{
	DOTHI g;
`
	char inputfile[100];
	char ch;
	do
	{
		printf("\n\nNhap ten file do thi: ");
		gets(inputfile);
		if(DocMaTranKe(inputfile, g)==1) 
		{
			printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g);
			
			printf("\n\n KRUSKAL: ");
			Kruskal(g);
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}
