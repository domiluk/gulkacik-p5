#include "ball.h"

#define SERVER 1
#define CLIENT 2

char rcv[32] = "";                      // Pøijímaný text
char snd[5][5] = {"","","","",""};
char sndqm[11] = "";
int qmval[10] = {3,3,3,3,3,3,3,3,3,3};
char gm[32] = "";                      // Velky message

struct sockaddr_in sockName;           // "Jméno" soketu a èíslo portu
struct sockaddr_in clientInfo;         // Klient, který se pøipojil 
SOCKET mainSocket, client;             // Sokety
char buf[128] = "";                			// Pøijímací buffer
int size;                              // Poèet pøijatých a odeslaných bytù
int addrlen;                           // Velikost adresy vzdáleného poèítaèe
struct hostent *host;                   // Vzdálený poèítaè
struct sockaddr_in serverSock;          // Vzdálený "konec potrubí"
int server;                           // Soket
char ip[100];                           // IP
int port = 20001;                      // Èíslo portu

WORD wVersionRequested = MAKEWORD(2,2); // Èíslo verze
WSADATA data;           // Struktura s info. o knihovnì;

int dl_send(const char *text, int to)
{
   int s=0;
   if(to == SERVER) // to server
   {
	   if ((s = send(server, text, (int)strlen(text)+1, 0)) == -1)
	   {
	      printf("Problem s odoslanim dat\n");
	      WSACleanup();
	      system("PAUSE");
	      return -1;
	   }
			}
			else if(to == CLIENT) // to client
			{
				if ((s = send(client, text, (int)strlen(text)+1, 0)) == -1)
	   {
	      printf("Problem s odoslanim dat\n");
	      WSACleanup();
	      system("PAUSE");
	      return -1;
	   }
			}
   
   return s;
}


int dl_recv(char *dest, int from)
{
   int s = 0;
	  if(from == CLIENT)
	  {
				s = recv(client, dest, 5, 0);
	   if (s == -1 || s == 0)
	   {
					  printf("Nejde prijat data s = %d\n", s);
	   }
		 }
   else if(from == SERVER)
   {
    s = recv(server, dest, 31, 0);
    if (s == -1 || s == 0)
    {
       printf("Nejde prijat data s = %d\n", s);
    }
   }
}


int make_values_qm(LEVEL *l)
{
 int i;
 for(i = 0; i < lvl->qma*2; i++)
 {
  if(l->qm[i].done == 1)
   qmval[i] = 2;
  else
   qmval[i] = l->qm[i].flip;
 }
}

int dl_code(char *dest, int i, int i2, int cifry)
{
	if(cifry == 4)
	{
	  dest[0] = 48 + (i / 1000);
	  dest[1] = 48 + ((i % 1000) / 100);
	  dest[2] = 48 + (((i % 1000) % 100) / 10);
	  dest[3] = 48 + i % 10;
	  dest[4] = '\0';
	}
	else if(cifry == 2)
	{
		 dest[0] = 48 + (i / 10);
		 dest[1] = 48 + (i % 10);
		 dest[2] = 48 + (i2 / 10);
		 dest[3] = 48 + (i2 % 10);
		 dest[4] = '\0';
	}
}

int dl_code_qm(char *dest, int i[10])
{
	dest[0] = 48 + i[0]; dest[5] = 48 + i[5];
	dest[1] = 48 + i[1]; dest[6] = 48 + i[6];
	dest[2] = 48 + i[2]; dest[7] = 48 + i[7];
	dest[3] = 48 + i[3]; dest[8] = 48 + i[8];
	dest[4] = 48 + i[4]; dest[9] = 48 + i[9];
	dest[10] = '\0';
}

int dl_decode_server(const char *c)
{
   bll2_is_up = c[0] - 48;
   bll2_is_down = c[1] - 48;
   bll2_is_left = c[2] - 48;
   bll2_is_right = c[3] - 48;
   if(c[4] == '\0') printf("message probably okay\n");
   else printf("message corrupted\n");
   
			/*int i = 0;
   
   i += 1000 * (c[0] - 48);
   i += 100 * (c[1] - 48);
   i += 10 * (c[2] - 48);
   i += c[3] - 48;
   bll2->x = i;
   
   i += 1000 * (c[4] - 48);
   i += 100 * (c[5] - 48);
   i += 10 * (c[6] - 48);
   i += c[7] - 48;
   bll2->y = i;*/
}

int dl_decode_client(const char *c)
{
   int a = 0;
   int i = 0;
   printf("%s\n", c);
   //server x
   i += 1000 * (c[0] - 48);
   i += 100 * (c[1] - 48);
   i += 10 * (c[2] - 48);
   i += c[3] - 48;
   bll2->x = i;
   //server y
   i = 0;
   i += 1000 * (c[4] - 48);
   i += 100 * (c[5] - 48);
   i += 10 * (c[6] - 48);
   i += c[7] - 48;
   bll2->y = i;
   //client x
   i = 0;
   i += 1000 * (c[8] - 48);
   i += 100 * (c[9] - 48);
   i += 10 * (c[10] - 48);
   i += c[11] - 48;
   bll->x = i;
   //client y
   i = 0;
   i += 1000 * (c[12] - 48);
   i += 100 * (c[13] - 48);
   i += 10 * (c[14] - 48);
   i += c[15] - 48;
   bll->y = i;
   //server pts
   i = 0;
   i += 10 * (c[16] - 48);
   i += c[17] - 48;
   bll2->points = i;
   //client pts
   i = 0;
   i += 10 * (c[18] - 48);
   i += c[19] - 48;
   bll->points = i;
   //QMs
   for(a = 0; a < lvl->qma*2; a++)
   {
				i = 0;
				i = c[20+a] - 48;
				if(i == 2)
				{
					lvl->qm[a].done = 1;
     draw_sprite(lvl->bmp, symbol_brick[lvl->qm[a].value-5], lvl->qm[a].x*FIELD_SIZE, lvl->qm[a].y*FIELD_SIZE);
    }
				else if(i == 1)
				{
				 lvl->qm[a].flip = i;
				 draw_sprite(lvl->bmp, symbol_brick[lvl->qm[a].value-10], lvl->qm[a].x*FIELD_SIZE, lvl->qm[a].y*FIELD_SIZE);
    }
    else if(i == 0)
    {
     lvl->qm[a].flip = i;
				 draw_sprite(lvl->bmp, qm[rand()%4], lvl->qm[a].x*FIELD_SIZE, lvl->qm[a].y*FIELD_SIZE);
    }
			}
			if(c[30] == '\0') printf("message probably okay\n");
			else printf("message corrupted\n");
}

int make_great_msg(char *msg1, char *msg2, char *msg3, char *msg4, char *msg5, char *msg6)
{
   strcpy(gm, "\0");
   strcat(gm, msg1);
   strcat(gm, msg2);
   strcat(gm, msg3);
   strcat(gm, msg4);
   strcat(gm, msg5);
   strcat(gm, msg6);
   gm[30] = '\0';
}

int init_server()
{
 // Pøipravíme sokety na práci
 if (WSAStartup(wVersionRequested, &data) != 0)
 {
    printf("Nepodaøilo se inicializovat sokety\n");
    system("PAUSE");
    return -1;
 }
 // Vytvoøíme soket
 if ((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
 {
    printf("Nelze vytvoøit soket\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 // Zaplníme strukturu sockaddr_in
 // 1) Rodina protokolù;
 sockName.sin_family = AF_INET;
 // 2) Èíslo portu, na kterém èekáme
 sockName.sin_port = htons(port);
 // 3) Nastavení IP adresy lokální síové karty, pøes kterou 
 // je možno se pøipojit. 
 // Nastavíme možnost pøipojit se odkudkoliv. 
 sockName.sin_addr.s_addr = INADDR_ANY;
 //pøiøadíme soketu jméno
 if (bind(mainSocket, (struct sockaddr *)&sockName, sizeof(sockName)) 
        == SOCKET_ERROR)
 {
    printf("Problém s pojmenováním soketu.\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 // Vytvoøíme frontu požadavkù na spojení. 
 // Vytvoøíme frontu maximální velikosti 10 požadavkù.
 if (listen(mainSocket, 10) == SOCKET_ERROR)
 {
    printf("Problém s vytvoøením fronty\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 // Poznaèím si velikost struktury clientInfo.
 // Pøedám to funkci accept. 
 addrlen = sizeof(clientInfo);
 // Vyberu z fronty požadavek na spojení.
 // "client" je nový soket spojující klienta se serverem.
 client = accept(mainSocket, (struct sockaddr*)&clientInfo, 
                   &addrlen);
 
 int flags = 1;
 //ioctlsocket(client, FIONBIO, (u_long *)&flags);
 
 int totalSize = 0;
 if (client == INVALID_SOCKET)
 {
     printf("Problém s pøijetím spojeni\n");
     WSACleanup();
     system("PAUSE");
     return -1;
 }
 // Zjistím IP adresu klienta.
 printf("Nìkdo se pøipojil z adresy: %s\n", inet_ntoa((struct in_addr)clientInfo.sin_addr));
}

int init_client()
{
	// Pøipravíme sokety na práci
 if (WSAStartup(wVersionRequested, &data) != 0)
 {
    printf("Nepodaøilo se inicializovat sokety\n");
    system("PAUSE");
    return -1;
 }
 // Zjistíme info o vzdáleném poèítaèi
 if ((host = gethostbyname(ip)) == NULL)
 {
    printf("Špatná adresa\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 // Vytvoøíme soket
 if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
 {
    printf("Nelze vytvoøit soket\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 
 // Zaplníme strukturu sockaddr_in
 // 1) Rodina protokolù
 serverSock.sin_family = AF_INET;
 // 2) Èíslo portu, ke kterému se pøipojíme
 serverSock.sin_port = htons(port);
 // 3) Nastavení IP adresy, ke které se pøipojíme
 memcpy(&(serverSock.sin_addr), host->h_addr, host->h_length);
 // Pøipojení soketu
 if (connect(server, (struct sockaddr *)&serverSock, sizeof(serverSock)) == -1)
 {
    printf("Nelze navázat spojení\n");
    WSACleanup();
    system("PAUSE");
    return -1;
 }
 
 int flags = 1;
 //ioctlsocket(server, FIONBIO, (u_long *)&flags);
}
