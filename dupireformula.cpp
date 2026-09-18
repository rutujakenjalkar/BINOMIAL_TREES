#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;





//FUNCTION TO READ THE CSV FILE 

vector<vector<string>> readCSV(const string &filename)
{
    vector<vector<string>> data;
    ifstream option_price_file(filename);  //option_price_file is the name i want to give the file and open the file

    if (!option_price_file.is_open())
    {
        cout<<"the file is not  open."<<endl;
        return data;
    }

    string line_of_csv;
   

    while (getline(option_price_file, line_of_csv)) {
        vector<string> row;
        stringstream ss(line_of_csv);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }


    option_price_file.close();
    cout<<"the file is close."<<endl;
    return data;
}


//DUPIRE FORMULA FUNCTION














//FUNCTION TO PARSE DATA PROPERLY



int main()
{
    auto data = readCSV("C:\\Users\\rutuj\\Downloads\\local_vol_grid.csv");

  

    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }

    int  col_size= data[0].size();
    cout<<col_size<<endl;

    vector<string> strike_prices;
    strike_prices.resize(col_size);

    for(int i=1 ;i< col_size;i++)
    {
        string temp;
        temp=data[0][i];
        strike_prices[i]=temp;
    }

    cout<<"0:"<<strike_prices[0]<<endl;
    cout<<"1:"<<strike_prices[1]<<endl;


    vector<string> maturities;


    int row_size=data.size();
    maturities.resize(row_size);



    for (int i =0;i<row_size;i++)
    {
        string temp;
        temp= data[i][0];
        maturities[i]=temp;
    }

    cout<<"1:"<<maturities[1]<<endl;



    vector<vector<double>> local_volitalities[row_size][col_size];



    return 0;
}