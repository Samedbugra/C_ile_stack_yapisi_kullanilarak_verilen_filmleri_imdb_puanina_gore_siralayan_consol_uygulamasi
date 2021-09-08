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

void ekleme1(Yigin *data){					//inputStack için ekleme fonksiyonu
	
	if(inputStack==NULL){
		inputStack=data;
		inputStack->sonraki=NULL;
	}
	else{
		
		data->sonraki=inputStack;
		inputStack=data;
	}
}



void ekleme2(Yigin *data){					//tempStack için ekleme fonksiyonu
	
	if(tempStack==NULL){
		tempStack=data;
		tempStack->sonraki=NULL;
	}
	else{
		
		data->sonraki=tempStack;
		tempStack=data;
	}
}

Yigin *cikarma1(){							//inputStack için çýkarma fonksiyonu
	Yigin *ptr=inputStack;
	inputStack=inputStack->sonraki;
	return ptr;
	
}

Yigin *cikarma2(){							//tempStack için çýkarma fonksiyonu
	Yigin *ptr=tempStack;
	tempStack=tempStack->sonraki;
	return ptr;
}

void Dosya_oku(){							//dosayadan okuma iþlemi
	
	float sayi;
	char *isim;
	
	FILE* fp=fopen("filmler.txt","r");
	
	while(!feof(fp)){											//dosaynýn sonuna kadar döngüye gir
		
		Yigin *dugum=(Yigin *) malloc(sizeof (Yigin));		//yeni bir düðüm oluþtur
		isim = (char*)malloc(sizeof(char)*50);
		
		fscanf(fp,"%s %f",isim,&sayi);							//dosaydan verileri oku
		
		dugum->isim=isim;
		dugum->imdb=sayi;										//düðüme atama yap
		dugum->sonraki=NULL;
		
		ekleme1(dugum);											//dugumu inputStack içerisine ekle
	}
}


void Yer_Degistir(){											//sýralama fonksiyonu
	while(inputStack!=NULL){									//input stack boþ olana kadar
		Yigin *emanet=cikarma1();								//yýðýnýn en son elemanýný kenarda tut
		
		
		while(tempStack!=NULL){									//tempStack boþ olmadýðý sürece
			if( tempStack->imdb  >   emanet->imdb){				//tempStackteki puan daha büyük olanlarý çýkartýp inputStack e ekle
				
				Yigin *gecici=cikarma2();						
				ekleme1(gecici);
			}
			else break;
		}
		ekleme2(emanet);										//tempStack teki puan daha daha küçük ise üzerine ekle
	}	
}



void yazdir(Yigin *ptr){										//filmleri ve imdb puanlarýný yazdýr
	
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
