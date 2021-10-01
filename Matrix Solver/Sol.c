#include<stdio.h>
void columnSwap(int n,float a[][n],int m,float b[],int i,int j)
{
	float temp;
	int k,l;
	for(k=0;k<m;k++)
	{
		temp = a[k][i];
		a[k][i] = a[k][j];
		a[k][j] = temp;
	}
	printf("\n\nC%d<-->C%d\n\n",i,j);
	for(k=0;k<m;k++){
		for(l=0;l<n;l++)
			printf("%8.1f ",a[k][l]);
		printf("%16.1f ",b[k]);	
		printf("\n");
	}
}
void rowSwap(int n,float a[][n],int m,float b[],int i,int j)
{
	float temp;
	int k,l;
	for(k=0;k<n;k++)
	{
		temp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = temp;
	}
	temp = b[i];
	b[i] = b[j];
	b[j] = temp;
	printf("\n\nR%d<-->R%d\n\n",i,j);
	for(k=0;k<m;k++){
		for(l=0;l<n;l++)
			printf("%8.1f ",a[k][l]);
		printf("%16.1f ",b[k]);	
		printf("\n");
	}
}
void rowOperation(int n,float a[][n],int m,float b[],int pivot_row,int modify_row,float l){
	int k,i,j;
	for(k=0;k<n;k++){
		a[modify_row][k]-= l*a[pivot_row][k];	
		if((int)(a[modify_row][k]*(1000))==0)
			a[modify_row][k] = 0;	
	}
	b[modify_row]-= l*b[pivot_row];
	if((int)(b[modify_row]*(100))==0)
		b[modify_row] = 0;
	printf("\n\nR%d = R%d - (%f)*(R%d)\n\n",modify_row,modify_row,l,pivot_row);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%8.1f ",a[i][j]);
		printf("%16.1f ",b[i]);	
		printf("\n");
	}
}
int rref(int n,float a[][n],int m,float b[]){
	int i,j=0,k,flag,pivot=0;
	for(i=0;i<m,j<n;i++){
		flag = 0;
		if(a[i][j]==0){
			for(k=i+1;k<m;k++){
				if(a[k][j]==0)
					continue;
				else{
					flag = 1;
					rowSwap(n,a,m,b,i,k);	
					break;
				}
			}
		}
		else flag = 1;
		if(flag == 0){
			i--;
			j++;
			continue;
		}
		float l;
		int count=0;
		for(k=i+1;k<m;k++){
			l = a[k][j]/a[i][j];
			rowOperation(n,a,m,b,i,k,l);
			count++;
		}
		if(count>0) pivot++;
		j++;
		if(m<n){
			if(j>=n-1||i>=m-1)
			break;
		}
		if(m>=n){
			if(j>n-1||i>m-1)
			break;
		}
	}
	j--;
	if(m<=n){
		if(a[i][j]!=0)
		pivot++;
	}
	int x,y;
	y=j;
	for(x=i;x>=0,y>=0;x--){
		flag = 0;
		if(a[x][y]==0) flag=0;
		else flag = 1;
		if(flag == 0){
			x++;
			y--;
			continue;
		}
		float l;
		for(k=x-1;k>=0;k--){
			l = a[k][y]/a[x][y];
			rowOperation(n,a,m,b,x,k,l);
		}
		for(k=0;k<n;k++){
			a[x][k] = a[x][k]/a[x][y];
		}
		b[x]/=a[x][y];
		y--;	
	}
	return pivot;
}
int main(){
	int flag = 1;
	int m,n;
	printf("Ax = b\n\n");
	while(flag==1){
		printf("Enter m and n for an mxn matrix A:\nm = ");
		scanf("%d",&m);
		printf("n = ");
		scanf("%d",&n);
		if(m<=0||n<=0) printf("Invalid dimensions!!!\n");
		else flag=0;
	}
	float a[m][n];
	printf("Enter the elements of the matrix A row wise:\n\n");
	int i,j,rank;
	for(i=0;i<m;i++){
		printf("Row %d:\n",i+1);
		for(j=0;j<n;j++)
			scanf("%f",&a[i][j]);	
	}
	printf("\nThe final matrix A is:\n\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%8.1f ",a[i][j]);
		printf("\n");	
	}
	float b[m];
	printf("\nEnter the elements of mx1 matrix B row wise:\n\n");
	for(i=0;i<m;i++){
		printf("Row %d:",i+1);
		scanf("%f",&b[i]);	
	}
	printf("\nThe final matrix b is:\n\n");
	for(i=0;i<m;i++){
		printf("%8.1f \n",b[i]);
	}
	rank = rref(n,a,m,b);
	printf("\n\nRow Reduced Echelon form matrix:\n\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			printf("%8.1f ",a[i][j]);
		printf("%16.1f ",b[i]);	
		printf("\n");	
	}
	int solflag=0,solflag2=0;
	if(rank==m && rank<n)
		printf("The given system of equations has infinite solutions");
	if(rank<m && rank==n){
		for(i=m;i>n;i--){
			if(b[i]!=0){
				solflag=1;
				break;	
			}
		}
		if(solflag==1)
			printf("The given system of equations has no solution");
		else{
			printf("The given system of equations has unique solution\n");
			solflag2=1;
		} 
	}	
	if(rank<m && rank<n){
		for(i=m;i>rank;i--){
			if(b[i]!=0){
				solflag=1;
				break;	
			}
		}
		if(solflag==1)
			printf("The given system of equations has no solution");
		else{
			printf("The given system of equations has infinite solutions");
		} 
	}
	if(rank==m && rank==n){
		printf("The given system of equations has unique solution\n");		
		solflag2=1;
	}
	if(solflag2==1){
		for(i=0;i<rank;i++){
			printf("x%d = %f\n",(i+1),b[i]);
		}
	}	
}
