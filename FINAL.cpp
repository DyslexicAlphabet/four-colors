#include <stdio.h>
#include <stdlib.h>
using namespace std;

int table[30][30];
char colors[30][30];
int v0[100];
int h0[100]; 
int ans;
int count[100] = {0};
char country[100];
int numOfColors = 1;
//III. DFS Check Function
bool checkNeighbor(char color, char colors[30][30], int table[30][30], int v, int h) {
//Foolproof check function:
//1. Only check if there exists a color pixel in said direction
//2. To return false, i.e. to say that a color is not viable in said location, it must be the case that
//(a) The countries are different AND (b) They have the same colors. 	
if (v != 0) {
	if ((table[v-1][h] != table[v][h]) && (colors[v-1][h] == color)) {
		//Check up
		return false;
	} 
}
if (v != 29) {
	if ((table[v+1][h] != table[v][h]) && (colors[v+1][h] == color)) {
		//Check down
		return false;
	}
}
if (h != 0) {
	if ((table[v][h-1] != table[v][h]) && (colors[v][h-1] == color)) {
		//Check left
		return false;
	}
}
if (h != 29) {
	if ((table[v][h+1] != table[v][h]) && (colors[v][h+1] == color)) {
		//Check right
		return false;
	} 
} 
	return true;
}
//II. DFS
void DFS(int pos) {
	int i,j,k; //Temporary variables
	int v,h;
    v = pos/30; //Vertical position, the lower bound will automatically be taken
	h = pos%30; //Horizontal position
	if(pos == 900) {
		for (i=0; i<30; i++) {
			for (j=0; j<30; j++) {
				if (j == 29) {
    			printf("%c \n", colors[i][j]);
    			} else {
    			printf("%c ", colors[i][j]);
    			}	
			} 
		}
		printf("\n \n \n");
		ans++;
		return;
	}
	//Identify whether the pixel is a country or not
	if(table[v][h] == 0) {
		colors[v][h] = 96;
		DFS(pos + 1);
	} else {
		//Check whether this pixel is the first one of said country
		if (count[table[v][h]] == 0) {
			v0[table[v][h]] = v;
			h0[table[v][h]] = h;
			count[table[v][h]]++;
		}
		if (v == v0[table[v][h]] && h == h0[table[v][h]]) {
			for(k = 0; k<numOfColors; k++) {
				if(checkNeighbor(97 + k, colors, table, v, h)) {
					country[table[v][h]] = 97 + k; //Give it a color (97 + k) in ASCII code
					colors[v][h] = country[table[v][h]];
					DFS(pos + 1);
				}
			}
		} else {
			// Try the assigned color and if you can't, go back and decrease the count by 1
			if(checkNeighbor(country[table[v][h]], colors, table, v, h)) {
				colors[v][h] = country[table[v][h]];
				DFS(pos + 1);
			} else {
			} 
		}
	}	 
}
//I. Main Function
int main() {
	int i,j; //Temporary variable
	//Scan the file
    freopen("color900_1.txt","r",stdin);
    freopen("color900_1_out.txt","w",stdout);
    for(i=0; i<30; i++) {
    	for(j=0; j<30; j++) {
    		scanf("%2d", &table[i][j]);
    	}
    }
    for(ans = 0;ans == 0; ) {
	DFS(0);
	numOfColors++;
	}
	printf("The minimum number of color(s) needed is %d, and given %d color(s), there is a total of %d valid answer(s)", numOfColors - 1, numOfColors - 1, ans);
}
