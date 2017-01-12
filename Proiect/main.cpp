
#include<iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>   /* time */
using namespace std;

int mine[60][60], n, m, nrMine, nrClick, stiva[500];
bool butoane[60][60], jocPierdut;
char opt;

void creazaHarta()
{
	int vector[3600];
	int dim;
	dim = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			vector[dim++] = i * 100 + j;
	srand(time(NULL));
	for (int i = 0; i < nrMine; i++)
	{
		int pos = rand() % dim;
		mine[vector[pos] / 100][vector[pos] % 100] = 9;
		for (int aux = pos + 1; aux < dim; aux++)
			vector[aux - 1] = vector[aux];
		dim--;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (mine[i][j] != 9)
			{
				int contor = 0;
				if (i > 0 && mine[i - 1][j] == 9)
					contor++;
				if (i > 0 && j < m - 1 && mine[i - 1][j + 1] == 9)
					contor++;
				if (j < m - 1 && mine[i][j + 1] == 9)
					contor++;
				if (i < n - 1 && j < m - 1 && mine[i + 1][j + 1] == 9)
					contor++;
				if (i < n - 1 && mine[i + 1][j] == 9)
					contor++;
				if (i < n - 1 && j>0 && mine[i + 1][j - 1] == 9)
					contor++;
				if (j > 0 && mine[i][j - 1] == 9)
					contor++;
				if (i > 0 && j>0 && mine[i - 1][j - 1] == 9)
					contor++;
				mine[i][j] = contor;
			}

		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			butoane[i][j] = false;
}

void afiseazaHarta()
{
	int k = 0;

	cout << "      ";
	for (int j = 0; j < m; j++)
	{
		if(j+1 > 9)
			cout << " " << j + 1 << " ";
		else
			cout << " " << j + 1 << "  ";

	}
	cout << endl;

	for (int i = 0; i < n*2; i++)
	{
		if (i % 2 == 0)
		{
			cout << "     ";
			for (int j = 0; j < m; j++)
				cout << "____";
		}
		else
		{
			if (k + 1 > 9)
				cout << k + 1 <<"   |";
			else cout << k + 1 << "    |";

			for (int j = 0; j < m; j++)
			{
				if (butoane[k][j])
				{
					if (mine[k][j] == 9) cout << " Q |";
					else if (mine[k][j] == 10) cout << (char)176 << (char)176 << (char)176 << "|";
					else if (mine[k][j] == 0) cout << "   |";
					else cout << " " << mine[k][j] << " |";
				}
				else {
					cout << (char)178<< (char)178<< (char)178<< "|";
				}
			}
			k++;
		}
		cout << endl;
	}

	cout << "     ";
	for (int j = 0; j < m; j++)
		cout << "____";
	cout << endl;
}

void reavealMap()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			butoane[i][j] = true;
}



void addElementStiva(int valoare)
{
	int i = 0;
	int aux1, aux2;
	aux1 = stiva[i];
	do {
		i++;
		aux2 = stiva[i];
		stiva[i] = aux1;
		aux1 = aux2;

	} while (stiva[i] != -1);
	stiva[0] = valoare;
}

int getElementStiva()
{
	int i = 0, valoare;
	valoare = stiva[i];
	while (stiva[i] != -1)
	{
		stiva[i] = stiva[i + 1];
		i++;
	}
	return valoare;
}

void eliberareSpatii()
{
	int poz = getElementStiva();
	int i = poz / 100;
	int j = poz % 100;

	if (i > 0 && !butoane[i - 1][j])
	{
		butoane[i - 1][j] = true;
		nrClick++;
		if (mine[i - 1][j] == 0)
			addElementStiva((i - 1) * 100 + j);
	}

	if (i > 0 && j < m - 1 && !butoane[i - 1][j + 1])
	{
		butoane[i - 1][j + 1] = true;
		nrClick++;
		if (mine[i - 1][j + 1] == 0)
			addElementStiva((i - 1) * 100 + j + 1);
	}

	if (j < m - 1 && !butoane[i][j + 1])
	{
		butoane[i][j + 1] = true;
		nrClick++;
		if (mine[i][j + 1] == 0)
			addElementStiva(i * 100 + j + 1);
	}

	if (i < n - 1 && j < m - 1 && !butoane[i + 1][j + 1])
	{
		butoane[i + 1][j + 1] = true;
		nrClick++;
		if (mine[i + 1][j + 1] == 0)
			addElementStiva((i + 1) * 100 + j + 1);
	}

	if (i < n - 1 && !butoane[i + 1][j])
	{
		butoane[i + 1][j] = true;
		nrClick++;
		if (mine[i + 1][j] == 0)
			addElementStiva((i + 1) * 100 + j);
	}

	if (i < n - 1 && j>0 && !butoane[i + 1][j - 1])
	{
		butoane[i + 1][j - 1] = true;
		nrClick++;
		if (mine[i + 1][j - 1] == 0)
			addElementStiva((i + 1) * 100 + j - 1);
	}

	if (j > 0 && !butoane[i][j - 1])
	{
		butoane[i][j - 1] = true;
		nrClick++;
		if (mine[i][j - 1] == 0)
			addElementStiva(i * 100 + j - 1);
	}

	if (i > 0 && j>0 && !butoane[i - 1][j - 1])
	{
		butoane[i - 1][j - 1] = true;
		nrClick++;
		if (mine[i - 1][j - 1] == 0)
			addElementStiva((i - 1) * 100 + j - 1);
	}

	afiseazaHarta();
	system("CLS");
	if (stiva[0] != -1)
		eliberareSpatii();
}

bool apasaButon(int x, int y)
{
	nrClick++;
	if (mine[x][y] == 9)
	{
		reavealMap();
		mine[x][y] = 10;
		return false;
	}
	else if (mine[x][y] == 0)
	{
		butoane[x][y] = true;
		stiva[0] = x * 100 + y;
		stiva[1] = -1;
		eliberareSpatii();
	}
	else
	{
		butoane[x][y] = true;
	}
	return true;
}





bool jocCastigat()
{
	if (nrClick + nrMine == n*m)
	{
		reavealMap();
		return true;
	}
	return false;
}


bool coordonateGresite(int x, int y)
{
	if (x > n || y > m || x < 1 || y < 1)
	{
		cout << "Ai introdus o pozitie gresita. Dati alte coordonate.\n";
		return false;
	}
	return true;
}

bool pozitieApasata(int x, int y)
{
	if (butoane[x][y])
	{
		cout << "Pozitia este deja descoperita.\n";
		return false;
	}
	return true;
}

int citireInputMeniu()
{
    int input;
    cin>>input;
    while(input<1 || input>4)
    {
        cout << "Introduceti o valoare intre 1 si 4\n";
        cin>>input;
    }
    return input;
}
void afisareMeniu()
{
    cout<<"\n\n\n\t\t\tMINESWEEPER\n\n\n"<<endl;
    cout<<"MENIU - Alegeti intre 1-4: "<<endl;
    cout<<"1. Incepe un nou joc"<<endl;
    cout<<"2. Statistica"<<endl;
    cout<<"3. Optiuni"<<endl;
    cout<<"4. Exit"<<endl;
}

int startJoc()
{
   /* cout<<"Doriti jucati?"<<endl;
    cout<<"Alegeti y pentru da sau n pentru nu"<<endl;
   cin>>opt;
   while(opt!='y'&& opt!='n')
   {
       cout<<"Doriti sa jucati?"<<endl;
       cin>>opt;
   }

    return opt;*/
}

int afisareStatistica()
{

}

int afisareOptiuni()
{

}

int inputOptiune()
{

}
int meniu()
{
     bool quit = false;
    do{
        cout<<endl;
        afisareMeniu();
        cout<<endl;
        switch(citireInputMeniu())
        {
        case 1:
            system("CLS");
            startJoc();
            break;
        case 2:
            system("CLS");
            afisareStatistica();
            break;
        case 3:
            system("CLS");
            afisareOptiuni();
            char opt ;
            opt= inputOptiune();
            break;
        case 4:
            quit = true;
        }

    }while(!quit);
}

int main()
{
   // meniu();

    while(true)
    {
        cout << " Cate linii / coloane sa aiba harta? " << endl;
        cin >> n >> m;
        while (n > 60 || m > 60)
        {
            cout << "Puteti introduce maxim 60 de linii si coloane.\n";
            cin >> n >> m;
        }
        cout << "Cate bombe doresti pe harta?" << endl;
        cin >> nrMine;
        while (nrMine > n * m * 0.6 || nrMine < 1)
        {
            cout << "Puteti introduce maxim "<<(int)(n*m*0.6)<<" mine.\n";
            cin >> nrMine;
        }
        creazaHarta();
        afiseazaHarta();

        nrClick = 0;
        jocPierdut = false;
        bool finish = false;
        while (!finish && !jocPierdut)
        {

            int x, y;
            cout << "Apasa buton (x, y)\n";
            cin >> x >> y;
            while (!coordonateGresite(x,y) || !pozitieApasata(x-1,y-1))
                cin >> x >> y;

            system("CLS");
            if (!apasaButon(x-1, y-1))
            {
                cout << "Ai calcat pe o mina!\n";
                jocPierdut = true;
            }
            if (jocCastigat())
            {
                cout << "Ai castigat!!!\n";
                finish = true;
            }
            afiseazaHarta();
        }
    }



	cin >> n;

    return 0;
}

