#include<stdio.h>
#include<climits>
#include <algorithm>
#include<iostream>
#define INT_MAX 99999
//Antallet af byer
int n = 4;
//Adjancey matrix (afstande mellem byerne)
int dist[10][10] = {
    {0, 1, 15, 6},
    {2, 0, 7, 3},
    {9, 6, 0, 12},
    {10, 4, 8, 0}
};
//Hvis alle byer er besøgt
int visited_all = (1<<n) - 1;
//Rekursiv funktion til at finde den mindste afstand
int tsp(int ncity, int pos)
{
    //basis-tilfældet:Hvis alle byer er besøgt, returnér afstanden tilbage til startbyen
    if(ncity==visited_all) {
        return dist[pos][0];
    }
    //Initialliserer minimumsomkostningen til en stor værdi(defineret øverst)
    int ans = INT_MAX;
    //Prøver at besæge hver by
    for(int city=0; city<n; city++){
        //Tjekker om byen allerede er besøgt
        if((ncity&(1<<city))==0){
            //Hvis byen ikke er besøgt så:
            int newAns = dist[pos][city] +
            tsp(ncity|(1<<city),city);
            ans = min(ans,newAns);  //TODO: RASMUS: min skal defineres
        }
    }
    //Returner den mindste omkostning
    return ans;
}
int main (){
    printf("Minimum cost of visiting all cities: %d/n", tsp(1,0));
    return 0;
}