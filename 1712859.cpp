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
wchar_t* DOCTAPTIN(wchar_t *s, FILE* fp)

{

	int i = 0;

	wchar_t c = 'c';

	while (c != ',')

	{

		c = fgetwc(fp);

		s[i] = c;

		i++;

	}

	s[i - 1] = L'\0';

	return s;

}

int main()
{
	FILE *fp = fopen("list.csv", "rt");
	return 1;
}
