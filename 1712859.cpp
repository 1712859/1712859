#include<stdio.h>
#include<string>
#include<wchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
using namespace std;
struct SinhVien
{
	wchar_t MSSV[10];
	wchar_t HoVaTen[30];
	wchar_t Khoa[50];
	wchar_t NamHoc[4];
	wchar_t Date[100];
	wchar_t Hinh[100];
	wchar_t MoTaBanThan[100];
	wchar_t SoThich[1000];
	wchar_t email[100];
};
typedef struct SinhVien SV;
int SLDong;
void DemDong(FILE *fp, int &Sodong)
{
	char ch;
	do
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			Sodong++;
		}
	} while (ch != EOF);
}
void docsinhvien(FILE *f, SV &a)
{
	fscanf_s(f, "\" %[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\n]", &a.MSSV, &a.HoVaTen, &a.Khoa, &a.NamHoc, &a.Date, &a.Hinh, &a.MoTaBanThan, &a.email, &a.SoThich);
}
void DocFile(FILE *fp, SV a[])
{

	for (int i = 0; i < SLDong; i++)
	{
		docsinhvien(fp, a[i]);
	}
}
int main()
{
	int i;
	FILE *fp = _wfopen(L"list.csv", L"r , ccs = UTF - 8");
	DemDong(fp, SLDong);
	if (!fp)
	{
		wprintf(L"Mo file  that bai\n");
		return 0;
	}
	SV a[10];
	DocFile(fp, a);
	for (i = 0; i < SLDong; i++)
	{
		wprintf(L"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", a[i].MSSV, a[i].HoVaTen, a[i].Khoa, a[i].NamHoc, a[i].Date, a[i].Hinh, a[i].MoTaBanThan, a[i].email, a[i].SoThich);
	}
	fclose(fp);
	return 1;
}
