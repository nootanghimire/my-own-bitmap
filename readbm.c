 #include&lt;stdio.h&gt;
#include&lt;conio.h&gt;
#define MAX_BMP_SZ 100
//Struct Defn'
typedef struct {
  int char_id;            // Char_id
  int char_bmap[16];  // The real character bitmap
  } xbmp ;

void main() {

    FILE *fp;
    int i, j, k ; //legacy counters
    int len; //No. of characters loaded.
    xbmp char_coll[MAX_BMP_SZ], temp;
    i = j = k= 0; //not really needed. Just for fun :D
    //open a file
    fp = fopen(&quot;test.xbmp&quot;,&quot;rb&quot;);
    while(!feof(fp)) {
        fread(&amp;temp, sizeof(temp),1, fp);
        char_coll[i] = temp ;  //copying Structure
        i++; //update
    }
    fclose(fp);
    len = i - 2 ;  //Since we-are zero indexing, i think

    //Now display the contents : TEST CASE

    for(j=0;  j&lt;=i-2 ; j++ ) {
        printf(&quot;\n----------------------------\n\nChar ID: %d&quot;, char_coll[j].char_id);
        printf(&quot;\n\nShowing Character Bitmap Now: &quot;);
        for(k=0; k&lt;=15; k++) {
            printf(&quot;\nHex For Line %d :::  %x&quot;, char_coll[j], char_coll[j].char_bmap[k]);
        }
    }

}

void display_all_pixels(xbmp coll[], int len) {

    //This is the Turbo C Version of the function.
    //This requires #include &lt;graphics.h&gt; preprocessor directive.
    //You are welcome to make your own function for a different Platform
    //Showcasing the Font Contents

    //Check Screen Size rather than total entries
   int y_max = 199, x_max = 319;
   int curr_x, curr_y, hold_x, hold_y ;
   int i,j; //legacy counters
   int iterator=0; //for_number of entries
  typedef int element2d[8][16];
  element2d *output_array;
  output_array = (element2d*) (malloc(len*sizeof(element2d)));

   //Convert bitmap to readable, i.e, seperate hex to bin
   convert_bmp_for_showcase(coll, len, output_array);

   curr_x = curr_y = hold_x = hold_y = 0;

   do{
        curr_x = hold_x;
        curr_y = hold_y;
        for(i=curr_x ; i&lt;=curr_x+7; i++) {
            for(j=curr_y; j&lt;=curr_y+15; j++){
                    if (output_array[iterator][i][j]) putpixel(i,j, 1);
                        hold_y++;
            } //end inner for loop
            hold_x++;
        } //end outer for loop
        iterator++;
    }while(hold_x&lt;=x_max &amp;&amp; hold_y&lt;=y_max);

}

void convert_bmp_for_showcase(xbmp char_coll[], int len, int output_array[][8][16]) {

    //Converts Compelex Structure coll, to simpler array
    //The array will be 2-dimensional,  bmp_array[8][16],
    //which is again arrayed!!
    //So the final array: bmp_array[no_of_entries][8][16]

    //Logic: Use For loops

    //Counters:
    int i, j,k;
    for(i=0; i&lt;=len; i++){
        //This is for first dimension
        for(j=0; j&lt;=15;j++){
            //Now mask 'em
            //Use loops, instead, eh?
            output_array[i][0][j] = char_coll[j].char_bmap[k] &amp; 0x80 ;
            output_array[i][1][j] = char_coll[j].char_bmap[k] &amp; 0x40 ;
            output_array[i][2][j] = char_coll[j].char_bmap[k] &amp; 0x20 ;
            output_array[i][3][j] = char_coll[j].char_bmap[k] &amp; 0x10 ;
            output_array[i][4][j] = char_coll[j].char_bmap[k] &amp; 0x8 ;
            output_array[i][5][j] = char_coll[j].char_bmap[k] &amp; 0x4;
            output_array[i][6][j] = char_coll[j].char_bmap[k] &amp; 0x2 ;
            output_array[i][7][j] = char_coll[j].char_bmap[k] &amp; 0x1 ;
            //End Masking...
        } //End j loop
    }  //End i loop

   // This should probably work. Now you are presented with a array
   // which is 3-d and contains: [no_of_iterations][columns][columns]
} //End function


void plot_hex_horizontal(int hex_value, int start_x, int in_y, int color){
    //Plots hex value directly using plot pixel
    if(hex_value &amp; 0x80 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x40 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x20 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x10 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x8 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x4 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x2 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value &amp; 0x1 ) putpixel(start_x, in_y, color); start_x++;
    //End function
}

int* create_3d_array(int x, int y, int z){
int* a;
a = (int *) (malloc(x*y*z*sizeof(int)));
return a; //Hope it works!
}