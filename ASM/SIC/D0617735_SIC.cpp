#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;//           {Operation code}  {op coide in hex} {format}
map<string, vector<string> >opcode ={ {"ADD", {"18","3"}},
    {"ADDF", {"58", "3"}},{"ADDR", {"90", "2"}},{"AND", {"40", "3"}},
    {"CLEAR", {"B4", "2"}},{"COMP", {"28", "3"}},{"COMPF", {"88", "3"}},
    {"COMPR", {"A0", "2"}},{"DIV", {"24", "3"}},{"DIVF", {"64", "3"}},
    {"DIVR", {"9C", "2"}},{"FIX", {"C4", "1"}},{"FLOAT", {"C0", "1"}},
    {"HIO", {"F4", "1"}},{"J", {"3C", "3"}},{"JEQ", {"30", "3"}},
    {"JGT", {"34", "3"}},{"JLT", {"34", "3"}},{"JSUB", {"48", "3"}},
    {"LDA", {"00", "3"}},{"LDB", {"68", "3"}},{"LDCH", {"50", "3"}},
    {"LDF", {"70", "3"}},{"LDL", {"08", "3"}},{"LDS", {"6C", "3"}},
    {"LDT", {"74", "3"}},{"LDX", {"04", "3"}},{"LPS", {"D0", "3"}},
    {"MUL", {"20", "3"}},{"MULF", {"60", "3"}},{"MULR", {"98", "2"}},
    {"NORM", {"C8","1"}},{"OR", {"44", "3"}},{"RD", {"D8", "3"}},
    {"RMO", {"AC", "2"}},{"RSUB", {"4C", "3"}},{"SHIFTL", {"A4", "2"}},
    {"SHIFTR", {"A8", "2"}},{"SIO", {"F0", "1"}},{"SSK", {"EC", "3"}},
    {"STA", {"0C", "3"}},{"STB", {"78","3"}},{"STCH", {"54", "3"}},
    {"STF", {"80","3"}},{"STI", {"D4", "3"}},{"STL", {"14", "3"}},
    {"STS", {"7C", "3"}},{"STSW", {"E8", "3"}},{"STT", {"84", "3"}},
    {"STX", {"10", "3"}},{"SUB", {"1C", "3"}},{"SUBF", {"5C", "3"}},
    {"SUBR", {"94", "2"}},{"SVC", {"B0", "2"}},{"TD", {"E0", "3"}},
    {"TIO", {"F8", "1"}},{"TIX", {"2C", "3"}},{"TIXR", {"B8", "2"}},
    {"WD", {"DC", "3"}},
    {"START", {"", "0"}},{"END", {"", "0"}},{"RESB", {"", "0"}},
    {"RESW", {"", "0"}},{"WORD", {"", "3"}},{"BYTE", {"", "1"}},
    {"EQU", {"","0"}}, {"BASE", {"", "0"}}, {"USE", {"", "0"}}};
map<char, string>register_number = {{'A', "0"}, {'X', "1"}, {'L', "2"}, {'B', "3"},{'S', "4"}, {'T', "5"}, {'F', "6"}};// The register number
vector<vector<string>>data, program_block[3];//record the processed file input
map<string, string>symbolTable, EQUTable;// record the labels
vector<vector<string>> objectCode;

string start_loc, end_loc, program_name, end_label;//record the arddess of start and end
int pc;
//string base;

void start();
void read_File();
vector<string> split(string str, char delim);
void reorganization_program_block();
void show_Data();
bool check_Opcode_Error();
bool check_Label_Error();
void general_Location();
int hexString_to_int(string hex);
string int_to_hexString(int dec);
void general_Object_Code();
bool have_Index_Addressing(string label);
string remove_index_addressing(string label);
void write_file();
bool containPlus(string str);
string removePlus(string str);
string get_Argument_Addressing_Mode(string argument);
string remove_Argument_Addressing_mode(string argument);
vector<char> get_Register(string argument);
string PCRelative(string label, string pc);
string Base_Relative(string label, string base);
string general_one_noraml_object_code(string opc, string argument, string pc_address, string base_address, int line);
string general_register_object_code(string opc, string argument);
string get_PC(int line);
string general_EQU_object_code(string opc, string argument);

int main(){
    start();
    return 0;
}
void start(){
    read_File();
    //show_Data();
    reorganization_program_block();
    if(!check_Opcode_Error()){//if no error
        general_Location();
        if(!check_Label_Error()){//if no error
            general_Object_Code();
            //show_Data();
            write_file();
            printf("suessue\n");
        }
    }
}
void read_File(){
    printf("(If  the file is not at the same dictionary with the programme\nplease enter the whole path of file)\nEnter the file name:");
    string fileName;                                                      // test file name SIC_ER_01.asm
    cin>>fileName;//input file name                                                         SIC_ER_02.asm
    ifstream file(fileName);//read file                                                     SIC_ER_03.asm
    if(file.is_open()){//check file is opened                                               SIC_ER_04.asm
        string input;//                                                                     SIC_ER_05.asm
        int line =0;//                                                                      SIC_ER_06.asm
        vector<string>tmp;
        int block =0;
        while(getline(file, input)){//                                                      SIC_ER_07.asm
            tmp = split(input, ' ');//push the words into data                    SIC_OK_01.asm
            if(find(tmp.begin(), tmp.end(), "USE") != tmp.end() && find(tmp.begin(), tmp.end(), "CBLOCK") != tmp.end()){
                block = 2;
            }
            else if(find(tmp.begin(), tmp.end(), "USE") != tmp.end() && find(tmp.begin(), tmp.end(), "CDATA") != tmp.end()){
                block = 1;
            }
            else if(find(tmp.begin(), tmp.end(), "USE") != tmp.end() && tmp.size() == 1){
                block = 0;
                continue;
            }
            program_block[block].push_back(tmp);
        }
    }
    else{
        printf("Cannot find the file.\n");
    }
    file.close();
    
    
}
vector<string> split(string str, char delim){
    stringstream ss(str);
    string item;
    vector<string> words;
    int i =0;
    while(getline(ss, item, delim)){
        if(item == ".")
            break;
        if(item == "" )// if there is a empty string then skip
            continue;
        if(opcode.find(item) != opcode.end()){ //can find the string in opcode that mean it isn't a label
                                               //so reset the index(i) and skip taking label string
            i=1;
            
            if(item == "RSUB"){// this opcode don't need argument
                words.push_back(item);
                break;
            }
            //cout<<"find "<<item<<" in opcode"<<endl;
            }
        if(i >= 3)//if already take 3 strings then mean the coming strings are comment
            break;
        words.push_back(item);
        i++;

    }
    return words;//split all words and return the vector of strings
        
}
void reorganization_program_block(){
    program_block[1].erase(program_block[1].begin());
    program_block[2].erase(program_block[2].begin());
    int line;
    for(int i =0;i<3;i++){
        for(int j=0;j<program_block[i].size();j++){
            if(find(program_block[0][j].begin(), program_block[0][j].end(), "END") != program_block[0][j].end()){
                line = j;
                break;
            }
            data.push_back(program_block[i][j]);
        }
    }
    data.push_back(program_block[0][line]);
}
void show_Data(){
    for(int i =0; i < data.size(); i++){
        for(int j =0; j < data[i].size(); j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
    printf("\n\nShow Symbol table.\n");
    for(auto &[k, v] : symbolTable){
            cout << k << " " << v << endl;
              
    }
    printf("\n\nShow EQU table.\n");
    for(auto &[k, v] : EQUTable){
            cout << k << " " << v << endl;
              
    }
    printf("\n\nobject code\n");
    for(int i =0; i < objectCode.size(); i++){
        cout<<(i+1) << " = " ;
        for(int j =0; j < objectCode[i].size(); j++){
            cout<< objectCode[i][j]<<" " ;
        }
        cout<<endl;
    }


}
bool check_Opcode_Error(){// if there has error return true else false
    bool flag = false;
    string opcode_tmp;
    if(!any_of(data.cbegin(), data.cend(), [](const std::vector<std::string> &vec)-> bool {
        return find(vec.cbegin(), vec.cend(), "START") != vec.cend();})){//check the program isn't have START
        printf("Missing \"START\"\n");
        flag = true;
    }

    if(!any_of(data.cbegin(), data.cend(),[](const std::vector<std::string> &vec)-> bool {//check the program isn't have END
        return find(vec.cbegin(), vec.cend(), "END") != vec.cend();})){
        printf("Missing \"END\"\n");
        flag = true;
    }

    for(int i =0; i< data.size(); i++){//check all opcode
        bool havePlus = false;//check opcode isn't contain "+"
        switch (data[i].size())
        {
        case 3:
            opcode_tmp = data[i][1];//the opcode now is using
            havePlus = containPlus(opcode_tmp);
            if(containPlus(opcode_tmp)){// if the opcode contain + 
                opcode_tmp = removePlus(opcode_tmp);//remove + frome opcode
            }
            if(opcode.find(opcode_tmp) == opcode.end()){// if ther has three things in data mean the second is opcode
                cout<<"Line:" << (i+1) << " " << "\""<< opcode_tmp << "\"" << " is not a opcode." << endl;
                flag = true;
            }
            else if(havePlus && opcode[opcode_tmp][1] != "3"){//if the format isn't 3 mean it cann't be contain "+"
                cout<<"Line:" << (i+1) << " " << "\"" << opcode_tmp << "\"" << " cannot contain \"+\"." << endl;
                flag = true;
                
            }
            else if(opcode_tmp == "START"){
                start_loc = data[i][2];
                program_name = data[i][0];
                
            }
            else if(opcode[opcode_tmp][1] == "2"){//register command
                if(get_Register(data[i][2]).empty()){
                    printf("Line:%d the register argument is error.\n", i+1);
                }
            }
            break;
        
        case 2:
            opcode_tmp = data[i][0];//the opcode now is using
            havePlus = containPlus(opcode_tmp);
            if(havePlus){// if the opcode contain + 
                opcode_tmp = removePlus(opcode_tmp);//remove + frome opcode
            }
            if(opcode.find(opcode_tmp) == opcode.end()){
                cout<<"Line:" << (i+1) << " " << "\"" << opcode_tmp << "\"" << " is not a opcode." << endl;
                flag = true;
            }
            else if(havePlus && opcode[opcode_tmp][1] != "3"){//if the format isn't 3 mean it cann't be contain "+"
                cout<<"Line:" << (i+1) << " " << "\"" << opcode_tmp << "\"" << " cannot contain \"+\"." << endl;
                flag = true;
                
            }
            else if(opcode_tmp == "START"){//check START isn't missing the label
                printf("Line:%d \"START\" is missing a label.\n",i+1);
                flag = true;
            }
            else if(opcode_tmp == "WORD" || opcode_tmp == "BYTE" || opcode_tmp == "RESW" || opcode_tmp == "RESB" || opcode_tmp == "EQU"){
                flag = true;
                printf("Line:%d missing a label.\n", i+1);
            }
            else if(opcode[opcode_tmp][1] == "2"){//register command
                if(get_Register(data[i][1]).empty()){
                    printf("Line:%d the register argument is error.\n", i+1);
                }
            }

            break;
        
        case 1:
            opcode_tmp = data[i][0];
            if(opcode_tmp == "RSUB" || opcode_tmp == "END" || opcode_tmp =="USE"){// the opcode can have no argument
                continue;
            }
            else if(opcode.find(opcode_tmp) == opcode.end()){
                flag = true;
                
                cout<<"Line:" << (i+1) << " " << "\"" << opcode_tmp << "\"" << " is not a opcode." << endl;
            }
            else{
                printf("Line:%d is missing an argument.\n",i+1);
            }    
            break;

        default:
            break;
        }
    }
    return flag;
}

bool check_Label_Error(){
    bool haveError = false;
    for(int i =0; i< data.size(); i++){//pushing the label name and loc into the symbolTable
        if(data[i].size() == 4 && data[i][1] != "EQU"){// label exist when a line have 4 things (label, opcode, argument, loction) 
            string label = data[i][0];
            if(symbolTable.find(label) != symbolTable.end()){// if the label already in symbolTable mean repeated
                cout<<"Line:"<<(i+1)<<" \""<<label<<"\" is repeat.\n";
                haveError = true;
            }
            symbolTable[label] = data[i][3];
            }
    }

    for(int i=0; i<data.size();i++){//handle EQU
        if(data[i].size() == 4){
            string label = data[i][0];
            if(data[i][1] == "EQU"){
                if(data[i][2].find_first_not_of("0123456789") == string::npos){//the argument of EQU is all number
                    EQUTable[label] = data[i][2];
                }
                else{//the argument of EQU is label
                    EQUTable[label] = symbolTable[data[i][2]];
                }
            }
        }
    }
    
    for(int i = 0; i< data.size(); i++){
        string argument;
        switch (data[i].size())
        {
        case 4:
            argument = data[i][2];
            if(get_Argument_Addressing_Mode(argument) != "normal"){
                argument = remove_Argument_Addressing_mode(argument);
            }
            if(data[i][1] == "BYTE"){//check BYTE's argument
                if(argument.find("C'") == string::npos && argument.find("X'") == string::npos){
                    haveError = true;
                    cout<<"Line"<< (i+1) << ": "<< "the argument is error."<<endl;
                }
                else if(argument.find("C'") == (argument.rfind("'")-2) || argument.find("X'") == (argument.rfind("'")-2)){
                    haveError = true;
                    cout<<"Line"<< (i+1) << ": "<< "the argument is missing \" ' \"."<<endl;
                }
            }//                                                            check the label isn't a number
            else if(symbolTable.find(argument) == symbolTable.end() && !(argument.find_first_not_of( "0123456789" ) == string::npos)){
                if(!have_Index_Addressing(argument) /*&& ( symbolTable.find(remove_index_addressing(argument)) == symbolTable.end() )*/){// find the label isn't have index addressing if don't error
                    if(!get_Register(argument).empty()){//check the argument label isn't a register
                    continue;
                    }
                    cout<<"Line"<< (i+1) << ": \""<<argument<< "\"is undefined."<<endl;
                    haveError = true;
                }
                
            }
            break;
        case 3:
            argument = data[i][1];
            
            if(get_Argument_Addressing_Mode(argument) != "normal"){
                argument = remove_Argument_Addressing_mode(argument);
            }

            if(data[i][0] == "END"){
                end_label = symbolTable[argument][1];
            }
            else if(data[i][0] == "USE" && (data[i][1] == "CDATA" || data[i][1] == "CBLOCK")){
                continue;
            }
            else if(symbolTable.find(argument) == symbolTable.end() && !(argument.find_first_not_of( "0123456789" ) == string::npos)){
                
                if(!have_Index_Addressing(argument) /*|| (symbolTable.find(remove_index_addressing(data[i][1])) == symbolTable.end() )*/){// find the label isn't have index addressing if don't error
                    if(!get_Register(argument).empty()){//check the argument label isn't a register
                    continue;
                    }
                    cout<<"Line"<< (i+1) << ": \""<<argument<< "\"is undefined."<<endl;
                    haveError = true;
                }
            }
            break;
        
        case 2:
            if(data[i][0] == "END"){
                end_label = start_loc;
            }
            break;
        default:
            break;
        }
    }
    return haveError;

}

int hexString_to_int(string hex){
    int dec;
    stringstream ss;
    
    ss << std::hex << hex;
    ss >> dec;
    return dec;
}

string int_to_hexString(int dec){
    stringstream ss;
    ss << std::hex << dec;
    return ss.str();
}
void general_Location(){
    data[0].push_back(start_loc);
    pc = hexString_to_int(start_loc);
    string opcode_tmp;
    for(int i =0; (i+1) < data.size(); i++){
        //if((i+1)>=data.size())break;
        string loc;
        bool havePlus = false;
        switch (data[i].size())
        {
        case 4:
            opcode_tmp = data[i][1];
            if(containPlus(opcode_tmp)){// if the opcode contain + 
                opcode_tmp = removePlus(opcode_tmp);//remove + frome opcode
                havePlus = true;
            }

            if(opcode_tmp == "RESW"){
                pc += 3 * stoi(data[i][2]);
            }
            else if(opcode_tmp == "RESB"){
                pc += stoi(data[i][2]);
            }
            else if(opcode_tmp == "BYTE"){
                if(data[i][2].find("C") != string::npos){// check is it char or hex
                    pc += data[i][2].length() - 3;
                }
                else if(data[i][2].find("X") != string::npos){
                    pc += (data[i][2].length() - 3) / 2;
                }
                else{
                    printf("Line %d: the argument is error.\n",(i+1));
                }
            }
            else{//normal opcode
                if(havePlus){//if opcode contain "+" ,location add 4
                    pc += stoi(opcode[opcode_tmp][1]) + 1;
                }
                else//if don't location add 3
                {
                    pc += stoi(opcode[opcode_tmp][1]);
                }
            }
            break;
        case 3:
            opcode_tmp = data[i][0];
            if(containPlus(opcode_tmp)){// if the opcode contain + 
                opcode_tmp = removePlus(opcode_tmp);//remove + frome opcode
                havePlus = true;
            }
            if(opcode_tmp == "USE"){

            }
            else if(havePlus){//if opcode contain "+" ,location add 4
                pc += stoi(opcode[opcode_tmp][1]) + 1;
            }
            else//if don't location add 3
            {
                pc += stoi(opcode[opcode_tmp][1]);
            }
            
            
            break;

        case 2:
            pc += stoi(opcode[data[i][0]][1]);
            break;
        default://if there only contain location that mean nothing there pop the element
            data[i].pop_back();
            break;
        }
        
        //if(data[i].size()>= 2 && data[i].size() <= 4){
            loc = int_to_hexString(pc);
            for(int j = loc.length(); j < 4 ;j++){//add leading 0
                loc = "0" + loc;
            }
            data[i+1].push_back(loc);
        //}

        
        
    }
}
void general_Object_Code(){
    string objcode, opc, full_opc, argument, base, pc_address, addressing_Mode;
    
    for(int i =0; i< data.size();i++){
        objcode = "";
        int origin_line = i;//to note the origin line because i will change will next line is empty
        switch (data[i].size())
        {

        case 4:
            full_opc = opc = data[i][1];
            argument = data[i][2];
            addressing_Mode = get_Argument_Addressing_Mode(argument);
            if(containPlus(opc)){//remove "+" if the opcode contain it, if don't remove before using at opcode searching it will error
                opc = removePlus(opc);
            }
            if(opcode[opc][1] == "0"){//those opcode don't have object code
                objcode = "";
            }
            else if (opc == "WORD"){//general WORD object code
                objcode = int_to_hexString(stoi(argument));
                string zero;
                for(int j = objcode.length(); j < 6; j++){//add the leading zero
                    zero += "0";
                }
                objcode = zero + objcode;
            }
            else if(opc == "BYTE"){//general BYTE object code
                if(argument.find("C'") != string::npos){
                    for(int j =argument.find("'")+1; j < argument.length() - 1; j++){//read char by char
                        objcode = objcode + int_to_hexString(argument[j]);
                    }
                    
                }
                else if(data[i][2].find("X'") != string::npos){
                    objcode = data[i][2].substr(2,data[i][2].length() - 3);//get the hex number between "'" and "'"
                }
            }
            
            else if(opcode[opc][1] == "2"){//if the opcode is register command
                objcode = general_register_object_code(opc, argument);
            }
            else if(EQUTable.find(argument) != EQUTable.end()){//the argument label is a EQU label
                objcode = general_EQU_object_code(full_opc, argument);
            }
            else{//normal opcode to object code
                if(data[i+1].empty()){//if next pc is empty mean the next line is empty
                    while(data[i+1].empty()){//find the next line is not empty
                        i++;
                        vector<string>tmp {"",""};//location, object code
                        objectCode.push_back(tmp);//push back the empty line
                    }
                    pc_address = data[i+1].back();
                }
                else{//the next pc is not empty
                    pc_address = data[i+1].back();
                }
                objcode = general_one_noraml_object_code(full_opc, argument, pc_address, base, i+1);
            }
            break;
        
        case 3:
            full_opc = opc = data[i][0];
            argument = data[i][1];
            if(containPlus(opc)){
                opc = removePlus(opc);
            }
            if(opc == "BASE"){
                objcode = "";
                base = symbolTable[argument];
            }
            else if(opc == "END"){
                    objcode = "";
            }
            if(opcode[opc][1] == "0"){//those opcode don't have object code
                objcode = "";
            }
            else if(opcode[opc][1] == "2"){//if the opcode is register command
                objcode = general_register_object_code(opc, argument);
            }
            else if(EQUTable.find(argument) != EQUTable.end()){//the argument label is a EQU label
                objcode = general_EQU_object_code(full_opc, argument);
            }
            else{//normal opcode to object code
                if(data[i+1].empty()){//if next pc is emptymean the next line is empty
                    while(data[i+1].empty()){//find the next line is not empty
                        i++;
                        vector<string>tmp {"",""};//location, object code
                        objectCode.push_back(tmp);//push back the empty line
                    }
                    pc_address = data[i+1].back();
                }
                else{//the next pc is not empty
                    pc_address = data[i+1].back();
                }
                objcode = general_one_noraml_object_code(full_opc, argument, pc_address, base, i+1);
            }
            break;

        case 2:
            objcode = opcode[data[i][0]][0];
            for(int i =0;i<4;i++){
                objcode = objcode + "0";
            }
            break;
        
        default:
            break;
        }
        if(data[i].empty()){
            vector<string>tmp {"",""};// push back the empty line
            objectCode.push_back(tmp);
        }
        else{
            vector<string>tmp {data[origin_line].back(),objcode};//location, object code
            objectCode.push_back(tmp);
        }
        
        //cout<<"Line:"<<(origin_line+1)<<" = "<<objcode<<endl;

    }
}

bool have_Index_Addressing(string label){
    if(label.find(",X") != string::npos){
        return true;
    }
    else
    {
        return false;
    }
    
}
string remove_index_addressing(string label){
    return label.substr(0,label.length() - 2);
}

void write_file(){
    ofstream list;
    
    list.open("list.txt", ios::out);//writing the list program
    char line[100];
    snprintf(line,100,"%-13s %-13s %-13s %-13s %-13s","Location", "Label", "Opcode", "Argument", "Objectcode");
    list<<line<<endl;
    for(int i =0; i < data.size();i++){
        if(data[i].size() == 0){
            list<<""<<endl;
            continue;
        }
        snprintf(line,15,"%-15s ",data[i].back().c_str());//write loction
        list<<line;
        if(data[i].size() == 3){//fill the blank
                snprintf(line,15,"%-15s","");
                list<<line;
        }
        else if(data[i].size() == 2){//fill the blank
            snprintf(line,15,"%-15s","");
            list<<line;
        }
        for(int j =0;j < data[i].size()-1;j++){
            /*for(int k =0; (k<4 - data[i].size()) && j==0;k++){//fill the blank
                snprintf(line,15,"%-15s ","");
                list<<line;
            }*/
            
            snprintf(line,15,"%-15s",data[i][j].c_str());//write everythings else
            list<<line;
            
        }
        if(data[i].size() == 2){//fill the blank
                snprintf(line,15,"%-15s","");
                list<<line;
        }
        snprintf(line,15,"%-15s",objectCode[i][1].c_str());//write object code
        list<<line<<endl;
    }
    list.close();
    //write record
    ofstream record;
    record.open("record.txt",ios::out);
    string length = int_to_hexString(pc);
    for(int i=0;i<6-length.length();i++){
        length = "0" + length;
    }
    snprintf(line,15, "H^%-6s^%-6s",program_name.c_str(), length.c_str());//write H-record
    record<<line<<endl;
    
    int objcode_length =0;
    int prev_line = 0;
    int now_line = 0;
    for(;now_line<objectCode.size();){
        if(objectCode[now_line][1] != "" && objectCode[now_line].size()!= 0){//init the object code length
            objcode_length = 3;
        }
        else{
            objcode_length = 0;
        }
        
        for(; 
        ( (objcode_length + (objectCode[now_line][1].length() / 2) ) <= 30 && objectCode[now_line][1] != "") 
        || objectCode[now_line][0] == ""
        ; now_line++){//find the object code length ,if greater than 30 and emtry string break
            if(objectCode[now_line][0] == "" ){/*objectCode[now_line][0] == "" mean there is no location and is a empty line*/
                continue;
            }
            objcode_length += objectCode[now_line][1].length() / 2;
        }
        if(objcode_length != 0){
            for(;objectCode[prev_line][1] == "";prev_line++);//if this line if object code is empty go to next line
            string objcode_length_tmp = int_to_hexString(objcode_length);
            if(objcode_length_tmp.length() < 2){//if the hex's object code length is < 2, add the leading 0
                objcode_length_tmp = "0" + objcode_length_tmp;
            }
            string Trecord_start_loction = objectCode[prev_line][0];
            for(int i = Trecord_start_loction.length();i<6;i++){//adding the leading zero to every Trecord start location
                Trecord_start_loction = "0" + Trecord_start_loction;
            }
            record<<"T^"<<Trecord_start_loction<<"^"<<objcode_length_tmp;//wirting T^start location^object length
            for(int i = prev_line; i < now_line;i++){//write T-record
                if(objectCode[i][1] == "")continue;
                record<<"^"<<objectCode[i][1];
            }
            record<<endl;
        }
        prev_line = now_line;
        now_line++;
        
    }
    //printf("length = %d\n",end_label.length());
    for(;end_label.length()<6;){
        end_label = "0" + end_label;
    }
    //cout<<end_label<<endl;
    snprintf(line,10,"E^%6s",end_label.c_str());
    record<<line<<endl;
    record.close();
}

bool containPlus(string str){//check opcode isn't contain +
    if(str.find("+") != string::npos)
        return true;
    else
        return false;
    
}

string removePlus(string str){//remove + from str
    return str.erase(0,1);
}

string get_Argument_Addressing_Mode(string argument){
    if(argument.find("@") != string::npos){
        return "@";
    }
    else  if(argument.find("#") != string::npos){
        return "#";
    }
    else{
        return "normal";
    }
}

string remove_Argument_Addressing_mode(string argument){
    return argument.erase(0,1);
}

vector<char> get_Register(string argument){ //check the arugumnet label isn't register command
    vector<char> reg;
    if(argument.length() == 3){//get two tegister
        if(argument[1] == ','){
            if(register_number.find(argument[0]) != register_number.end() && register_number.find(argument[2]) != register_number.end()){//check two argument isn't a register
                reg.push_back(argument[0]); 
                reg.push_back(argument[2]);
            }
        }
    }
    else if(argument.length() == 1){//get the register
        if(register_number.find(argument[0]) != register_number.end()){
            reg.push_back(argument[0]);
        }
            
    }
    return reg;
    
}

string PCRelative(string label, string pc){
    //cout<<"Label = " << label << " PC = " <<pc_address<<endl;
    //cout<<"PC Relative = " <<address<<endl;
    int label_address = hexString_to_int(symbolTable[label]);
    int pc_address = hexString_to_int(pc);
    int decimal_address = label_address - pc_address;
    if(decimal_address < 0){
        if(decimal_address >= -2047){
            return int_to_hexString(decimal_address);
        }
    }
    else
    {
        if(decimal_address <= 2048)
            return int_to_hexString(decimal_address);
    }
    return "";
    
}

string Base_Relative(string label, string base){
    if(base != ""){
        int label_address = hexString_to_int(symbolTable[label]);
        int base_address = hexString_to_int(base);
        int decimal_address = label_address - base_address;
        if(decimal_address < 0){//if decimal address mean the address is negtive
            if(decimal_address >= -2047){
                return int_to_hexString(decimal_address);
            }
        }
        else
        {
            if(decimal_address <= 2048)
                return int_to_hexString(decimal_address);
        }
    }
    else{
        printf("Please set up a base.\n");
    }
    return "";
}

string general_one_noraml_object_code(string opc, string argument, string pc_address, string base_address, int line){
    string addressing_Mode  = get_Argument_Addressing_Mode(argument);//get arument's addressing mode {"#", "@" or "normal"}
    bool contain_Plus = containPlus(opc);//check opcode isn't contain "+"
    bool index_addressing = have_Index_Addressing(argument);//check argument isn't have index addressing
    bool pc_relative = true, base_relative = false;//expected using PC Relative
    
    if(addressing_Mode != "normal"){//addressing mode isn't normal
        argument = remove_Argument_Addressing_mode(argument);//remove "#" or "@"
    }
    if(contain_Plus){//opcode contain "+"
        opc = removePlus(opc);//remove "+"
    }
    if(index_addressing){//if have inex addressing remove it
        argument = remove_index_addressing(argument);
    }
    string objcode = opcode[opc][0];
    string address;
    if (argument.find_first_not_of("0123456789") == string::npos){//the argument is only contain number
        pc_relative = false; //doesn't need to use pc relative or base relative
        int address_value = hexString_to_int(argument);//change the decmail number argumnent to hex number
        address = argument;  
    }
    else{ //if the argument is label
        if(!contain_Plus){//do pc relative or base relative when the opcode not contain "+" and the argument is label
            address = PCRelative(argument, pc_address);
            if (address == ""){
                address = Base_Relative(argument, base_address);
                pc_relative = false;
                base_relative = true;
            }
            if (address == ""){ //the value lower than -2047 or greater than 2048
                cout << "Line:" << (line + 1) << "PC Relative and Base Relative fail the relative is lower than -2047 or greater than 2048\n"
                    << endl;
                base_relative = false;
            }
        }
        else{
            address = symbolTable[argument];
        }
        
    }
    if (address != ""){ //if the address is fine general object code
            //adding the leading zero
            if(contain_Plus){
                if(address.length() > 5){//if the address length is too long delete the head
                    int delete_length = address.length() - 5;
                    address.erase(0,delete_length-1);
                }
                else{
                    for(int i = address.length(); i <= 5;i++){//if the address length is too short adding the leading zero
                        address = "0" + address;//add the leading zero
                    }
                }
            }
            else{
                if(address.length() > 3){//if the address length is too long delete the head
                    int delete_length = address.length() - 3;
                    address.erase(0,delete_length-1);
                }
                else{
                    for(int i = address.length(); i <= 3;i++){//if the address length is too short adding the leading zero
                    address = "0" + address;//add the leading zero
                }
                }
                
            }
            objcode += address;
        }

    //adding n i x b p e
        int ni = 0;
        int xbpe = 0;
        if(addressing_Mode == "@"){//adding ni to object code
            ni =2;
        }
        else if(addressing_Mode == "#"){
            ni = 1;
        }
        else if(addressing_Mode == "normal"){
            ni = 3;
        }
        string opcode_second_half_byte = "";
        opcode_second_half_byte += objcode[1];
        objcode[1] = int_to_hexString(ni + hexString_to_int(opcode_second_half_byte))[0];//opcode + ni 

        //adding x b p e to object code
        if(index_addressing){//check the argument isn't have index adddressing
                xbpe += 8;//adding x
            }
        if(base_relative){//adding b
            xbpe += 4;
        }
        if(pc_relative){//adding p
            xbpe += 2;
        }
        if(contain_Plus){
            xbpe += 1;//adding e
        }
        objcode[2] = int_to_hexString(xbpe)[0];
        return objcode;
}

string general_register_object_code(string opc, string argument){
    string objcode = opcode[opc][0];
    if(argument.length() == 3){//get two tegister
        if(argument[1] == ','){
            if(register_number.find(argument[0]) != register_number.end() && register_number.find(argument[2]) != register_number.end()){//check two argument isn't a register
                objcode += register_number[argument[0]];
                objcode += register_number[argument[2]];
            }
        }
    }
    else if(argument.length() == 1){//get the register
        if(register_number.find(argument[0]) != register_number.end())
            objcode += register_number[argument[0]];
            objcode += "0";
    }
    return objcode;
}

string general_EQU_object_code(string opc, string argument){
    string addressing_Mode = get_Argument_Addressing_Mode(argument);
    string objcode = "";
    int length;
    if(containPlus(opc)){//if the opcode contain plus the address length is 5
        length = 5;
    }
    else{//if the opcode not contain plus the address length is 3
        length = 3;
    }
    string address = EQUTable[argument];
    for(int i = address.length();i <= length;i++){//adding the leading zero
        address = "0" + address;
    }
    objcode = opcode[opc][0] + address;
    int ni = 0;
    if(addressing_Mode == "@"){//adding ni to object code
        ni +=2;
    }
    else if(addressing_Mode == "#"){
        ni += 1;
    }
    else{
        ni += 3;
    }
    string opcode_second_half_byte = "";
    opcode_second_half_byte += objcode[1];
    objcode[1] = int_to_hexString(ni + hexString_to_int(opcode_second_half_byte))[0];//opcode + ni 
    return objcode;
}
