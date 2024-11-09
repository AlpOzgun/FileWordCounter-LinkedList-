#include <iostream>
#include <fstream>
#include <chrono>
#include <cctype>
#include <string>
#include <iomanip>
using namespace std;

class fileNode{
    public:
        string data;
        fileNode* next;
        fileNode(string fileno){
            next=nullptr;
            this->data=fileno;
        }
};

class fileList{
    private:
        fileNode* head;
    public:
        fileList(){
            head=nullptr;
        }
        void printFiles(){
            fileNode* w=head;
                if(head==nullptr){
                    cout<<"No file includes this word."<<endl;
                    return;
                }
                while(w != nullptr){
                    cout<<w->data;
                    if(w->next != nullptr) cout<<"->";
                    w=w->next;
                }
                cout<<endl;
        }
        void copy(fileList files){
            fileNode* w=files.head;
            while(w != nullptr){
                addFile(w->data);
                w=w->next;
            }
        }
        void addFile(string fileno){
            if(head==nullptr){
                fileNode* p= new fileNode(fileno);
                head=p;
                return;
            }
            fileNode* w=head;
            while(w != nullptr){
                if(w->data.compare(fileno)==0) 
                    return;
                if(w->next == nullptr) 
                    break;
                w=w->next;
            }
            fileNode* p= new fileNode(fileno);
            w->next=p;
        }

};
class wordNode{
    public:
         int count;
        string data;
        wordNode* next;
        fileList files;
        wordNode(string word){
            count=1;
            this->data=word;
            next=nullptr;
        }
        wordNode(wordNode* word){
            data=word->data;
            next=nullptr;
            count=word->count;
            files.copy(word->files);
        }
        void printWord(){
            cout<<"____________________________________________________________________________________________________________________________"<<endl;
            cout<<"Word :"<<data<<endl;
            cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"count: "<<count<<endl;
            cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Files : "<<endl;
            files.printFiles();
            cout<<"_____________________________________________________________________________________________________________________________"<<endl;
        }
};

class wordList{
    private:
        wordNode* head;
        int size;
    public:
        ~wordList(){
            	while(head != nullptr){
                    deleteNode(head->data);
                }    
        }
        wordList(){head=nullptr;}

        void mostUsed(wordList alphabet[]){
            wordNode* w=nullptr;
            wordNode* w2=nullptr;
            wordNode* w3=nullptr;
            wordNode* p=nullptr;
            w=alphabet[0].head;
            int size=0,i=0;
            while(size<10){
                p=new wordNode(w);
                if(w->next==nullptr){
                    do{
                        i++;
                        w=alphabet[i].head;
                    }while(i<26 && w == nullptr);
                    if(i==26){
                        cout<<"Not enough words for top 10"<<endl;
                        return;
                    }
                }
               if(head == nullptr){
                head=p;
                w2=head;
               }
               else{
                w2->next=p;
                w2=w2->next;
               }
               size++;
               w=w->next;
            }
            i++;
            while(i<26){
                w=get_lastNode();
                w2=alphabet[i].head;
                while(w2 != nullptr){
                    if(w2->count < w->count)break;
                    else{
                        p=new wordNode(w2);
                        w->next=p;
                        sort();
                        w3=get_lastNode();
                        //w3->printWord();
                        deleteNode(w3->data);
                        w2=w2->next;
                        w=get_lastNode();
                    }
                }
                i++;
            }
        }


        wordNode* get_lastNode(){
            wordNode *w;
            if(head==nullptr)return head;
            w=head;
            while(w!=nullptr){
                if(w->next==nullptr)break; 
                w=w->next;
            }
            return w;
        }


        void leastUsed(wordList alphabet[26]){
            wordNode *w,*w2,*w3,*w4,*p;
            int i=0,size=0;
            w=alphabet[0].head;
            w2=alphabet[0].get_lastNode();
            i++;

            while(size<10){
                w=alphabet[i].head;
                if(w==w2){
                    w=alphabet[i].head;
                    do{
                    w=alphabet[i].head;
                    i++;
                    }while(i<26 && w == nullptr);
                    if(i==26){
                        cout<<"Nor enough word for least 10"<<endl;
                    }
                }
                p=new wordNode(w2);
                if(head==nullptr){
                    head=p;
                    w3=head;
                }
                else{
                    w3->next=p;
                    w3=w3->next;
                }
                size++;
                while(w != nullptr){
                    if(w->next==nullptr)break;
                    if(w->next==w2)break;
                    w=w->next;
                }
                w2=w;
            }
            
            while(i<26){
                w=alphabet[i].head;
                w2=alphabet[i].get_lastNode();
                w3=get_lastNode();
                if(alphabet[i].head != nullptr)
                while(w3->count >= w2->count){
                    //w3=get_lastNode();
                    p=new wordNode(w2);
                    w3->next=p;
                    sort();
                    w4=get_lastNode();
                    w3=head->next;
                    deleteNode(head->data);
                    head=w3;
                    w3=get_lastNode();
                    while(w != nullptr){
                        if(w==nullptr || w==w2)break;
                        if(w->next==w2)break;
                        w=w->next;
                    }
                    if(w==nullptr || w==w2)break;
                    w2=w;
                    w=alphabet[i].head;
                }
                i++;
            }
            
        }
        void printListForward(){
            wordNode* w=head;
            int i=1;
            cout<<" _______________________________Most_Used_Words________________________________"<<endl;
            while(w != nullptr){
                cout<<"|"<<i<<".";
                //w->printWord();
                cout<<w->data<<"|";
                cout<<"Count : "<<w->count<<right<<setw(79-9-1-to_string(w->count).length()-w->data.length()-to_string(i).length())<<"|"<<endl;
                w=w->next;
                i++;
            }
            cout<<" ----------------------------------------------------------------------------\n"<<endl;
        }
        void printListBackward(){
            wordNode* w=head;
            wordNode* w2=get_lastNode();
            int i=1;
            cout<<" _______________________________Least_Used_Words_______________________________"<<endl;
            while(w != w2){
                while(w != nullptr){
                    if(w->next==w2)break;
                    w=w->next;
                }
                cout<<"|"<<i<<".";
                //w2->printWord();
                cout<<w2->data<<"|";
                cout<<"Count : "<<w2->count<<right<<setw(79-9-1-to_string(w2->count).length()-w2->data.length()-to_string(i).length())<<"|"<<endl;
                w2=w;
                w=head;
                i++;
            }
            cout<<"|"<<i<<".";
            cout<<head->data<<"|";
            cout<<"Count : "<<head->count<<right<<setw(79-9-1-to_string(head->count).length()-head->data.length()-to_string(i).length())<<"|"<<endl;
            cout<<" -----------------------------------------------------------------------------\n"<<endl;
        }






        void addWord(string newWord,string fileno){
            wordNode* w=head;
            if(head==nullptr){
                wordNode* p=new wordNode(newWord);
                head=p;
                head->files.addFile(fileno);
                return;
            }
            while(w != nullptr){
                if(!w->data.compare(newWord)){
                    w->files.addFile(fileno);
                    w->count++;
                    return;
                }
                if(w->next==nullptr)break;
                w=w->next;
            }
            wordNode* p=new wordNode(newWord);
            w->next=p;
            w->next->files.addFile(fileno);
        }

        wordNode* get_wordNode(string word){
            wordNode* w=head;
            if(head==nullptr){
                cerr<<"word does not exist in list"<<endl;
                return nullptr;
            }
            while(w != nullptr){
                if(w->data.compare(word)==0) return w;
                w=w->next;
            }
            cerr<<"word does not exist in list"<<endl;
            return nullptr;            
        }

        void deleteNode(string word){
            wordNode* w=head;
            wordNode* prev=nullptr;
            if(head==nullptr)return;
            if(head->data.compare(word)==0){
                head=head->next;
                delete w;
                return;
            }
                while(w != nullptr){
                    if(w->data.compare(word)==0){
                        prev->next=w->next;
                        delete w;
                        return;
                    }
                    prev=w;
                    w=w->next;
                    }
                }

        void sort(){//done
            if(head==nullptr)return;
            if(head->next==nullptr)return;
            wordNode* dummyNode = new wordNode("ok");
            wordNode* mostUsed=head;
            wordNode* prevMost = nullptr;
            wordNode* prev = nullptr;
            wordNode* w=head;
            wordNode* w2=dummyNode;
            
            while(head != nullptr){

                if(w->count > mostUsed->count){
                    prevMost=prev;
                    mostUsed=w;
                }

                if(w->next==nullptr){
                    if(prevMost==nullptr){
                        head=head->next;
                        w2->next=mostUsed;
                        w2=w2->next;
                    }
                    else{
                        prevMost->next=mostUsed->next;
                        w2->next=mostUsed;
                        w2=w2->next;
                        
                    }
                    mostUsed=head;
                    prevMost=nullptr;
                    w=head;
                    prev=nullptr;
                }
                else{
                    prev=w;
                    w=w->next;
                }
            }
            head=dummyNode->next;
            delete dummyNode;
        }
        void sort2(){
            bool swapped=1;
            wordNode* w=head;
            wordNode* prev=nullptr;
            if(head == nullptr)return;
            if(head->next==nullptr)return;
            while(swapped==1){
                swapped=0;
                w=head;
                prev=nullptr;
                while(w != nullptr){
                    if(w->next==nullptr)break;
                    if(w->count < w->next->count){
                        swapped=1;
                        if(prev == nullptr){
                            prev=head;
                            head=head->next;
                            prev->next=head->next;
                            head->next=prev;
                            w=prev->next;
                        }
                        else{
                            prev->next=w->next;
                            w->next=w->next->next;
                            prev->next->next=w;
                            prev=prev->next;
                            w=w->next;
                        }
                    }
                    else{
                        prev=w;
                        w=w->next;
                    }
                }
            }
        }
        void findWord(string word){
            wordNode* w = head;
            if(head==nullptr){
                cout<<"Word does not exist in any file."<<endl;
                return;
            }
            while(w != nullptr){
                if(w->data.compare(word)==0){
                    w->printWord();
                    return;
                }
                if(w->next==nullptr)break;
                w=w->next;
            }
            cout<<"Word does not exist in any file."<<endl;
        }
};

class WordFinder{
    private:
    wordList  alphabet[26];
    wordList  mostUsed;
    wordList  leastUsed;
    public:
    
    WordFinder(){
    ifstream file;
    int fileno=1;
    char x=' ';
    string word="";
    string filename="";
    chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    cout<<"Please wait as files are being sorted..."<<endl;
    while(fileno <= 10000){
        if(fileno%100==0){
            cout<<"Reached file "<<fileno<<"/10000"<<endl;
        }
        if(fileno%1000==0){
            cout<<fileno/100<<"%"<<" done"<<endl;
        }
        filename="AllDocs/"+to_string(fileno)+".txt";
        file.open(filename);
    while(file.get(x)){
        if(isalpha(x))
        word += tolower(x);
        else if(word != ""){
            alphabet[word[0] -'a'].addWord(word,to_string(fileno));
            word="";
        }
    }
    if(word != ""){
    alphabet[word[0] -'a'].addWord(word,to_string(fileno));
    word="";
    }
    file.close();
    fileno++;
    }
    
    cout<<"Sorting Linked Lists..."<<endl;
    //cout<<"Elapsed Time : "<<elapsed_seconds.count()<<"s\n"<<endl;
    for(int i=0;i<26;i++)
        alphabet[i].sort();//<----------------------------------------------------------------------------------------------------2
    //alphabet['a'-'a'].printhead();
    
    mostUsed.mostUsed(alphabet);
    leastUsed.leastUsed(alphabet);
    //cin>>x;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    interface(elapsed_seconds);
    }
    void interface(std::chrono::duration<double> elapsed_seconds){
        char choice;
        string word;
        char letter;
        wordNode* w=nullptr;
        int i=0;
        int mins=elapsed_seconds.count()/60;
        string min_len=to_string(mins);
        string sec_len=to_string(elapsed_seconds.count()-mins*60);
        do{
            cout<<" ________________________________________________________________________"<<endl;
            cout<<"|                                   WELCOME                              |"<<endl;
            cout<<"|------------------------------------------------------------------------|"<<endl;
            cout<<"|                      Elapsed Time:"<<mins<<"min"<<"-"<<elapsed_seconds.count()-mins*60<<"s"<<setw(77-42-min_len.length()-sec_len.length())<<right<<"|"<<endl;
            cout<<"|________________________________________________________________________|"<<endl;
            cout<<"|  1. Enter a single keyword to list the document(s)(file names)         |"<<endl;
            cout<<"|  2. Print the top 10 words that appeared most frequently               |"<<endl;
            cout<<"|  3. Print the top 10 words that appeared least frequently              |"<<endl;
            cout<<"|  4.Exit                                                                |"<<endl;
            cout<<"|________________________________________________________________________|"<<endl;
            cout<<"  Enter choice(1-4):";
            cin.clear();
            cin>>choice;
            cin.ignore(1000,'\n');
            switch(choice){
                case '1':
                word="";
                cout<<"Enter keyword : ";
                cin>>word;
                i=0;
                while(word[i] != '\0'){
                    word[i]=tolower(word[i]);
                    i++;
                }
                cin.ignore(1000,'\n');
                if(word !=""){
                    if(isalpha(word[0])){
                        w=alphabet[word[0]-'a'].get_wordNode(word);
                        if(w!=nullptr){
                            w->printWord();
                            w=nullptr;
                        }
                    }
                    else
                        cout<<"Word does not exist in list"<<endl;
                }
                word="";
                letter=' ';
                break;
                case '2':
                    mostUsed.printListForward();
                    break;                
                case '3':
                    leastUsed.printListBackward();
                    break;
                case '4':
                    cout<<"Goodbye!"<<endl;
                    break;
                default:
                    cout<<"Please enter numbers 1-4 only!!!\n"<<endl;
            }
        }while(choice != '4');
    }
};
int main(){
    WordFinder plswork;
}