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

struct GearPair{
    StarPart pair[2];

    GearPair(StarPart part1, StarPart part2): pair{part1, part2}{}
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

    //Check from first to last. If exactly two numbers with same star
    //are found, multiply them.
    //End iteration by deleting the items with same star.
    cout << "Detecting gears..." << endl;
    list<GearPair> gpairs;
    list<Schem::Point> points_checked;

    for(list<StarPart>::iterator it=spart_list.begin();
        it != spart_list.end(); ++it){

        StarPart originp(*it);
        bool alredy_checked = false;

        for(list<Schem::Point>::iterator jt = points_checked.begin();
            jt != points_checked.end(); ++jt){
            if(originp.star_p==*jt){
                alredy_checked = true;
                break;
            }
        }

        list<StarPart> parts_to_check = {originp};

        list<StarPart>::iterator jt(it);
        jt++;
        while(jt != spart_list.end() && !(alredy_checked)){
            StarPart compp(*jt);

            if((originp.star_p == compp.star_p)){
                parts_to_check.push_back(compp);
            }

            jt++;
        }

        if(parts_to_check.size()==2){
            GearPair pair{parts_to_check.front(), parts_to_check.back()};
            gpairs.push_back(pair);
        }
    }

    for(list<GearPair>::iterator it = gpairs.begin();
        it != gpairs.end(); ++it){
        cout << "Pair: (" << (*it).pair[0].num << ","
             << (*it).pair[1].num << ") has a gear!" << endl;

        result += (*it).pair[0].num * (*it).pair[1].num;
    }

    cout << result << endl;
    return 0;
}
