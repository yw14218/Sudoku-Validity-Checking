#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool valid_sudoku(const std::vector<int>& g);
bool check_sequence(const std::vector<int>& v);
int  mfind(int n, const std::vector<int>& v);
void get_row(int r, const std::vector<int>& in, std::vector<int>& out);
void get_col(int c, const std::vector<int>& in, std::vector<int>& out);
void get_subsq(int subs, const std::vector<int>&in, std::vector<int>& out);
int twod_to_oned(int row, int col, int rowlen);
/// Download the source file as instructed in the guidelines. 
/// Should not type the code here, because if anything goes wrong in your typing, the auto-test is going to fail.
int main(){

    std::vector<int> s;
    std::string filename;

    std::cout << "please enter name of file containing the sudoku" << std::endl;
    std::cin >> filename;

    std::ifstream infile;
    infile.open(filename.c_str());

    if(!infile.is_open()){
        std::cout << "error, can't open input file" << std::endl;
        exit(EXIT_FAILURE);
    }

    int tmp;

    while(infile >> tmp){
        s.push_back(tmp);
    }

    int side = std::sqrt(s.size());

    for(int i = 0; i < side; i++){
         for(int j = 0; j < side; j++){
             std::cout << s[twod_to_oned(i,j,side)] << " ";
        }
        std::cout << std::endl;
    }

    bool valid = valid_sudoku(s);

    if(valid){
        std::cout << "valid" << std::endl;
    }
    else{
        std::cout << "not valid" << std::endl;
    }

    return 0;
}


int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}

bool valid_sudoku(const std::vector<int>& g){
     int side = std::sqrt(g.size());

    // for each row...
     for(int i = 0; i < side; i++){
        std::vector<int> row;
        get_row(i, g, row);

        if(!check_sequence(row)){
            return false;
        }
     }

    // for each column...
     for(int i = 0; i < side; i++){
        std::vector<int> col;
        get_col(i, g, col);

        if(!check_sequence(col)){
            return false;
        }
     }

    // for each subsquare...
     for(int i = 0; i < side; i++){
        std::vector<int> subsq;
        get_subsq(i, g, subsq);

        if(!check_sequence(subsq)){
            return false;
        }
     }


     return true;
}

int mfind(int n, const std::vector<int>& v){
    for(int i = 0; i < v.size(); i++){
          if(n == v[i]){
          return i;} /// Wrong indentation.
    }
    return -1;
}

bool check_sequence(const std::vector<int>& v){
     int i,x;
     for(i = 1; i <= v.size(); i++){ /// Declare i in the for-loop condition as the way taught in the lab instructions.
         x = mfind(i, v);
         if(x == -1)
         return false; /// Wrong indentation. Always use full pair of {} in case you need to add something later.
     }
     return true;
}


void get_row(int r, const std::vector<int>& in, std::vector<int>& out){
     int side = std::sqrt(in.size());
     for(int i = 0; i < side; i++){
     int x = twod_to_oned(r, i, side); /// Wrong indentation
     out.push_back(in[x]);
     }
}

void get_col(int c, const std::vector<int>& in, std::vector<int>& out){
     int side = std::sqrt(in.size());
     for(int i = 0; i < side; i++){
     int x = twod_to_oned(i, c, side); /// Wrong indentation
     out.push_back(in[x]);
     }
}

/// Should not alter the parameters given to you.
/// Parameter names should to be consistent with the parameters names in the function prototypes at the beginning of this file.
/// This is more readable for human beings than your implementation (though yours also works for computer).
void get_subsq(int index, const std::vector<int>& in, std::vector<int>& out){
     int row = 0;

     int side = std::sqrt(in.size());
     int subside = std::sqrt(side);
     while(index >= subside){
        index = index - subside;
        row = row + 1;
     } /// Why not use "%" (modulo)?
    int subrow = 0;
    int subcol = 0;
    subrow = subrow + row*subside; /// Why not use "subrow = row*subside"?
    subcol = subcol + index*subside; /// Same as above.

    int subrow_ = subrow;
    int subcol_ = subcol; /// These reuses of variables are not necessary and confusing.
    for(subrow= subrow_; subrow < (subrow_ + subside); subrow++){
         for(subcol = subcol_; subcol < (subcol_ + subside); subcol++){
              int x = twod_to_oned(subrow, subcol, side);
              /// You can simply use in[twod_to_oned(subrow, subcol, side)]
              out.push_back(in[x]);
         }
     }

}
/// The code is in general OK, but please pay attention to your coding style and try to avoid unecessary implementations.
/// Please stick to the guidelines in other assignments.
/// Please also review the labs done in the autumn term.