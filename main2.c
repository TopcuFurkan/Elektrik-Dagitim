
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_RECORD_COUNT 100

struct indirici{
    int id;
    double x1;
    double x2;
    double y1;
    double y2;
};


struct musteri{
    int id;
    int tip;
    double x1;
    double x2;
    double y1;
    double y2;
};


struct hat{
    int id;
    double x1;
    double x2;
    double y1;
    double y2;
};

void readFile(char *filename, struct indirici indiriciler[MAX_RECORD_COUNT],
                struct musteri musteriler[MAX_RECORD_COUNT], struct hat hatlar[MAX_RECORD_COUNT] );

void print_Test_System_file(struct indirici indiriciler[MAX_RECORD_COUNT],
                            struct musteri musteriler[MAX_RECORD_COUNT], struct hat hatlar[MAX_RECORD_COUNT] );


void indiriciMerkezBilgileri(struct indirici indiriciler[MAX_RECORD_COUNT]);
void musteriBilgileri(struct musteri musteriler[MAX_RECORD_COUNT]);
void hatBilgileri(struct hat hatlar[MAX_RECORD_COUNT]);

double toplamHatUzunlugu(struct hat hatlar[MAX_RECORD_COUNT]);

double ikiHatArasindakiUzaklik(double x1, double x2, double y1, double y2);

void kopukHatlar(struct hat hatlar[MAX_RECORD_COUNT]);
void hatGuzergah(struct hat hatlar[MAX_RECORD_COUNT]);


void toplamMusteriSayisi(struct musteri musteriler[MAX_RECORD_COUNT]);
                                                                                             // tüm fonksyon adlarý bulunan maine kadar olan bölüm
void hatBilgi(int id, struct hat hatlar[MAX_RECORD_COUNT]);
void musteriBilgi(int id, struct musteri musteriler[MAX_RECORD_COUNT]);
void indiriciBilgi(int id, struct indirici indiriciler[MAX_RECORD_COUNT]);

void kopukHatlariListele(struct hat hatlar[MAX_RECORD_COUNT]);
void musteriKusUcusuMesafe(struct musteri musteriler[MAX_RECORD_COUNT], struct indirici indiriciler[MAX_RECORD_COUNT]);




void musteriHatUzunlugu(struct musteri musteriler[MAX_RECORD_COUNT],struct indirici indiriciler[MAX_RECORD_COUNT],
                         struct hat hatlar[MAX_RECORD_COUNT]);




void musteriHatGuzergahi(int musteriId, 
struct musteri musteriler[MAX_RECORD_COUNT],
struct indirici indiriciler[MAX_RECORD_COUNT], 
struct hat hatlar[MAX_RECORD_COUNT]);




int lineNumber = 0;
int indiriciCount = 0;
int musteriCount = 0;
int hatCount = 0;
int i=0;
int j=0;

int main(){                                                    //fonksyon çaðýrma iþlemleri yaptýðýmýz kod bloðu

    struct indirici indiriciler[MAX_RECORD_COUNT];
    struct musteri musteriler[MAX_RECORD_COUNT];
    struct hat hatlar[MAX_RECORD_COUNT];

    int hatId, musteriId, indiriciId;


    char filename[] = "test_system.txt";

    //dosyadan oku ve struclara ata
    readFile(filename, indiriciler, musteriler,hatlar);

    //dosyayi bastir
    print_Test_System_file(indiriciler, musteriler,hatlar);

    //indirici merkez bilgileri bastir
    indiriciMerkezBilgileri(indiriciler);

    //musteri  bilgileri bastir
    musteriBilgileri(musteriler);

    //hat  bilgileri bastir
    hatBilgileri(hatlar);

    
    printf("Toplam hat uzunlugu : %lf\n", toplamHatUzunlugu(hatlar));


    kopukHatlar(hatlar);


    hatGuzergah(hatlar);

    toplamMusteriSayisi(musteriler);

    printf("hangi HATTIN bilgilerini istersiniz (id yaziniz)?");
	scanf("%d",&hatId);
    hatBilgi(hatId, hatlar);


    printf("hangi MUSTERININ bilgilerini istersiniz (id yaziniz)?");
	scanf("%d",&musteriId);
    musteriBilgi(musteriId, musteriler);

    printf("hangi INDIRICININ bilgilerini istersiniz (id yaziniz)?");
	scanf("%d",&indiriciId);
    indiriciBilgi(indiriciId, indiriciler);


    kopukHatlariListele(hatlar);
    printf("\nkopukHatlariListele Yazildi\n");


    musteriKusUcusuMesafe(musteriler, indiriciler);
    printf("\nmusteriKusUcusuMesafe Yazildi\n");

    musteriHatGuzergahi(123, musteriler, indiriciler, hatlar);
    printf("\n123 Musteri Hat Gugzergahi Yazildi\n");
    musteriHatGuzergahi(101, musteriler, indiriciler, hatlar);
    printf("\n101 Musteri Hat Gugzergahi Yazildi\n");
    musteriHatGuzergahi(55, musteriler, indiriciler, hatlar);
    printf("\n55 Musteri Hat Gugzergahi Yazildi\n");


    musteriHatUzunlugu(musteriler, indiriciler, hatlar);
    printf("\nmusteriHatUzunlugu Yazildi\n");

    



    return 0;
}




void readFile(char *filename, struct indirici indiriciler[MAX_RECORD_COUNT],
              struct musteri musteriler[MAX_RECORD_COUNT], struct hat hatlar[MAX_RECORD_COUNT] ) {

    FILE* filePointer;
    int karakteruzunluk = 255;
    char uzunluk[karakteruzunluk];

    filePointer = fopen(filename, "r");


    const size_t line_size = 300;
    char* line = malloc(line_size);
    char temp[20];


    fgets(line, line_size, filePointer);
    while (fgets(line, line_size, filePointer) != NULL)  {
        //printf("%s", line);
        sscanf(line, "%s",temp);
        if( strcmp(temp,"END") == 0)
            break;

        sscanf(line, "%d %lf %lf %lf %lf",
               &indiriciler[indiriciCount].id, &indiriciler[indiriciCount].x1,
               &indiriciler[indiriciCount].y1, &indiriciler[indiriciCount].x2, &indiriciler[indiriciCount].y2);

        indiriciCount++;
        lineNumber++;

    }

    //printf("<<<<1<<<<%d \n\n", lineNumber);

    lineNumber = 0;

    fgets(line, line_size, filePointer);
    while (fgets(line, line_size, filePointer) != NULL)  {
        //printf("%s", line);
        sscanf(line, "%s",temp);
        if( strcmp(temp,"END") == 0)
            break;

        sscanf(line, "%d %d %lf %lf %lf %lf",
               &musteriler[musteriCount].id, &musteriler[musteriCount].tip, &musteriler[musteriCount].x1,
               &musteriler[musteriCount].y1, &musteriler[musteriCount].x2, &musteriler[musteriCount].y2);

        musteriCount++;
        lineNumber++;
    }

    //printf("<<<<2 %d\n\n", lineNumber);
    lineNumber = 0;


    fgets(line, line_size, filePointer);
    while (fgets(line, line_size, filePointer) != NULL)  {
        //printf("%s", line);
        sscanf(line, "%s",temp);
        if( strcmp(temp,"END") == 0)
            break;

        sscanf(line, "%d %lf %lf %lf %lf",
               &hatlar[hatCount].id, &hatlar[hatCount].x1,
               &hatlar[hatCount].y1, &hatlar[hatCount].x2, &hatlar[hatCount].y2);

        hatCount++;
        lineNumber++;
    }


    //rewind(filePointer);  //dosyanin basina git


    fclose(filePointer);
}

void print_Test_System_file(struct indirici indiriciler[MAX_RECORD_COUNT],                                          //bütün bilgileri konsola yazdýrma fonksyonu.
                            struct musteri musteriler[MAX_RECORD_COUNT], struct hat hatlar[MAX_RECORD_COUNT] ){

    printf("\n\n\tTEXT SYSTEM DOSYASI BILGILERI\n\n");

    for( i = 0; i < indiriciCount; i++){
        printf("%d \t %lf \t %lf \t %lf \t %lf\n",
               indiriciler[i].id, indiriciler[i].x1,
               indiriciler[i].y1, indiriciler[i].x2, indiriciler[i].y2);
    }
    printf("\n\n");

    for( i = 0; i < musteriCount; i++){
        printf("%d \t %lf \t %lf \t %lf \t %lf\n",
               musteriler[i].id, musteriler[i].x1,
               musteriler[i].y1, musteriler[i].x2, musteriler[i].y2);
    }

    printf("\n\n");
    for( i = 0; i < hatCount; i++){
        printf("%d \t %lf \t %lf \t %lf \t %lf\n",
               hatlar[i].id, hatlar[i].x1,
               hatlar[i].y1, hatlar[i].x2, hatlar[i].y2);
    }

}



void indiriciMerkezBilgileri(struct indirici indiriciler[MAX_RECORD_COUNT]){

    printf("\tINDIRICI MERKEZ BILGILERI\n");
    printf("INDIRICI_ID\tX1\t\tY1\t\tX2\t\tY2\n");
    for( i = 0; i < indiriciCount; i++){
        printf("%d \t\t %lf \t %lf \t %lf \t %lf\n",
               indiriciler[i].id, indiriciler[i].x1,
               indiriciler[i].y1, indiriciler[i].x2, indiriciler[i].y2);
    }
    printf("\n\n");

}



void musteriBilgileri(struct musteri musteriler[MAX_RECORD_COUNT]){

    printf("\tMUSTERI BILGILERI\n");
    printf("MUSTERI_ID\tX1\t\tY1\t\tX2\t\tY2\n");
    for( i = 0; i < musteriCount; i++){
        printf("%d \t %d \t %lf \t %lf \t %lf \t %lf\n",
               musteriler[i].id, musteriler[i].tip,  musteriler[i].x1,
               musteriler[i].y1, musteriler[i].x2, musteriler[i].y2);
    }

    printf("\n\n");

}


void hatBilgileri(struct hat hatlar[MAX_RECORD_COUNT]){

    printf("\tHAT BILGILERI\n");
    printf("HAT_ID\tX1\t\tY1\t\tX2\t\tY2\n");
    for( i = 0; i < hatCount; i++){
        printf("%d \t %lf \t %lf \t %lf \t %lf\n",
               hatlar[i].id, hatlar[i].x1,
               hatlar[i].y1, hatlar[i].x2, hatlar[i].y2);
    }
    printf("\n\n");

}

double ikiHatArasindakiUzaklik(double x1, double x2, double y1, double y2){

   // printf("%lf %lf %lf %lf  **** \n", x1, y1, x2,y2);
    return (double) sqrt( pow( (y2-y1),2) + pow((x2-x1),2)) ;
}


double toplamHatUzunlugu(struct hat hatlar[MAX_RECORD_COUNT]){
    double  toplamHatUzunlugu = 0;

    printf("\nToplam hat sayisi : %d\n", hatCount);

    for( i = 0; i < hatCount; i++){
        toplamHatUzunlugu += ikiHatArasindakiUzaklik(hatlar[i].x1,hatlar[i].x2,hatlar[i].y1,hatlar[i].y2);
        //printf("\n%d::: : %lf\n", i, toplamHatUzunlugu);
    }

    return toplamHatUzunlugu;
}

void kopukHatlar(struct hat hatlar[MAX_RECORD_COUNT]){ //kopuk hat algoritmasýnýn yanlýþ olmasý nedeniyle kopuk olmayan hatlarý bulan algoritma.
	double X1, X2, Y1, Y2;
    int kopukOlmayanHatlar[MAX_RECORD_COUNT];
    int count = 0;
    int kopukSayisi = 0;
    int kopukVar = 0;


	for(i=0; i < hatCount; i++){
        X1 = hatlar[i].x1;
        Y1 = hatlar[i].y1;
        X2 = hatlar[i].x2;
        Y2 = hatlar[i].y2;
        
        for(j=0; j < hatCount; j++){
            if(i!=j){
                if( (hatlar[j].x1== X1  && hatlar[j].y1 == Y1 ) || (hatlar[j].x2== X1  && hatlar[j].y2 == Y1) ) {
                    
                    //i = hatCount; 
                    kopukOlmayanHatlar[count++] = hatlar[i].id; 
                    break ; 
                }
                if( (hatlar[j].x1== X2  && hatlar[j].y1 == Y2 ) || (hatlar[j].x2== X2  && hatlar[j].y2 == Y2) ) {
                    kopukOlmayanHatlar[count++] = hatlar[i].id; 
                    //i = hatCount;  
                    break ; 
                }
                
            }
        }
	}
    
    printf("Kopuk OLMAYAN hatlar ID :  ");

    for(i=0; i < count; i++){
        printf("%d  ",kopukOlmayanHatlar[i]);
    }

    for(i=0; i < hatCount; i++){
        kopukVar = 0;
        for(j=0; j < count; j++){
            if(kopukOlmayanHatlar[j] == hatlar[i].id){
                kopukVar = 1;
            }
        }
        if(kopukVar != 1){
            printf("\nKOPUK  Hat ID :  %d\n", hatlar[i].id);            
            kopukSayisi++;
            kopukVar = 0;
        } else {
               

        }
    }


    printf("\nKopuk hat sayisi : %d \n", kopukSayisi);

			
}



void hatGuzergah(struct hat hatlar[MAX_RECORD_COUNT]){  //hat güzergahýný kordinat yardýmýyla bulan fonksyon.
	int a;
	printf("hangi hattin guzeraghini istersiniz?");
	scanf("%d",&a);
	for(i=0;i<hatCount;i++){
		if(hatlar[i].x2==hatlar[i+1].x1){
			printf(">> %d\n",hatlar[i].id);
			
		}
		else {
			break;
		}
	}		
}



void toplamMusteriSayisi(struct musteri musteriler[MAX_RECORD_COUNT]){

    int mesken=0, ticari=0, sanayi=0;
    
    printf("\nToplam musteri sayisi : %d\n", musteriCount);



    for( i = 0; i < musteriCount; i++){
        if(musteriler[i].tip == 1)
            mesken++;
        if(musteriler[i].tip == 2)
            ticari++;
        if(musteriler[i].tip == 3)
            sanayi++;
    }

    printf("Mesken sayisi : %d\n", mesken);
    printf("Ticari sayisi : %d\n", ticari);
    printf("Sanayi sayisi : %d\n", sanayi);

}


void hatBilgi(int id, struct hat hatlar[MAX_RECORD_COUNT]){   // hat bilgisini konsola yazdýrma.
 
    for( i = 0; i < hatCount; i++){
        if(hatlar[i].id == id){

            printf("\nHat %d, (%lf, \t %lf, \t %lf, \t %lf)\n\n",
                hatlar[i].id, hatlar[i].x1, hatlar[i].y1, hatlar[i].x2, hatlar[i].y2);
        }  
    }

}


void musteriBilgi(int id, struct musteri musteriler[MAX_RECORD_COUNT]){  //müþetri bilgileri ile tipini konsola yazdýrma.
 
    for( i = 0; i < musteriCount; i++){
        if(musteriler[i].id == id){

            printf("Musteri %d, ", musteriler[i].id);
            if(musteriler[i].tip == 1)
                printf("Mesken");
            if(musteriler[i].tip == 2)
                printf("Ticari");
            if(musteriler[i].tip == 3)
                printf("Sanayi");
            
             printf(", (%lf, \t %lf, \t %lf, \t %lf)\n\n",
                musteriler[i].x1, musteriler[i].y1, musteriler[i].x2, musteriler[i].y2);
        }  
    }

}



void indiriciBilgi(int id, struct indirici indiriciler[MAX_RECORD_COUNT]){    //structa tutulan deðeri konsolla yazdýrma.
 
    for( i = 0; i < indiriciCount; i++){
        if(indiriciler[i].id == id){

            printf("\nIndirici %d, (%lf, \t%lf, \t %lf, \t %lf)\n\n",
                indiriciler[i].id, indiriciler[i].x1, indiriciler[i].y1, indiriciler[i].x2, indiriciler[i].y2);
        }  
    }

}




void kopukHatlariListele(struct hat hatlar[MAX_RECORD_COUNT]){   //kopuk hat algoritmasýnýn yanlýþ olmasý sebebi ile kopuk olmayan hatlarý metin belgesine yazdýrma.

    FILE* filePointer;

    filePointer = fopen("Kopuk_hat_listesi.txt", "w");


	double X1, X2, Y1, Y2;
    int kopukOlmayanHatlar[MAX_RECORD_COUNT];
    int count = 0;
    int kopukSayisi = 0;
    int kopukVar = 0;


	for(i=0; i < hatCount; i++){
        X1 = hatlar[i].x1;
        Y1 = hatlar[i].y1;
        X2 = hatlar[i].x2;
        Y2 = hatlar[i].y2;
        
        for(j=0; j < hatCount; j++){
            if(i!=j){
                if( (hatlar[j].x1== X1  && hatlar[j].y1 == Y1 ) || (hatlar[j].x2== X1  && hatlar[j].y2 == Y1) ) {
                    
                    //i = hatCount; 
                    kopukOlmayanHatlar[count++] = hatlar[i].id; 
                    break ; 
                }
                if( (hatlar[j].x1== X2  && hatlar[j].y1 == Y2 ) || (hatlar[j].x2== X2  && hatlar[j].y2 == Y2) ) {
                    kopukOlmayanHatlar[count++] = hatlar[i].id; 
                    //i = hatCount;  
                    break ; 
                }
                
            }
        }
	}
    
    fprintf(filePointer, "Kopuk OLMAYAN hatlar :  ");

    for(i=0; i < count; i++){
        fprintf(filePointer, "%d  ",kopukOlmayanHatlar[i]);
    }

    for(i=0; i < hatCount; i++){
        kopukVar = 0;
        for(j=0; j < count; j++){
            if(kopukOlmayanHatlar[j] == hatlar[i].id){
                kopukVar = 1;
            }
        }
        if(kopukVar != 1){
            fprintf(filePointer, "\nKopuk Hat ID :  %d\n", hatlar[i].id);            
            kopukSayisi++;
            kopukVar = 0;
        } else {
               

        }
    }


    fprintf(filePointer, "\nKopuk hat sayisi : %d \n", kopukSayisi);
}


    
void musteriKusUcusuMesafe(struct musteri musteriler[MAX_RECORD_COUNT],struct indirici indiriciler[MAX_RECORD_COUNT] ){  //kuþ ucusu mesafe yaazdýran fonkson.
    int x1, x2, y1,y2;
    FILE* filePointer;

    filePointer = fopen("Musteri_kus_ucusu_mesafe.txt", "w");


   
    fprintf(filePointer, "\n\nID\t TIP\t KUS_UCUSU_MESAFE\n");

    for( i = 0; i < musteriCount; i++){
        fprintf(filePointer, "%d\t ", musteriler[i].id);
        if(musteriler[i].tip == 1)
            fprintf(filePointer, "Mesken\t ");
        if(musteriler[i].tip == 2)
            fprintf(filePointer, "Ticari\t ");
        if(musteriler[i].tip == 3)
            fprintf(filePointer, "Sanayi\t ");
       
       
        fprintf(filePointer, "%lf\n", 
            ikiHatArasindakiUzaklik(musteriler[i].x1, indiriciler[0].x2, musteriler[i].y1, indiriciler[0].y2));
       
    }
}


void musteriHatUzunlugu(struct musteri musteriler[MAX_RECORD_COUNT],struct indirici indiriciler[MAX_RECORD_COUNT], // struct yaardýmý ile alýnan bilgileri txt dosyasýna geçiren fonksyon.
    struct hat hatlar[MAX_RECORD_COUNT]){

    double toplamMesafe = 0;
    FILE* filePointer;
    int no = 0;
    int k;
    filePointer = fopen("Musteri_hat_uzunlugu.txt", "w");


   
    fprintf(filePointer, "\n\nID\t TIP\t HAT_UZUNKUGU\t KUS_UCUSU_MESAFE\t TOP_HAT_SAYISI\n");

    for( i = 0; i < musteriCount; i++){
        fprintf(filePointer, "%d\t ", musteriler[i].id);
        if(musteriler[i].tip == 1)
            fprintf(filePointer, "Mesken\t ");
        if(musteriler[i].tip == 2)
            fprintf(filePointer, "Ticari\t ");
        if(musteriler[i].tip == 3)
            fprintf(filePointer, "Sanayi\t ");

         for(  j = 0; j < hatCount; j++){
            if(musteriler[i].x1 == hatlar[j].x1 && musteriler[i].y1 == hatlar[j].y1 )
                no = j;
            if(musteriler[i].x2 == hatlar[j].x1 && musteriler[i].y2 == hatlar[j].y1 )
                no = j;
            if(musteriler[i].x1 == hatlar[j].x2 && musteriler[i].y1 == hatlar[j].y2 )
                no = j;
            if(musteriler[i].x2 == hatlar[j].x2 && musteriler[i].y2 == hatlar[j].y2 )
                no = j;
         
         }
         for(  k = i; k < no; k++){

             toplamMesafe += ikiHatArasindakiUzaklik(hatlar[k].x1, hatlar[k].x2, hatlar[k].y2, hatlar[k].y2);
         }


        fprintf(filePointer, "%lf\t %lf\t\t", toplamMesafe,
            ikiHatArasindakiUzaklik(musteriler[i].x1, indiriciler[0].x1, musteriler[i].y1, indiriciler[0].y1));
       
        fprintf(filePointer, "%d\t\n", no+1);
        no = 0;
        toplamMesafe = 0;
    }

}


void musteriHatGuzergahi(int musteriId, struct musteri musteriler[MAX_RECORD_COUNT],   //structan veri alýnýp hat güzergahý oluþturmak için yapýlan fonksyon.
                            struct indirici indiriciler[MAX_RECORD_COUNT], 
                             struct hat hatlar[MAX_RECORD_COUNT]){


    FILE* filePointer;
    int no = 0;
    int musteriNo = 0;
    

    if(musteriId == 123)
        filePointer = fopen("Mesken_123_hat_guzergahi.txt", "w");
    
    if(musteriId == 101)
        filePointer = fopen("Ticari_101_hat_guzergahi.txt", "w");
    
    if(musteriId == 55)
        filePointer = fopen("Mesken_55_hat_guzergahi.txt", "w");
    


   
    fprintf(filePointer, "\n\nIndirici Merkez %d\n", indiriciler[0].id);

    
    for( i = 0; i < musteriCount; i++){
        if(musteriler[i].id == musteriId){
            musteriNo = i;
            for(  j = 0; j < hatCount; j++){
                if(musteriler[i].x1 == hatlar[j].x1 && musteriler[i].y1 == hatlar[j].y1 )
                    no = j;
                if(musteriler[i].x2 == hatlar[j].x1 && musteriler[i].y2 == hatlar[j].y1 )
                    no = j;
                if(musteriler[i].x1 == hatlar[j].x2 && musteriler[i].y1 == hatlar[j].y2 )
                    no = j;
                if(musteriler[i].x2 == hatlar[j].x2 && musteriler[i].y2 == hatlar[j].y2 )
                    no = j;
            
            }
        }
    }

    if(no == 0)
        no = hatCount;
    for( i = 0; i <= no; i++){
        fprintf(filePointer, "%d\n", hatlar[i].id);

    }
    
    fprintf(filePointer, "%d\t", musteriId);
    if(musteriler[musteriNo].tip == 1)
        fprintf(filePointer, "Mesken\t\n ");
    if(musteriler[musteriNo].tip == 2)
        fprintf(filePointer, "Ticari\t\n ");
    if(musteriler[musteriNo].tip == 3)
        fprintf(filePointer, "Sanayi\t\n ");

    no++;
    if(no >= hatCount)
        fprintf(filePointer, "Kopuk HAT %d\n ", no);
}




