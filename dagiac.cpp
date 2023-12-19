#include <stdio.h>
#include <string.h>
#include<cmath>
#include <graphics.h>
#include <stdlib.h>
#include<list>
#include<iostream>
#define MAX 100
#define INPUT "points.inp"

using namespace std;

int enable_click  = 1;
int isDrawPolygon = 0;
//char* listTextHelper[] = 
//	{ 
//		"Please Load File for run demo...", 
//		"Load File Success!", 
//		"Filling the graph using the ScanLine algorithm",
//		"Fill Success", 
//		"Filling the graph using the FloodFill algorithm", 
//		"Please choose color!",
//		"Loading file...",
//	};

//int sizeListTextHelper = sizeof(listTextHelper)/sizeof(*listTextHelper);

struct toado {
    int x;
    int y;
};

int sodinh, xc, yc;
FILE *fp;

struct toado td[MAX]; //moi td la mot kieu toado(x,y)

// khai bao kich thuoc button (chieu cao va chieu rong)
int widthButton = 100, heightButton = 40;

// Khai báo toa do cac button
struct toado buttonLoadFile    = { 30 , 500};
struct toado buttonFloodFill   = { 30 + 100 + 60, 500};
struct toado buttonScanLine    = { 30 + (100 + 60)*2, 500};
struct toado buttonChangeColor = { 30 + (100 + 60)*3, 500};
struct toado buttonAbout       = { 30 + (100 + 60)*4, 500};
//struct toado buttonLoadFile    ={ 610, 10};
//struct toado buttonFloodFill   ={ 610, 70};
//struct toado buttonScanLine    ={ 610, 130};
//struct toado buttonChangeColor ={ 610, 190};
//struct toado buttonAbout       ={ 610, 250};

//------------------------------
void readfile();
void printfpoints(struct toado m[MAX], int size);

//------------- ham doc File-----------------
void readfile() {
    fp = fopen(INPUT, "r");
    if (fp == NULL) { 
        printf("File not found");
        return;
    }

    fscanf(fp, "%d %d %d", &sodinh, &xc, &yc); //doc gia tri tu file la sodinh
    printf("So phan tu can sap xep: %d %d %d\n", sodinh, xc , yc);

    for (int i = 0; i < sodinh; i++) {
        fscanf(fp, "%d %d", &td[i].x, &td[i].y); //doc toa do & in ra ca diem
    }
    
    td[sodinh].x = td[0].x;
    td[sodinh].y = td[0].y;
    
    printfpoints(td, sodinh); //in ra toa do cac diem 
    fclose(fp); 
}
//in ra toa do cua tung diem  
void printfpoints(struct toado m[MAX], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d %d\n", m[i].x, m[i].y); 
    }
}

//to mau ben phai
void FillRight(int xa, int ya)
{ 		
	if(getpixel(xa,ya) == 0) //mau nen la mau den (BLACK) nen ham getpixel tra ve gia tri la 0
	{
	  	putpixel(xa,ya,RED);
	  	//delay(1);
		//to mau het ve phia ben phai
	  	FillRight(++xa,ya);
	  	  
	  	xa--;
	  	  
		//to mau tu diem ke bien den tan cung ben duoi
	  	FillRight(xa,ya+1);
	  	  
	  	//to mau tu diem ke bien den tan cung ben tren
	  	FillRight(xa,ya-1);
	}
		
}

//to mau ben trai
void FillLeft(int xa, int ya)
{ 	
	if(getpixel(xa,ya) == 0) //mau nen la mau den (BLACK) nen ham getpixel tra ve gia tri la 0
	{
	  	putpixel(xa,ya,RED);
	  	//delay(1);
		//to mau het ve phia ben trai
	  	FillLeft(--xa,ya);
	  	  
	  	xa++;
	  	
		//to mau tu diem ke bien den tan cung ben duoi
	  	FillLeft(xa,ya+1);
	  	  
	  	//to mau tu diem ke bien den tan cung ben tren
	  	FillLeft(xa,ya-1);
	}
}

//============= to mau da giac FloodFill =============
void FloodFill()
{ 
  	FillRight(xc,yc);
	FillLeft(xc-1,yc);
}
//============= to mau da giac ScanLine =============
void scanline(){
	setcolor(2);
	float m[100];  //khai bao mang chua hesogoc
	//tinh hesogoc , neu 'dy==0' hsg la 0.0, neu 'dx==0' hsg la 999999
	for(int i=0; i<sodinh; i++){ 
		int dy=td[i+1].y - td[i].y;
		int dx=td[i+1].x - td[i].x;
		if(dy==0){
			m[i]= 0.0;
		}
		if(dx==0){
			m[i]=999999;
		}
		m[i]=(float)dy/dx;
	}
		
	for(int i=0; i<sodinh; i++){
		printf("%.1f  ", m[i]); //in ra he so goc
	}
	
	int ymin= td[0].y;
	int ymax= td[0].y;
	
	// tim ymax & ymin
	for(int i=1; i<sodinh; i++){
		if(ymin > td[i].y){
			ymin = td[i].y;
		}
		if(ymax < td[i].y){
			ymax = td[i].y;
		}		
	}
	
	printf("\nYmax = %d", ymax);
	printf("\nYmin = %d\n", ymin);
	
	// to mau do thi tu ymin -> ymax
	for(int y=ymin; y<=ymax; y++){
		int xgd[100];
		int dem=0; //dem so luong diem cat
		for(int i=0; i<sodinh; i++){
			if((y<td[i].y && y>=td[i+1].y)||(y>=td[i].y && y<td[i+1].y)){
				xgd[dem++]=round(td[i].x + (float)(y-td[i].y)/m[i]);
				printf("    (%d, %d)", xgd[dem-1],y);
			}
					
			for(int i=0; i<=dem; i++){
				printf("(%d, %d)\n", xgd[i],y);
			}
			for(int i=0; i<dem-1; i=i+2){
				line(xgd[i],y,xgd[i+1],y);
				delay(1);
			}
		}
	}
}
void vedagiac(){
	setcolor(15);
	for(int i=0; i<sodinh; i++){
		line(td[i].x,td[i].y,td[i+1].x,td[i+1].y);
	}
} 

// ========= Text Helper
void drawTextHelper(char text[],bool display,  bool isSuccess){
	// clear text in screen
	setcolor(display? isSuccess? 2: 15   : 0);
	settextstyle(2,0,7);
	outtextxy( 50,570,text);
}
//void drawTextHelper(int index, int isSuccess){
//	// clear text in screen
//	setcolor(0);
//	settextstyle(2,0,7); 
//	for (int i=0; i<  sizeListTextHelper; i++ ){		
//		outtextxy( 50,570,listTextHelper[i]);
//	}
//	// display new text
//	setcolor(isSuccess? 2: 15);
//	settextstyle(2,0,7);
//	outtextxy( 50,570,listTextHelper[index]);
//}

void colorPicker(bool isDisplay){
	int x = 10, y = 600;
	int width = 30, height = 30;
	int space = 10;
	for (int i=1; i<= 15; i++){
		setcolor(isDisplay? i : 0);
		setlinestyle(0,1,3);
		rectangle(x + (space + width) *(i-1), y , (x+ width) + (space + width) *(i-1) ,(y + height) );
//		circle(x + (space + width) *(i-1), y , 10);
	}
}
void displayAbout(bool isDisplay){
	setcolor(isDisplay? 15 : 0);
	settextstyle(2,0,7);
	outtextxy( 50,580,"DO AN TTCS: MO PHONG THUAT TOAN TO MAU DO THI");
	outtextxy( 50,610,"GVHD:  Nguyen Khac Cuong");
	outtextxy( 50,640,"SVTH:  Nguyen Thi Teo Ty Toe");
	outtextxy( 50,670,"MSSV:  123456789");
	
	setlinestyle(0,1,3);
	rectangle(40,570, 600,700);
}

//=========== Ve border va cac Button ======================
void veUI(){
	//--------- ve border --------------
	setcolor(15);
	setlinestyle(0,1,3);
	rectangle(10,10, 800,480);
	
	setcolor(15);
	
	//-------Load File Button
	rectangle(buttonLoadFile.x,buttonLoadFile.y, buttonLoadFile.x + widthButton,buttonLoadFile.y + heightButton);
	settextstyle(2,0,7);
	outtextxy(buttonLoadFile.x + 10 ,buttonLoadFile.y + 10,"Load File");
	
	setcolor(isDrawPolygon == 1? 15: 8);
	//----------Flood Fill Button
	rectangle(buttonFloodFill.x,buttonFloodFill.y, buttonFloodFill.x + widthButton,buttonFloodFill.y + heightButton);
	settextstyle(2,0,7);
	outtextxy(buttonFloodFill.x + 10,buttonFloodFill.y + 10,"Flood Fill");
	
	//----------Starting Button
	rectangle(buttonScanLine.x,buttonScanLine.y, buttonScanLine.x + widthButton,buttonScanLine.y + heightButton);
	settextstyle(2,0,7);
	outtextxy(buttonScanLine.x + 10,buttonScanLine.y + 10,"Scan Line");
	
	setcolor(15);
	//----------Change Color Button
	rectangle(buttonChangeColor.x,buttonChangeColor.y, buttonChangeColor.x + widthButton,buttonChangeColor.y + heightButton);
	settextstyle(2,0,7);
	outtextxy(buttonChangeColor.x + 25,buttonChangeColor.y + 10,"Color");
	
	//----------About Information Button
	rectangle(buttonAbout.x,buttonAbout.y, buttonAbout.x + widthButton,buttonAbout.y + heightButton);
	settextstyle(2,0,7);
	outtextxy(buttonAbout.x + 25,buttonAbout.y + 10,"About");
}

//====================== Bat Su kien click chuot=========================
void mouse(){
	int x_mouse;
	int y_mouse;
	
	bool isDisplayAbout = false;
	bool isDisplayColor = false;
	
	char textHelper[] = "Please Load File for run demo...";
	drawTextHelper(textHelper, true, false);
	
	while(enable_click){
		//get even mouse click
		if(ismouseclick(WM_LBUTTONDOWN)){
			//get position of mouse
			getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
			//print x,y mouse to console
			printf("(%d,%d)",x_mouse,y_mouse);
			//checking for buttons
			if(x_mouse > buttonLoadFile.x && x_mouse <( buttonLoadFile.x + widthButton ) 
				&& y_mouse > buttonLoadFile.y && y_mouse < (buttonLoadFile.y + heightButton))
			{//load file button
				//read from file
				cleardevice();
				
				strcpy(textHelper, "File loading...");
				drawTextHelper(textHelper, true, false);
				isDrawPolygon = 1;
				veUI();
				readfile();
				vedagiac();
				
				strcpy(textHelper, "Load File Success!");
				drawTextHelper(textHelper, true, true);
			}
			// FloodFill
			if(x_mouse > buttonFloodFill.x && x_mouse < (buttonFloodFill.x + widthButton) 
			&& y_mouse > buttonFloodFill.y && y_mouse < (buttonFloodFill.y + heightButton))
			{//load file button
				if (isDrawPolygon){
					cleardevice();
					
					strcpy(textHelper, "Filling the graph using the ScanLine algorithm...");
					drawTextHelper(textHelper, true, false);
					veUI();
					printf("Running FloodFill ...");

					vedagiac();
					FloodFill();
					
					drawTextHelper(textHelper, false, false);
					strcpy(textHelper, "Fill Success!");
					drawTextHelper(textHelper, true, true);	
				}
			}
			//checking for buttons Scanline
			if(x_mouse > buttonScanLine.x && x_mouse < (buttonScanLine.x + widthButton) 
			&& y_mouse > buttonScanLine.y && y_mouse < (buttonScanLine.y + heightButton))
			{//fill  Scanline
				if (isDrawPolygon){
					cleardevice();
					
					strcpy(textHelper, "Filling the graph using the FloodFill algorithm....");
					drawTextHelper(textHelper, true, false);
					
					veUI();

					vedagiac();
					printf("Running Scanline ...");
					scanline();	
					
					drawTextHelper(textHelper, false, false);
					strcpy(textHelper, "Fill Success!");
					drawTextHelper(textHelper, true, true);
				}
			}
			
			if(x_mouse > buttonChangeColor.x && x_mouse < (buttonChangeColor.x + widthButton) 
			&& y_mouse > buttonChangeColor.y && y_mouse < (buttonChangeColor.y + heightButton))
			{
				if (isDisplayAbout) displayAbout(false);
								
				drawTextHelper(textHelper, false, false);
				strcpy(textHelper, "Please choose color..");
				drawTextHelper(textHelper, true, false);
				
				colorPicker(true);
				isDisplayColor = true;
			}
			
			if(x_mouse > buttonAbout.x && x_mouse < (buttonAbout.x + widthButton) 
			&& y_mouse > buttonAbout.y && y_mouse < (buttonAbout.y + heightButton))
			{
				if (isDisplayColor)  colorPicker(false);
				
				drawTextHelper(textHelper, false, false);
				displayAbout(true);
				isDisplayAbout= true;
			}
		}
		//check right mouse click to exit loop
		if(ismouseclick(WM_RBUTTONDOWN)){
			getmouseclick(WM_RBUTTONDOWN,x_mouse,y_mouse);
			printf("\nExiting...");
			break;
		}
		delay(1000);//wait for next cycle mouse click
	}
}

//chuong trinh chinh 
int main() {
    initwindow(820,750);
    veUI();
	mouse();
    getch();
    return 0;
}

