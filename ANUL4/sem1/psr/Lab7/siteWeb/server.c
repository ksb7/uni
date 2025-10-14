#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 2000
#define BUFFER_SIZE 1000

int parseRequest(char* requestFromClient, int requestSize, char* string, int stringSize)
{
	/* charPtr[4] este un tabel cu 4 pointere care poiteaza asupra inceputului sirului, cele 2 spatii 	*/
	/* ale cererii (cel de dupa GET si cel de dupa numelefisierului)	*/
	/* Pointerul end se va utiliza pentru a pune un '\0' la sfarsitul returului dublu la linie.		*/

	char *charPtr[4], *end;

	/* Se cauta dublul retur la linie in requestFromClient
	* in functie de sisteme de va utiliza \r sau \n (new line, new feed)
	* prin conventie in http se utilizeaza ambele \r\n dar in practic e vorba de un singur retur la linie.
	* Pentru a simplifica, aici se cauta doar '\n'.
	* Se va plasa un '\0' imediat dupa dublul retur la linie permitand prelucrarea cererii 
	* casi uilizarea functiilor din biblioteca string.h. 
	*/

	/* Citire pana la dublul retur de linie */
	requestFromClient[requestSize-1]='\0';//Permite utilizarea strchr() - atentie, nu merge daca requestSize indica lungimea sirului de caractere

	if( (end=strstr(requestFromClient,"\r\n\r\n"))==NULL) return(-1);
	*(end+4)='\0';
	
	// Verificarea syntaxei (GET fisier HTTP/1.1) 		
	charPtr[0]=requestFromClient;	//Inceputul cererii (GET in principiu)
	//Se cauta primul spatiu, codul ascii 0x20 (in hexa), este inceputul numelui fisierului
	charPtr[1]=strchr(requestFromClient,' ');	
	if(charPtr[1]==NULL) return(-1);
	charPtr[2]=strchr(charPtr[1]+1,' ');	
	if(charPtr[2]==NULL) return(-1);
	charPtr[3]=strchr(charPtr[2]+1,'\r');	
	if(charPtr[3]==NULL) return(-1);

	//Se separa sirurile
	*charPtr[1]='\0';
	*charPtr[2]='\0';
	*charPtr[3]='\0';

	if(strcmp(charPtr[0],"GET")!=0) return(-1);
	if(strcmp(charPtr[2]+1,"HTTP/1.1")!=0) return(-1);
	strncpy(string,charPtr[1]+2,stringSize);//Se decaleasa sirul cu 2 octeti: primul octet este '\0', al doilea decalaj permite sa retragem "/" 

	//Daca stringSize nu este suficient de mare, sirul nu contine '\0'. Pentru a verifica et suficient sa testam string[stringSize-1] care
	// trebuie sa fie = '\0' deoarece  strncpy unple sirul cu '\0' cand exista loc.
	if(string[stringSize-1]!='\0'){
		fprintf(stderr,"Erreur parseRequest(): lungimea sirului string nu este suficienta (stringSize=%d)\n",stringSize);
		exit(3);
	}
	
	//DEBUG 
	if( *(charPtr[1]+2) == '\0') fprintf(stderr,"DEBUG-SERVEUR: numele fisieruui este vid -\nDEBUG-SERVEUR: - se asociaza fisierul implicit index.html\n");
	else fprintf(stderr,"DEBUG-SERVEUR: numele fisierului cerut este %s\n",string);

	if( *(charPtr[1]+2) == '\0') strcpy(string,"index.html");

	return(0);
}

const char* getContentType(const char* filename) 
{
    const char *ext = strrchr(filename, '.');  // gasim ultima aparitie a punctului
    if (!ext) return "text/plain"; // fara extensie => text

    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0)
        return "text/html";
    else if (strcmp(ext, ".txt") == 0)
        return "text/plain";
    else if (strcmp(ext, ".png") == 0)
        return "image/png";
    else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
        return "image/jpeg";
    else if (strcmp(ext, ".gif") == 0)
        return "image/gif";
    else if (strcmp(ext, ".css") == 0)
        return "text/css";
    else if (strcmp(ext, ".js") == 0)
        return "application/javascript";
    else
        return "application/octet-stream"; // fallback pentru fisiere binare necunoscute
}


int main() 
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    char fileName[256];
    FILE *fp;
    int bytesRead;
    
    // folosit ca sa afisam IP-ul clientului
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Creare socket TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) 
    {
        perror("Eroare la crearea socketului");
        exit(EXIT_FAILURE);
    }

    // setam adresa serverului
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // asculta pe toate interfețele
    address.sin_port = htons(PORT);

    // Bind + listen
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
    {
        perror("Eroare la bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) 
    {
        perror("Eroare la listen");
        exit(EXIT_FAILURE);
    }

    printf("Server pornit pe portul %d...\n", PORT);

    // bucla pentru a accepta conexiuni, va exista atata timp cat procesul e activ
    while (1) 
    {
        new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (new_socket < 0) 
        {
            perror("Eroare la accept");
            continue;
        }
        
        //afiseaza adresa IP a clientului 
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, client_ip, sizeof(client_ip));
        printf("Conexiune de la: %s\n", client_ip);

        // citeste cererea HTTP
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer) - 1);

        printf("Cerere primită:\n%s\n", buffer);

        // Folosim parseRequest pentru a obtine numele fișierului
        if (parseRequest(buffer, BUFFER_SIZE, fileName, sizeof(fileName)) == -1) 
        {
            char *error = "HTTP/1.1 400 Bad Request\r\n\r\nEroare la cerere.\n";
            write(new_socket, error, strlen(error));
            close(new_socket);
            continue;
        }

        printf("Fișier cerut: %s\n", fileName);
	
	// deschide fisierul in mod read
        fp = fopen(fileName, "r");
        if (fp == NULL) 
        {
            char *notfound = "HTTP/1.1 404 Not Found\r\n\r\nFisierul nu exista.\n";
            write(new_socket, notfound, strlen(notfound));
        } else 
        {
            char header[256];
            // trimitem header cu Content-Type corect
	    snprintf(header, sizeof(header),
	 	"HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",
	 	getContentType(fileName));
	    write(new_socket, header, strlen(header));

            // Trimite continutul fișierului
            while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) 
            {
                write(new_socket, buffer, bytesRead);
            }
            fclose(fp);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}

