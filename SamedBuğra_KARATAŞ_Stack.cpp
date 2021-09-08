#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct Yigin{
	
	float imdb;
	char *isim;
	Yigin *sonraki;
	
};

Yigin *inputStack=NULL;
Yigin *tempStack=NULL;

void ekleme1(Yigin *data){					//inputStack i�in ekleme fonksiyonu
	
	if(inputStack==NULL){
		inputStack=data;
		inputStack->sonraki=NULL;
	}
	else{
		
		data->sonraki=inputStack;
		inputStack=data;
	}
}



void ekleme2(Yigin *data){					//tempStack i�in ekleme fonksiyonu
	
	if(tempStack==NULL){
		tempStack=data;
		tempStack->sonraki=NULL;
	}
	else{
		
		data->sonraki=tempStack;
		tempStack=data;
	}
}

Yigin *cikarma1(){							//inputStack i�in ��karma fonksiyonu
	Yigin *ptr=inputStack;
	inputStack=inputStack->sonraki;
	return ptr;
	
}

Yigin *cikarma2(){							//tempStack i�in ��karma fonksiyonu
	Yigin *ptr=tempStack;
	tempStack=tempStack->sonraki;
	return ptr;
}

void Dosya_oku(){							//dosayadan okuma i�lemi
	
	float sayi;
	char *isim;
	
	FILE* fp=fopen("filmler.txt","r");
	
	while(!feof(fp)){											//dosayn�n sonuna kadar d�ng�ye gir
		
		Yigin *dugum=(Yigin *) malloc(sizeof (Yigin));		//yeni bir d���m olu�tur
		isim = (char*)malloc(sizeof(char)*50);
		
		fscanf(fp,"%s %f",isim,&sayi);							//dosaydan verileri oku
		
		dugum->isim=isim;
		dugum->imdb=sayi;										//d���me atama yap
		dugum->sonraki=NULL;
		
		ekleme1(dugum);											//dugumu inputStack i�erisine ekle
	}
}


void Yer_Degistir(){											//s�ralama fonksiyonu
	while(inputStack!=NULL){									//input stack bo� olana kadar
		Yigin *emanet=cikarma1();								//y���n�n en son eleman�n� kenarda tut
		
		
		while(tempStack!=NULL){									//tempStack bo� olmad��� s�rece
			if( tempStack->imdb  >   emanet->imdb){				//tempStackteki puan daha b�y�k olanlar� ��kart�p inputStack e ekle
				
				Yigin *gecici=cikarma2();						
				ekleme1(gecici);
			}
			else break;
		}
		ekleme2(emanet);										//tempStack teki puan daha daha k���k ise �zerine ekle
	}	
}



void yazdir(Yigin *ptr){										//filmleri ve imdb puanlar�n� yazd�r
	
	while(ptr!=NULL){
		
		printf("%s isimli filmin imdb puani =  %.1f\n",ptr->isim,ptr->imdb);
		ptr=ptr->sonraki;	
	}
}






int main(){
	
	Dosya_oku();
	printf("\n\n-----Yigin 1-----\n\n");
	yazdir(inputStack);
	Yer_Degistir();
	printf("\n\n-----Yigin 2-----\n\n");
	yazdir(tempStack);
	printf("\n\n-----Yigin 1 Son Hali -----\n\n");
	yazdir(inputStack);
	
	
}
