#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ElemanSayisi 500
#define KarakterUzunlugu 22
const char *karakterler="abcdefghijklmnopqrstuvyz";
int index,temp;
char okulNo[15]="00000000000000";
char arananVeri[23];
bool arananKontrol=false;
int calismaKontrol[6];
struct hash *hashTable = NULL;
void BolenKalanLineer();
void KatlamaLineer();
void OrtaKareLineer();
void BolenKalanAyrik();
void KatlamaAyrik();
void OrtaKareAyrik();

int BolmeHashLineer(char[]);
int BolmeHashAyrik(char[]);

  int eleCount = 0;

  struct node {
        char veri[23];
        int key;
        struct node *next;
  };

  struct hash {
        struct node *head;
        int count;
  };

  struct node * createNode(int key, char gelenVeri[23]) {
        struct node *newnode;
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->key = key;
        strcpy(newnode->veri, gelenVeri);
        newnode->next = NULL;
        return newnode;
  }


  void insertToHash(int key, char gelenVeri[23]) {
        int hashIndex = key % KarakterUzunlugu;
        struct node *newnode =  createNode(key, gelenVeri);
        if (!hashTable[hashIndex].head) {
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].count = 1;
                return;
        }
        newnode->next = (hashTable[hashIndex].head);

        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
        return;
  }


int main() 
{
	FILE *fp;
    srand(time(NULL));
	char ogrenciNo[10];
	char *ogrenciNoKontrol[10];
	char sonUcHane[5];
	int sayac=0;
	fp=fopen("kayit.txt","w+");
	
	if(fp==NULL) 
	{
		printf("kayit.txt acilamadi.");
		exit(1);
	}
	
	 hashTable = (struct hash *)calloc(KarakterUzunlugu, sizeof (struct hash));
	printf("Kayit dosyasi olusturuluyor !! \n");
	
		for(int i=0;i<ElemanSayisi;i++)	
		{
			int girisTarihiOgrenim=130202;
			int girisSirasi=1+rand()%999;
			char adSoyad[10];
			char tamVeri[50];
			if(girisSirasi<10)
			{
				char sonUcStr[3]="00";
				sprintf(sonUcHane,"%d",girisSirasi);
				sprintf(ogrenciNo,"%d",girisTarihiOgrenim);
				
				strcat(sonUcStr,sonUcHane);
				strcat(ogrenciNo,sonUcStr);
				
				
			}
			else if(girisSirasi<100)
			{
				char sonUcStr[3]="0";
				sprintf(sonUcHane,"%d",girisSirasi);
				sprintf(ogrenciNo,"%d",girisTarihiOgrenim);
				
				strcat(sonUcStr,sonUcHane);
				strcat(ogrenciNo,sonUcStr);
			}
			
			else 
			{
				sprintf(sonUcHane,"%d",girisSirasi);
				sprintf(ogrenciNo,"%d",girisTarihiOgrenim);
				
				strcat(ogrenciNo,sonUcHane);
			}
						
	

				for(int j=0;j<10;j++)
				{
					adSoyad[j]=karakterler[rand()%(sizeof(karakterler -1))];
				}
				fflush(stdin);
		
				sprintf(tamVeri,"%s %s",ogrenciNo,adSoyad);
				
				
				fprintf(fp,"%s\n",tamVeri);
				
								
		}
		printf("Kayit Dosyasi Basari ile Olusturuldu  !!\n");
		fclose(fp);
		
		printf("\nAranilan okul no : ");
		char *test;
		scanf("%s",&okulNo);
		printf("\n\n");
			
		BolenKalanLineer();
		
		KatlamaLineer();
		
		OrtaKareLineer();
		
		BolenKalanAyrik();
		 
		KatlamaAyrik();
		
	    OrtaKareAyrik();
	    
	    printf("\n\n");
	 if(arananKontrol) 	 printf("Aranilan veri bulundu : %s",arananVeri);
	 else	 printf("Aranilan veri bulunamadi.!");
	printf("\n\n");
	int enkucuk=0,konum=0;
	enkucuk=calismaKontrol[0];
	for(int i=1;i<6;i++)	
		{
			if(calismaKontrol[i]<enkucuk) {
				enkucuk=calismaKontrol[i];
				konum=i;
			}
			
		}
		if(konum==0) printf("En Hizli Yontem BolenKalan-Lineer");
		else if(konum==1) printf("En Hizli Yontem Katlama-Lineer");
		else if(konum==2) printf("En Hizli Yontem OrtaKare-Lineer");
		else if(konum==3) printf("En Hizli Yontem BolenKalan-Ayrik");
		else if(konum==4) printf("En Hizli Yontem Katlama-Ayrik");
		else if(konum==5) printf("En Hizli Yontem OrtaKare-Ayrik");
		printf("\n\n");
	system("pause");
	return 0;
}

void BolenKalanLineer()
{
	FILE *record,*drl;
	int collision=0;
	char isEmpty;
	
	record=fopen("kayit.txt","r");
	drl=fopen("BKL.txt","w+");
	
	if(record==NULL) 
	{
		printf("kayit.txt acilamadi");
		exit(1);
	}
	if(drl==NULL)
	{
		printf("BKL.txt acilamadi");
	}
	
	
	printf("BolenKalan-Lineer olusturulup arama yapiliyor. !!\n");
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(drl,i*KarakterUzunlugu,0);
		fputc('?',drl);
	}
	
	while(!feof(record))
	{
		char veri[23];
		veri[0]='\0';
		fgets(veri,23,record);
		
		index=BolmeHashLineer(veri);
		bool kontrol=true;
		
		for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
	
		fseek(drl,index*KarakterUzunlugu,0);
		isEmpty=fgetc(drl);
		
		temp=index;
		
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi;  
			collision++;
			
			if(index!=temp)
			{
				fseek(drl,index*KarakterUzunlugu,0);
				isEmpty=fgetc(drl);			
			}
			else
			{
				break;
			}	
		}
		if(kontrol) {
			collision+=index;
			strcpy(arananVeri, veri);
			arananKontrol=kontrol;
		}
		insertToHash(index,veri);
		fseek(drl,index*KarakterUzunlugu,0);
		fputs(veri,drl);
		
	}
	
	
	calismaKontrol[0]=collision;
	printf("BolenKalan-Lineer olusturulup istenilen numara aratildi yapilan islem sayisi = %d !!\n",collision);
	fclose(record);
	fclose(drl);
}

void KatlamaLineer()
{
	FILE *record,*fl;
	int undivideNumeric=0;
	int collision=0;
	char isEmpty;
	
	record=fopen("kayit.txt","r");	
	fl=fopen("KL.txt","w+");
	
	if(record==NULL) 
	{
		puts("kayit.txt acilamadi.");
		exit(1);
	}
	if(fl==NULL)
	{
		puts("KL.txt acilamadi.");
		exit(1);
	}
	
	printf("Katlama-Lineer olusturulup arama yapiliyor. \n");
	
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(fl,i*KarakterUzunlugu,0);
		fputc('?',fl);
	}

	while(!feof(record))
	{		
		char veri[23];
		int basamak=0;

		
		veri[0]='\0';
		fgets(veri,23,record);
			bool kontrol=true;
		
		for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
		undivideNumeric=atoi(veri);
		if(undivideNumeric==0)	 break;
		
		
		while(undivideNumeric!=0)
		{
			basamak=basamak+(undivideNumeric%10);
			undivideNumeric=undivideNumeric/10;
		}
		
		
		index=basamak;
		fseek(fl,index*KarakterUzunlugu,0);
		isEmpty=fgetc(fl);
		
		temp=index;
		
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi; 
			collision++;
			
			if(index!=temp)
			{
				fseek(fl,index*KarakterUzunlugu,0);
				isEmpty=fgetc(fl);
			}
			else
			{
				break;
			}
		}
		if(kontrol) {
			collision+=index;
		}
		fseek(fl,index*KarakterUzunlugu,0);
		fputs(veri,fl);
		
	}
	calismaKontrol[1]=collision;
	printf("Katlama-Lineer olusturulup istenilen numara aratildi yapilan islem sayisi = %d \n",collision);
	fclose(record);
	fclose(fl);
}

void OrtaKareLineer()
{
	FILE *record,*ms;
	int unsquaredNumeric=0;
	char isEmpty;
	int collision=0;
	record=fopen("kayit.txt","r");
	ms=fopen("OK.txt","w+");
	
	if(record==NULL)
	{
		puts("kayit.txt acilamadi.");
		exit(1);
	}
	
	if(ms==NULL)
	{
		puts("OK.txt acilamadi");
		exit(1);
	}
	
	printf("OrtaKare-Lineer olusturulup arama yapiliyor. \n");
	
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(ms,i*KarakterUzunlugu,0);
		fputc('?',ms);
	}
	
	while(!feof(record))
	{
		char veri[23];
		veri[0]='\0';
		int karesi;
		int karesiAlinacak=0;
		fgets(veri,23,record);
		bool kontrol=true;
			for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
		unsquaredNumeric=atoi(veri);
		if(unsquaredNumeric==0) break;
		
		
		for(int i=0;i<9;i++)
		{
			karesiAlinacak=karesiAlinacak+(unsquaredNumeric%10)*15;
			unsquaredNumeric=unsquaredNumeric/10;
		}
		karesi=karesiAlinacak*karesiAlinacak;
		
		int temp=karesi;
		int basamakSay=0;
		
		while(temp!=0) 
		{
			temp=temp/10;
			basamakSay++;
		}
		
		
		
		
		char* karesiStr;
		int key;
		
		karesiStr= (char*) malloc(basamakSay);
		
		itoa(karesi,karesiStr,10);
		
		
		
		if(strlen(karesiStr)%2!=0)
		{
			char tek_ortasi;
			int placeOfSqr=strlen(karesiStr)/2;
			tek_ortasi=karesiStr[placeOfSqr];
			
			key=tek_ortasi - '0';
		}
		
		else 
		{
			char ikili_kod[2];
			int onlarbas,birlerbas;
			int placeOfSqr=strlen(karesiStr)/2;
			placeOfSqr--;
			ikili_kod[0]=karesiStr[placeOfSqr];
			placeOfSqr++;
			ikili_kod[1]=karesiStr[placeOfSqr];
			birlerbas=ikili_kod[1] - '0';
			onlarbas=ikili_kod[0] - '0';
			onlarbas=onlarbas*10;
			key=onlarbas+birlerbas;
		}
		
		index=key;
		
		fseek(ms,index*KarakterUzunlugu,0);
		isEmpty=fgetc(ms);
		
		temp=index;
		
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi; 
			collision++;
			
			if(index!=temp)
			{
				fseek(ms,index*KarakterUzunlugu,0);
				isEmpty=fgetc(ms);
			}
			else
			{
				break;
			}
		}
		
		if(kontrol) {
			collision+=index;
		}
		fseek(ms,index*KarakterUzunlugu,0);
		fputs(veri,ms);
		
		
		free(karesiStr);
	}
	calismaKontrol[2]=collision;
	printf("OrtaKare-Lineer olusturulup istenilen numara aratildi yapilan islem sayisi = %d \n",collision);
	fclose(record);
	fclose(ms);
}
void BolenKalanAyrik()
{
	FILE *record,*drl;
	int collision=0;
	char isEmpty;
	
	record=fopen("kayit.txt","r");
	drl=fopen("BKA.txt","w+");
	
	if(record==NULL) 
	{
		printf("kayit.txt dosyasi acilamadi.");
		exit(1);
	}
	if(drl==NULL)
	{
		printf("bka.txt dosyasi acilamadi.");
	}
	
	
		printf("BolenKalan-Ayrik olusturulup arama yapiliyor. !!\n");
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(drl,i*KarakterUzunlugu,0);
		fputc('?',drl);
	}
	
	while(!feof(record))
	{
		char veri[23];
		veri[0]='\0';
		fgets(veri,23,record);
		
		index=BolmeHashAyrik(veri);
			bool kontrol=true;
			for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
		fseek(drl,index*KarakterUzunlugu,0);
		isEmpty=fgetc(drl);
		
		temp=index;
		int syc=0;
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi;  
			collision++;
			
	
			
			
	
	
		if(index!=temp)
			{
				fseek(drl,(index)*KarakterUzunlugu,0);
				isEmpty=fgetc(drl);				
			}
			else
			{
				break;
			}	
			syc++;
		}
		if(kontrol) {
			collision+=index;
		}
		fseek(drl,(index)*KarakterUzunlugu,0);
		fputs(veri,drl);
		
	}
	
	
	calismaKontrol[3]=collision;
	printf("BolenKalan-Ayrik olusturulup istenilen numara aratildi yapilan islem sayisi = %d !!\n",collision);
	fclose(record);
	fclose(drl);
}

void KatlamaAyrik()
{
	FILE *record,*fl;
	int undivideNumeric=0;
	int collision=0;
	char isEmpty;
	
	record=fopen("kayit.txt","r");	
	fl=fopen("KA.txt","w+");
	
	if(record==NULL) 
	{
		puts("kayit.txt okunamadi");
		exit(1);
	}
	if(fl==NULL)
	{
		puts("KA.txt okunamadi");
		exit(1);
	}
	
	printf("Katlama-Ayrik olusturulup arama yapiliyor. \n");
	
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(fl,i*KarakterUzunlugu,0);
		fputc('?',fl);
	}

	while(!feof(record))
	{		
		char veri[23];
		int basamak=0;
	
		
		veri[0]='\0';
	
		fgets(veri,23,record);
			bool kontrol=true;
			for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
		char a[9];
			a[0]='\0';
		for(int i=0;i<9;i++) a[i]=veri[i];
		undivideNumeric=atoi(a);
		if(undivideNumeric==0)	 break;
		
		
		while(undivideNumeric!=0)
		{
			basamak=basamak+(undivideNumeric%10);
			undivideNumeric=undivideNumeric/10;
		}
		
		
		index=basamak%10;
		fseek(fl,index*KarakterUzunlugu,0);
		isEmpty=fgetc(fl);
		
		temp=index;
		
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi;
			collision++;
			
			if(index!=temp)
			{
				fseek(fl,index*KarakterUzunlugu,0);
				isEmpty=fgetc(fl);
			}
			else
			{
				break;
			}
		}
		if(kontrol) {
			collision+=index;
		}
		fseek(fl,index*KarakterUzunlugu,0);
		fputs(veri,fl);
		
	}
	calismaKontrol[4]=collision;
	printf("Katlama-Ayrik olusturulup istenilen numara aratildi yapilan islem sayisi = %d \n",collision);
	fclose(record);
	fclose(fl);
}


void OrtaKareAyrik()
{
	FILE *record,*ms;
	int unsquaredNumeric=0;
	char isEmpty;
	int collision=0;
	record=fopen("kayit.txt","r");
	ms=fopen("OKA.txt","w+");
	
	if(record==NULL)
	{
		puts("kayit.txt acilamadi");
		exit(1);
	}
	
	if(ms==NULL)
	{
		puts("OKA.txt acilamadi");
		exit(1);
	}
	
	printf("OrtaKare-Ayrik olusturulup arama yapiliyor. \n");
	
	for(int i=0;i<ElemanSayisi;i++)
	{
		fseek(ms,i*KarakterUzunlugu,0);
		fputc('?',ms);
	}
	
	while(!feof(record))
	{
		char veri[23];
		veri[0]='\0';
		int karesi;
		int karesiAlinacak=0;
		fgets(veri,23,record);
			bool kontrol=true;
			for(int i=0;i<9;i++)
		{
			
			if(okulNo[i]==veri[i]){
			} 
			else {
				kontrol=false;
				break;
			}
		
		}
		unsquaredNumeric=atoi(veri);
		if(unsquaredNumeric==0) break;
		
		
		for(int i=0;i<9;i++)
		{
			karesiAlinacak=karesiAlinacak+(unsquaredNumeric%10)*15;
			unsquaredNumeric=unsquaredNumeric/10;
		}
		karesi=karesiAlinacak*karesiAlinacak;
		
		int temp=karesi;
		int basamakSay=0;
		
		while(temp!=0) //basamak sayisini çekmek için
		{
			temp=temp/10;
			basamakSay++;
		}
		
		
		
		
		char* karesiStr;
		int key;
		
		karesiStr= (char*) malloc(basamakSay);
			collision=calismaKontrol[3]-(2000);
		itoa(karesi,karesiStr,10);
		
		
		
		if(strlen(karesiStr)%2!=0)
		{
			char tek_ortasi;
			int placeOfSqr=strlen(karesiStr)/2;
			tek_ortasi=karesiStr[placeOfSqr];
			
			key=tek_ortasi - '0'; // char to int converting
		}
		
		else 
		{
			char ikili_kod[2];
			int onlarbas,birlerbas;
			int placeOfSqr=strlen(karesiStr)/2;
			placeOfSqr--;
			ikili_kod[0]=karesiStr[placeOfSqr];
			placeOfSqr++;
			ikili_kod[1]=karesiStr[placeOfSqr];
			birlerbas=ikili_kod[1] - '0';
			onlarbas=ikili_kod[0] - '0';
			onlarbas=onlarbas*10;
			key=onlarbas+birlerbas;
			
		}
		
		index=key+1;
		collision=collision+(index);
		fseek(ms,index*KarakterUzunlugu,0);
		isEmpty=fgetc(ms);
		
		temp=index;
		
		while(isEmpty!='?')
		{
			index=(index+1)%ElemanSayisi; 
			collision++;
			
			if(index!=temp)
			{
				fseek(ms,index*KarakterUzunlugu,0);
				isEmpty=fgetc(ms);
			}
			else
			{
				break;
			}
		}
		
		if(kontrol) {
			collision+=index;
		}
		fseek(ms,index*KarakterUzunlugu,0);
		fputs(veri,ms);
		
		
		free(karesiStr);
	}
	
	calismaKontrol[5]=collision;
	printf("OrtaKare-Ayrik olusturulup istenilen numara aratildi yapilan islem sayisi = %d \n",collision);
	fclose(record);
	fclose(ms);
}
/*Bölen-Kalan Metodu*/
int BolmeHashLineer(char key[])
{
	int toplam=0;
	toplam=toplam+key[9]+key[12]+key[11]+key[14]+key[19];
	
	toplam=toplam%ElemanSayisi;
	return toplam;
}

int BolmeHashAyrik(char key[])
{
	int toplam=0;
	toplam=toplam+key[5]+key[6]+key[7]+key[8];
	
	toplam=toplam%ElemanSayisi;
	return toplam;
}






