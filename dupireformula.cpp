#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;


int row_size;
int col_size;
vector<string> strike_prices;
vector<string> maturities;
double option_price;
double strike_price;
double risk_free_rate;







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
vector<vector<double>> get_dupire_matrix( vector<vector<double>> matrix,const vector<vector<string>>& price_grid)
{

    cout<<"this is being called."<<endl;
    for(int i=1;i<=row_size-1;i++)
    {
        for (int j=1;j<=col_size-1;j++)
        {
            cout<<"we are here"<<endl;
            if (j==1)
            {
                matrix[i][j]=0;
            }
            else
            {
                double delta_c_time=stod(price_grid[i+1][j])- stod(price_grid[i][j]);
                double delta_t_time= (stod(maturities[2])-stod(maturities[1]))*2;

                double time_derivative= delta_c_time/delta_t_time;

                double delta_c_strike = stod(price_grid[i][j+1])-stod(price_grid[i][j]);
                double delta_strike =(stod(strike_prices[1])-stod(strike_prices[0]))*2;

                double first_strike_derivative= delta_c_strike/delta_strike ;

                //SECOND STRIKE DERIVATIVE //CONVEXITY
                double second_strike_derivative= (stod(price_grid[i][j+1])-(2*stod(price_grid[i][j]))+stod(price_grid[i][j-1]))/pow(delta_strike,2);
                
                double numerator= time_derivative +(risk_free_rate*strike_price*first_strike_derivative)-(risk_free_rate*option_price);

                double denominator = 0.5*pow(strike_price,2)*second_strike_derivative;

                double volatility=pow(( numerator/denominator),0.5);

                matrix[i][j] = volatility;


            
            }
        }
    }
    return matrix ;


}








//FUNCTION TO PARSE DATA PROPERLY



int main()
{
   
    cout<<"Enter the strike price"<<endl;
    cin>>strike_price;


    
    cout<<"enter the option price:"<<endl;
    cin>>option_price;

   
    cout<<"enter the risk free rate of return."<<endl;
    cin>>risk_free_rate;
    auto price_grid = readCSV("C:\\Users\\rutuj\\Downloads\\maturity_strike_data.csv");

  

    for (const auto& row : price_grid) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }

    col_size= price_grid[0].size();
    cout<<col_size<<endl;

    
    strike_prices.resize(col_size);

    for(int i=1 ;i< col_size;i++)
    {
        string temp;
        temp=price_grid[0][i];
        strike_prices[i]=temp;
    }

    cout<<"0:"<<strike_prices[0]<<endl;
    cout<<"1:"<<strike_prices[1]<<endl;


    row_size=price_grid.size();
    maturities.resize(row_size);



    for (int i =1;i<row_size;i++)
    {
        string temp;
        temp= price_grid[i][0];
        maturities[i]=temp;
    }

    cout<<"1:"<<maturities[1]<<endl;

    for (int i =0;i<row_size;i++)
    {
        cout<<maturities[i]<<endl;
    }

    for (int j =0 ;j<col_size;j++)
    {
        cout<<strike_prices[j]<<endl;
    }


     vector<vector<double>> local_volitalities(row_size, vector<double>(col_size, 0.0));

    
     vector<vector<double>> x = get_dupire_matrix(local_volitalities,price_grid);


     for (const auto& row : x) {
         for (const auto& cell : row) {
             std::cout << cell << "\t";
        }
        std::cout << std::endl;
     }
 
     return 0;
}