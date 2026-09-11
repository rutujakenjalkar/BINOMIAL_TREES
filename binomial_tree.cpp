
#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
#include <cstdio>

class node;

void print_horizontal_tree(double current_price, double up_move, double down_move, double option_value, const std::vector<std::vector<node>>& tree, int total_level);



class node
{
    public:
    double probability_of_exercise;
    double payoff;
    double value_of_option;

    node(double probability_of_exercise,double payoff,double value_of_option)
    {
        probability_of_exercise=probability_of_exercise;
        payoff=payoff;
        value_of_option=value_of_option;
    }
};


int get_factorial(int x)
{
    if  ( x ==0 || x==1)
    {    return 1;
    }
    else
    {   return x * get_factorial(x-1);
    }
}


int get_binomial_coeff(int level, int node)
{
    int level_factorial= get_factorial(level);
    int term_factorial= get_factorial(node);
    int sub_factorial= get_factorial(level- node);

    return level_factorial/(term_factorial*sub_factorial);

}

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
    

    double T= maturity/frequency;
    double factor_1=volatility*sqrt(T)*0.01;

    // make changes to the t to sqrtt in the factor_1

    double up_move=exp(factor_1);
    
    double down_move= 1/up_move;

    double factor_2=exp(risk_free_rate*T*0.01);
    double up_probability=(factor_2-down_move)/(up_move-down_move);
    double down_probability=1-up_probability;


    // storing the three vector 
    std::vector<std::vector<node>>tree(level+1,std::vector<node>(level+1 , node(0.0,0.0,0.0)));

    //adding values

    int term =0 ;
    for(int i = 0;i<=level;i++)
    {
        for(int j =0;j<=level;j++)
        {
            if(i+j == level)
            {
                if (j==0)
                {

                    // pure up move
                    double  power_value=pow(up_move,i);
                    double  value_after_up=current_price*power_value;
                    double   final_probability=pow(up_probability,i)*get_binomial_coeff(level,term);
                    term+=1;
                    double pay_off = get_pay_off(type,strike_price,value_after_up);

                    
                    tree[i][j].payoff=pay_off;
                    tree[i][j].value_of_option=value_after_up;
                    tree[i][j].probability_of_exercise=final_probability;

                }
                else if (i==0)
                {

                     double power_value=pow(down_move,j);
                     double value_after_down= current_price*power_value;
                     double final_probability=pow(down_probability,j)*get_binomial_coeff(level,term);
                    
                     term+=1;
                     double pay_off = get_pay_off( type,strike_price,value_after_down);


                     tree[i][j].payoff=pay_off;
                     tree[i][j].value_of_option=value_after_down;
                     tree[i][j].probability_of_exercise=final_probability;
                     
                    
                }
                else
                {

                  double power_value_up= pow(up_move,i);
                  double power_value_down= pow(down_move,j);
                  double value_of_stock=current_price*power_value_up*power_value_down;
                  double pay_off= get_pay_off(type,strike_price,value_of_stock);

                  double final_probability=pow(up_probability,i)*pow(down_probability,j)*get_binomial_coeff(level, term);
                  
                  term+=1;
                  tree[i][j].payoff=pay_off;
                  tree[i][j].value_of_option=value_of_stock;
                  tree[i][j].probability_of_exercise=final_probability;

                }
            }
        }
    }



    cout << "\n--- TERMINAL NODES VERIFICATION ---" << endl;
    for(int i = 0; i <= level; i++)
    {
        for(int j = 0; j <= level; j++)
        {
            if(i + j == level)
            {
                if (j == 0)
                {
                    cout << " Node (UP =" << i << ", DOWN =" << j << ")  -> Price: " 
                         << tree[i][j].value_of_option << " | Payoff: " << tree[i][j].payoff 
                         << " | Prob: " << tree[i][j].probability_of_exercise << endl;
                }
                else if (i == 0)
                {
                    cout << " Node (UP =" << i << ", DOWN =" << j << ")  -> Price: " 
                         << tree[i][j].value_of_option << " | Payoff: " << tree[i][j].payoff 
                         << " | Prob: " << tree[i][j].probability_of_exercise << endl;
                }
                else
                {
                    cout << " Node ( UP =" << i << ", DOWN  =" << j << ")  -> Price: " 
                         << tree[i][j].value_of_option << " | Payoff: " << tree[i][j].payoff 
                         << " | Prob: " << tree[i][j].probability_of_exercise << endl;
                }
            }
        }
    }


    double weighted_sum=0;
    //adding up to the weighted average
    for (int i =0;i<=level;i++)
    {
        for(int j =0;j<=level;j++)
        {
            
           weighted_sum += (tree[i][j].probability_of_exercise * tree[i][j].payoff);
        }
    }



    double discount_factor = pow(1.0 / factor_2, level);
//     cout<<"discount_factor"<<discount_factor;
//    cout<<"weighted_sum"<<weighted_sum<<endl;

    double option_value=weighted_sum*discount_factor;

    print_horizontal_tree(current_price, up_move, down_move, option_value, tree, level);

    cout<<"the value of the option is "<<option_value;







}




void print_horizontal_tree(double current_price, double up_move, double down_move, 
                            double option_value, const std::vector<std::vector<node>>& tree, int total_level) 
{
    // Fix: Compute the steps dynamically to display real numbers instantly
    double s0_val = current_price;
    double u1_val = current_price * up_move;
    double d1_val = current_price * down_move;

    double u2_val = current_price * up_move * up_move;
    double m2_val = current_price * up_move * down_move;
    double d2_val = current_price * down_move * down_move;

    std::cout << "\n=================================================================================\n";
    std::cout << "                      HORIZONTAL BINOMIAL LATTICE VIEW (t0 -> t2)                \n";
    std::cout << "=================================================================================\n\n";

    printf("                                                            +--------------+\n");
    printf("                                                            |  2 Up, 0 Dn  |\n");
    printf("                                                            | Stock: %-5.2f |\n", u2_val);
    printf("                                                            +--------------+\n");
    printf("                                                           /\n");
    printf("                                   +--------------+       /\n");
    printf("                                   |  1 Up, 0 Dn  |------┘\n");
    printf("                                   | Stock: %-5.2f |\n", u1_val);
    printf("                                   +--------------+       \\\n");
    printf("                                  /                        \\\n");
    printf("                                 /                          \\\n");
    printf("+--------------+                /                            +--------------+\n");
    printf("|  Root (S0)   |---------------┘                             |  1 Up, 1 Dn  |\n");
    printf("| Stock: %-5.2f |\n", s0_val);
    printf("| Option:%-5.2f |---------------┐                             | Stock: %-5.2f |\n", option_value, m2_val);
    printf("+--------------+                \\                            +--------------+\n");
    printf("                                 \\                          /\n");
    printf("                                  \\                        /\n");
    printf("                                   +--------------+       /\n");
    printf("                                   |  0 Up, 1 Dn  |------┘\n");
    printf("                                   | Stock: %-5.2f |\n", d1_val);
    printf("                                   +--------------+       \\\n");
    printf("                                                           \\\n");
    printf("                                                            +--------------+\n");
    printf("                                                            |  0 Up, 2 Dn  |\n");
    printf("                                                            | Stock: %-5.2f |\n", d2_val);
    printf("                                                            +--------------+\n\n");

    printf("... [Lattice tree continues processing dynamically down to level %d] ...\n", total_level);
    std::cout << "=================================================================================\n\n";
}
