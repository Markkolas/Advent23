#include "../adventbasics.cpp"
#include <list>

using namespace std;

struct Schem{
    string data;
    int files, cols;

    const char invalid = 0;

    struct Point{
        int p[2];
        Point(int y, int x): p{y,x}{}

        inline bool operator==(const Point& other){
            return (p[0] == other.p[0]) && (p[1] == other.p[1]);
        }

        inline bool operator!=(const Point& other){return !(*this==other);}
    };

    Schem(string s);

    char& operator[](Point p){return data[pts(p)];}
    char& operator[](size_t pos){return data[pos];}

    Point stp(size_t pos); //serial to pararel
    size_t pts(Point p); //pararel to serial

    char getSafely(int y, int x);

};

//TODO: Securize methods
Schem::Point Schem::stp(size_t pos){
    Point point(pos/cols, pos%cols);

    return point;
}

size_t Schem::pts(Point p){
    return p.p[0]*cols+p.p[1];
}

char Schem::getSafely(int y, int x){
    if(x < 0 || x > cols - 1 || y < 0 || y > files - 1) return 0;

    return data[y*cols+x];
}

Schem::Schem(string s){
    cout << "Autodetecting cols... ";
    cols = s.find("\n")+1;
    cout << "Done: " << cols << endl;

    cout << "Cleaning indents...";
    adbasic::cleanIndents(s, ".");
    cout << " Done!" << endl;

    files = s.size()/cols;
    cout << "Schem is size: " << files << "x" << cols << endl;

    data = s;
}

struct Part{
    int num;
    size_t i_indx, e_indx;

    Part(){}
    Part(int initnum): num{initnum}{}
    Part(int initnum, size_t i, size_t e): Part(initnum){
        i_indx = i;
        e_indx = e;
    }

};

struct StarPart:Part{
    Schem::Point star_p;

    StarPart(Part part, Schem::Point p): Part{part}, star_p{p}{};
};

int main(int argc, char *argv[]){
    string in;
    list<Part> numlist;

    if(argc == 1){
        cout << "Specify argument.\n"
             << "0: From console\n"
             << "1: From 'test.txt' file\n"
             << "2: From 'input.txt' file" << endl;

        return 0;
    }

    if(*argv[1] == '0')
        adbasic::getFromConsole(in);
    else if(*argv[1] == '1')
        in = adbasic::readTest();
    else if(*argv[1] == '2')
        in = adbasic::readInput();
    else{
        cout << "Wrong argument, exiting..." << endl;
        return 0;
    }

    Schem schem(in);

    cout << "Detecting numbers..." << endl;
    for(size_t i=0; i<schem.data.size(); i++){
        if(schem[i] >= 48 && schem[i] <= 57){
            size_t e_num_indx;
            string aux = schem.data.substr(i);
            int num = stoi(aux, &e_num_indx);
            Part part(num, i, i+e_num_indx-1);

            numlist.push_back(part);

            i += e_num_indx;
        }
    }

    int result = 0;
    list<StarPart> spart_list;
    cout << "Detecting numbers with stars..." << endl;
    for(list<Part>::iterator it=numlist.begin();
        it != numlist.end(); ++it){
        // cout << "Num: " << (*it).num
        //      << "; Init indx: " << (*it).i_indx
        //      << "; End indx: " << (*it).e_indx << endl;

        Schem::Point left = schem.stp((*it).i_indx);
        Schem::Point right = schem.stp((*it).e_indx);

        // cout << "Checking: " << (*it).num << endl;
        if(left.p[0] != right.p[0]){
            cout << "Something is very odd!" << endl;
            exit(0);
        }

        for(int y = left.p[0]-1; y <= left.p[0]+1; y++){
            for(int x = left.p[1]-1; x <= right.p[1]+1; x++){
                const char c = schem.getSafely(y, x);
                if(c==42){
                    //cout << (*it).num << " has a star!" << endl;
                    Schem::Point spoint(y,x);
                    spart_list.push_back(StarPart(*it, spoint));
                }
            }
        }
    }

    list<list<StarPart>> paired_by_gear_list;
    list<StarPart> aux_list;
    Schem::Point prev_point(-1,-1);//Initial impossible value

    cout << "Detecting numbers with gears..." << endl;
    for(list<StarPart>::iterator it=spart_list.begin();
        it != spart_list.end(); ++it){
        StarPart spart = *it;

        if(spart.star_p == prev_point){
            aux_list.push_back(spart);
        }
        else{
            if(aux_list.size()==2)
                paired_by_gear_list.push_back(aux_list);

            aux_list.clear();
            aux_list.push_back(spart);
        }

        prev_point = (*it).star_p;
    }

    //Another final comprobation just in case the last two values
    //are related to a gear
    if(aux_list.size()==2)
        paired_by_gear_list.push_back(aux_list);

    cout << "Calculating final results..." << endl;
    for(list<list<StarPart>>::iterator it=paired_by_gear_list.begin();
        it != paired_by_gear_list.end(); ++it){
        if((*it).size() != 2){
            cout << "OOOOPs, something went very wrong!" << endl;
            return 0;
        }

        // cout << (*it).front().num << " and " << (*it).back().num
        //      << " have a gear in common!" << endl;

        result += (*it).front().num * (*it).back().num;
    }


    cout << result << endl;
    return 0;
}
