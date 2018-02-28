/*-----------------------------------------------------------------
-                       CprE 489 Lab 3 - CRC
-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-----------------------------------------------------------------
-                       Memory Constants
-----------------------------------------------------------------*/
static long M = 2147483647;
/*----------------------------------------------------------------
-                          Global Variables
-----------------------------------------------------------------*/
unsigned char *userInput;
static unsigned char *generatorPoly;
//uint32_t gPoly;
int size;
#define bufferSize 32
/*----------------------------------------------------------------
-                          Procedures
-----------------------------------------------------------------*/
char* LongDivision(char *Px);
void XORalg(char *Px);
void leftShift(char *Px);
char* ex2LongDivision(char *Px, char *Gx);
void ex2XORalg(char *Px, char *Gx);

void IntroduceError( char *data, double p )
{
	char *pointer = data;

	while ( *pointer != '\0' )
   	{
		if ( ( (double)random() / M ) <= p )
		{
		    *pointer = ( *pointer == '0' ) ? '1' : '0';
		}
		pointer++;
	}
}

void inputData(){
	printf("enter 16 1s or 0s. Any extra characters entered will be ignored\n");
	userInput = calloc(bufferSize, sizeof(char));
	bool exitBool = false;
	int i = 0;
	int temp;
	while((temp = getchar()) != EOF && exitBool == false){ //temp !='\n' && 
		if(temp == '1' || temp == '0'){
			userInput[i] = temp;
			i++;
		}
		if(i > 15){
			exitBool = true;
			break;
		}
	}
	printf("Collection Complete\nUser Input: ");
	int j = 0;
	for(j =0; j < 16; j++){
		printf("%c", userInput[j]);
	}
	printf("\n");
}

/*uint32_t crcAlgorithm(unsigned char* data, uint32_t poly){
	
}*/

int main(int argc, char** argv){
	double BER;
	if(argc > 1){
		sscanf(argv[1], "%lf", &BER);
		printf("%lf\n", BER);
	}else{
		printf("Bit Error Rate Not Entered");
		return 1;
	}
	inputData();
	//double ber = argv[0];

	//Generator polynomial
	IntroduceError(userInput, BER);
	generatorPoly = "10001000000100001";
	int i;
	for(i = 16; i < 32; i++){
		userInput[i] = '0';
	}
	printf("Input with errors: ");
	for(i = 0; i < 32; i++){
		printf("%c", userInput[i]);
	}
	printf("\n");
	char *Codeword;
	Codeword = (char *) malloc(16);
	Codeword = LongDivision(userInput);

//delete this
	userInput = "00000001000100000010000100000000";
	printf("Error Pattern: ");
	for(i = 0; i < 32; i++){
		printf("%c", userInput[i]);
	}
	printf("\n");
	printf("codeword: ");
	for(i = 0; i < 16; i++){
		printf("%c", Codeword[i]);
	}
	printf("\n");
	char *Final;
	Final = (char *) malloc(16);
	Final =	ex2LongDivision(userInput, Codeword);
	printf("Final: ");
	for(i = 0; i < 16; i++){
		printf("%c", Final[i]);
	}
	printf("\n");
	return 0;
//don't delete
/*
	char *cwAppend;
	cwAppend = (char *) malloc(32);
	for(i = 0; i < 16; i++){
		cwAppend[i] = userInput[i];
		cwAppend[i+16] = Codeword[i];
	}
	printf("Codeword appended: ");
	for(i = 0; i < 32; i++){
		printf("%c", cwAppend[i]);
	}
	printf("\n");	
	char *Final;
	Final = (char *) malloc(16);
	Final = LongDivision(cwAppend);
	printf("Final: ");
	for(i = 0; i < 16; i++){
		printf("%c", Final[i]);
	}
	printf("\n");
	return 0; */
}

char* LongDivision(char *Px){
	char *temp;
	temp = (char *) malloc(32);
	int i;
	for(i = 0; i < 32; i++){
		temp[i] = Px[i];
	}
	size = 32; 

	while(size > 16){

		if(temp[0] == '1'){
			XORalg(temp);
		}else{
			leftShift(temp);
			size--;
		}
	}
	return temp;
}

void XORalg(char *Px){
	int i;
	for(i = 0; i < 17; i++){
		if(Px[i] == '1' || generatorPoly[i] == '1'){
			if(Px[i] == '1' && generatorPoly[i] == '1'){
				Px[i] = '0';
			}else{
				Px[i] = '1';
			}
		}else{
			Px[i] = '0';
		}
	}
	/*for(i = 0; i < size; i++){
		printf("%c", Px[i]);
	}
	printf("\n"); */
	return;
}

void leftShift(char *Px){
	int i;
	for(i = 0; i < size - 1; i++){
		Px[i] = Px[i + 1];
	}
	for(i = size - 1; i < 32; i++){
		Px[i] = '0';
	}
	return;
}	



char* ex2LongDivision(char *Px, char *Gx){
	char *temp;
	temp = (char *) malloc(32);
	int i;
	for(i = 0; i < 32; i++){
		temp[i] = Px[i];
	}
	size = 32; 

	while(size > 16){

		if(temp[0] == '1'){
			ex2XORalg(temp, Gx);
		}else{
			leftShift(temp);
			size--;
		}
	}
	return temp;
}

void ex2XORalg(char *Px, char *Gx){
	int i;
	for(i = 0; i < 17; i++){
		if(Px[i] == '1' || generatorPoly[i] == '1'){
			if(Px[i] == '1' && generatorPoly[i] == '1'){
				Px[i] = '0';
			}else{
				Px[i] = '1';
			}
		}else{
			Px[i] = '0';
		}
	}
/*	for(i = 0; i < size; i++){
		printf("%c", Px[i]);
	}
	printf("\n"); */
	return;
}




/*
	char *ErrorPattern;
	ErrorPattern = (char *) malloc(32);
	ErrorPattern = "00000001000100000010000100000000";
	for(i = 0; i < 16; i++){
		generatorPoly[i] = Codeword[i];
	}
	Final = LongDivision(ErrorPattern);
*/








