// Assignment 3 
// COLORED IMAGES FILTERS (BONUS)
// Name:Ismail Magdy Ismail , ID=20210069 , Group:A , Section:25/26
// Name:Abdallah Khaled     , ID=20210216 , Group:A , Section:25/26
// Name:Basel Ayman Saleh   , ID=20210084 , Group:A , Section:25/26


// Final Phase (12 Filters): 

// Colored Images (BONUS)

// 1-Black & White Filter
// 2-Invert Filter
// 3-Flip Image
// 4-Rotate Image
// 5-Mirror Image
// 6-Shuffle Image
// 7-Blur Image
// 8-Enlarge Image
// 9-detect Edges
// 10-Darken or lighten Image
// 11-Merge with another Image
// 12-Shrink Image

//---------------------------------------

#include <iostream>
#include <cmath>
#include "bmplib.cpp"
#define unchar unsigned char
using namespace std;



unchar image[SIZE][SIZE][RGB];



// (Control / Menu)  functions 
void save_image();
void menu();
void check_choice();
void load_image(unchar image[SIZE][SIZE][RGB]);


// Filters main Functions 
void black_and_white(unchar image[SIZE][SIZE][RGB]);
void invert_filter(unchar image[SIZE][SIZE][RGB]);
void flip_image(unchar image[SIZE][SIZE][RGB]);
void rotate_image(unchar  image[SIZE][SIZE][RGB]);
void mirror_image(unchar  image[SIZE][SIZE][RGB]);
void shuffle_image(unchar  image[SIZE][SIZE][RGB]);
void blur_image(unchar  image[SIZE][SIZE][RGB]);
void enlarge_image(unchar  image[SIZE][SIZE][RGB]);
void detect_edges(unchar  image[SIZE][SIZE][RGB]);
void darken_or_lighten(unchar  image[SIZE][SIZE][RGB]);
void merge_image(unchar  image[SIZE][SIZE][RGB]);
void shrink_image(unchar image[SIZE][SIZE][RGB]);


// sub Functions (2d Array Manipulation / Kernels)
void transpose(unchar image[SIZE][SIZE][RGB]);
void copy_left(unchar image[SIZE][SIZE][RGB]); 
void copy_right(unchar image[SIZE][SIZE][RGB]); 
void copy_upper(unchar image[SIZE][SIZE][RGB]) ;
void copy_down(unchar image[SIZE][SIZE][RGB]) ;
void quarters(unchar q1[SIZE/2][SIZE/2][3],unchar q2[SIZE/2][SIZE/2][3],
unchar q3[SIZE/2][SIZE/2][3],unchar q4[SIZE/2][SIZE/2][3]);
void rearrange(unchar array[SIZE/2][SIZE/2][RGB],const int& current_quarter);
void kernel_sum(const int& row,const int& coulmn,unchar copy[256][256][RGB]);
void quarter(unsigned char array[SIZE/2][SIZE/2][RGB],const int& order);
void repeat_pixels(unchar quarter[SIZE/2][SIZE/2][RGB]);
void laplacian(const int& row,const int& coulmn,unchar copy[256][256][RGB]);
void reduce_image(unchar image[SIZE][SIZE][RGB],const int& ratio);

int main()
{

    while(true)
    {
        load_image(image);
        menu();
        check_choice();
    }    
}

//---------------------------------------

void load_image(unchar array[SIZE][SIZE][RGB])
{
    // Adding extinstion .bmp to the picture (file) name
    char file_name[100];
    cout<<"Enter the name of the (colored) picture  : ";
    cin>>file_name;

    strcat(file_name,".bmp");
   readRGBBMP(file_name, array);
}

//---------------------------------------

void save_image()
{
    //adding ".bmp" and saving picture
    char file_name[100];
    cout<<"Enter the target image file name:";
    cin>>file_name;
    strcat(file_name,".bmp");
    writeRGBBMP(file_name, image);
}

//---------------------------------------

void menu()
{
    // display filters list
    cout<<"Choose The filter you want to add\n";
    cout<<"1-Black & White Filter\n";
    cout<<"2-Invert Filter\n";
    cout<<"3-Flip Image\n";
    cout<<"4-Rotate Image\n";
    cout<<"5-Mirror Image\n";
    cout<<"6-Shuffle Image\n";
    cout<<"7-Blur Image\n";
    cout<<"8-Enlarge Image\n";
    cout<<"9-Detect Edges in Image\n";
    cout<<"10-Darken OR lighten Image\n";
    cout<<"11-Merge With another Image\n";
    cout<<"12-Shrink Image\n";
    cout<<"0-Exit\n";
}

//---------------------------------------

void black_and_white(unchar image[SIZE][SIZE][RGB])
{
    // make all the pixels white and black only
    // if the pixel is dark then we change it to a darker pixel
    // if the pixel is light then we change it to lighter pixel 
  
       for (int i = 0; i < 256; i++)
       {
           for (int j = 0; j < 256; j++)
           {
                if(image[i][j][0]+image[i][j][1]+image[i][j][2]>382)
                {
                    image[i][j][0]=255;
                    image[i][j][1]=255;
                    image[i][j][2]=255;
                }
                else
                {
                    image[i][j][0]=0;
                    image[i][j][1]=0;
                    image[i][j][2]=0;
                }
           }
       }
}

//---------------------------------------

void  invert_filter(unchar image[SIZE][SIZE][RGB])
{
    // inverting each pixel
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
           image[i][j][0]=255-image[i][j][0];
           image[i][j][1]=255-image[i][j][1];
           image[i][j][2]=255-image[i][j][2];
        }        
    }
    
}

//---------------------------------------


void flip_image(unchar image[SIZE][SIZE][RGB])
{
    int choice ;
    cout<<"choose the filter you want to add\n";
    cout<<"1-horizontally\n";
    cout<<"2-vertically\n";
    cin>>choice; 
    // check if the user input is valid
    while (choice!=1&&choice!=2)
    {
      cout<<"invalid option , choose  again:";
      cin>>choice;
    }

    // flipping verically by swapping the first pixel with the last pixel and so on..

    if(choice==2)
    {
        for (int i = 0; i < 256; i++)
        {
           for (int j = 0; j < 256/2; j++)
           {
               swap(image[i][j][0],image[i][255-j][0]) ;
               swap(image[i][j][1],image[i][255-j][1]) ;
               swap(image[i][j][2],image[i][255-j][2]) ;

           }
           
        }
    }

    // flipping horizonatlly by swapping the top pixel with the bottom pixel and so on..

    else if(choice==1)
    {
        for (int i = 0; i < 256/2; i++)
        {
           for (int j = 0; j < 256; j++)
           {
                swap(image[i][j][0],image[255-i][j][0]);
                swap(image[i][j][1],image[255-i][j][1]);
                swap(image[i][j][2],image[255-i][j][2]);

           }
           
        }
    }
}

//---------------------------------------

void rotate_image(unchar image[SIZE][SIZE][RGB])
{
    int choice ;
    cout<<"1-Rotate 90º\n";
    cout<<"2-Rotate 180º\n";
    cout<<"3-Rotate 270º\n";
    cin>>choice;

    // check if the user input is valid

    while(choice!=1&&choice!=2&&choice!=3)
    {
        cout<<"Invalid choice ,Choose again\n";
        cin>>choice;
    }
    // Rotating image by 90º or 180 or 270.

    if(choice==1)
    {
       transpose(image);
    }
    else if(choice==2)
    {
        for (int i = 0; i < 2; i++)
        {
            transpose(image);
        }
        
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
           transpose(image);
        }
        
    }
}

//---------------------------------------

void mirror_image(unchar image[SIZE][SIZE][RGB])
{
    int choice ;
    cout<<"Choose the side your want to mirror:\n";
    cout<<"1-Left Side\n";
    cout<<"2-Right Side\n";
    cout<<"3-Upper Side\n";
    cout<<"4-Down Side\n";
    cin>>choice;

    // check if the user input is valid

    while(choice!=1&&choice!=2&&choice!=3&&choice!=4)
    {
        cout<<"Invalid side , Choose another one:";
        cin>>choice;
    }

    // mirror the left side or Right side or upper or lower

    if(choice==1)
    {
        copy_left(image);
    }
    else if(choice==2)
    {
        copy_right(image);
    }
    else if(choice==3)
    {
        copy_upper(image);
    }
    else
    {
        copy_down(image);
    }
    
}

//---------------------------------------

void shuffle_image(unchar image[SIZE][SIZE][RGB])
{
    // Taking the new order of quarters
    int choice[4];
    cout<<"Enter the New order of quarters ? ";
    for (int i = 0; i < 4; i++)
    {
       cin>>choice[i];

       //validating the users new order of quarters

       while (choice[i]>4||choice[i]<1)
        {
            cout<<"invalid order/quarter ,input should be numbers from[1-4] only , Enter a valid order:";
            cin>>choice[i];
        }
    }
    unchar quarter1[128][128][3];
    unchar quarter2[128][128][3];
    unchar quarter3[128][128][3];
    unchar quarter4[128][128][3];
    // making 4 arrays storing each storing a quarter
    quarters(quarter1,quarter2,quarter3,quarter4);

    // counter that keeps track of the current quarter to copy to
    int current_quarter=1;

    for (int i = 0; i <4; i++)
    {
        if(choice[i]==1)
        {
            rearrange(quarter1,current_quarter);
        }
        else if(choice[i]==2)
        {
            rearrange(quarter2,current_quarter);
        }
        else if(choice[i]==3)
        {
            rearrange(quarter3,current_quarter);
        }
        else
        {
            rearrange(quarter4,current_quarter);
        }

        // counter that keeps track of which quarter to copy to
        current_quarter++;
    }
    
}

//---------------------------------------

void blur_image(unchar image[SIZE][SIZE][RGB])
{
    // using the AVG  blur teqchniue to blur each pixel

    // Making a copy to hold the pixels weights temporarily to be copied later to the original image

    unsigned char copy[SIZE][SIZE][RGB];

    for (int i = 0; i < 256; i++)
    {
       for (int j = 0; j < 256; j++)
       {
          kernel_sum(i,j,copy);
       }
       
    }

    // Copying the Wights of each pixel to the Orignal Image

    for (int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            image[i][j][0]=copy[i][j][0];
            image[i][j][1]=copy[i][j][1];
            image[i][j][2]=copy[i][j][2];

        }
    }
    
}

//---------------------------------------

void enlarge_image(unchar image[SIZE][SIZE][RGB])
{
    cout<<"choose The quarter you Want to Enlarge {1,2,3,4} : ";
    int choice ;cin>>choice;

    //validating user's input

    while(choice<0||choice>4)
    {
        cout<<"Invalid quarter choose a quarter from [1-4] :";
        cin>>choice;
    }

    unsigned char  enlarged_quarter[128][128][RGB];

    if(choice==1)
    {
        quarter(enlarged_quarter,1);
        repeat_pixels(enlarged_quarter);
    }
    else if(choice==2)
    {
        quarter(enlarged_quarter,2);
        repeat_pixels(enlarged_quarter);
    }
    else if(choice==3)
    {
        quarter(enlarged_quarter,3);
        repeat_pixels(enlarged_quarter);
    }
    else
    {
        quarter(enlarged_quarter,4);
        repeat_pixels(enlarged_quarter);
    }
}

//---------------------------------------

void detect_edges(unchar image[SIZE][SIZE][RGB])
{

    unchar copy[256][256][RGB];

    // using laplacian technique to detect edges  and copying values to an extranal array 

    for (int i = 0; i < 256; i++)
    {
      for(int j = 0; j < 256; j++)
      {
          laplacian(i,j,copy);
      }
    }
    
    // Copying the Wights of each pixel to the Orignal Image
    
    for (int i = 0; i < 256; i++)
    {
      for(int j = 0; j < 256; j++)
      {
          image[i][j][0]=copy[i][j][0];
          image[i][j][1]=copy[i][j][1];
          image[i][j][2]=copy[i][j][2];
      }
    }

    // using the Invert filter to revert the image 

    invert_filter(image);

    // darkining the edges to be more Visible

    for(int i=0; i < 256; i++)
    {
        for (int j = 0; j< 256; j++)
        {
            
        }
        
    }
}

//---------------------------------------


void darken_or_lighten(unchar image[SIZE][SIZE][RGB])
{
    int choice;
    cout<<"1-Darken\n";
    cout<<"2-Lighten\n";
    cout<<"Enter your choice :";
    cin>>choice;
    
    //validating user's input

    while (choice>2||choice<1)
    {
        cout<<"invalid choice ,choose  another one [1 OR 2]:";
    }

    int factor ;
    // Detirmne whether to lighten or darken the pixels according to input 
    if(choice==1)
    {
        factor=-1;
    }
    else
    {
        factor=1;
    }
        for (int i = 0; i < 256; i++)
        {
            for (int j= 0; j < 256; j++)
            {
                if(image[i][j][0]+(65*factor)>=0&&image[i][j][0]+(65*factor)<256)
                {
                    image[i][j][0]+=(65*factor);
                }
                else
                {
                    if(image[i][j][0]<0)
                    {
                        image[i][j][0]=0;
                    }
                    else if(image[i][j][0]>255)
                    {
                        image[i][j][0]=255;
                    } 
                }
                if(image[i][j][1]+(65*factor)>=0&&image[i][j][1]+(65*factor)<256)
                {
                    image[i][j][1]+=(65*factor);
                }
                else
                {
                    if(image[i][j][1]<0)
                    {
                        image[i][j][1]=0;
                    }
                    else if(image[i][j][1]>255)
                    {
                        image[i][j][1]=255;
                    }
                }
                if(image[i][j][2]+(65*factor)>=0&&image[i][j][2]+(65*factor)<256)
                {
                    image[i][j][2]+=(65*factor);
                }
                else
                {
                    if(image[i][j][2]<0)
                    {
                        image[i][j][2]=0;
                    }
                    else if(image[i][j][2]>255)
                    {
                        image[i][j][2]=255;
                    }
                    
                }
            }   
        }
}

//---------------------------------------

void merge_image(unchar image[SIZE][SIZE][RGB])
{
    // loading the other Image to Merge With.
   unchar array[SIZE][SIZE][RGB];
    load_image(array);
    for (int i = 0; i < 256; i++)
    {
        for(int j=0 ; j<256; j++)
        {
            image[i][j][0] =(image[i][j][0]+array[i][j][0])/2;
            image[i][j][1] =(image[i][j][1]+array[i][j][1])/2;
            image[i][j][2] =(image[i][j][2]+array[i][j][2])/2;

        }

    }
    
}
//---------------------------------------

void shrink_image(unchar image[SIZE][SIZE][RGB])
{
    int choice = 0;
    // getiing tha ratio to shrink with

    cout<<"Shrink to (1/2) or (1/3) or (1/4)\n";
    cout<<"1-(1/2)\n";
    cout<<"2-(1/3)\n";
    cout<<"3-(1/4)\n";
    cout<<"Enter your choice :";
    cin>>choice;
    
    //validating input

    while(choice>4||choice<1)
    {
        cout<<"invalid input,choose again :";
    }

    if(choice==1)
    {
        reduce_image(image,2);
    }
    else if(choice==2)
    {
        reduce_image(image,3);
    }
    else
    {
        reduce_image(image,4);
    }
}

//---------------------------------------

void check_choice()
{
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;

    // check if the user input is valid

    while (choice < 0||choice > 12)
    {
        cout<<"invalid filter choice , try another :";
        cin>>choice;
    }

    //call the function that performs this filter function

    if(choice == 0)
    {
        exit(0);
    }
    else if(choice == 1)
    {
        black_and_white(image);
        save_image();
    }
    else if(choice == 2)
    {
        invert_filter(image);
        save_image();
    }
    else if(choice == 3)
    {
        flip_image(image);
        save_image();
    }
    else if(choice == 4)
    {
        rotate_image(image);
        save_image();
    }
    else if(choice == 5)
    {
        mirror_image(image);
        save_image();
    }
    else if(choice == 6)
    {
        shuffle_image(image);
        save_image();
    }
    else if(choice == 7)
    {
        blur_image(image);
        save_image();
    }
    else if(choice == 8)
    {
       enlarge_image(image);
       save_image();
    }
    else if(choice == 9)
    {
        detect_edges(image);
        save_image();
    }
    else if(choice == 10)
    {
        darken_or_lighten(image);
        save_image();
    }
    else if(choice ==11)
    {
        merge_image(image);
        save_image();
    }
    else if(choice == 12)
    {
        shrink_image(image);
        save_image();
    }
}

//---------------------------------------

void transpose(unchar image[SIZE][SIZE][RGB])
{
    // switch each row of pixels with each coulmn 

    unchar array[SIZE][SIZE][RGB];
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j <256 ; j++)
        {
            array[255-j][255-i][0]=image[i][255-j][0];
            array[255-j][255-i][1]=image[i][255-j][1];
            array[255-j][255-i][2]=image[i][255-j][2];

        }
        
    }
    for (int i = 0; i < 256; i++)
    {
       for (int j = 0; j < 256; j++)
       {
           image[i][j][0]=array[i][j][0];
           image[i][j][1]=array[i][j][1];
           image[i][j][2]=array[i][j][2];

       }
       
    }
    
    
}

//---------------------------------------

void copy_left(unchar image[SIZE][SIZE][RGB]) 
{
    // copying Left side to Right side

    for (int i = 0; i <256; i++)
    {
        for (int j = 0; j < 256/2; j++)
        {
            image[i][255-j][0]=image[i][j][0];
            image[i][255-j][1]=image[i][j][1];
            image[i][255-j][2]=image[i][j][2];

        }
        
    }
    
}

//---------------------------------------

void copy_right(unchar image[SIZE][SIZE][RGB]) 
{
    // copying Right side to Left side

    for (int i = 0; i < 256; i++)
    {
        for (int j = 255; j>=128; j--)
        {
            image[i][255-j][0]=image[i][j][0];
            image[i][255-j][1]=image[i][j][1];
            image[i][255-j][2]=image[i][j][2];

        }
        
    }
    
}

//---------------------------------------

void copy_upper(unchar image[SIZE][SIZE][RGB])
{
    // copying Upper side to Lower side

    for (int i = 0; i < 256/2; i++)
    {
       for (int j = 0; j < 256; j++)
       {
           image[255-i][j][0]=image[i][j][0];
           image[255-i][j][1]=image[i][j][1];
           image[255-i][j][2]=image[i][j][2];

       }
       
    }
    
}

//---------------------------------------

void copy_down(unchar image[SIZE][SIZE][RGB])
{
    // copying down side to upper side

    for (int i = 255; i >= 127; i--)
    {
       for (int j = 0; j < 256; j++)
       {
           image[255-i][j][0]=image[i][j][0];
           image[255-i][j][1]=image[i][j][1];
           image[255-i][j][1]=image[i][j][1];

       }
       
    }
    
}

//---------------------------------------

void quarters(unchar q1[SIZE/2][SIZE/2][3],unchar q2[SIZE/2][SIZE/2][3],
unchar q3[SIZE/2][SIZE/2][3],unchar q4[SIZE/2][SIZE/2][3])
{
    // making an array for eahc quarter of the orignal imaged to be shuffled and re-arranged 
    int row=0,coulmn=0;
    for (int i = 0; i <256/2; i++)
    {
        coulmn=0;
        for (int j = 0; j < 256/2; j++)
        {
            q1[row][coulmn][0] = image[i][j][0];
            q1[row][coulmn][1] = image[i][j][1];
            q1[row][coulmn][2] = image[i][j][2];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 0; i < 256/2; i++)
    {
        coulmn=0;
        for (int j = 128; j < 256; j++)
        {
            q2[row][coulmn][0]= image[i][j][0];
            q2[row][coulmn][1]= image[i][j][1];
            q2[row][coulmn][2]= image[i][j][2];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 128; i < 256; i++)
    {
        coulmn=0;
        for (int j = 0; j < 256/2; j++)
        {
            q3[row][coulmn][0] = image[i][j][0];
            q3[row][coulmn][1] = image[i][j][1];
            q3[row][coulmn][2] = image[i][j][2];
            coulmn++;
        }
        row++;
    }
    row=0,coulmn=0;
    for (int i = 128; i < 256; i++)
    {
        coulmn=0;
        for (int j = 128; j <256; j++)
        {
            q4[row][coulmn][0]=image[i][j][0];
            q4[row][coulmn][1]=image[i][j][1];
            q4[row][coulmn][2]=image[i][j][2];
            coulmn++;
        }
        row++;
    }
}

//---------------------------------------

void rearrange(unchar array[SIZE/2][SIZE/2][RGB],const int& current_quarter)
{
    //shuffling the arrays that was storing each quarter and copying them back to the orignal image in the new specifed order by the user

    int row=0,coulmn=0;
    if(current_quarter ==1)
    {
        row=0,coulmn=0;
        for (int i = 0; i < SIZE/2; i++)
        {
            coulmn=0;
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j][0]= array[row][coulmn][0];
                image[i][j][1]= array[row][coulmn][1];
                image[i][j][2]= array[row][coulmn][2];

                coulmn++;
            }
            row++;
        }
    }
    else if(current_quarter ==2)
    {
        row=0,coulmn=0;
        for (int i = 0; i < SIZE/2; i++)
        {
            coulmn=0;
            for (int j = 128; j <256; j++)
            {
                image[i][j][0]= array[row][coulmn][0];
                image[i][j][1]= array[row][coulmn][1];
                image[i][j][2]= array[row][coulmn][2];
                coulmn++;
            }
            row++;
        }
    }
    else if(current_quarter==3)
    {
        row=0,coulmn=0;
       for (int i = 128; i < SIZE; i++)
        {
            coulmn=0;
            for (int j = 0; j <SIZE/2; j++)
            {
                image[i][j][0]= array[row][coulmn][0];
                image[i][j][1]= array[row][coulmn][1];
                image[i][j][2]= array[row][coulmn][2];                
                coulmn++;
            }
            row++;
        } 
    }
    else
    {
        row=0,coulmn=0;
        for (int i = 128; i < 256; i++)
        {
            coulmn=0;
            for (int j = 128; j <256; j++)
            {
                image[i][j][0]= array[row][coulmn][0];
                image[i][j][1]= array[row][coulmn][1];
                image[i][j][2]= array[row][coulmn][2];
                coulmn++;
            }
            row++;
        } 
    }
}

//---------------------------------------

void kernel_sum(const int& row,const int& coulmn,unchar copy[256][256][RGB])
{
    // Making a kernel of size 3X3 to get the weighted Avg of the pixels

    int kernel[3][3][3];

    int kernel_row=0,kernel_col=0;
    int coulmn_move=coulmn-1+3;
    int row_move=row-1+3;

    for (int i = row-1; i <row_move; i++)
    {
        for (int j = coulmn-1; j <coulmn_move; j++)
        {
            if(i>=0&&i<=255&&j>=0&&j<=255)
            {
                kernel[kernel_row][kernel_col][0]=image[i][j][0]*4;
                kernel[kernel_row][kernel_col][1]=image[i][j][1]*4;
                kernel[kernel_row][kernel_col][2]=image[i][j][2]*4;

            }
            kernel_col++;
        }
        kernel_col=0;
       kernel_row++;
    }

    //Finding the weighted AVG for every Pixel
    long long sum0 = 0;
    long long sum1 = 0;
    long long sum2 = 0;

    for (int i = 0; i < 3; i++)
    {
       for (int j = 0; j < 3; j++)
       {
           sum0 += kernel[i][j][0];
           sum1+= kernel[i][j][1];
           sum2 += kernel[i][j][2];

       }
    }
    double wighted_avg0=ceil(sum0/36.0);
    double wighted_avg1=ceil(sum1/36.0);
    double wighted_avg2=ceil(sum2/36.0);

    copy[row][coulmn][0] =  wighted_avg0;
    copy[row][coulmn][1] =  wighted_avg1;
    copy[row][coulmn][2] =  wighted_avg2;

    
}

//---------------------------------------

void quarter(unchar array[SIZE/2][SIZE/2][RGB],const int& order)
{
    if(order == 1)
    {
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
               array[i][j][0]=image[i][j][0];
               array[i][j][1]=image[i][j][1];
               array[i][j][2]=image[i][j][2];

            }
            
        }
    }
    else if(order ==2)
    {
        int row=0,coulmn=0;
        for (int i = 0 ; i < 128; i++)
        {
            coulmn=0;
            for (int j = 128; j < 256; j++)
            {
               array[row][coulmn][0] = image[i][j][0];
               array[row][coulmn][1] = image[i][j][1];
               array[row][coulmn][2] = image[i][j][2];

               coulmn++;
            }
            row++;
        }
    }
    else if(order ==3)
    {
        int row=0,coulmn=0;
        for (int i = 128 ; i < 256; i++)
        {
            coulmn=0;
            for (int j = 0; j < 128; j++)
            {
               array[row][coulmn][0] = image[i][j][0];
               array[row][coulmn][1] = image[i][j][1];
               array[row][coulmn][2] = image[i][j][2];               
               coulmn++;
            }
            row++;
        }
    }
    else
    {
        int row=0,coulmn=0;
        for (int i = 128 ; i < 256; i++)
        {
            coulmn=0;
            for (int j = 128; j < 256; j++)
            {
               array[row][coulmn][0] = image[i][j][0];
               array[row][coulmn][1] = image[i][j][1];
               array[row][coulmn][2] = image[i][j][2];               
               coulmn++;
            }
            row++;
        }
    }
}

//---------------------------------------

void repeat_pixels(unchar quarter[SIZE/2][SIZE/2][RGB])
{
    // repeat Each pixel four times (square shape 2x2) to enlarge a certain quarter

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            for (int k= ((i+1)*2)-2; k <= (i+1)*2-1; k++)
            {
               for (int l = ((j+1)*2)-2 ; l<=(j+1)*2-1 ; l++)
               {
                   image[k][l][0]=quarter[i][j][0];
                   image[k][l][1]=quarter[i][j][1];
                   image[k][l][2]=quarter[i][j][2];

               }
               
            }
            
        }
        
    }
    
}

//---------------------------------------

void laplacian(const int& row,const int& coulmn,unchar copy[256][256][RGB])
{
    // Making a kernel of size 3X3 to get the Laplacian weights of the pixels
    int delta_pos_x0=0;
    int delta_pos_x1=0;
    int delta_pos_x2=0;

    int delta_neg_x0=0;
    int delta_neg_x1=0;
    int delta_neg_x2=0;

    int delta_pos_y0=0;
    int delta_pos_y1=0;
    int delta_pos_y2=0;

    int delta_neg_y0=0;
    int delta_neg_y1=0;
    int delta_neg_y2=0;

    int center0=4*image[row][coulmn][0];
    int center1=4*image[row][coulmn][1];
    int center2=4*image[row][coulmn][2];

    if(coulmn+1<256)
    {
        delta_pos_x0=image[row][coulmn+1][0];
        delta_pos_x1=image[row][coulmn+1][1];
        delta_pos_x2=image[row][coulmn+1][2];
    }
    if(coulmn-1>=0)
    {
        delta_neg_x0=image[row][coulmn-1][0];
        delta_neg_x1=image[row][coulmn-1][1];
        delta_neg_x2=image[row][coulmn-1][2];

    }
    if(row+1<256)
    {
        delta_pos_y0=image[row+1][coulmn][0];
        delta_pos_y1=image[row+1][coulmn][1];
        delta_pos_y2=image[row+1][coulmn][2];
    }
    if(row-1>=0)
    {
        delta_neg_y0=image[row-1][coulmn][0];
        delta_neg_y1=image[row-1][coulmn][1];
        delta_neg_y2=image[row-1][coulmn][2];
    }

    int laplace0=abs(delta_pos_y0+delta_neg_y0+delta_pos_x0+delta_neg_x0-center0);
    int laplace1=abs(delta_pos_y1+delta_neg_y1+delta_pos_x1+delta_neg_x1-center1);
    int laplace2=abs(delta_pos_y2+delta_neg_y2+delta_pos_x2+delta_neg_x2-center2);
    copy[row][coulmn][0]=laplace0;
    copy[row][coulmn][1]=laplace1;
    copy[row][coulmn][2]=laplace2;
}

//---------------------------------------

void reduce_image(unchar image[SIZE][SIZE][RGB],const int& ratio)
{
    unchar copy[SIZE][SIZE][RGB];
    // making an extrnal array  w making all it's pixels white
    for (int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            copy[i][j][0] = 255;
            copy[i][j][1] = 255;
            copy[i][j][2] = 255;
        }
    }
    // copying the orignal image into the extrnal array according to the shrink ratio 
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            copy[i/ratio][j/ratio][0] =image[i][j][0];
            copy[i/ratio][j/ratio][1] =image[i][j][1];
            copy[i/ratio][j/ratio][2] =image[i][j][2];
        }
    }


    //returning back the content to original image
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            image[i][j][0] =copy[i][j][0];
            image[i][j][2] =copy[i][j][2];
            image[i][j][1] =copy[i][j][1];
        }
    }
}

//---------------------------------------
