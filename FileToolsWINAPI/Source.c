#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <math.h>
#include <stdio.h>

void f(float a, float b, float c)
{
	HANDLE otv;
	otv = CreateFile(L"otvet.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char text[300];
	DWORD bytes;
	int size = 0;
	float D, x1, x2;
	D = b * b - 4.0f * a * c;
	printf("Дискириминант: %f\n", D);
	//WriteFile(otv, "Дискириминант: %f\n", D, 50, &bytes, NULL);
	if (D > 0.0f)
	{
		x1 = (sqrt(D) - b) / (2.0f * a);
		x2 = (-sqrt(D) - b) / (2.0f * a);
		sprintf(text, "x1=%f\nx2=%f", x1, x2);
		while (text[size] != 0)
		{
			size++;
		}
		WriteFile(otv, text, size, &bytes, NULL);
		return 1;
	}
	else if (D < 0.0f)
	{
		WriteFile(otv, "Вещественных корней нет", size, &bytes, NULL);
		return -1;
	}
	else if (D == 0.0f)
	{
		x1 = x2 = -b / (2.0f * a);
		sprintf(text, "x1 = %f", x1);
		while (text[size] != 0)
		{
			size++;
		}
		WriteFile(otv, text, size, &bytes, NULL);
		return 0;
	}
}


INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HANDLE file; 
	file = CreateFile(L"data.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	float a, b, c;
	a = 0; b = 0; c = 0;
	int lpBuff[] = { a,b,c };
	DWORD size = 100, bytes;
	char line[254];
	if (file != INVALID_HANDLE_VALUE)
	{
		ReadFile(file, line, size, &bytes, NULL);
		
		//A
		int probelA = 0;
		int umnA = 1;
		int numA = 1;
		double Apr = 0;
		//счётчик символов до пробела
		for (int i = 0; i < 254; i++)
		{
			if (line[i] != 32)
			{
				probelA++;
			}
			else
			{
				break;
			}
		}
		//считывание числа A из файла
		for (int i = probelA - 1; i >= 0; i--)
		{
			if (line[i] == 46)
			{
				for (int j = 0; j < probelA - 1; j++)
				{
					numA = numA * 10;
				}
				a = a / numA;
				umnA = 1;
			}
			else
			{
				if (line[0] == 45)
				{
					if (line[i] != 45)
					{
						Apr = line[i] - '0';
						a += Apr * umnA;
						umnA = umnA * 10;
					}
					else
					{
						a = a * -1;
					}
				}
				else
				{
					Apr = line[i] - '0';
					a += Apr * umnA;
					umnA = umnA * 10;
				}
			}
		}
		//B
		int probelB = probelA;
		int umnB = 1;
		int numB = 1;
		double Bpr = 0;
		//счётчик символов до пробела		
		for (int i = probelA + 1; i < 255; i++)
		{
			if (line[i] != 32)
			{
				probelB++;
			}
			else
			{
				break;
			}
		}
		//считывание числа B из файла
		for (int i = probelB; i >= probelA + 1; i--)
		{
			if (line[i] == 46)
			{
				for (int j = 0; j < probelB - 1; j++)
				{
					numB = numB * 10;
				}
				b = b / numB;
				umnB = 1;
			}
			else
			{
				if (line[0] == 45)
				{
					if (line[i] != 45)
					{
						Bpr = line[i] - '0';
						b += Bpr * umnB;
						umnB = umnB * 10;
					}
					else
					{
						b = b * -1;
					}
				}
				else
				{
					Bpr = line[i] - '0';
					b += Bpr * umnB;
					umnB = umnB * 10;
				}
			}
		}
		//C
		int probelC = probelB;
		int umnC = 1;
		int numC = 1;
		double Cpr = 0;
		//счётчик символов до пробела		
		for (int i = probelB + 2; i < 255; i++)
		{
			if (line[i] != -52)
			{
				probelC++;
			}
			else
			{
				break;
			}
		}
		//считывание числа C из файла
		for (int i = probelC; i >= probelB + 2; i--)
		{
			if (line[i] == 46)
			{
				for (int j = 0; j < probelC - 1; j++)
				{
					numC = numC * 10;
				}
				c = c / numC;
				umnC = 1;
			}
			else
			{
				if (line[0] == 45)
				{
					if (line[i] != 45)
					{
						Cpr = line[i] - '0';
						c += Cpr * umnC;
						umnC = umnC * 10;
					}
					else
					{
						c = c * -1;
					}
				}
				else
				{
					Cpr = line[i] - '0';
					c += Cpr * umnC;
					umnC = umnC * 10;
				}
			}
		}

	}
	
	f(a, b, c);
}

