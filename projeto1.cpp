//TP3 INF110 by Pedro Santos Teixeira 116224 - Filtros em imagens PNM 08/24
//github: https://github.com/pedrot00 segue la ;)
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <cmath>
using namespace std;

//struct com informacoes do rgb
struct Cor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
//constantes utilizadas no filtro de Prewitt
const int Gx[3][3] = {
    { 1, 0, -1 },
    { 1, 0, -1 },
    { 1, 0, -1 }
};
const int Gy[3][3] = {
    { 1, 1, 1 },
    { 0, 0, 0 },
    { -1, -1, -1 }
};

//escopo de constantes
const int MAX = 500;
const int MAXALTURA = 500;
const int MAXLARGURA = 500;
const int MAX_PIXEL = 255;

//escopo de funcoes
void clearScreen();	//funcao auxiliar de limpar tela em win, ubuntu, mac e linux		 	
void arqRead(const char* arqName, string& tipo, int& largura, int& altura, int& valor, 
    Cor img[MAXALTURA][MAXLARGURA]); //funcao para abertura e leitura da matriz da imagem
void arqRecord(const char* arqNew, string& tipo, int& largura, int& altura, 
    Cor img[MAXALTURA][MAXLARGURA]);//funcao para leitura da nova imagem e fechamento
	
int main(){
    //escopo de variaveis
    char arqName[MAX]; //nome do arquivo original
    char arqNew[MAX];  // nome do arquivo que será criado
    short choice;	
    string tipo;	   
    char comment[200], c; //variaveis auxiliares
    int largura, altura; 
    int valor, fator;   
    Cor img[MAXALTURA][MAXLARGURA]; //declaracao da imagem atraves do tipo Cor (tanto cinza quanto colorida)
    
    //variaveis de fluxo stream
    ifstream arqIn; 
    ofstream arqOut; 
do{

    inicio: 
  	system("color 4F"); //troca a cor da tela de saida no windows;
    do {
        clearScreen();
        cout << "|Bem-vindo(a) aos nossos servicos! Favor inserir o valor desejado:\n\n";

        cout << "|-----------> |MENU| <-----------|\n";
        cout << "|01|-> Clareamento.\n";
        cout << "|02|-> Escurecimento.\n";
        cout << "|03|-> Negativo.\n";
        cout << "|04|-> Espelhar.\n";
        cout << "|05|-> Filtro de Prewitt.\n";
        cout << "|06|-> Contraste.\n";
        cout << "|07|-> Tons de cinza.\n";
        cout << "|08|-> Sair.\n";
        cout << "|--------------------------------|\n";
        cout << "\n|Sua escolha: ";
        cin >> choice;
        
        if(choice < 1 || choice > 8){
     		cout << "|Escolha invalida. Tente novamente.\n\n";
            system("pause");
		}
		
    } while (choice < 1 || choice > 8);
    
	if(choice!=8){
    	cout << "|Insira o nome do arquivo: ";
    	cin >> arqName;
    	cout << "|Insira o nome do novo arquivo: ";
    	cin >> arqNew;	
	}
    clearScreen();
    	
    switch(choice){
    	case 1:
    		do{
    			clearScreen();
        		arqRead(arqName, tipo, largura, altura, valor, img);
        		cout << "|Insira o fator de clareamento da imagem(1-100): ";
        		cin >> fator;
        		
        		if(fator < 1 || fator > 100){
        			cout<< endl <<"|Insira um valor entre 1 e 100."<< endl;
        			system("pause");
				}	
        	} while(fator < 1 || fator > 100); //validacao de fator
        	
        	if (tipo == "P2"){
        		//alterando a imagem para clarear
        		for(int i = 0; i < altura; i++){
        			for(int j = 0; j < largura; j++){
        				valor = (int)img[i][j].r;
        				valor += fator;
        				if(valor > MAX_PIXEL){
        					valor = MAX_PIXEL;
						}
						//maneira mais segura de fazer conversao no lugar da forma mais dinamica e comum
						img[i][j].r = static_cast <unsigned char>(valor);
						img[i][j].g = static_cast <unsigned char>(valor);
						img[i][j].b = static_cast <unsigned char>(valor);
					}		
				}
			}
			else if(tipo == "P3"){
				//aalterando a imagem colorida para clarear 
				for(int i = 0; i < altura; i++){
					for (int j = 0; j < largura; j++){
						
						//clareamento dos componentes de cor r
						valor = (int)img[i][j].r;
						valor += fator;
						if(valor > MAX_PIXEL){
							valor = MAX_PIXEL;
						}
						img[i][j].r = static_cast <unsigned char>(valor);
							
						//clareamento dos componentes de cor g
						valor = (int)img[i][j].g;
						valor += fator;
						if(valor > MAX_PIXEL){
							valor = MAX_PIXEL;
						}
						img[i][j].g = static_cast <unsigned char>(valor);
						
						//clareamento dos componentes de cor b
						valor = (int)img[i][j].b;
						valor += fator;
						if(valor > MAX_PIXEL){
							valor = MAX_PIXEL;
						}
						img[i][j].b = static_cast <unsigned char>(valor);
					}
				}
			}
			arqRecord(arqNew, tipo, largura, altura, img);
    	break;
    	case 2:
    		do{	
    			clearScreen();
        		arqRead(arqName, tipo, largura, altura, valor, img);
        		cout << "|Insira o fator de escurecimento da imagem(1-100): ";
        		cin >> fator;
        		
        		if(fator < 1 || fator > 100){
        			cout<< endl<<"|Insira um valor entre 1 e 100."<< endl;
        			system("pause");
				}	
        	} while(fator < 1 || fator > 100); //Validacao de fator
        	
        	if (tipo == "P2"){
        		//alterando a imagem para escurecer
        		for(int i = 0; i < altura; i++){
        			for(int j = 0; j < largura; j++){
        				valor = (int)img[i][j].r;
        				valor -= fator;
        				if(valor <0){
        					valor = 0;
						}
						img[i][j].r = static_cast <unsigned char>(valor);
						img[i][j].g = static_cast <unsigned char>(valor);
						img[i][j].b = static_cast <unsigned char>(valor);
					}		
				}
			}
			else if(tipo == "P3"){
				//alterando a imagem colorida para escurecer 
				for(int i =0; i < altura; i++){
					for (int j = 0; j < largura; j++){
						
						//escurecimento dos componentes de cor r
						valor = (int)img[i][j].r;
						valor -= fator;
        				if(valor < 0){
        					valor = 0;
						}
						img[i][j].r = static_cast <unsigned char>(valor);
							
						//escurecimento dos componentes de cor g
						valor = static_cast <int>(img[i][j].g);
						valor -= fator;
        				if(valor <0){
        					valor = 0;
						}
						img[i][j].g = static_cast <unsigned char>(valor);
						
						//escurecimento dos componentes de cor b
						valor = (int)img[i][j].b;
						valor -= fator;
        				if(valor < 0){
        					valor = 0;
						}
						img[i][j].b = static_cast <unsigned char>(valor);
					}
				}
			}
			arqRecord(arqNew, tipo, largura, altura, img);
    	break;	
    	case 3:
    		arqRead(arqName, tipo, largura, altura, valor, img);
    		for(int i = 0; i < altura; i++){
    			for(int j = 0; j < largura; j++){
    				
    				//negativando a imagem cinza;
    				if(tipo == "P2"){
    					valor = (int) img[i][j].r;
    					img[i][j].r = img[i][j].g = img[i][j].b = static_cast <unsigned char>
						(MAX_PIXEL - valor);
					}
					//negativando cada elemento do rgb da imagem colorido
					else if(tipo =="P3"){
						img[i][j].r = static_cast <unsigned char>(MAX_PIXEL - (static_cast <int>(img[i][j].r)));
						img[i][j].g = static_cast <unsigned char>(MAX_PIXEL - (static_cast <int>(img[i][j].g)));
						img[i][j].b = static_cast <unsigned char>(MAX_PIXEL - (static_cast <int>(img[i][j].b)));
					}
				}
			}
    		cout << "|A imagem foi negativada.";
    		arqRecord(arqNew, tipo, largura, altura, img);
    	break;
    	case 4:
    		arqRead(arqName, tipo, largura, altura, valor, img);
    		 for(int i = 0; i < altura; i++){
                for(int j = 0; j < largura / 2; j++){
                   
                    Cor temp = img[i][j]; //criacao de uma variavel temporaria para salvar o primeiro valor
                    img[i][j] = img[i][largura - 1 - j];
                    img[i][largura - 1 - j] = temp;
                }
            }
    		arqRecord(arqNew, tipo, largura, altura, img);
    	break;
    	case 5:
    		arqRead(arqName, tipo, largura, altura, valor, img);
    		Cor imgResult[MAXALTURA][MAXLARGURA];
    		int gxR, gyR, gxG, gyG, gxB, gyB;

    		for (int i = 1; i < altura - 1; ++i) {
        		for (int j = 1; j < largura - 1; ++j) {
            		gxR = gyR = 0;
            		gxG = gyG = 0;
            		gxB = gyB = 0;

            		for (int k = -1; k <= 1; ++k) {
                		for (int l = -1; l <= 1; ++l) {
                    		gxR += img[i + k][j + l].r * Gx[k + 1][l + 1];
                    		gyR += img[i + k][j + l].r * Gy[k + 1][l + 1];
                    		gxG += img[i + k][j + l].g * Gx[k + 1][l + 1];
                    		gyG += img[i + k][j + l].g * Gy[k + 1][l + 1];
                    		gxB += img[i + k][j + l].b * Gx[k + 1][l + 1];
                    		gyB += img[i + k][j + l].b * Gy[k + 1][l + 1];
                		}
            		}
            		int magnitudeR = sqrt(gxR * gxR + gyR * gyR);
            		int magnitudeG = sqrt(gxG * gxG + gyG * gyG);
            		int magnitudeB = sqrt(gxB * gxB + gyB * gyB);

            		if (magnitudeR > MAX_PIXEL){
            			magnitudeR = MAX_PIXEL;
					}
            		if (magnitudeG > MAX_PIXEL){
            			magnitudeG = MAX_PIXEL;
					}
            		if (magnitudeB > MAX_PIXEL){
            			magnitudeB = MAX_PIXEL;
					} 
					imgResult[i][j].r = static_cast <unsigned char>(magnitudeR);
					imgResult[i][j].g = static_cast <unsigned char>(magnitudeG);
					imgResult[i][j].b = static_cast <unsigned char>(magnitudeB);
        		}
    		}
    		//tratamento de bordas
    		for (int i = 0; i < altura; ++i) {
        		for (int j = 0; j < largura; ++j) {
            		if (i == 0 || i == altura - 1 || j == 0 || j == largura - 1) {
                		imgResult[i][j].r = imgResult[i][j].g = imgResult[i][j].b = 0;
            		}
       			}
    		}
    		arqRecord(arqNew, tipo, largura, altura, imgResult);
    	break;
    	case 6:
    		do{
    			clearScreen();
   				arqRead(arqName, tipo, largura, altura, valor, img);
    			cout << "|Insira o fator de contraste (0.0-2.0): ";
    			cin >> fator;
    			
    			if (fator < 0.0 || fator > 2.0) {
        			cout << "|Insira um valor entre 0.0 e 2.0." << endl;
        			system("pause");
        			break;
    			}
    		} while(fator<0.0 || fator > 2.0); //validacao de fator

    		for (int i = 0; i < altura; i++) {
        		for (int j = 0; j < largura; j++) {
            		if (tipo == "P2") {
                		int valorAtual = static_cast<int>(img[i][j].r);
                		int novoValor = static_cast<int>(fator * (valorAtual - 128) + 128);
                		unsigned char valorFinal = static_cast<unsigned char>(min(MAX_PIXEL, max(0, novoValor)));
                		img[i][j].r = img[i][j].g = img[i][j].b = valorFinal;
            		} 
            		else if (tipo == "P3") {
               			int tr = static_cast<int>(fator * (img[i][j].r - 128) + 128);
                		int tg = static_cast<int>(fator * (img[i][j].g - 128) + 128);
                		int tb = static_cast<int>(fator * (img[i][j].b - 128) + 128);

                		img[i][j].r = static_cast<unsigned char>(min(MAX_PIXEL, max(0, tr)));
                		img[i][j].g = static_cast<unsigned char>(min(MAX_PIXEL, max(0, tg)));
                		img[i][j].b = static_cast<unsigned char>(min(MAX_PIXEL, max(0, tb)));
            		}
        		}
    		}
    		arqRecord(arqNew, tipo, largura, altura, img);
    	break;
    	case 7:
    		arqRead(arqName, tipo, largura, altura, valor, img);
    		if (tipo=="P2"){
    			cout << endl << "|A imagem ja e tons de cinza, tente com outra imagem." << endl;
    			return main();
			}
			else if(tipo =="P3"){
				tipo = "P2";
				
				for(int i =0; i<altura; i++){
					for(int j = 0; j<largura; j++){
						unsigned char gray = static_cast<unsigned char>
						((img[i][j].r + img[i][j].g + img[i][j].b) / 3);
						img[i][j].r = img[i][j].g = img[i][j].b = gray;
					}
				}	
			}
			arqRecord(arqNew, tipo, largura, altura, img);	
    	break;
    	case 8:
    		clearScreen();
    		cout<<"|Obrigado pela sua atencao, tenha um bom dia!"<< endl <<"|";
    		system("pause");
    		return 0;
    	break;
	}
	system("pause");
}while(choice !=8);

return 0;
}

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  //limpa a tela no Windows
    #else
        system("clear");  //limpa a tela no Unix/Linux/MacOS/Ubuntu
    #endif
}

void arqRead(const char* arqName, string& tipo, int& largura, int& altura, int& valor, 
    Cor img[MAXALTURA][MAXLARGURA]){
		
	ifstream arqIn(arqName, ios::in);
	
    if (!arqIn) {
        cout << "|Erro na abertura do arquivo." << endl;
        system("pause");
        return; 
    }

    arqIn >> tipo;
    arqIn.get();

    if (tipo == "P2") {
        cout << "|Imagem: tons de cinza\n";		   
    } else if (tipo == "P3") {
        cout << "|Imagem: colorida\n";
    } else if (tipo == "P1" || tipo == "P4" || tipo == "P5") {
        cout << "|Desculpe, nao trabalho com esse tipo de imagem. Tente novamente.\n";
        arqIn.close();
        system("pause");
        return;  
    }
	
	//lendo a proxima linha, como e comentario, apenas ignora.
    char c = arqIn.get();
    while (c == '#') {
        arqIn.ignore(numeric_limits<streamsize>::max(), '\n');
        c = arqIn.get();
    }
    arqIn.putback(c);
	
	//leitura largura e altura
    arqIn >> largura >> altura;

    cout << "|Tamanho: " << largura << " x " << altura << endl;
    if (largura > MAXLARGURA) {
        cout << "|Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << 
		" pixels de largura.\n";
        arqIn.close();
        return; 
    }
    if (altura > MAXALTURA) {
        cout << "|Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << 
		" pixels de altura.\n";
        arqIn.close();
        return;
    }
    //leitura maximo de cor
    arqIn >> valor; 
    
    //leitura dos pixels da imagem
    for(int i = 0; i < altura; i++){
    	for(int j = 0; j < largura; j++){
    		if(tipo == "P2"){
    			arqIn >> valor;
    			img[i][j].r = img[i][j].g=img[i][j].b = static_cast <unsigned char>(valor);
			}
			else if(tipo == "P3"){
				int r, g, b;
				arqIn >> r >> g >> b;
				img[i][j].r = static_cast <unsigned char>(r);
				img[i][j].g = static_cast <unsigned char>(g);
				img[i][j].b = static_cast <unsigned char>(b);
			}
    	
		}
	}
	
	arqIn.close();
}
void arqRecord(const char* arqNew, string& tipo, int& largura, int& altura, 
    Cor img[MAXALTURA][MAXLARGURA]) {
    	
    ofstream arqOut;
    arqOut.open(arqNew, ios::out);
    
    if (!arqOut) {
        cout << "|Nao consegui criar o arquivo " << arqNew << endl;
        return;
    }
    arqOut << tipo << endl;
    arqOut << "# TP3-INF110, by PST\n"; //comentário no novo arquivo
    arqOut << largura << " " << altura << " " << MAX_PIXEL << endl;
    
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (tipo == "P2") {
                arqOut << (int)img[i][j].r << endl;
            } 
			else if (tipo == "P3") {
				
                arqOut << static_cast<int>(img[i][j].r) << " "
                       << static_cast<int>(img[i][j].g) << " "
                       << static_cast<int>(img[i][j].b) << endl;
            }
        }
    }
    cout << endl << "|O novo arquivo foi gerado com sucesso, verifique o diretorio!" << endl;
    arqOut.close();
}
