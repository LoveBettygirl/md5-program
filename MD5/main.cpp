#include "MD5.h" 

MD5 md5;

void showUsage()
{
	cout << "MD5: usage: [-h]  --help information" << endl;
	cout << setw(12) << " " << "[-t]  --test MD5 application" << endl;
	cout << setw(12) << " " << "[-c]  [file path of the file computed]" << endl;
	cout << setw(20) << " " << "--compute MD5 of the given file" << endl;
	cout << setw(12) << " " << "[-v]  [file path of the file validated]" << endl;
	cout << setw(20) << " " << "--validate the integrality of a given file by manual input MD5 value" << endl;
	cout << setw(12) << " " << "[-f]  [file path of the file validated]  [file path of the .md5 file] " << endl;
	cout << setw(20) << " " << "--validate the integrality of a given file by read MD5 value from .md5 file" << endl;
	exit(1);
}

void parse_args(int argc, char *argv[])
{
	if (argc == 1)	// 不指定任何命令行参数
		showUsage();
	for (int i = 1; i < argc; )
	{
		if (strcmp(argv[i], "-h") == 0)	// 帮助选项
		{
			showUsage();
		}
		else if (strcmp(argv[i], "-t") == 0)	// 测试字符串
		{
			if (i + 1 < argc)
			{
				showUsage();
			}
			else
			{
				md5.testApplication();
				break;
			}
		}
		else if (strcmp(argv[i], "-c") == 0) // 指定文件计算MD5值
		{
			if (i + 2 < argc)
				showUsage();
			if (i + 1 < argc)
			{
				md5.computeFile(argv[i + 1]);
				break;
			}
			else
				showUsage();
		}
		else if (strcmp(argv[i], "-v") == 0) // 输入字符串校验文件
		{
			if (i + 2 < argc)
				showUsage();
			if (i + 1 < argc)
			{
				md5.validateFromString(argv[i + 1]);
				break;
			}
			else
				showUsage();
		}
		else if (strcmp(argv[i], "-f") == 0) // 指定MD5文件校验文件
		{
			if (i + 3 < argc)
				showUsage();
			else if (i + 2 < argc)
			{
				md5.validateFromFile(argv[i + 2], argv[i + 1]);
				break;
			}
			else
				showUsage();
		}
		else
		{
			showUsage();
		}
	}
}

int main(int argc, char *argv[])
{
	parse_args(argc, argv);
	return 0;
}
