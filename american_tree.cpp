#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <optional>










//NODE CLASS
class node
{
    public:
    double payoff;
    double value_of_stock;
    double probability_up_prev;
    double probability_down_prev;

    node(double payoff,double value_of_stock,double pi_u,double pi_d)
    {
        payoff=payoff;
        value_of_stock=value_of_stock;
        probability_up_prev=pi_u;
        probability_down_prev=pi_d;

    }
};



double get_pay_off(char type, double strike_price, double value)
{
    double temp;
    if (type=='c')
    {
        temp= value-strike_price;
        if (temp<0)
        {
            return 0;
        }
        else
        {
            return temp;
        }
    }
    else
    {
        temp=strike_price-value;
        if (temp<0)
        {
            return 0;
        }
        else
        {
            return temp;
        }
    }
}















int main()
{
    cout<<"WELCOME TO THE BINOMIAL TREE CALCUTION FOR EUROPIAN OPTION"<<endl;

    //TAKING THE INPUTS

    double current_price,strike_price;
    double volatility,maturity;
    double frequency;
    double risk_free_rate;
    int level;
    char type;

    
    std::cout<<"Enter the current stock price:";
    std::cin>>current_price;
    
    std::cout<<"Enter the strike price:";
    std::cin>>strike_price;
    
    std::cout<<"Enter the volatility of the stock:";
    std::cin>>volatility;
    
    std::cout<<"Enter the maturity of the stock :";
    std::cin>>maturity;

    std::cout<<"Enter the frequency of the compounding:";
    std::cin>>frequency;

    std::cout<<"Enter the risk free rate of the stock :";
    std::cin>>risk_free_rate;

    std::cout<<"Enter the size of the binomial tree :";
    std::cin>>level;

    std::cout<<"Enter the type of option c for call p for put :";
    std::cin>>type;
    

    //CALCULATING THE FACTORS 


    double T= maturity/frequency;
    double factor_1=volatility*sqrt(T)*0.01;

    double up_move=exp(factor_1);
    
    double down_move= 1/up_move;

    double factor_2=exp(risk_free_rate*T*0.01);
    double up_probability=(factor_2-down_move)/(up_move-down_move);
    double down_probability=1-up_probability;


    cout<<"up move (u):"<<up_move<<endl;
    cout<<"down move (d):"<<down_move<<endl;
    cout<<"up probability:"<<up_probability<<endl;
    cout<<"down probability:"<<down_probability<<endl;
    


    //CREATING A VECTOR TO STORE VALUES 
    // storing the three vector 
    std::vector<std::vector<node>>tree(level+1,std::vector<node>(level+1 , node(0.0,0.0,0.0,0.0)));

    //ADDING VALUES TO THE VECTOR 
    for(int i =0 ;i<=level;i++)
    {
        for(int j =0;j<=level;j++)
        {

            if (i+j <= level)
            {
            if(i==0 && j==0)
            {
                
                tree[i][j].probability_up_prev=1;
                tree[i][j].probability_down_prev=1;
                tree[i][j].value_of_stock=current_price;
                tree[i][j].payoff=0;
                cout<<"i: "<<i<<"j: "<<j<<endl;
                cout<<"prob up:"<<tree[i][j].probability_up_prev<<endl;
                cout<<"prob down:"<<tree[i][j].probability_down_prev<<endl;
                cout<<"value of option:"<<tree[i][j].value_of_stock<<endl;
                cout<<"payoff: "<<tree[i][j].payoff<<endl;
                
            }
            else if (i==0)
            {


                //setting the probability
                cout<<"i: "<<i<<"j: "<<j<<endl;
                tree[i][j].probability_up_prev=0.0;
                cout<<"prob _up "      <<tree[i][j].probability_up_prev<<endl;
                tree[i][j].probability_down_prev=down_probability;
                cout<<"prob _down "      <<tree[i][j].probability_down_prev<<endl;

                //geting the pay off and the stock price 
                double power_value=pow(down_move,j);
                double value_after_down= current_price*power_value;
                
                //setting the pay off and the current strike price 
                tree[i][j].value_of_stock=value_after_down;
                cout<<"value of option"<<tree[i][j].value_of_stock;
                tree[i][j].payoff=get_pay_off(type,strike_price,value_after_down);
                cout<<"pay off:"<<tree[i][j].payoff<<endl;

            }
            else if (j==0)
            {


                cout<<"i: "<<i<<"j: "<<j<<endl;
                 //setting the probability
                tree[i][j].probability_down_prev=0.0;
                cout<<"prob _down "      <<tree[i][j].probability_down_prev<<endl;
                tree[i][j].probability_up_prev=up_probability;
                cout<<"prob _up "      <<tree[i][j].probability_up_prev<<endl;

                //geting the pay off and the stock price 
                double power_value=pow(up_move,i);
                double value_after_up= current_price*power_value;
                
                //setting the pay off and the current strike price 
                tree[i][j].value_of_stock=value_after_up;
                cout<<"value of option"<<tree[i][j].value_of_stock;
                tree[i][j].payoff=get_pay_off(type,strike_price,value_after_up);
                cout<<"pay off:"<<tree[i][j].payoff<<endl;



            }
            else
            {   

                 cout<<"i:"<<i<<"j:"<<j<<endl;
                 // logic for the mixed nodes
                 tree[i][j].probability_up_prev=up_probability;
                 cout<<"up probability: "<<tree[i][j].probability_up_prev<<endl;
                 tree[i][j].probability_down_prev=down_probability;
                  cout<<"down probability: "<<tree[i][j].probability_down_prev<<endl;

                 
                  double power_value_up= pow(up_move,i);
                  double power_value_down= pow(down_move,j);
                  double value_of_stock=current_price*power_value_up*power_value_down;
                  tree[i][j].value_of_stock=value_of_stock;
                  cout<<"current value of the stock: "<<tree[i][j].value_of_stock<<endl;
                  double pay_off= get_pay_off(type,strike_price,value_of_stock);
                  tree[i][j].payoff=pay_off;
                  cout<<"the value of payoff :"<<tree[i][j].payoff<<endl;


            }
        }
    }
    }





}