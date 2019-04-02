#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------
void output(int midrow,int midcolumn,int multiresult,char* outputfilename){					
    FILE *write;
    write = fopen(outputfilename,"a");
    fprintf(write,"%d,%d:%d\n",midrow,midcolumn,multiresult);                               //writes the output file

    fclose(write);

}
//--------------------------------------------------------------------------------------------------------------------------------------------------
int multiply(int **mapmatrix,int **keymatrix,int currow ,int curcolumn,int keysize){
    int count=0;		// multiply result(multiresult)		

    int i;
    int j;                                                                                  
    for(i=0;i<keysize;i++){				//for multiply each key and map row
        for(j=0;j<keysize;j++){      	//for multiply each key and map column
            count+=((mapmatrix[i+currow][j+curcolumn])*(keymatrix[i][j])); //multiplies keymatrix and sub matrix and adds count 
        }
    }
    return count;																		

}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void searchtreasure(int** mapmatrix,int** keymatrix,int keysize,int rowsize,int columnsize, int currow, int curcolumn,char* outputfilename){

    int resultvalue;																
    int multiresult;
    int a=keysize/2;															  //for reaching sub map matrix(map*key)'s middle for output

    multiresult = multiply(mapmatrix,keymatrix,currow,curcolumn,keysize);         //multiresult = multiply result
    resultvalue= multiresult%5;													  //resultvalue = mod 5 of multiply result for operations

    if(resultvalue <0) resultvalue = resultvalue + 5;							  //if mod negative, turn positive

    //1: Go up
    //2: Go down
    //3: Go right
    //4: Go left

    output (currow+a,curcolumn+a, multiresult,outputfilename);					   //current row+a and current column+a shows that where is the sub mutrix 

	
    if (resultvalue==0 ){															//treasure found, exit
        exit(0);
																					//currow= current row of mapmatrix, curcolumn= current column of map matrix
    }
    else if (resultvalue==1 && currow-keysize >= 0){								//for going up,if currow-keysize>=0 it in the map matrix so i can subtract keysize from currow 	

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow-= keysize, curcolumn,outputfilename);
    }
    else if (resultvalue==2 && currow+keysize < rowsize){							//for going down,if it is not exceed the map matrix row, then i can add currow and keysize 

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow+= keysize, curcolumn,outputfilename);
    }
    else if (resultvalue==3 && curcolumn-keysize < columnsize){						//for going right, if it is not exceed the map matrix column, then i can add curcolumn and keysize

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow, curcolumn+=keysize,outputfilename);
    }
    else if (resultvalue==4 && curcolumn-keysize >= 0){								//for going left, if curcolumn-keysize>=0 it in the map matrix so i can subtract keysize from curcolumn

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow, curcolumn-=keysize,outputfilename);
    }
    else if (resultvalue==1 && currow-keysize < 0){									//for going up,if current row -keysize<0 it can not go up so it has to go down, i add currow and keysize

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow+=keysize, curcolumn,outputfilename);
    }
    else if (resultvalue==2 && currow+keysize >= rowsize){							//for going down, if it is not exceed the map matrix row, then i can subtract currow from keysize

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow-=keysize, curcolumn,outputfilename);
    }
    else if (resultvalue==3 && curcolumn-keysize >= columnsize){					//for going	right, if it is exceed the column, then it has go to left, so i subtract keysize from curcolumn  		

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow, curcolumn-=keysize,outputfilename);
    }
    else if (resultvalue==4 && curcolumn-keysize < 0){								//for going left, if curcolumn-keysize negative then it is not in the map matrix, then i add them for going right

        searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize, currow, curcolumn+=keysize,outputfilename);
    }



}
//---------------------------------------------------------------------------------------------------
int main(int argc,char *argv[]) {


    char *matrixsize = argv[1];					//map matrix size	
    char* rowsizestr=strtok(matrixsize,"x");    //takes map matrix row size(str) with strtok
    char* columnsizestr=strtok(NULL,"x");		//takes map matrix column size(str) with strtok
    char* keysizestr=argv[2];					//key matrix size(str)
    int rowsize = atoi(rowsizestr);				//map matrix row size
    int columnsize=atoi(columnsizestr);			//map matrix column size

    int keysize = atoi(keysizestr);				//key matrix size
    char* mapfilename =argv[3];					
    char* keyfilename =argv[4];					
    char* outputfilename= argv[5];					

    int currow=0;								//initial current column for map matrix	
    int curcolumn=0;							//initial current row for map matrix

    //---------------------------------------------------------------------------------------------------
    int i;
    int j;

    int** keymatrix= (int**)malloc(keysize*sizeof(int*));
    for(i=0;i<keysize;i++)											//Dynamic memory allocation for key matrix
        keymatrix[i]=malloc(keysize*sizeof(int));

    FILE *file1;
    file1=fopen(keyfilename, "r");									//file read						

    for(i = 0; i < keysize; i++)
        for(j = 0; j < keysize; j++)
            fscanf(file1, "%d", &keymatrix[i][j]);					//assigning values in the file


//--------------------------------------------------------------------------------
    int** mapmatrix=(int**) malloc((rowsize) * sizeof(int *));
    for(i=0;i<rowsize;i++)
        mapmatrix[i]=malloc(columnsize*sizeof(int));				//Dynamic memory allocation for map matrix
    FILE *file;
    file=fopen(mapfilename, "r");									//file read

    for(i = 0; i < rowsize; i++)
        for(j = 0; j < columnsize; j++)
            fscanf(file, "%d", &mapmatrix[i][j]);                   //assigning values in the file
    

//----------------------------------------------------------------------------------------
    searchtreasure(mapmatrix,keymatrix,keysize,rowsize,columnsize,currow,curcolumn,outputfilename);		//goes the search function
//-----------------------------------------------------------------------------------------
    fclose(file1);		//file closing
    fclose(file);		//file closing
    free(mapmatrix);	//deallocate 
    free(keymatrix);	//deallocate 
    return 0;
}