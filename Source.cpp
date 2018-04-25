#include <stdio.h>
#include <string>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct SinhVien
{
	wchar_t* MSSV;
	wchar_t* HoVaTen;
	wchar_t* Khoa;
	wchar_t* NamHoc;
	wchar_t* Date;
	wchar_t* Hinh;
	wchar_t* MoTaBanThan;
	wchar_t* email;
	wchar_t** SoThich;
	int nSoThich;
};
typedef struct SinhVien SV;
struct DanhSach
{
	SV *DS;
	int SLSinhVien;
};
int SLdong;

/*void dem_sv(FILE* fp, DanhSach &m)
{
wchar_t s[2000];
int dem = 0;
while (feof(fp) == NULL){
fgetws(s, 2000, fp);
dem++;
}
m.SLSinhVien = dem - 1;
}*/
wchar_t* GmailField(SV sv)
{
	wchar_t* gmail = (wchar_t*)malloc((wcslen(sv.MSSV) + wcslen(L"@student.hcmus.edu.vn") + 1) * sizeof(wchar_t));
	wcscpy(gmail, sv.MSSV);
	wcscpy(gmail + wcslen(sv.MSSV), L"@student.hcmus.edu.vn");

	return gmail;
}
void FreeInfo(SV &sv)
{
	free(sv.HoVaTen);
	sv.HoVaTen = NULL;
	free(sv.Hinh);
	sv.Hinh = NULL;
	free(sv.Khoa);
	sv.Khoa = NULL;
	free(sv.MoTaBanThan);
	sv.MoTaBanThan = NULL;
	free(sv.MSSV);
	sv.MSSV = NULL;
	free(sv.Date);
	sv.Date = NULL;
	free(sv.HoVaTen);
	sv.HoVaTen = NULL;
	free(sv.NamHoc);
	sv.NamHoc = NULL;

	for (int i = 0; i < sv.nSoThich; i++)
	{
		free(sv.SoThich[i]);
		sv.SoThich[i] = NULL;
	}
	free(sv.SoThich);
	sv.SoThich = NULL;
	sv.nSoThich = 0;
}

void FreeList(DanhSach &Dssv)
{
	for (int i = 0; i < Dssv.SLSinhVien; i++)
		FreeInfo(Dssv.DS[i]);
	Dssv.DS = NULL;
	Dssv.SLSinhVien = 0;

}
wchar_t* Getline(FILE *f)
{
	wchar_t* info = NULL;
	wchar_t* temp = NULL;
	int count = 0;
	int i = 0;
	wchar_t c;

	c = fgetwc(f);

	while (c != L'\n' && !feof(f))
	{
		count++;
		temp = (wchar_t*)malloc(count * sizeof(wchar_t));

		if (temp)
		{
			info = temp;
			info[i] = c;
			i++;
		}

		else
		{
			free(info);
			wprintf(L"Đọc thất bại\n");
		}
		c = fgetwc(f);
	}
	info[i] = L'\0';

	return info;
}wchar_t* My_wcstok(wchar_t* str, wchar_t Delim)
{
	static wchar_t* des = NULL;
	bool flag = false;

	if (des == NULL && str == NULL)
		return NULL;

	if (str == NULL)
		str = des;

	int i = 0;
	while (str[i] != Delim || flag == true)
	{
		if (str[i] == L'"')
		{
			flag = !flag;
			str[i] = L' ';
		}

		if (!str[i])
		{
			des = NULL;
			return NULL;
		}
		i++;
	}
	str[i] = '\0';
	des = str + i + 1;

	return str;
}
wchar_t* GetInfo(wchar_t* str, int MaxCount)
{
	int len = (wcslen(str) >= MaxCount) ? MaxCount : wcslen(str);
	wchar_t* info = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	wcscpy(info, str);

	return info;
}
void ReadInStruct(wchar_t* str, SV &sv)
{
	wchar_t* pc = My_wcstok(str, L',');
	sv.MSSV = pc;

	pc = My_wcstok(NULL, L',');
	sv.HoVaTen = pc,

		pc = My_wcstok(NULL, L',');
	sv.Khoa = pc,

		pc = My_wcstok(NULL, L',');
	sv.NamHoc = pc,

		pc = My_wcstok(NULL, L',');
	sv.Date = pc,

		pc = My_wcstok(NULL, ',');
	sv.Hinh = pc,

		pc = My_wcstok(NULL, ',');
	sv.MoTaBanThan = pc;

	pc = My_wcstok(NULL, ',');

	while (pc)
	{
		sv.nSoThich++;
		wchar_t** temp = (wchar_t**)malloc(sv.nSoThich * sizeof(wchar_t*));

		if (temp)
		{
			sv.SoThich = temp;
			sv.SoThich[sv.nSoThich - 1] = pc;
		}

		else
		{
			for (int k = 0; k < sv.nSoThich; k++)
			{
				free(sv.SoThich[k]);
				sv.SoThich[k] = NULL;
			}

			free(sv.SoThich);
			sv.SoThich = NULL;
		}
		pc = My_wcstok(NULL, L',');
	}
}
void ReadFileCSV(FILE *f, DanhSach &Dssv)
{

	SV* temp = NULL;

	while (!feof(f))
	{
		Dssv.SLSinhVien++;
		temp = (SV*)malloc(Dssv.SLSinhVien * sizeof(SV));

		if (temp)
		{
			Dssv.DS = temp;
			wchar_t* line = Getline(f);
			SV k;
			ReadInStruct(line, k);
			Dssv.DS[Dssv.SLSinhVien - 1] = k;

		}
		else
		{
			for (int i = 0; i < Dssv.SLSinhVien - 1; i++)
				FreeInfo(Dssv.DS[i]);
			Dssv.DS = NULL;
		}
	}
	fclose(f);
}



void viet_1_sv_html(FILE* fo, SV x)
{
	fwprintf(fo, L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
	fwprintf(fo, L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fwprintf(fo, L"<head>\n");
	fwprintf(fo, L"<meta http-equiv=\"Content - Type\" content=\"text / html; charset = utf - 8\" />\n");
	fwprintf(fo, L"<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
	fwprintf(fo, L"<title>HCMUS - ");
	fwprintf(fo, x.HoVaTen);//
	fwprintf(fo, L"</title>\n");
	fwprintf(fo, L"</head>\n");
	fwprintf(fo, L"<body>\n");
	fwprintf(fo, L"<div class=\"Layout_container\">\n");
	fwprintf(fo, L"<!-- Begin Layout Banner Region -->\n");
	fwprintf(fo, L"<div class=\"Layout_Banner\" >\n");
	fwprintf(fo, L"<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
	fwprintf(fo, L"<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Layout Banner Region -->\n");
	fwprintf(fo, L"<!-- Begin Layout MainContents Region -->\n");
	fwprintf(fo, L"<div class=\"Layout_MainContents\">\n");
	fwprintf(fo, L"<!-- Begin Below Banner Region -->\n");
	fwprintf(fo, L"<div class=\"Personal_Main_Information\">\n");
	fwprintf(fo, L"<!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(fo, L"<div class=\"Personal_Location\">\n");
	fwprintf(fo, L"<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");
	fwprintf(fo, L"<span class=\"Personal_FullName\">");
	fwprintf(fo, x.HoVaTen);
	fwprintf(fo, L" - ");
	fwprintf(fo, x.MSSV);
	fwprintf(fo, L"</span>\n");
	fwprintf(fo, L"<div class=\"Personal_Department\">KHOA CÔNG NGHỆ THÔNG TIN</div>\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<div class=\"Personal_Phone\">\n");
	fwprintf(fo, L"Email: ");
	fwprintf(fo, x.email);
	fwprintf(fo, L"\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<br /> \n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(fo, L"<div class=\"Personal_HinhcanhanKhung\">\n");
	fwprintf(fo, L"<img src=\"Images/");
	fwprintf(fo, x.Hinh);
	fwprintf(fo, L"\" class=\"Personal_Hinhcanhan\" />\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Below Banner Region -->\n");
	fwprintf(fo, L"<!-- Begin MainContents Region -->\n");
	fwprintf(fo, L"<div class=\"MainContain\">\n");
	fwprintf(fo, L"<!-- Begin Top Region -->\n");
	fwprintf(fo, L"<div class=\"MainContain_Top\">\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
	fwprintf(fo, L"<div>\n");
	fwprintf(fo, L"<ul class=\"TextInList\">\n");
	fwprintf(fo, L"<li>Họ và tên: ");
	fwprintf(fo, x.HoVaTen);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>MSSV: ");
	fwprintf(fo, x.MSSV);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Sinh viên khoa ");
	fwprintf(fo, x.Khoa);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Ngày sinh: ");
	fwprintf(fo, x.Date);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Email: ");
	fwprintf(fo, x.email);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"</ul>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Sở thích</div>\n");
	fwprintf(fo, L"<div>\n");
	fwprintf(fo, L"<ul class=\"TextInList\">\n");
	fwprintf(fo, L"<li>");
	fwprintf(fo, x.SoThich[1]);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>");
	fwprintf(fo, x.SoThich[2]);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"</ul>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Mô tả</div>\n");
	fwprintf(fo, L"<div class=\"Description\">\n");
	fwprintf(fo, x.MoTaBanThan);
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- Begin Layout Footer -->\n");
	fwprintf(fo, L"<div class=\"Layout_Footer\">\n");
	fwprintf(fo, L"<div class=\"divCopyright\">\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"@2018</br>\n");
	fwprintf(fo, L"Đồ án giữ kỳ</br>\n");
	fwprintf(fo, L"Kỹ thuật lập trình</br>\n");
	fwprintf(fo, L"TH2012/03</br>\n");
	fwprintf(fo, L"1712859 - Nguyễn Phạm Anh tú</br>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Layout Footer -->\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</body>\n");
	fwprintf(fo, L"</html>\n");
	fclose(fo);
}
wint_t WSTRLEN(wchar_t s[])
{
	wint_t dem = 0;
	while (s[dem] != L'\0')
	{
		dem++;
	}
	return dem;
}
wchar_t* NamedFile(SV sv)
{
	wchar_t* name = (wchar_t*)malloc((wcslen(sv.MSSV) + wcslen(L".htm") + 1) * sizeof(wchar_t));
	wcscpy(name, sv.MSSV);
	wcscpy(name + wcslen(sv.MSSV), L".htm");

	return name;
}
void viet_html(int n, DanhSach  a)
{
	for (int i = 0; i < n; i++)
	{
		FILE *fo;
		wchar_t *s = NamedFile(a.DS[i]);
		fo = _wfopen(s, L" w, ccs = UTF-8");
		if (fo == NULL)
			wprintf(L"Mo file %ls that bai", s);
		viet_1_sv_html(fo, a.DS[i]);
	}
}
int main()
{
	int i;
	FILE *fp = _wfopen(L"Book1.csv", L"r , ccs=UTF-8");
	if (!fp)
	{
		wprintf(L"Mo file  that bai\n");
		return 0;
	}
	DanhSach m;
	//dem_sv(fp, m);
	m.SLSinhVien = 10;
	ReadFileCSV(fp, m);
	viet_html(10, m);
	fclose(fp);
	return 1;
}
