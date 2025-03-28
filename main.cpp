#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <variant>
#include <unordered_map>
#include <algorithm>
#include <utility>
using namespace std;
namespace fs = std::filesystem;
using InnerVector = vector<variant<int, string>>;

// Function prototypes
void print_table(const vector<variant<string, vector<variant<int, string>>>>& table, const vector<string> attribute);
void f_insert(const string insert_into, const string cond_start,const string cond_end, const int num, vector<string>& insert_, vector<string>& value_type);
string get_table_name(const vector<string> word, const size_t i);
int total_count(const vector<variant<string, vector<variant<int, string>>>>& table);
string full_sql_command(const vector<string> word, const size_t i);
string f_update(const string update_sql, const string cond_start,const string cond_end, const int num);
vector<string> sort(vector<string> insert_attr,vector<string> value,vector<string> attribute );
bool update_change_dataTYPE(const vector<string>& attribute, const vector<string>& dataType, const string& value, const string& update_att, int& index, const bool update_sql);


int main() {
    vector<variant<string, vector<variant<int, string>>>> table;
    vector<variant<int,string>> daT_values;
    vector<std::string> inputfiles;
    string path = R"(C:\Users\User\Documents\Degree year 1\sem 1\Programming fundamentals\light_mariadb_interpreter)";  // Change this to your folder path
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
    string insert_into, update, del;
    bool repeat_equal_sign = false;
    string final_sql;
    int int_val,int_where_val,r;
    string delete_table_name;
    bool delete_same_value;
   
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
                for (int i=0; i < word.size(); i++){

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
                            vector<string> insert_attr; 
                            vector<string> unless;
                            f_insert(insert_into,cond_start, cond_end, num, insert_attr,unless);


                            // Obtain values 
                            cond_start ="VALUES(";
                            cond_end =");";
                            num = 7;
                            vector<string> value; 
                            vector<string> value_type;
                            f_insert(insert_into,cond_start, cond_end, num, value, value_type);
                          
                            vector<string> sorted_values = sort(insert_attr,value,attribute);
                            vector<string> sorted_value_type = sort(insert_attr,value_type,attribute);

                            // Change the data type of value by following the data type given (CRETE TABLE).
                            for(size_t j =0; j<dataType.size(); j++){
                                
                                if(dataType[j] == "int" && sorted_value_type[j] == "i"){
                                    try{ daT_values.push_back(stoi(sorted_values[j]));}
                                    
                                    // When the values cannot change to int.
                                    catch (const std::invalid_argument&){
                                        cout << "Error: value \"" << sorted_values[j] << "\" from INSERT INTO sql is not a valid integer. "
                                             << "Please check your INSERT INTO SQL command." << endl;
                                        exit(1); 
                                    }
                                }

                                else if (dataType[j] == "string" && sorted_value_type[j] == "s"){
                                    daT_values.push_back(sorted_values[j]);
                                }

                                else if (dataType[j] == "int" && sorted_value_type[j] == "s"){
                                    cout << "Error: value \"" << sorted_values[j] << "\" from INSERT INTO sql."
                                         << "Your CREATE TABLE SQL sets the attribute's value (" << attribute[j] << ") to the INT data type. "
                                         << "However, your INSERT INTO SQL sets the value to a STRING. "
                                         << "Make sure your value in the INSERT INTO SQL does not contain quotation marks ('') and is an integer."
                                         << endl;
                                    exit(1); 
                                }

                                else{
                                    cout << "Error: value \"" << sorted_values[j] << "\" from INSERT INTO sql."
                                         << "Your CREATE TABLE SQL sets the attribute's value (" << attribute[j] << ") to the STRING data type. "
                                         << "However, your INSERT INTO SQL sets the value to a INT. "
                                         << "Make sure your value in the INSERT INTO SQL do contain quotation marks ('')."
                                         << endl;
                                    exit(1); 
                                    
                                }
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
                                    final_sql += update[j];
                                    break;
                                }
                                
                                else {
                                    final_sql += update[j];
                                }
                            }

                            repeat_equal_sign = false;
                            // cout << final_sql << endl;
                        
                            // Obtain attribute
                            string cond_start ="SET";
                            string cond_end ="=";
                            int num = 3;
                            string update_att = f_update(final_sql,cond_start, cond_end, num);
                          
                            // Obtain value 
                            cond_start ="=";
                            cond_end ="WHERE";
                            num = 1;
                            auto update_att_value = f_update(final_sql,cond_start, cond_end, num);

                            // Obtain attribute 
                            cond_start ="WHERE";
                            cond_end ="==";
                            num = 5;
                            string update_where_att = f_update(final_sql,cond_start, cond_end, num);

                            // Obtain value 
                            cond_start ="==";
                            cond_end =";";
                            num = 2;
                            auto update_where_val = f_update(final_sql,cond_start, cond_end, num);

                            final_sql.clear();
                           
                            bool has_update_att = find(attribute.begin(), attribute.end(), update_att) != attribute.end();
                            bool has_update_where_att = find(attribute.begin(), attribute.end(), update_where_att) != attribute.end();
                            
                            // Check if attribute is found
                            if(has_update_att && has_update_where_att){

                                int index_update_att, index_update_where_att;
                                bool update_sql=true;
                                bool a =update_change_dataTYPE(attribute,dataType, update_att_value ,update_att, index_update_att,update_sql);
                                bool b =update_change_dataTYPE(attribute,dataType, update_where_val, update_where_att, index_update_where_att,update_sql);
                            
                                if(a){
                                    int_val = stoi(update_att_value);
                                }

                                if(b){
                                    int_where_val = stoi(update_where_val);
                                }

                                int index= index_update_where_att;
                            
                                for (size_t i = 1; i < table.size(); ++i) {  // 跳过表头

                                    if (holds_alternative<InnerVector>(table[i])) {
                                        const InnerVector& row = get<InnerVector>(table[i]);

                                        if (index < row.size()) {

                                            if (auto* str = get_if<string>(&row[index])) {
                                                if(*str == update_where_val){
                                                    r = i;
                                                    break;
                                                }
                                            } 
                                            else if (auto* num = get_if<int>(&row[index])) {
                                                if(*num == int_where_val){
                                                   r = i;
                                                   break;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (r > 0 && holds_alternative<InnerVector>(table[r])) {

                                    auto& row = get<InnerVector>(table[r]);  // Safe access

                                    if (holds_alternative<int>(row[index_update_att])) {
                                        get<int>(row[index_update_att]) = int_val;
                                    } 

                                    else if (holds_alternative<string>(row[index_update_att])) {
                                        get<string>(row[index_update_att]) = update_att_value;
                                    }
                                } 
                                
                                else {
                                    cout << update_where_val << " no founded in attribute " << update_where_att <<" in table " << update_table<< endl ;
                                }
                                
                                r = 0;
                            }

                            else if(!has_update_att && has_update_where_att){
                                cout << "Error: Attribute \"" << update_att << "\" not found in the attribute list." << endl;
                                exit(1);
                            }

                            else if(has_update_att && ! has_update_where_att){
                                cout << "Error: Attribute \"" << update_where_att << "\" not found in the attribute list." << endl;
                                exit(1);
                            }

                            else{
                                cout << "Error: Attribute \"" << update_where_att << "\" and \" " << update_att << " \"not found in the attribute list." << endl;
                                exit(1);
                            }
                        
                        }
                        else{
                            cout << update_table << " table doesn't exit. Please check your UPDATE sql command.";
                        }
                    }

                    else if (word[i] == "DELETE" && word[i+1] == "FROM" ){

                        delete_table_name = word[i+2];

                        if(delete_table_name == get<string>(table[0])){

                            del = full_sql_command(word,i+2);

                            // cout<< del<<endl;

                            string cond_start ="WHERE";
                            string cond_end ="=";
                            int num = 5;
                            string delete_att = f_update(del,cond_start, cond_end, num);
                        
                            cond_start ="=";
                            cond_end =";";
                            num = 1;
                            string delete_val = f_update(del,cond_start, cond_end, num);
                         
                            del.clear();

                            bool has_delete_att = find(attribute.begin(), attribute.end(), delete_att) != attribute.end();

                            if(has_delete_att){

                                int index_delete_att;
                                bool update_sql=false;
                                bool is_int = update_change_dataTYPE(attribute,dataType, delete_val ,delete_att, index_delete_att,update_sql);

                                if(is_int){
                                    int_val = stoi(delete_val);
                                }

                                int index = index_delete_att;
                             

                                for (size_t i = 1; i < table.size(); ++i) {  // 跳过表头
                              
                                    if (holds_alternative<InnerVector>(table[i])) {
                                        const InnerVector& row = get<InnerVector>(table[i]);

                                        if (index < row.size()) {
                                            if (auto* str = get_if<string>(&row[index])) {
                                                if(*str == delete_val){

                                                    table.erase(table.begin() + i);
                                                    delete_same_value = true;
                                                    break;
                                                }
                                            } 
                                            else if (auto* num = get_if<int>(&row[index])) {
                                                if(*num == int_val){

                                                    table.erase(table.begin() + i);
                                                    delete_same_value = true;
                                                   break;
                                                }
                                            }
                                        }
                                    }
                                }

                                if(!delete_same_value){
                                    cout << "Error: Attribute \""<< delete_val << "\" is no founded in attribute " << delete_att <<" in table " << delete_table_name<< ". Please check your DELETE sql command."<< endl ;
                                }

                                delete_same_value = false;

                            }
                            else{
                                cout << "Error: Attribute \"" << delete_att << "\" not found in the attribute list. Please check your DELETE sql command." << endl;
                                exit(1);
                            }

                        }

                        else{
                            cout << delete_table_name << " table doesn't exit. Please check your DELETE sql command.";
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
            // cout << "Data: ";
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
void f_insert(const string insert_into, const string cond_start,const string cond_end, const int num, vector<string>& insert_, vector<string>& value_type){
    size_t start = insert_into.find(cond_start) + num;
    size_t end = insert_into.find(cond_end);
    string insert = insert_into.substr(start, end - start);
    insert = insert.substr(0, insert.size());


    // vector<string> insert_;  // Vector to store split values
    stringstream ss(insert);
    string token;
    // vector<string> value_type;

    // Split string using ',' as the delimiter
    while (getline(ss, token, ',')) {
        insert_.push_back(token);
    }

    for (string &s : insert_) {
        if (s.find('\'') != std::string::npos){
            s.erase(remove(s.begin(), s.end(), '\''), s.end());  
            value_type.push_back("s");
        }
        else{value_type.push_back("i");}
        
    }
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
    string temp;

    if(update.find("'")!= string::npos){
        update.erase(remove(update.begin(), update.end(), '\''), update.end());
    }

    return update;
}

vector<string> sort(vector<string> insert_attr,vector<string> value,vector<string> attribute ){

    unordered_map<string, string> value_map;
    for (size_t j = 0; j < insert_attr.size(); j++) {
        value_map[insert_attr[j]] = value[j];
    }

    vector<std::string> sorted_values;
    for (const auto& key : attribute) {
        sorted_values.push_back(value_map[key]);
    }

    return sorted_values;
}

bool update_change_dataTYPE(const vector<string>& attribute, const vector<string>& dataType, const string& value, const string& update_att, int& index, const bool update_sql) {

    // Find the index of update_att in attribute
    auto it = find(attribute.begin(), attribute.end(), update_att);
   
    index = distance(attribute.begin(), it);
    string typeOf_att_value = dataType[index];

    if (typeOf_att_value == "int") {
        try {
            stoi(value);  // Try converting value to int
            bool is_int = true;
            return true;

        } catch (const invalid_argument&) {

            if (update_sql){
                cout << "Error: Value \"" << value << "\" from UPDATE SQL is not a valid integer. "
                << "Please check your UPDATE SQL command." << endl;
            }
            else{
                cout << "Error: Value \"" << value << "\" from DELETE SQL is not a valid integer. "
                << "Please check your DELETE SQL command." << endl;
            }
           
            exit(1);
        }
    }

    return false;
}
