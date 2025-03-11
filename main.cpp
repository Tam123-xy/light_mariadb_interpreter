#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <unordered_map>
using namespace std;
namespace fs = std::filesystem;

// Function prototypes
void print_table(const vector<variant<string, vector<variant<int, string>>>>& table, const vector<string> attribute);
vector<string> f_insert(const string insert_into, const string cond_start,const string cond_end, const int num);
string get_table_name(const vector<string> word, const size_t i);
int total_count(const vector<variant<string, vector<variant<int, string>>>>& table);
string full_sql_command(const vector<string> word, const size_t i);
string f_update(const string update_sql, const string cond_start,const string cond_end, const int num);


int main() {
    vector<variant<string, vector<variant<int, string>>>> table;
    vector<variant<int,string>> daT_values;
    vector<std::string> inputfiles;
    string path = R"(C:\Users\User\Documents\Degree year 1\Programming fundamentals\light_mariadb_interpreter)";  // Change this to your folder path
    string line;
    vector<string> words;
    vector<string> word;
    vector<string> attribute_dataType;
    vector<string> attribute;
    vector<string> dataType;
    int j;
    bool create_table= true;
    bool datatype= false;
    bool insert = true;
    string tableName, file_outputName, type, insert_value,insert_table,select_table,count_table, update_table ;
    string insert_into, update;
    bool repeat_equal_sign = false;
    string final_sql;
   
    // Detect file mdb 
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mdb") {  
            inputfiles.push_back(entry.path().filename().string());
        }
    }
   
    // No file mdb founded
    if (inputfiles.size() == 0){
        cout << "No mdb file founded in path "<< path << endl << "You may change the path in main.cpp";
    }

    else{

        // Loop each file
        for (size_t i = 0; i < inputfiles.size(); ++i) {
            ifstream dataIn(inputfiles[i]);

            // Check file is empty
            if (dataIn.peek() == ifstream::traits_type::eof()) {
                cout << inputfiles[i] << " is empty!" << endl;}

            else {

                // Loop the file line and put in variable line
                while (std::getline(dataIn, line)){

                    stringstream ss(line);
                    string theline;

                    // Loop variable line and split by space store in vector words
                    while (getline(ss, theline, ' ')) {
                        words.push_back(theline);}
                }

                // Remove spaces form each element and store in vector word
                for (int i = 0; i < words.size(); i++) {
                    string results; 
                    for (char c : words[i]) {
                        if (c != ' ') {
                            results += c;
                        }
                    }
                    if (!results.empty()) { 
                        word.push_back(results);
                    }
                }

                // Loop vector words
                for (i=0; i < word.size(); i++){

                    // Handle CREATE
                    if (word[i] == "CREATE"){

                        // Create file output
                        if (word[i+1].find(".txt;")!= string::npos ){
                            for (char c : word[i+1]) {
                                if (c != ';') { 
                                    file_outputName += c;}}
                            ofstream file(file_outputName);}
                           
                        
                        // Create table
                        else if (word[i+1].find("TABLE")!= string::npos){

                            //First time create table, user only can create one tabe.
                            if(create_table==true){
                                create_table = false;

                                // Obtain table name
                                for (char c : word[i+2]) {
                                    if (c != '(') { 
                                        tableName += c;}
                                }

                                table.push_back(tableName);

                                // Put only atribute and data type into vector table
                                for (j = i+3; j < word.size(); j++){
                                    if (word[j] == ");"){ break;};
                                    attribute_dataType.push_back(word[j]);}

                                // Obtain attribute and data type seprately in vector attribute and vector type
                                for (j = 0; j < attribute_dataType.size(); j++){

                                    if (datatype == false){
                                        attribute.push_back(attribute_dataType[j]);
                                        datatype = true;
                                    }

                                    else if (datatype == true){

                                        if(attribute_dataType[j] == "TEXT," || attribute_dataType[j] == "TEXT"){ 
                                                type = "string";}
                                        else if (attribute_dataType[j] == "INT," || attribute_dataType[j] == "INT"){
                                                type = "int";}

                                        else {
                                            cout << "Unsupport data type of " << attribute_dataType[j] << " .Please check you CREATE TABLE sql command, we only support INT and STRING data type";
                                            exit(0);
                                        }

                                        dataType.push_back(type); 
                                        datatype = false;
                                    }
                                }
                            }

                            else if(create_table == false){
                                cout << "You only can create one table. You have created "<< tableName << " table" << endl;
                            }
                        }
                    }

                    // Handle INSERT INTO
                    else if (word[i] == "INSERT" && word[i+1]== "INTO"){

                        // Obtain INSERT INTO sql command
                        insert_into = full_sql_command(word,i+2);

                        // Obtain table name
                        for (char c : insert_into) {
                            if (c != '(') { 
                                insert_table += c;}

                            else{break;}
                        }

                        // Check is the table created
                        if(insert_table == get<string>(table[0])){

                            insert_table.clear();

                            // Obtain attributes 
                            string cond_start ="(";
                            string cond_end =")";
                            int num = 1;
                            vector<string> insert_attr = f_insert(insert_into,cond_start, cond_end, num);

                            // Obtain values 
                            cond_start ="VALUES(";
                            cond_end =");";
                            num = 7;
                            vector<string> value = f_insert(insert_into,cond_start, cond_end, num);

                            
                            // Sort the value by following the oder of attribute (CREATE TABLE).
                            unordered_map<string, string> value_map;
                            for (size_t j = 0; j < insert_attr.size(); j++) {
                                value_map[insert_attr[j]] = value[j];
                            }

                            std::vector<std::string> sorted_values;
                            for (const auto& key : attribute) {
                                sorted_values.push_back(value_map[key]);
                            }

                            // Change the data type of value by following the data type given (CRETE TABLE).
                            for(size_t j =0; j<dataType.size(); j++){
                                
                                if(dataType[j] == "int"){
                                    try{ daT_values.push_back(stoi(sorted_values[j]));}
                                    
                                    // When the values cannot change to int.
                                    catch (const std::invalid_argument&){
                                        cout << "Error: \"" << sorted_values[j] << "\" is not a valid integer. "
                                             << "Please check your INSERT INTO and CREATE TABLE SQL command." << endl;
                                        exit(1); 
                                    }
                                    
                                }
                                else{daT_values.push_back(sorted_values[j]);}
                            }

                            table.push_back(daT_values);
                            daT_values.clear();
                            insert_into.clear();
                        }
                        else{
                            cout<<"Error, "<< insert_table << " table dosen't exit. Please check your INSERT INTO sql command"<< endl;
                        }
                    }

                    else if (word[i] == "SELECT*" || (word[i] == "SELECT" && word[i+1] == "*")){

                        select_table = get_table_name(word,i);

                        // Check is the table created
                        if(select_table == get<string>(table[0])){
                            print_table(table,attribute);
                        }

                        else{
                            cout << select_table << " table doesn't exit. Please check your SELECT* sql command.";
                        }
                    }

                    else if (word[i] == "SELECT" && word[i+1] == "COUNT(*)"){

                        count_table = get_table_name(word,i+2);

                        if(count_table == get<string>(table[0])){
                            int num_count = total_count(table);

                            cout << "Total row of data from table " << count_table << " is " << num_count<< "."<< endl;
                        }

                        else{
                            cout << count_table << " table doesn't exit. Please check your SELECT(*) COUNT sql command.";
                        }
                    }

                    else if (word[i] == "UPDATE"){

                        update_table = word[i+1];

                        // Check is the table created
                        if(update_table == get<string>(table[0])){
                            
                            update = full_sql_command(word,i+2);

                            for (size_t j = 0; j < update.size(); j++) {

                                if (update[j] == '=') {
                                    final_sql += repeat_equal_sign ? "==" : "=";
                                    repeat_equal_sign = true;
                                }

                                else if (update[j] == ';'){
                                    break;
                                }
                                
                                else {
                                    final_sql += update[j];
                                }
                            }

                            cout << final_sql << endl;
                        

                            // Obtain attribute
                            string cond_start ="SET";
                            string cond_end ="=";
                            int num = 3;
                            string update_att = f_update(final_sql,cond_start, cond_end, num);

                            cout<< update_att<< endl;

                            // Obtain attribute 
                            cond_start ="WHERE";
                            cond_end ="==";
                            num = 5;
                            string update_where_att = f_update(final_sql,cond_start, cond_end, num);

                            cout<< update_where_att<< endl;

                            break;

                        }
                        else{
                            cout << update_table << " table doesn't exit. Please check your UPDATE sql command.";
                        }
                    }
            }
        }
    }

}
    return 0;

}

// Function of printing the table
void print_table(const vector<variant<string, vector<variant<int, string>>>>& table, const vector<string> attribute ){
    
    cout << endl;
    for (const auto& row : table) {
        if (holds_alternative<string>(row)) {
            cout << "TABLE " << get<string>(row) << endl;
        }
    }

    for(int i=0; i<attribute.size(); i++){
        cout<< attribute[i]<< " ";
    }

    cout << endl;

    for (const auto& row : table) {
        if (holds_alternative<vector<variant<int, string>>>(row)) {
            cout << "Data: ";
            for (const auto& item : get<vector<variant<int, string>>>(row)) {
                if (holds_alternative<int>(item)) {
                    cout << get<int>(item) << " ";
                } else if (holds_alternative<string>(item)) {
                    cout << get<string>(item) << " ";
                }
            }
            cout << endl;
        }
    }
}

// Function of finding attributes and the values from the INSERT INTO sql command.
vector<string> f_insert(const string insert_into, const string cond_start,const string cond_end, const int num){
    size_t start = insert_into.find(cond_start) + num;
    size_t end = insert_into.find(cond_end);
    string insert = insert_into.substr(start, end - start);
    insert = insert.substr(0, insert.size());

    vector<string> insert_;  // Vector to store split values
    stringstream ss(insert);
    string token;

    // Split string using ',' as the delimiter
    while (getline(ss, token, ',')) {
        insert_.push_back(token);
    }

    return insert_;
}

// Function of finding the table name from SELECT* and SELECT COUNT sql command.
string get_table_name(const vector<string> word, const size_t i){
    int j=0;
    string table_name;

    for (j=i+1 ; j<word.size(); j++){
        if(word[j] == "FROM"){
            table_name = word[j+1];
            break;
        }
    }

    size_t pos = table_name.find(';');
    if (pos != string::npos) {
        table_name.erase(pos, 1); // Erase one character at the found position
    }
    return table_name;
}

int total_count(const vector<variant<string, vector<variant<int, string>>>>& table){
    cout << endl;
    int i=0;

    for (const auto& row : table) {
        if (holds_alternative<vector<variant<int, string>>>(row)) {
            i+=1;
        }
    }

    return i;
}

// Function to get INSERT INTO, UPDATE full sql command start from the table name.
string full_sql_command(const vector<string> word, const size_t i){
    int j;
    bool s_condition= true;
    bool second= false;
    string sql;

    // Obtain INSERT INTO sql command
    for (j = i; j<word.size(); j++){
        if (s_condition == true){
            sql+=word[j];

            if (word[j].find(";") != string::npos) {
                s_condition = false;
            }
        }
    }
    return sql;
}

// Function of finding attributes and the values from the UPDATE sql command.
string f_update(const string update_sql, const string cond_start,const string cond_end, const int num){

    size_t start = update_sql.find(cond_start) + num;
    size_t end = update_sql.find(cond_end);
    string update = update_sql.substr(start, end - start);
    update = update.substr(0, update.size());

    return update;
}
