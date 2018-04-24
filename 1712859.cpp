#include <stdio.h>
#include <string>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
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
	wchar_t* SoThich;
	;
};
typedef struct SinhVien SV;
struct DanhSach
{
	SV *DS;
	int SLSinhVien;
};
int SLdong;
void DemDong(FILE *fp, int &SLdong)
{
	char ch;
	do
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			SLdong++;
		}
	} while (ch != EOF);
}

wchar_t* DocDK(wchar_t* str, wchar_t Delim)
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
void DocvaoSV(wchar_t *s, SV &a)
{
	
	wchar_t *pc = DocDK(s, L',');
		a.MSSV = pc;

		pc = DocDK(NULL, L',');
		a.HoVaTen = GetInfo(pc, 30);

		pc = DocDK(NULL, L',');
		a.Khoa = GetInfo(pc, 30);

		pc = DocDK(NULL, L',');
		a.NamHoc = GetInfo(pc, 4);

		pc = DocDK(NULL, L',');
		a.Date = GetInfo(pc, 10);

		pc = DocDK(NULL, ',');
		a.Hinh = GetInfo(pc, 30);

		pc = DocDK(NULL, ',');
		a.MoTaBanThan = GetInfo(pc, 1000);

		pc = DocDK(NULL, ',');
		a.email = GetInfo(pc, 30);

		pc = DocDK(NULL, '\n');
		a.SoThich = GetInfo(pc, 1000);
		
}
wchar_t* DocDong(FILE *fp)
{

	wchar_t* s = NULL;
	wchar_t* temp = NULL;
	int count = 1;
	int i = 0;
	wchar_t c;

	c = fgetwc(fp);

	while (c != L'\n')
	{
		count++;
		temp = (wchar_t*)realloc(s, count * sizeof(wchar_t));

		if (temp)
		{
			s = temp;
			s[i] = c;
			i++;
		}
		c = fgetwc(fp);
	}
	s[i] = L'\0';

	return s;
}
wchar_t* Getline(FILE *f)
{
	wchar_t* info = NULL;
	wchar_t* temp = NULL;
	int count = 1;
	int i = 0;
	wchar_t c;

	c = fgetwc(f);

	while (c != L'\n')
	{
		count++;
		temp = (wchar_t*)realloc(info, count * sizeof(wchar_t));

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
}
void DocFile(FILE *fp, DanhSach &b)
{
	SV* temp = NULL;
	while (!feof(fp))
	{
		b.SLSinhVien++;
		temp = (SV*)realloc(b.DS, b.SLSinhVien * sizeof(SV));

		if (temp)
		{
			b.DS = temp;
			wchar_t* line = Getline(fp);
			DocvaoSV(line, b.DS[b.SLSinhVien - 1]);
		}
		else
		{
			for (int i = 0; i < b.SLSinhVien - 1; i++)
			b.DS = NULL;
		}
	}
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
	fwprintf(fo, x.SoThich);
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"</ul>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Mô tả</div>\n");
	fwprintf(fo, L"<div class=\"Description\">\n");
	fwprintf(fo, x.MoTaBanThan);//
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
int main()
{
	int i;
	FILE *fp = _wfopen(L"list.csv", L"r , ccs=UTF-8");
	if (!fp)
	{
		wprintf(L"Mo file  that bai\n");
		return 0;
	}
	DanhSach m;
	DemDong(fp, SLdong);
	DocFile(fp,m);

	fclose(fp);
	return 1;
}
