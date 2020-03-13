#include <iostream>
#include <fstream>
using namespace std;

/*
author : reza octaviany
github : recchan13
*/

//kamus
int angka[9][9];
bool isChange[9][9];
struct awalAkhir{
	int line;
	int row;
};
	awalAkhir index[2]; 	//berisi indeks dari letak 0 paling awal dan yang paling akhir

//subprogram
void loadData(int soal);
void game(int *baris, int *kolom);
bool cekBasKom(int baris,int kolom);
bool cekKotak(int baris,int kolom);
void saveFile(int simpan);

//main program
int main (){
	int i,j,round;
	
	for (round=0;round<3;round++){
		loadData(round); 	//meload data dari file eksternal untuk di solve
	
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				cout<<angka[i][j]<<" "; //cout angka yang ada dalam matrix
			}cout<<"\n";
		}cout<<"\n";
		
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				game(&i,&j); 	//masuk ke game untuk setiap angka nya
			}
		}
	
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				cout<<angka[i][j]<<" "; //cout angka yang ada dalam matrix
			}cout<<"\n";
		}cout<<"\n";
	
		saveFile(round); //untuk save file yang sudah solved
	}
}

//sub program
void loadData(int soal){
	ifstream load;			//variable untuk load data soal
	int i,j;
	bool awal=false;		//untuk nandain dimana letak 0 yang paling awal sbg patokan jika masalah tidak bisa solve
	
	if (soal==0){
		load.open("soal1.txt");	//load data soal dari file external
	}else if(soal==1){
		load.open("soal2.txt");	//load data soal dari file external
	}else if(soal==2){
		load.open("soal3.txt");	//load data soal dari file external
	}
	
	
	while (!load.eof()){	//ketika file belum selesai
		for(i=0;i<9;i++){	//cek matriks 9x9
			for(j=0;j<9;j++){
				load>>angka[i][j];	//load angka
				
				if (angka[i][j]==0){ 		//untuk nandain apakah angka skrng nol bukan
					isChange[i][j]=true; 	//jika nol maka true
					if(!awal){				//jika awal tidak true (*false) maka masuk sini
						index[0].line=i;	//simpan index baris ke dalam array line
						index[0].row=j;		//simpan index kolom ke dalam array row
						awal=true;			//maka awal=true
					}
					index[1].line=i;		//simpan index baris paling akhir yang nilainya 0 dalam array line
					index[1].row=j;			//simpan index kolom paling akhir yang nilainya 0 dalam array row
				}else{
					isChange[i][j]=false; //jika bukan nol maka false
				}
			}
		}
	}
}

void game(int *baris, int *kolom){
	if(isChange[*baris][*kolom]==true){ 	//apakah baris itu bisa di isi? jika bisa maka
		if (angka[*baris][*kolom]<9){		//apakah angkanya kurang dari 9
			angka[*baris][*kolom]++;		//jika ya maka angkanya +1
		}else{
			angka[*baris][*kolom]=0;		//jika tidak 9 maka nilai nya jadi 0 lagi
            do{
                if(*kolom==0){				//jika kolomnya udh yang paling awal				
                    *baris-=1;				//maka barisnya naek ke atas
                    *kolom=8;				//dan kolom nya paling kanan
                }else{						//jika gak
			        *kolom=*kolom-1;		//cukup kolomnya yang mundur
                }
            }while(!isChange[*baris][*kolom]);
            
            if(*kolom==0){				//jika kolomnya udh yang paling awal
                *baris-=1;				//maka barisnya naek ke atas
                *kolom=8;				//dan kolom nya paling kanan
            }else{
		        *kolom=*kolom-1;		//cukup kolomnya yang mundur
            }
		}
		
		if(!cekBasKom(*baris,*kolom) || !cekKotak(*baris,*kolom)){ // cek apakah bisa di isi dengan angka tsb
			game (baris,kolom);
		}
	}
}

bool cekBasKom(int baris,int kolom){
	for (int i=0;i<9;i++){
		if(i!=baris){
			if (angka[baris][kolom]==angka[i][kolom]){		//cek dlu kebawah
				return false;
			}
		}
		if(i!=kolom){
			if (angka[baris][kolom]==angka[baris][i]){		//cek dlu kesamping
				return false;
			}
		}
	}return true;
}

bool cekKotak(int baris,int kolom){
	int awalBaris,akhirBaris;
	int awalKolom,akhirKolom;
	
	if (baris/3==0){	//cek di kotak mana cell nya berada
		awalBaris=0;
		akhirBaris=2;
	}else if (baris/3==1){
		awalBaris=3;
		akhirBaris=5;
	}else{
		awalBaris=6;
		akhirBaris=8;
	}
	
	if (kolom/3==0){
		awalKolom=0;
		akhirKolom=2;
	}else if (kolom/3==1){
		awalKolom=3;
		akhirKolom=5;
	}else{
		awalKolom=6;
		akhirKolom=8;
	}
	
	for (int i=awalBaris;i<=akhirBaris;i++){			//untuk ngecek kotak matrix 3x3
		for (int j=awalKolom;j<=akhirKolom;j++){
			if(i!=baris && j!=kolom){					//kalo kolom dan baris nya sama dengan cell sekarang maka pengecekan di skip
				if (angka[baris][kolom]==angka[i][j]){	//apakah angka yg terdapat pada cell tsb = angka di cell lain dlm kotak yg sama
					return false;
				}
			}
		}
	}return true;
}

void saveFile(int simpan){		//untuk save file 
	ofstream save;
			
	if (simpan==0){
		save.open("answer1.txt");
	}else if(simpan==1){
		save.open("answer2.txt");
	}else if(simpan==2){
		save.open("answer3.txt");
	}
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			save<<angka[i][j]<<" ";
		}save<<"\n";
	}
}
