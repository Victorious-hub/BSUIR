#include <iostream>

int main()
{

	long long int inp, n1, n2;
	int mas1[20]{}, mas2[20]{}, mas3[100]{}; // по умолчанию инициализируем нулями, чтобы мусора не было
	int i = 0, j = 0, variable = 0;
	int len3 = 1, len30 = 0;
	bool a;
	std::cin >> inp;

	if ((inp % 2) == 0) // далее два условия(они повлияют на заполнение нашего третьего массива) 
    {
		n1 = inp / 2;
		n2 = inp - 1;
	}else
    {
		n2 = (inp - 1) / 2;
		n1 = inp;
	}

	if (n1 > n2) a = true;
	else a = false;
	do
    {
		mas1[i] = n1 % 10; // здесь раскладываем первое число на разряды(ложим с конца)
		n1 = n1 / 10;
		i++;
	} while (n1 > 0);

	int len1 = i;

	do
    {
		mas2[j] = n2 % 10;
		n2 = n2 / 10; // здесь делаем аналогично
		j++;
	} while (n2 > 0);

	int len2 = j;
	mas3[0] = 1; // присваиваем для выполения условия суммы арифметчиеской прогрессии +1(для удлинителей)

	if (a == true) 
    {
		for (int j = 0; j < len2; j++) 
        {
			len30 = 0;
			for (int k = 0; k < len1; k++) // если a-нечетное
            {
				mas3[j + k] += mas1[k] * mas2[j];
				len30 = j + k;
			}
		}
	}else // здесь поразрядно перемножаем каждое с каждыми числом и кладем в массив(почти как в столбике умножаем)
    {
		for (int j = 0; j < len1; j++) 
        {
			len30 = 0;
			for (int k = 0; k < len2; k++) // если а - четное
            {
				mas3[j + k] += mas1[k] * mas2[j];
				len30 = j + k;
			}
		}
	}

	len3 += len30;

	for (int i = 0; i < len3; i++) 
    {//после получения произведения элементов двух массивов раскладываем числа на разряды при умножениии которых мы бы получили наше число

		mas3[i] = mas3[i] + variable;
		variable = mas3[i] / 10;
		mas3[i] = mas3[i] % 10;
	}

	if (variable != 0) 
    {
		do 
        {
			mas3[len3] = variable % 10;
			variable = variable / 10;
			len3++;// условие в случае того, если вводим числа от 1 до 9
		} while (variable > 0);
	}
    
	for (int i = len3 - 1; i >= 0; i--) std::cout << mas3[i];// так как заполнение шло с конца, перебираем в обратном порядке

}