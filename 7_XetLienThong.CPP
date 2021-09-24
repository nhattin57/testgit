#include<conio.h>
#include<stdio.h>

#define MAX 20

typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

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
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		if(g.a[i][j] != g.a[j][i])
			return 0; // co huong
	return 1;
}
//==============================================================
int KiemTraDoThiTrongSo(DOTHI g) 
{
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
		if(g.a[i][j] !=0 && g.a[i][j] !=1)
			return 1; // co trong so
	return 0;
}
//==============================================================
void DiTimCacDinhLienThong(DOTHI g, int Nhan[], int i)
{
	for(int j=0;j<g.n;j++)
	{
		if(g.a[i][j] !=0 && Nhan[j] != Nhan[i])
		{
			Nhan[j] = Nhan[i];
			DiTimCacDinhLienThong(g, Nhan, j);
		}
	}
}
void XetLienThong(DOTHI g)
{
	int Nhan[MAX];
	
	for(int i=0;i<g.n;i++)
		Nhan[i] = 0;
	
	int SoThanhPhanLT = 0;
	
	for(int i=0;i<g.n;i++)
	{
		if(Nhan[i] ==0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
			DiTimCacDinhLienThong(g, Nhan, i);
		}
	}
	//Hien thi nhung thanh phan lien thong
	printf ("\n So thanh phan lien thong la: %d\n",SoThanhPhanLT); 
	for (int i = 1; i <= SoThanhPhanLT; i++) 
 	{ 
		printf("Thanh phan lien thong thu %d gom cac dinh: ", i); 
		// Cac ban tu code phan này

		printf("\n");
	}
}
//==============================================================
int main()
{                                 
			DOTHI g;
			int nV,nE,start;
			scanf("%d%d%d",&nV,&nE,&start);
			//int Matrixx[MAX][MAX];
			for(int i = 0;i<nV;i++){
				for(int j = 0;j<nV;j++){
					g.a[i][j]=0;
				}	
			}
			int a,b;
			for(int i = 0;i<nE;i++){
				scanf("%d%d",&a,&b);
				g.a[a-1][b-1]=g.a[b-1][a-1]=1;
			}
			
			g.n=nV;
		//	g.a=Matrixx;
	
			XuatMaTranKe(g);
			if(KiemTraMaTranKeHopLe(g)==1)
			{
				printf("Do thi hop le.\n");
			
				if(KiemTraDoThiVoHuong(g)==1)
					printf("Do thi vo huong.\n");
				else
					printf("Do thi co huong.\n");
				
				if(KiemTraDoThiTrongSo(g)==1)
					printf("Do thi co trong so.\n");
				else
					printf("Do thi khong trong so.\n");
					
				XetLienThong(g);
			}else
				printf("Do thi khong hop le.\n");

	return 0;
}
