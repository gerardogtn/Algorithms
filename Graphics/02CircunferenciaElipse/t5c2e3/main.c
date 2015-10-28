#include <graphics.h>
#include <stdio.h>

int ellipsePoints(int x, int y, int puntos[], int i);
int midPointEllipse(int a,int b, int puntos[]);
void generaArchivo(int puntos[], int count);

int main()
{
	int gd=DETECT, gm;
	int x, y;
	
	int puntos[20000];
	int count=0;
	
	printf("Entre la longitud de los ejes (x,y): ");
	scanf("%d,%d", &x, &y);
	
	initgraph(&gd, &gm, NULL);
	
	count = midPointEllipse(x, y, puntos);
	
	generaArchivo(puntos, count);
	
	getch();
	closegraph();
	
	return 0;
}

/* Dibuja los puntos por simetría en los demás cuadrantes */
int ellipsePoints(int x, int y, int puntos[], int i)
{
	int maxx = getmaxx()/2;
	int maxy = getmaxy()/2;
	
	putpixel(maxx+x,maxy+y,WHITE);
	
	puntos[i]=maxx+x;
	puntos[i+1]=maxy+y;
	i+=2;
	
	putpixel(maxx-x,maxy+y,WHITE);
	putpixel(maxx+x,maxy-y,WHITE);
	putpixel(maxx-x,maxy-y,WHITE);
	
	return i;
}

/* Algoritmo MidPointElipse */
int midPointEllipse(int a,int b, int puntos[])
{
	int i = 0;
	double d2;
	int x=0;
	int y=b;
	
	double dl=b*b-(a*a*b)+(0.25*a*a);
	
	putpixel(x,y, WHITE);
	
	while((a*a*(y-0.5))>(b*b*(x+1)))
	{
		if(dl<0)
			dl+=b*b*(2*x+3);
		else
		{
			dl+=b*b*(2*x+3)+a*a*(-2*y+2);
			y--;
		}
		x++;
		
		i = ellipsePoints(x, y, puntos, i);
	}
	
	d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
	
	while(y>0)
	{
		if(d2<0)
		{
			d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
		}
		else
			d2+=a*a*(-2*y+3);
		y--;
		
		i = ellipsePoints(x, y, puntos, i);
	}
	
	return i;
}

/* Guardar los puntos dibujados en un archivo */
void generaArchivo(int puntos[], int count)
{
	FILE *fp;
	
	int i,np;
	
	fp=fopen("puntos.txt","w");

	fprintf(fp,"%s","Los puntos dibujados son:\n");

	np=0;

	for(i = 0; i < count; i += 2)
	{
		fprintf(fp,"(%d, %d) ", puntos[i], puntos[i+1]);

		np++;

		if(np==5) { fprintf(fp,"\n"); np=0; }
	}

	fclose(fp);
}

