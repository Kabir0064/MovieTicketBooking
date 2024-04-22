#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <random>
#include <set>
using namespace std;

int f = 1;

class seats {
public:
    vector<vector<int> > theater_seats;
    vector<int> rand_nums;
    int arraySize = rand()%10;

void rand_num_gen() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 29);
    std::set<int> unique_nums; 
    while (unique_nums.size() < arraySize) {
        int random_number = dis(gen); 
        unique_nums.insert(random_number);
    }
    rand_nums.assign(unique_nums.begin(), unique_nums.end());
}
    bool isAvl(int seatRow, int seatCol) {
        if (theater_seats[seatRow][seatCol] == 1) {
            return false;
        } else {
            return true;
        }
    }

    seats() {
        theater_seats = vector<vector<int> >(5, vector<int>(6, 0));
        rand_num_gen();
        int dcount = 0;
        int l = 0;
        while (dcount < 10) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (l == rand_nums[dcount]) {
                        theater_seats[i][j] = 1;
                    }
                    l++;
                }
            }
            dcount++;
        }
    }

    void print_seats() {
        char c = 'A';
        int d = 1;
        int k=0;
        int kc=0;
        while(k<arraySize){
            for(int i=0;i<5;i++){
                for(int j=0;j<6;j++){
                    if (kc==rand_nums[k]){
                        k++;
                        theater_seats[i][j]=1;
                    }
                    kc++;
                }
            }
        }
            std::cout << "____________________________\n"
         << "\t\t\tSCREEN\t\t\t\n"
         << "____________________________\n\n\n";

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (isAvl(i,j)) {
                    cout << "[" << c << "," << d << "]" << "\t";
                } else {
                    cout << "\t";
                }
                d++;
            }
            cout << endl;
            c++;
            d = 1;
        }
    }
};

class payment;
class customer
{
    string password;
    string username;
    string email;
    long int wallet_bal;

public:
    // Getter and setter for username
    string get_username() const {
        return username;
    }

    void set_username(const string& new_username) {
        username = new_username;
    }

    // Getter and setter for password
    string get_password() const {
        return password;
    }

    void set_password(const string& new_password) {
        password = new_password;
    }
    friend class payment;
    
    long int get_wbal(){
        return wallet_bal;
    }
    void set_wbal(long int num){
        wallet_bal = num;
    }
    
    void login(string user,string paas)
    {   
        username=user;
        password=paas;

        ifstream file("customer_details.txt");

        string line;
        bool found = false;
        while (getline(file, line))
        {
            size_t pos = line.find(",");
            string name = line.substr(0, pos);
            string pass = line.substr(pos + 1);

            if (name == username && pass == password)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << "Login successful.\n\n\n";
        }
        else
        {
            cout << "Invalid username or password.\n\n";
            f = 0;
        }

        file.close();
    }

    bool usernameExists(const string &username, ifstream &file)
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(",");
            string existingUsername = line.substr(0, pos);
            if (existingUsername == username)
            {
                return true; // Username exists
            }
        }
        return false; // Username does not exist
    }

    int Register(string user)
    {
        const int bonusamt = 200;
        ifstream readFile("customer_details.txt");
        if (!readFile.is_open())
        {
            cout << "Unable to open file.\n";
        }

        // Get new customer details from user
        username=user;

        // Check if username already exists
        if (usernameExists(username, readFile))
        {
            cout << "Username already exists.\n";
            return 0;
        }

        // Close the file
        readFile.close();

        // Open the file in append mode to add new customer details
        ofstream writeFile("customer_details.txt", ios::app);
        if (!writeFile.is_open())
        {
            cout << "Unable to open file.\n";
        }
        // -- for output to the money.txt
        ofstream moneyfile("money.txt",ios::app);
        if (!moneyfile.is_open())
        {
            cout << "Unable to open file.\n";
        }
        moneyfile << endl << username << "," << bonusamt;
        // Get password from user
        cout << "Enter password: ";
        std::cin >> password;

        // Write new customer details to the file
        writeFile << username << "," << password << endl;
        cout << "New customer details added successfully.\n";

        // Close the file
        moneyfile.close();
        writeFile.close();

        // Write new customer details to the file
        // file << username << "," << password << endl;
        // cout << "You are Successfully Registered.\n";
        // file.close();
    }

    friend void book_ticket();
};

class payment : public customer {
    long int amt;
    public :
    long int balance = get_wbal();
    string as=username;
    string str;
    
    void show_balance(const string& username_to_check) const {
        ifstream moneyfile("money.txt");
        if (!moneyfile) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        string line;
        while (getline(moneyfile, line)) {
            istringstream iss(line);
            string name;
            long int money;
            getline(iss, name, ','); // Read username until comma
            iss >> money; // Read balance after comma
            if (name == username_to_check) {
                cout << money << endl;
                return;
            }
        }
        cout << "User not found or balance not available." << endl;
        moneyfile.close();
    }

 int get_balance(string user){
           ifstream inFile("money.txt");
        ofstream outFile("temp_money.txt");
        
        if (!inFile) {
            cerr << "Error: Unable to open input file." << endl;
            return 0;
        }
        if (!outFile) {
            cerr << "Error: Unable to open output file." << endl;
            return 0;
        }

        string line;
        bool userFound = false;
        while (getline(inFile, line)) {
            string usr;
            long int bal;
            stringstream ss(line);
            getline(ss, usr, ',');
            ss >> bal;

            if (usr == username) {
                
                return bal;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        
        if (!userFound) {
            cerr << "Error: User not found." << endl;
            return 0;
        }

        // Rename temp file to original file
        remove("money.txt");
        rename("temp_money.txt", "money.txt");
        return 0;

    }
    
    void set_wbl(const string& username_to_check, long int new_balance) {
        ifstream inFile("money.txt");
        ofstream outFile("temp_money.txt");
        
        if (!inFile) {
            cerr << "Error: Unable to open input file." << endl;
            return;
        }
        if (!outFile) {
            cerr << "Error: Unable to open output file." << endl;
            return;
        }

        string line;
        bool userFound = false;
        while (getline(inFile, line)) {
            string usr;
            long int bal;
            stringstream ss(line);
            getline(ss, usr, ',');
            ss >> bal;

            if (usr == username_to_check) {
                bal = new_balance;
                outFile << usr << "," << bal << endl;
                userFound = true;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        
        if (!userFound) {
            cerr << "Error: User not found." << endl;
            return;
        }

        // Rename temp file to original file
        remove("money.txt");
        rename("temp_money.txt", "money.txt");

        cout << "Balance updated successfully." << endl;
    }
   void add_bal(long int amount, const string& username_to_check) {
        ifstream inFile("money.txt");
        ofstream outFile("temp_money.txt");
        
        if (!inFile) {
            cerr << "Error: Unable to open input file." << endl;
            return;
        }
        if (!outFile) {
            cerr << "Error: Unable to open output file." << endl;
            return;
        }

        string line;
        bool userFound = false;
        while (getline(inFile, line)) {
            string usr;
            long int bal;
            stringstream ss(line);
            getline(ss, usr, ',');
            ss >> bal;

            if (usr == username_to_check) {
                bal += amount;
                outFile << usr << "," << bal << endl;
                userFound = true;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        
        if (!userFound) {
            cerr << "Error: User not found." << endl;
            return;
        }

        // Rename temp file to original file
        remove("money.txt");
        rename("temp_money.txt", "money.txt");

        cout << "Balance updated successfully." << endl;
    }
 
};

class Movie
{
    string title;
    float imdb;
    string genre;
    int duration;
    string language;

public:
    void show_Movie()
    {
        int moviecount = 1;
        ifstream file("Movies.txt");
        if (!file.is_open())
        {
            cout << "Unable to open file.\n";
        }
        cout << left << setw(30) << "Title" << setw(8) << "IMDB" << setw(15) << "Genre" << setw(10) << "Duration"
             << "Languages" << endl;
        cout << setfill('-') << setw(70) << "-" << endl;
        cout << setfill(' ');

        while (getline(file, title, ','))
        {
            file >> imdb;
            file.ignore(); // Ignore the comma
            getline(file, genre, ',');
            file >> duration;
            file.ignore(); // Ignore the comma
            getline(file, language);

            cout << moviecount << '.' << setw(10) << left << setw(30) << title.substr(0, 30) << setw(8) << fixed << setprecision(1) << imdb << setw(15) << genre << setw(10) << duration << language << endl;
            cout << endl;
            moviecount += 1;
        }

        file.close();
    }
};


class showtime
{
public:
    string getshowtime(int line_number, int tn, int sn)
    {
        ifstream movies_file("Movies.txt");
        
        if (!movies_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return "Error";
        }

        string line;
        for (int i = 0; i < line_number; ++i)
        {
            getline(movies_file, line);
            if (movies_file.eof())
            {
                cout << "Error: Line number exceeds the number of movies!" << endl;
                return "Error";
            }
        }

        // Extract the movie name from the line
        stringstream ss(line);
        string movie_name;
        getline(ss, movie_name, ',');

        ifstream theater_file("theater.txt");

        if (!movies_file.is_open() || !theater_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return "Error";
        }

        string theater_info;
        bool mf = false;
        int j = 0;
        int k = 0;
        int l = 0;
        while (getline(theater_file, theater_info))
        {
            stringstream ss(theater_info);
            vector<string> theater_details;
            string detail;
            while (getline(ss, detail, ','))
            {
                theater_details.push_back(detail);
            }

            if (theater_details[0] == movie_name)
            {
                mf = true;
                j += 1;
                if (j == tn)
                {
                    while (k < 3)
                    {
                        k++;
                        if (k == sn)
                        {
                            return theater_details[k + 1];
                        }
                    }
                }
            }
            theater_details.clear();
        }
        if (!mf)
        {
            cout << "Error: Movie not found in theater schedule!" << endl;
        }
        return "Error";
    }
    void displayshowtime(int line_number, int tn)
    {
        ifstream movies_file("Movies.txt");

        if (!movies_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string line;
        for (int i = 0; i < line_number; ++i)
        {
            getline(movies_file, line);
            if (movies_file.eof())
            {
                cout << "Error: Line number exceeds the number of movies!" << endl;
                return;
            }
        }

        // Extract the movie name from the line
        stringstream ss(line);
        string movie_name;
        getline(ss, movie_name, ',');

        ifstream theater_file("theater.txt");

        if (!movies_file.is_open() || !theater_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string theater_info;
        bool mf = false;
        int j = 0;
        int k = 0;
        cout << "\nMovie Name: " << movie_name << endl;
        while (getline(theater_file, theater_info))
        {
            stringstream ss(theater_info);
            vector<string> theater_details;
            string detail;
            while (getline(ss, detail, ','))
            {
                theater_details.push_back(detail);
            }

            if (theater_details[0] == movie_name)
            {
                mf = true;
                j += 1;
                if (j == tn)
                {
                    while (k < 3)
                    {
                        k++;
                        cout << "[" << k << "]" << theater_details[k + 1] << endl;
                    }
                }
            }
            theater_details.clear();
        }
        if (!mf)
        {
            cout << "Error: Movie not found in theater schedule!" << endl;
        }
    }
    string getmoviename(int line_number){
        ifstream movies_file("Movies.txt");

        if (!movies_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return "Error";
        }

        string line;
        for (int i = 0; i < line_number; ++i)
        {
            getline(movies_file, line);
            if (movies_file.eof())
            {
                cout << "Error: Line number exceeds the number of movies!" << endl;
                return "Error";
            }
        }

        // Extract the movie name from the line
        stringstream ss(line);
        string movie_name;
        getline(ss, movie_name, ',');
        return movie_name;

    }
    string gettheatername(int tn, int line_number)
    {
        ifstream movies_file("Movies.txt");

        if (!movies_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return "Error";
        }

        string line;
        for (int i = 0; i < line_number; ++i)
        {
            getline(movies_file, line);
            if (movies_file.eof())
            {
                cout << "Error: Line number exceeds the number of movies!" << endl;
                return "Error";
            }
        }

        // Extract the movie name from the line
        stringstream ss(line);
        string movie_name;
        getline(ss, movie_name, ',');

        ifstream theater_file("theater.txt");

        if (!movies_file.is_open() || !theater_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return "Error";
        }

        string theater_info;
        bool mf = false;
        int j = 0;
        cout << "\nMovie Name: " << movie_name << endl;
        cout<<"\n";
        while (getline(theater_file, theater_info))
        {
            stringstream ss(theater_info);
            vector<string> theater_details;
            string detail;
            while (getline(ss, detail, ','))
            {
                theater_details.push_back(detail);
            }

            if (theater_details[0] == movie_name)
            {
                mf = true;
                j += 1;
                if (j == tn)
                {
                    return theater_details[1];
                }
            }
            theater_details.clear();
        }
        if (!mf)
        {
            cout << "Error: Movie not found in theater schedule!" << endl;
        }
        return "wrong number";
    }
    void viewshows(int line_number)
    {
        ifstream movies_file("Movies.txt");

        if (!movies_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string line;
        for (int i = 0; i < line_number; ++i)
        {
            getline(movies_file, line);
            if (movies_file.eof())
            {
                cout << "Error: Line number exceeds the number of movies!" << endl;
                return;
            }
        }

        // Extract the movie name from the line
        stringstream ss(line);
        string movie_name;
        getline(ss, movie_name, ',');

        ifstream theater_file("theater.txt");

        if (!movies_file.is_open() || !theater_file.is_open())
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string theater_info;
        bool mf = false;
        int j = 0;
        cout << "\nMovie Name: " << movie_name << endl;
        while (getline(theater_file, theater_info))
        {
            stringstream ss(theater_info);
            vector<string> theater_details;
            string detail;
            while (getline(ss, detail, ','))
            {
                theater_details.push_back(detail);
            }

            if (theater_details[0] == movie_name)
            {
                mf = true;
                j += 1;

                cout << "[" << j << "] Theater Name: " << theater_details[1] << endl;
                cout<<"\n";
                cout << "     Showtimes: " << theater_details[2] << ", " << theater_details[3] << ", " << theater_details[4] << endl;
                cout<<"\n\n";
            }
            theater_details.clear();
        }
        if (!mf)
        {
            cout << "Error: Movie not found in theater schedule!" << endl;
        }
    }
};

int integer(char cha){
    vector<char> kar;
    char kh = 'A';
    for(int i = 0; i < 5; i++){
        kar.push_back(kh+i);
    } 

    for(int i=0;i<5;i++){
        if(toupper(cha)==kar[i]){
            return i;
        }
    }
    return -1;
}

void clearScreen() {
        std::cout<<"\n";
    }

int main()
{
    int c = 1;
    char t;
    int ip0;
    for (int c = 1; c <= 1; c += 0)
    {
        int a;
        int seatcost=180;
        customer *c1 = new customer;
        Movie *m = new Movie;
        showtime *s = new showtime;
        seats *se=new seats;
        payment *p=new payment;
        string user,paas;
    loop1:
    cout<<"\n\n";
    cout <<
    "                  ========================        ==========================        ======================\n"
    "                  * (1)  LOGIN            *        * (2) REGISTER *                * (3) QUIT            *\n"
    "                  ========================        ==========================        ======================\n\n";      
     std:: cin >> a;
        cout<<"\n\n";
        if (a == 1)

        {   
            
            cout<<"Enter username: ";
            cin>>user;
            cout<<"\n";
            cout<<"Enter password: ";
            cin>>paas;
            cout<<"\n";
            p->login(user,paas);
            
            if (f)

            { char ca;
            cout<<"Your current balance in wallet is: ";
            p->show_balance(user);
            cout<<"\n\n";
            cout<<"Do you wish to add money or would you like to continue? [A,C]";
            std:: cin >> ca;
            cout<<"\n\n";
            if(ca=='A'||ca=='a'){
                clearScreen();
                cout<<"Enter the amount: ";
                int amount;
                std::cin >>amount;
                p->add_bal(amount,user);
                cout<<"Amount is Succesfully added, Your current balance is: " <<endl;
                p->show_balance(user);
            }
                  loop7:
                  clearScreen();
                cout << "Show Available Movies[y/n]: ";
                cout<<"\n\n";
                std::cin >> t;
                if (t == 'y' || t == 'Y')
                {
                loop2:
                    m->show_Movie();
                    cout << "Enter your movie choice: ";
                    std ::cin >> ip0;
                    clearScreen();
                    switch (ip0)
                    {
                    case 1:
                        s->viewshows(ip0);
                        break;
                    case 2:
                        s->viewshows(ip0);
                        break;
                    case 3:
                        s->viewshows(ip0);
                        break;
                    case 4:
                        s->viewshows(ip0);
                        break;
                    case 5:
                        s->viewshows(ip0);
                        break;
                    case 6:
                        s->viewshows(ip0);
                        break;
                    case 7:
                        s->viewshows(ip0);
                        break;
                    case 8:
                        s->viewshows(ip0);
                        break;
                    case 9:
                        s->viewshows(ip0);
                        break;
                    case 10:
                        s->viewshows(ip0);
                        break;
                    case 11:
                        s->viewshows(ip0);
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            {
                f = 1;
                goto loop1;
            }
        loop3:
            cout << "Display the movies again ,Proceed or end ? [D/P/E]: ";
            std::cin >> t;
            cout<<"\n\n";
            if (t == 'e' || t == 'E')
            {
                return 0;
            }
            else if (tolower(t) == 'd')
            {
                clearScreen();
                goto loop2;
            }
            else if (tolower(t) == 'p')
            {
                int tn;
                int sn;
                cout << "Enter the theater: ";
                std::cin >> tn;
                string theatername = s->gettheatername(tn, ip0);
                cout << "Your selected movie theater is: " << theatername << endl;
                cout<<"\n\n";
                cout << "Select Showtime: ";
                s->displayshowtime(ip0, tn);
                cout << "Enter ";
                std::cin >> sn;
                clearScreen();
                string st = s->getshowtime(ip0, tn, sn);
                cout << "Your selected showtime is " << st << endl;
                se->print_seats();
                loop4:
                cout<<"\n\n";
                loop8:
                cout<<"Select no.of seats you want: ";
                cout<<"\n";
                int tic;
                std::cin>>tic;
                if(tic<1 || tic>30){
                    cout<<"Enter valid seat number (Maximum Limit is 30)"<<endl;
                    goto loop8;
                }
                long int amount=tic*seatcost;
                cout<<"Total price for "<<tic<<" tickets is :"<<tic*seatcost<<endl;
                cout<<"\n";
                vector<char> alphabet;
                vector<int> integer1;
                for(int i=0;i<tic;i++){
                cout<<"Select the row and column: ";
                char row_name;
                int cl_name;
                std::cin>>row_name>>cl_name;
                int integer_row_eq;
                integer_row_eq=integer(row_name);
                if(integer_row_eq==-1){
                    cout<<"Enter Valid Seat Number"<<endl;
                    goto loop4;
                }
                
                bool seatAvailability;
                seatAvailability = se->isAvl(integer_row_eq,cl_name-1);
                if(seatAvailability){
                    se->theater_seats[integer_row_eq][cl_name-1]=1;
                    alphabet.push_back(row_name);
                    integer1.push_back(cl_name);
                }
                else{
                    cout<<"Select a Different Seat"<<endl;
                    goto loop4;
                }

                }
                
                p->show_balance(user);
                cout<<endl;
                int as=p->get_balance(user);
                loop5:
                if(amount>as){
                    cout<<"Your current balance isn't sufficient.Please select one of the following options."<<endl;
                    cout<<"\n[1]Add balance [2]Exit "<<endl;
                    int q;
                    cin>>q;
                    if(q==1){
                        int qw;
                        cout<<"\n";
                        cout<<"Minimum amount to be added : "<<amount-as<<endl;
                        cout<<"\n";
                        cout<<"Enter amount you wish to add: ";
                        cin>>qw;
                        p->add_bal(qw,user);
                        as=p->get_balance(user);
                        if(as<amount){
                            goto loop5;
                        }
                        goto loop6;
                    }
                    else if(q==2){
                        goto loop1;
                    }
                    else{
                        cout<<"Enter correct number"<<endl;
                        goto loop5;
                    }
                } 
                else {
                    loop6:
                    char qa;
                    cout<<"Your balance is enough do you wish to continue payment :[y/n]";
                    cin>>qa;
                    
                    if(tolower(qa) == 'y'){
                        clearScreen();
                        int remaining_amount=as-amount;
                        string mn=s->getmoviename(ip0);
                        p->set_wbl(user,remaining_amount);
                        cout<<"Remaining Balance in your account is :"<<remaining_amount<<endl;
                        cout<<"\n\n";
                        cout << "=========================================================\n"
                            << "=                         RECEIPT                       =\n"
                             << "---------------------------------------------------------\n"
                             << "=                       MOVIE TICKET                    =\n"
                            << "=========================================================\n\n";
                        cout<<"|Username: "<<user<<endl;
                        cout<<"|Moviename:"<<mn<<endl;
                        cout<<"|Theatername: "<<theatername<<endl;
                        cout<<"|Showtime: "<<st<<endl;
                        cout<<"|Selected seats: ";
                        for(int i=0;i<alphabet.size();i++){
                            cout<<alphabet[i]<<" "<<integer1[i]<<",";}
                            cout<<endl;
                        cout<<"-----------------------"<<endl;
                        cout<<"Do you wish to book another movie:[y/n] ";
                        cout<<"\n";
                        char q2;
                        cin>>q2;
                        if(tolower(q2)=='y'){
                            clearScreen();
                            goto loop7;
                        }
                        else if(tolower(q2)=='n'){
                            clearScreen();
                            goto loop1;
                        }
                        else{
                            cout<<"Enter valid choice "<<endl;
                        }

                    }
                    else if(tolower(qa)=='n'){
                        goto loop7;
                    }
                }
                

                se->print_seats();
                goto loop1;

            }
            else
            {
                cout << "Enter a valid choice "<<endl;
                goto loop3;
            }
        }
        else if (a == 2)
        {   cout<<"Enter username: ";
            cin>>user;
            p->Register(user);
            cout<<"You have recieved 200 Ruppees in your wallet as a Registeration Bonus"<<endl;
        }
        else if (a == 3)
        {
            return 0;
        }
        else
        {
            cout << "Enter Valid Number" << endl;
        }
    }
    return 0;
}