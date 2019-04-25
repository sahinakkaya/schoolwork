/* You need to define MAX_OPERATOR_SIZE *before* including this file. */

#include <iostream>
#include <vector>
#include <map>
#define DIRECTIONS
#define RIGHT {0, 1}
#define LEFT {0, -1}
#define TOP {-1, 0}
#define BOTTOM {1, 0}
#define TOP_RIGHT {-1, 1}
#define TOP_LEFT {-1, -1}
#define BOTTOM_RIGHT {1, 1}
#define BOTTOM_LEFT {1, -1}
using namespace std;

class Operator{
    int center_x;
    int center_y;
    int op_size;
    int previous_x;
    int previous_y;
    int previous_size;
    void set_prev_y() {previous_y = center_y;}
    void set_prev_x() {previous_x = center_x;}
    void set_prev_size() {previous_size = op_size;}
  public:
    Operator(int, int, int);
    void reset(int,int,int);
    void set_x(int val) {center_x=val;}
    int get_x() const {return center_x;}
    void set_y(int val) {center_y = val;} 
    int get_y() const {return center_y;}
    void set_size(int val) {op_size = val;} 
    int get_size() const {return op_size;}
    int get_prev_x() const {return previous_x;}
    int get_prev_y() const {return previous_y;}
    int get_prev_size() const {return previous_size;}
};

Operator::Operator(int x, int y, int size){
    center_x = x;
    center_y = y;
    op_size = size;
}

void Operator::reset(int x,int y,int size){
    set_prev_x();
    set_prev_y();
    set_prev_size();
    set_x(x);
    set_y(y);
    set_size(size);
}

class ArithmeticOperator: public Operator{
    char sign;
    vector<vector<int>> directions;
    int direction_count;
    void set_directions();

  public:
    ArithmeticOperator(int,int,int,char);
    ~ArithmeticOperator();
    int get_direction_count() const { return direction_count;}
    vector<vector<int>> get_directions() const { return directions;}
    char get_sign() const { return sign;}
    void print_operator() const;
    void print_directions() const;
};

ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign):Operator(x,y,size){
    switch(sign)
    {
        case '-':        
        case '+':
        case 'x':
        case '/':
            this->sign = sign;
            set_directions();
            break;
        default:
            cout << "SIGN parameter is invalid!"<<endl;
            this->sign = '0';
            break;
    }
}

void ArithmeticOperator::print_operator() const{
    cout << "ARITHMETIC_OPERATOR["<<get_sign()<<"], "
         << "CENTER_LOCATION["<<get_x()<<","<<get_y()<<"], "
         << "SIZE["<<get_size()<<"]"<<endl;
}


ArithmeticOperator::~ArithmeticOperator(){
}
void ArithmeticOperator::print_directions() const{
    cout << sign << ": "<< endl;
    for(int i = 0;i<direction_count;i++){
        for(int j = 0; j<2;j++){
            cout << directions[i][j] << ", ";
        }
        cout << endl;
    }
}

void ArithmeticOperator::set_directions(){
    if (sign == '-')
        directions = {LEFT, RIGHT};
    else if(sign == '+')
        directions = {LEFT, RIGHT, TOP, BOTTOM};
    else if(sign == '/')
        directions = {TOP_RIGHT, BOTTOM_LEFT};
    else
        directions = {TOP_RIGHT, TOP_LEFT, BOTTOM_RIGHT, BOTTOM_LEFT};
    if(sign == '-' || sign == '/')
        direction_count = 2;
    else 
        direction_count = 4;
}
class OperatorGrid{
    int grid_rows;
    int grid_cols;
    char** grid;
    int num_operators;
    ArithmeticOperator* operators[MAX_OPERATOR_SIZE];

    void init_vals_with_operator(ArithmeticOperator*, int&, int&, int&,int&, char&);
    bool errors_in_placement(ArithmeticOperator*, int&);
    bool causes_border_error(ArithmeticOperator*);
    bool causes_conflict_error(ArithmeticOperator*);
    void handle_errors(const ArithmeticOperator&, const int&, bool = false);
    bool is_in_borders(int&, int&);
    void print_message(const ArithmeticOperator&, string, bool, bool = false);
    void write_symbols_to_grid(int, int, int, vector<vector<int>>, int, char);
  public:
    OperatorGrid(int,int);
    ~OperatorGrid();

    bool place_operator(ArithmeticOperator* op, bool = false);
    bool move_operator(int,int, char, int);
    void print();
    void print_operators();
    
};
OperatorGrid::OperatorGrid(int rows, int cols){
    grid_rows = rows;
    grid_cols = cols;
    num_operators = 0;
    grid = new char*[grid_rows];
    for(int i =0;i<grid_rows;i++){
        grid[i] = new char[grid_cols];
        for(int j = 0;j<grid_cols;j++)
            grid[i][j] = 'O';
    }  
}

OperatorGrid::~OperatorGrid(){
    
    for(int i = 0;i<grid_rows;i++){
        delete[] grid[i];
    }
    delete[] grid;
    cout << "DESTRUCTOR: GIVE BACK[" << grid_rows << "," << grid_cols << "] chars." << endl;
    for(int i = 0;i<num_operators;i++){
        delete operators[i];
    }
    cout << "DESTRUCTOR: GIVE BACK[" << num_operators << "] Operators." << endl;
}

void OperatorGrid::print(){
    cout << "  ";
    for(int i = 1;i<=grid_cols;i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i=0;i<grid_rows;i++){
        cout << i+1 << " ";
        for(int j = 0;j<grid_cols;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool OperatorGrid::place_operator(ArithmeticOperator* op, bool moving){
    int error_code = 1;
    int x, y, size, direction_count;
    char sign;
    init_vals_with_operator(op, x, y, size, direction_count, sign);
    if(moving){
        vector<vector<int>> directions = op->get_directions();
        if(errors_in_placement(op,error_code)){
            handle_errors(*op,error_code, moving);
            
            op->set_x(op->get_prev_x());
            op->set_y(op->get_prev_y());
            init_vals_with_operator(op, x, y, size, direction_count, sign);
            
            write_symbols_to_grid(x, y, size, directions, direction_count, sign);
            
            return false;
        }
        else{
            operators[num_operators] = op;
            for(int s = 0;s <= size;s++)
                for(int i = 0; i < direction_count; i++)
                    write_symbols_to_grid(x,y,size,directions,direction_count,sign);
            print_message(*op, "SUCCESS", true, true);
            return true;
        }
    }
    else if (num_operators<MAX_OPERATOR_SIZE){
        if (sign == '0'){
            return false;
        }
        
        ArithmeticOperator* new_op = new ArithmeticOperator(x,y,size,sign);
        if(errors_in_placement(new_op, error_code)){
            handle_errors(*new_op, error_code);
            delete new_op;
            return false;
        }
        else{
            operators[num_operators] = new_op;
            vector<vector<int>> directions = new_op->get_directions();
            for(int s = 0;s <= size;s++)
                for(int i = 0; i < direction_count; i++)
                    write_symbols_to_grid(x,y,size,directions,direction_count,sign);
            num_operators++;
            print_message(*new_op, "SUCCESS",true);
            return true;
        }
    }
    else 
        cerr << "Can not place. MAX_OPERATOR_SIZE limit (" << MAX_OPERATOR_SIZE << ") reached." <<endl;
    return false;

}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by){
    int old_x, old_y, size, direction_count, new_x, new_y, old_num_operators;
    char sign;
    bool found = false;
    int i = 0;
    vector<vector<int>> directions;
    while(!found && i< num_operators){
        init_vals_with_operator(operators[i],old_x,old_y,size,direction_count,sign);
        directions = operators[i]->get_directions();
        new_x = old_x;
        new_y = old_y;
        for(int s = 0;s <= size; s++){
            for(int j = 0; j < direction_count;j++){
                if (old_x + directions[j][0]*s == x && old_y+directions[j][1]*s== y){
                    write_symbols_to_grid(old_x,old_y,size,directions,operators[i]->get_direction_count(),'O');
                    found = true;
                    break;
                }
            }
        }
        if(!found)
            i++;
    }
    
    old_num_operators = num_operators;
    num_operators = i;
    switch (direction)
    {
        case 'R':
            operators[i]->reset(new_x, new_y + move_by, size);
            break;
        case 'L':
            operators[i]->reset(new_x, new_y - move_by, size);
            break;
        case 'U':
            operators[i]->reset(new_x - move_by, new_y, size);
            break;
        case 'D':
            operators[i]->reset(new_x + move_by, new_y, size);
            break;
        default:
            cerr << "ERROR: Direction is not valid" << endl;
            return false;
    }
    if(place_operator(operators[i], true)){
        num_operators = old_num_operators;
        return true;
    }else{
        num_operators = old_num_operators;
        return false;
    }

}

void OperatorGrid::init_vals_with_operator(ArithmeticOperator* op, int& x, int& y, int& size,int& direction_count, char& sign){
    x = op->get_x();
    y = op->get_y();
    size = op->get_size();
    direction_count = op->get_direction_count();
    sign = op->get_sign();
}

bool OperatorGrid::errors_in_placement(ArithmeticOperator* op, int& error_code){
    if(causes_border_error(op))
        error_code *= 2;
    if(causes_conflict_error(op))
        error_code *= 3;
    return error_code != 1;

}

bool OperatorGrid::causes_border_error(ArithmeticOperator* op){
    int x, y, size, direction_count;
    char sign;
    init_vals_with_operator(op, x, y, size, direction_count, sign);
    vector<vector<int>> directions = op->get_directions();

    for(int s = 0;s <= size;s++){
        for(int i = 0; i < direction_count; i++){
            int abscissa = x+directions[i][0]*s-1;
            int ordinate = y+directions[i][1]*s-1;
            if(!is_in_borders(abscissa, ordinate))
                return true;
        }
    }
    return false;

}

bool OperatorGrid::causes_conflict_error(ArithmeticOperator* op){
    int x, y, size, direction_count;
    char sign;
    init_vals_with_operator(op, x, y, size, direction_count, sign);
    vector<vector<int>> directions = op->get_directions();
    for(int s = 0;s <= size;s++){
        for(int i = 0; i < direction_count; i++){
            int abscissa = x+directions[i][0]*s-1;
            int ordinate = y+directions[i][1]*s-1;
            if(is_in_borders(abscissa, ordinate) && grid[abscissa][ordinate] != 'O')
                return true;
        }
    }
    return false;
}

void OperatorGrid::handle_errors(const ArithmeticOperator& op, const int& error_code, bool moving){
    if(error_code % 2 == 0) 
        print_message(op, "BORDER ERROR", false, moving);
    if(error_code % 3 == 0)
        print_message(op, "CONFLICT ERROR", false, moving);
}

bool OperatorGrid::is_in_borders(int& x, int& y){
    return x>=0 && x<grid_rows && y>=0 && y < grid_cols;
}
void OperatorGrid::print_message(const ArithmeticOperator& op, string message, bool success, bool moving){
    if(moving)
        cout << message << ": " << op.get_sign() << (success?" ":" can not be ") << "moved from (" 
             << op.get_prev_x() << "," << op.get_prev_y() << ") to (" << op.get_x() << "," <<op.get_y()
             << ")." << endl;
    else 
        cout << message << ": Operator " << op.get_sign() << " with size " << op.get_size() << (success?" is":" can not be")
             << " placed on (" << op.get_x() << "," << op.get_y() << ")." << endl;
}

void OperatorGrid::write_symbols_to_grid(int x, int y, int size, vector<vector<int>> directions, int direction_count, char symbol){
    for(int s = 0;s <= size;s++)
        for(int i = 0; i < direction_count; i++)
            grid[x+directions[i][0]*s-1][y+directions[i][1]*s-1] = symbol;
}

void OperatorGrid::print_operators(){
    for(int i = 0; i<num_operators;i++){
        operators[i]->print_operator();
    }
}