#include<iostream>
#include<stdlib.h>
#include<chrono>
#include<vector>
using namespace std;

void metodo_insertion_sort(int n, vector<int>& arreglo);
void metodo_quicksort(vector<int>& arreglo, int inicio, int final);
int partir_arreglo(vector<int>& arreglo, int inicio, int final);
void metodo_heapsort(int n, vector<int>& arreglo);
void heapsort(int n, vector<int>& arreglo);
void ordenar_heap(int n, vector<int>& arreglo, int i);
void primer_heap(int n, vector<int>& arreglo);
void cambio_posicion(vector<int>& arreglo, int i, int j);
void imprimir_arreglo(vector<int>& arreglo, int n);

int main(){
	int opc, n;
	cin>>opc;
	cin>>n;
	vector<int> arreglo(n);
	srand(time(NULL));
    for(int i=0; i<n; i++){
		cin>>arreglo[i];
    }
	auto start = std::chrono::system_clock::now();
	switch(opc){
		case 1:{
			metodo_heapsort(n, arreglo);
			break;
		}
		case 2:{
			metodo_insertion_sort(n,arreglo);
			break;
		}
		case 3:{
			metodo_quicksort(arreglo, 0, (n-1));
			break;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> duracion = end - start;
	imprimir_arreglo(arreglo,n);
	cout<<duracion.count()<<" ms"<<endl;
	arreglo.clear();
	return 0;
}

void metodo_heapsort(int n, vector<int>& arreglo){
	primer_heap(n,arreglo);
	heapsort(n,arreglo);
}

void heapsort(int n, vector<int>& arreglo){
	for(int posiciones=n-1;posiciones>=0;posiciones--){
		cambio_posicion(arreglo,0,posiciones);
		ordenar_heap(posiciones,arreglo, 0);
	}
}

void primer_heap(int n, vector<int>& arreglo){
	for(int i=(n-2)/2;i>=0;i--){
		ordenar_heap(n,arreglo,i);
	}
}

void ordenar_heap(int n,vector<int>& arreglo, int i){
	int hija_izquierda,hija_der, nuevo_padre;
		hija_izquierda=2*i+1;
		hija_der=2*i+2;
		nuevo_padre=i;
		if(hija_izquierda<n && arreglo[hija_izquierda]>arreglo[i]){
			nuevo_padre = hija_izquierda;
		}
		if(hija_der<n && arreglo[hija_der] > arreglo[nuevo_padre]){
			nuevo_padre = hija_der;
		}
		if(nuevo_padre!=i){
			cambio_posicion(arreglo,i,nuevo_padre);
			ordenar_heap(n,arreglo,nuevo_padre);
		}
}

void metodo_insertion_sort(int n, vector<int>& arreglo){
	int k,aux;
	for(int i=0;i<n;i++){
		k = i;
		aux = arreglo[i];
		while((k>0) && (arreglo[k-1]>aux)){
			arreglo[k] = arreglo[k-1];
			k--;
		}
		arreglo[k]=aux;
	}
}

void metodo_quicksort(vector<int>& arreglo, int inicio, int final){
    if(inicio<final){
        int pivote = partir_arreglo(arreglo, inicio, final);
        metodo_quicksort(arreglo, inicio, pivote-1);
        metodo_quicksort(arreglo, pivote+1, final);
    }
}

int partir_arreglo(vector<int>& arreglo, int inicio, int final){
    srand(time(NULL));
    int indiceRandom = inicio + rand()%(final-inicio+1);
    cambio_posicion(arreglo, inicio, indiceRandom);
    int pivote = arreglo[inicio];
    int i = inicio+1;
    for(int j=i; j<=final; j++){
        if(arreglo[j]<pivote){
            cambio_posicion(arreglo, i, j);
            i++;
        }
    }cambio_posicion(arreglo, inicio, (i-1));
    return i-1;
}

void cambio_posicion(vector<int>& arreglo, int i, int j){
    int temp = arreglo[i];
    arreglo[i] = arreglo[j];
    arreglo[j] = temp;
}

void imprimir_arreglo(vector<int>& arreglo, int n){
    for(int i=0; i<n; i++){
        cout<<arreglo[i]<<" ";
    }cout<<endl;
}
