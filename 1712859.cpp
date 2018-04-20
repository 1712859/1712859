#include<stdio.h>
#include<string>
using namespace std;
struct SinhVien
{
	int MSSV;
	wchar_t HoVaTen;
	wchar_t Khoa;
	int NamHoc;
	wchar_t Date;
	wchar_t Hinh;
	wchar_t MoTaBanThan;
	wchar_t SoThich[10];
	wchar_t email;
};
typedef struct SinhVien SV;

int KiemTraKetThuc(wchar_t c)
{
	return (c == '\n' || c == EOF);
}
int DocDong(wchar_t * dong, int SLDong, FILE *fp)
{
	wchar_t c;
	int i = 0;
	while (!KiemTraKetThuc(c = fgetc(fp)) && i < SLDong - 1)
		dong[i++] = c;
	dong[i] = 0; 

	if (i == SLDong - 1) 
	while ((c = fgetc(fp)) != '\n') 
		;

	return i; 
}
int main()
{
	FILE *fp = fopen("list.csv", "r");
	return 1;
}
