#include<stdio.h>
#include<limits.h>  //RAS: changed climits (c++) to limits.h (c)
//#include <algorithm.h>  //RAS: what is this? (looking at it, it was probably just used for the "min" function)

//RAS: function that returns the smallest number of the two
int min(const int a, const int b) {
    if (a < b) return a;
    return b;
}

//RAS: hvis du har hentet INT_MAX fra limits.h hvorfor så definere den her?
#define INT_MAX 99999

//JIN: Adjancey matrix (afstande mellem byerne)
int dist[20][20] = {
    {0, 2, 5, 12,10,15,12,5, 7, 8, 8, 6, 9, 5, 14,11,14,4, 3, 3},
    {2, 0, 4, 9, 15,13,12,15,5, 5, 6, 9, 11,4, 5, 2, 14,6, 1, 13},
    {7, 8, 0, 3, 4, 12,4, 1, 6, 9, 5, 5, 12,3, 11,8, 10,12,15,9},
    {7, 5, 10,0, 6, 13,8, 9, 11,10,5, 6, 14,5, 14,14,2, 7, 1, 14},
    {5, 11,5, 10,0, 7, 8, 8, 12,1, 1, 6, 2, 12,4, 6, 14,8, 6, 10},
    {3, 11,13,8, 6, 0, 12,11,3, 1, 11,8, 6, 1, 14,2, 6, 6, 9, 6},
    {14,11,6, 5, 11,9, 0, 5, 3, 1, 2, 3, 11,8, 9, 7, 5, 5, 15,9},
    {3, 15,11,7, 12,9, 12,0, 10,1, 12,5, 7, 13,3, 4, 12,15,14,2},
    {3, 12,6, 5, 3, 14,7, 11,0, 6, 2, 12,5, 2, 15,10,1, 12,10,5},
    {3, 12,14,4, 8, 11,1, 7, 15,0, 12,8, 7, 1, 10,12,11,13,9, 3},
    {4, 7, 10,4, 5, 8, 9, 3, 11,5, 0, 7, 1, 11,3, 14,9, 11,3, 10},
    {13,14,1, 3, 8, 6, 13,3, 4, 2, 13,0, 6, 9, 12,7, 11,15,8, 8},
    {4, 11,1, 12,14,3, 7, 9, 15,15,14,4, 0, 15,14,11,5, 5, 11,8},
    {9, 8, 9, 10,6, 1, 7, 13,13,15,5 ,15,2 ,0 ,11,2, 3, 3, 5, 8},
    {9, 10,14,5, 9, 2, 8, 3, 9, 12,9, 1, 4, 14,0, 1, 1, 7, 7, 4},
    {9, 10,10,12,3, 5, 11,4, 12,13,2, 14,15,8, 10,0, 5, 5, 12,9},
    {4, 15,11,4, 4,14, 1, 9, 6, 2, 11,15,1, 9, 6, 3, 0, 11,7, 1},
    {10,14,14,15,6, 7, 14,5, 6, 8, 6, 6, 6, 14,2, 12,15,0, 15,6},
    {13,2, 8, 12,13,14,6, 15,11,9, 7, 15,4, 5, 6, 15,15,14,0, 8},
    {3, 3, 9, 3, 15,4, 9, 12,9, 13, 6, 2, 13,6, 9,13,12,11,9 ,0}
};

//JIN: Antallet af byer
const int n = sizeof(dist[0]) / sizeof(int);  //RAS: ændrede det om til en constant (pga. linje 42 og ændrede den til selv at hente størrelsen på matrixen)

//JIN: Hvis alle byer er besøgt
int visited_all = (1<<n) - 1;

//JIN: Rekursiv funktion til at finde den mindste afstand
int tsp_jin(int ncity, int pos)
{
    //JIN: basis-tilfældet:Hvis alle byer er besøgt, returnér afstanden tilbage til startbyen
    if(ncity==visited_all) {
        return dist[pos][0];
    }
    //JIN: Initialliserer minimumsomkostningen til en stor værdi(defineret øverst)
    int ans = INT_MAX;

    //JIN: Prøver at besæge hver by
    for(int city=0; city<n; city++){

        //JIN: Tjekker om byen allerede er besøgt
        if((ncity&(1<<city))==0){
            //JIN: Hvis byen ikke er besøgt så:
            int newAns = dist[pos][city] + tsp_jin(ncity|(1<<city),city);
            ans = min(ans,newAns);
        }
    }
    //JIN: Returner den mindste omkostning
    return ans;
}
int main (){
    printf("Minimum cost of visiting all cities: %d\n", tsp_jin(1,0));
    return 0;
}