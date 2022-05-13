#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct huffman{
    char deger;
    int tekrar;
    int toplandiMi;
    struct huffman* next;
    struct huffman* left;
    struct huffman* right;
};

struct huffman* start=NULL;
struct huffman* temp;
struct huffman* temp2;

struct huffman* dugumOlustur(char harf, int T){
    struct huffman* yeni=(struct huffman*)malloc(sizeof(struct huffman));
    yeni->deger=harf;
    yeni->tekrar=T;
    yeni->toplandiMi=0;
    yeni->next=NULL;
    yeni->left=NULL;
    yeni->right=NULL;
    return yeni;
}
/*struct huffman* toplamDugumOlustur(struct huffman* birinci, struct huffman* ikinci, int T){
    struct huffman* yeni=(struct huffman*)malloc(sizeof(struct huffman));
    yeni->tekrar=T;
    yeni->toplandiMi=0;
    yeni->deger=NULL;
    yeni->next=NULL;
    yeni->left=birinci;
    yeni->right=ikinci;
    return yeni;
}*/

void ekle(char harf, int T){
    struct huffman* eklenecek = dugumOlustur(harf, T);

    if(start==NULL){
        start=eklenecek;
    }
    else{
        if(T<start->tekrar){
            eklenecek->next=start;
            start=eklenecek;
        }
        else{
            temp=start;
            while(temp->next!=NULL){
                if(T>=(temp->tekrar)){
                    temp2=temp;
                }

                temp=temp->next;
            }
            eklenecek->next=temp2->next;
            temp2->next=eklenecek;
            if(T>=(temp->tekrar)){
                temp->next=eklenecek;
                eklenecek->next=NULL;
            }
        }
    }
}
/*void toplamEkle(struct huffman* birinci, struct huffman* ikinci, int T){

    struct huffman* eklenecek = toplamDugumOlustur(birinci,ikinci,T);

    if(start==NULL){
        start=eklenecek;
    }
    else{
        if(T<start->tekrar){
            eklenecek->next=start;
            start=eklenecek;
        }
        else{
            temp=start;
            while(temp->next!=NULL){
                if(T>=(temp->tekrar)){
                    temp2=temp;
                }

                temp=temp->next;
            }
            eklenecek->next=temp2->next;
            temp2->next=eklenecek;
            if(T>=(temp->tekrar)){
                temp->next=eklenecek;
                eklenecek->next=NULL;
            }
        }
    }
}*/
void yazdir(){
    temp=start;
    while(temp!=NULL){
        printf("%c-->%d\n",temp->deger,temp->tekrar);
        temp=temp->next;
    }
}
/*int say(){
    int sayac=0;
    temp=start;
    while(temp!=NULL){
       sayac++;
        temp=temp->next;
    }
    return say;
}*/
/*void huffmanKodlama(int S){

    int sayac=0;
    int sayacTut=0;
    int toplam;

   for(int p=S;p<2;p--){
        temp=start;
        while(temp->next!=NULL){

                if(temp->toplandiMi==0 && temp->next->toplandiMi==0){
                    temp2=temp->next;
                    toplam=temp->tekrar+temp2->tekrar;

                    toplamEkle(temp,temp2,toplam);

                    temp->toplandiMi=1;

                    temp2->toplandiMi=1;

                }
                if(temp->toplandiMi==0){
                    sayac++;
                }


            temp=temp->next;
        }
        sayacTut=sayac;
        sayac=0;
    }


}*/

int main()
{
    FILE *dosya = fopen("metin.txt","r");

   if(dosya==NULL){
        printf("Dosya bulunamadi.. \n");
        return 0;
    }

    FILE *output = fopen("output.txt","w");

    if(output==NULL){
        printf("Dosya acilamadi.");
    }

    char *sag;
    sag=(char*)malloc(sizeof(char));

    char *sol;
    sol=(char*)malloc(sizeof(char));

    char *huffman;
    huffman=(char*)malloc(sizeof(char));
    int huffmanTut=1;

    char c;
    int N=1;
    int I=0;

     while(!feof(dosya)){
        c=fgetc(dosya);
        sag=(char*)realloc(sag,N*sizeof(char));
        sag[I]=c;
        I++;
        N++;
    }
    fclose(dosya);


    int A=1;
    int J=0;
    int ilk=0;
    int eslesme=0;
    int benzerlik=0;
    int uzaklik;
    int yok=0;
    int tutB;
    int u=0;

    printf("lz77 algoritmasi ciktisi:\n");
    int k=0;
    while(k<(I-1)){

        if(ilk==0){
            printf("[0,0,C(%c)]\n",sag[k]);
            fprintf(output,"[0,0,C(%c)]\n",sag[k]);
            huffman=(char*)realloc(huffman,huffmanTut*sizeof(char));
            huffman[u]=sag[k];
            ilk++;
            huffmanTut++;
            u++;
        }

        else{

            for(int x=0;x<J;x++){
                if(sol[x]==sag[k] && eslesme==0){
                    yok++;
                    eslesme++;
                    uzaklik=J-x;
                    int a=x;
                    int b=k;
                    while(sol[a]==sag[b]){
                        benzerlik++;
                        a++;
                        b++;
                    }
                    tutB=benzerlik;
                    printf("[%d,%d,C(%c)]\n",uzaklik,benzerlik,sag[k+benzerlik]);
                    fprintf(output,"[%d,%d,C(%c)]\n",uzaklik,benzerlik,sag[k+benzerlik]);
                    huffman=(char*)realloc(huffman,huffmanTut*sizeof(char));
                    huffman[u]=sag[k+benzerlik];
                    u++;
                    huffmanTut++;

                }
            }

            if(yok==0){
                printf("[0,0,C(%c)]\n",sag[k]);
                fprintf(output,"[0,0,C(%c)]\n",sag[k]);
                huffman=(char*)realloc(huffman,huffmanTut*sizeof(char));
                huffman[u]=sag[k];
                u++;
                huffmanTut++;

            }
            benzerlik=0;
            eslesme=0;
            yok=0;

        }

        if(tutB>0){
            A=A+tutB;
            sol=(char*)realloc(sol,A*sizeof(char));
            int d=k;
            for(int z=0;z<tutB+1;z++){
            sol[J]=sag[d];
            J++;
            d++;
            }
            A++;
            k+=tutB+1;
        }
        else{
            sol=(char*)realloc(sol,A*sizeof(char));
            sol[J]=sag[k];
            J++;
            A++;
            k++;
        }

        tutB=0;


    }

    printf("\n\nKodun sikistirilmis hali: \n");
    fprintf(output,"\n\nKodun sikistirilmis hali: \n");

    for(int a=0;a<u;a++){
        printf("%c", huffman[a]);
        fprintf(output,"%c", huffman[a]);
    }
    printf("\n\n");

    free(sag);
    free(sol);

    int m,n;
    int harfinTekrari=0;
    int karakterSayisi=strlen(huffman)-1;

    printf("sikistirilmis haldeki her karakterin tekrar sayisi:\n");
    for(m=0;m<karakterSayisi;m++){
        harfinTekrari++;
        for(n=m+1;n<karakterSayisi;n++){
            if(huffman[m]==huffman[n] && huffman[n]!=0){
                harfinTekrari++;
                huffman[n]=0;
            }
        }
        if(huffman[m]!=0){
            printf("%c:%d\n",huffman[m],harfinTekrari);
            char H= huffman[m];
            ekle(H,harfinTekrari);
        }

        harfinTekrari=0;
    }

    printf("\n\n");

    printf("sikistirilmis haldeki her karakterin tekrar sayisinin siralanmis hali:\n");
    yazdir();

    fclose(output);


    return 0;
}
