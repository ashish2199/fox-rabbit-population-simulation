#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>

#define MAX_AGE 10
#define MAX_RABBITS_PER_GRID 20
#define MAX_FOXES_PER_GRID 9
#define MAX_POPR 20
using namespace std;

typedef struct Rabbit;
typedef struct Fox;

    //fox structure
    struct Fox {
    bool alive=true;
    //constructor for the fox so that every fox ia alive at the beginning
    Fox(void) : alive(true) {}
    int xIndex;
    int yIndex;
    int fedLevel;
    };

//structure of rabbit
            struct Rabbit {
                int age;
                bool alive;
              //constructor for the rabbit
              Rabbit(void): age(0),alive(true){}
                        int xIndex;
                        int yIndex;
            };

//function prototype of the three function
void PrintGrids(int **FoxBoard, int **RabbitBoard, ostream& outStream, int numRows, int numCols);
bool RabbitStep( int **rabbitBoard,Rabbit *listOfRabbits, int& numberRabbitsTotal, int& numberRabbitsAlive,int numRows, int numCols, int rabbitListLength,int maxNumRabbitsPerGrid, int numChildren);
void FoxStep( int **foxBoard,Fox *listOfFoxes, int **rabbitBoard,Rabbit *listOfRabbits, int numberFoxesTotal, int& numberFoxesAlive, int numberRabbitsTotal,int& numberRabbitsAlive, int numRows, int numCols, int foxListLength, int rabbitListLength,ostream& outFile);

int main(void) {

int XX,tries,numRows,numCols,generations,seed,fractsquares,maxFoxes,maxRabbits,maxchildren;
float  fracFox,fracRabbit,maxChildren;

//for Writing to File
string filename;
ofstream outFile;


tries=6;
while(tries>0){
    // Read the name of the input file
    cout << "Enter the name of the output file:";
    cin >> filename;
// open the output file (attach it to the stream outFile)
outFile.open(filename.c_str());

    // Check to assure the output file has been correctly opened
    if(outFile.fail())
    {    // if there is a problem opening the file print an error
        cout << "ERROR: output" << filename << " didnot not opened correctly\n";
        return 1;
        //when tries are over
        if(tries=1){cout<<"ERROR: could not open output file after 6 tries";}
    }
    else
    { //when correct input entered break
        break;
        }
}

tries=6;
while(tries>0){
cout << "Enter the number of rows in the simulation grid: ";
//numRows=6;
if( !(cin >> numRows) )
    {
      cout << "ERROR: Cannot read number of rows";

    }
if(numRows>0&&numRows<15){
        //input match the condition
        break;
}else{
//when input does not match criteria
cout << "ERROR: Read an illegal number of rows for the board ";
//when tries are over
if(tries==1){cout << " ERROR: could not read number of columns after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the number of columns in the simulation grid:";
//numCols=5;
if( !(cin >> numCols) )
    {
      cout << "ERROR: Cannot read number of columns";
    }
if(numCols>0&&numCols<15){break;}else{
cout << "ERROR: Read an illegal number of columns for the board ";
if(tries==1){cout << " ERROR: could not read number of columns after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the number of generations:";
//generations=4;
if( !(cin >> generations) )
    {
        cout << "ERROR: Cannot read number of generations";

    }
if(generations>0&&generations<40){break;}else{
cout << " ERROR: Read an illegal number of generations ";
if(tries==1){cout << "ERROR: could not read number of generations after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the seed for the random number generator: ";
//seed=432;
if( !(cin >> seed) )
    {
        cout << "ERROR: Cannot read number of seeds";

    }
if(seed>0&&seed<RAND_MAX){break;}else{
cout << "ERROR: Read an illegal seed ";
if(tries==1){cout << "ERROR: could not read the seed for the random number generator after 6 tries ";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the initial fraction of squares in the grid containing foxes:";
//fracFox =0.2;
if( !(cin >> fracFox) )
    {
        cout << " ERROR: Cannot read the initial fraction of squares in the grid containing foxes";

    }
if( fracFox >0.05&& fracFox <0.95){break;}else{
cout << "ERROR: Read an illegal initial fraction of squares in the grid with foxes ";
if(tries==1){cout << "ERROR: could not read the initial fraction of squares in the grid containing foxes after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the initial fraction of squares in the grid containing rabbits:";
//fracRabbit = 0.5 ;
if( !(cin >> fracRabbit) )
    {
        cout << "ERROR: Cannot read the initial fraction of squares in the grid containing rabbits";

    }
if(  fracRabbit>0.05&&fracRabbit<0.95){break;}else{
cout << "ERROR: Read an illegal initial fraction of squares in the grid containing rabbits";
if(tries==1){cout << "ERROR: could not read the initial fraction of squares in the grid containing rabbits after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the initial maximum number of foxes per grid:";
//maxFoxes=8;
if( !(cin >> maxFoxes) )
  {
    cout << "ERROR: Cannot read the initial maximum number of foxes per grid";

 }
if(  maxFoxes>0.05&&maxFoxes<=MAX_FOXES_PER_GRID){break;}else{
cout << "ERROR: Read an illegal initial maximum number of foxes per grid";
if(tries==1){cout << "ERROR: could not read the initial maximum number of foxes per grid after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the initial maximum number of rabbits per grid:";
//maxRabbits  =8;
if( !(cin >> maxRabbits) )
    {
        cout << "ERROR: Cannot read the initial maximum number of Rabbits per grid";
    }
if(  maxRabbits>0.05&&maxRabbits<=MAX_RABBITS_PER_GRID){break;}else{
cout << "ERROR: Read an illegal initial maximum number of rabbits per grid";
if(tries==1){cout << "ERROR: could not read the initial maximum number of rabbits per grid after 6 tries";}
}
tries--;
}

tries=6;
while(tries>0){
cout << "Enter the initial maximum number of children produced when rabbits breed:";
//maxchildren = 2;
if( !(cin >> maxChildren) )
    {
        cout << " ERROR: Cannot read the maximum number of children produced when rabbits breed";
    }
if(  maxChildren>0.05&&maxChildren<=MAX_RABBITS_PER_GRID){break;}else{
cout << "ERROR: Read an illegal maximum number of children produced when rabbits breed";
if(tries==1){cout << "ERROR: could not read the maximum number of children produced when rabbits breed after 6 tries";}
}
tries--;
}


int maxNumRabbitsPerGrid=20;
int numChildren = maxchildren;
float foxFract = fracFox;

//dynamically allocate array
int** foxGrid = new int*[numRows];
for(int i = 0; i < numRows; ++i)
    foxGrid[i] = new int[numCols];



//int increment_temp
for(int i=0;i<numRows;i++){
for(int j=0;j<numCols;j++){
    l1:XX=rand();

        if(XX<(1.0-foxFract)*RAND_MAX)
            {
                foxGrid[i][j]=0;
                }
        else{
                float increment = foxFract / maxFoxes;
                float prob = (double)XX / (double)RAND_MAX;

                if(prob<1){

                    for(int MM=1;MM<= maxFoxes;MM++){
                    if( ((1-foxFract) + (MM-1) * increment)<prob && prob<((1-foxFract) + MM * increment)  ){

                            foxGrid[i][j]=MM;


                    }
                    }
                }
                else{ //if probability is more than one generate a new random number
                        goto l1;}
            }
    }
}

                                    /*
                                    cout<<"after initialising foxgrid now making foxlist \n";
                                    for(int i=0;i<numRows;i++){
                                    for(int j=0;j<numCols;j++){
                                        cout<<foxGrid[i][j];
                                    }cout<<"\n"; }
                                    */

//dynamically allocate array
Fox* foxList= new Fox[numRows*numCols*maxFoxes*2];

int foxListLength=numRows*numCols*maxFoxes*2;
int numberFoxesTotal=0;
int numberFoxesAlive=0;
int m=1;
for(int k=0;k<numRows;k++){
for(int p=0;p<numCols;p++){
          for( int ff=1;ff<=foxGrid[k][p];ff++){
                numberFoxesTotal++;
                numberFoxesAlive++;
                foxList[m].xIndex = p;
                foxList[m].yIndex = k;
                foxList[m].fedLevel  = rand() % 10;
                foxList[m].alive = true;
                m++;
            }
    }
    }

float rabbitFract = fracRabbit;

//dynamically allocate array
int** rabbitGrid = new int*[numRows];
for(int i = 0; i < numRows; ++i)
    rabbitGrid[i] = new int[numCols];


for(int i=0;i<numRows;i++){
for(int j=0;j<numCols;j++){
    l2:XX=rand();

float temp1=(1.0 - rabbitFract)*RAND_MAX;
        if(XX<temp1)
            {
                rabbitGrid[i][j]=0;
            }
        else{

                float increment =  rabbitFract  /  maxRabbits;
                float prob = (double)XX / (double)RAND_MAX;

                if(prob<1){
                    for(int MM=0;MM<=  maxRabbits;MM++){
                    if( ((1- rabbitFract) + (MM-1) * increment)<prob && prob<((1-rabbitFract) + MM * increment)  ){
                            rabbitGrid[i][j]=MM;
                    }
                    }
                }
                else{goto l2;}
            }
    }
}

//dynamically allocate array
Rabbit* rabbitList= new Rabbit[numRows*numCols*maxRabbits*20];
int rabbitListLength=numRows*numCols*maxRabbits*20;
int numberRabbitsTotal=0;
int numberRabbitsAlive=0;
int xi,yi;
m=1;
for(int k=0;k<numRows;k++){
for(int p=0;p<numCols;p++){
          for(int ff=1;ff<=rabbitGrid[k][p];ff++){

                numberRabbitsTotal += 1;
                 rabbitList[m].xIndex = p;
                  xi = rabbitList[m].xIndex = p;
                 rabbitList[m].yIndex = k;
                  yi= rabbitList[m].yIndex = k;

                 rabbitList[m].age  = rand() % 10;
                  int ager = rabbitList[m].age;

                 rabbitList[m].alive = true;
                 bool alv = rabbitList[m].alive = true;

                 numberRabbitsAlive += 1;
                m++;

            }
    }
}



                    /*  int rabbitsum =0;
                        cout<<"after initialising rabbttgrid now making rabbitlist \n";
                        for(int i=0;i<numRows;i++){
                        for(int j=0;j<numCols;j++){
                            cout<<rabbitGrid[i][j];
                            rabbitsum += rabbitGrid[i][j];
                        }
                        cout<<"\n"; }
                    */
outFile<<"after initialization\n";
cout<<"after initialization\n";
PrintGrids(foxGrid, rabbitGrid, cout, numRows, numCols);
PrintGrids(foxGrid, rabbitGrid, outFile, numRows, numCols);

    for(int g=0;g<=generations;g++){

        outFile<<"\n GENERATION : "<<g<<"\n";
        cout<<"\n GENERATION : "<<g<<"\n";
        RabbitStep(rabbitGrid,rabbitList,numberRabbitsTotal,numberRabbitsAlive,numRows,numCols,rabbitListLength,maxNumRabbitsPerGrid,numChildren);
        outFile<<"after rabbits die of old age and breed\n";
        cout<<"after rabbits die of old age and breed\n";
        PrintGrids(foxGrid, rabbitGrid, cout, numRows, numCols);
        PrintGrids(foxGrid, rabbitGrid, outFile, numRows, numCols);

        FoxStep(foxGrid,foxList,rabbitGrid,rabbitList,numberFoxesTotal,numberFoxesAlive,numberRabbitsTotal,numberRabbitsAlive,numRows,numCols, foxListLength, rabbitListLength,outFile);

    }
    outFile.close();
        return 0;
}

void PrintGrids(int **FoxBoard, int **RabbitBoard, ostream& outStream, int numRows, int numCols){
    int i;int j;

        for( i = 0; i < numRows; i++ )
        {
            for( j = 0; j < numCols; j++ )
            {
                outStream << std::setw(3)<< FoxBoard[i][j] << ",";
                outStream <<std::setw(2)<< RabbitBoard[i][j] << " ";
            }
            outStream << "\n";

        }
}

bool RabbitStep( int **rabbitBoard,Rabbit *listOfRabbits,
                int& numberRabbitsTotal, int& numberRabbitsAlive,int numRows, int numCols,
                int rabbitListLength,int maxNumRabbitsPerGrid, int numChildren)
{
//temporary varibale to keep track of number of rabbits present
//we cannot directly use numberRabbitsTotal as it will interfere in loop
int endrabbit =numberRabbitsTotal;
    for(int m=1;m<=numberRabbitsTotal;m++){
                listOfRabbits[m].age += 1;
                int age = listOfRabbits[m].age;
                int i = listOfRabbits[m].xIndex;
                int j = listOfRabbits[m].yIndex;
                if(age > MAX_AGE&&rabbitBoard[i][j]>0) {
                    listOfRabbits[m].alive = false;
                    numberRabbitsAlive--;
                    endrabbit--;
                    rabbitBoard[i][j]--;
                        }
                }

//variable to create pair of rabbits
        int pair=0;
        for(int m=1;m<numberRabbitsTotal;m++){
            int i = listOfRabbits[m].xIndex;
            int j = listOfRabbits[m].yIndex;


            if(rabbitBoard[i][j]<maxNumRabbitsPerGrid&&listOfRabbits[m].alive == true){
                {
                pair++;
                if(pair==4&&listOfRabbits[m].alive == true){

                    int childrenborn = rand()%numChildren+1;
                    if((rabbitBoard[i][j]+childrenborn)>20){
                            childrenborn = 0;
                        }

                    for(int ii=0;ii<childrenborn;ii++)
                        {
                            endrabbit++;
                    listOfRabbits[endrabbit].xIndex=i;
                    listOfRabbits[endrabbit].yIndex=j;
                    listOfRabbits[endrabbit].age=true;

                            }
                    numberRabbitsTotal+=childrenborn;
                    numberRabbitsAlive+=childrenborn;
                    pair = 0;
                    }
                }
            }
        }

    return true;
}

void FoxStep( int **foxBoard,struct Fox *listOfFoxes, int **rabbitBoard, Rabbit *listOfRabbits,
             int numberFoxesTotal, int& numberFoxesAlive, int numberRabbitsTotal,int& numberRabbitsAlive,
              int numRows, int numCols, int foxListLength, int rabbitListLength,ostream& outFile){
int endrabbit = numberRabbitsTotal;
for(int i=0;i<numRows;i++){
for(int j=0;j<numCols;j++){

            for(int m=1;m<numberFoxesTotal;m++){
                   int xf=listOfFoxes[m].xIndex;
                   int yf=listOfFoxes[m].yIndex;
                for(int n=1;n<numberRabbitsTotal;n++){
                        int xr = listOfRabbits[n].xIndex;
                        int yr = listOfRabbits[n].yIndex;
                        // to check in same block
                    if(i==xf&&j==yf&&i==xr&&j==yr){
                            //if there are alive rabbits in block
                            if(rabbitBoard[i][j]>0&&foxBoard[i][j]>0&&listOfRabbits[n].alive==true){
                               listOfRabbits[n].alive=false;
                               listOfFoxes[m].fedLevel += 1;
                               rabbitBoard[i][j] -= 1;
                               numberRabbitsAlive -= 1;
                               endrabbit--;
                            }
                            else
                            {
                                listOfFoxes[m].fedLevel -= 1;
                                if(listOfFoxes[m].fedLevel<0){
                                    listOfFoxes[m].alive=false;
                                }
                            }
                        }
                    }
                }
            }
        }
//updating the rabbitTotal
numberRabbitsTotal = endrabbit;

//writing to file
cout<<"after foxes eat rabbits\n";
outFile<<"after foxes eat rabbits\n";
PrintGrids(foxBoard, rabbitBoard, cout, numRows, numCols);
PrintGrids(foxBoard, rabbitBoard, outFile, numRows, numCols);


for(int m=1;m<numberFoxesTotal;m++){
        //direction from 1 to 7
                    int dir = rand()%7;
                //what to add to the fox's x coordinate and fox's y coordinate
                    int x,y;
                    if(dir==0){
                    x = 0;
                    y = 1;
                    }
                    else if(dir==1){
                    x = 1;
                    y = 1;
                    }
                    else if(dir==2){
                    x = 1;
                    y = 0;
                    }
                    else if(dir==3){
                    x = 1;
                    y = -1;
                    }
                    else if(dir==4){
                    x = 0;
                    y = -1;
                    }
                    else if(dir==5){
                    x = -1;
                    y = -1;
                    }
                    else if(dir==6){
                    x = -1;
                    y = 0;
                    }
                    else if(dir==7){
                    x = -1;
                    y = 1;
                    }
                    int xcheck = listOfFoxes[m].xIndex;
                    int ycheck = listOfFoxes[m].xIndex;
        //check block has some fox
        if(foxBoard[xcheck][ycheck]>0){
                    if(0<listOfFoxes[m].xIndex&&listOfFoxes[m].xIndex<numCols&&0<listOfFoxes[m].yIndex&&listOfFoxes[m].yIndex<numRows ){
                        int xold = listOfFoxes[m].xIndex;
                        int yold = listOfFoxes[m].xIndex;
                        listOfFoxes[m].xIndex += x;
                        listOfFoxes[m].yIndex += y;
                        foxBoard[xold][yold] -= 1;
                        int xnew = listOfFoxes[m].xIndex;
                        int ynew = listOfFoxes[m].xIndex;
                        foxBoard[xnew][ynew] +=1 ;
                        }
                    }
                }
outFile<<"after foxes move\n";
cout<<"after foxes move\n";
PrintGrids(foxBoard, rabbitBoard, cout, numRows, numCols);
PrintGrids(foxBoard, rabbitBoard, outFile, numRows, numCols);

}
