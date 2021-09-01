#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << "\n";
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << "\n";
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << "\n";
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* nah =  new int[length];
  
  for (int i = 0; i < length ; ++i){
    nah[i] = 0;
  }

  return nah;
}

void deleteSeam(int* seam) {
  delete[] seam;
  seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  string type;
  ifstream fns;
  fns.open(filename);

  if (!fns.is_open()){
    cout <<"Error: failed to open input file - "<<filename<<endl;
    return false;
  }
  fns >> type;
  if (type != "P3"){
    cout << "Error: type is " <<type<<" instead of P3."<<endl;
    return false;
  }

  int filewidth;
  int fileheight;

  fns >> filewidth;
  if (fns.fail()){
        cout << "Error: read non-integer value" ;
        return false;
  }
  fns >> fileheight;
  if (fns.fail()){
        cout << "Error: read non-integer value" ;
        return false;
  }

  if (filewidth != width){
    cout << "Error: input width ("<<width<<") does not match value in file ("<<filewidth<<")";
    return false;
  }

  else if (fileheight != height){
    cout << "Error: input height (" <<height<< ") does not match value in file (" <<fileheight<< ")";
    return false;
  }

  int maxcolor;
  fns >> maxcolor;
  int r,g,b;
  int count = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      count += 1;
      fns >> r;
      if (fns.eof()){
        cout << "Error: not enough color values";
        return false;
      }
      if (fns.fail()){
        cout << "Error: read non-integer value" ;
        return false;
      }

      fns >> g;
      if (fns.eof()){
        cout << "Error: not enough color values";
        return false;
      }
      if (fns.fail()){
        cout << "Error: read non-integer value" ;
        return false;
      }

      fns >> b;
      if (fns.eof() && count != width * height){
        cout << "Error: not enough color values";
        return false;
      }
      if (fns.fail() && !fns.eof()){
        cout << "Error: read non-integer value";
        return false;
      }
      if (fns.eof() && fns.fail()){
        cout << "Error: not enough color values";
        return false;
      }


      if (r > 255 || r < 0){
        cout << "Error: invalid color value "<<r;
        return false;
      }
      else if (g > 255 || g < 0){
        cout << "Error: invalid color value "<<g;
        return false;
      }
      else if (b > 255 || b < 0){
        cout << "Error: invalid color value "<<b;
        return false;
      }

      image[j][i].r = r;
      image[j][i].g = g;
      image[j][i].b = b;
    }
  }
  int bye;
  fns >> bye;
  if (fns.eof() || fns.fail()){
    fns.close();
    return true;
  }
  else {
    cout << "Error: too many color values";
    return false;
  }
  
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  ofstream ofs(filename);
  if (!ofs.is_open()){
    cout << "Error: failed to open output file - "<<filename<<"\n";
    return false;
  }
  ofs << "P3"<<"\n";
  ofs << width << " "<<height<<"\n";
  ofs << "255"<<"\n";

  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      ofs << image[j][i].r<< " "<< image[j][i].g<< " "<< image[j][i].b<< " ";
    }
    ofs << "\n";
  }
  ofs << "\n";
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
  int energy;
  int n = x;
  int m = y;
  int t = 0;
  int q = 0;

  if (x==0 && y==0){
    n = width-1;
    m = height-1;
    t = (image[n][y].r - image[x+1][y].r)*(image[n][y].r - image[x+1][y].r) + (image[n][y].g - image[x+1][y].g)*(image[n][y].g - image[x+1][y].g) +(image[n][y].b - image[x+1][y].b)*(image[n][y].b - image[x+1][y].b);
    q = (image[x][m].r - image[x][y+1].r)*(image[x][m].r - image[x][y+1].r) + (image[x][m].g - image[x][y+1].g)*(image[x][m].g - image[x][y+1].g) + (image[x][m].b - image[x][y+1].b)*(image[x][m].b - image[x][y+1].b);
  }
  else if (x==width-1 && y==0){
    n = 0;
    m = height-1;
    t = (image[x-1][y].r - image[n][y].r)*(image[x-1][y].r - image[n][y].r) + (image[x-1][y].g - image[n][y].g)*(image[x-1][y].g - image[n][y].g) + (image[x-1][y].b - image[n][y].b)*(image[x-1][y].b - image[n][y].b);
    q = (image[x][m].r - image[x][y+1].r)*(image[x][m].r - image[x][y+1].r) + (image[x][m].g - image[x][y+1].g)*(image[x][m].g - image[x][y+1].g) + (image[x][m].b - image[x][y+1].b)*(image[x][m].b - image[x][y+1].b);    
  }
  else if(x==width-1 && y==height-1){
    n = 0;
    m = 0;
    t = (image[x-1][y].r - image[n][y].r)*(image[x-1][y].r - image[n][y].r) + (image[x-1][y].g - image[n][y].g)*(image[x-1][y].g - image[n][y].g) + (image[x-1][y].b - image[n][y].b)*(image[x-1][y].b - image[n][y].b);
    q = (image[x][y-1].r - image[x][m].r)*(image[x][y-1].r - image[x][m].r) + (image[x][y-1].g - image[x][m].g)*(image[x][y-1].g - image[x][m].g) + (image[x][y-1].b - image[x][m].b)*(image[x][y-1].b - image[x][m].b);
  }
  else if (x == 0 && y == height-1){
    n = width-1;
    m = 0;
    t = (image[n][y].r - image[x+1][y].r)*(image[n][y].r - image[x+1][y].r) + (image[n][y].g - image[x+1][y].g)*(image[n][y].g - image[x+1][y].g) +(image[n][y].b - image[x+1][y].b)*(image[n][y].b - image[x+1][y].b);
    q = (image[x][y-1].r - image[x][m].r)*(image[x][y-1].r - image[x][m].r) + (image[x][y-1].g - image[x][m].g)*(image[x][y-1].g - image[x][m].g) + (image[x][y-1].b - image[x][m].b)*(image[x][y-1].b - image[x][m].b);    
  }
  else if (x == 0){
    n = width-1;
    t = (image[n][y].r - image[x+1][y].r)*(image[n][y].r - image[x+1][y].r) + (image[n][y].g - image[x+1][y].g)*(image[n][y].g - image[x+1][y].g) +(image[n][y].b - image[x+1][y].b)*(image[n][y].b - image[x+1][y].b);
    q = (image[x][y-1].r - image[x][y+1].r)*(image[x][y-1].r - image[x][y+1].r) + (image[x][y-1].g - image[x][y+1].g)*(image[x][y-1].g - image[x][y+1].g) + (image[x][y-1].b - image[x][y+1].b)*(image[x][y-1].b - image[x][y+1].b);
  }
  else if (x == width-1){
    n = 0;
    t = (image[x-1][y].r - image[n][y].r)*(image[x-1][y].r - image[n][y].r) + (image[x-1][y].g - image[n][y].g)*(image[x-1][y].g - image[n][y].g) + (image[x-1][y].b - image[n][y].b)*(image[x-1][y].b - image[n][y].b);
    q = (image[x][y-1].r - image[x][y+1].r)*(image[x][y-1].r - image[x][y+1].r) + (image[x][y-1].g - image[x][y+1].g)*(image[x][y-1].g - image[x][y+1].g) + (image[x][y-1].b - image[x][y+1].b)*(image[x][y-1].b - image[x][y+1].b);
  
  }
  else if (y == 0){
    m = height-1;
    t = (image[x-1][y].r - image[x+1][y].r)*(image[x-1][y].r - image[x+1][y].r) + (image[x-1][y].g - image[x+1][y].g)*(image[x-1][y].g - image[x+1][y].g) + (image[x-1][y].b - image[x+1][y].b)*(image[x-1][y].b - image[x+1][y].b);
    q = (image[x][m].r - image[x][y+1].r)*(image[x][m].r - image[x][y+1].r) + (image[x][m].g - image[x][y+1].g)*(image[x][m].g - image[x][y+1].g) + (image[x][m].b - image[x][y+1].b)*(image[x][m].b - image[x][y+1].b);
  }
  else if (y == height-1){
    m = 0;
    t = (image[x-1][y].r - image[x+1][y].r)*(image[x-1][y].r - image[x+1][y].r) + (image[x-1][y].g - image[x+1][y].g)*(image[x-1][y].g - image[x+1][y].g) + (image[x-1][y].b - image[x+1][y].b)*(image[x-1][y].b - image[x+1][y].b);
    q = (image[x][y-1].r - image[x][m].r)*(image[x][y-1].r - image[x][m].r) + (image[x][y-1].g - image[x][m].g)*(image[x][y-1].g - image[x][m].g) + (image[x][y-1].b - image[x][m].b)*(image[x][y-1].b - image[x][m].b);
  }
  else {
    t = (image[x-1][y].r - image[x+1][y].r)*(image[x-1][y].r - image[x+1][y].r) + (image[x-1][y].g - image[x+1][y].g)*(image[x-1][y].g - image[x+1][y].g) + (image[x-1][y].b - image[x+1][y].b)*(image[x-1][y].b - image[x+1][y].b);
    q = (image[x][y-1].r - image[x][y+1].r)*(image[x][y-1].r - image[x][y+1].r) + (image[x][y-1].g - image[x][y+1].g)*(image[x][y-1].g - image[x][y+1].g) + (image[x][y-1].b - image[x][y+1].b)*(image[x][y-1].b - image[x][y+1].b);
  }
  energy = t + q;
  return energy;
}


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  int sum = energy(image, start_col, 0, width,height);
  seam[0] = start_col;
  int big_boi, forward, backward;

  for (int i = 1;i < height; ++i){
    big_boi = energy(image, start_col, i , width, height);

    if (start_col < width-1){
      forward = energy(image, start_col+1, i , width, height);
      if (start_col >= 1){
        backward = energy(image, start_col-1, i , width, height);
        if (big_boi > forward && forward <= backward){
          big_boi = forward;
          start_col += 1;
        }
        else if (backward < forward && backward < big_boi){
          big_boi = backward;
          start_col -= 1;
        }
      }
      else {
        if (forward < big_boi){
          big_boi = forward;
          start_col += 1;
        }
      }
    }
    else {
      backward = energy(image, start_col-1, i , width, height);
      if (backward < big_boi){
        big_boi = backward;
        start_col -= 1;
      }
    }

    sum += big_boi;
    seam[i] = start_col;
  }
  return sum;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int sum = energy(image, 0, start_row, width,height);
  seam[0] = start_row;
  int big_boi, forward, backward;

  for (int i = 1;i < width; ++i){
    big_boi = energy(image, i, start_row , width, height);

    if (start_row < height-1){
      forward = energy(image, i, start_row+1 , width, height);
      if (start_row >= 1){
        backward = energy(image, i, start_row-1 , width, height);
        if (big_boi > forward && forward < backward){
          big_boi = forward;
          start_row += 1;
        }
        else if (backward <= forward && backward < big_boi){
          big_boi = backward;
          start_row -= 1;
        }
      }
      else {
        if (forward < big_boi){
          big_boi = forward;
          start_row += 1;
        }
      }
    }
    else {
      backward = energy(image, i, start_row-1 , width, height);
      if (backward < big_boi){
        big_boi = backward;
        start_row -= 1;
      }
    }

    sum += big_boi;
    seam[i] = start_row;
  }
  return sum;

}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int poopy = 0;
  int* nah = createSeam(height);
  int first_seam_e = loadVerticalSeam(image,0,width,height,nah);
  for (int i = 1; i < width; ++i){
    int new_seam_e = loadVerticalSeam(image,i,width,height,nah);
    if(new_seam_e <= first_seam_e){
      first_seam_e = new_seam_e;
      poopy = i;
    }
  }

  loadVerticalSeam(image,poopy,width,height,nah);
  return nah;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int first_seam_e;
  int new_seam_e;
  int poopy = 0;

  int* nah = createSeam(width);
  first_seam_e = loadHorizontalSeam(image,0,width,height,nah);
  for (int i = 1; i < height; ++i){
    new_seam_e = loadHorizontalSeam(image,i,width,height,nah);
    if(new_seam_e < first_seam_e){
      first_seam_e = new_seam_e;
      poopy = i;
    }
  }

  loadHorizontalSeam(image,poopy,width,height,nah);
  return nah;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int i = 0; i < height ;++i){
    for (int j = verticalSeam[i]; j < width-1; ++j){
      image[j][i] = image[j+1][i];
    }
  }
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for (int i = 0; i < width ;++i){
    for (int j = horizontalSeam[i]; j < height-1; ++j){
      image[i][j] = image[i][j+1];
    }
  }
}


