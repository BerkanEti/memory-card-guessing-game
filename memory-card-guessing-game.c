#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32            //sleep() icin kutuphaneler
#include <Windows.h>
#else
#include <unistd.h>
#endif  

#ifdef _WIN32  // windows icin terminal ekrani temizleme
	void clearAll(){
		system("cls");
	}
#endif

#ifdef __APPLE__ // mac icin terminal ekrani temizleme
	void clearAll(){
		system("clear");
	}
#endif
void mode(int boardSize , int memorySize,int timeControl){

	int i,j,k,randomArray[8][8],randomRow,randomColumn,control=0,memory[32],memoryCounter=0,insertedIndex1,insertedIndex2,userPoint=0,userTotal=0,computerPoint=0,computerTotal=0,userRow1,userColumn1,userRow2,userColumn2,computerRow1=0,computerColumn1=0,computerRow2=0,computerColumn2=0,sameGuess=0,correctGuess=0,differentGuess,turn=0;  
	char gameBoard[8][8] , isComma;
	for(i=0;i<boardSize;i++){     //oyun tahtasini * ile doldurma ve rastgele olusturulacak arrayi sifirlanmistir.
		for(j=0;j<boardSize;j++){
		randomArray[i][j]=0;
		gameBoard[i][j] = '*' ;
		}
	}
	for(i=0;i<2*memorySize;i++)memory[i] = 0; // hafiza arrayini sifirlanmistir.
	
	i=1;
	while(i<=boardSize*boardSize/2){  // rastgele satir ve sutunlara i degerini atayarak rasgele bir dizi olusturulmustur.
		randomRow = rand()%boardSize;
		randomColumn = rand()%boardSize;
		if(control ==2){
			control=0;
			i++;
		}
		if(randomArray[randomRow][randomColumn] == 0){
			randomArray[randomRow][randomColumn] = i ;
			control++; 
		}
	}
	
	for(i=0;i<boardSize;i++){  // oyun baslamadan once ekranda dogru cevaplar belirli bir sure gosterilmistir.
		printf("\n");
		for(j=0;j<boardSize;j++){
			if(randomArray[i][j]<10)printf("%c ",randomArray[i][j] - 1 +'1');
			else printf("%c ",randomArray[i][j]-10 +'A');
			
		}
	}
	printf("Kartlar Kapaniyor..."); // oyun moduna gore gosterilme suresi düzenlenmistir.
	for(i=0;i<=timeControl;i++){
		sleep(1);
		printf("..%d",i);
	}
	clearAll();
	 
	while(userPoint!=boardSize*boardSize/4+1 && computerPoint!=boardSize*boardSize/4+1 && (userPoint!=boardSize*boardSize/4 || computerPoint!=boardSize*boardSize/4) ){	//beraberlik veya kazanma disinda donguye girer.
		
		printf("\n");
		printf("Tahminlerinizi satir,sutun seklinde giriniz. ornek:1,4\nSen:%d   Bilgisayar:%d",userPoint,computerPoint); // 
		
			
		for(i=0;i<boardSize+1;i++){ //oyun tahtasi
			printf("\n");
			for(k=0;k<4*boardSize+4;k++){
				printf("-");
			}
			printf("\n");
			for(j=0;j<boardSize+1;j++){
				if(i==0 && j==0)printf(" / |");
				else if(i==0)printf(" %d |",j);
				else if(j==0)printf(" %d |",i);
				else printf(" %c |",gameBoard[i-1][j-1]);
			}
		}
		
		if(turn==0){ // kullanicinin sirasi
			userTotal++;
			printf("\n 1.Tahmininiz:");
			scanf("%d%c%d",&userRow1,&isComma,&userColumn1);
			if(gameBoard[userRow1-1][userColumn1-1] != '*' || isComma != ',' ){ // uygun girdi alinmistir.(virgüllü ve daha once acilmamis bir kart)
				sameGuess=1;
				while(sameGuess==1){
					printf("\n Lutfen farkli bir 1. tahmin yapiniz:");
					scanf("%d%c%d",&userRow1,&isComma,&userColumn1);
					if(gameBoard[userRow1-1][userColumn1-1] == '*' && isComma == ',' )sameGuess=0;
				}
			}
			//integer dizideki degere karsilik gelen char ifade(harf veya rakam) kontrol edilerek degistirilmistir.
			if(randomArray[userRow1-1][userColumn1-1] <10)gameBoard[userRow1-1][userColumn1-1] = randomArray[userRow1-1][userColumn1-1] - 1 + '1' ;
			else gameBoard[userRow1-1][userColumn1-1] = randomArray[userRow1-1][userColumn1-1] - 10 + 'A';	
			
			for(i=0;i<boardSize+1;i++){ //oyun tahtasi
			printf("\n");
			for(k=0;k<4*boardSize+4;k++){
				printf("-");
			}
			printf("\n");
			for(j=0;j<boardSize+1;j++){
				if(i==0 && j==0)printf(" / |");
				else if(i==0)printf(" %d |",j);
				else if(j==0)printf(" %d |",i);
				else printf(" %c |",gameBoard[i-1][j-1]);
				}
			}
			
			printf("\n 2.Tahmininiz:");
			scanf("%d%c%d",&userRow2,&isComma,&userColumn2);
			if((userRow1 == userRow2 && userColumn1 == userColumn2)||(gameBoard[userRow2-1][userColumn2-1] != '*') || isComma != ','){
				sameGuess=1;
				while(sameGuess==1){
					printf("\n Lutfen farkli bir 2. tahmin yapiniz:");
					scanf("%d%c%d",&userRow2,&isComma,&userColumn2);
					if(userRow1 == userRow2 && userColumn1-userColumn2||(gameBoard[userRow2-1][userColumn2-1] == '*')&& isComma == ',')sameGuess=0;
				}
			}
			if(randomArray[userRow2-1][userColumn2-1] <10)gameBoard[userRow2-1][userColumn2-1] = randomArray[userRow2-1][userColumn2-1] - 1 + '1' ;
			else gameBoard[userRow2-1][userColumn2-1] = randomArray[userRow2-1][userColumn2-1] - 10 + 'A';
			printf("\n\n");
			for(i=0;i<boardSize+1;i++){
			printf("\n");
			for(k=0;k<4*boardSize+4;k++){
				printf("-");
			}
			printf("\n");
			for(j=0;j<boardSize+1;j++){
				if(i==0 && j==0)printf(" / |");
				else if(i==0)printf(" %d |",j);
				else if(j==0)printf(" %d |",i);
				else printf(" %c |",gameBoard[i-1][j-1]);
			}
			}
			if(randomArray[userRow1-1][userColumn1-1] == randomArray[userRow2-1][userColumn2-1]){ // dogru cevap durumu
				printf("\n\nTebrikler Dogru Cevap !");
				gameBoard[userRow1-1][userColumn1-1] = '-';
				gameBoard[userRow2-1][userColumn2-1] = '-';
				userPoint++;
				control=0;
				while(control<2*memorySize){ // eger dogru cevap hafýzada da bulunuyorsa hafizadaki deger sifirlanmistir.
					if(userRow1==memory[control] && userColumn1==memory[control+1]){
						memory[control] =0;
						memory[control+1] =0;
					}
					else if(userRow2==memory[control] && userColumn2==memory[control+1]){
						memory[control] =0;
						memory[control+1] =0;
					}
					control=control+2;
				}
				
				
			}
			else{ // yanlis cevap durumu
				turn=1;	// sira bilgisayara gecer.
				printf("\n\n Yanlis Tahmin");
				gameBoard[userRow1-1][userColumn1-1] = '*';
				gameBoard[userRow2-1][userColumn2-1] = '*';
				insertedIndex1=0; //hafizaya aktarilacak 1. ifade
				insertedIndex2=0; // hafizaya aktarilacak 2. ifade
				control=0;
				while(control<2*memorySize && (insertedIndex1==0 || insertedIndex2==0)){ //zaten hafizada bulunuyorsa...
					if(memory[control] == userRow1 && memory[control+1] == userColumn1)insertedIndex1 = 1;
					else if(memory[control] == userRow2 && memory[control+1] == userColumn2)insertedIndex2 = 1;
					control = control + 2;
				}
				while(insertedIndex1 == 0 || insertedIndex2 == 0){ // hafizada bulunmuyorsa...
					if(memoryCounter >=2*memorySize)memoryCounter=0 ; // hafizanin sonuna gelinmisse eklemeler icin basa donulur.
					if(insertedIndex1 == 0 && (memory[memoryCounter]!=userRow1 || memory[memoryCounter+1]!=userColumn1)){ // ilk tahmin eklenir.
						memory[memoryCounter]=userRow1;
						memory[memoryCounter+1]=userColumn1;
						insertedIndex1=1;
					}
					else if(insertedIndex2 == 0 &&  (memory[memoryCounter]!=userRow2 || memory[memoryCounter+1]!=userColumn2)){ // ikinci tahmin eklenir.
						memory[memoryCounter]=userRow2;
						memory[memoryCounter+1]=userColumn2;
						insertedIndex2=1;
					}
					memoryCounter = memoryCounter + 2;
				}
				 
				 
				 
				
				
			}
					
		}
		else{ // bilgisayarin sirasi
			computerTotal++;
			printf("\nBilgisayarin 1. tahmini yapiliyor.. :");
			sleep(1);
			computerRow1=0;
			computerColumn1=0;
			correctGuess=0;
			i=0;
			j=0;
			while(i<2*memorySize && correctGuess==0){ //hafizada eslesen 2 ayni cevap varsa otomatik olarak o cevaplar tahmin olarak alinir.(1 ve 2. tahminler icin)
				j=i+2;
				while(j<2*memorySize && correctGuess==0){
					if(memory[i]!=0 && memory[i+1]!=0 && memory[j+1]!=0 && memory[j]!=0 && randomArray[memory[i]-1][memory[i+1]-1] == randomArray[memory[j]-1][memory[j+1]-1]){
						computerRow1 = memory[i];
						computerColumn1 = memory[i+1];
						computerRow2 = memory[j];
						computerColumn2 = memory[j+1];
						correctGuess=1;					
					}
					j=j+2;
				}
				i=i+2;
			}
			
			if(correctGuess==1){ // eslesen iki cevap bulunma durumu
				printf("\n1. tahmin %d,%d",computerRow1,computerColumn1);
			}
	
			else{ // eger eslesmemisse rastgele tahmin yapilir.
				while(gameBoard[computerRow1-1][computerColumn1-1]!='*'){ // daha once kart acilmissa tekrar edilir.
				computerRow1 = 1 + rand()%boardSize;
				computerColumn1 = 1 + rand()%boardSize;
				}
				printf("\n1. tahmin %d,%d",computerRow1,computerColumn1);
			}
			
			if(randomArray[computerRow1-1][computerColumn1-1] <10)gameBoard[computerRow1-1][computerColumn1-1] = randomArray[computerRow1-1][computerColumn1-1] - 1 + '1' ;
			else gameBoard[computerRow1-1][computerColumn1-1] = randomArray[computerRow1-1][computerColumn1-1] - 10 + 'A';
			
			for(i=0;i<boardSize+1;i++){
			printf("\n");
			for(k=0;k<4*boardSize+4;k++){
				printf("-");
			}
			printf("\n");
			for(j=0;j<boardSize+1;j++){
				if(i==0 && j==0)printf(" / |");
				else if(i==0)printf(" %d |",j);
				else if(j==0)printf(" %d |",i);
				else printf(" %c |",gameBoard[i-1][j-1]);
			}
			}
			printf("\n Bilgisayarin 2. tahmini yapiliyor.. :");
			sleep(2);
			if(correctGuess==0){ // eslesen iki cevap olmama durumu
			control=0;
			sameGuess=0;
			while(sameGuess == 0 && control<2*memorySize){ // rastgele yapilan ilk tahminle eslesen bir cevap aranir ve sameGuess degiskeni ile kontrol edilir.
				if(randomArray[computerRow1-1][computerColumn1-1]==randomArray[memory[control]-1][memory[control+1]-1]&&(memory[control]!=computerRow1||memory[control+1]!=computerColumn1))sameGuess=1;
				else control = control + 2;
				}
			}
		
			if(correctGuess==1){ // eslesen iki cevap
				printf("\n2. tahmin %d,%d",computerRow2,computerColumn2);
			}
			
			else if(sameGuess==1){ // ilk tahmin ile eslesen ikinci cevap
				computerRow2 = memory[control];
				computerColumn2 = memory[control+1];
				printf("\n2. tahmin %d,%d",computerRow2,computerColumn2);
			}
			else{ // ikisi de yoksa rastgele tahmin
				computerRow2=0;
				computerColumn2=0;
				differentGuess=0;
				while(gameBoard[computerRow2-1][computerColumn2-1]!='*' || differentGuess==0){ // olasiligi arttýrmak icin hafizada olmayan bir cevap secilir.(hafizadaki cevabýn olmadýgýna onceki kontrollerde bakildi.)
					computerRow2 = 1 + rand()%boardSize;
					computerColumn2 = 1 + rand()%boardSize;
					if(gameBoard[computerRow2-1][computerColumn2-1]=='*'){
						i=0;
						differentGuess=1;
						while(i<2*memorySize && differentGuess==1){
							if(memory[i]==computerRow2 && memory[i+1]==computerColumn2){
								differentGuess=0;
							}
							i=i+2;
						}
					}
				}
				printf("\n2. tahmin %d,%d",computerRow2,computerColumn2);
			}
			if(randomArray[computerRow2-1][computerColumn2-1] <10)gameBoard[computerRow2-1][computerColumn2-1] = randomArray[computerRow2-1][computerColumn2-1] - 1 + '1' ;
			else gameBoard[computerRow2-1][computerColumn2-1] = randomArray[computerRow2-1][computerColumn2-1] - 10 + 'A';
			for(i=0;i<boardSize+1;i++){
			printf("\n");
			for(k=0;k<4*boardSize+4;k++){
				printf("-");
			}
			printf("\n");
			for(j=0;j<boardSize+1;j++){
				if(i==0 && j==0)printf(" / |");
				else if(i==0)printf(" %d |",j);
				else if(j==0)printf(" %d |",i);
				else printf(" %c |",gameBoard[i-1][j-1]);
			}
			}
			
			
			if(randomArray[computerRow1-1][computerColumn1-1] == randomArray[computerRow2-1][computerColumn2-1]){
				printf("\n\n Dogru Cevap !");
				gameBoard[computerRow1-1][computerColumn1-1] = '-';
				gameBoard[computerRow2-1][computerColumn2-1] = '-';
				computerPoint++;
				control=0;
				while(control<2*memorySize){
					if(computerRow1==memory[control] && computerColumn1==memory[control+1]){
						memory[control] =0;
						memory[control+1] =0;
					}
					else if(computerRow2==memory[control] && computerColumn2==memory[control+1]){
						memory[control] =0;
						memory[control+1] =0;
					}
					control=control+2;
				}
				
			}
			else{
				turn=0;
				printf("\n\n Yanlis Tahmin");
				gameBoard[computerRow1-1][computerColumn1-1] = '*';
				gameBoard[computerRow2-1][computerColumn2-1] = '*';
				insertedIndex1=0;
				insertedIndex2=0;
				control=0;
				while(control<2*memorySize && (insertedIndex1==0 ||insertedIndex2==0)){
					if(memory[control] == computerRow1 && memory[control+1] == computerColumn1)insertedIndex1 = 1;
					else if(memory[control] == computerRow2 && memory[control+1] == computerColumn2)insertedIndex2 = 1;
					control = control + 2;
				}
				while(insertedIndex1 == 0 || insertedIndex2 == 0){
					if(memoryCounter >=2*memorySize)memoryCounter=0 ;
					if(insertedIndex1 == 0 && (memory[memoryCounter]!=computerRow1 || memory[memoryCounter+1]!=computerColumn1)){
						memory[memoryCounter]=computerRow1;
						memory[memoryCounter+1]=computerColumn1;
						insertedIndex1=1;
					}
					else if(insertedIndex2 == 0 && (memory[memoryCounter]!=computerRow2 || memory[memoryCounter+1]!=computerColumn2)){
						memory[memoryCounter]=computerRow2;
						memory[memoryCounter+1]=computerColumn2;
						insertedIndex2=1;
					}
					memoryCounter = memoryCounter + 2;
				}
				}
			
			
		}
		sleep(3);
		clearAll();
		
	}
	
	if(userPoint>=boardSize*boardSize/4+1)printf("\nTEBRIKLER KAZANDINIZ ! TOPLAM TAHMIN SAYISI : %d",userTotal);
	else if(computerPoint>=boardSize*boardSize/4+1)printf("\nMaalesef kaybettiniz :( Bilgisayarin toplam tahmin sayisi %d",computerTotal);
	else printf("\nOyun Berabere ! Toplam Tahmin sayisi : %d",userTotal);
	printf("\n");
	for(i=0;i<4;i++){
		sleep(1);
		printf("..%d",i);
	}
	
	

	

}
		

void newGame(){
	int difficulty; // oyun modu secmek icin kullanicidan girdi alinir.
	printf("\nKolay mod icin 1'e\nNormal mod icin 2'ye\nZor mod icin 3'e bas! ");
	scanf("%d",&difficulty);
	if(difficulty==1){
	printf("\nKartlarda rakamlar kullanilmistir.Tahminlerinizi satir,sutun seklinde giriniz. ornek:1,4 Basarilar !");
	mode(4,2,3);
	}
	else if(difficulty==2){
	printf("\nKartlarda rakamlar ve harfler kullanilmistir.Tahminlerinizi satir,sutun seklinde giriniz. ornek:1,4 Basarilar !");	
	mode(6,6,5);
	}
	else if(difficulty==3){
	printf("\nKartlarda rakamlar ve harfler kullanilmistir.Tahminlerinizi satir,sutun seklinde giriniz. ornek:1,4 Basarilar !");
	mode(8,16,7);
	}
	else{
		printf("\nLutfen gecerli bir numara giriniz.");
		newGame();
	}
}





int main(int argc, char *argv[]) {
	int mod=1;
	srand(time(NULL));
	while(mod==1){ // kullanicidan 1 girildigi surece yeni oyun baslatilir.
	printf("\nOyun modu secmek icin 1'e\nOyunu sonlandirmak icin 0'a bas! ");
	scanf("%d",&mod);
	if(mod==1){
		newGame();
		}
	}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
