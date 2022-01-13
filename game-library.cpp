#include <conio.h> // funkcia getch()
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#pragma pack(2)

struct Game
{
public:

    char name[50];

    long status;

    char type[50];

};

struct Games
{
    static const int Max_size = 100;

    char m_fileName[1000];

    int m_nMaxGames;

    Game m_gameList[Max_size];

    Games(const char *filename)
    {
        m_nMaxGames = 0;

        strcpy(m_fileName, filename);
    }

    void Add_data(const char *name, int status, const char *type)
    {
        int pos = m_nMaxGames;

        strcpy(m_gameList[pos].name,name);

        strcpy(m_gameList[pos].type,type);

        m_gameList[pos].status = status;

        m_nMaxGames++;

        Write_data();
    }

    void Edit_data(int pos, const char *name, int status, const char *type)
    {
        strcpy(m_gameList[pos].name,name);

        strcpy(m_gameList[pos].type,type);

        m_gameList[pos].status = status;

        Write_data();
    }

    void Delete_data(int pos)
    {
        m_nMaxGames--;

        for(int i = pos; i < m_nMaxGames; i++)
        {
            m_gameList[i] = m_gameList[i + 1];
        }

        Write_data();
    }

    int Read_data()
    {
        FILE *istream = fopen(m_fileName, "rb");

        if (istream == 0)

            return false;

        char buf[4096];

        int nTotalDataRead = 0;

        for(int i = 0; i < Max_size; i++)
        {
            if(feof(istream))
                break;

            int nBytesRead = fread(buf, 1, sizeof(Game), istream);

            if(nBytesRead < sizeof(Game))
                break;

            char *p = reinterpret_cast<char*>(&m_gameList[i]);

            memcpy(p, buf, sizeof(Game));

            nTotalDataRead++;
        }

        fclose(istream);

        m_nMaxGames = nTotalDataRead;

        return nTotalDataRead;
    }

    int Write_data()
    {
        FILE *ostream = fopen(m_fileName, "wb");

        if (ostream == 0)
            return false;

        int nTotalDataWritten = 0;

        char buf[4096];

        for(int i = 0; i < m_nMaxGames; i++)
        {
            fwrite((char*)&m_gameList[i], 1, sizeof(Game), ostream);

            nTotalDataWritten++;
        }
        fclose(ostream);

        return nTotalDataWritten;
    }
};

Games theGames("C:\\Games.bin"); // Číta a Zapíše do binárnych súborov

void gotoxy(int x, int y)
{
    COORD ord;
    ord.X = x;
    ord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

int MainMenu()
{
    ::system("cls");

    gotoxy(1,2);

    std::cout << "[Game-Library Database Application]";

    gotoxy(1,4);

    std::cout << "***********************************";

    gotoxy(1,5);

    std::cout << "*     1. Insert the game data     *";

    gotoxy(1,6);

    std::cout << "*     2. View the game data       *";

    gotoxy(1,7);

    std::cout << "*     3. Edit the game data       *";

    gotoxy(1,8);

    std::cout << "*     4. Delete the game data     *";

    gotoxy(1,9);

    std::cout << "*     5. Quit a program           *\n";

    gotoxy(1,10);

    std::cout << "***********************************\n\n";

    gotoxy(1,12);

    std::cout << "Your selection: ";

    int m = -1;

    std::cin >> m;

    gotoxy(1,11);
    if(m > 5 or m < 1){
        std::cout << "Invalid Entry, you have to use(1-5)!";
        return MainMenu();
    }
        
    return m;

}

void Input_data()
{
    while(1)
    {
        ::system("cls");

        gotoxy(1,2);

        std::cout << "[Game-Library Database Application]";

        gotoxy(1,4);

        std::cout << "***********************************";

        gotoxy(1,5);

        std::cout << "Name:                             *";

        gotoxy(1,6);

        std::cout << "Rating:                           *";

        gotoxy(1,7);

        std::cout << "Type:                             *";

        gotoxy(1,8);

        std::cout << "***********************************";

        gotoxy(7,5);

        char name[50];
        
        std::cin >> name;

        gotoxy(9,6);

        int status;

        std::cin >> status;

        gotoxy(7,7);

        char type[50];

        std::cin >> type;

        theGames.Add_data(name, status, type);

        gotoxy(1,10);

        std::cout << "Do you want to add another data(Y/N): ";

        char ch = getch();

        if(ch == 'Y' || ch == 'y')
            continue;
        else
            break;
    }
}

void View_data()
{
    theGames.Read_data();

    ::system("cls"); // prehľadnosť obrazovky

    gotoxy(1,2);

    std::cout << "                  [Game-Library Database Application]                      ";

    gotoxy(1,4);

    std::cout << "***************************************************************************";

    gotoxy(1,5);

    std::cout << "*   ID     Name                     Rating     Type                       *";
    
    gotoxy(1,6);

    std::cout << "***************************************************************************";


    int pos = 7;
    

    for(int i = 0; i < theGames.m_nMaxGames; i++)
    {
        gotoxy(5,pos);

        std::cout << i + 1;


        gotoxy(12,pos);

        std::cout << theGames.m_gameList[i].name;

        gotoxy(37,pos);

        std::cout << theGames.m_gameList[i].status;

        gotoxy(48,pos);

        std::cout << theGames.m_gameList[i].type;

        pos++;
    }

    gotoxy(1,pos++);

    std::cout << "***************************************************************************\n";

    pos++;

    gotoxy(1,pos++);
}

void Edit_data()
{
    View_data();

    std::cout << "Enter the ID you want to edit: ";

    int m;

    std::cin >> m;

    if(m >= 1 && m <= theGames.m_nMaxGames)
    {
        ::system("cls");

        gotoxy(1,2);

        std::cout << "[Game-Library Database Application] (Edit)";

        gotoxy(1,4);

        std::cout << "*****************************************";

        gotoxy(1,5);

        std::cout << "Name:                                   *";

        gotoxy(1,6);

        std::cout << "Rating:                                 *";

        gotoxy(1,7);

        std::cout << "Type:                                   *";

        gotoxy(1,8);

        std::cout << "*****************************************";

        gotoxy(7,5);

        char name[50];

        std::cin >> name;

        gotoxy(9,6);

        int status;

        std::cin >> status;

        gotoxy(7,7);

        char type[50];

        std::cin >> type;

        gotoxy(1,10);

        std::cout << "Data Updated. press ENTER key to return!";

        theGames.Edit_data(m - 1, name, status, type);       

        char ch = getch();
    }

    else
    {
        gotoxy(1,12);

        std::cout << "Invalid Entry. press ENTER key to return!";

        char ch = getch();
    }
}

void Delete_data()
{
    View_data();
    
    gotoxy(1,11);

    std::cout << "Enter the ID you want to delete: ";

    int m;

    std::cin >> m;

    if(m >= 1 && m <= theGames.m_nMaxGames)
    {
        theGames.Delete_data(m - 1);

        gotoxy(1,11);

        std::cout << "Data Deleted. press ENTER key to return!";

        char ch = getch();
    }

    else
    {   
        gotoxy(1,11);
        
        std::cout << "Invalid Entry. press ENTER key to return!";
        
        char ch = getch();
    }
}

int _tmain(int argc, _TCHAR* argv[]) // main() v C++
{
    theGames.Read_data();

    while(true)
    {
        int select = MainMenu();

        switch(select)
        {
        case 1:
            Input_data();
            break;

        case 2:
            {
            View_data();

            std::cout << "Press ENTER key to return!";

            char ch = getch();
            }
            break;

        case 3:
            Edit_data();
            break;

        case 4:
            Delete_data();
            break;

        case 5:

        default:
            return 0;
        };
    }
      return 0;
}