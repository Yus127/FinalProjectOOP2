#include <iostream>
#include <string>
#include <typeinfo>
#include <new>
#include <fstream>
#include <sstream>

using namespace std;

class Video {
    private:
        int length;
        int id;
        string title;
        string genre;
        int rating;
    
    public:
        void setRating(int rating){
            if (rating<=0 || rating >5){
                throw runtime_error("Invalid rating");
            }
            this->rating=rating;
        }
        void setLength(int length) {
            this->length = length;
        }
        void setId(int id){
            this->id=id;
        }
        void setTitle(string title){
            this->title=title;
        }
        void setGenre(string genre){
            this-> genre=genre;
        }
        int getLength() {
            return length;
        }
        int getId(){
            return id;
        }
        int getRating(){
            return rating;
        }
        string getTitle(){
            return title;
        }
        string getGenre(){
            return genre;
        }
        
        friend ostream& operator <<(ostream& os, Video* v){//i dont modify the video
            
            os << "The title of the video is: "<<v->getTitle()<<" the rating is: "<<v->getRating()<<" the length is: "<<v->getLength()<<" and the genre is: "<<v->getGenre();
            return os;
        }
};

class CatalogElement {  //CatalogElement is an abstract class since it has abtracts methods
    private:
        int id;
        string title;
    public:
        string getMainTitle(){
            return title;
        }

        void setId(int id) { this->id = id; }
        int getId() { return id; }
        void setTitle (string title){this->title= title;}
  
        virtual string getTitle(int id)=0;
    
        virtual int getLength() = 0;    //getLength is an abstract method
    
        virtual int getRating() = 0;
        virtual string getGenre() = 0;
        virtual void setRating(int rating) = 0;
        virtual Video* getVideo(int id)=0;
        virtual int getCount()=0;

};

class Movie : public CatalogElement {
    private:
        Video* video;
    public:
        void setVideo(Video* video) {
            this->video = video;
        }
    
    void setRating(int rating){
        video->setRating(rating);
    }
        
    Video* getVideo(int id){
        return video;
    }
    int getCount(){
        return 0;
    }
    int getRating(){
        return video->getRating();
    }
        int getLength() {
            return video->getLength();
        }
    string getGenre() {
        return video->getGenre();
    }
    string getTitle(int id) {
        return video->getTitle();
    }
    
    friend ostream& operator <<(ostream& os, Movie* m) {
        os << m->video;
        return os;
    }
};

class Series : public CatalogElement {
    private:
        Video* videos[10];
        int count;
    public:
  
        Series() {
            count = 0;
        }
        int getCount(){
            return count;
        }
        Video* getVideo(int id){
               return videos[id];
           }
        int getRating(){
              return videos[0]->getRating();
          }
        void setRating(int rating){
            for (int i=0; i<count; i++) {
               videos[i]->setRating(rating);
            }
           }
        string getGenre(){
            return videos[0]->getGenre();
        }
        void addVideo(Video* v) {
            videos[count] = v;
            count++;
        }
        string getTitle(int id) {
            return videos[id]->getTitle();
         }
    
        int getLength() {
            int total = 0;
            for (int i=0; i<count; i++) {
                total += videos[i]->getLength();
            }
            return total;
        }
    
        friend ostream& operator <<(ostream& os, Series* s) {
            os << "The serie "<<s->getMainTitle() << " has " << s->count<<" videos"<<endl;
            return os;
        }
};

class Catalog {
    private:
        CatalogElement* elements[20];
        int counter;
    public:
        Catalog() {
            counter = 0;
        }
        CatalogElement* getElement(int id){
            return elements[id];
        }
        void addCatalogElement(CatalogElement* e) {
            elements[counter] = e;
            counter++;
        }
        void displayLengths() {
            cout << "Available elements " << counter << endl;
            for (int i=0; i<counter; i++) {
                cout << elements[i]->getLength() << endl;
            }
        }
        void deleteCatalogElement(int id) {
            for (int i=0; i<counter; i++) {
                if (elements[i]->getId() == id) {
                    elements[i] = elements[counter-1];
                    counter--;
                    break;
                }
            }
            cout<<"Deleted correctly "<<endl;
        }
        int getCounter(){
            return counter;
        }
        friend ostream& operator <<(ostream& os, const Catalog c){
            os << "Total elements in catalog: "<<c.counter;
            return os;
        }
};
class NetflixMenu{
private:
    Catalog catalog;
    int theId=0;
    
    int selectOption(){
        int option;
        do {
            cout <<"Select an option: ";
            cin >>option;
            performAction(option);
        } while ( option !=7);
        return option;
        
        
    }
    void performAction(int action){
        string title, genre, tmp;
        int length, rating, theId;
        
        Movie* m;
        Series* s;
        Video* v;
        
        int numVideos;
        switch (action){
                
            case 1:
            {
                try{
                    string line;
                    ifstream f1;
                    f1.open("MoviesData.txt");
                    while(!f1.ios_base::eof()){
                    m = new Movie();
                    v=new Video();
                    //cout<<"Movie title: ";
                        
                    getline(f1, line);
                    title = line;
                    //cout << line << endl;
                    //cout<< "movie length ";
                    getline(f1, line);
                    length = stoi(line);
                    //cout << length << endl;
                    //cout<<"movie genre ";
                    getline(f1, line);
                    genre = line;
                    //cout << genre << endl;
                    //cout<<"rating of movie ";
                    getline(f1, line);
                    rating = stoi(line);
                    //cout << rating << endl;
                    
                    v->setLength(length);
                    m->setId(theId);
                    v->setId(theId);
                    theId++;
                    v->setGenre(genre);
                    v->setRating(rating);
                    v->setTitle(title);
                    m->setVideo(v);
                    m->setTitle(title);
                    catalog.addCatalogElement(m);
                    cout<<m<<endl;
                    //cout<<"Movie created"<<endl;
                }
                
                f1.close();
                }catch(exception& e){
                    cout<<e.what()<<endl;
                }
                
                break;
                
            }
                
            case 2:
            {try{
                string line;
                ifstream f2;
                f2.open("SeriesData.txt");
                while(!f2.ios_base::eof()){
                string titleEp, title1;
               
                //cout<<"title: ";
              
                getline(f2, line);
                title1= line;
                //cout<<"genre";
            
                getline(f2, line);
                genre = line;
                    
                //cout<<" number of videos(up to 10): ";
                getline(f2, line);
                numVideos = stoi(line);
             
                    
                s=new Series();
                s->setTitle(title1);
                s->setId(theId);
                //cout<<"rating: ";
               
                //Video *videos[numVideos];
                 
                for(int i =0; i<numVideos; i++){
                    v= new Video();
                    //cout<<"title of episoide "<<i+1<<": ";
                    getline(f2, line);
                    titleEp = line;
                    

                    //cout <<"The length of video "<< i+1<< ": ";
                    getline(f2, line);
                    length = stoi(line);
                    
                    //cout<<"rating of episode "<< i+1<< ": ";
                    getline(f2, line);
                    rating = stoi(line);
                    
                    
                    v->setTitle(titleEp);
                    v->setLength(length);
                    v->setGenre(genre);
                    v->setRating(rating);
                    s->addVideo(v);
                }
                catalog.addCatalogElement(s);
                
                cout<<s;
                }
                f2.close();
                }catch(exception& e){
                    cout<<e.what()<<endl;
                }
                break;}
                
            case 3:{
                int rOg, rating;
                string genre;
                cout<<"1. Videos by rating "<<endl;
                cout<<"2. Videos by genre "<<endl;
                cin >>rOg;
                if (rOg==1){
                    
                    bool isValid=0;
                        do {
                            try {
                                cout << "Tell me the rating ";
                                cin >>rating;
                                if (rating<=0 || rating >5) throw runtime_error("Invalid rating");
                                                                     
                                isValid = 1;
                            } catch (runtime_error& err) {
                            cout << err.what() << endl;
                        }
                        } while (isValid == 0);
                    
                    for(int i=0; i<catalog.getCounter(); i++){
                   
                        string a=typeid(*catalog.getElement(i)).name();
                        string b=typeid(Movie).name();
                        //cout<<a<<"\n"<<b<<"\n";
                        if (a ==b) {
                            if (catalog.getElement(i)->getRating()==rating){
                                cout<<"Movie with same rating: ";
                                cout<<catalog.getElement(i)->getTitle(0)<<endl;
                            }
                            //else{
                                //cout<<"No coincidence "<<endl;
                            //}
                        }
                        else{
                            Video* vi;
                            for (int j=0; j<catalog.getElement(i)->getCount();j++){
                                vi = catalog.getElement(i)->getVideo(j);
                                if(vi->getRating()==rating){
                                    cout<<"Video with the same rating: ";
                                    cout<<vi->getTitle()<<endl;
                                }
                                //else{
                                    //cout<<"No coincidence "<<endl;
                                //}
                            }
                        }
                    }
                }else if(rOg==2){
                    bool isValid=0;
                    do {
                        try {
                            cout << "Tell me the genre: ";
                            cin >> genre;
                            if (genre.size() == 0) throw runtime_error("Genre can't be empty");
                            isValid = 1;
                        } catch (runtime_error& err) {
                            cout << err.what() << endl;
                        }
                    } while (isValid == 0);
                    
                     for(int i=0; i<catalog.getCounter(); i++){
                    
                         string a=typeid(*catalog.getElement(i)).name();
                         string b=typeid(Movie).name();
                         //cout<<a<<"\n"<<b<<"\n";
                         if (a ==b) {
                             if (catalog.getElement(i)->getGenre()==genre){
                                 cout<<"Movie with same genre: ";
                                 cout<<catalog.getElement(i)->getTitle(0)<<endl;
                             }
                             //else{
                                 //cout<<"No coincidence "<<endl;
                            // }
                         }
                         else{
                             Video* vi;
                             for (int j=0; j<catalog.getElement(i)->getCount();j++){
                                 vi = catalog.getElement(i)->getVideo(j);
                                 if(vi->getGenre()==genre){
                                     cout<<"Video with the same genre: ";
                                     cout<<vi->getTitle()<<endl;
                                 }
                                 //else{
                                     //cout<<"No coincidence "<<endl;
                                 //}
                             }
                         }
                     }
                    
                }
                else {cout<<"please enter a valid number"<<endl;}
                break;}
                
                
            case 4:{
                string nameSerie, trash;
               
                bool isVali=0;
                do {
                    try {
                        cout << "Tell me the name of the serie: ";
                         getline(cin, trash);
                        getline(cin, nameSerie);
                        if (nameSerie.size() == 0) throw runtime_error("Empty is not allowed");
                        isVali = 1;
                    } catch (runtime_error& err) {
                        cout << err.what() << endl;
                    }
                } while (isVali == 0);
                
                
                for(int i=0; i<catalog.getCounter(); i++){
                                  
                    string a=typeid(*catalog.getElement(i)).name();
                    string b=typeid(Series).name();
                    //cout<<a<<"\n"<<b<<"\n";
                        if (a ==b) {
                            if (catalog.getElement(i)->getMainTitle()==nameSerie){
                                cout<<"There's a serie with this name "<<endl;
                                cout<<catalog.getElement(i)->getMainTitle()<<endl;
                                bool isValid=0;
                                do {
                                    try {
                                        cout << "Give me the rating ";
                                        cin >>rating;
                                        if (rating<=0 || rating >5) throw runtime_error("Invalid rating");
                                        isValid = 1;
                                    } catch (runtime_error& err) {
                                        cout << err.what() << endl;
                                    }
                                } while (isValid == 0);
                                
                                
                                Video* vi;
                                for (int j=0; j<catalog.getElement(i)->getCount();j++){
                                    vi = catalog.getElement(i)->getVideo(j);
                                    if(vi->getRating()==rating){
                                        cout<<"Episoide with the same rating: ";
                                        cout<<vi->getTitle()<<endl;
                                    }
                                    //else{
                                        //cout<<"No coincidence "<<endl;
                                    //}
                                }

                            }
      
                        }
                    }
                
                break;}
                
            case 5:{
                int  rating;
               
               
                bool isValid=0;
                do {
                    try {
                        cout << "Tell me the rating ";
                          cin >>rating;
                        if (rating<=0 || rating >5) throw runtime_error("Invalid rating");
                                   
                        isValid = 1;
                    } catch (runtime_error& err) {
                        cout << err.what() << endl;
                    }
                } while (isValid == 0);
                
                    
                for(int i=0; i<catalog.getCounter(); i++){
                   
                    string a=typeid(*catalog.getElement(i)).name();
                    string b=typeid(Movie).name();
                    //cout<<a<<"\n"<<b<<"\n";
                    if (a ==b) {
                        //cout<<catalog.getElement(i)<<endl;
                        
                        if (catalog.getElement(i)->getRating()==rating){
                            cout<<"Movie with this rating: ";
                            cout<<catalog.getElement(i)->getTitle(0)<<endl;
                        }
                        //else{
                            //cout<<"No coincidence "<<endl;
                        //}
                    }
            
                }
                break;
                
            }
            case 6:
                string title, trash;
                int newRating;
                int validRating=0;
                getline(cin, trash);
                cout<<"Rate a video "<<endl;
                
                bool isVali=0;
                do {
                    try {
                        cout << "Give me the title of the video (the title of the movie or episoide of a serie): ";
                        getline(cin, title);
                        if (title.size() == 0) throw runtime_error("Empty is not allowed");
                        isVali = 1;
                    } catch (runtime_error& err) {
                            cout << err.what() << endl;
                    }
                } while (isVali == 0);
                
                
                
                for(int i=0; i<catalog.getCounter(); i++){
                    
                    string a=typeid(*catalog.getElement(i)).name();
                    string b=typeid(Movie).name();
                    //cout<<a<<"\n"<<b<<"\n";
                    if (a ==b) {
                    
                        if(catalog.getElement(i)->getTitle(0)==title){
                                
                            do{
                                try{
                                    cout<<"Give me the new rating "<<endl;
                                    cin>>newRating;
                                    catalog.getElement(i)->setRating(newRating);
                                    validRating=1;
                                    //cout<<"Video's new rating "<<catalog.getElement(i)->getRating()<<endl;
                                          
                                }catch(runtime_error& err){
                                    cout<<err.what()<<endl;
                                }
                            }
                            while (validRating==0);
                        }
                        //else{
                            //cout<<"No coincidence"<<endl;
                        //}
                    }
                    else{
                      
                            Video* vi;
                        for (int j=0; j<catalog.getElement(i)->getCount();j++){
                            vi = catalog.getElement(i)->getVideo(j);
                            
                            if(vi->getTitle()==title){
                                do{
                                    try{
                                        cout<<"Give me the new rating: ";
                                        cin>>newRating;
                                        vi->setRating(newRating);
                                        validRating=1;
                                        cout<<"New rating updated"<<endl;
                                        }catch(runtime_error& err){
                                            cout<<err.what()<<endl;
                                        }
                                        }
                                    while (validRating==0);
                                
                                }
                        }
                        
                    }
                }
        }
    }
    
    public:
    void displayOptions(){
        cout<<"1. Upload data movies."<<endl;
        cout<<"2. Upload data series."<<endl;
        cout<<"3. Show the videos with a specific rating or from a specific genre."<<endl;
        cout<<"4. Show the episodes of a specific series with a specific rating."<<endl;
        cout<<"5. Show the movies with a specific rating."<<endl;
        cout<<"6. Rate a video."<<endl;
        cout<<"7. Exit"<<endl;
        selectOption();
    }
    
};

int main() {
    NetflixMenu net;
    net.displayOptions();
}
